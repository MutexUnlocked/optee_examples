// Copyright (c) 2021, Friedrich Doku

#include <err.h>
#include <stdio.h>
#include <string.h>
#include "incbin.h"

#define INCBIN_PREFIX
#define INCBIN_STYLE INCBIN_STYLE_SNAKE


/* OP-TEE TEE client API (built by optee_client) */
#include <tee_client_api.h>

/* To the the UUID (found the the TA's h-file(s)) */
#include "xphoton_uuid.h"

// Load the image into memory
INCBIN(image, "/host/f1.jpg");

// Load the model into memory
INCBIN(face_realnet_model, "/host/face.realnet.sod");


int main(void)
{
	printf("File loaded\n");

	TEEC_Result	   res;
	TEEC_Context   ctx;
	TEEC_Session   sess;
	TEEC_Operation op;
	TEEC_UUID	   uuid = XPHOTON_UUID;
	uint32_t	   err_origin;

	/* Initialize a context connecting us to the TEE */
	res = TEEC_InitializeContext(NULL, &ctx);
	if (res != TEEC_SUCCESS) {
		errx(1, "TEEC_InitializeContext failed with code 0x%x", res);
	}

	/*
	 * Open a session to the TA */
	res = TEEC_OpenSession(&ctx, &sess, &uuid, TEEC_LOGIN_PUBLIC, NULL, NULL, &err_origin);
	if (res != TEEC_SUCCESS) {
		errx(1, "TEEC_Opensession failed with code 0x%x origin 0x%x", res, err_origin);
	}


	/* Clear the TEEC_Operation struct */
	memset(&op, 0, sizeof(op));

	/*
	 * Prepare the argument. Pass a value in the first parameter,
	 * the remaining three parameters are unused.
	 */


	/* printf("I GOT THIS DATA");
    for(int i = image_size-100; i < image_size; i++){
        printf("%x",image_data[i]);
    }
    printf("\n\n");*/

	op.paramTypes			   = TEEC_PARAM_TYPES(TEEC_MEMREF_TEMP_INPUT, TEEC_MEMREF_TEMP_INPUT, TEEC_NONE, TEEC_NONE);
	op.params[0].tmpref.buffer = face_realnet_model_data;
	op.params[0].tmpref.size   = face_realnet_model_size;
	op.params[1].tmpref.buffer = image_data;
	op.params[1].tmpref.size   = image_size;


	printf("SENDING MODEL AND IMAGE... \n");
	res = TEEC_InvokeCommand(&sess, XPHOTON_LOAD_IMAGE_AND_MODEL, &op, &err_origin);
	if (res != TEEC_SUCCESS) {
		errx(1, "TEEC_InvokeCommand failed with code 0x%x origin 0x%x", res, err_origin);
	}
	printf("PASSED!!");

	/*
	 * We're done with the TA, close the session and
	 * destroy the context.
	 */

	TEEC_CloseSession(&sess);

	TEEC_FinalizeContext(&ctx);

	return 0;
}
