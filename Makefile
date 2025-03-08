include ./make.config
include ./arch/$(ARCH)/make.config

CSOURCES += $(shell find . -type d \( -path ./arch  \) -prune -o -name "*.c" -print)
CSOURCES += $(shell find arch/$(ARCH) -type f -name "*.c")

SSOURCES += $(shell find . -type d -name arch -prune -o -name "*.s" -print)
SSOURCES += $(shell find arch/$(ARCH) -type f -not -name "crt*.s" -and -name "*.s")

CRTI_OBJ = arch/$(ARCH)/crti_s.o
CRTBEGIN_OBJ = $(shell $(CC) --print-file-name=crtbegin.o)
CRTEND_OBJ = $(shell $(CC) --print-file-name=crtend.o)
CRTN_OBJ = arch/$(ARCH)/crtn_s.o

OBJECTS = $(CRTI_OBJ) $(CRTBEGIN_OBJ)
OBJECTS += $(CSOURCES:.c=_c.o)
OBJECTS += $(SSOURCES:.s=_s.o)
OBJECTS += $(CRTEND_OBJ) $(CRTN_OBJ)

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
