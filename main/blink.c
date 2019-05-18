#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/gpio.h"
#include "esp_log.h"

QueueHandle_t ledQueue;             //キュー制御用ハンドル
static const char *TAG = "MAIN";    //ESP_LOGIとかやるときの出力につけるヘッダ

/*  LED状態リスト   */
typedef enum ledTaskArg_t
{
    LED_NONE = 0,   //何もしない予定
    LED_ON = 1,
    LED_OFF = 2
}ledTaskArg_t;

/*  点滅制御キューを送信    */
static void sendQueueTask (void *pvParameters)
{
    BaseType_t xStatus;
    int32_t SendValue = LED_ON;

    while (1)
    {
        xStatus = xQueueSend(ledQueue, &SendValue, 0);  //キュー送信
        if(xStatus != pdPASS) //キュー通ったかチェック
        {
            ESP_LOGE(TAG, "Queue send error");
        }
        /*  ON/OFF切り替え  */
        if(SendValue == LED_ON) SendValue = LED_OFF;
        else                SendValue = LED_ON;
        vTaskDelay(1000 / portTICK_PERIOD_MS);  //1sec待つ
    }
}

/*  GPIOを制御するタスク。キューを受信して実際に点滅させる    */
static void blinkTask(void *pvParameters)
{
    /* 出力ピンの設定 */
    gpio_config_t io_conf;    //GPIOピンのコンフィグ変数
    io_conf.pin_bit_mask = (1ULL<<5);    //この設定は5番に適用するというビットマスク
    io_conf.intr_type = GPIO_PIN_INTR_DISABLE;    //割り込みを無効化
    io_conf.mode = GPIO_MODE_OUTPUT;    //出力に設定
    io_conf.pull_down_en = 0;    //プルダウンをオフ
    io_conf.pull_up_en = 0;    //プルアップをオフ
    gpio_config(&io_conf);    //設定を適用

    BaseType_t xStatus;
    int ReceivedValue = 0;
    while (1)
    {
        //キュー受信。受け取るまで portMAX_DELAY:無限に待つ
        xStatus = xQueueReceive(ledQueue, &ReceivedValue, portMAX_DELAY);
        if(xStatus == pdPASS)   //キュー受け取ったら
        {
            ESP_LOGI(TAG, "received: %d", ReceivedValue);
            /*  キューの引数によってピンを駆動  */
            switch(ReceivedValue)
            {
                case LED_ON:
                    gpio_set_level(5, true);
                    break;
                case LED_OFF:
                    gpio_set_level(5, false);
                    break;
                default:
                    break;
            }
        }
    }
}

void app_main()
{
    ledQueue = xQueueCreate(1, sizeof(int));  //キューハンドル初期化

    if(ledQueue != NULL)
    {
        //キュー送信タスク開始
        xTaskCreate(sendQueueTask, "sendQueueTask", 4096, NULL, 1, (TaskHandle_t *) NULL);
        //キュー受信タスク開始
        xTaskCreate(blinkTask, "blinkTask", 4096, NULL, 2, (TaskHandle_t *) NULL);
    }
    else
    {
        ESP_LOGE(TAG, "Queue create failed");
        while(1)
        {
            vTaskDelay(1000 / portTICK_PERIOD_MS);
        }
    }
}