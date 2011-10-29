/*******************************************************************************
* Copyright 2009, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

/* This header exports the configuration method(s) defined by this file. */
#include <cyfitter_cfg.h>

/* This header includes all of the necessary type definitions. */
#include <cytypes.h>

/* Standard system includes */
#if !defined(__ARMCC_VERSION)
#include <string.h>
#endif

/* This header contains all of the macros necessary for accessing registers on the device */
#include <cydevice.h>

/* This header contains all of the macros defined based on the users choices in the System DWR as well as instance
   based macros for register access. */
#include <cyfitter.h>

/* This header contains functions needed to enable the digital array */
#include <CyLib.h>

/* The section below contains all of the data used to initialize the device. */
#include <CyDmac.h>

#if defined(__C51__) || defined(__CX51__)
#define CYCODE code
#define CYDATA data
#define CYXDATA xdata
#define CYFAR far
extern void cymemzero(void CYFAR *addr, uint16 size);
extern void cyconfigcpy(uint16 size, const void CYFAR *src, void CYFAR *dest) small;
extern void cyconfigcpycode(uint16 size, const void CYCODE *src, void CYFAR *dest);
#define CYMEMZERO(a,c) cymemzero((a),(c))
#define CYCONFIGCPY(d,s,c) cyconfigcpy((c),(s),(d))
#define CYCONFIGCPYCODE(d,s,c) cyconfigcpycode((c),(s),(d))
#else
#define CYCODE
#define CYDATA
#define CYXDATA
#define CYFAR
#define CYMEMZERO(a,c) cymemset((a),0,(c))
#define CYCONFIGCPY(d,s,c) cymemcpy((d),(s),(c))
#define CYCONFIGCPYCODE(d,s,c) cymemcpy((d),(s),(c))
#endif

/* Disable warnings about pointer truncation and pointer to integer conversion */
#if defined(__ARMCC_VERSION)

#pragma diag_suppress 767,69
#elif defined(__GNUC__)
#pragma GCC diagnostic ignored "-Wpointer-to-int-cast"
#endif

#if defined(__GNUC__) || defined(__ARMCC_VERSION)
#define CYPACKED __attribute__ ((packed))
#define DMAINITSEC __attribute__ ((section (".dma_init")))
#if defined(__ARMCC_VERSION)
#define CY_CFG_MEMORY_BARRIER() __memory_changed()
#else
#define CY_CFG_MEMORY_BARRIER() __sync_synchronize()
#endif
#else
#define CYPACKED
#define DMAINITSEC
#define CY_CFG_MEMORY_BARRIER()
#endif

#define CYDATADECL(name) const uint8 CYCODE name

typedef struct {
	void CYFAR *address;
	uint16 size;
} CYPACKED cfg_memset_t;

typedef struct {
	void CYFAR *dest;
	const void CYCODE *src;
	uint16 size;
} CYPACKED cfg_memcpy_t;

#define CFG_MEMSET_COUNT (sizeof(cfg_memset_list)/sizeof(*cfg_memset_list))
static const cfg_memset_t CYCODE cfg_memset_list [] = {
	/* address, size */
	{(void CYFAR *)(CYDEV_TMR0_CFG0), 11},
	{(void CYFAR *)(CYDEV_IO_PRT_PRT1_DR), 16},
	{(void CYFAR *)(CYDEV_IO_PRT_PRT3_DR), 16},
	{(void CYFAR *)(CYDEV_IO_PRT_PRT5_DR), 32},
	{(void CYFAR *)(CYDEV_IO_PRT_PRT12_DR), 16},
	{(void CYFAR *)(CYDEV_IO_PRT_PRT15_DR), 16},
	{(void CYFAR *)(CYDEV_UCFG_B0_P0_U0_BASE), 4096},
	{(void CYFAR *)(CYDEV_UCFG_B1_P2_U0_BASE), 2048},
	{(void CYFAR *)(CYDEV_UCFG_DSI0_BASE), 2560},
	{(void CYFAR *)(CYDEV_UCFG_DSI12_BASE), 512},
};

