#include <Wire.h>
#include "rgb_lcd.h"
#include <math.h>

#define ADC_REF 5 //reference voltage of ADC is 5v.If the Vcc switch on the seeeduino
#define FULL_ANGLE 1023 //full value of the rotary angle is 300 degrees
#define GROVE_VCC 5 //VCC of the grove interface is normally 5v
#define THERMISTOR 4275
const int R0 = 100000;
#define TEMPERATURE_POTAR A1
const int TEMPERATURE_SENSOR = A0;

rgb_lcd lcd;

void setup()
{
    Serial1.begin(9600);
    lcd.begin(16, 2);
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

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Temp:");
    lcd.print(temperature_value, 2); 
    lcd.print((char)223);
    lcd.print("C");
    lcd.setCursor(0, 1);
    lcd.print("Cons:");
    lcd.print(temp_cons_value, 1);
    lcd.print((char)223);
    lcd.print("C");

    if(temp_cons_value >= temperature_value - 0.5 && temp_cons_value <= temperature_value + 0.5){
        Serial.println("Vert");
        lcd.setRGB(0, 255, 0); // Green color
    } else if (temperature_value < temp_cons_value) {
        Serial.println("Bleu");
        lcd.setRGB(0, 0, 255); // Blue color
    } else if (temperature_value > temp_cons_value) {
        Serial.println("Red");
        lcd.setRGB(255, 0, 0); // Red color
    }
    
    delay(1000);
}
