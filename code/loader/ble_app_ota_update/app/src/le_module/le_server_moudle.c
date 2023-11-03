/*********************************************************************************************
    *   Filename        : le_server_module.c

    *   Description     :

    *   Author          :

    *   Email           : zh-jieli.com

    *   Last modifiled  : 2017-01-17 11:14

    *   Copyright:(c)JIELI  2011-2016  @ , All Rights Reserved.
*********************************************************************************************/

// *****************************************************************************
/* EXAMPLE_START(le_counter): LE Peripheral - Heartbeat Counter over GATT
 *
 * @text All newer operating systems provide GATT Client functionality.
 * The LE Counter examples demonstrates how to specify a minimal GATT Database
 * with a custom GATT Service and a custom Characteristic that sends periodic
 * notifications.
 */
// *****************************************************************************
#include "lib_include.h"
#include "btstack/ble_api.h"
#include "btstack/le_user.h"
#include "btstack/bluetooth.h"
/* #include "custom_cfg.h" */
#include "platform_config.h"


#define TCFG_BLE_SECURITY_EN	0

#include "ble_rcsp_server.h"
#include "le_common.h"
#include "custom_cfg.h"

#if 1
extern void printf_buf(u8 *buf, u32 len);
#define log_info          printf
#define log_info_hexdump  printf_buf
#else
#define log_info(...)
#define log_info_hexdump(...)
#endif


/*--------------------------extern api start -----------------------------*/

/*--------------------------extern api end -------------------------------*/

//------
#define ATT_CTRL_BLOCK_SIZE       (80)                    //note: fixed
#define ATT_LOCAL_PAYLOAD_SIZE    (247)//(200)                   //note: need >= 20
#define ATT_SEND_CBUF_SIZE        (512)                   //note: need >= 20,缓存大小，可修改
#define ATT_RAM_BUFSIZE           (ATT_CTRL_BLOCK_SIZE + ATT_LOCAL_PAYLOAD_SIZE + ATT_SEND_CBUF_SIZE)                   //note:
static u8 att_ram_buffer[ATT_RAM_BUFSIZE] __attribute__((aligned(4)));
//---------------

//---------------
#define ADV_INTERVAL_MIN          (32)

static hci_con_handle_t con_handle;

//加密设置
static const uint8_t sm_min_key_size = 7;
static const uint8_t sm_encryption_flag = 0; ///0--not encrypt, 1--encrypt

//连接参数设置
static const uint8_t connection_update_enable = 1; ///0--disable, 1--enable
static uint8_t connection_update_cnt = 0; ///0--disable, 1--enable
static const struct conn_update_param_t connection_param_table[] = {
    {6, 12, 0, 400},
    {16, 24, 0, 600},//11
    {12, 28, 0, 600},//3.7
    {8,  20, 0,  600},
};
#define CONN_PARAM_TABLE_CNT      (sizeof(connection_param_table)/sizeof(struct conn_update_param_t))

// 广播包内容
/* static u8 adv_data[ADV_RSP_PACKET_MAX];//max is 31 */
// scan_rsp 内容
/* static u8 scan_rsp_data[ADV_RSP_PACKET_MAX];//max is 31 */

#if (ATT_RAM_BUFSIZE < 64)
#error "adv_data & rsp_data buffer error!!!!!!!!!!!!"
#endif

#define adv_data       &att_ram_buffer[0]
#define scan_rsp_data  &att_ram_buffer[32]

static char *gap_device_name = "br22_ble_test";
static u8 gap_device_name_len = 0;
static u8 ble_work_state = 0;
static u8 test_read_write_buf[4];

static void (*app_recieve_callback)(void *priv, void *buf, u16 len) = NULL;
static void (*app_ble_state_callback)(void *priv, ble_state_e state) = NULL;
static void (*ble_resume_send_wakeup)(void) = NULL;
static u32 channel_priv;

static int app_send_user_data_check(u16 len);
static int app_send_user_data_do(void *priv, u8 *data, u16 len);
static int app_send_user_data(u16 handle, u8 *data, u16 len, u8 handle_type);

// Complete Local Name  默认的蓝牙名字

