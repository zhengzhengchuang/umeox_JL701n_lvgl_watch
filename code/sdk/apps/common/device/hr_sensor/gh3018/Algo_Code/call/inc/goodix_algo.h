#ifndef GOODIX_ALGO_H
#define GOODIX_ALGO_H

// #include "stdint.h"
// #include "string.h"
// #include "stdio.h"

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

typedef unsigned char       GU8;    /**< 8bit unsigned integer type */
typedef signed char         GS8;    /**< 8bit signed integer type */
typedef unsigned short      GU16;   /**< 16bit unsigned integer type */
typedef signed short        GS16;   /**< 16bit signed integer type */
typedef int                 GS32;   /**< 32bit signed integer type */
typedef unsigned int        GU32;   /**< 32bit unsigned integer type */
typedef float               GF32;   /**< float type */
typedef double              GD64;   /**< double type */
typedef char                GCHAR;  /**< char type */
typedef unsigned char       GBOOL; 
typedef long long           GS64;   /**< 64bit signed integer type */

#define   GH30X_PTR_NULL                           ((void *) 0)
#define   GH30X_CHANNEL_MAP_MAX_CH                             (32)

/* extern log function */
extern void GH30X_Log(GCHAR *chLogString);

/// log support len
#define GH30X_LOG_ALGO_SUP_LEN     (128)

//#define   GH30X_ALGO_LOG_PARAM(...)       do {\
                                                if(g_pSnprintfUser)\
                                                {\
                                                    GCHAR _7iwtO6qX0[GH30X_LOG_ALGO_SUP_LEN] = {0};\
                                                    g_pSnprintfUser(_7iwtO6qX0, GH30X_LOG_ALGO_SUP_LEN, \
                                                            "[gh30x_drv]: "__VA_ARGS__);\
                                                    GH30X_Log(_7iwtO6qX0);\
                                                 }\
                                                 if(g_pPrintfUser)g_pPrintfUser("[gh30x_drv]: "__VA_ARGS__);\
                                            } while (0)

/* ******************************************************************************************* */
//public part
typedef struct
{
    void *pnParametersBuffer;          //STGoodixAlgorithmXXXControlConfigParametersBuffer
    GS32 nBaseBufferLen;
    GS32 *pnBaseBuffer;
}STGoodixAlgorithmControlConfig;

typedef struct
{
    GU8  uchFrameId;                   //frame id 0x00~0xFF
    /* suggest default struct : 0-7:green, 8-15:ir, 16-23:red, 24-31:other(bg) */
    GU8  uchRawdataLen;                //rawdata number(<=32)
    GS32 *pnRawdata;                   //rawdata buffer basic address
    GU8  *puchCurAdjFlag;              //tx current adj flag buffer basic address
    GU16 *pusCurAdjValue;             //tx current adj value buffer basic address, dr0:0-8bit dr1:9-16bit
    GU8  *puchGainAdjValue;            //rx gain adj value buffer basic address
    GU8  *puchChnlColorInfo;           //color info & enable flag buffer basic address 0:Not enable,1:Green,2:Ir,3:Red,4:Ecg,5:Bg
    /* *********************************************************************** */
    void *psAccdata;                   //STGoodixAlgorithmXXXCalculateInputAccdata
    void *pnRefBuffer;                 //STGoodixAlgorithmXXXInputRefBuffer
}STGoodixAlgorithmCalculateInput;

/* Goodix Algorithm Output Struct */
typedef struct
{
    void *pnResult;                    //STGoodixAlgorithmXXXCalculateOutputResult
    GS32  nMiddleBaseBufferLen;
    GS32 *pnMiddleBaseBuffer;
}STGoodixAlgorithmCalculateOutput;

/* Goodix Algorithm Deinit Struct */
typedef struct
{
    void *pnFinalResult;               //STGoodixAlgorithmXXXFinalOutputResult
    GS32 nBaseBufferLen;
    GS32* pnBaseBuffer;
}STGoodixAlgorithmFinalOutput;

/**
 * @brief Goodix Algorithm Whole struct
 */
typedef struct
{
    /* Application section malloc part */
    STGoodixAlgorithmControlConfig stAlgorithmConfig;
    STGoodixAlgorithmCalculateInput stAlgorithmCalcInput;

    /* Algorithm section malloc part */
    STGoodixAlgorithmCalculateOutput stAlgorithmCalcOutput;
    STGoodixAlgorithmFinalOutput stAlgorithmFinalOutput;
}STGoodixAlgorithmInfo;

typedef GS32 (*pfnAlgoCallFunc)(STGoodixAlgorithmInfo* pstGoodixAlgorithmInfo); 
typedef GU8* (*pfnAlgoCallGetVersion)(void); 

#ifdef __cplusplus
}
#endif
#endif
