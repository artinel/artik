/**
 * \file arch/x86/vga.c
 * \brief VGA implementation for x86 architecture
 * \author Artinel <artinel@proton.me>
 * \version 0.0.1
 * \date 2025-03-04
 * \copyright GNU Public License V3
 */

#include<kernel/vga.h>
#include<stdint.h>
#include<stdbool.h>

#define VGA_BUFFER_ADDR 0xB8000 		/**< Address of vga buffer in memory */
#define VGA_TAB 8 				/**< Number of spaces when tab character occures */

static uint16_t* vga_buffer;			/**< Pointer to vga buffer address */
static uint8_t vga_bg = VGA_COLOR_BLACK; 	/**< Character background */
static uint8_t vga_fg = VGA_COLOR_WHITE; 	/**< Character foreground(Text color) */
static uint8_t vga_color;			/**< Combination of vga_bg and vga_fg */
static const size_t VGA_WIDTH = 80; 		/**< VGA mode width(Columns) */
static const size_t VGA_HEIGHT = 25;		/**< VGA mode height(Rows) */
static size_t vga_row;				/**< Current cursor position on the screen(Row)*/
static size_t vga_col;				/**< Current cursor position on the screen(Column) */
static bool is_vga_init = false;		/**< For stating the vga initialization */

/**
 * Combine the background and foreground color together.
 *
 * \param bg Background color
 * \param fg Foreground color 
 *
 * \return The combined value of background and foreground.\n
 * Both background and foreground color are 4-Bits(|  BG  |  FG  |).\n
 * The return value is uint8_t which is 8-Bits.\n
 */

static inline uint8_t vga_entry_color(uint8_t bg, uint8_t fg){
        return fg | bg << 4;
}

/**
 * Combine a color and a character together.
 *
 * \param c	Entry Character
 * \param color	Entry color
 *
 * \return The combined value of character and color.\n
 * Both character and color are 8-Bits(|  COLOR  |  CHAR  |).\n
 * The return value is uint16_t which is 16-Bits.\n
 *
 * \sa vga_entry_color
 */

static inline uint16_t vga_entry(unsigned char c, uint8_t color){
        return (uint16_t) c | (uint16_t) color << 8;
}

/**
 * Put an entry at a specific location on the screen.
 *
 * \param c	Entry character
 * \param color	Entry color
 * \param x	Entry x location (0 >= x < VGA_WIDTH)
 * \param y	Entry y location (0 >= y < VGA_HEIGHT) 
 *
 * \sa VGA_WIDTH VGA_HEIGHT vga_entry vga_buffer
 */

static void vga_putentryat(unsigned char c, uint8_t color, size_t x, size_t y){
        const size_t index = y * VGA_WIDTH + x;
        vga_buffer[index] = vga_entry(c, color);
}

/**
 * Scroll the screen if cursor reach the end of screen.
 *
 * \sa VGA_WIDTH vga_buffer vga_putentryat vga_color
 */

static void vga_scroll(){
        for(size_t y = 1; y < VGA_HEIGHT; y++){
                for(size_t x = 0; x < VGA_WIDTH; x++){
                        const size_t cur_index = y * VGA_WIDTH + x;
                        vga_putentryat(vga_buffer[cur_index], vga_color, x, y - 1);

                }
        }
}

/**
 * Delete the last line on the screen after scrolling.
 *
 * \sa VGA_WIDTH VGA_BUFFER_ADDR VGA_HEIGHT
 */

static void vga_delete_last_line(){
        unsigned int x, *ptr;
        
        for(x = 0; x < VGA_WIDTH * 2; x++){
                ptr =(unsigned int*) VGA_BUFFER_ADDR + (VGA_WIDTH * 2) * (VGA_HEIGHT - 1) + x;
                *ptr = 0;
        }
}

/**
 * Initialize the VGA.
 *
 * \sa vga_buffer vga_row vga_col vga_color vga_entry_color vga_bg vga_fg is_vga_init VGA_BUFFER_ADDR
 */

void vga_init(void){
        if(!is_vga_init){
                vga_buffer = (uint16_t*) VGA_BUFFER_ADDR;                
		vga_row = 0;
                vga_col = 0;
                vga_color = vga_entry_color(vga_bg, vga_fg);
                is_vga_init = true;
        }
}

/**
 * Set VGA background color.
 *
 * \param color Background color
 * 
 * \sa vga_color vga_bg vga_entry_color vga_bg vga_fg
 */

inline void vga_set_bg(enum vga_color color){
        vga_bg = color;
        vga_color = vga_entry_color(vga_bg, vga_fg);
}

/**
 * Set VGA foreground color.
 *
 * \param color Foreground color
 *
 * \sa vga_color vga_fg vga_color vga_entry_color vga_bg
 */
inline void vga_set_fg(enum vga_color color){
        vga_fg = color;
        vga_color = vga_entry_color(vga_bg, vga_fg);
}

/**
 * Print a character on the screen.
 *
 * \param c The character that will be printed on the screen
 *
 * \sa is_vga_init vga_row vga_col VGA_TAB vga_putentryat vga_color
 * \sa VGA_WIDTH VGA_HEIGHT vga_scroll vga_delete_last_line vga_init
 */
void vga_putchar(unsigned char c){
        if(is_vga_init){
                if(c == '\n'){
                        vga_row++;
                        vga_col = 0;
                }else if(c == '\t'){
                        for(int i = 0; i < VGA_TAB; i++){
                                vga_putchar(' ');
                        }
                }else{
                        vga_putentryat(c, vga_color, vga_col, vga_row);
                        vga_col++;
                }
                if(vga_col >= VGA_WIDTH){
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
                /** \todo add error report for when the vga is not initialized */
        }
}

/**
 * Write a string with the given size on the screen
 *
 * \param data The string that will be printed on the screen
 * \param size Size of the string
 */
void vga_write(const char* data, size_t size){
        if(is_vga_init){
                for(size_t i = 0; i < size; i++){
                        vga_putchar(data[i]);
                }
        }else{
                vga_init();
                vga_write(data, size);
                /** \todo add error report for when the vga is not initialized */
        }
}
