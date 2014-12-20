/**
	A graphical LCD framebuffer interface

	martink firmware project is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	martink firmware is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with martink firmware.  If not, see <http://www.gnu.org/licenses/>.

	Author: Martin K. Schröder
	Email: info@fortmax.se
	Github: https://github.com/mkschreder
*/

#pragma once 

typedef enum {
	FB_PIXEL_FORMAT_1BIT, 
	FB_PIXEL_FORMAT_RGB8,
	FB_PIXEL_FORMAT_RGB16
} fb_pixel_type_t; 

typedef struct fb_image {
	uint16_t w; 
	uint16_t h;
	uint8_t *data; 
	fb_pixel_type_t format; 
} fb_image_t; 

typedef struct {
	uint8_t r, g, b, a; 
} fb_color_t; 

#define RGBA(r, g, b, a) (fb_color_t){r, g, b, a}

typedef void		(*fb_fill)(fb_color_t color, size_t count); 
typedef void 		(*fb_set_region)(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1); 
typedef size_t 	(*fb_write)(const uint8_t *data, size_t sz, fb_pixel_type_t type_of_supplied_data); 
typedef size_t 	(*fb_read)(uint8_t *data, size_t sz, fb_pixel_type_t encode_in_format); 
typedef void		(*fb_get_size)(uint16_t *width, uint16_t *height); 

struct fb_device {
	fb_fill				fill; 
	fb_set_region set_region; 
	fb_write 			write; 
	fb_read				read; 
	fb_get_size		get_size; 
}; 

typedef struct text_display_interface text_display_t;
typedef uint16_t color_t;

struct text_display_interface {
	void (*draw_char)(text_display_t *disp, uint8_t ch, uint16_t x, uint16_t y, color_t fg, color_t bg);
	void (*draw_fill_rect)(text_display_t *disp, uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, color_t color);

	void (*get_size)(text_display_t *disp, uint16_t *w, uint16_t *h); 
	void (*set_scroll_region)(text_display_t *disp, uint16_t start, uint16_t end);
	void (*set_top_line)(text_display_t *disp, uint16_t idx);
	void (*clear)(text_display_t *disp);
}; 
