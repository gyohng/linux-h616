/*
 * include/linux/dma/sunxi-dma.h
 *
 * Copyright (C) 2015-2020 Allwinnertech Co., Ltd
 *
 * Author: Wim Hwang <huangwei@allwinnertech.com>
 *
 * Sunxi DMA controller driver
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

/*
 * The source DRQ type and port corresponding relation
 *
 */
#ifndef __SUNXI_DMA_H__
#define __SUNXI_DMA_H__

#include <linux/dmaengine.h>

#ifdef CONFIG_PINCTRL_SUN50I_H616
#define CONFIG_ARCH_SUN50IW9 1
#define CONFIG_EVB_PLATFORM 1
#endif

#if defined(CONFIG_ARCH_SUN8IW10)
#include "sunxi/dma-sun8iw10.h"
#elif defined(CONFIG_ARCH_SUN8IW11)
#include "sunxi/dma-sun8iw11.h"
#elif defined(CONFIG_ARCH_SUN8IW17)
#include "sunxi/dma-sun8iw17.h"
#elif defined(CONFIG_ARCH_SUN50IW2P1)
#include "sunxi/dma-sun50iw2.h"
#elif defined(CONFIG_ARCH_SUN50IW3P1)
#include "sunxi/dma-sun50iw3.h"
#elif defined(CONFIG_ARCH_SUN50IW6P1)
#include "sunxi/dma-sun50iw6.h"
#elif defined(CONFIG_ARCH_SUN3IW1P1)
#include "sunxi/dma-sun3iw1.h"
#elif defined(CONFIG_ARCH_SUN8IW7)
#include "sunxi/dma-sun8iw7.h"
#elif defined(CONFIG_ARCH_SUN8IW12)
#include "sunxi/dma-sun8iw12.h"
#elif defined(CONFIG_ARCH_SUN8IW15)
#include "sunxi/dma-sun8iw15.h"
#elif defined(CONFIG_ARCH_SUN50IW8)
#include "sunxi/dma-sun50iw8.h"
#elif defined(CONFIG_ARCH_SUN8IW18)
#include "sunxi/dma-sun8iw18.h"
#elif defined(CONFIG_ARCH_SUN50IW5T)
#include "sunxi/dma-sun50iw5t.h"
#elif defined(CONFIG_ARCH_SUN50IW9)
#include "sunxi/dma-sun50iw9.h"
#elif defined(CONFIG_ARCH_SUN50IW10)
#include "sunxi/dma-sun50iw10.h"
#else

#define DRQSRC_SRAM		0
#define DRQSRC_SDRAM		0

#if !defined(CONFIG_ARCH_SUN8IW5) \
	&& !defined(CONFIG_ARCH_SUN8IW3) \
	&& !defined(CONFIG_ARCH_SUN8IW8) \
	&& !defined(CONFIG_ARCH_SUN8IW9)
#define DRQSRC_SPDIFRX		2
#endif

#if !defined(CONFIG_ARCH_SUN8IW9)
#define DRQSRC_DAUDIO_0_RX	3
#endif

#if !defined(CONFIG_ARCH_SUN9I) \
	&& !defined(CONFIG_ARCH_SUN8IW8)
#define DRQSRC_DAUDIO_1_RX	4
#define DRQSRC_NAND0		5
#endif

#define DRQSRC_UART0_RX		6
#define DRQSRC_UART1_RX 	7
#define DRQSRC_UART2_RX		8

#ifndef CONFIG_ARCH_SUN8IW8
#define DRQSRC_UART3_RX		9
#define DRQSRC_UART4_RX		10
#endif
/* #define DRQSRC_RESEVER		11 */
/* #define DRQSRC_RESEVER		12 */

#ifndef CONFIG_ARCH_SUN9I

#ifdef CONFIG_ARCH_SUN8IW1
#define DRQSRC_HDMI_DDC		13
#define DRQSRC_HDMI_AUDIO	14
#endif

#if !defined(CONFIG_ARCH_SUN8IW6)
#define DRQSRC_AUDIO_CODEC	15
#if defined(CONFIG_ARCH_SUN50I)
#define DRQSRC_CODEC		DRQSRC_AUDIO_CODEC
#endif
#endif

#if !defined(CONFIG_ARCH_SUN8IW3) \
	&& !defined(CONFIG_ARCH_SUN8IW6)
#define DRQSRC_SS		16
#if defined(CONFIG_ARCH_SUN50I)
#define DRQSRC_CE_RX		DRQSRC_SS
#endif
#endif

#define DRQSRC_OTG_EP1		17
#define DRQSRC_OTG_EP2		18
#define DRQSRC_OTG_EP3		19
#define DRQSRC_OTG_EP4		20

#if !defined(CONFIG_ARCH_SUN8IW8)
#define DRQSRC_OTG_EP5		21
#endif

#else
#define DRQSRC_AC97		18
#endif

#if defined(CONFIG_ARCH_SUN8IW1) \
	|| defined(CONFIG_ARCH_SUN9I)
#define DRQSRC_UART5_RX		22
#endif

#define DRQSRC_SPI0_RX		23

#if !defined(CONFIG_ARCH_SUN8IW8)
#define DRQSRC_SPI1_RX		24
#endif

#if defined(CONFIG_ARCH_SUN8IW1) \
	|| defined(CONFIG_ARCH_SUN9I)
#define DRQSRC_SPI2_RX		25
#define DRQSRC_SPI3_RX		26
#endif

#if defined(CONFIG_ARCH_SUN8IW1)
#define DRQSRC_TP		27
#define DRQSRC_NAND1		28
#define DRQSRC_MTC_ACC		29
#define DRQSRC_DIGITAL_MIC	30

