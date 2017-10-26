/**
 * Author: Yongseok Jin
 * File: devices/ocssd/dm_ocssd.c
 *
 * Description: Interfaces to access Open-Channel SSD for BlueDBM.
 */

#if defined (KERNEL_MODE)
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/vmalloc.h>
#include <linux/sched/sysctl.h>
#include <linux/slab.h>
#include <linux/types.h>

#include <linux/nvme.h>
#include <linux/lightnvm.h>
#include <uapi/linux/lightnvm.h>

#else
#error Invalid Platform (KERNEL_MODE)
#endif

#include "debug.h"
#include "dm_ocssd.h"
#include "dev_params.h"

/* interface for dm */
bdbm_dm_inf_t _bdbm_dm_inf = {
	.ptr_private = NULL,
	.probe = dm_ocssd_probe,
	.open = dm_ocssd_open,
	.close = dm_ocssd_close,
	.make_req = dm_ocssd_make_req,
	.make_reqs = dm_ocssd_make_reqs,
	.end_req = dm_ocssd_end_req,
	.load = dm_ocssd_load,
	.store = dm_ocssd_store,
};

/* NVMe device command */
typedef struct {
	__u8	opcode;
	__u8	flags;
	__u16	command_id;
	__le32	nsid;
	__u64	rsvd2;
	__le64	metadata;
	__le64	prp1;
	__le64	prp2;
	__le64	spba;
	__le16	length;
	__le16	control;
	__le32	dsmgmt;
	__le64	slba;
} bdbm_nvme_command;

/**
 * Initializes and finds the NVMe Device from kernel.
 * 'params' does not really care for this function,
 * since device specification is fixed for CNEX-8800.
 *
 * @param bdi (bdbm_drv_info_t *): 			device information
 * @param params (bdbm_device_params_t *): 	given parameters
 * @return: 								0 if successful, else if not.
 */
uint32_t dm_ocssd_probe (bdbm_drv_info_t* bdi, bdbm_device_params_t* params)
{
	/* TODO find NVMe Device. */
	return -1;
}

/**
 * TODO don't know what would come here, maybe probe can do it all.
 * Creates target block device from given NVMe Device.
 *
 * @param bdi (bdbm_drv_info_t *): 	device information
 * @return: 						0 if successful, else if not.
 */
uint32_t dm_ocssd_open (bdbm_drv_info_t* bdi)
{
	/* TODO initialize NVMe target device. */
	return -1;
}

/**
 * Close the target device of NVMe.
 *
 * @param bdi (bdbm_drv_info_t *): 	device information
 * @return: 						0 if successful, else if not.
 */
uint32_t dm_ocssd_close (bdbm_drv_info_t* bdi)
{
	/* TODO close target device. */
	return -1;
}

/**
 * Creates and sends request for given low-level request.
 *
 * @param bdi (bdbm_drv_info_t *): 			device information
 * @param ptr_llm_req (bdbm_llm_req_t *): 	low-level request
 * @return: 								0 if successful, else if not.
 */
uint32_t dm_ocssd_make_req (bdbm_drv_info_t* bdi, bdbm_llm_req_t* ptr_llm_req)
{
	/* TODO make request for low-level request. */
	/* setting rq->private(?) data to ptr_llm_req would help for callback. */
	return -1;
}

/**
 * Creates and sends request for given high-level request.
 *
 * @param bdi (bdbm_drv_info_t *): 	device information
 * @param hr (bdbm_llm_req_t *): 	high-level request
 * @return: 						0 if successful, else if not.
 */
uint32_t dm_ocssd_make_reqs (bdbm_drv_info_t* bdi, bdbm_hlm_req_t* hr)
{
	/* TODO to make these work below,
	   new callback for bdbm_hlm_req_t should be defined. */
	bdbm_nvme_command cmd;
	struct request* rq = NULL;
	struct bio* bio = hr->blkio_req->bio;

	switch(hr->req_type)
	{
		/* write operation */
		case REQTYPE_WRITE:
		case REQTYPE_GC_WRITE:
		case REQTYPE_RMW_WRITE:
		case REQTYPE_META_WRITE:
			//cmd.opcode = NVM_OP_PWRITE;
			break;

		/* read operation */
		case REQTYPE_READ:
		case REQTYPE_GC_READ:
		case REQTYPE_RMW_READ:
		case REQTYPE_META_READ:
		case REQTYPE_READ_DUMMY:
			//cmd.opcode = NVM_OP_PREAD;
			break;

		/* erase operation for gc */
		case REQTYPE_GC_ERASE:
			//cmd.opcode = NVM_OP_ERASE;
			break;

		/* undefined request type */
		default:
			return -1;
	}
}

/**
 * Callback function for the end of I/O request.
 *
 * @param bdi (bdbm_drv_info_t *):			device information
 * @param ptr_llm_req (bdbm_llm_req_t *): 	low-level request
 */
uint32_t dm_ocssd_end_req (bdbm_drv_info_t* bdi, bdbm_llm_req_t* ptr_llm_req)
{
	bdbm_bug_on (ptr_llm_req == NULL);
	bdi->ptr_llm_inf->end_req (bdi, ptr_llm_req);
}

/* OCSSD would not support snapshots. */

uint32_t dm_ocssd_load (bdbm_drv_info_t* bdi, const char* fn)
{
	return -1;
}

uint32_t dm_ocssd_store (bdbm_drv_info_t* bdi, const char* fn)
{
	return -1;
}

















