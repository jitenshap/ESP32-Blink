deps_config := \
	/home/ubuntu/esp/esp-idf/components/app_trace/Kconfig \
	/home/ubuntu/esp/esp-idf/components/aws_iot/Kconfig \
	/home/ubuntu/esp/esp-idf/components/bt/Kconfig \
	/home/ubuntu/esp/esp-idf/components/esp32/Kconfig \
	/home/ubuntu/esp/esp-idf/components/esp_adc_cal/Kconfig \
	/home/ubuntu/esp/esp-idf/components/ethernet/Kconfig \
	/home/ubuntu/esp/esp-idf/components/fatfs/Kconfig \
	/home/ubuntu/esp/esp-idf/components/freertos/Kconfig \
	/home/ubuntu/esp/esp-idf/components/heap/Kconfig \
	/home/ubuntu/esp/esp-idf/components/libsodium/Kconfig \
	/home/ubuntu/esp/esp-idf/components/log/Kconfig \
	/home/ubuntu/esp/esp-idf/components/lwip/Kconfig \
	/home/ubuntu/esp/esp-idf/components/mbedtls/Kconfig \
	/home/ubuntu/esp/esp-idf/components/openssl/Kconfig \
	/home/ubuntu/esp/esp-idf/components/pthread/Kconfig \
	/home/ubuntu/esp/esp-idf/components/spi_flash/Kconfig \
	/home/ubuntu/esp/esp-idf/components/spiffs/Kconfig \
	/home/ubuntu/esp/esp-idf/components/tcpip_adapter/Kconfig \
	/home/ubuntu/esp/esp-idf/components/wear_levelling/Kconfig \
	/home/ubuntu/esp/esp-idf/components/bootloader/Kconfig.projbuild \
	/home/ubuntu/esp/esp-idf/components/esptool_py/Kconfig.projbuild \
	/home/ubuntu/esp/esp-idf/components/partition_table/Kconfig.projbuild \
	/home/ubuntu/esp/esp-idf/Kconfig

include/config/auto.conf: \
	$(deps_config)


$(deps_config): ;