#define CY_CFG_BASE_ADDR_COUNT 25
typedef struct
{
	uint8 offset;
	uint8 value;
} CYPACKED cy_cfg_addrvalue_t;

static const uint32 CYCODE cy_cfg_addr_table[] = {
	0x40004F02u, /* Base address: 0x40004F00 Count: 2 */
	0x40005B01u, /* Base address: 0x40005B00 Count: 1 */
	0x40006401u, /* Base address: 0x40006400 Count: 1 */
	0x40010501u, /* Base address: 0x40010500 Count: 1 */
	0x40010701u, /* Base address: 0x40010700 Count: 1 */
	0x40010811u, /* Base address: 0x40010800 Count: 17 */
	0x40010910u, /* Base address: 0x40010900 Count: 16 */
	0x40010A3Bu, /* Base address: 0x40010A00 Count: 59 */
	0x40010B37u, /* Base address: 0x40010B00 Count: 55 */
	0x40010C0Eu, /* Base address: 0x40010C00 Count: 14 */
	0x40010D0Au, /* Base address: 0x40010D00 Count: 10 */
	0x40011906u, /* Base address: 0x40011900 Count: 6 */
	0x40011A0Bu, /* Base address: 0x40011A00 Count: 11 */
	0x40011B12u, /* Base address: 0x40011B00 Count: 18 */
	0x40014102u, /* Base address: 0x40014100 Count: 2 */
	0x40014205u, /* Base address: 0x40014200 Count: 5 */
	0x40014301u, /* Base address: 0x40014300 Count: 1 */
	0x40014402u, /* Base address: 0x40014400 Count: 2 */
	0x40014509u, /* Base address: 0x40014500 Count: 9 */
	0x40014609u, /* Base address: 0x40014600 Count: 9 */
	0x40014705u, /* Base address: 0x40014700 Count: 5 */
	0x40014C06u, /* Base address: 0x40014C00 Count: 6 */
	0x40014D0Eu, /* Base address: 0x40014D00 Count: 14 */
	0x40015006u, /* Base address: 0x40015000 Count: 6 */
	0x40015101u, /* Base address: 0x40015100 Count: 1 */
};

