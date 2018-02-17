#include <DHT.h>
#include <DHT_U.h>


#include <OneWire.h> 
#include <DallasTemperature.h>

#include <RCSwitch.h>
#include <FastCRC.h>


/* Water temperature sensor */
#define ONE_WIRE_BUS 8 // d8

OneWire oneWire(ONE_WIRE_BUS); 
DallasTemperature sensors(&oneWire);

/* rel humidity and air temp sensor */
#define DHTPIN 3 // d3
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

/* 433 mHz transmitter */
#define TRANSMITTER_PIN 13
RCSwitch rcSwitch;
FastCRC8 crc8;

/**
 * Possible protocol:
 * Fixed size message, and one transmission per sensor-value.
 * 1 byte   id of the sensornode
 * 2 byte   key of the measurement (temperature, humidity, ...?)
 * 4 byte   float, the actual measurement.
 * 1 byte   checksum, CRC8 of the rest of the message
 */
typedef struct __attribute__ ((packed))
{
  byte sensorId;
  char key[2];
  float value;
  byte crc;
} SensorMsg_t;


SensorMsg_t messageWaterTmp, messageAirTmp, messageHumidity;

void setup(void) 
{ 
 const int sid = 123; // TODO
 messageWaterTmp.sensorId = sid;
 strncpy(messageWaterTmp.key, "tw", 2);
 messageAirTmp.sensorId = sid;
 strncpy(messageAirTmp.key, "ta", 2);
 messageHumidity.sensorId = sid;
 strncpy(messageHumidity.key, "rh", 2);

 Serial.begin(9600); 
 Serial.println("Dallas Temperature IC Control Library Demo"); 
 sensors.begin(); 
 dht.begin();
 delay(2000);

 rcSwitch.enableTransmit(TRANSMITTER_PIN);
 rcSwitch.setRepeatTransmit(4);
} 


void sendMessage(SensorMsg_t* msg)
{
  // split into 2 * 32 bit
  int32_t* ptr = (int32_t*) msg;
  Serial.print( "sending: " ); Serial.println( *ptr );
  rcSwitch.send(*ptr, 32);
  
  Serial.print( "sending: " ); Serial.println( *(ptr+1) );
  rcSwitch.send(*(ptr+1), 32);
}


void loop(void) 
{
  //Serial.print(" Requesting temperatures..."); 
  sensors.requestTemperatures(); // Send the command to get temperature readings
  float waterTmp = sensors.getTempCByIndex(0);
  
  Serial.print("water temp: ");
  Serial.print(waterTmp); // Why "byIndex"?  
  Serial.print("°C ");
  
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();
  Serial.print("rel hum: "); Serial.print(humidity); Serial.print("%, temp: "); Serial.print(temperature); Serial.println("°C");

  // fill messages
  messageWaterTmp.value = waterTmp;
  messageAirTmp.value = temperature;
  messageHumidity.value = humidity;

  // crc8
  messageWaterTmp.crc = crc8.smbus((uint8_t*) &messageWaterTmp, sizeof(SensorMsg_t)-1);
  messageAirTmp.crc = crc8.smbus((uint8_t*) &messageAirTmp, sizeof(SensorMsg_t)-1);
  messageHumidity.crc = crc8.smbus((uint8_t*) &messageHumidity, sizeof(SensorMsg_t)-1);

  // send
  sendMessage(&messageWaterTmp);
  sendMessage(&messageAirTmp);
  sendMessage(&messageHumidity);
  
  delay(1000);
} 
