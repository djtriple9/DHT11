# DHTxx
Designed to make use of the DHT11/21/22 sensors for SensESP (support version SignalK v1.45 as of this writing).  Just comment out the sensors you aren't using and and uncomment the one that you are.  Don't forget to set it to the pin you want to use!  Yes you can use multiple sensors on one board if you want, just add the sensor variable as defined in the adafruit dht sensor library and add ".sensor(x)" to you variables, also numbering said variables.

Also, please disconnect the sensor from your ESP board during upload.  failure to so so will get you upload errors and/or corruption.  You have been warned.

file bugs and requests here; I might fix them; I might not.

DJ Triple9
