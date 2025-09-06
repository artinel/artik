include ./make.config
include ./arch/$(ARCH)/make.config

CSOURCES += $(shell find . -type d \( -path ./arch  \) -prune -o -name "*.c" -print)
CSOURCES += $(shell find arch/$(ARCH) -type f -name "*.c")

ASM_SOURCES += $(shell find . -type d -name arch -prune -o -name "*.asm" -print)
ASM_SOURCES += $(shell find arch/$(ARCH) -type f -name "*.asm")

OBJECTS = $(CSOURCES:.c=_c.o)
OBJECTS += $(ASM_SOURCES:.asm=_asm.o)

LINKER = arch/$(ARCH)/linker.ld

DOXYGEN_CONF = doc-config

%_c.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%_asm.o: %.asm
	$(ASM) $(ASMFLAGS) $< -o $@

all: $(TARGET)

$(TARGET): $(OBJECTS)
	ld -T $(LINKER) $(LDFLAGS) -o $(TARGET) $(OBJECTS)

clean:
	rm -f $(shell find . -type f -name "*.o")
	rm -f $(TARGET)

docs:
	doxygen doc-config

clean-docs:
	rm -rf docs
