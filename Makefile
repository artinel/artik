include ./make.config
include ./arch/$(ARCH)/make.config

CSOURCES += $(shell find . -type d \( -path ./arch  \) -prune -o -name "*.c" -print)
CSOURCES += $(shell find arch/$(ARCH) -type f -name "*.c")

SSOURCES += $(shell find . -type d -name arch -prune -o -name "*.s" -print)
SSOURCES += $(shell find arch/$(ARCH) -type f -name "*.s")

OBJECTS = $(CSOURCES:.c=_c.o)
OBJECTS += $(SSOURCES:.s=_s.o)

LINKER = arch/$(ARCH)/linker.ld

DOXYGEN_CONF = doc-config

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

docs:
	doxygen doc-config

clean-docs:
	rm -rf docs