#elif defined(CONFIG_ARCH_SUN8IW6) \
	|| defined(CONFIG_ARCH_SUN8IW7)

#define DRQDST_TDMRX		28
#endif


/*
 * The source and destination DRQ type and port corresponding relation
 */
#define DRQDST_SRAM		0
#define DRQDST_SDRAM		0

#if !defined(CONFIG_ARCH_SUN8IW5) \
	&& !defined(CONFIG_ARCH_SUN8IW5) \
	&& !defined(CONFIG_ARCH_SUN8IW8)
#define DRQDST_SPDIFTX		2
#endif

#if !defined(CONFIG_ARCH_SUN8IW9)
#define DRQDST_DAUDIO_0_TX	3
#endif

#if !defined(CONFIG_ARCH_SUN8IW8) \
	&& !defined(CONFIG_ARCH_SUN8IW9)
#define DRQDST_DAUDIO_1_TX	4
#endif

#if !defined(CONFIG_ARCH_SUN9I) \
	&& !defined(CONFIG_ARCH_SUN8IW8)
#define DRQDST_NAND0		5
#endif

#define DRQDST_UART0_TX		6
#define DRQDST_UART1_TX 	7
#define DRQDST_UART2_TX		8

#if !defined(CONFIG_ARCH_SUN8IW8)
#define DRQDST_UART3_TX		9
#define DRQDST_UART4_TX		10
#endif

#if defined(CONFIG_ARCH_SUN8IW3) \
	|| defined(CONFIG_ARCH_SUN8IW5) \
	|| defined(CONFIG_ARCH_SUN8IW8) \
	|| defined(CONFIG_ARCH_SUN8IW9)
#define DRQSRC_TCON0		12
#endif

#ifndef CONFIG_ARCH_SUN9I

#if defined(CONFIG_ARCH_SUN8IW1)
#define DRQDST_HDMI_DDC		13
#define DRQDST_HDMI_AUDIO	14
#endif

#if !defined(CONFIG_ARCH_SUN8IW6)
#define DRQDST_AUDIO_CODEC	15
#if defined(CONFIG_ARCH_SUN50I)
#define DRQDST_CODEC		DRQDST_AUDIO_CODEC
#endif
#endif

#if !defined(CONFIG_ARCH_SUN8IW3) \
	&& !defined(CONFIG_ARCH_SUN8IW6)
#define DRQDST_SS		16
#if defined(CONFIG_ARCH_SUN50I)
#define DRQDST_CE_TX		DRQDST_SS
#endif
#endif

#define DRQDST_OTG_EP1		17
#define DRQDST_OTG_EP2		18
#define DRQDST_OTG_EP3		19
#define DRQDST_OTG_EP4		20
#if !defined(CONFIG_ARCH_SUN8IW8)
#define DRQDST_OTG_EP5		21
#endif

#else
#define DRQDST_CIR_TX		15
#define DRQDST_AC97		18
#endif

#if defined(CONFIG_ARCH_SUN8IW1) \
	|| defined(CONFIG_ARCH_SUN9I)
#define DRQDST_UART5_TX		22
#endif

#define DRQDST_SPI0_TX		23
#define DRQDST_SPI1_TX		24

#if defined(CONFIG_ARCH_SUN8IW1) \
	&& defined(CONFIG_ARCH_SUN9I)
#define DRQDST_SPI2TX		25
#define DRQDST_SPI3TX		26
#endif

#if defined(CONFIG_ARCH_SUN8IW1)
#define DRQDST_NAND1		28
#define DRQDST_MTC_ACC		29
#define DRQDST_DIGITAL_MIC	30

#elif defined(CONFIG_ARCH_SUN8IW6) \
	|| defined(CONFIG_ARCH_SUN8IW7)

#define DRQDST_DAUDIO_2_TX	27
#define DRQDST_TDM_TX		28
#define	DRQDST_CIR_TX		29
#elif defined(CONFIG_ARCH_SUN50I)
#define DRQDST_DAUDIO_2_TX	27
#endif

#endif /* CONFIG_ARCH_SUN8IW10 */

#define sunxi_slave_id(d, s) (((d)<<16) | (s))
#define GET_SRC_DRQ(x)	((x) & 0x000000ff)
#define GET_DST_DRQ(x)	((x) & 0x00ff0000)

/*
 * The following DRQ type just for CPUs.
 */
#ifdef CONFIG_ARCH_SUN9I
#define DRQSRC_R_DAUDIO_0_RX	1
#define DRQSRC_R_UART_RX	2
#define DRQSRC_R_CIR_RX		3
#define DRQSRC_R_DAUDIO_1_RX	4
#define DRQSRC_SPI3_RX		5

#define DRQDST_R_DAUDIO_0_TX	1
#define DRQDST_R_UART_TX	2
#define DRQDST_R_CIR_TX		3
#define DRQDST_R_DAUDIO_1_TX	4
#define DRQDST_SPI3_TX		5
#endif

#define SUNXI_DMA_DRV	"sunxi_dmac"
#define SUNXI_RDMA_DRV	"sunxi_rdmac"

#define SUNXI_FILTER(name)	name##_filter_fn

bool sunxi_rdma_filter_fn(struct dma_chan *chan, void *param);
bool sunxi_dma_filter_fn(struct dma_chan *chan, void *param);

struct sunxi_dma_info {
	char name[16];
	u32 port;
	struct device *use_dev;
};

#endif /* __SUNXI_DMA_H__ */
