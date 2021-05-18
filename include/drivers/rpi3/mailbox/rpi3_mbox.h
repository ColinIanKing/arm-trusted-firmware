/*
 * Copyright (c) 2019, Arm Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef RPI3_MBOX_H
#define RPI3_MBOX_H

#include <stdint.h>

/* This struct must be aligned to 16 bytes */
typedef struct __packed __aligned(16) rpi3_mbox_request {
	uint32_t	size; /* Buffer size in bytes */
	uint32_t	code; /* Request/response code */
	uint32_t	tags[0];
} rpi3_mbox_request_t;

#define RPI3_MBOX_BUFFER_SIZE		U(256)

/* Constants to perform a request/check the status of a request. */
#define RPI3_MBOX_PROCESS_REQUEST	U(0x00000000)
#define RPI3_MBOX_REQUEST_SUCCESSFUL	U(0x80000000)
#define RPI3_MBOX_REQUEST_ERROR		U(0x80000001)

/* Command constants */
#define RPI3_TAG_HARDWARE_GET_BOARD_REVISION	U(0x00010002)
#define RPI_MBOX_SET_POWER_STATE                U(0x00028001)
#define RPI_MBOX_GET_CLOCK_RATE					U(0x00030002)
#define RPI_MBOX_GET_MAX_CLOCK_RATE				U(0x00030004)
#define RPI_MBOX_GET_MIN_CLOCK_RATE				U(0x00030007)
#define RPI_MBOX_GET_POE_HAT_VAL                U(0x00030049)
#define RPI_MBOX_SET_POE_HAT_VAL                U(0x00030050)
#define RPI_MBOX_SET_CLOCK_RATE					U(0x00038002)

#define RPI3_TAG_END				U(0x00000000)

#define RPI3_TAG_REQUEST		U(0x00000000)
#define RPI3_TAG_IS_RESPONSE		U(0x80000000) /* Set if response */
#define RPI3_TAG_RESPONSE_LENGTH_MASK	U(0x7FFFFFFF)

#define RPI3_CHANNEL_ARM_TO_VC		U(0x8)
#define RPI3_CHANNEL_MASK		U(0xF)

#define RPI_MBOX_CLOCK_RATE_EMMC				 U(0x000000001)
#define RPI_MBOX_CLOCK_RATE_UART				 U(0x000000002)
#define RPI_MBOX_CLOCK_RATE_ARM					 U(0x000000003)
#define RPI_MBOX_CLOCK_RATE_CORE				 U(0x000000004)
#define RPI_MBOX_CLOCK_RATE_V3D					 U(0x000000005)
#define RPI_MBOX_CLOCK_RATE_H264				 U(0x000000006)
#define RPI_MBOX_CLOCK_RATE_ISP					 U(0x000000007)
#define RPI_MBOX_CLOCK_RATE_SDRAM				 U(0x000000008)
#define RPI_MBOX_CLOCK_RATE_PIXEL				 U(0x000000009)
#define RPI_MBOX_CLOCK_RATE_PWM					 U(0x00000000a)


#define RPI_MBOX_POWER_STATE_ENABLE                           1
#define RPI_MBOX_POWER_STATE_WAIT                             2


void rpi3_vc_mailbox_request_send(rpi3_mbox_request_t *req, int req_size);

#endif
