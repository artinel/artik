#include<kernel/vga.h>
#include<stdint.h>
#include<stdbool.h>

#define VGA_BUFFER_ADDR 0xB8000

static uint16_t* vga_buffer;
static uint8_t vga_bg = VGA_COLOR_BLACK;
static uint8_t vga_fg = VGA_COLOR_WHITE;
static uint8_t vga_color;
static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;
static size_t vga_row;
static size_t vga_col;
static bool is_vga_init = false;

static inline uint8_t vga_entry_color(uint8_t bg, uint8_t fg){
        return fg | bg << 4;
}

static inline uint16_t vga_entry(unsigned char c, uint8_t color){
        return (uint16_t) c | (uint16_t) color << 8;
}

static void vga_putentryat(unsigned char c, uint8_t color, size_t x, size_t y){
        const size_t index = y * VGA_WIDTH + x;
        vga_buffer[index] = vga_entry(c, color);
}

static void vga_scroll(){
        for(size_t y = 1; y < VGA_HEIGHT; y++){
                for(size_t x = 0; x < VGA_WIDTH; x++){
                        const size_t cur_index = y * VGA_WIDTH + x;
                        vga_putentryat(vga_buffer[cur_index], vga_color, x, y - 1);

                }
        }
}

static void vga_delete_last_line(){
        unsigned int x, *ptr;
        
        for(x = 0; x < VGA_WIDTH * 2; x++){
                ptr =(unsigned int*) VGA_BUFFER_ADDR + (VGA_WIDTH * 2) * (VGA_HEIGHT - 1) + x;
                *ptr = 0;
        }
}

void vga_init(void){
        if(!is_vga_init){
                vga_buffer = (uint16_t*) VGA_BUFFER_ADDR;
                vga_row = 0;
                vga_col = 0;
                vga_color = vga_entry_color(vga_bg, vga_fg);
                is_vga_init = true;
        }
}

inline void vga_set_bg(enum vga_color color){
        vga_bg = color;
        vga_color = vga_entry_color(vga_bg, vga_fg);
}

inline void vga_set_fg(enum vga_color color){
        vga_fg = color;
        vga_color = vga_entry_color(vga_bg, vga_fg);
}

void vga_putchar(unsigned char c){
        if(is_vga_init){
                vga_putentryat(c, vga_color, vga_col, vga_row);
                if(++vga_col == VGA_WIDTH){
                        vga_col = 0;
                        if(++vga_row == VGA_HEIGHT){
                                vga_scroll();
                                vga_delete_last_line();
                                vga_row = VGA_HEIGHT - 1;
                        }
                }
        }else{
                vga_init();
                vga_putchar(c);
                //TODO: add error report
        }
}

void vga_write(const char* data, size_t size){
        if(is_vga_init){
                for(size_t i = 0; i < size; i++){
                        vga_putchar(data[i]);
                }
        }else{
                vga_init();
                vga_write(data, size);
                //TODO: add error report
        }
}
