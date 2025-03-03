include ./make.config
include ./kernel/arch/$(ARCH)/make.config

CSOURCES += $(shell find . -type d \( -path ./kernel/arch  \) -prune -o -name "*.c" -print)
CSOURCES += $(shell find kernel/arch/$(ARCH) -type f -name "*.c")

SSOURCES += $(shell find . -type d -name arch -prune -o -name "*.s" -print)
SSOURCES += $(shell find kernel/arch/$(ARCH) -type f -name "*.s")

OBJECTS = $(CSOURCES:.c=_c.o)
OBJECTS += $(SSOURCES:.s=_s.o)

LINKER = kernel/arch/$(ARCH)/linker.ld

%_c.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%_s.o: %.s
	$(CC) $(CFLAGS) -c $< -o $@

all: $(TARGET)

$(TARGET): $(OBJECTS)
	ld -T $(LINKER) $(LDFLAGS) -o $(TARGET) $(OBJECTS)

clean:
	rm $(shell find . -type f -name "*.o")
	rm $(TARGET)
