#include <stdio.h>
#include <string.h>
#include "esp_log.h"
#include "esp_http_server.h"
#include "esp_spiffs.h"

#include "driver.h"
#include "camera.h"
#include "led.h"

#define TAG "SERVER"

static esp_err_t on_url_hit(httpd_req_t *req)
{
    esp_vfs_spiffs_conf_t config = {
        .base_path = "/spiffs",
        .partition_label = NULL,
        .max_files = 5,
        .format_if_mount_failed = true};
    esp_vfs_spiffs_register(&config);

    ESP_LOGI(TAG, "url %s was hit", req->uri);
    char path[600];
    sprintf(path, "/spiffs%s", req->uri);
    if (strcmp(path, "/spiffs/") == 0)
    {
        sprintf(path, "/spiffs/%s", "index.html");
    }
    //style.css
    char *ptr = strrchr(path, '.');
    if (strcmp(ptr, ".css") == 0)
    {
        ESP_LOGI(TAG, "setting mime type to css");
        httpd_resp_set_type(req, "text/css");
    }
    FILE *file = fopen(path, "r");
    if (file == NULL)
    {
        httpd_resp_send_404(req);
        return ESP_OK;
    }

    char lineRead[256];
    while (fgets(lineRead, sizeof(lineRead), file))
    {
        httpd_resp_sendstr_chunk(req, lineRead);
    }
    httpd_resp_sendstr_chunk(req, NULL);
    esp_vfs_spiffs_unregister(NULL);
    return ESP_OK;
}

static esp_err_t on_straight(httpd_req_t *req)
{
    driverGoStraight();
    char *message = "{\"straight\": \"ok\"}";
    httpd_resp_send(req, message, strlen(message));
    return ESP_OK;
}

static esp_err_t on_back(httpd_req_t *req)
{
    driverGoBack();
    char *message = "{\"back\": \"ok\"}";
    httpd_resp_send(req, message, strlen(message));
    return ESP_OK;
}

static esp_err_t on_left(httpd_req_t *req)
{
    driverTurnLeft();
    char *message = "{\"left\": \"ok\"}";
    httpd_resp_send(req, message, strlen(message));
    return ESP_OK;
}

static esp_err_t on_right(httpd_req_t *req)
{
    driverTurnRight();
    char *message = "{\"right\": \"ok\"}";
    httpd_resp_send(req, message, strlen(message));
    return ESP_OK;
}

static esp_err_t on_stop(httpd_req_t *req)
{
    driverStop();
    char *message = "{\"stop\": \"ok\"}";
    httpd_resp_send(req, message, strlen(message));
    return ESP_OK;
}

static esp_err_t on_led(httpd_req_t *req)
{
    ledToggle();
    char *message = "{\"led\": \"ok\"}";
    httpd_resp_send(req, message, strlen(message));
    return ESP_OK;
}

void serverStart(void)
{
    httpd_handle_t server = NULL;
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();
    config.uri_match_fn = httpd_uri_match_wildcard;

    ESP_LOGI(TAG, "starting server");
    if (httpd_start(&server, &config) != ESP_OK)
    {
        ESP_LOGE(TAG, "failed to start http server");
    }

    httpd_handle_t video_server = NULL;
    httpd_config_t video_server_config = HTTPD_DEFAULT_CONFIG();
    video_server_config.task_priority = tskIDLE_PRIORITY + 4;
    video_server_config.server_port = 81;
    video_server_config.ctrl_port = 32769;

    ESP_LOGI(TAG, "starting video server");
    if (httpd_start(&video_server, &video_server_config) != ESP_OK)
    {
        ESP_LOGE(TAG, "failed to start http video server");
    }

    httpd_uri_t straight_end_point_config = {
        .uri = "/straight",
        .method = HTTP_POST,
        .handler = on_straight};

    httpd_uri_t back_end_point_config = {
        .uri = "/back",
        .method = HTTP_POST,
        .handler = on_back};

    httpd_uri_t left_end_point_config = {
        .uri = "/left",
        .method = HTTP_POST,
        .handler = on_left};

    httpd_uri_t right_end_point_config = {
        .uri = "/right",
        .method = HTTP_POST,
        .handler = on_right};

    httpd_uri_t stop_end_point_config = {
        .uri = "/stop",
        .method = HTTP_POST,
        .handler = on_stop};

    httpd_uri_t led_end_point_config = {
        .uri = "/led",
        .method = HTTP_POST,
        .handler = on_led};

    httpd_uri_t camera_end_point_config = {
        .uri = "/camera",
        .method = HTTP_GET,
        .handler = video_jpg_stream_httpd_handler};

    httpd_uri_t first_end_point_config = {
        .uri = "/*",
        .method = HTTP_GET,
        .handler = on_url_hit};

    httpd_register_uri_handler(server, &straight_end_point_config);
    httpd_register_uri_handler(server, &back_end_point_config);
    httpd_register_uri_handler(server, &left_end_point_config);
    httpd_register_uri_handler(server, &right_end_point_config);
    httpd_register_uri_handler(server, &stop_end_point_config);
    httpd_register_uri_handler(server, &led_end_point_config);
    httpd_register_uri_handler(server, &first_end_point_config);

    httpd_register_uri_handler(video_server, &camera_end_point_config);

    // indicate wifi is on
    ledToggle();
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    ledToggle();
}