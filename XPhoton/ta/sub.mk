global-incdirs-y += include
srcs-y += xphoton_ta.c
srcs-y += sod.c
cflags-y := -w -D_SBK_SGX  -DCS_ENABLE_STDIO=0  -DSTBI_NO_STDIO -DSOD_DISABLE_CNN -DSTBI_WRITE_NO_STDIO
# To remove a certain compiler flag, add a line like this
#cflags-template_ta.c-y += -Wno-strict-prototypes
