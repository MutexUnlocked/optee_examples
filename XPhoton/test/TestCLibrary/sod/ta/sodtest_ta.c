// Copyright (c) 2020, Friedrich Doku


#include <tee_internal_api.h>
#include <tee_internal_api_extensions.h>

#include <sodtest_ta.h>

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
	uint32_t exp_param_types = TEE_PARAM_TYPES(TEE_PARAM_TYPE_VALUE_INOUT,
											   TEE_PARAM_TYPE_VALUE_INPUT,
											   TEE_PARAM_TYPE_NONE,
											   TEE_PARAM_TYPE_NONE);

	if (param_types != exp_param_types) {
		return TEE_ERROR_BAD_PARAMETERS;
	}

	IMSG("Got value: %u from NW", params[0].value.a);
	IMSG("Got value: %u from NW", params[1].value.a);

	params[0].value.a = params[0].value.a + params[1].value.a;

	return TEE_SUCCESS;
}


TEE_Result
TA_InvokeCommandEntryPoint(void __maybe_unused * sess_ctx,
						   uint32_t				 cmd_id,
						   uint32_t				 param_types,
						   TEE_Param			 params[4])
{
	if (cmd_id == TA_ADD_TWO_NUMBERS) {
		return sodtest(param_types, params);
	}
}
