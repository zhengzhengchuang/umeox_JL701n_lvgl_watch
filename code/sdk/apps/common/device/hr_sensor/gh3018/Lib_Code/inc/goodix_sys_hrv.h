/*
* HRVLib.h
*/

#ifndef _GOODIX_SYS_HRV_LIB_H_
#define _GOODIX_SYS_HRV_LIB_H_

#include <stdint.h>
#include "iot_sys_def.h"
#if DEBUG_HRV
#include "..\..\HRVTest\goodix_debug.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* ���ش����� */
typedef enum {
    GX_HRV_ALGO_OK              = 0x00000000, // �ɹ����أ����޳�ֵˢ��
    GX_HRV_ALGO_FAILED          = 0x10000001, // ʧ�ܷ���
    GX_HRV_ALGO_NULL_PTR        = 0x10000002, // �ⲿ�����ָ��Ϊ��
    GX_HRV_ALGO_INVALID_PARAM   = 0x10000003, // ������Χ��Ч
    GX_HRV_ALGO_OUT_OF_MEM      = 0x10000004, // �ڴ����ʧ��
    GX_HRV_ALGO_DEINIT_ABORT    = 0x10000005, // �ͷ�ʧ��
    GX_HRV_ALGO_UPDATE          = 0x10000006, // �г�ֵˢ��
}goodix_hrv_ret;

#define PPG_CHANNEL_NUM		            4
#define RRI_NUM                         4
#define ACC_THR_NUM                     4

typedef struct {
    int32_t need_ipl;                                   // �Ƿ���Ҫ��ֵ��1KHz
    int32_t fs;                                         // ������
    int32_t acc_thr[ACC_THR_NUM];                       // acc �����ֵ��Ĭ��ֵΪ��20/10/3/3
}goodix_hrv_config;

typedef struct {
	uint8_t bit_num;                                //����λ��
    int32_t ppg_rawdata[PPG_CHANNEL_NUM];                 // PPGԭʼ�źţ������ͨ��
    int32_t rawdata_cur_adj_flag[PPG_CHANNEL_NUM];        // ���������־λ
    int32_t rawdata_gain_adj_flag[PPG_CHANNEL_NUM];       // ��������־λ
	int32_t acc_x;                                      // ���ټ� x ��
    int32_t acc_y;                                      // ���ټ� y ��
    int32_t acc_z;                                      // ���ټ� z ��
    int32_t frame_id;                                   // ֡���
    int32_t hr;                                         // ��ǰ����ֵ
}goodix_hrv_input_rawdata;

typedef struct {
    int32_t rri[RRI_NUM];                               // RRI�������
    int32_t rri_confidence;                             // ������Ŷ�
	int32_t rri_valid_num;                              // RRI��Ч�������
}goodix_hrv_result;

IOT_SYS_DLL_API uint8_t *goodix_hrv_version(void);

IOT_SYS_DLL_API goodix_hrv_ret goodix_hrv_init(goodix_hrv_config *config);

IOT_SYS_DLL_API goodix_hrv_ret goodix_hrv_calc(goodix_hrv_input_rawdata *input_data, goodix_hrv_result *output_data);

IOT_SYS_DLL_API goodix_hrv_ret goodix_hrv_deinit(void);

#if DEBUG_HRV
IOT_SYS_DLL_API goodix_hrv_debug *copy_debug_addr();
#endif
#ifdef __cplusplus
}
#endif

#endif // _GOODIX_SYS_HRV_LIB_H_
