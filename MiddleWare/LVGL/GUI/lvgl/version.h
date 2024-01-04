/**
 *******************************************************************************************************************************************
 * @file        version.h
 * @brief       �汾/Ŀ�����
 * @details     /
 * @since       Change Logs:
 * Date         Author       Notes
 * 2022-12-08   lzh          the first version
 * 2023-05-10   lzh          add configurable options( LCD_TYPE / TP_TYPE )
 * @note        ���û�ʹ�õ� TFT-LCD ģ�鲻��ԭ���ѵ��Թ����ͺŷ�Χ��, ��Ҫ���б�д/���Ķ�Ӧ TFT-LCD ��ʾ/���� ����������.
 * ��֪Ϥ : û���κ�һ��������Լ��������ʽ��������ͬ��������Ļ.
 *
 * @remark      �������ۺ��� SWM34S ϵ�в�ͬ��λ��װ( CE-48 / RE-64 / VE-100 )�� DEMO ��������ͬ�� TFT-LCD ��(RGB�ӿ�) ��Ӧ��
 * �û�����Ҫ���ħ������ߵ� Target ��������Ŀ��ѡ��, �ٵ��� "version.h" �ĺ궨���Խ��� <__ƽ̨����__> , ���������ز鿴Ч��.
 *
 * <__ƽ̨����__> :
 * ���Զ��� : Demo �� PCB ˿ӡ / TFT-LCD ģ���ͺ�(����ֱ��� + TP�ͺ�, Ҳ֧���Զ���)
 *
 * ������������������Ŀ���, �����޸�, �û�ֻ��Ҫ���ѡȡ�����б����.
 *
 * enum : ����Ŀ��ѡ�� < ������� __TARGET_CONST__ Ԥ��ֵ >
 *
 * ****************************************** RGB565 ******************************************
 *
 * 0 => LVGL �ٷ�ʾ��, �� UI ��������Ӧ�ֱ���, �����ʾ��ͨ���� lv_ex_conf.h �����ÿ��غ����ѡ��, 
 * �ر���� lv_music ʾ��, ������ͼƬ�زĳ���, Ƭ��Flash�治��, ����Ҫ�� Flash Download �����Ƭ�� SPI Flash�������㷨,
 * ʹ�� SFC ��� Scatter File �趨��ͼƬ�ز������һ������, ���� MDK ��һ������ ���� + �ز�.
 * 
 * 1 => Lib \ SimplLCD_RGB ������ LVGL ��ʵ�� - ���������κ� UI �ز�, ������ʾ��ɫ����
 *
 * 2 => SYNWIT Ӧ������ - 480 * 272 �ֱ��� UI �ز�
 *
 * 3 => SYNWIT Ӧ������ - 480 * 480 �ֱ��� UI �ز�
 *
 * 4 => SYNWIT Ӧ������ - 800 * 480 �ֱ��� UI �ز�
 *
 * 5 => SYNWIT Ӧ������ - 1024 * 600 �ֱ��� UI �ز�
 *
 * ****************************************** ARGB888 ******************************************
 *
 * 6 => LVGL �ٷ�ʾ��, �� UI ��������Ӧ�ֱ���, �����ʾ��ͨ���� lv_ex_conf.h �����ÿ��غ����ѡ��, 
 * �ر���� lv_music ʾ��, ������ͼƬ�زĳ���, Ƭ��Flash�治��, ����Ҫ�� Flash Download �����Ƭ�� SPI Flash�������㷨,
 * ʹ�� SFC ��� Scatter File �趨��ͼƬ�ز������һ������, ���� MDK ��һ������ ���� + �ز�.
 *
 * 7 => Lib \ SimplLCD_RGB ������ LVGL ��ʵ�� - ���������κ� UI �ز�, ������ʾ��ɫ����
 *
 * 8 => SYNWIT Ӧ������ - 480 * 272 �ֱ��� UI �ز�
 *
 * 9 => SYNWIT Ӧ������ - 480 * 480 �ֱ��� UI �ز�
 *
 * 10 => SYNWIT Ӧ������ - 800 * 480 �ֱ��� UI �ز�
 *
 * 11 => SYNWIT Ӧ������ - 1024 * 600 �ֱ��� UI �ز�
 *
 * ****************************************** UserBoot ******************************************
 *
 * 0xFF => UserBoot ����Ӧ��, ��������������Ŀ��Ĺ̼�(��ע��: ʹ��ǰ�����ȴ򿪲鿴 userboot.c �ļ��ڵ�˵��, ����˵��ֱ�������ǲ��е�)
 *
 * @warning     ���ļ��� __TARGET_CONST__ �Ѱ�Ԥ������ Target �趨��ֵ,
 *
 * Ӧ�ñ�����ʱ < ������� >< ������� >< ������� > __TARGET_CONST__ Ԥ��ֵ,
 *
 * (__TARGET_CONST__ �� Keil Option for Target => C/C++(AC6) => Preprocessor Symbols => Define ����)
 *
 * @test        ʵ���� 1024*600-RGB888 ��Ӧ�� lvgl, 8 MB SDRAM �ռ�׽�����, Ч������(�������Ƴ������� SDRAM)
 *******************************************************************************************************************************************
 * @attention
 *
 * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS WITH CODING INFORMATION
 * REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME. AS A RESULT, SYNWIT SHALL NOT BE HELD LIABLE
 * FOR ANY DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE CONTENT
 * OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING INFORMATION CONTAINED HEREIN IN CONN-
 * -ECTION WITH THEIR PRODUCTS.
 *
 * @copyright   2012 Synwit Technology
 *******************************************************************************************************************************************
 */
