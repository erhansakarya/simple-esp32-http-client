#include <stdio.h>
#include "esp_wifi.h"
#include "esp_event.h"
#include "nvs_flash.h"
#include "esp_http_client.h"
#include "protocol_examples_common.h"

esp_err_t clientEventCallback(esp_http_client_event_t *event) {
    switch(event->event_id) {
    case HTTP_EVENT_ON_DATA:
        printf("data: %s\n", (char *)event->data);
        break;
    default:
        break;
    }
    return ESP_OK;
}

void app_main(void)
{
    nvs_flash_init();
    tcpip_adapter_init();
    esp_event_loop_create_default();
    example_connect();

    esp_http_client_config_t clientConfig = {
        .url = "http://erhansakarya.com",
        .event_handler = clientEventCallback
    };
    esp_http_client_handle_t clientHandler = esp_http_client_init(&clientConfig);
    esp_http_client_perform(clientHandler);
    esp_http_client_cleanup(clientHandler);
}
