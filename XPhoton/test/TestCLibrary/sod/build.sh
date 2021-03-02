cd host
make \
    CROSS_COMPILE=/home/friedy/Documents/optee/out-br/host/bin/arm-linux-gnueabihf- \
    TEEC_EXPORT=/home/friedy/Documents/optee/optee_client/out/export/usr \
    --no-builtin-variables

cd ../
cd ta
 make \
    CROSS_COMPILE=/home/friedy/Documents/optee/out-br/host/bin/arm-linux-gnueabihf- \
    PLATFORM=vexpress-qemu_virt \
    TA_DEV_KIT_DIR=/home/friedy/Documents/optee/optee_os/out/arm/export-ta_arm32
