/**
 *******************************************************************************************************************************************
 * @file        version.h
 * @brief       版本/目标控制
 * @details     /
 * @since       Change Logs:
 * Date         Author       Notes
 * 2022-12-08   lzh          the first version
 * 2023-05-10   lzh          add configurable options( LCD_TYPE / TP_TYPE )
 * @note        若用户使用的 TFT-LCD 模组不在原厂已调试过的型号范围内, 需要自行编写/更改对应 TFT-LCD 显示/触摸 的驱动程序.
 * 请知悉 : 没有任何一个程序可以兼容市面各式各样、不同参数的屏幕.
 *
 * @remark      本例程综合了 SWM34S 系列不同脚位封装( CE-48 / RE-64 / VE-100 )的 DEMO 板驱动不同的 TFT-LCD 屏(RGB接口) 的应用
 * 用户首先要点击魔术棒左边的 Target 下拉进行目标选择, 再调整 "version.h" 的宏定义以进行 <__平台适配__> , 最后编译下载查看效果.
 *
 * <__平台适配__> :
 * 可自定义 : Demo 板 PCB 丝印 / TFT-LCD 模组型号(捆绑分辨率 + TP型号, 也支持自定义)
 *
 * 其他配置项则与下拉目标绑定, 无需修改, 用户只需要点击选取下拉列表项即可.
 *
 * enum : 编译目标选择 < 请勿更改 __TARGET_CONST__ 预设值 >
 *
 * ****************************************** RGB565 ******************************************
 *
 * 0 => LVGL 官方示例, 其 UI 布局自适应分辨率, 具体的示例通过在 lv_ex_conf.h 中配置开关宏进行选择, 
 * 特别对于 lv_music 示例, 由于其图片素材超多, 片内Flash存不下, 故需要在 Flash Download 中添加片外 SPI Flash的下载算法,
 * 使用 SFC 配合 Scatter File 设定将图片素材随程序一并下载, 即在 MDK 下一键下载 程序 + 素材.
 * 
 * 1 => Lib \ SimplLCD_RGB 例程在 LVGL 下实现 - 不依赖于任何 UI 素材, 单纯显示颜色测试
 *
 * 2 => SYNWIT 应用例程 - 480 * 272 分辨率 UI 素材
 *
 * 3 => SYNWIT 应用例程 - 480 * 480 分辨率 UI 素材
 *
 * 4 => SYNWIT 应用例程 - 800 * 480 分辨率 UI 素材
 *
 * 5 => SYNWIT 应用例程 - 1024 * 600 分辨率 UI 素材
 *
 * ****************************************** ARGB888 ******************************************
 *
 * 6 => LVGL 官方示例, 其 UI 布局自适应分辨率, 具体的示例通过在 lv_ex_conf.h 中配置开关宏进行选择, 
 * 特别对于 lv_music 示例, 由于其图片素材超多, 片内Flash存不下, 故需要在 Flash Download 中添加片外 SPI Flash的下载算法,
 * 使用 SFC 配合 Scatter File 设定将图片素材随程序一并下载, 即在 MDK 下一键下载 程序 + 素材.
 *
 * 7 => Lib \ SimplLCD_RGB 例程在 LVGL 下实现 - 不依赖于任何 UI 素材, 单纯显示颜色测试
 *
 * 8 => SYNWIT 应用例程 - 480 * 272 分辨率 UI 素材
 *
 * 9 => SYNWIT 应用例程 - 480 * 480 分辨率 UI 素材
 *
 * 10 => SYNWIT 应用例程 - 800 * 480 分辨率 UI 素材
 *
 * 11 => SYNWIT 应用例程 - 1024 * 600 分辨率 UI 素材
 *
 * ****************************************** UserBoot ******************************************
 *
 * 0xFF => UserBoot 功能应用, 适用于上述所有目标的固件(请注意: 使用前必须先打开查看 userboot.c 文件内的说明, 不看说明直接下载是不行的)
 *
 * @warning     本文件中 __TARGET_CONST__ 已按预期下拉 Target 设定赋值,
 *
 * 应用本工程时 < 请勿更改 >< 请勿更改 >< 请勿更改 > __TARGET_CONST__ 预设值,
 *
 * (__TARGET_CONST__ 在 Keil Option for Target => C/C++(AC6) => Preprocessor Symbols => Define 设置)
 *
 * @test        实测在 1024*600-RGB888 下应用 lvgl, 8 MB SDRAM 空间捉襟见肘, 效果不佳(待后续推出大容量 SDRAM)
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
 * Public Define Config (以下配置项需用户根据实际硬件环境情况配置) 
 *******************************************************************************************************************************************/
