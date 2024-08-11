ifndef ANDROID_NDK_HOME
    $(error ANDROID_NDK_HOME not set)
endif

ifndef KP_DIR
    KP_DIR = ../KernelPatch
endif


CC = $(ANDROID_NDK_HOME)/toolchains/llvm/prebuilt/linux-x86_64/bin/aarch64-linux-android35-clang
LD = $(ANDROID_NDK_HOME)/toolchains/llvm/prebuilt/linux-x86_64/bin/ld.lld

CFLAGS := -Wall -O2 -fno-PIC -fno-asynchronous-unwind-tables -fno-common

INCLUDE_DIRS := . include patch/include linux/include linux/arch/arm64/include linux/tools/arch/arm64/include

INCLUDE_FLAGS := $(foreach dir,$(INCLUDE_DIRS),-I$(KP_DIR)/kernel/$(dir))

objs := hello.o

all: hello.kpm

hello.kpm: ${objs}
	${CC} -r -o $@ $^

%.o: %.c
	${CC} $(CFLAGS) $(INCLUDE_FLAGS) -c -o $@ $<

.PHONY: clean
clean:
	rm -rf *.kpm
	find . -name "*.o" | xargs rm -f
