#include <Wire.h>
#include <math.h>

#define ADC_REF 5 //reference voltage of ADC is 5v.If the Vcc switch on the seeeduino
#define FULL_ANGLE 1023 //full value of the rotary angle is 300 degrees
#define GROVE_VCC 5 //VCC of the grove interface is normally 5v
#define THERMISTOR 4275
const int R0 = 100000;
#define TEMPERATURE_POTAR A1
const int TEMPERATURE_SENSOR = A0;


void setup()
{
    Serial1.begin(9600);
}

void loop()
{
    //--- Température Consigne ---//
    float voltage;
    int sensor_value = analogRead(TEMPERATURE_POTAR);
    voltage = (float)sensor_value * 5 / 1023;
    float degrees = (voltage * FULL_ANGLE) / 5;
    float temp_cons_value = int(degrees / 20.25) * 0.5 + 5;
    
    //--- Capteur Température ---//
    int a = analogRead(TEMPERATURE_SENSOR);

    float R = 1023.0/a-1.0;
    R = R0*R;

    float temperature_value = 1.0/(log(R/R0)/THERMISTOR+1/298.15)-273.15; 

    //--- Affichage ---//
    Serial.print("Température Consigne: ");
    Serial.println(temp_cons_value);
    Serial.print("Capteur Température: ");
    Serial.println(temperature_value);
    
    delay(1000);
}