#define SWM34SCE_PIN48_A2               0 /**< SWM34SCET6_A2 - Demo板 */
#define SWM34SRE_PIN64_A001             1 /**< SWM34SRET6_A001 - Demo板 */
#define SWM34SVE_PIN100_A001            2 /**< SWM34SVET6_A001 - Demo板(较早期版本) */
#define SWM34SVE_PIN100_A002            3 /**< SWM34SVET6_A002 && A003 - Demo板 仅丝印不同, 其余均兼容 */

/** (用户必须设置)请根据实际使用的官方 Demo 板 PCB 丝印选择对应型号 */
#define SWM34S_LCM_PCBV                 SWM34SVE_PIN100_A002
#ifndef SWM34S_LCM_PCBV
	#error "Please define the SWM34S_LCM_PCBV"
#endif

/* 以下宏名均为屏幕模组丝印, 其取值为枚举值无实际意义 */
#define JLT35002A_V2                0 /**< [480*320 / 320*480] 晶力泰 3.5 寸屏 + CTP (JLT35002A 仅 V2 版本支持 RGB 模式驱动, 请勿买错 V3 版本) */
#define JLT4303A                    1 /**< [480*272] 晶力泰 4.3 寸屏 + CTP */
#define TL040WVS03                  2 /**< [480*480] 冠显光电 4.0 寸方屏 + CTP */
#define TL021WVC02                  3 /**< [480*480] 冠显光电 2.1 寸圆屏 + CTP */
#define JLT4305A                    4 /**< [800*480] 晶力泰 4.3 寸屏 + CTP */
#define ATK_MD0700R                 5 /**< [800*480] 正点原子 7 寸屏 + CTP */
#define WKS70170                    6 /**< [1024*600] 慧勤光电 7 寸屏 + CTP */
#define RS_7_V1_3                   7 /**< [1024*600] 玫瑰科技 7 寸屏 + CTP */
/* 如使用本示例未包含的屏幕模组型号, 用户可自行添加, 但需要编写对应的 LCD 驱动并添加至工程 */

/* 以下宏名均为 TP_ + 具体芯片型号, 其取值为枚举值无实际意义 */
#define TP_GT911                   0 /**< CTP : JLT35002A_V2 [480*320] / JLT4303A [480*272] / JLT4305A [800*480] / RS_7_V1_3 [1024*600] */
#define TP_FT6336                  1 /**< CTP : TL040WVS03 [480*480] */
#define TP_CST826                  2 /**< CTP : TL021WVC02 [480*480] */
#define TP_FT5206                  3 /**< CTP : ATK_MD0700R [800*480] / WKS70170 [1024*600] */
#define TP_CST328                  4 /**< CTP : No instance */
#define TP_TANGO_C32               5 /**< CTP : No instance */
#define TP_ILI2117A                6 /**< CTP : No instance */
/* 如使用本示例未包含的 TP 型号, 用户可自行添加, 但需要编写对应的 TP 驱动并添加至工程 */


/* 使用说明 : 在用户选定的下拉目标下(高亮提示), 根据对应注释说明选择 屏幕模组型号
 * 若选择的屏幕模组为本例程已适配的型号, 分辨率规格 和 TP 型号会自动适配(用户无感)
 * 否则, 若用户选择屏幕模组不在本例程适配型号列表内, 需要在后续条件宏中自行添加 分辨率规格 / TP 型号
 */
/*******************************************************************************************************************************************
 * RGB565 __TARGET__
 *******************************************************************************************************************************************/
#if         (__TARGET_CONST__ == 0)
    /** 屏幕模组型号可自定义更换, 如为本示例未包含的模组型号, 须自行编写添加 LCD/TP 驱动 */
    #define LCD_TYPE            JLT4305A

#elif       (__TARGET_CONST__ == 1)
    /** 屏幕模组型号可自定义更换, 如为本示例未包含的模组型号, 须自行编写添加 LCD/TP 驱动 */
    #define LCD_TYPE            JLT4305A

#elif       (__TARGET_CONST__ == 2)
    /** [480*272/320] 屏幕模组型号可选 JLT35002A_V2 / JLT4303A */
    #define LCD_TYPE            JLT4303A

