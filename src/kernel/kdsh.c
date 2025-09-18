#include <kernel/kdsh.h>
#include <libk/stdio.h>
#include <io/console.h>
#include <libk/string.h>
#include <kernel/version.h>
#include <libk/stdlib.h>
#include <kernel/memmap.h>
#include <stdlib.h>

enum color_type {
	PAINT_BG,
	BG,
	FG
};

static void process_cmd(const char *cmd);
static void set_color(enum color_type type);
static void interrupt(void);
static void kdsh_sleep(void);
static void kdsh_memmap(void);
static void kdsh_meminfo(void);

void init_kdsh(void) {
	while (1) {
		printf("$> ");
		char buffer[1024];
		gets(buffer, 1024);
		putchar('\n');
		process_cmd(buffer);
	}
}

static void process_cmd(const char *cmd) {
	if (strcmp(cmd, "help") == 0) {
		printf("version  \tPrint kernel version\n");
		printf("paint_bg \tPaint console background\n");
		printf("set_bg   \tSet console character background color\n");
		printf("set_fg   \tSet console character foreground color\n");
		printf("clear    \tClear the screen\n");
		printf("int      \tInterrupt the kernel\n");
		printf("sleep    \tSleep for n seconds\n");
		printf("memmap   \tPrint memory map\n");
		printf("meminfo  \tPrint memory information\n");
		return;
	}
	if (strcmp(cmd, "version") == 0) {
		printf("%s\n", VERSION);
		return;
	}

	if (strcmp(cmd, "paint_bg") == 0) {
		set_color(PAINT_BG);
		return;
	}

	if (strcmp(cmd, "clear") == 0) {
		console_clear();
		return;
	}

	if (strcmp(cmd, "set_bg") == 0) {
		set_color(BG);
		return;
	}

	if (strcmp(cmd, "set_fg") == 0) {
		set_color(FG);
		return;
	}

	if (strcmp(cmd, "int") == 0) {
		interrupt();
		return;
	}

	if (strcmp(cmd, "sleep") == 0) {
		kdsh_sleep();
		return;
	}

	if (strcmp(cmd, "memmap") == 0) {
		kdsh_memmap();
		return;
	}

	if (strcmp(cmd, "meminfo") == 0) {
		kdsh_meminfo();
		return;
	}

	printf("Command not found!!!\n");
}

static void set_color(enum color_type type) {
	printf("1-RED\n2-GREEN\n3-BLUE\n4-WHITE\n5-BLACK\n");
	printf("Enter : ");
	int c = getchar();
	printf("\n");
	uint32_t color = 0;
	switch(c) {
		case '1':
			color = 0xFF0000;
			break;
		case '2':
			color = 0x00FF00;
			break;
		case '3':
			color = 0x0000FF;
			break;
		case '4':
			color = 0xFFFFFF;
			break;
		case '5':
			color = 0x000000;
			break;
		default:
			printf("Invalid Option\n");
	}
	
	if (type == PAINT_BG){
		console_paint_background(color);
	} else if (type == BG) {
		console_set_background(color);
	} else {
		console_set_foreground(color);
	}
}

static void interrupt(void) {
	char buffer[3];
	printf("Enter the interrupt number(0 - 31) : ");
	gets(buffer, 3);
	uint8_t res = uatoi(buffer);
	
	if (res > 31) {
		printf("Interrupt number must be between 0 and 31\n");
		return;
	}

	switch(res) {
		case 0:
			__asm__ volatile("int $0");
			break;
		case 1:
			__asm__ volatile("int $1");
			break;
		case 2:
			__asm__ volatile("int $2");
			break;
		case 3:
			__asm__ volatile("int $3");
			break;
		case 4:
			__asm__ volatile("int $4");
			break;
		case 5:
			__asm__ volatile("int $5");
			break;
		case 6:
			__asm__ volatile("int $6");
			break;
		case 7:
			__asm__ volatile("int $7");
			break;
		case 8:
			__asm__ volatile("int $8");
			break;
		case 9:
			__asm__ volatile("int $9");
			break;
		case 10:
			__asm__ volatile("int $10");
			break;
		case 11:
			__asm__ volatile("int $11");
			break;
		case 12:
			__asm__ volatile("int $12");
			break;
		case 13:
			__asm__ volatile("int $13");
			break;
		case 14:
			__asm__ volatile("int $14");
			break;
		case 15:
			__asm__ volatile("int $15");
			break;
		case 16:
			__asm__ volatile("int $16");
			break;
		case 17:
			__asm__ volatile("int $17");
			break;
		case 18:
			__asm__ volatile("int $18");
			break;
		case 19:
			__asm__ volatile("int $19");
			break;
		case 20:
			__asm__ volatile("int $20");
			break;
		case 21:
			__asm__ volatile("int $21");
			break;
		case 22:
			__asm__ volatile("int $22");
			break;
		case 23:
			__asm__ volatile("int $23");
			break;
		case 24:
			__asm__ volatile("int $24");
			break;
		case 25:
			__asm__ volatile("int $25");
			break;
		case 26:
			__asm__ volatile("int $26");
			break;
		case 27:
			__asm__ volatile("int $27");
			break;
		case 28:
			__asm__ volatile("int $28");
			break;
		case 29:
			__asm__ volatile("int $29");
			break;
		case 30:
			__asm__ volatile("int $30");
			break;
		case 31:
			__asm__ volatile("int $31");
			break;
	}
}

