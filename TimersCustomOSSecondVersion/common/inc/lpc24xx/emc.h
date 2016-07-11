#ifndef __EMC_H
#define __EMC_H

#define EMC_BASE_ADDR           (0xFFE08000)
#define EMCCONTROL              (*(volatile uint32_t *)(EMC_BASE_ADDR + 0x000)) /* RW */
#define EMCSTATUS               (*(volatile uint32_t *)(EMC_BASE_ADDR + 0x004)) /* RO */
#define EMCCONFIG               (*(volatile uint32_t *)(EMC_BASE_ADDR + 0x008)) /* RW */
#define EMCDYNAMICCONTROL       (*(volatile uint32_t *)(EMC_BASE_ADDR + 0x020)) /* RW */
#define EMCDYNAMICREFRESH       (*(volatile uint32_t *)(EMC_BASE_ADDR + 0x024)) /* RW */
#define EMCDYNAMICREADCONFIG    (*(volatile uint32_t *)(EMC_BASE_ADDR + 0x028)) /* RW */
#define EMCDYNAMICRP            (*(volatile uint32_t *)(EMC_BASE_ADDR + 0x030)) /* RW */
#define EMCDYNAMICRAS           (*(volatile uint32_t *)(EMC_BASE_ADDR + 0x034)) /* RW */
#define EMCDYNAMICSREX          (*(volatile uint32_t *)(EMC_BASE_ADDR + 0x038)) /* RW */
#define EMCDYNAMICAPR           (*(volatile uint32_t *)(EMC_BASE_ADDR + 0x03C)) /* RW */
#define EMCDYNAMICDAL           (*(volatile uint32_t *)(EMC_BASE_ADDR + 0x040)) /* RW */
#define EMCDYNAMICWR            (*(volatile uint32_t *)(EMC_BASE_ADDR + 0x044)) /* RW */
#define EMCDYNAMICRC            (*(volatile uint32_t *)(EMC_BASE_ADDR + 0x048)) /* RW */
#define EMCDYNAMICRFC           (*(volatile uint32_t *)(EMC_BASE_ADDR + 0x04C)) /* RW */
#define EMCDYNAMICXSR           (*(volatile uint32_t *)(EMC_BASE_ADDR + 0x050)) /* RW */
#define EMCDYNAMICRRD           (*(volatile uint32_t *)(EMC_BASE_ADDR + 0x054)) /* RW */
#define EMCDYNAMICMRD           (*(volatile uint32_t *)(EMC_BASE_ADDR + 0x058)) /* RW */
#define EMCSTATICEXTENDEDWAIT   (*(volatile uint32_t *)(EMC_BASE_ADDR + 0x080)) /* RW */
#define EMCDYNAMICCONFIG0       (*(volatile uint32_t *)(EMC_BASE_ADDR + 0x100)) /* RW */
#define EMCDYNAMICRASCAS0       (*(volatile uint32_t *)(EMC_BASE_ADDR + 0x104)) /* RW */
#define EMCDYNAMICCONFIG1       (*(volatile uint32_t *)(EMC_BASE_ADDR + 0x120)) /* RW */
#define EMCDYNAMICRASCAS1       (*(volatile uint32_t *)(EMC_BASE_ADDR + 0x124)) /* RW */
#define EMCDYNAMICCONFIG2       (*(volatile uint32_t *)(EMC_BASE_ADDR + 0x140)) /* RW */
#define EMCDYNAMICRASCAS2       (*(volatile uint32_t *)(EMC_BASE_ADDR + 0x144)) /* RW */
#define EMCDYNAMICCONFIG3       (*(volatile uint32_t *)(EMC_BASE_ADDR + 0x160)) /* RW */
#define EMCDYNAMICRASCAS3       (*(volatile uint32_t *)(EMC_BASE_ADDR + 0x164)) /* RW */
#define EMCSTATICCONFIG0        (*(volatile uint32_t *)(EMC_BASE_ADDR + 0x200)) /* RW */
#define EMCSTATICWAITWEN0       (*(volatile uint32_t *)(EMC_BASE_ADDR + 0x204)) /* RW */
#define EMCSTATICWAITOEN0       (*(volatile uint32_t *)(EMC_BASE_ADDR + 0x208)) /* RW */
#define EMCSTATICWAITRD0        (*(volatile uint32_t *)(EMC_BASE_ADDR + 0x20C)) /* RW */
#define EMCSTATICWAITPAGE0      (*(volatile uint32_t *)(EMC_BASE_ADDR + 0x210)) /* RW */
#define EMCSTATICWAITWR0        (*(volatile uint32_t *)(EMC_BASE_ADDR + 0x214)) /* RW */
#define EMCSTATICWAITTURN0      (*(volatile uint32_t *)(EMC_BASE_ADDR + 0x218)) /* RW */
#define EMCSTATICCONFIG1        (*(volatile uint32_t *)(EMC_BASE_ADDR + 0x220)) /* RW */
#define EMCSTATICWAITWEN1       (*(volatile uint32_t *)(EMC_BASE_ADDR + 0x224)) /* RW */
#define EMCSTATICWAITOEN1       (*(volatile uint32_t *)(EMC_BASE_ADDR + 0x228)) /* RW */
#define EMCSTATICWAITRD1        (*(volatile uint32_t *)(EMC_BASE_ADDR + 0x22C)) /* RW */
#define EMCSTATICWAITPAGE1      (*(volatile uint32_t *)(EMC_BASE_ADDR + 0x230)) /* RW */
#define EMCSTATICWAITWR1        (*(volatile uint32_t *)(EMC_BASE_ADDR + 0x234)) /* RW */
#define EMCSTATICWAITTURN1      (*(volatile uint32_t *)(EMC_BASE_ADDR + 0x238)) /* RW */
#define EMCSTATICCONFIG2        (*(volatile uint32_t *)(EMC_BASE_ADDR + 0x240)) /* RW */
#define EMCSTATICWAITWEN2       (*(volatile uint32_t *)(EMC_BASE_ADDR + 0x244)) /* RW */
#define EMCSTATICWAITOEN2       (*(volatile uint32_t *)(EMC_BASE_ADDR + 0x248)) /* RW */
#define EMCSTATICWAITRD2        (*(volatile uint32_t *)(EMC_BASE_ADDR + 0x24C)) /* RW */
#define EMCSTATICWAITPAGE2      (*(volatile uint32_t *)(EMC_BASE_ADDR + 0x250)) /* RW */
#define EMCSTATICWAITWR2        (*(volatile uint32_t *)(EMC_BASE_ADDR + 0x254)) /* RW */
#define EMCSTATICWAITTURN2      (*(volatile uint32_t *)(EMC_BASE_ADDR + 0x258)) /* RW */
#define EMCSTATICCONFIG3        (*(volatile uint32_t *)(EMC_BASE_ADDR + 0x260)) /* RW */
#define EMCSTATICWAITWEN3       (*(volatile uint32_t *)(EMC_BASE_ADDR + 0x264)) /* RW */
#define EMCSTATICWAITOEN3       (*(volatile uint32_t *)(EMC_BASE_ADDR + 0x268)) /* RW */
#define EMCSTATICWAITRD3        (*(volatile uint32_t *)(EMC_BASE_ADDR + 0x26C)) /* RW */
#define EMCSTATICWAITPAGE3      (*(volatile uint32_t *)(EMC_BASE_ADDR + 0x270)) /* RW */
#define EMCSTATICWAITWR3        (*(volatile uint32_t *)(EMC_BASE_ADDR + 0x274)) /* RW */
#define EMCSTATICWAITTURN3      (*(volatile uint32_t *)(EMC_BASE_ADDR + 0x278)) /* RW */