#ifndef __VERSION_H__
#define __VERSION_H__
/*******************************************************************************************************************************************
 * Public Define Config (�������������û�����ʵ��Ӳ�������������) 
 *******************************************************************************************************************************************/
#define SWM34SCE_PIN48_A2               0 /**< SWM34SCET6_A2 - Demo�� */
#define SWM34SRE_PIN64_A001             1 /**< SWM34SRET6_A001 - Demo�� */
#define SWM34SVE_PIN100_A001            2 /**< SWM34SVET6_A001 - Demo��(�����ڰ汾) */
#define SWM34SVE_PIN100_A002            3 /**< SWM34SVET6_A002 && A003 - Demo�� ��˿ӡ��ͬ, ��������� */

/** (�û���������)�����ʵ��ʹ�õĹٷ� Demo �� PCB ˿ӡѡ���Ӧ�ͺ� */
#define SWM34S_LCM_PCBV                 SWM34SVE_PIN100_A002
#ifndef SWM34S_LCM_PCBV
	#error "Please define the SWM34S_LCM_PCBV"
#endif

/* ���º�����Ϊ��Ļģ��˿ӡ, ��ȡֵΪö��ֵ��ʵ������ */
#define JLT35002A_V2                0 /**< [480*320 / 320*480] ����̩ 3.5 ���� + CTP (JLT35002A �� V2 �汾֧�� RGB ģʽ����, ������� V3 �汾) */
#define JLT4303A                    1 /**< [480*272] ����̩ 4.3 ���� + CTP */
#define TL040WVS03                  2 /**< [480*480] ���Թ�� 4.0 �緽�� + CTP */
#define TL021WVC02                  3 /**< [480*480] ���Թ�� 2.1 ��Բ�� + CTP */
#define JLT4305A                    4 /**< [800*480] ����̩ 4.3 ���� + CTP */
#define ATK_MD0700R                 5 /**< [800*480] ����ԭ�� 7 ���� + CTP */
#define WKS70170                    6 /**< [1024*600] ���ڹ�� 7 ���� + CTP */
#define RS_7_V1_3                   7 /**< [1024*600] õ��Ƽ� 7 ���� + CTP */
/* ��ʹ�ñ�ʾ��δ��������Ļģ���ͺ�, �û����������, ����Ҫ��д��Ӧ�� LCD ��������������� */

/* ���º�����Ϊ TP_ + ����оƬ�ͺ�, ��ȡֵΪö��ֵ��ʵ������ */
#define TP_GT911                   0 /**< CTP : JLT35002A_V2 [480*320] / JLT4303A [480*272] / JLT4305A [800*480] / RS_7_V1_3 [1024*600] */
#define TP_FT6336                  1 /**< CTP : TL040WVS03 [480*480] */
#define TP_CST826                  2 /**< CTP : TL021WVC02 [480*480] */
#define TP_FT5206                  3 /**< CTP : ATK_MD0700R [800*480] / WKS70170 [1024*600] */
#define TP_CST328                  4 /**< CTP : No instance */
#define TP_TANGO_C32               5 /**< CTP : No instance */
#define TP_ILI2117A                6 /**< CTP : No instance */
/* ��ʹ�ñ�ʾ��δ������ TP �ͺ�, �û����������, ����Ҫ��д��Ӧ�� TP ��������������� */


