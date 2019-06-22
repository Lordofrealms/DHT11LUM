#include "DHT11LUM.h"


DHT11LUM::DHT11LUM(int pin, void (*isr_wrapper)()) {
	init(pin);
	this->isr_wrapper=isr_wrapper;
	getdata();
}

DHT11LUM::DHT11LUM(int pin, void (*isr_wrapper)(), bool overrideinitialpoll) {
	init(pin);
	this->isr_wrapper=isr_wrapper;
}

void DHT11LUM::isr() {
	status = digitalRead(pin);
	timediff = micros() - lastpinchange;
	lastpinchange = micros();
	if(status == 0)
		{
			if(timediff < lowthreshold)
				{
					dhtin = dhtin + "0";
				}
			else if(timediff > highthreshold)
				{
					dhtin = dhtin + "1";
				}
		}
}

void DHT11LUM::getdata() {
	while(millis() < waitmillis + lastpollmillis)
		{
			delay(10);
		}
	timediff = 0;
	dhtin = "";
	pinMode(pin,OUTPUT);
	timevar = micros();
	digitalWrite(pin,LOW);
	while(timediff < pollthreshold)
		{
			timediff = micros() - timevar;
		}
	digitalWrite(pin,HIGH);
	pinMode(pin,INPUT);
	attachInterrupt(pininterrupt,isr_wrapper,CHANGE);
	lastpinchange = micros();
	while((dhtin.length()) < 42)
		{
			delay(10);
		}
	lastpollmillis = millis();
	rhhigh = strtol(dhtin.substring(2,10).c_str(),NULL,2);
	rhlow = strtol(dhtin.substring(10,18).c_str(),NULL,2);
	temphigh = strtol(dhtin.substring(18,26).c_str(),NULL,2);
	templow = strtol(dhtin.substring(26,34).c_str(),NULL,2);
	cs = strtol(dhtin.substring(34,42).c_str(),NULL,2);
	cscalc = (strtol(dhtin.substring(2,10).c_str(),NULL,2)+strtol(dhtin.substring(10,18).c_str(),NULL,2)+strtol(dhtin.substring(18,26).c_str(),NULL,2)+strtol(dhtin.substring(26,34).c_str(),NULL,2)) % 256;
	if(cs == cscalc)
		{
			tempc = (String(strtol(dhtin.substring(18,26).c_str(),NULL,2))+"."+String(strtol(dhtin.substring(26,34).c_str(),NULL,2))).toFloat();
			tempf = tempc * 9/5 + 32;
			tempk = tempc + 273.15;
			rh = (String(strtol(dhtin.substring(2,10).c_str(),NULL,2))+"."+String(strtol(dhtin.substring(10,18).c_str(),NULL,2))).toFloat();
		}
	else
		{
			tempc = sqrt(-1.00);
			tempf = sqrt(-1.00);
			tempk = sqrt(-1.00);
			rh = sqrt(-1.00);
		}
}

void DHT11LUM::init(int pin) {
	this->pin = pin;
	this->pininterrupt = digitalPinToInterrupt(pin);
}

float DHT11LUM::gettempc() {
	if(automaticupdates)
		{
			if((millis() > waitmillis + lastpollmillis) || forceupdatewait)
				{ 
					getdata();
				}
		}
	return tempc;	
}

float DHT11LUM::gettempf() {
	if(automaticupdates)
		{
			if((millis() > waitmillis + lastpollmillis) || forceupdatewait)
				{ 
					getdata();
				}
		}
	return tempf;	
}

float DHT11LUM::gettempk() {
	if(automaticupdates)
		{
			if((millis() > waitmillis + lastpollmillis) || forceupdatewait)
				{ 
					getdata();
				}
		}
	return tempk;	
}

float DHT11LUM::getrh() {
	if(automaticupdates)
		{
			if((millis() > waitmillis + lastpollmillis) || forceupdatewait)
				{ 
					getdata();
				}
		}
	return rh;	
}