//------------------------------------------------------
//广播参数设置
static void advertisements_setup_init();
extern const char *bt_get_local_name();
static int set_adv_enable(void *priv, u32 en);
static int get_buffer_vaild_len(void *priv);
//------------------------------------------------------
static void send_request_connect_parameter(u8 table_index)
{
    struct conn_update_param_t *param = (void *)&connection_param_table[table_index];//static ram

    log_info("update_request:-%d-%d-%d-%d-\n", param->interval_min, param->interval_max, param->latency, param->timeout);
    if (con_handle) {
        ble_user_cmd_prepare(BLE_CMD_REQ_CONN_PARAM_UPDATE, 2, con_handle, param);
    }
}

static void check_connetion_updata_deal(void)
{
    if (connection_update_enable) {
        if (connection_update_cnt < CONN_PARAM_TABLE_CNT) {
            send_request_connect_parameter(connection_update_cnt);
        }
    }
}

void ble_upgrade_speed(void)
{
    send_request_connect_parameter(0);
}

static void connection_update_complete_success(u8 *packet)
{
    int con_handle, conn_interval, conn_latency, conn_timeout;

    con_handle = hci_subevent_le_connection_update_complete_get_connection_handle(packet);
    conn_interval = hci_subevent_le_connection_update_complete_get_conn_interval(packet);
    conn_latency = hci_subevent_le_connection_update_complete_get_conn_latency(packet);
    conn_timeout = hci_subevent_le_connection_update_complete_get_supervision_timeout(packet);

    log_info("conn_interval = %d\n", conn_interval);
    log_info("conn_latency = %d\n", conn_latency);
    log_info("conn_timeout = %d\n", conn_timeout);
}


static void set_ble_work_state(ble_state_e state)
{
    if (1) {//state != ble_work_state) {
        log_info("ble_work_st:%x->%x\n", ble_work_state, state);
        ble_work_state = state;
        if (app_ble_state_callback) {
            app_ble_state_callback((void *)channel_priv, state);
        }
    }
}

static ble_state_e get_ble_work_state(void)
{
    return ble_work_state;
}

u16 get_ble_update_work_state(void)
{
    return con_handle;
}

static void cbk_sm_packet_handler(uint8_t packet_type, uint16_t channel, uint8_t *packet, uint16_t size)
{
    sm_just_event_t *event = (void *)packet;
    u32 tmp32;
    switch (packet_type) {
    case HCI_EVENT_PACKET:
        switch (hci_event_packet_get_type(packet)) {
        case SM_EVENT_JUST_WORKS_REQUEST:
            sm_just_works_confirm(sm_event_just_works_request_get_handle(packet));
            log_info("Just Works Confirmed.\n");
            break;
        case SM_EVENT_PASSKEY_DISPLAY_NUMBER:
            log_info_hexdump(packet, size);
            memcpy(&tmp32, event->data, 4);
            log_info("Passkey display: %06u.\n", tmp32);
            break;
        }
        break;
    }
}

static void can_send_now_wakeup(void)
{
    //putchar('E');
    if (ble_resume_send_wakeup) {
        ble_resume_send_wakeup();
    }
}

/*
 * @section Packet Handler
 *
 * @text The packet handler is used to:
 *        - stop the counter after a disconnect
 *        - send a notification when the requested ATT_EVENT_CAN_SEND_NOW is received
 */

