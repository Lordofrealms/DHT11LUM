#ifndef DHT11LUM_h
#define DHT11LUM_h

#if defined(ARDUINO) && (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

class DHT11LUM
{
private:
	void init(int pin);
	void (*isr_wrapper)(void);
	int pin;
	int pininterrupt;
	bool status;
	unsigned long timevar;
	unsigned long timediff = 0;
	unsigned long lastpinchange = 0;
	String dhtin;
	int rhhigh = 0;
	int rhlow = 0;
	int temphigh = 0;
	int templow = 0;
	int cs = 0;
	int cscalc = 0;
	unsigned long lastpollmillis = 0; //last time an update poll occurred, allows unblocking status queries
	unsigned long waitmillis = 1200; //minimum time to wait between polling for update
	unsigned long lowthreshold = 40; //maximum microseconds to consider bit a 0
	unsigned long highthreshold = 60; //minimum microseoncds to consider bit a 1
	unsigned long pollthreshold = 20000; //time to pull data pin low to trigger DHT11 to start a new poll
	float tempc = 0.0;
	float tempf = 0.0;
	float tempk = 0.0;
	float rh = 0.0;
public:
	//declarations
	DHT11LUM(int pin, void (*isr_wrapper)());
	DHT11LUM(int pin, void (*isr_wrapper)(), bool overrideinitialpoll); // use this initialization if the user's program cannot tolerate the 1.2s initial polling delay -- note the bool value doesn't matter and isn't checked
	
	//internal functions, getdate() only needing if using manual polling -- see options section
	void isr();
	void getdata();

	//options
	bool forceupdatewait = false; //library will auto poll if enough time has elapsed since last poll to get updated data, but set this to true in the setup function to force the library to wait for an update each time a value is requested; 
	bool automaticupdates = true; //change to false to require manual calling of the getdate() function to update temp and humidity values -- recommend leaving set to true unless there is a need to know specifically when the temp and humidity was last updated

	//user functions
	float gettempc();
	float gettempf();
	float gettempk();
	float getrh();
};

#endif