#ifndef __FILE_INDEX_H__ 
#define __FILE_INDEX_H__ 

#ifdef __cplusplus
extern "C" {
#endif

struct file_index_t {
    char *name;
    int addr;
    int len;
};

extern const struct file_index_t file_index[];

#define font_common_32_address (0x00000000)

#define watchface_00_bg_index (0x00000000)
#define watchface_00_hour_index (0x00000001)
#define watchface_00_min_index (0x00000002)
#define watchface_00_sec_index (0x00000003)
#define watchface_00_sports_index (0x00000004)
#define weather_bg_index (0x00000005)

#ifdef __cplusplus
} /* extern "C" */
#endif
#endif