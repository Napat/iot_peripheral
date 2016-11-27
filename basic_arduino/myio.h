
#ifndef __MYIO_H__
#define __MYIO_H__

enum led_hw{
  LED_RED = 9,
  LED_GREEN = 10,
  LED_BLUE = 11,
} led_hw_t;

enum switch_hw{
	SWITCH_01 = 2,
	SWITCH_02 = 3,
} switch_hw_t;

//#define   DELAY_MS  (250)
#define   DELAY_MS  (100)

#endif /* __MYIO_H__ */
