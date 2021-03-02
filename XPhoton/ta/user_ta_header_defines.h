// Copyright (c) 2021, Friedrich Doku

/*
 * The name of this file must not be modified
 */

#ifndef USER_TA_HEADER_DEFINES_H
#define USER_TA_HEADER_DEFINES_H

/* To get the TA UUID definition */
#include <xphoton_ta.h>

#define TA_UUID XPHOTON_UUID

/*
 * TA properties: multi-instance TA, no specific attribute
 * TA_FLAG_EXEC_DDR is meaningless but mandated.
 */
#define TA_FLAGS TA_FLAG_EXEC_DDR
#define PGT_CACHE_SIZE 7
/* Provisioned stack size */
#define TA_STACK_SIZE (1 * 1024 * 1024)

/* Provisioned heap size for TEE_Malloc() and friends */
#define TA_DATA_SIZE (5 * 1024 * 1024)

/* Extra properties (give a version id and a string name) */
#define TA_CURRENT_TA_EXT_PROPERTIES                                                                         \
	{"gp.ta.description", USER_TA_PROP_TYPE_STRING, "XPhoton Monitoring Space Without Sacrificing Privacy"}, \
	{                                                                                                        \
		"gp.ta.version", USER_TA_PROP_TYPE_U32, &(const uint32_t) { 0x0010 }                                 \
	}

#endif /* USER_TA_HEADER_DEFINES_H */
