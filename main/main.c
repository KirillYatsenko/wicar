#include "esp_event.h"
#include "esp_log.h"

#include "connect.h"
#include "server.h"

#define TAG "MAIN"

void app_main()
{
  if (wifiInit() != ESP_OK)
  {
    ESP_LOGE(TAG, "Restarting esp");
    esp_restart();
  }

  serverStart();
}