/* LISTING_START(packetHandler): Packet Handler */
static void cbk_packet_handler(uint8_t packet_type, uint16_t channel, uint8_t *packet, uint16_t size)
{
    int mtu;
    u32 tmp;

    switch (packet_type) {
    case HCI_EVENT_PACKET:
        switch (hci_event_packet_get_type(packet)) {

        /* case DAEMON_EVENT_HCI_PACKET_SENT: */
        /* break; */
        case ATT_EVENT_HANDLE_VALUE_INDICATION_COMPLETE:
            log_info("ATT_EVENT_HANDLE_VALUE_INDICATION_COMPLETE\n");
        case ATT_EVENT_CAN_SEND_NOW:
            can_send_now_wakeup();
            break;

        case HCI_EVENT_LE_META:
            switch (hci_event_le_meta_get_subevent_code(packet)) {
            case HCI_SUBEVENT_LE_CONNECTION_COMPLETE: {
                con_handle = little_endian_read_16(packet, 4);
                log_info("HCI_SUBEVENT_LE_CONNECTION_COMPLETE: %0x\n", con_handle);
                connection_update_complete_success(packet + 8);
#ifdef BLE_GATT_UPDATA_MODULE_CONTROL
                ble_user_cmd_prepare(BLE_CMD_ATT_SEND_INIT, 4, con_handle, att_ram_buffer, ATT_RAM_BUFSIZE, ATT_LOCAL_PAYLOAD_SIZE);
                ble_upgrade_speed();
#endif
                set_ble_work_state(BLE_ST_CONNECT);
            }
            break;

            case HCI_SUBEVENT_LE_CONNECTION_UPDATE_COMPLETE:
                connection_update_complete_success(packet);
                break;
            }
            break;

        case HCI_EVENT_DISCONNECTION_COMPLETE:
            log_info("HCI_EVENT_DISCONNECTION_COMPLETE: %0x\n", packet[5]);
            con_handle = 0;
#ifdef BLE_GATT_UPDATA_MODULE_CONTROL
            ble_user_cmd_prepare(BLE_CMD_ATT_SEND_INIT, 4, con_handle, 0, 0, 0);
#endif
            set_ble_work_state(BLE_ST_IDLE);
            set_adv_enable(0, 1);
            connection_update_cnt = 0;
            break;

        case ATT_EVENT_MTU_EXCHANGE_COMPLETE:
            mtu = att_event_mtu_exchange_complete_get_MTU(packet) - 3;
            log_info("ATT MTU = %u\n", mtu);
#ifdef BLE_GATT_UPDATA_MODULE_CONTROL
            ble_user_cmd_prepare(BLE_CMD_ATT_MTU_SIZE, 1, mtu);
#endif
            break;

        /* case BTSTACK_EVENT_STATE: */
        /* switch (btstack_event_state_get_state(packet)) { */
        /* case HCI_STATE_WORKING: */
        /* log_info("ble_stack init complete\n"); */
        /* set_ble_work_state(BLE_ST_INIT_OK); */
        /* set_adv_enable(0, 1); */
        /* break; */
        /* case HCI_STATE_OFF: */
        /* log_info("ble_stack exit complete\n"); */
        /* set_ble_work_state(BLE_ST_NULL); */
        /* break; */
        /* } */
        /* break; */

        case HCI_EVENT_VENDOR_REMOTE_TEST:
            log_info("--- HCI_EVENT_VENDOR_REMOTE_TEST\n");
            break;

        case L2CAP_EVENT_CONNECTION_PARAMETER_UPDATE_RESPONSE:
            tmp = little_endian_read_16(packet, 4);
            log_info("-update_rsp: %02x\n", tmp);
            if (tmp) {
                connection_update_cnt++;
                log_info("remoter reject!!!\n");
                check_connetion_updata_deal();
            } else {
                connection_update_cnt = CONN_PARAM_TABLE_CNT;
            }
            break;

        case HCI_EVENT_ENCRYPTION_CHANGE:
            log_info("HCI_EVENT_ENCRYPTION_CHANGE= %d\n", packet[2]);
            break;
        }
        break;
    }
}


/* LISTING_END */

/*
 * @section ATT Read
 *
 * @text The ATT Server handles all reads to constant data. For dynamic data like the custom characteristic, the registered
 * att_read_callback is called. To handle long characteristics and long reads, the att_read_callback is first called
 * with buffer == NULL, to request the total value length. Then it will be called again requesting a chunk of the value.
 * See Listing attRead.
 */

/* LISTING_START(attRead): ATT Read */

// ATT Client Read Callback for Dynamic Data
// - if buffer == NULL, don't copy data, just return size of value
// - if buffer != NULL, copy data and return number bytes copied
// @param offset defines start of attribute value
static uint16_t att_read_callback(hci_con_handle_t connection_handle, uint16_t att_handle, uint16_t offset, uint8_t *buffer, uint16_t buffer_size)
{

    uint16_t  att_value_len = 0;
    uint16_t handle = att_handle;

    log_info("read_callback, handle= 0x%04x,buffer= %08x\n", handle, (u32)buffer);

    switch (handle) {
    case ATT_CHARACTERISTIC_2a00_01_VALUE_HANDLE:
        att_value_len = gap_device_name_len;

        if ((offset >= att_value_len) || (offset + buffer_size) > att_value_len) {
            break;
        }

        if (buffer) {
            memcpy(buffer, &gap_device_name[offset], buffer_size);
            att_value_len = buffer_size;
            log_info("\n------read gap_name: %s \n", gap_device_name);
        }
        break;

    case ATT_CHARACTERISTIC_ae02_01_CLIENT_CONFIGURATION_HANDLE:
        if (buffer) {
            buffer[0] = att_get_ccc_config(handle);
            buffer[1] = 0;
        }
        att_value_len = 2;
        break;

    default:
        break;
    }

    log_info("att_value_len= %d\n", att_value_len);
    return att_value_len;

}


