/* 
 * This example sends data from an Adafruit-compatible BMP280 
 * temperature and pressure sensor (located in the engine room)
 * to a Signal K Server. Comments here in the program file are
 * minimal - for a full explanation, see
 * https://github.com/SignalK/SensESP/pages/tutorials/bmp280
 * 
 * Here's the sensor: https://www.adafruit.com/product/2651
 *
 * NOTE: Use this as a template for almost any other Arduino-compatible
 * physical sensor.
*/

// Boilerplate #includes:
#include "sensesp_app_builder.h"
#include "sensesp/signalk/signalk_output.h"

// Sensor-specific #includes:
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <Wire.h>
// For RepeatSensor:
#include "sensesp/sensors/sensor.h"

#define DHTPIN 23     // Digital pin connected to the DHT sensor note that only certain GPIO #'s are useable!

using namespace sensesp;

// SensESP builds upon the ReactESP framework. Every ReactESP application
// must instantiate the "app" object.
reactesp::ReactESP app;

// Uncomment whatever type you're using!
#define DHTTYPE DHT11   // DHT 11
//#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

// Connect pin 1 (on the left) of the sensor to +5V
// NOTE: If using a board with 3.3V logic like an Arduino Due connect pin 1
// to 3.3V instead of 5V!
// Connect pin 2 of the sensor to whatever your DHTPIN is
// Connect pin 3 (on the right) of the sensor to GROUND (if your sensor has 3 pins)
// Connect pin 4 (on the right) of the sensor to GROUND and leave the pin 3 EMPTY (if your sensor has 4 pins)
// Connect a 10K resistor from pin 2 (data) to pin 1 (power) of the sensor

// Initialize DHT sensor.
// Note that older versions of this library took an optional third parameter to
// tweak the timings for faster processors.  This parameter is no longer needed
// as the current DHT reading algorithm adjusts itself to work on faster procs.
DHT dht(DHTPIN, DHTTYPE);

// (Replace this with whatever function you need to read whatever value you want
// to read from any other sensor you're using in your project.)
// Define the function that will be called every time we want
// an updated temperature value from the sensor. The sensor reads degrees
// Celsius, but all temps in Signal K are in Kelvin, so add 273.15.

float read_temp_callback() { return (dht.readTemperature() + 273.15); }
float read_humidity_callback() { return (dht.readHumidity()); }


uint32_t delayMS;
// The setup function performs one-time application initialization
void setup() {


// Some initialization boilerplate when in debug mode
#ifndef SERIAL_DEBUG_DISABLED
  SetupSerialDebug(115200);
#endif
  // Construct the global SensESPApp() object
  SensESPAppBuilder builder;
  sensesp_app = (&builder)
                    // Set a custom hostname for the app.
                    ->set_hostname("my-sensesp-DHTxx")
                    // Optionally, hard-code the WiFi and Signal K server
                    // settings. This is normally not needed.
                    ->set_wifi("Your_Wifi", "Your_Wifi_pwd")
                    ->set_sk_server("SK IP", SK Port)
                    ->get_app();
 

  // (Do whatever is required to "start" your project's sensor here)
  // Initialize the DHTxx device using the default address
 dht.begin();

  // Read the sensor every 2 seconds
  unsigned int read_interval = 1000;

  // Create a RepeatSensor with float output that reads the temperature
  // using the function defined above.
  auto* engine_room_temp =
      new RepeatSensor<float>(read_interval, read_temp_callback);

  // Set the Signal K Path for the output
  const char* sk_path1 = "propulsion.engineRoom.temperature";

    auto* engine_room_relativehumidity =
      new RepeatSensor<float>(read_interval, read_humidity_callback);

  // Set the Signal K Path for the output
  const char* sk_path2 = "propulsion.engineRoom.humidity";

  // Send the temperature to the Signal K server as a Float
  engine_room_temp->connect_to(new SKOutputFloat(sk_path1));
  engine_room_relativehumidity->connect_to(new SKOutputFloat(sk_path2));

  // Start the SensESP application running
  sensesp_app->start();

}

// loop simply calls `app.tick()` which will then execute all reactions as needed
void loop() {
  
  app.tick();
  
}