/* ʹ��˵�� : ���û�ѡ��������Ŀ����(������ʾ), ���ݶ�Ӧע��˵��ѡ�� ��Ļģ���ͺ�
 * ��ѡ�����Ļģ��Ϊ��������������ͺ�, �ֱ��ʹ�� �� TP �ͺŻ��Զ�����(�û��޸�)
 * ����, ���û�ѡ����Ļģ�鲻�ڱ����������ͺ��б���, ��Ҫ�ں������������������ �ֱ��ʹ�� / TP �ͺ�
 */
/*******************************************************************************************************************************************
 * RGB565 __TARGET__
 *******************************************************************************************************************************************/
#if         (__TARGET_CONST__ == 0)
    /** ��Ļģ���ͺſ��Զ������, ��Ϊ��ʾ��δ������ģ���ͺ�, �����б�д��� LCD/TP ���� */
    #define LCD_TYPE            JLT4305A

#elif       (__TARGET_CONST__ == 1)
    /** ��Ļģ���ͺſ��Զ������, ��Ϊ��ʾ��δ������ģ���ͺ�, �����б�д��� LCD/TP ���� */
    #define LCD_TYPE            JLT4305A

#elif       (__TARGET_CONST__ == 2)
    /** [480*272/320] ��Ļģ���ͺſ�ѡ JLT35002A_V2 / JLT4303A */
    #define LCD_TYPE            JLT4303A

#elif       (__TARGET_CONST__ == 3)
    /** [480*480] ��Ļģ���ͺſ�ѡ TL040WVS03 / TL021WVC02 */
    #define LCD_TYPE            TL040WVS03

#elif       (__TARGET_CONST__ == 4)
    /** [800*480] ��Ļģ���ͺſ�ѡ JLT4305A / ATK_MD0700R */
    #define LCD_TYPE            JLT4305A

#elif       (__TARGET_CONST__ == 5)
    /** [1024*600] ��Ļģ���ͺſ�ѡ WKS70170 / RS_7_V1_3 */
    #define LCD_TYPE            WKS70170

/*******************************************************************************************************************************************
 * ARGB888 __TARGET__
 *******************************************************************************************************************************************/
#elif       (__TARGET_CONST__ == 6)
    /** ��Ļģ���ͺſ��Զ������, ��Ϊ��ʾ��δ������ģ���ͺ�, �����б�д��� LCD/TP ���� */
    #define LCD_TYPE            JLT4305A

#elif       (__TARGET_CONST__ == 7)
    /** ��Ļģ���ͺſ��Զ������, ��Ϊ��ʾ��δ������ģ���ͺ�, �����б�д��� LCD/TP ���� */
    #define LCD_TYPE            JLT4305A

#elif       (__TARGET_CONST__ == 8)
    /** [480*272] ��Ļģ���ͺſ�ѡ JLT4303A */
    #define LCD_TYPE            JLT4303A

#elif       (__TARGET_CONST__ == 9)
    /** [480*480] ��Ļģ���ͺſ�ѡ TL040WVS03 / TL021WVC02 */
    #define LCD_TYPE            TL040WVS03

#elif       (__TARGET_CONST__ == 10)
    /** [800*480] ��Ļģ���ͺſ�ѡ JLT4305A / ATK_MD0700R */
    #define LCD_TYPE            JLT4305A

#elif       (__TARGET_CONST__ == 11)
    /** [1024*600] ��Ļģ���ͺſ�ѡ WKS70170 / RS_7_V1_3 */
    #define LCD_TYPE            WKS70170

#elif       (__TARGET_CONST__ == 0xFF)
    /** Userboot δʹ����Ļģ���ͺ�, �˴���ʵ������, ��Ϊ��Ӧ�Ա���ʱ���ܳ��ֵĴ��� */
    #define LCD_TYPE            JLT4303A

#else
    #error "Please define the __TARGET_CONST__ "
#endif

/* ��Ļģ���ͺ����Ӧ�� �ֱ��ʹ�� �� TP �ͺ�
 * ���û�����������µ���Ļģ���ͺ�, ��Ҫ�ڴ˴�������Ӧ�� �ֱ��ʹ�� �� TP �ͺ�
 * ��δ������ͺ�, �Ա�ʾ�����������Ļģ���ͺŻ��Զ��� �ֱ��ʹ�� �� TP �ͺ�.
 */
