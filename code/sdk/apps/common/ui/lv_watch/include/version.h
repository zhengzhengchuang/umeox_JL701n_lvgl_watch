#ifndef __VERSION_H__
#define __VERSION_H__

#ifdef __cplusplus
extern "C" {
#endif

/*********************************************************************************
                                    版本号(Vx.x.x)                             
*********************************************************************************/
#define Version_Minor    1
#define Version_Major    0
#define Version_Release  0
#define Num_3_Str(a,b,c) \
    "V" #a "." #b "." #c
#define _Version_Release_Str(a,b,c) \
    Num_3_Str(a,b,c)
#define Version_Release_Str \
    _Version_Release_Str(Version_Release,Version_Major,Version_Minor)

#ifdef __cplusplus
}
#endif

#endif