/* LISTING_END */
/*
 * @section ATT Write
 *
 * @text The only valid ATT write in this example is to the Client Characteristic Configuration, which configures notification
 * and indication. If the ATT handle matches the client configuration handle, the new configuration value is stored and used
 * in the heartbeat handler to decide if a new value should be sent. See Listing attWrite.
 */

/* LISTING_START(attWrite): ATT Write */
static int att_write_callback(hci_con_handle_t connection_handle, uint16_t att_handle, uint16_t transaction_mode, uint16_t offset, uint8_t *buffer, uint16_t buffer_size)
{
    int result = 0;
    u16 tmp16;

    u16 handle = att_handle;


    switch (handle) {

    case ATT_CHARACTERISTIC_2a00_01_VALUE_HANDLE:
        break;

    case ATT_CHARACTERISTIC_ae02_01_CLIENT_CONFIGURATION_HANDLE:
        set_ble_work_state(BLE_ST_NOTIFY_IDICATE);
        //check_connetion_updata_deal();
        log_info("\n------write ccc:%04x,%02x\n", handle, buffer[0]);
        att_set_ccc_config(handle, buffer[0]);
        break;

    case ATT_CHARACTERISTIC_ae01_01_VALUE_HANDLE:
        printf("\n-ae01_rx(%d):", buffer_size);
        u32 deg_len = (buffer_size > 0x20) ? 0x20 : buffer_size;
        //printf_buf(buffer, deg_len);
        if (app_recieve_callback) {
            app_recieve_callback((void *)channel_priv, buffer, buffer_size);
        }
        //收发测试，自动发送收到的数据;for test
        ///app_send_user_data(ATT_CHARACTERISTIC_ae02_01_VALUE_HANDLE, buffer, buffer_size, ATT_OP_AUTO_READ_CCC);
        break;

    default:
        break;
    }

    return 0;
}

static int app_send_user_data(u16 handle, u8 *data, u16 len, u8 handle_type)
{
    u32 ret = APP_BLE_NO_ERROR;

    if (!con_handle) {
        return APP_BLE_OPERATION_ERROR;
    }

    //printf("usr_send:%x\n", len);
    //printf_buf(data, len);
    ret = ble_user_cmd_prepare(BLE_CMD_ATT_SEND_DATA, 4, handle, data, len, handle_type);
    if (ret == BLE_BUFFER_FULL) {
        ret = APP_BLE_BUFF_FULL;
    }

    if (ret) {
        log_info("app_send_fail:%d !!!!!!\n", ret);
    }
    return ret;
}

#define AD_TYPE_FLAGS                               0x01
#define AD_TYPE_UUID_16                             0x03
#define AD_TYPE_COMPLETE_LOCAL_NAME                 0x09
#define AD_TYPE_MANUFACTURER_SPEC_DATA				0xff
/// Advertising Data
// Flags
#define FLAGS_LE_LIMITED_DISCOVER_MODE		        BIT(0)
#define FLAGS_LE_GENERAL_DISCOVER_MODE		        BIT(1)
#define FLAGS_BREDR_NOT_SUPPORTED		            BIT(2)
#define FLAGS_SIMULTANEOUS_DUAL_CONTROLLER          BIT(3)
#define FLAGS_SIMULTANEOUS_DUAL_HOST		        BIT(4)
#define HID_SERVER_FLAGS    (FLAGS_LE_GENERAL_DISCOVER_MODE|FLAGS_BREDR_NOT_SUPPORTED)
// Complete List of 16-bit Service Class UUIDs
#define HID_SERVER_UUID16   0x12,0x18
// Complete Default Name

/* #define BLE_DEV_NAME_LEN        11 */
/* #define BLE_DEV_NAME            'R', 'A', 'P','O', 'O', ' ', 'V', 'X', '3', '5', '0' */