typedef volatile struct ATTR_PACKED_ALIGNED4 _LPC24XX_EMC {
    uint32_t CONTROL;              /* RW Offset 0x000*/
    uint32_t STATUS;               /* RO Offset 0x004*/
    uint32_t CONFIG;               /* RW Offset 0x008*/
    uint32_t __pad_0C;
    uint32_t __pad_10;
    uint32_t __pad_14;
    uint32_t __pad_18;
    uint32_t __pad_1C;
    uint32_t DYNAMICCONTROL;       /* RW Offset 0x020*/
    uint32_t DYNAMICREFRESH;       /* RW Offset 0x024*/
    uint32_t DYNAMICREADCONFIG;    /* RW Offset 0x028*/
    uint32_t __pad_2C;
    uint32_t DYNAMICRP;            /* RW Offset 0x030*/
    uint32_t DYNAMICRAS;           /* RW Offset 0x034*/
    uint32_t DYNAMICSREX;          /* RW Offset 0x038*/
    uint32_t DYNAMICAPR;           /* RW Offset 0x03C*/
    uint32_t DYNAMICDAL;           /* RW Offset 0x040*/
    uint32_t DYNAMICWR;            /* RW Offset 0x044*/
    uint32_t DYNAMICRC;            /* RW Offset 0x048*/
    uint32_t DYNAMICRFC;           /* RW Offset 0x04C*/
    uint32_t DYNAMICXSR;           /* RW Offset 0x050*/
    uint32_t DYNAMICRRD;           /* RW Offset 0x054*/
    uint32_t DYNAMICMRD;           /* RW Offset 0x058*/
    uint32_t __pad_5c;
    uint32_t __pad_60;
    uint32_t __pad_64;
    uint32_t __pad_68;
    uint32_t __pad_6C;
    uint32_t __pad_70;
    uint32_t __pad_74;
    uint32_t __pad_78;
    uint32_t __pad_7C;
    uint32_t STATICEXTENDEDWAIT;   /* RW Offset 0x080*/
    uint32_t __pad_84;
    uint32_t __pad_88;
    uint32_t __pad_8C;
    uint32_t __pad_90;
    uint32_t __pad_94;
    uint32_t __pad_98;
    uint32_t __pad_9C;
    uint32_t __pad_A0;
    uint32_t __pad_A4;
    uint32_t __pad_A8;
    uint32_t __pad_AC;
    uint32_t __pad_B0;
    uint32_t __pad_B4;
    uint32_t __pad_B8;
    uint32_t __pad_BC;
    uint32_t __pad_C0;
    uint32_t __pad_C4;
    uint32_t __pad_C8;
    uint32_t __pad_CC;
    uint32_t __pad_D0;
    uint32_t __pad_D4;
    uint32_t __pad_D8;
    uint32_t __pad_DC;
    uint32_t __pad_E0;
    uint32_t __pad_E4;
    uint32_t __pad_E8;
    uint32_t __pad_EC;
    uint32_t __pad_F0;
    uint32_t __pad_F4;
    uint32_t __pad_F8;
    uint32_t __pad_FC;
    uint32_t DYNAMICCONFIG0;       /* RW Offset 0x100*/
    uint32_t DYNAMICRASCAS0;       /* RW Offset 0x104*/
    uint32_t __pad_108;
    uint32_t __pad_10C;
    uint32_t __pad_110;
    uint32_t __pad_114;
    uint32_t __pad_118;
    uint32_t __pad_11C;
    uint32_t DYNAMICCONFIG1;       /* RW Offset 0x120*/
    uint32_t DYNAMICRASCAS1;       /* RW Offset 0x124*/
    uint32_t __pad_128;
    uint32_t __pad_12C;
    uint32_t __pad_130;
    uint32_t __pad_134;
    uint32_t __pad_138;
    uint32_t __pad_13C;
    uint32_t DYNAMICCONFIG2;       /* RW Offset 0x140*/
    uint32_t DYNAMICRASCAS2;       /* RW Offset 0x144*/
    uint32_t __pad_148;
    uint32_t __pad_14C;
    uint32_t __pad_150;
    uint32_t __pad_154;
    uint32_t __pad_158;
    uint32_t __pad_15C;
    uint32_t DYNAMICCONFIG3;       /* RW Offset 0x160*/
    uint32_t DYNAMICRASCAS3;       /* RW Offset 0x164*/
    uint32_t __pad_168;
    uint32_t __pad_16C;
    uint32_t __pad_170;
    uint32_t __pad_174;
    uint32_t __pad_178;
    uint32_t __pad_17C;
    uint32_t __pad_180;
    uint32_t __pad_184;
    uint32_t __pad_188;
    uint32_t __pad_18C;
    uint32_t __pad_190;
    uint32_t __pad_194;
    uint32_t __pad_198;
    uint32_t __pad_19C;
    uint32_t __pad_1A0;
    uint32_t __pad_1A4;
    uint32_t __pad_1A8;
    uint32_t __pad_1AC;
    uint32_t __pad_1B0;
    uint32_t __pad_1B4;
    uint32_t __pad_1B8;
    uint32_t __pad_1BC;
    uint32_t __pad_1C0;
    uint32_t __pad_1C4;
    uint32_t __pad_1C8;
    uint32_t __pad_1CC;
    uint32_t __pad_1D0;
    uint32_t __pad_1D4;
    uint32_t __pad_1D8;
    uint32_t __pad_1DC;
    uint32_t __pad_1E0;
    uint32_t __pad_1E4;
    uint32_t __pad_1E8;
    uint32_t __pad_1EC;
    uint32_t __pad_1F0;
    uint32_t __pad_1F4;
    uint32_t __pad_1F8;
    uint32_t __pad_1FC;
    uint32_t STATICCONFIG0;        /* RW Offset 0x200*/
    uint32_t STATICWAITWEN0;       /* RW Offset 0x204*/
    uint32_t STATICWAITOEN0;       /* RW Offset 0x208*/
    uint32_t STATICWAITRD0;        /* RW Offset 0x20C*/
    uint32_t STATICWAITPAGE0;      /* RW Offset 0x210*/
    uint32_t STATICWAITWR0;        /* RW Offset 0x214*/
    uint32_t STATICWAITTURN0;      /* RW Offset 0x218*/
    uint32_t __pad_21C;
    uint32_t STATICCONFIG1;        /* RW Offset 0x220*/
    uint32_t STATICWAITWEN1;       /* RW Offset 0x224*/
    uint32_t STATICWAITOEN1;       /* RW Offset 0x228*/
    uint32_t STATICWAITRD1;        /* RW Offset 0x22C*/
    uint32_t STATICWAITPAGE1;      /* RW Offset 0x230*/
    uint32_t STATICWAITWR1;        /* RW Offset 0x234*/
    uint32_t STATICWAITTURN1;      /* RW Offset 0x238*/
    uint32_t __pad_23C;
    uint32_t STATICCONFIG2;        /* RW Offset 0x240*/
    uint32_t STATICWAITWEN2;       /* RW Offset 0x244*/
    uint32_t STATICWAITOEN2;       /* RW Offset 0x248*/
    uint32_t STATICWAITRD2;        /* RW Offset 0x24C*/
    uint32_t STATICWAITPAGE2;      /* RW Offset 0x250*/
    uint32_t STATICWAITWR2;        /* RW Offset 0x254*/
    uint32_t STATICWAITTURN2;      /* RW Offset 0x258*/
    uint32_t __pad_25C;
    uint32_t STATICCONFIG3;        /* RW Offset 0x260*/
    uint32_t STATICWAITWEN3;       /* RW Offset 0x264*/
    uint32_t STATICWAITOEN3;       /* RW Offset 0x268*/
    uint32_t STATICWAITRD3;        /* RW Offset 0x26C*/
    uint32_t STATICWAITPAGE3;      /* RW Offset 0x270*/
    uint32_t STATICWAITWR3;        /* RW Offset 0x274*/
    uint32_t STATICWAITTURN3;      /* RW Offset 0x278*/
}  LPC24XX_EMC_t, *P_LPC24XX_EMC_t;

