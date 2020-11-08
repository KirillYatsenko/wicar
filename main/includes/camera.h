#ifndef CAMERA_H
#define CAMERA_H

#include "esp_http_server.h"

esp_err_t video_jpg_stream_httpd_handler(httpd_req_t *req);

#endif