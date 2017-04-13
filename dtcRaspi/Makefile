
dtcMainFile := dtcMain

dtcIncFiles := $(dtcMainFile) rpi-gpio rpi-systimer

dtcDefault: kernel7.img

ARMGCC = arm-none-eabi-gcc
CFLAGS = -O0 -DRPI2 -mfpu=neon-vfpv4 -mfloat-abi=hard -march=armv7-a -mtune=cortex-a7 -nostartfiles

clean :
	@echo -e "\e[1;33m [1] clean files \e[0m"
	@rm -f *.o
	@rm -f *.bin
	@rm -f *.hex
	@rm -f *.elf
	@rm -f *.list
	@rm -f *.img
	@rm -f *.bc
	@rm -f *.clang.opt.s


kernel.elf : 
	@echo -e '\e[1;33m [2] build kernel \e[0m'
	@$(ARMGCC) $(CFLAGS) -g -Wl,-T,rpi.x $(addsuffix .c, $(dtcIncFiles)) armc-09-cstubs.c armc-09-cstartup.c armc-09-start.S -o kernel.elf

kernel7.img: clean kernel.elf
	@echo -e '\e[1;33m [3] format kernel \e[0m'
	@arm-none-eabi-objcopy kernel.elf -O binary kernel7.img
	@rm -f *.o
	@rm -f *.elf
