include ../make.config
include arch/$(ARCH)/make.config

KERNEL_TARGET = kernel.o
LINKER = arch/$(ARCH)/linker.ld

CSOURCES ?= $(shell find . -type d \( -path ./arch -o -path ./include \) -prune -o -name "*.c" -print)
CSOURCES += $(shell find arch/$(ARCH) -type f -name "*.c")

SSOURCES ?= $(shell find . -type d \( -path ./arch -o -path ./include \) -prune -o -name "*.s" -print)
SSOURCES += $(shell find arch/$(ARCH) -type f -name "*.s")

OBJECTS = $(CSOURCES:.c=_c.o)
OBJECTS += $(SSOURCES:.s=_s.o)

CFLAGS += -I./include

%_c.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%_s.o: %.s
	$(ASM) $(ASMFLAGS) -c $< -o $@


all: $(KERNEL_TARGET)

$(KERNEL_TARGET): $(OBJECTS)
	$(LD) -T $(LINKER) $(LDFLAGS) -o $(KERNEL_TARGET) $(OBJECTS)

clean:
	rm $(OBJECTS) $(KERNEL_TARGET)
