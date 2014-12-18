/**
	This file is part of martink project.

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

#ifdef __cplusplus
extern "C" {
#endif

#include <disp/interface.h>

#define VT100_CHAR_WIDTH 6
#define VT100_CHAR_HEIGHT 8

#define VT100_MAX_COMMAND_ARGS 4


struct vt100_private {
	union flags {
		uint8_t val;
		struct {
			// 0 = cursor remains on last column when it gets there
			// 1 = lines wrap after last column to next line
			uint8_t cursor_wrap : 1; 
			uint8_t scroll_mode : 1;
			uint8_t origin_mode : 1; 
		}; 
	} flags;

	struct text_display_interface *display;
	
	//uint16_t screen_width, screen_height;
	// cursor position on the screen (0, 0) = top left corner. 
	int16_t cursor_x, cursor_y;
	int16_t saved_cursor_x, saved_cursor_y; // used for cursor save restore
	int16_t scroll_start_row, scroll_end_row; 
	// character width and height
	int8_t char_width, char_height;
	// colors used for rendering current characters
	uint16_t back_color, front_color;
	// the starting y-position of the screen scroll
	uint16_t scroll_value; 
	// command arguments that get parsed as they appear in the terminal
	uint8_t narg; uint16_t args[VT100_MAX_COMMAND_ARGS];
	// current arg pointer (we use it for parsing) 
	uint8_t carg;
	uint16_t screen_height, screen_width;
	
	void (*state)(struct vt100_private *term, uint8_t ev, uint16_t arg);
	//void (*send_response)(char *str);
	void (*ret_state)(struct vt100_private *term, uint8_t ev, uint16_t arg);
};

// we could hide the implementation completely, but then we would need to always use
// dynamic allocation. So we do it like this instead just to tell the user that the
// private variables are not meant to be accessed. 
struct vt100 {
	uint8_t data[sizeof(struct vt100_private)]; 
}; 

//void vt100_init(void (*send_response)(char *str));
void vt100_init(struct vt100 *self, struct text_display_interface *display); 
void vt100_putc(struct vt100 *self, uint8_t ch);
void vt100_puts(struct vt100 *self, const char *str);

#ifdef __cplusplus
}
#endif
