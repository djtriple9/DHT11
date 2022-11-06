; PlatformIO Project Configuration File
;
;   Build options: build flags, source filter
;   Upload options: custom upload port, speed and extra flags
;   Library options: dependencies, extra library storages
;   Advanced options: extra scripting
;
; Please visit documentation for the other options and examples
; https://docs.platformio.org/page/projectconf.html

; This is the platformio.ini file to be used with the BMP280 
; Tutorial / example.

[platformio]
; set default_envs to whichever board(s) you use. Build/Run/etc processes those envs
default_envs = 
;   esp32dev

[env]
; Global data for all [env:***]
framework = arduino
lib_ldf_mode = deep
monitor_speed = 115200
lib_deps =
  SignalK/SensESP @ ^2.6.0
  adafruit/DHT sensor library @ ^1.4.4
  adafruit/Adafruit Unified Sensor @ ^1.1.6

[espressif32_base]
;this section has config items common to all ESP32 boards
platform = espressif32
build_unflags =
  -Werror=reorder
board_build.partitions = min_spiffs.csv
monitor_filters = esp32_exception_decoder

[env:esp32dev]
extends = espressif32_base
board = esp32dev
build_flags =
  -D LED_BUILTIN=2
  ; Uncomment the following to disable debug output altogether
  ;-D DEBUG_DISABLED
  ; Uncomment the following to enable the remote debug telnet interface on port 23
  ;-D REMOTE_DEBUG

;; Uncomment and change these if PlatformIO can't auto-detect the ports
;upload_port = /dev/tty.SLAB_USBtoUART
;monitor_port = /dev/tty.SLAB_USBtoUART