static const cy_cfg_addrvalue_t CYCODE cy_cfg_data_table[] = {
	{0x01u, 0x20u},
	{0x09u, 0x1Bu},
	{0x27u, 0x84u},
	{0x8Au, 0x0Fu},
	{0xE2u, 0x02u},
	{0xECu, 0x80u},
	{0xC0u, 0x03u},
	{0xC7u, 0x15u},
	{0xC8u, 0x30u},
	{0xC9u, 0xFFu},
	{0xCAu, 0x07u},
	{0xCBu, 0xFFu},
	{0xCCu, 0x40u},
	{0xCDu, 0x20u},
	{0xCEu, 0xF0u},
	{0xCFu, 0x05u},
	{0xD0u, 0x08u},
	{0xDAu, 0x04u},
	{0xDDu, 0x01u},
	{0xE0u, 0x40u},
	{0xE1u, 0xA8u},
	{0xE2u, 0x40u},
	{0xE3u, 0x20u},
	{0x41u, 0x08u},
	{0x50u, 0x04u},
	{0x52u, 0x02u},
	{0x53u, 0x04u},
	{0x92u, 0x01u},
	{0x94u, 0x08u},
	{0x97u, 0x08u},
	{0x9Du, 0x08u},
	{0xA0u, 0x24u},
	{0xA1u, 0x08u},
	{0xA3u, 0x20u},
	{0xA7u, 0x04u},
	{0xAFu, 0x40u},
	{0xB7u, 0x08u},
	{0xD0u, 0x02u},
	{0xECu, 0x82u},
	{0x00u, 0x80u},
	{0x01u, 0x94u},
	{0x03u, 0x2Bu},
	{0x04u, 0x09u},
	{0x05u, 0x20u},
	{0x06u, 0x10u},
	{0x07u, 0x08u},
	{0x08u, 0x2Au},
	{0x09u, 0xFCu},
	{0x0Au, 0x44u},
	{0x0Bu, 0x02u},
	{0x0Du, 0x18u},
	{0x10u, 0x62u},
	{0x11u, 0x88u},
	{0x12u, 0x05u},
	{0x13u, 0x54u},
	{0x14u, 0x02u},
	{0x16u, 0x40u},
	{0x1Au, 0x20u},
	{0x1Du, 0x03u},
	{0x24u, 0x52u},
	{0x26u, 0x04u},
	{0x29u, 0x05u},
	{0x2Bu, 0x68u},
	{0x30u, 0x07u},
	{0x31u, 0x1Fu},
	{0x32u, 0x38u},
	{0x33u, 0x80u},
	{0x34u, 0x80u},
	{0x35u, 0x60u},
	{0x36u, 0x40u},
	{0x37u, 0x1Fu},
	{0x38u, 0x08u},
	{0x39u, 0x8Au},
	{0x3Bu, 0x20u},
	{0x3Eu, 0x50u},
	{0x3Fu, 0x04u},
	{0x40u, 0x54u},
	{0x41u, 0x03u},
	{0x45u, 0xE0u},
	{0x46u, 0xCBu},
	{0x47u, 0x0Cu},
	{0x48u, 0x1Eu},
	{0x49u, 0xFFu},
	{0x4Au, 0xFFu},
	{0x4Bu, 0xFFu},
	{0x4Eu, 0xF0u},
	{0x4Fu, 0x44u},
	{0x50u, 0x08u},
	{0x54u, 0x01u},
	{0x58u, 0x04u},
	{0x59u, 0x04u},
	{0x5Au, 0x09u},
	{0x5Bu, 0x04u},
	{0x5Cu, 0x11u},
	{0x5Du, 0x19u},
	{0x62u, 0xC0u},
	{0x64u, 0x40u},
	{0x65u, 0x02u},
	{0x00u, 0x12u},
	{0x01u, 0x08u},
	{0x0Au, 0x80u},
	{0x0Bu, 0x28u},
	{0x13u, 0x08u},
	{0x18u, 0x10u},
	{0x19u, 0x80u},
	{0x1Au, 0x80u},
	{0x1Bu, 0x22u},
	{0x21u, 0x08u},
	{0x22u, 0x80u},
	{0x23u, 0x48u},
	{0x2Bu, 0x04u},
	{0x32u, 0x80u},
	{0x33u, 0x02u},
	{0x38u, 0x98u},
	{0x3Au, 0x01u},
	{0x40u, 0x10u},
	{0x43u, 0x02u},
	{0x48u, 0x02u},
	{0x49u, 0x02u},
	{0x50u, 0x40u},
	{0x52u, 0x08u},
	{0x53u, 0x10u},
	{0x58u, 0x22u},
	{0x59u, 0x82u},
	{0x5Au, 0x08u},
	{0x68u, 0x25u},
	{0x6Au, 0x01u},
	{0x71u, 0xA0u},
	{0x73u, 0xA0u},
	{0x7Bu, 0x04u},
	{0x7Cu, 0x20u},
	{0x7Eu, 0x08u},
	{0x80u, 0x02u},
	{0x82u, 0x01u},
	{0x92u, 0x08u},
	{0x9Cu, 0x02u},
	{0x9Fu, 0xA0u},
	{0xA5u, 0xA0u},
	{0xABu, 0x50u},
	{0xB3u, 0x02u},
	{0xC0u, 0x0Eu},
	{0xC2u, 0x0Eu},
	{0xC4u, 0x04u},
	{0xCAu, 0x04u},
	{0xCCu, 0x09u},
	{0xCEu, 0x0Fu},
	{0xD0u, 0x03u},
	{0xD2u, 0x08u},
	{0xD6u, 0x0Fu},
	{0xDEu, 0x04u},
	{0xE2u, 0x06u},
	{0xE8u, 0x04u},
	{0xECu, 0x01u},
	{0x98u, 0x02u},
	{0x9Cu, 0x01u},
	{0xA8u, 0x04u},
	{0xACu, 0x08u},
	{0xADu, 0x01u},
	{0xB0u, 0x08u},
	{0xB2u, 0x04u},
	{0xB3u, 0x01u},
	{0xB4u, 0x02u},
	{0xB6u, 0x01u},
	{0xBEu, 0x55u},
	{0xBFu, 0x04u},
	{0xD8u, 0x04u},
	{0xD9u, 0x04u},
	{0x09u, 0xA0u},
	{0x13u, 0xA0u},
	{0x1Au, 0x20u},
	{0x1Bu, 0x52u},
	{0x22u, 0x04u},
	{0x28u, 0x02u},
	{0x8Eu, 0x10u},
	{0xC2u, 0x03u},
	{0xC4u, 0x03u},
	{0xCAu, 0x08u},
	{0x92u, 0x01u},
	{0x9Du, 0x08u},
	{0xA0u, 0x24u},
	{0xA2u, 0x02u},
	{0xA7u, 0x04u},
	{0xB7u, 0x20u},
	{0x04u, 0x02u},
	{0x0Cu, 0x01u},
	{0x1Cu, 0x08u},
	{0x24u, 0x04u},
	{0x30u, 0x04u},
	{0x32u, 0x01u},
	{0x34u, 0x08u},
	{0x36u, 0x02u},
	{0x3Eu, 0x51u},
	{0x58u, 0x04u},
	{0x5Cu, 0x01u},
	{0x00u, 0x08u},
	{0x02u, 0x02u},
	{0x0Au, 0x01u},
	{0x10u, 0x20u},
	{0x19u, 0x08u},
	{0x1Bu, 0x66u},
	{0x87u, 0x22u},
	{0x8Fu, 0x40u},
	{0x92u, 0x01u},
	{0x9Du, 0x08u},
	{0xA0u, 0x24u},
	{0xA2u, 0x02u},
	{0xA7u, 0x04u},
	{0xC0u, 0x05u},
	{0xC2u, 0x01u},
	{0xC4u, 0x04u},
	{0xE0u, 0x08u},
	{0xE4u, 0x08u},
	{0x13u, 0x08u},
	{0xC4u, 0x10u},
	{0x30u, 0x08u},
	{0x84u, 0x08u},
	{0x9Bu, 0x08u},
	{0xCCu, 0x40u},
	{0xE2u, 0x40u},
	{0xB3u, 0x08u},
	{0x54u, 0x04u},
	{0xD4u, 0x02u},
	{0x50u, 0x02u},
	{0x52u, 0x08u},
	{0x55u, 0x80u},
	{0x5Cu, 0x40u},
	{0x8Cu, 0x40u},
	{0xA4u, 0x04u},
	{0xD4u, 0x07u},
	{0xD6u, 0x04u},
	{0xE0u, 0x02u},
	{0x2Au, 0x10u},
	{0x80u, 0x04u},
	{0x86u, 0x10u},
	{0xA4u, 0x04u},
	{0xA9u, 0x80u},
	{0xAAu, 0x08u},
	{0xB0u, 0x02u},
	{0xCAu, 0x08u},
	{0xECu, 0x01u},
	{0xA1u, 0x20u},
	{0xACu, 0x04u},
	{0xB1u, 0x20u},
	{0xB4u, 0x04u},
	{0xECu, 0x03u},
	{0x31u, 0x20u},
	{0x90u, 0x02u},
	{0xA1u, 0x20u},
	{0xB4u, 0x01u},
	{0xCCu, 0x08u},
	{0xE8u, 0x02u},
	{0x40u, 0x04u},
	{0x41u, 0x10u},
	{0x4Cu, 0x02u},
	{0x4Fu, 0x20u},
	{0x50u, 0x01u},
	{0x51u, 0x10u},
	{0x54u, 0x01u},
	{0x57u, 0x10u},
	{0x84u, 0x03u},
	{0x8Cu, 0x04u},
	{0x90u, 0x02u},
	{0xD4u, 0x07u},
	{0xD6u, 0x04u},
	{0xE4u, 0x02u},
	{0x00u, 0x02u},
	{0x01u, 0x01u},
	{0x0Cu, 0x02u},
	{0x0Du, 0x01u},
	{0x10u, 0x02u},
	{0x1Cu, 0x02u},
	{0x03u, 0x03u},
};


