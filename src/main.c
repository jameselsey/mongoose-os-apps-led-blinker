#include <stdio.h>
#include "mgos_app.h"
#include "mgos_gpio.h"
#include "mgos_timers.h"

// Define the GPIO pins for the LEDs
#define RED_LED 16
#define YELLOW_LED 17
#define GREEN_LED 18

// Initialise states for LEDs, start with the red on and others off
bool redOn = 1;
bool yellowOn = 0;
bool greenOn = 0;

// This function gets invoked by the timer, every X seconds
static void timer_cb(void *arg) {
  
  // Check which LED is on, then flip the next one on
  if (redOn){
    redOn = 0;
    yellowOn = 1;
    greenOn = 0;
    printf("YELLOW\n");
  } else if (yellowOn){
    redOn = 0;
    yellowOn = 0;
    greenOn = 1;
    printf("GREEN\n");
  } else if (greenOn){
    redOn = 1;
    yellowOn = 0;
    greenOn = 0;
    printf("RED\n");
  }

// Update states of LEDs /GPIO pins
  mgos_gpio_write(RED_LED, redOn);
  mgos_gpio_write(YELLOW_LED, yellowOn);
  mgos_gpio_write(GREEN_LED, greenOn);

  (void) arg;
}

// Entry point to app
enum mgos_app_init_result mgos_app_init(void) {
  // GPIO pins can work on input or output, as we're lighting LEDs, they
  // are all set to output
  mgos_gpio_set_mode(RED_LED, MGOS_GPIO_MODE_OUTPUT);
  mgos_gpio_set_mode(YELLOW_LED, MGOS_GPIO_MODE_OUTPUT);
  mgos_gpio_set_mode(GREEN_LED, MGOS_GPIO_MODE_OUTPUT);
  
  // Every 1 second, invoke timer_cb. 2nd arg means repeat continuously
  mgos_set_timer(1000 , true , timer_cb, NULL);

  return MGOS_APP_INIT_SUCCESS;
}
