#ifndef _SSD1306_H
#define _SSD1306_H

#include <stdint.h>

// Colors
#define BLACK SSD1306_BLACK		///< Draw 'off' pixels
#define WHITE SSD1306_WHITE		///< Draw 'on' pixels
#define INVERSE SSD1306_INVERSE ///< Invert pixels

/// fit into the SSD1306_ naming scheme
#define SSD1306_BLACK 0	  ///< Draw 'off' pixels
#define SSD1306_WHITE 1	  ///< Draw 'on' pixels
#define SSD1306_INVERSE 2 ///< Invert pixels

#define SSD1306_EXTERNALVCC 0x01  ///< External display voltage source
#define SSD1306_SWITCHCAPVCC 0x02 ///< Gen. display voltage from 3.3V

#define SSD1306_ADDR_CMD 0x00
#define SSD1306_ADDR_FB  0x40

typedef struct ssd1306_i2c_f ssd1306_i2c_f;
typedef struct ssd1306_oled ssd1306_oled;
struct ssd1306_i2c_f
{
	void (*command_list_fun)(ssd1306_oled *, uint8_t *, uint8_t);
	void (*command1_fun)(ssd1306_oled *, uint8_t);
	void (*framebuf_transmit_fun)(ssd1306_oled *);
};

struct ssd1306_oled
{
	void *i2cdev;
	uint8_t i2c_addr;
	ssd1306_i2c_f i2c_fun;

	uint16_t width, height;
	uint8_t rotation, inversion;

	uint8_t *frameBuffer;
};

// Init function
void oled_init(ssd1306_oled *oled, void *i2c, uint8_t addr, uint8_t vccstate, uint16_t w, uint16_t h);

// Command functions
void oled_set_invert(ssd1306_oled *oled, uint8_t i);
void oled_invert(ssd1306_oled *oled);

// Graphics Functions
void oled_flush(ssd1306_oled *oled);
void oled_clear(ssd1306_oled *oled);

void oled_draw_pixel(ssd1306_oled *oled, int16_t x, int16_t y, uint16_t color);
void oled_draw_bitmap(ssd1306_oled *oled, int16_t x, int16_t y, const uint8_t bitmap[], int16_t w, int16_t h, uint16_t color);

#endif /* _SSD1306_H */
