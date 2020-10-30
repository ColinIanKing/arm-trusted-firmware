/*
 * Copyright (c) 2018-2019, ARM Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <assert.h>

#include <platform_def.h>

#include <arch_helpers.h>

#include <drivers/rpi3/mailbox/rpi3_mbox.h>

#define RPI3_MBOX_BUFFER_SIZE		U(256)
static uint8_t __aligned(16) rpi3_mbox_buffer[RPI3_MBOX_BUFFER_SIZE];

/*******************************************************************************
 * Request board revision. Returns the revision and 0 on success, -1 on error.
 ******************************************************************************/
int rpi4_vc_get_board_revision(uint32_t *revision)
{
	uint32_t tag_request_size = sizeof(uint32_t);
	rpi3_mbox_request_t *req = (rpi3_mbox_request_t *) rpi3_mbox_buffer;

	assert(revision != NULL);

	req->size = sizeof(rpi3_mbox_buffer);
	req->code = RPI3_MBOX_PROCESS_REQUEST;

	req->tags[0] = RPI3_TAG_HARDWARE_GET_BOARD_REVISION;
	req->tags[1] = tag_request_size; /* Space available for the response */
	req->tags[2] = RPI3_TAG_REQUEST;
	req->tags[3] = 0; /* Placeholder for the response */

	req->tags[4] = RPI3_TAG_END;

	rpi3_vc_mailbox_request_send(req, RPI3_MBOX_BUFFER_SIZE);

	if (req->code != RPI3_MBOX_REQUEST_SUCCESSFUL) {
		ERROR("rpi4: mbox: Code = 0x%08x\n", req->code);
		return -1;
	}

	if (req->tags[2] != (RPI3_TAG_IS_RESPONSE | tag_request_size)) {
		ERROR("rpi4: mbox: get board revision failed (0x%08x)\n",
		      req->tags[2]);
		return -1;
	}

	*revision = req->tags[3];

	return 0;
}

int rpi4_vc_set_clock(uint32_t clock)
{
	uint32_t tag_request_size = sizeof(uint32_t)*2;
	rpi3_mbox_request_t *req = (rpi3_mbox_request_t *) rpi3_mbox_buffer;

	assert(revision != NULL);

	req->size = sizeof(rpi3_mbox_buffer);
	req->code = RPI3_MBOX_PROCESS_REQUEST;

	req->tags[0] = RPI_MBOX_SET_CLOCK_RATE;
	req->tags[1] = tag_request_size; /* Space available for the response */
	req->tags[2] = RPI3_TAG_REQUEST;
	req->tags[3] = RPI_MBOX_CLOCK_RATE_ARM;

	req->tags[4] = clock;
	req->tags[5] = 0; /*enable turbo*/
	req->tags[6] = RPI3_TAG_END;

	rpi3_vc_mailbox_request_send(req, RPI3_MBOX_BUFFER_SIZE);

	if (req->code != RPI3_MBOX_REQUEST_SUCCESSFUL) {
		ERROR("rpi4: mbox: Code = 0x%08x\n", req->code);
		return -1;
	}

	if (req->tags[2] != (RPI3_TAG_IS_RESPONSE | tag_request_size)) {
		ERROR("rpi4: mbox: set clock revision failed (0x%08x)\n",
		      req->tags[2]);
		return -1;
	}

	return 0;
}


int rpi4_vc_get_clock(uint32_t *clock)
{
	uint32_t tag_request_size = sizeof(uint32_t)*2;
	rpi3_mbox_request_t *req = (rpi3_mbox_request_t *) rpi3_mbox_buffer;

	assert(revision != NULL);

//	VERBOSE("rpi4: mbox: Sending request at %p\n", (void *)req);

	req->size = sizeof(rpi3_mbox_buffer);
	req->code = RPI3_MBOX_PROCESS_REQUEST;

	req->tags[0] = RPI_MBOX_GET_CLOCK_RATE;
	req->tags[1] = tag_request_size; /* Space available for the response */
	req->tags[2] = RPI3_TAG_REQUEST;
	req->tags[3] = RPI_MBOX_CLOCK_RATE_ARM;

	req->tags[4] = 0; /* Placeholder for the response */
	req->tags[5] = RPI3_TAG_END;

	rpi3_vc_mailbox_request_send(req, RPI3_MBOX_BUFFER_SIZE);

	if (req->code != RPI3_MBOX_REQUEST_SUCCESSFUL) {
		ERROR("rpi4: mbox: Code = 0x%08x\n", req->code);
		return -1;
	}

	if (req->tags[2] != (RPI3_TAG_IS_RESPONSE | tag_request_size)) {
		ERROR("rpi4: mbox: get clock revision failed (0x%08x)\n",
		      req->tags[2]);
		return -1;
	}

	*clock = req->tags[4];

	return 0;
}

int rpi4_vc_max_clock(uint32_t *clock)
{
	uint32_t tag_request_size = sizeof(uint32_t)*2;
	rpi3_mbox_request_t *req = (rpi3_mbox_request_t *) rpi3_mbox_buffer;

	assert(revision != NULL);

//	VERBOSE("rpi4: mbox: Sending request at %p\n", (void *)req);

	req->size = sizeof(rpi3_mbox_buffer);
	req->code = RPI3_MBOX_PROCESS_REQUEST;

	req->tags[0] = RPI_MBOX_GET_MAX_CLOCK_RATE;
	req->tags[1] = tag_request_size; /* Space available for the response */
	req->tags[2] = RPI3_TAG_REQUEST;
	req->tags[3] = RPI_MBOX_CLOCK_RATE_ARM;

	req->tags[4] = 0; /* Placeholder for the response */
	req->tags[5] = RPI3_TAG_END;

	rpi3_vc_mailbox_request_send(req, RPI3_MBOX_BUFFER_SIZE);

	if (req->code != RPI3_MBOX_REQUEST_SUCCESSFUL) {
		ERROR("rpi4: mbox: Code = 0x%08x\n", req->code);
		return -1;
	}

	if (req->tags[2] != (RPI3_TAG_IS_RESPONSE | tag_request_size)) {
		ERROR("rpi4: mbox: get clock revision failed (0x%08x)\n",
		      req->tags[2]);
		return -1;
	}

	*clock = req->tags[4];

	return 0;
}