/* #if defined(CONFIG_CPU_BR22) */
/* #define BLE_DEV_NAME_LEN        14 */
/* #define BLE_DEV_NAME            '6', '9', '3','X','_','L','E','_','U', 'P', 'D', 'A', 'T','E' */
/* #elif defined(CONFIG_CPU_BR23) */
/* #define BLE_DEV_NAME_LEN        14 */
/* #define BLE_DEV_NAME            '6', '9', '5','X','_','L','E','_','U', 'P', 'D', 'A', 'T','E' */
/* #elif defined(CONFIG_CPU_BR26) */
/* #define BLE_DEV_NAME_LEN        14 */
/* #define BLE_DEV_NAME            '6', '9', '4','X','_','L','E','_','U', 'P', 'D', 'A', 'T','E' */
/* #elif defined(CONFIG_CPU_BR18) */
/* #define BLE_DEV_NAME_LEN        14 */
/* #define BLE_DEV_NAME            '8', '0', '0','X','_','L','E','_','U', 'P', 'D', 'A', 'T','E' */
/* #elif defined(CONFIG_CPU_BR21) */
/* #define BLE_DEV_NAME_LEN        14 */
/* #define BLE_DEV_NAME            '6', '9', '2','X','_','L','E','_','U', 'P', 'D', 'A', 'T','E' */
/* #elif defined(CONFIG_CPU_BD29) */
/* #define BLE_DEV_NAME_LEN        14 */
/* #define BLE_DEV_NAME            '6', '3', '0','X','_','L','E','_','U', 'P', 'D', 'A', 'T','E' */
/* #elif defined(CONFIG_CPU_BR25) */
/* #define BLE_DEV_NAME_LEN        14 */
/* #define BLE_DEV_NAME            '6', '9', '6','X','_','L','E','_','U', 'P', 'D', 'A', 'T','E' */
/* #elif defined(CONFIG_CPU_BR30) */
/* #define BLE_DEV_NAME_LEN        14 */
/* #define BLE_DEV_NAME            '6', '9', '7','X','_','L','E','_','U', 'P', 'D', 'A', 'T','E' */
/* #elif defined(CONFIG_CPU_BR34) */
/* #define BLE_DEV_NAME_LEN        14 */
/* #define BLE_DEV_NAME            '6', '9', '8','X','_','L','E','_','U', 'P', 'D', 'A', 'T','E' */
/* #elif defined(CONFIG_CPU_BD19) */
/* #define BLE_DEV_NAME_LEN        14 */
/* #define BLE_DEV_NAME            '6', '3', '2','N','_','L','E','_','U', 'P', 'D', 'A', 'T','E' */
/* #elif defined(CONFIG_CPU_BR36) */
/* #define BLE_DEV_NAME_LEN        14 */
/* #define BLE_DEV_NAME            'B', 'R', '3','6','_','L','E','_','U', 'P', 'D', 'A', 'T','E' */
/* #elif defined(CONFIG_CPU_BR28) */
/* #define BLE_DEV_NAME_LEN        14 */
/* #define BLE_DEV_NAME            'B', 'R', '2','8','_','L','E','_','U', 'P', 'D', 'A', 'T','E' */
/* #endif */

#define BLE_DEV_NAME_LEN        14
#define BLE_DEV_NAME            'J', 'L', 'B','T','_','L','E','_','U', 'P', 'D', 'A', 'T','E'

#define JL_MANUFACTURER_DATA	0x8f,0x03,0x08,0x00,'J','L','B','T','S','D','K'

static const u8 manufactureer_data[] = {JL_MANUFACTURER_DATA};

static u8 adv_ind_data[] = {
//  len---------------------AD Type-------------------------Value
    0x02,                   AD_TYPE_FLAGS,                  0x06,//HID_SERVER_FLAGS,
    0x03,                   AD_TYPE_UUID_16,                0x0a, 0x18, //HID_SERVER_UUID16,
    /* BLE_DEV_NAME_LEN + 1,   AD_TYPE_COMPLETE_LOCAL_NAME,    BLE_DEV_NAME, */
};

