include ./make.config
include ./kernel/arch/$(ARCH)/make.config

LINKER = kernel/arch/$(ARCH)/linker.ld

SUB_TARGETS += kernel/kernel.o

all:
	$(MAKE) -C kernel all
	$(LD) -T $(LINKER) $(LDFLAGS) -o $(TARGET) $(SUB_TARGETS)

clean:
	rm $(shell find . -type f -name "*.o") $(TARGET)
