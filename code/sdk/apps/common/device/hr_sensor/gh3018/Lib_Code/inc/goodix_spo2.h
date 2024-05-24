#ifndef __GOODIX_SPO2_INTERFACE_H
#define __GOODIX_SPO2_INTERFACE_H

#include <stdint.h>
#include "goodix_type.h"

/**
* @brief SPO2 �㷨��������״ֵ̬
*/
typedef enum
{
	GX_ALGO_SPO2_SUCCESS = 0x00000000,			/**< �ɹ�     */
	GX_ALGO_SPO2_RWONG_INPUT = 0x00000001,		/**< �������ݸ�ʽ���Ϸ�     */
	GX_ALGO_SPO2_NO_MEMORY = 0x00000002,        /**< �ڴ�ռ䲻��     */
	GX_ALGO_SPO2_FRAME_UNCOMPLETE = 0x00000003, /**< ���ڽ�����ƽ��������*/
	GX_ALGO_SPO2_WIN_UNCOMPLETE = 0x00000004,   /**< δ����������֡λ�ã�����s��     */
	GX_ALGO_SPO2_UNEXPECTED = 0x00000005,      /*��������߼��쳣 */
}goodix_spo2_ret;

#define CHIP_PPG_CHL_NUM		                4  //оƬ֧�ֵ�ͨ����

typedef struct {
	//raw ������Ϣ
	uint32_t valid_chl_num;			// ��Чͨ����
	uint32_t raw_fs;			    // ԭʼ������
	
	int32_t cali_coef_a;							//У׼����2����
	int32_t cali_coef_b;							//У׼����1����
	int32_t cali_coef_c;							//У׼����������
	//hbʹ�ܱ�־
	uint32_t hb_en_flg;					//hbʹ�ܱ�־
	//���״̬
	uint32_t wear_mode;					//���״̬ 0:�ֻ�  1����ָ  2������
	// acc move thr
	uint32_t acc_thr_max;
	uint32_t acc_thr_min;
	uint32_t acc_thr_scale;
	uint32_t acc_thr_num;
	
	//CTR����
	uint32_t ctr_en_flg;
	uint32_t ctr_red_thr;
}goodix_spo2_config;


typedef struct
{
	uint32_t frameid;								// ֡���
	uint8_t bit_num;                                //����λ��
	int32_t ppg_rawdata[3 * CHIP_PPG_CHL_NUM];		// PPGԭʼ���ݣ������̹�1234-����1234-���1234
	int8_t cur_adj_flg[3 * CHIP_PPG_CHL_NUM];		// ���������־λ�� �����̹�1234-����1234-���1234
	int8_t gain_adj_flg[3 * CHIP_PPG_CHL_NUM];		// ��������־λ�� �����̹�1234-����1234-���1234
	int8_t enable_flg[3 * CHIP_PPG_CHL_NUM];		    // ͨ��ʹ�ܱ�־λ�� �����̹�1234-����1234-���1234

	int32_t ch_agc_drv0[3 * CHIP_PPG_CHL_NUM];		//  ��������0-�����̹�1234-����1234-���1234
	int32_t ch_agc_drv1[3 * CHIP_PPG_CHL_NUM];		//  ��������1-�����̹�1234-����1234-���1234
	int8_t ch_agc_gain[3 * CHIP_PPG_CHL_NUM];	    //  gainֵ1-�����̹�1234-����1234-���1234
	//ch_agc_drv0   ch_agc_drv1  ch_agc_gain
	//int8_t valid_ch_num;                            //ʵ��ʹ��ͨ����

	int32_t acc_x;				//���ٶȼ�x��
	int32_t acc_y;				//���ٶȼ�y��
	int32_t acc_z;				//���ٶȼ�z��
	int32_t wear_on_flag;		//�������־
}goodix_spo2_input_rawdata;

typedef struct
{
	//float32_t spo2[CHIP_PPG_CHL_NUM];				//Ѫ��ֵ
	int32_t spo2[CHIP_PPG_CHL_NUM];				//Ѫ��ֵ*10000
	int32_t valid_level[CHIP_PPG_CHL_NUM];		//���ŵȼ�
	int32_t confi_coeff[CHIP_PPG_CHL_NUM];		//���Ŷ�
	int32_t WeightR[CHIP_PPG_CHL_NUM];		//���Ŷ�

	//HB
	int32_t hb_mean[CHIP_PPG_CHL_NUM];
	int32_t hb_confi_lvl[CHIP_PPG_CHL_NUM];

	int32_t invalidFlg[CHIP_PPG_CHL_NUM];
	int32_t piIR[CHIP_PPG_CHL_NUM];
	int32_t piRed[CHIP_PPG_CHL_NUM];
	int32_t snrIR[CHIP_PPG_CHL_NUM];
	int32_t snrRed[CHIP_PPG_CHL_NUM];
	int32_t r_val[CHIP_PPG_CHL_NUM];				//rֵ��*10000��
	int32_t calc_flg[CHIP_PPG_CHL_NUM];

	//**********************��ͨ���������ֵ***************************//
	int32_t final_spo2;
	int32_t final_valid_level;
	int32_t final_confi_coeff;
	int32_t final_WeightR;

	int32_t final_hb_mean;
	int32_t final_hb_confi_lvl;

	int32_t final_invalidFlg;
	int32_t final_piIR;
	int32_t final_piRed;
	int32_t final_snrIR;
	int32_t final_snrRed;
	int32_t final_r_val;
	int32_t final_calc_flg;
}goodix_spo2_result;

#ifdef __cplusplus
extern "C" {
#endif

	/**
	* @brief SPO2 �����㷨�汾��
	* @param[in]  version     �ⲿ����汾�ſռ䣬����20�ֽ�
	* @param[out] ��
	* @return     ����ִ�����
	*/
	DRVDLL_API goodix_spo2_ret goodix_spo2_version(uint8_t version[100]);

	/**
	* @brief SPO2 �����㷨��ʼ��
	* @param[in]  fs         PPG��ACC�Ĳ�����
	* @param[in]  memaddr    �����㷨ʹ�õ��ⲿ�ڴ��׵�ַ
	* @param[in]  memsize	 �����㷨ʹ�õ��ⲿ�ڴ��С
	* @param[out] ��
	* @return     ����ִ�����
	*/
	DRVDLL_API goodix_spo2_ret goodix_spo2_init(goodix_spo2_config *cfg);

	/**
	* @brief SPO2 Ѫ������
	* @param[in]  raw		����ԭʼ���ݽṹ��
	* @param[out] res		�������ṹ��
	* @return     ����ִ�����
	*/
	DRVDLL_API goodix_spo2_ret goodix_spo2_calc(goodix_spo2_input_rawdata* raw, goodix_spo2_result* res);

	/**
	* @brief SPO2 �㷨���٣��ͷ��ڲ����ڴ�ռ䣬��������ģ���㷨ʱʹ��
	* @param[out] ��
	* @return     ����ִ�����
	*/
	DRVDLL_API goodix_spo2_ret goodix_spo2_deinit(void);

	DRVDLL_API goodix_spo2_ret goodix_spo2_calc_test_bin(float32_t* pin0, float32_t* pin1, goodix_spo2_result* res);
#ifdef __cplusplus
}
#endif

#endif