#define P_EMC_REGS ((LPC24XX_EMC_t *)EMC_BASE_ADDR)


#define EMCCONTROL_ENABLE       (1<<0)
#define EMCCONTROL_ADDR_MIRROR  (1<<1)
#define EMCCONTROL_LOW_PWR_MODE (1<<2)

#define EMCSTATUS_BUSY          (1<<0)
#define EMCSTATUS_S_DATA        (1<<1)
#define EMCSTATUS_SA            (1<<2)

#define EMCDYNAMICREADCONFIG_RD_CLKOUT      0
#define EMCDYNAMICREADCONFIG_RD_CMDDELAY    1
#define EMCDYNAMICREADCONFIG_RD_CMDDELAY1   2
#define EMCDYNAMICREADCONFIG_RD_CMDDELAY3   3

#define EMCDYNAMICRASCAS_RAS1   (1<<0)
#define EMCDYNAMICRASCAS_RAS2   (2<<0)
#define EMCDYNAMICRASCAS_RAS3   (3<<0)
#define EMCDYNAMICRASCAS_CAS1   (1<<8)
#define EMCDYNAMICRASCAS_CAS2   (2<<8)
#define EMCDYNAMICRASCAS_CAS3   (3<<8)

#define EMCDYNAMICCONTROL_CE        (1<<0)
#define EMCDYNAMICCONTROL_CS        (1<<1)
#define EMCDYNAMICCONTROL_SR        (1<<2)
#define EMCDYNAMICCONTROL_MMC       (1<<5)
#define EMCDYNAMICCONTROL_I_NORMAL  (0<<7)
#define EMCDYNAMICCONTROL_I_MODE    (1<<7)
#define EMCDYNAMICCONTROL_I_PALL    (2<<7)
#define EMCDYNAMICCONTROL_I_NOP     (3<<7)
#define EMCDYNAMICCONTROL_I_MASK    (3<<7)
#define EMCDYNAMICCONTROL_DP        (1<<13)

#define EMCDYNAMICCONFIG_MD_SDRAM       (0<<3)
#define EMCDYNAMICCONFIG_MD_LPSDRAM     (1<<3)
#define EMCDYNAMICCONFIG_MD_SYNCFLASH   (2<<3)
#define EMCDYNAMICCONFIG_AM_32BIT_HP_256MB_4BANKS_R13_C9  ((1<<14) | (0<<12) | (3<<9) | (1<<7))
#define EMCDYNAMICCONFIG_AM_32BIT_LP_256MB_4BANKS_R13_C9  ((1<<14) | (1<<12) | (3<<9) | (1<<7))
#define EMCDYNAMICCONFIG_BUFFER_ENABLE  (1<<19)
#define EMCDYNAMICCONFIG_WRITE_PROTECT  (1<<20)


#endif /* __EMC_H */
