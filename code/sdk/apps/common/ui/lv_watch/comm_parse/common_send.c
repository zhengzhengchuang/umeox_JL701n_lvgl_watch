#include "common_cmd.h"
#include "common_send.h"
#include "../lv_watch.h"
#include "../../../../../include_lib/btstack/le/le_user.h"

void umeox_common_le_resp_fail(uint8_t *notify_buf, \
    uint16_t notify_len)
{
    uint32_t verify_sum = 0;
    uint8_t notify_data[Le_Cmd_Max_Len] = {0};

    notify_data[0] = notify_buf[0] | 0x80;
    
    /*********去掉开头与和校验*********/
    memcpy(&notify_data[1], &notify_buf[1], notify_len - 2);

    for(uint8_t i = 0; i < notify_len - 1; i++)
        verify_sum += notify_data[i];

    notify_data[notify_len - 1] = (uint8_t)(verify_sum&(0xff));

    struct ble_server_operation_t *ble_server_operation;
    ble_get_server_operation_table(&ble_server_operation);
    ble_server_operation->send_data(NULL, notify_data, notify_len);

    return;
}

void umeox_common_le_resp_success(uint8_t *notify_buf, \
    uint16_t notify_len)
{
    uint8_t notify_data[Le_Cmd_Max_Len] = {0};

    memcpy(notify_data, notify_buf, notify_len);
    struct ble_server_operation_t *ble_server_operation;
    ble_get_server_operation_table(&ble_server_operation);
    ble_server_operation->send_data(NULL, notify_data, notify_len);

    return;
}

bool umeox_common_le_notify_data(uint8_t *notify_buf, \
    uint16_t notify_len)
{
    int ret;

    if(notify_buf == NULL || notify_len == 0)
        return;

    if(notify_len > Le_Cmd_Max_Len)
        notify_len = Le_Cmd_Max_Len;

    struct ble_server_operation_t *ble_server_operation;
    ble_get_server_operation_table(&ble_server_operation);
    ret = ble_server_operation->send_data(NULL, notify_buf, notify_len);
    if(!ret)
        return true;

    printf("notify_data fail!!!!!!!!!!!!!!!!!!!!!\n");

    return false;
}


