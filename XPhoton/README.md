# XPhoton

Clone XPhoton into a folder named XPhoton in Documents.
```
$ cd ~/Documents && mkdir XPhoton && cd XPhoton
$ git clone git@gitlab.prognosticlab.org:friedrich12/xphoton.git XPhoton
```

To run XPhoton on QEMU
```
$ cd ~/Documents && mkdir -p optee
$ cd optee
$ repo init -u https://github.com/OP-TEE/manifest.git -m default_stable.xml
$ repo sync -j4 --no-clone-bundle
```

and STM32MP1.
```
$ cd ~/Documents && mkdir -p optee2
$ cd optee2
$ repo init -u https://github.com/OP-TEE/manifest.git -m stm32mp1.xml.xml
$ repo sync
$ cd build
$ make toolchains
```


Build and add XPhoton to QEMU and STM32MP1 optee builds.
```
$ cd ~/Documents/XPhoton/XPhoton
$ ./build.sh
$ ./install.sh
```

Run on QEMU.
```
$ cd ~/Documents/optee/build
$ make && make run
```

Run on STM32MP1.
```
$ cd ~/Documents/optee2/build
$ make PLATFORM=stm32mp1-157C_DK2 all
$ sudo dd if=../out/bin/sdcard.img of=/dev/sdX conv=fdatasync status=progress
```


  
## Requirements

OP-TEE 3.15.0

## TODO

- [x] Port the mlibc generic math library to OPTEE
- [x] Load model in memory.
- [x] Load image in memory.
- [x] Solve memory limit problem.
 



