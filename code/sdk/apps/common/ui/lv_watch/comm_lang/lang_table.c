#include "lang_table.h"

const uint8_t lang_str_table[Comm_Lang_Num]\
    [Comm_Lang_Str_Num][Comm_Lang_Str_Len] = 
{
#if Comm_Conf_Lang_Ar
    //阿拉伯语
    {
        "الهاتف",
        "إشعارات الرسائل",
        "مشغل القران الكريم",
        "أوقات الصلاة",
        "الأذكار",
        "التذكير بالتسبيح",
        "أسماء الله الحسنى",
        "التقويم الهجري",
        "النوم",
        "معدل ضربات القلب",
        "أكسجين الدم",
        "الرياضة",
        "المنبه",
        "المزيد",
        "الإعدادات",
        "الخطي",
    },
#endif

#if Comm_Conf_Lang_En
    //英文
    {
        "Phone",
        "Messages Notifications",
        "Quran Player",
        "Prayer Times",
        "Azkar",
        "Tasbih Reminder",
        "Allah's 99 Name",
        "Hijri Calendar",
        "Sleep",
        "Heart Rate",
        "SPO2",
        "Sports",
        "Alarm",
        "More",
        "Settings",
        "Pedometer",
    },
#endif

#if Comm_Conf_Lang_Fr
    //法语
    {
        "Téléphone",
        "Notifications du messages",
        "Coran Joueur",
        "Horaires de prière",
        "Azkar",
        "Rappel du Tasbih",
        "99 Nom d'Allah",
        "Calendrier Hijri",
        "Sommeil",
        "Rythme cardiaque",
        "SPO2",
        "Sports",
        "Alarme",
        "Plus",
        "Réglages",
        "Podomètre",
    }, 
#endif

#if Comm_Conf_Lang_Ur
    //乌尔都语
    {
        "فون",
        "پیغامات کی اطلاعات",
        "قرآن پاک",
        "نماز کے اوقات",
        "ازکار",
        "تسبیح یاد دہانی",
        "اللہ کے 99 نام",
        "ہجری کیلنڈر",
        "سونا",
        "دل کی شرح",
        "SPO2",
        "کھیل",
        "الارم",
        "مزید",
        "ترتیبات",
        "پیڈومیٹر",
    },
#endif

#if Comm_Conf_Lang_Tu
    //土耳其语
    {
        "Telefon",
        "Mesajlar Bildirimler",
        "Kuran",
        "İbadet Zamanları",
        "Azkar",
        "Tesbih Hatırlatma",
        "Allah'ın 99 İsmi",
        "Hicri Takvim",
        "Uyumak",
        "Nabız",
        "SPO2",
        "Spor Dalları",
        "Alarmı",
        "Daha",
        "Ayarlar",
        "Pedometre",
    },
#endif

#if Comm_Conf_Lang_Ch
    //简体中文
    {
        "电话",
        "消息通知",
        "古兰经播放器",
        "礼拜时间",
        "祈祷词",
        "赞念提醒",
        "阿拉的 99 个尊名",
        "回历",
        "睡眠",
        "心率",
        "血氧",
        "运动",
        "闹钟",
        "更多",
        "设置",
        "计步",
    },
#endif

#if Comm_Conf_Lang_In
    //印尼语
    {
        "Telepon",
        "Pemberitahuan Pesan",
        "Quran",
        "Waktu Sholat",
        "Azkar",
        "Pengingat Tasbih",
        "99 Nama Allah",
        "Kalender Hijriah",
        "Tidur",
        "Detak Jantung",
        "SPO2",
        "Olahraga",
        "Alarm",
        "Lagi",
        "Setelan",
        "Pedometer",
    },
#endif

#if Comm_Conf_Lang_Pe
    //波斯语
    {
        "تلفن",
        "اعلان های پیام ها",
        "قرآن",
        "اوقات نماز",
        "اذکار",
        "یادآوری تسبیح",
        "نام الله 99",
        "تقویم هجری",
        "خواب",
        "ضربان قلب",
        "SPO2",
        "ورزش ها",
        "زنگ هشدار",
        "بیشتر",
        "تنظیمات",
        "گام شمار",
    },
#endif

#if Comm_Conf_Lang_Ge
    //德语
    {
        "Telefon",
        "Nachrichten",
        "Koran-Spieler",
        "Gebetszeiten",
        "Azkar",
        "Tasbih-Erinnerung",
        "Allahs 99 Name",
        "Hijri-Kalender",
        "Schlaf",
        "Herzfrequenz",
        "SPO2",
        "Sport",
        "Alarm",
        "Mehr",
        "Einstellungen",
        "Schrittzähler",
    }, 
#endif

#if Comm_Conf_Lang_Th
    //泰语
    {
        "โทรศัพท์",
        "การแจ้งเตือนข้อความ",
        "คัมภีร์กุรอาน",
        "เวลาละหมาด",
        "อัซคาร์",
        "ตัวเตือนตัสบีห์",
        "ชื่อ 99 ของอัลลอฮ์",
        "ปฏิทินฮิจเราะห์",
        "หลับ",
        "อัตราการเต้นของหัวใจ",
        "SPO2",
        "กีฬา",
        "เตือน",
        "มากกว่า",
        "การตั้งค่า",
        "เครื่องนับก้าว",
    },
#endif

#if Comm_Conf_Lang_Ru
    //俄语
    {
        "Телефон",
        "Уведомления",
        "Коран Игрок",
        "Время молитвы",
        "Азкар",
        "Тасби Напомнить",
        "99 Имя Аллаха",
        "Календарь хиджры",
        "Спать",
        "ЧСС",
        "SPO2",
        "Спортивный",
        "Тревога",
        "Более",
        "Настройки",
        "Шагомер",
    },
#endif

#if Comm_Conf_Lang_Hi
    //印地语
    {
        "फोन",
        "संदेश सूचना",
        "कुरान खेलाड़ी",
        "सप्ताह काल समय",
        "प्रार्थना",
        "स्मार्क जहिना",
        "अला के 99 प्रतिक्षित नाम",
        "मुस्लिम कैलेन्डर",
        "सुप",
        "हृदय दर",
        "Name",
        "चलना",
        "अलार्म घड़ी",
        "अधिक",
        "सेटअप",
        "चरण गणना",
    },
#endif

#if Comm_Conf_Lang_Ma
    //马来西亚语
    {
        "telefon",
        "Pemberitahuan mesej",
        "Pemain Al-Quran",
        "Waktu akhir minggu",
        "Berdoa",
        "Seperti peringatan",
        "99 Nama Ala Dihormati",
        "Kalendar Muslim",
        "tidur",
        "kadar jantung",
        "oksigen darah",
        "gerakan",
        "jam penggera",
        "lebih",
        "tetapkan",
        "Kiraan langkah",
    },
#endif

#if Comm_Conf_Lang_Uz
    //乌兹别克斯坦语
    {
        "Telefon",
        "bildirishnoma",
        "Qur'on o'yinchisi",
        "Ibodat vaqti",
        "ibodatlar",
        "Rahmat eslatma",
        "Allohning 99 ismlari",
        "Hijriy kalendar",
        "uyqu",
        "yurak urish tezligi",
        "qon kislorodi",
        "sport",
        "Uyg'otuvchi soat",
        "Ko'proq",
        "sozlash; o'rnatish",
        "Qadamlarni sanash",
    },
#endif
};

