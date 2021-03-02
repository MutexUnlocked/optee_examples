// Copyright (c) 2021, Friedrich Doku

#include <tee_internal_api.h>
#include <tee_internal_api_extensions.h>
#include <string.h>
#include <xphoton_ta.h>
#include <sod.h>

sod_realnet * pNet = NULL;

TEE_Result
TA_CreateEntryPoint(void)
{
	IMSG("ENTRY POINT CREATED");
	return TEE_SUCCESS;
}

void TA_DestroyEntryPoint(void)
{
	IMSG("Destory Entry Point");
}

TEE_Result
TA_OpenSessionEntryPoint(uint32_t				  param_types,
						 TEE_Param __maybe_unused params[4],
						 void __maybe_unused ** sess_ctx)
{
	uint32_t exp_param_types = TEE_PARAM_TYPES(TEE_PARAM_TYPE_NONE,
											   TEE_PARAM_TYPE_NONE,
											   TEE_PARAM_TYPE_NONE,
											   TEE_PARAM_TYPE_NONE);

	if (param_types != exp_param_types) {
		return TEE_ERROR_BAD_PARAMETERS;
	}
	int * t = (int *)malloc(sizeof(int) * 1000);
	(void)&params;
	(void)&sess_ctx;

	return TEE_SUCCESS;
}

void TA_CloseSessionEntryPoint(void __maybe_unused * sess_ctx)
{
	(void)&sess_ctx; /* unused parameter*/
	IMSG("Goodbye To A World\n");
}

static TEE_Result
sodtest(uint32_t  param_types,
		TEE_Param params[4])
{
	uint32_t		exp_param_types			= TEE_PARAM_TYPES(TEE_PARAM_TYPE_MEMREF_INPUT,
												  TEE_PARAM_TYPE_MEMREF_INPUT,
												  TEE_PARAM_TYPE_NONE,
												  TEE_PARAM_TYPE_NONE);
	unsigned char * face_realnet_model_data = NULL;
	uint32_t		face_realnet_model_size = 0;
	uint8_t *		image_data				= NULL;
	size_t			image_size				= 0;

	if (param_types != exp_param_types) {
		return TEE_ERROR_BAD_PARAMETERS;
	}


	face_realnet_model_data = params[0].memref.buffer;
	face_realnet_model_size = params[0].memref.size;
	image_data				= params[1].memref.buffer;
	image_size				= params[1].memref.size;

	if (image_data == NULL) {
		DMSG("Failed to get IMAGE DATA");
		goto err;
	} else {
		IMSG("THE TA GOT THE MODEL");
	}

	{
		int ret = 0;

		ret = sod_realnet_create(&pNet);
		if (ret != SOD_OK) {
			DMSG("Could not create sod realnet.");
			return TEE_ERROR_GENERIC;
		}

		ret = sod_realnet_load_model_from_mem(pNet, face_realnet_model_data, face_realnet_model_size, 0);

		if (ret != SOD_OK) {
			DMSG("Could not load model realnet.");
			goto err;
		}
	}

	// Let's check if we got the write data

	/*IMSG("I GOT THIS DATA");
    for(int i = image_size-100; i < image_size; i++){
        IMSG("%x",image_data[i]);
    }
    IMSG("\n\n");*/

	// Let's see if we can load an image.
	{
		size_t	out_img_size = 0;
		sod_img grayscale_img;

		grayscale_img = sod_img_load_from_mem(image_data, image_size, SOD_IMG_GRAYSCALE);
		if (grayscale_img.data == NULL) {
			IMSG("Failed to load image.");
			goto err;
		} else {
			IMSG("IMAGE LOADED");
		}
	}

	return TEE_SUCCESS;

err:
	if (pNet != NULL) {
		sod_realnet_destroy(pNet);
	}
	return TEE_ERROR_GENERIC;
}


TEE_Result
TA_InvokeCommandEntryPoint(void __maybe_unused * sess_ctx,
						   uint32_t				 cmd_id,
						   uint32_t				 param_types,
						   TEE_Param			 params[4])
{
	if (cmd_id == XPHOTON_LOAD_IMAGE_AND_MODEL) {
		return sodtest(param_types, params);
	}
}
