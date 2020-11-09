#include <stdio.h>
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

#define TAG "DRIVER"

#define LEFT_SIDE_MOTORS_1_PIN 12
#define LEFT_SIDE_MOTORS_2_PIN 13

#define RIGHT_SIDE_MOTORS_1_PIN 14
#define RIGHT_SIDE_MOTORS_2_PIN 15

static bool initialized = false;

static void initialize(void);

void driverStop(void)
{
    gpio_set_level(LEFT_SIDE_MOTORS_1_PIN, 0);
    gpio_set_level(LEFT_SIDE_MOTORS_2_PIN, 0);
    gpio_set_level(RIGHT_SIDE_MOTORS_1_PIN, 0);
    gpio_set_level(RIGHT_SIDE_MOTORS_2_PIN, 0);
}

void driverGoStraight(void)
{
    ESP_LOGI(TAG, "driverGoStraight start");
    initialize();

    gpio_set_level(LEFT_SIDE_MOTORS_1_PIN, 1);
    gpio_set_level(LEFT_SIDE_MOTORS_2_PIN, 0);

    gpio_set_level(RIGHT_SIDE_MOTORS_1_PIN, 1);
    gpio_set_level(RIGHT_SIDE_MOTORS_2_PIN, 0);

    ESP_LOGI(TAG, "driverGoStraight end");
}

void driverGoBack(void)
{
    ESP_LOGI(TAG, "driverGoBack start");
    initialize();

    gpio_set_level(LEFT_SIDE_MOTORS_1_PIN, 0);
    gpio_set_level(LEFT_SIDE_MOTORS_2_PIN, 1);

    gpio_set_level(RIGHT_SIDE_MOTORS_1_PIN, 0);
    gpio_set_level(RIGHT_SIDE_MOTORS_2_PIN, 1);

    ESP_LOGI(TAG, "driverGoBack end");
}

void driverTurnLeft(void)
{
    ESP_LOGI(TAG, "driverTurnLeft start");
    initialize();

    gpio_set_level(LEFT_SIDE_MOTORS_1_PIN, 1);
    gpio_set_level(LEFT_SIDE_MOTORS_2_PIN, 0);

    gpio_set_level(RIGHT_SIDE_MOTORS_1_PIN, 0);
    gpio_set_level(RIGHT_SIDE_MOTORS_2_PIN, 1);

    ESP_LOGI(TAG, "driverTurnLeft end");
}

void driverTurnRight(void)
{
    ESP_LOGI(TAG, "driverTurnRight start");
    initialize();

    gpio_set_level(LEFT_SIDE_MOTORS_1_PIN, 0);
    gpio_set_level(LEFT_SIDE_MOTORS_2_PIN, 1);

    gpio_set_level(RIGHT_SIDE_MOTORS_1_PIN, 1);
    gpio_set_level(RIGHT_SIDE_MOTORS_2_PIN, 0);

    ESP_LOGI(TAG, "driverTurnRight end");
}

static void initialize(void)
{
    if (initialized == true)
        return;

    initialized = true;

    gpio_pad_select_gpio(LEFT_SIDE_MOTORS_1_PIN);
    gpio_set_direction(LEFT_SIDE_MOTORS_1_PIN, GPIO_MODE_OUTPUT);

    gpio_pad_select_gpio(LEFT_SIDE_MOTORS_2_PIN);
    gpio_set_direction(LEFT_SIDE_MOTORS_2_PIN, GPIO_MODE_OUTPUT);

    gpio_pad_select_gpio(RIGHT_SIDE_MOTORS_1_PIN);
    gpio_set_direction(RIGHT_SIDE_MOTORS_1_PIN, GPIO_MODE_OUTPUT);

    gpio_pad_select_gpio(RIGHT_SIDE_MOTORS_2_PIN);
    gpio_set_direction(RIGHT_SIDE_MOTORS_2_PIN, GPIO_MODE_OUTPUT);
}
