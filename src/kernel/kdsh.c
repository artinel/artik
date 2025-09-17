#include <kernel/kdsh.h>
#include <libk/stdio.h>
#include <io/console.h>
#include <libk/string.h>
#include <kernel/version.h>

enum color_type {
	PAINT_BG,
	BG,
	FG
};

static void process_cmd(const char *cmd);
static void set_color(enum color_type type);

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
		printf("version  Print kernel version\n");
		printf("paint_bg Paint console background\n");
		printf("set_bg   Set console character background color\n");
		printf("set_fg   Set console character foreground color\n");
		printf("clear    Clear the screen\n");
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