static u8 scan_rsp_array[] = {
//  len---------------------AD Type-------------------------Value
    //BLE_DEV_NAME_LEN + 1,   AD_TYPE_COMPLETE_LOCAL_NAME,    BLE_DEV_NAME,
    sizeof(manufactureer_data) + 1,					AD_TYPE_MANUFACTURER_SPEC_DATA, JL_MANUFACTURER_DATA,
};

//------------------------------------------------------
static int make_set_adv_data(void)
{
    u8 offset = 0;
    u8 *buf = adv_data;

    memset(buf, 0, ADV_RSP_PACKET_MAX);
#ifdef BLE_GATT_UPDATA_MODULE_CONTROL
    if (EX_CFG_ERR_NONE == ex_cfg_get_content_api(CFG_ITEM_ADV_IND, buf, 31)) {
        offset = 31;
    } else
#endif
    {
        memcpy(buf, adv_ind_data, sizeof(adv_ind_data));
        offset = sizeof(adv_ind_data);
        offset += make_eir_packet_data(&buf[offset], offset, HCI_EIR_DATATYPE_COMPLETE_LOCAL_NAME, (void *)CONFIG_BT_NAME, sizeof(CONFIG_BT_NAME));
    }
    log_info("adv_data(%d):", offset);
    log_info_hexdump(buf, offset);
    ble_user_cmd_prepare(BLE_CMD_ADV_DATA, 2, offset, buf);

    if (offset > ADV_RSP_PACKET_MAX) {
        puts("***adv_data overflow!!!!!!\n");
        return -1;
    }
    return 0;
}

static int make_set_rsp_data(void)
{

    u8 offset = 0;
    u8 *buf = scan_rsp_data;
    memset(buf, 0, ADV_RSP_PACKET_MAX);
#ifdef BLE_GATT_UPDATA_MODULE_CONTROL
    if (EX_CFG_ERR_NONE == ex_cfg_get_content_api(CFG_ITEM_SCAN_RSP, buf, 31)) {
        offset = 31;
    } else
#endif
    {
        memcpy(buf, scan_rsp_array, sizeof(scan_rsp_array));
        offset = sizeof(scan_rsp_array);
    }
    log_info("rsp_data(%d):", offset);
    log_info_hexdump(buf, offset);
    ble_user_cmd_prepare(BLE_CMD_RSP_DATA, 2, offset, buf);
    return 0;
}

//广播参数设置
static void advertisements_setup_init()
{
    uint8_t adv_type = 0;
    uint8_t adv_channel = 7;
    int   ret = 0;

    ble_user_cmd_prepare(BLE_CMD_ADV_PARAM, 3, ADV_INTERVAL_MIN, adv_type, adv_channel);

    ret |= make_set_adv_data();
    ret |= make_set_rsp_data();

    if (ret) {
        puts("advertisements_setup_init fail !!!!!!\n");
        return;
    }

}

void ble_sm_setup_init(io_capability_t io_type, u8 auth_req, uint8_t min_key_size, u8 security_en)
{
    //setup SM: Display only
    sm_init();
    sm_set_io_capabilities(io_type);
    sm_set_authentication_requirements(auth_req);
    sm_set_encryption_key_size_range(min_key_size, 16);
    sm_set_request_security(security_en);
    //sm_event_callback_set(&cbk_sm_packet_handler);
}


extern void le_device_db_init(void);
extern void le_l2cap_register_packet_handler(void (*handler)(uint8_t packet_type, uint16_t channel, uint8_t *packet, uint16_t size));

u8 gatt_profile_data[0x200] = {0};
void ble_profile_init(void)
{
    printf("ble profile init\n");
    /* setup ATT server */

#ifdef BLE_GATT_UPDATA_MODULE_CONTROL
    le_device_db_init();
    ble_sm_setup_init(IO_CAPABILITY_NO_INPUT_NO_OUTPUT, SM_AUTHREQ_BONDING, 7, TCFG_BLE_SECURITY_EN);
#if 0
    if (EX_CFG_ERR_NONE == ex_cfg_get_content_api(CFG_ITEM_GATT_PROFILE, gatt_profile_data, 0x200)) {
        att_server_init(gatt_profile_data, NULL, att_write_callback);
    } else
#endif
    {
        att_server_init(profile_data, NULL, att_write_callback);
    }

    att_server_register_packet_handler(cbk_packet_handler);
    le_l2cap_register_packet_handler(&cbk_packet_handler);
#endif


    /* gatt_client_register_packet_handler(packet_cbk); */

    // register for HCI events
    hci_event_callback_set(&cbk_packet_handler);
    /* ble_l2cap_register_packet_handler(packet_cbk); */
    /* sm_event_packet_handler_register(packet_cbk); */

}



