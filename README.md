# DHT11LUM
Interrupt driven library for DHT11 Temp and Humidity Sensors

If anyone wants this library to work with DHT22 and/or verification with ESP processors I would like to test, but isn't needed for my projects; if anyone would like to donate to make that happen please PM me.

This library specifically written to deal with high speed MCs and their interactions with the DHT11. This library doesn't support DHT22, but should shortly. This library requires the DHT11 data pin to be on an interrupt enabled pin. This library is for higher speed MCs which typically have all digital IO pins interrupt enabled.

The library has two significant options. It is recommended that the defaults are used for the largest ease of use.

If the system requires more precise control. These options provide it.

bool forceupdatewait = false; //library will auto poll if enough time has elapsed since last poll to get updated data, but set this to true in the setup function to force the library to wait for an update each time a value is requested. This will force up to a 1.2s blocking wait during polling.

bool automaticupdates = true; //change to false to require manual calling of the getdate() function to update temp and humidity values -- recommend leaving set to true unless there is a need to know specifically when the temp and humidity was last updated.

Look at the example for more information on using this library.