/* IOPINS0_0 Address: CYDEV_IO_PRT_PRT0_DM0 Size (bytes): 8 */
static CYDATADECL(BS_IOPINS0_0_VAL) [] DMAINITSEC = {
	0x20, 0x22, 0x02, 0x00, 0x02, 0x00, 0x80, 0x00};

/* IOPINS0_2 Address: CYDEV_IO_PRT_PRT2_DM0 Size (bytes): 8 */
static CYDATADECL(BS_IOPINS0_2_VAL) [] DMAINITSEC = {
	0x00, 0x0F, 0x0F, 0x00, 0x0F, 0x00, 0x00, 0x00};

/* IOPINS0_4 Address: CYDEV_IO_PRT_PRT4_DM0 Size (bytes): 8 */
static CYDATADECL(BS_IOPINS0_4_VAL) [] DMAINITSEC = {
	0x00, 0x0F, 0x0F, 0x00, 0x0F, 0x00, 0x00, 0x00};

/* IOPORT_0 Address: CYDEV_PRTDSI_PRT0_BASE Size (bytes): 7 */
static CYDATADECL(BS_IOPORT_0_VAL) [] DMAINITSEC = {
	0x02, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00};

/* IOPORT_2 Address: CYDEV_PRTDSI_PRT2_BASE Size (bytes): 7 */
static CYDATADECL(BS_IOPORT_2_VAL) [] DMAINITSEC = {
	0x0C, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00};

