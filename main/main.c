#include <stdio.h>
#include <string.h>
#include <time.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_event_loop.h"
#include "esp_wifi.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "cJSON.h"

#include "connect.h"
#include "server.h"

#define TAG "MAIN"
#define COUNTRY CONFIG_COUNTRY

xSemaphoreHandle connectionSemaphore;

void OnConnected(void *para)
{
  while (true)
  {
    if (xSemaphoreTake(connectionSemaphore, 10000 / portTICK_RATE_MS))
    {
      ESP_LOGI(TAG, "Processing");
      serverRegisterEndpoints();
      ESP_LOGI(TAG, "Done!");
      xSemaphoreTake(connectionSemaphore, portMAX_DELAY);
    }
    else
    {
      ESP_LOGE(TAG, "Restarting esp");
      esp_restart();
    }
  }
}

void app_main()
{
  esp_log_level_set(TAG, ESP_LOG_DEBUG);
  connectionSemaphore = xSemaphoreCreateBinary();
  wifiInit();
  xTaskCreate(&OnConnected, "handle connections", 1024 * 3, NULL, 5, NULL);
}