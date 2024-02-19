#include "lang_conf.h"
#include "lang_txtid.h"
#include "lang_table.h"
#include "../lv_watch.h"
#include "../poc_modem/poc_modem_vm.h"

/*********************************************************************************
                                  获取语言                                       
*********************************************************************************/
comm_language_id_t get_comm_sys_language(void)
{
    int vm_lang_id = \
        get_vm_para_cache_with_label(vm_label_sys_language);

    comm_language_id_t lang_id = \
        (comm_language_id_t)vm_lang_id;

    return lang_id;
}

/*********************************************************************************
                                  设置语言                                       
*********************************************************************************/
void set_comm_sys_language(comm_language_id_t lang_id)
{
    comm_language_id_t vm_lang_id = \
        get_vm_para_cache_with_label(vm_label_sys_language);

    if(lang_id == vm_lang_id)
        return;

    set_vm_para_cache_with_label(vm_label_sys_language, \
        lang_id);

    return;
}

/*********************************************************************************
                                  通过对应id获取词条                                       
*********************************************************************************/
const void *get_lang_txt_with_id(comm_lang_txtid_t txtid)
{
    int vm_lang_id = \
        get_vm_para_cache_with_label(vm_label_sys_language);

    comm_language_id_t lang_id = \
        (comm_language_id_t)vm_lang_id;
        

    return (lang_str_table[lang_id][txtid]);
}

/*********************************************************************************
                                  语言是阿拉伯文?(阿拉伯文只有右对齐、居中对齐q)                                 
*********************************************************************************/
bool lang_txt_is_arabic(void)
{
    comm_language_id_t lang_id = \
        get_comm_sys_language();

    if(lang_id == comm_language_id_arabic || \
        lang_id == comm_language_id_urdu || \
            lang_id == comm_language_id_persian)
        return true;

    return false;
}