/* IOPORT_4 Address: CYDEV_PRTDSI_PRT4_BASE Size (bytes): 7 */
static CYDATADECL(BS_IOPORT_4_VAL) [] DMAINITSEC = {
	0x06, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00};


#if defined(__C51__) || defined(__CX51__)
extern void cfg_write_bytes_code(void CYCODE *table);
extern void cfg_write_bytes(void CYFAR *table);
#else
/* For 32-bit little-endian architectures */
static void cfg_write_bytes32(void)
{
	unsigned int i, j = 0;
	for (i = 0; i < CY_CFG_BASE_ADDR_COUNT; i++)
	{
		uint32 baseAddr = cy_cfg_addr_table[i];
		uint8 count = baseAddr & 0xFFu;
		baseAddr &= 0xFFFFFF00u;
		while (count--)
		{
			CY_SET_XTND_REG8((void CYFAR *)(baseAddr + cy_cfg_data_table[j].offset), cy_cfg_data_table[j].value);
			j++;
		}
	}
}
#endif

#if defined(__C51__) || defined(__CX51__)
#define CYMEMZERO8(a,c) cymemzero((a),(c))
#define CYCONFIGCPY8(d,s,c) cyconfigcpy((c),(s),(d))
#define CYCONFIGCPYCODE8(d,s,c) cyconfigcpycode((c),(s),(d))
#else
#if defined(__GNUC__) || defined(__ARMCC_VERSION)
__attribute__ ((unused))
#endif
static void cymemzero8(void *addr, unsigned int count)
{
	uint8 *addr8 = (uint8 *)addr;
	while (count--)
	{
		*addr8 = 0;
		addr8++;
	}
}

#if defined(__GNUC__) || defined(__ARMCC_VERSION)
__attribute__ ((unused))
#endif
static void cymemcpy8(void *dest, const void *src, unsigned int count)
{
	uint8 *dest8 = (uint8 *)dest;
	const uint8 *src8 = (const uint8 *)src;

	while (count--)
	{
		*dest8 = *src8;
		dest8++;
		src8++;
	}
}

