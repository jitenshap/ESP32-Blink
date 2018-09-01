#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"


void app_main()
{
    /* 出力ピンの設定 */
    //GPIOピンのコンフィグ変数
    gpio_config_t io_conf;
    //この設定は2番に適用するというビットマスク
    io_conf.pin_bit_mask = (1ULL<<2);
    //割り込みを無効化
    io_conf.intr_type = GPIO_PIN_INTR_DISABLE;
    //出力に設定
    io_conf.mode = GPIO_MODE_OUTPUT;
    //プルダウンをオフ
    io_conf.pull_down_en = 0;
    //プルアップをオフ
    io_conf.pull_up_en = 0;
    //設定を適用
    gpio_config(&io_conf);


    bool toggle=true;
    /*ループ*/
    while(1) 
    {        
        gpio_set_level(2, toggle);
	toggle = !toggle;
        //1000ms待機
        vTaskDelay(1000 / portTICK_RATE_MS);
    }
}