static int set_adv_enable(void *priv, u32 en)
{
    ble_state_e next_state, cur_state;

    if (con_handle) {
        return APP_BLE_OPERATION_ERROR;
    }

    if (en) {
        next_state = BLE_ST_ADV;
    } else {
        next_state = BLE_ST_IDLE;
    }

    cur_state =  get_ble_work_state();
    switch (cur_state) {
    case BLE_ST_ADV:
    case BLE_ST_IDLE:
    case BLE_ST_INIT_OK:
    case BLE_ST_NULL:
        break;
    default:
        return APP_BLE_OPERATION_ERROR;
        break;
    }

    if (cur_state == next_state) {
        return APP_BLE_NO_ERROR;
    }
    log_info(">>>>>>adv_en:%d\n", en);
    set_ble_work_state(next_state);
    if (en) {
        advertisements_setup_init();
    }
    ble_user_cmd_prepare(BLE_CMD_ADV_ENABLE, 1, en);
    return APP_BLE_NO_ERROR;
}


static int ble_disconnect(void *priv)
{
    if (con_handle) {
        set_ble_work_state(BLE_ST_SEND_DISCONN);
        ble_user_cmd_prepare(BLE_CMD_DISCONNECT, 1, con_handle);
        return APP_BLE_NO_ERROR;
    } else {
        return APP_BLE_OPERATION_ERROR;
    }
}

static int get_buffer_vaild_len(void *priv)
{
    u32 vaild_len = 0;
    ble_user_cmd_prepare(BLE_CMD_ATT_VAILD_LEN, 1, &vaild_len);
    return vaild_len;
}

static int app_send_user_data_do(void *priv, u8 *data, u16 len)
{
#if PRINT_DMA_DATA_EN
    if (len < 128) {
        log_info("-le_tx(%d):");
        log_info_hexdump(data, len);
    } else {
        putchar('L');
    }
#endif
    return app_send_user_data(ATT_CHARACTERISTIC_ae02_01_VALUE_HANDLE, data, len, ATT_OP_AUTO_READ_CCC);
}

static int app_send_user_data_check(u16 len)
{
    u32 buf_space = get_buffer_vaild_len(0);
    if (len <= buf_space) {
        return 1;
    }
    return 0;
}


static int regiest_wakeup_send(void *priv, void *cbk)
{
    ble_resume_send_wakeup = cbk;
    return APP_BLE_NO_ERROR;
}

static int regiest_recieve_cbk(void *priv, void *cbk)
{
    channel_priv = (u32)priv;
    app_recieve_callback = cbk;
    printf("--------------%s %d\n", __func__, __LINE__);
    return APP_BLE_NO_ERROR;
}

int regiest_state_cbk(void *priv, void *cbk)
{
    channel_priv = (u32)priv;
    app_ble_state_callback = cbk;
    return APP_BLE_NO_ERROR;
}

void bt_ble_adv_enable(u8 enable)
{
    set_adv_enable(0, enable);
}

u8 check_ble_is_disconnect(void)
{
    return con_handle;
}

void bt_ble_init(void)
{
    log_info("***** ble_init_rcsp******\n");

    set_ble_work_state(BLE_ST_INIT_OK);
    set_adv_enable(0, 1);
}

void bt_ble_exit(void)
{
    log_info("***** ble_exit******\n");
    set_adv_enable(0, 0);
}

static const struct ble_server_operation_t rcsp_ble_operation = {
    .adv_enable = set_adv_enable,
    .disconnect = ble_disconnect,
    .get_buffer_vaild = get_buffer_vaild_len,
    .send_data = (void *)app_send_user_data_do,
    .regist_wakeup_send = regiest_wakeup_send,
    .regist_recieve_cbk = regiest_recieve_cbk,
    .regist_state_cbk = regiest_state_cbk,
};


void ble_get_server_operation_table(struct ble_server_operation_t **interface_pt)
{
    *interface_pt = (void *)&rcsp_ble_operation;
}