#define CYMEMZERO8(a,c) cymemzero8((a),(c))
#define CYCONFIGCPY8(d,s,c) cymemcpy8((d),(s),(c))
#define CYCONFIGCPYCODE8(d,s,c) cymemcpy8((d),(s),(c))
#endif

static void ClockSetup(void)
{
	reg32  timeout;
	reg32* timeout_p = &timeout;
	reg8   pllLock;
	CY_SET_XTND_REG24((void CYFAR *)(CYDEV_CLKDIST_DCFG0_CFG0), 0x180001);
	CY_SET_XTND_REG24((void CYFAR *)(CYDEV_CLKDIST_DCFG1_CFG0), 0x190026);
	CY_SET_XTND_REG24((void CYFAR *)(CYDEV_CLKDIST_DCFG2_CFG0), 0x193414);
	CY_SET_XTND_REG8((void CYFAR *)(CYDEV_SLOWCLK_ILO_CR0), 0x02);
	CY_SET_XTND_REG8((void CYFAR *)(CYDEV_CLKDIST_CR), 0x08);
	CY_SET_XTND_REG8((void CYFAR *)(CYDEV_FASTCLK_IMO_CR), 0x03);
	CY_SET_XTND_REG8((void CYFAR *)(CYDEV_MFGCFG_IMO_TR1), (CY_GET_XTND_REG8(CYDEV_FLSHID_BASE + 0x108)));
	CY_SET_XTND_REG16((void CYFAR *)(CYDEV_FASTCLK_PLL_P), 0x0008);
	CY_SET_XTND_REG8((void CYFAR *)(CYDEV_CLKDIST_CR), 0x08);
	CY_SET_XTND_REG16((void CYFAR *)(CYDEV_FASTCLK_PLL_CFG0), 0x1051);
	pllLock = 0;
	for (timeout = 304; *timeout_p && (pllLock != 0x03u); timeout--) { pllLock = 0x03u & ((pllLock << 1) | ((CY_GET_XTND_REG8(CYDEV_FASTCLK_PLL_SR) & 0x01u) >> 0)); }
	CY_SET_XTND_REG16((void CYFAR *)(CYDEV_CLKDIST_MSTR0), 0x0103);
	CY_SET_XTND_REG8((void CYFAR *)(CYDEV_CLKDIST_MSTR0), 0x00);
	CY_SET_XTND_REG8((void CYFAR *)(CYDEV_CLKDIST_BCFG0), 0x00);
	CY_SET_XTND_REG8((void CYFAR *)(CYDEV_CLKDIST_BCFG2), 0x48);
	CY_SET_XTND_REG8((void CYFAR *)(CYDEV_CLKDIST_LD), 0x02);

	CY_SET_XTND_REG8((void CYFAR *)(CYDEV_PM_ACT_CFG2), ((CY_GET_XTND_REG8(CYDEV_PM_ACT_CFG2) | 0x07)));
}

/* Analog API Functions */
void AnalogSetDefault(void)
{
	CY_SET_XTND_REG8(CYDEV_IO_PRT_PRT0_AG, 0x80);
	CY_SET_XTND_REG8(CYDEV_ANAIF_CFG_BG_CR0, 0x08);
	CY_SET_XTND_REG8(CYDEV_ANAIF_CFG_SAR0_CSR1, 0x40);
	CY_SET_XTND_REG8(CYDEV_ANAIF_RT_SAR0_SW0, 0x80);
	CY_SET_XTND_REG8(CYDEV_ANAIF_RT_SAR0_SW3, 0x20);
	CY_SET_XTND_REG8(CYDEV_ANAIF_CFG_PUMP_CR0, 0x44);
}

#define CY_AMUX_UNUSED CYDEV_BOOST_SR

