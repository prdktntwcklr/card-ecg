#ifndef DISPLAY_REGISTERS_H
#define DISPLAY_REGISTERS_H

#define SSD1306_SET_LOW_COLUMN                       (0x00)
#define SSD1306_SET_HIGH_COLUMN                      (0x10)

#define SSD1306_MEMORY_MODE                          (0x20)
#define SSD1306_COLUMN_ADDR                          (0x21)
#define SSD1306_PAGE_ADDR                            (0x22)

#define SSD1306_SET_START_LINE                       (0x40)

#define SSD1306_SET_CONTRAST                         (0x81)

#define SSD1306_SEG_REMAP                            (0xA0)

#define SSD1306_DISPLAYALLON_RESUME                  (0xA4)
#define SSD1306_DISPLAYALLON                         (0xA5)

#define SSD1306_DISPLAY_NORMAL                       (0xA6)
#define SSD1306_DISPLAY_INVERT                       (0xA7)

#define SSD1306_SET_MULTIPLEX                        (0xA8)

#define SSD1306_DISPLAY_OFF                          (0xAE)
#define SSD1306_DISPLAY_ON                           (0xAF)

#define SSD1306_COM_SCAN_INC                         (0xC0)
#define SSD1306_COM_SCAN_DEC                         (0xC8)

#define SSD1306_SET_DISPLAY_OFFSET                   (0xD3)

#define SSD1306_SET_DISPLAY_CLOCK_DIV                (0xD5)

#define SSD1306_SET_PRECHARGE                        (0xD9)

#define SSD1306_SET_COM_PINS                         (0xDA)

#define SSD1306_SET_VCOMH_DESELECT                   (0xDB)

#define SSD1306_CHARGE_PUMP                          (0x8D)

#define SSD1306_RIGHT_HORIZONTAL_SCROLL              (0x26)
#define SSD1306_LEFT_HORIZONTAL_SCROLL               (0x27)
#define SSD1306_VERTICAL_AND_RIGHT_HORIZONTAL_SCROLL (0x29)
#define SSD1306_VERTICAL_AND_LEFT_HORIZONTAL_SCROLL  (0x2A)
#define SSD1306_DEACTIVATE_SCROLL                    (0x2E)
#define SSD1306_ACTIVATE_SCROLL                      (0x2F)
#define SSD1306_SET_VERTICAL_SCROLL_AREA             (0xA3)

#endif // DISPLAY_REGISTERS_H
/*** end of file ***/
