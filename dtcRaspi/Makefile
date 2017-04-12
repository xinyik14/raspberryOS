
dtcMainFile := dtcMain

dtcDefault: kernel7.img

ARMGCC = arm-none-eabi-gcc
ARGS = -O0 -DRPI2 -mfpu=neon-vfpv4 -mfloat-abi=hard -march=armv7-a -mtune=cortex-a7 -nostartfiles

clean :
	rm -f *.o
	rm -f *.bin
	rm -f *.hex
	rm -f *.elf
	rm -f *.list
	rm -f *.img
	rm -f *.bc
	rm -f *.clang.opt.s



kernel.elf : 
	$(ARMGCC) $(ARGS) -g -Wl,-T,rpi.x $(dtcMainFile).c rpi-gpio.c armc-09-cstubs.c armc-09-cstartup.c armc-09-start.S -o kernel.elf

kernel7.img: clean kernel.elf
	arm-none-eabi-objcopy kernel.elf -O binary kernel7.img
	rm -f *.o
	rm -f *.elf