/* Digital routing enable Functions */
static void EnableDigitalRouting() {
	CY_SET_XTND_REG8(CYDEV_UCFG_BCTL0_BANK_CTL, CY_GET_XTND_REG8(CYDEV_UCFG_BCTL0_BANK_CTL) | 0x02);
	CY_SET_XTND_REG8(CYDEV_UCFG_BCTL1_BANK_CTL, CY_GET_XTND_REG8(CYDEV_UCFG_BCTL1_BANK_CTL) | 0x02);
}

/* This function is called by the start-up code for the selected device. */
void cyfitter_cfg(void)
{
	uint8 CYDATA i;

#ifdef CYGlobalIntDisable
	CYGlobalIntDisable;
#endif

	CY_SET_XTND_REG8((void CYFAR *)(CYDEV_CACHE_CC_CTL), ((CYDEV_INSTRUCT_CACHE_ENABLED) ? 0x40 : 0x41));
	CY_SET_XTND_REG8((void CYFAR *)(CYDEV_PHUB_CH0_BASIC_CFG), 0x00);
	CY_SET_XTND_REG8((void CYFAR *)(CYDEV_PHUB_CH1_BASIC_CFG), 0x00);

	CY_SET_XTND_REG8(CYDEV_MFGCFG_MLOGIC_DBG_DBE, (CY_GET_XTND_REG8(CYDEV_MFGCFG_MLOGIC_DBG_DBE) | 0x01));
	for (i = 0; i < CFG_MEMSET_COUNT; i++)
	{
		const cfg_memset_t CYCODE * CYDATA ms = &cfg_memset_list[i];
		CYMEMZERO(ms->address, ms->size);
	}

	cfg_write_bytes32();

	CYCONFIGCPYCODE8((void CYFAR *)(CYDEV_PRTDSI_PRT0_BASE), (void CYCODE *)(BS_IOPORT_0_VAL), 7);
	CYMEMZERO8((void CYFAR *)(CYDEV_PRTDSI_PRT1_BASE), 7);
	CYCONFIGCPYCODE8((void CYFAR *)(CYDEV_PRTDSI_PRT2_BASE), (void CYCODE *)(BS_IOPORT_2_VAL), 7);
	CYMEMZERO8((void CYFAR *)(CYDEV_PRTDSI_PRT3_BASE), 7);
	CYCONFIGCPYCODE8((void CYFAR *)(CYDEV_PRTDSI_PRT4_BASE), (void CYCODE *)(BS_IOPORT_4_VAL), 7);
	CYMEMZERO8((void CYFAR *)(CYDEV_PRTDSI_PRT5_BASE), 7);
	CYMEMZERO8((void CYFAR *)(CYDEV_PRTDSI_PRT6_BASE), 7);
	CYMEMZERO8((void CYFAR *)(CYDEV_PRTDSI_PRT12_BASE), 6);
	CYMEMZERO8((void CYFAR *)(CYDEV_PRTDSI_PRT15_BASE), 7);
	/* BYTES WRITTEN: 62 */
	EnableDigitalRouting();

	CyEnableDigitalArray();

	CYCONFIGCPYCODE((void CYFAR *)(CYDEV_IO_PRT_PRT0_DM0), (void CYCODE *)(BS_IOPINS0_0_VAL), 8);
	CYCONFIGCPYCODE((void CYFAR *)(CYDEV_IO_PRT_PRT2_DM0), (void CYCODE *)(BS_IOPINS0_2_VAL), 8);
	CYCONFIGCPYCODE((void CYFAR *)(CYDEV_IO_PRT_PRT4_DM0), (void CYCODE *)(BS_IOPINS0_4_VAL), 8);
	/* BYTES WRITTEN: 24 */

	CY_SET_XTND_REG8((void CYFAR *)(CYDEV_CACHE_CC_CTL), ((CYDEV_INSTRUCT_CACHE_ENABLED) ? 0x00 : 0x01));
	ClockSetup();
	CY_SET_XTND_REG8((void CYFAR *)(CYDEV_CACHE_CC_CTL), ((CYDEV_INSTRUCT_CACHE_ENABLED) ? 0x40 : 0x41));

	AnalogSetDefault();
}

/* [] END OF FILE */
