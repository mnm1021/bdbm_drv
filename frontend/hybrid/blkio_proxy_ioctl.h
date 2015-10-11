/*
The MIT License (MIT)

Copyright (c) 2014-2015 CSAIL, MIT

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

#ifndef _BDBM_HOST_BLOCKIO_PROXY_IOCTL_H
#define _BDBM_HOST_BLOCKIO_PROXY_IOCTL_H

#define BDBM_PROXY_MAX_REQS 128
#define BDBM_PROXY_MAX_VECS	128

typedef enum {
	REQ_STT_ALLOC = 0x0100,

	REQ_STT_FREE = 0,
	REQ_STT_KERN_INIT = REQ_STT_ALLOC | 0x1, 
	REQ_STT_KERN_SENT = REQ_STT_ALLOC | 0x2,
	REQ_STT_USER_PROG = REQ_STT_ALLOC | 0x3,
	REQ_STT_USER_DONE = REQ_STT_ALLOC | 0x4,
} bdbm_proxy_req_status_t;

typedef struct {
	uint32_t id;
	bdbm_proxy_req_status_t stt;
	uint64_t bi_rw;
	uint64_t bi_sector;	
	uint64_t bi_size;
	uint64_t bi_bvec_cnt;
	uint8_t bi_bvec_data[BDBM_PROXY_MAX_VECS][KERNEL_PAGE_SIZE];	/* # of bvec is fixed to 32 by default */
	uint8_t ret;
	void* bio; /* only used by the kernel proxy */
} bdbm_blockio_proxy_req_t;

#define BDBM_BLOCKIO_PROXY_IOCTL_NAME		"bdbm_blockio_proxy"
#define BDBM_BLOCKIO_PROXY_IOCTL_DEVNAME	"/dev/bdbm_blockio_proxy"
#define BDBM_BLOCKIO_PROXY_IOCTL_MAGIC		'Y'

#define BDBM_BLOCKIO_PROXY_IOCTL_DONE		_IOWR (BDBM_BLOCKIO_PROXY_IOCTL_MAGIC, 0, int)

#endif