#elif       (__TARGET_CONST__ == 3)
    /** [480*480] 屏幕模组型号可选 TL040WVS03 / TL021WVC02 */
    #define LCD_TYPE            TL040WVS03

#elif       (__TARGET_CONST__ == 4)
    /** [800*480] 屏幕模组型号可选 JLT4305A / ATK_MD0700R */
    #define LCD_TYPE            JLT4305A

#elif       (__TARGET_CONST__ == 5)
    /** [1024*600] 屏幕模组型号可选 WKS70170 / RS_7_V1_3 */
    #define LCD_TYPE            WKS70170

/*******************************************************************************************************************************************
 * ARGB888 __TARGET__
 *******************************************************************************************************************************************/
#elif       (__TARGET_CONST__ == 6)
    /** 屏幕模组型号可自定义更换, 如为本示例未包含的模组型号, 须自行编写添加 LCD/TP 驱动 */
    #define LCD_TYPE            JLT4305A

#elif       (__TARGET_CONST__ == 7)
    /** 屏幕模组型号可自定义更换, 如为本示例未包含的模组型号, 须自行编写添加 LCD/TP 驱动 */
    #define LCD_TYPE            JLT4305A

#elif       (__TARGET_CONST__ == 8)
    /** [480*272] 屏幕模组型号可选 JLT4303A */
    #define LCD_TYPE            JLT4303A

#elif       (__TARGET_CONST__ == 9)
    /** [480*480] 屏幕模组型号可选 TL040WVS03 / TL021WVC02 */
    #define LCD_TYPE            TL040WVS03

#elif       (__TARGET_CONST__ == 10)
    /** [800*480] 屏幕模组型号可选 JLT4305A / ATK_MD0700R */
    #define LCD_TYPE            JLT4305A

#elif       (__TARGET_CONST__ == 11)
    /** [1024*600] 屏幕模组型号可选 WKS70170 / RS_7_V1_3 */
    #define LCD_TYPE            WKS70170

#elif       (__TARGET_CONST__ == 0xFF)
    /** Userboot 未使用屏幕模组型号, 此处无实际作用, 仅为了应对编译时可能出现的错误 */
    #define LCD_TYPE            JLT4303A

#else
    #error "Please define the __TARGET_CONST__ "
#endif

/* 屏幕模组型号相对应的 分辨率规格 与 TP 型号
 * 如用户自行添加了新的屏幕模组型号, 需要在此处新增对应的 分辨率规格 与 TP 型号
 * 若未添加新型号, 对本示例已适配的屏幕模组型号会自动绑定 分辨率规格 与 TP 型号.
 */
#if (LCD_TYPE == JLT35002A_V2)
    /* JLT35002A_V2 屏内 COG 驱动芯片支持横竖屏转换, 本示例已做支持, 在此处对调分辨率即可(eg : 320 * 480) */
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
 * enum : LCD 显示格式(LCD_FORMAT)
 * 其值为一个像素点所占用的字节数, 可使用该值结合分辨率计算一帧显示缓存的大小
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
    #define LCD_FMT                 LCD_RGB565 /* 仅为了绕过编译错误所需, 无实际作用 */
#else
    #error "Please define the LCD_FMT : LCD_RGBxxx"
#endif

/* 48/64 脚无法配置成 ARGB888, 引脚不足. */
#if (LCD_FMT == LCD_ARGB888 && SWM34S_LCM_PCBV < SWM34SVE_PIN100_A001)
    #error "The Target cannot select this option, No more Pins(IO)!"
#endif

#define SIZE_32MB               (0x02000000)
#define SIZE_16MB               (0x01000000)
#define SIZE_8MB                (0x00800000)
#define SIZE_2MB                (0x00200000)

/** SDRAMM_SIZE : 内置的 SDRAM 大小,提供客制化选项 */
#if (SWM34S_LCM_PCBV == SWM34SCE_PIN48_A2)
	#define SDRAMM_SIZE             SIZE_2MB /**< SDRAM 大小 = 2 MB */
    #if (LCD_HDOT > 480 && LCD_VDOT >= 480)
        /* 48 脚不建议驱动屏幕分辨率超过 480*480, 受限于 SDRAM 大小及管脚数量, 无法适应复杂的应用需求. */
        #error "The Target cannot select this option, No more SDRAMM_SIZE!"
    #endif
#else
    #define SDRAMM_SIZE             SIZE_8MB /**< SDRAM 大小 = 8 MB */
#endif

#endif //__VERSION_H__
