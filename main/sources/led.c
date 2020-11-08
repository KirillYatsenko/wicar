#include <stdio.h>
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

#define TAG "LED"
#define LED_PIN 4

static bool ledIsOn = false;
static bool initialized = false;

static void initialize(void);

void ledToggle(void)
{
    ESP_LOGI(TAG, "letToogle with current led status = %d", ledIsOn);

    initialize();
    ledIsOn = !ledIsOn;
    gpio_set_level(LED_PIN, ledIsOn);
}

static void initialize(void)
{
    if (initialized == true)
        return;

    initialized = true;

    gpio_pad_select_gpio(LED_PIN);
    gpio_set_direction(LED_PIN, GPIO_MODE_OUTPUT);
}