static void kdsh_sleep(void) {
	printf("Enter seconds to sleep : ");
	char buffer[4];
	gets(buffer, sizeof(buffer));
	putchar('\n');
	uint16_t sec = uatoi(buffer);
	sleep(sec);
}

static void kdsh_memmap(void) {

	const char *types[] = {
		"USABLE",
		"RESERVED",
		"ACPI RECLAIMABLE",
		"ACPI NVS",
		"BAD MEMORY",
		"BOOTLOADER RECLAIMABLE",
		"EXECUTABLE AND MODULES",
		"FRAMEBUFFER"
	};

	uint64_t count = memmap_get_entry_count();
	memmap_entry_t *entry = 0;

	for (uint64_t i = 0; i < count; i++) {
		entry = memmap_get_entry(i);
		if (entry != NULL) {
			printf("BASE = 0x%ux\t", entry->base);
			printf("LENGTH = 0x%ux\t", entry->length);
			printf("TYPE = %ud - %s\n", entry->type, types[entry->type]);
		}
	}
}

static void kdsh_meminfo(void) {
	uint64_t count = memmap_get_entry_count();
	memmap_entry_t *entry = 0;

	uint64_t total = 0;
	uint64_t used = 0;
	uint64_t free = 0;

	for (uint64_t i = 0; i < count; i++) {
		entry = memmap_get_entry(i);
		if (entry != NULL) {
			if (entry->type == MEMMAP_USABLE) {
				free += entry->length;
			} else {
				used += entry->length;
			}

			total += entry->length;
		}
	}

	printf("Select Unit\n1 - Bytes\n2 - KB\n3 - MB\nEnter : ");
	char buffer[3];
	gets(buffer, sizeof(buffer));
	printf("\n");
	uint64_t unit = uatoi(buffer);

	const char *unit_txt[] = {"Bytes", "KB", "MB"};

	const char *total_unit = unit_txt[0];
	const char *used_unit = unit_txt[0];
	const char *free_unit = unit_txt[0];

	if (unit == 2) {
		if (total >= 1024) {
			total /= 1024;
			total_unit = unit_txt[1];	
		} else {
			total_unit = unit_txt[0];	
		}

		if (used >= 1024) {
			used /= 1024;
			used_unit = unit_txt[1];
		} else {
			used_unit = unit_txt[0];
		}

		if (free >= 1024) {
			free /= 1024;
			free_unit = unit_txt[1];
		} else {
			free_unit = unit_txt[0];
		}
	}

	if (unit == 3) {
		if (total >= 1024 * 1024) {
			total /= (1024 * 1024);
			total_unit = unit_txt[2];
		} else {
			if (total >= 1024) {
				total /= 1024;
				total_unit = unit_txt[1];	
			} else {
				total_unit = unit_txt[0];	
			}
		}

		if (used >= 1024 * 1024) {
			used /= (1024 * 1024);
			used_unit = unit_txt[2];
		} else {
			if (used >= 1024) {
				used /= 1024;
				used_unit = unit_txt[1];	
			} else {
				used_unit = unit_txt[0];	
			}
		}


		if (free >= 1024 * 1024) {
			free /= (1024 * 1024);
			free_unit = unit_txt[2];
		} else {
			if (free >= 1024) {
				free /= 1024;
				free_unit = unit_txt[1];	
			} else {
				free_unit = unit_txt[0];	
			}
		}
	}

	if (unit > 3) {
		printf("Invalid Option. Defaulting to bytes\n");
	}

	
	printf("TOTAL MEMORY = %ul %s\n", total, total_unit);
	printf("USED MEMORY  = %ul %s\n", used, used_unit);
	printf("FREE MEMORY  = %ul %s\n", free, free_unit);
}