#if (LCD_TYPE == JLT35002A_V2)
    /* JLT35002A_V2 ���� COG ����оƬ֧�ֺ�����ת��, ��ʾ������֧��, �ڴ˴��Ե��ֱ��ʼ���(eg : 320 * 480) */
    #define LCD_HDOT        (480) 
    #define LCD_VDOT        (320)
    #define TP_TYPE         TP_GT911
    
#elif (LCD_TYPE == JLT4303A)
    #define LCD_HDOT        (480)
    #define LCD_VDOT        (272)
    #define TP_TYPE         TP_GT911
    
#elif (LCD_TYPE == TL040WVS03 || LCD_TYPE == TL021WVC02)
    #define LCD_HDOT        (480)
    #define LCD_VDOT        (480)
    #define TP_TYPE         ( (LCD_TYPE == TL040WVS03) ? TP_FT6336 : TP_CST826 )
    
#elif (LCD_TYPE == JLT4305A || LCD_TYPE == ATK_MD0700R)
    #define LCD_HDOT        (800)
    #define LCD_VDOT        (480)
    #define TP_TYPE         ( (LCD_TYPE == JLT4305A) ? TP_GT911 : TP_FT5206 )
    
#elif (LCD_TYPE == WKS70170 || LCD_TYPE == RS_7_V1_3)
    #define LCD_HDOT        (1024)
    #define LCD_VDOT        (600)
    #define TP_TYPE         ( (LCD_TYPE == RS_7_V1_3) ? TP_GT911 : TP_FT5206 )
    
#else
    #error "Please define the LCD_TYPE : you custom"
#endif

#ifndef TP_TYPE
    #error "Please define the TP_TYPE"
#endif

#ifndef LCD_TYPE
    #error "Please define the LCD_TYPE"
#endif

#ifndef LCD_HDOT
	#error "Please define the LCD HDOT"
#endif

#ifndef LCD_VDOT
	#error "Please define the LCD VDOT"
#endif

/*******************************************************************************************************************************************
 * Public Define Constant
 *******************************************************************************************************************************************/
#define LCD_RGB565              (2) /**< RGB565 = 16 Bit */
#define LCD_ARGB888             (4) /**< RGB888 + Alpha = 32 Bit */
/**
 * enum : LCD ��ʾ��ʽ(LCD_FORMAT)
 * ��ֵΪһ�����ص���ռ�õ��ֽ���, ��ʹ�ø�ֵ��Ϸֱ��ʼ���һ֡��ʾ����Ĵ�С
 *
 * 2 => RGB565 (Support RGB or MPU/MCU Interface)
 *
 * 4 => ARGB888 (Only Support RGB Interface)
 */
#if         (0 <= __TARGET_CONST__ && __TARGET_CONST__ < 6)
    #define LCD_FMT                 LCD_RGB565
#elif       (6 <= __TARGET_CONST__ && __TARGET_CONST__ < 12)
    #define LCD_FMT                 LCD_ARGB888
#elif       (__TARGET_CONST__ == 0xFF)
    #define LCD_FMT                 LCD_RGB565 /* ��Ϊ���ƹ������������, ��ʵ������ */
#else
    #error "Please define the LCD_FMT : LCD_RGBxxx"
#endif

/* 48/64 ���޷����ó� ARGB888, ���Ų���. */
#if (LCD_FMT == LCD_ARGB888 && SWM34S_LCM_PCBV < SWM34SVE_PIN100_A001)
    #error "The Target cannot select this option, No more Pins(IO)!"
#endif

#define SIZE_32MB               (0x02000000)
#define SIZE_16MB               (0x01000000)
#define SIZE_8MB                (0x00800000)
#define SIZE_2MB                (0x00200000)

/** SDRAMM_SIZE : ���õ� SDRAM ��С,�ṩ���ƻ�ѡ�� */
#if (SWM34S_LCM_PCBV == SWM34SCE_PIN48_A2)
	#define SDRAMM_SIZE             SIZE_2MB /**< SDRAM ��С = 2 MB */
    #if (LCD_HDOT > 480 && LCD_VDOT >= 480)
        /* 48 �Ų�����������Ļ�ֱ��ʳ��� 480*480, ������ SDRAM ��С���ܽ�����, �޷���Ӧ���ӵ�Ӧ������. */
        #error "The Target cannot select this option, No more SDRAMM_SIZE!"
    #endif
#else
    #define SDRAMM_SIZE             SIZE_8MB /**< SDRAM ��С = 8 MB */
#endif

#endif //__VERSION_H__
