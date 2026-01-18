#ifndef DISPLAY_REGISTERS_H
#define DISPLAY_REGISTERS_H

#define SSD1306_SET_LOW_COLUMN                       (0x00U)
#define SSD1306_SET_HIGH_COLUMN                      (0x10U)

#define SSD1306_MEMORY_MODE                          (0x20U)
#define SSD1306_COLUMN_ADDR                          (0x21U)
#define SSD1306_PAGE_ADDR                            (0x22U)

#define SSD1306_SET_START_LINE                       (0x40U)

#define SSD1306_SET_CONTRAST                         (0x81U)

#define SSD1306_SEG_REMAP                            (0xA0U)

#define SSD1306_DISPLAYALLON_RESUME                  (0xA4U)
#define SSD1306_DISPLAYALLON                         (0xA5U)

#define SSD1306_DISPLAY_NORMAL                       (0xA6U)
#define SSD1306_DISPLAY_INVERT                       (0xA7U)

#define SSD1306_SET_MULTIPLEX                        (0xA8U)

#define SSD1306_DISPLAY_OFF                          (0xAEU)
#define SSD1306_DISPLAY_ON                           (0xAFU)

#define SSD1306_COM_SCAN_INC                         (0xC0U)
#define SSD1306_COM_SCAN_DEC                         (0xC8U)

#define SSD1306_SET_DISPLAY_OFFSET                   (0xD3U)

#define SSD1306_SET_DISPLAY_CLOCK_DIV                (0xD5U)

#define SSD1306_SET_PRECHARGE                        (0xD9U)

#define SSD1306_SET_COM_PINS                         (0xDAU)

#define SSD1306_SET_VCOMH_DESELECT                   (0xDBU)

#define SSD1306_CHARGE_PUMP                          (0x8DU)

#define SSD1306_RIGHT_HORIZONTAL_SCROLL              (0x26U)
#define SSD1306_LEFT_HORIZONTAL_SCROLL               (0x27U)
#define SSD1306_VERTICAL_AND_RIGHT_HORIZONTAL_SCROLL (0x29U)
#define SSD1306_VERTICAL_AND_LEFT_HORIZONTAL_SCROLL  (0x2AU)
#define SSD1306_DEACTIVATE_SCROLL                    (0x2EU)
#define SSD1306_ACTIVATE_SCROLL                      (0x2FU)
#define SSD1306_SET_VERTICAL_SCROLL_AREA             (0xA3U)

#endif // DISPLAY_REGISTERS_H
/*** end of file ***/
