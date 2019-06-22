#include <DHT11LUM.h>

int DHT11pin = 2; //Digital pin for comunications

// have to declare here to allow proper setup of dht object then redefine to dht object ISR after object is created
void dht_wrapper();

DHT11LUM dht = DHT11LUM(DHT11pin,dht_wrapper);

void dht_wrapper()
  {
    dht.isr();
  }

void setup()
{
  Serial.begin(115200);
  //dht.forceupdatewait = true;
  //dht.automaticupdates = false;
}

void loop()
{
  Serial.println(dht.gettempc());
  Serial.println(dht.gettempf());
  Serial.println(dht.gettempk());
  Serial.println(dht.getrh());
}

