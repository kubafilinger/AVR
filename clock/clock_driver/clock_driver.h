#define DAY_SECONDS 86400
#define DAY_MINUTES 3600
#define DAY_HOURS 24
#define MINUTE_SECONDS 60
#define HOUR_SECONDS 3600

#define CHANGE_STATUS 0

volatile uint32_t CLOCKTime = 0;
volatile uint8_t CLOCKStatus = 0b00000000;

void set_timer_rtc();
int getSeconds();
int getMinutes();
int getHours();
int * getTime();

#include "clock_driver.c"