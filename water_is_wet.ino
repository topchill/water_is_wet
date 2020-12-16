/*
* Project water_is_wet
* Description: water quality tester
* Author: Vincent Milot and Jordan côté
* Date: 9/21/2020
*/
// Command-Shift-P on the Mac, 
// Ctrl-Shift-P on Windows and Linux
// Select Particle: Serial Monitor.
//https://circuitdigest.com/microcontroller-projects/arduino-ph-meter

#include <Arduino.h>
double ph_act = 0;
int temperatureC = 0; 
double turbidityVoltage = 0;
double tdsValue = 0;


float calibration_value = 21.34;
int phval = 0; 
unsigned long int avgval; 
int buffer_arr[10],temp;
const int temperatureSense = A5;

#define sensorPin A2
 
int sensorValue = 0;
float Voltage = 0;

void setup() {
	Serial.begin(9600);
	Particle.variable("temperature", temperatureC);
	Particle.variable("phValue", ph_act);
	Particle.variable("TDS", tdsValue);
	Particle.variable("turbidityValue", turbidityVoltage);
	delay(1000);
}



void loop() {
	phLoop();
	temperatureLoop();
	turbuditySensor();
	tdsSensor();
	particlePublish();
	delay(5000);
	/*------------------------------*/
}

void phLoop() {
	for (int i=0;i<10;i++) { 
		buffer_arr[i]=analogRead(A0);
		delay(30);
	}
	for (int i = 0;i < 9; i++) {
		for (int j = i + 1; j < 10; j++) {
			if (buffer_arr[i] > buffer_arr[j]){
				temp = buffer_arr[i];
				buffer_arr[i]=buffer_arr[j];
				buffer_arr[j]=temp;
			}
		}
	}
	avgval=0;
	for (int i=2;i<8;i++)
	avgval+=buffer_arr[i];
	float volt=(float)avgval*5.0/1024/6;
	ph_act = -5.70 * volt + calibration_value;
	Serial.print("ph = ");
	Serial.println(ph_act);
}

void temperatureLoop() {
	int temp = 0;
	if (temp == 0) {
		int temperatureF;

		int analogTemp;
		analogTemp = analogRead(temperatureSense);
		temperatureF = (analogTemp - 1000) / 3.85;
		temperatureC = (temperatureF - 32) * 5/9;
		Serial.print("temperature = ");
		Serial.println(temperatureC);
		temp++;
	}
}

void turbuditySensor() {
	int sensorValue = analogRead(A4);
	turbidityVoltage = sensorValue * (5.0 / 1024.0);
	
	Serial.print("Sensor Output (V):");
	Serial.println(turbidityVoltage);
}

void tdsSensor() {
    sensorValue = analogRead(sensorPin);
    Voltage = sensorValue*5/1024.0; //Convert analog reading to Voltage
    tdsValue = (133.42 * Voltage * Voltage * Voltage - 255.86 * Voltage * Voltage + 857.39 * Voltage)*0.5; //Convert voltage value to TDS value
    Serial.print("TDS Value = "); 
    Serial.print(tdsValue);
    Serial.println(" ppm");
   
}

int getMedianNum(int bArray[], int iFilterLen) {
	int bTab[iFilterLen];
	for (byte i = 0; i < iFilterLen; i++)
		bTab[i] = bArray[i];
	int i, j, bTemp;
	for (j = 0; j < iFilterLen - 1; j++) {
		for (i = 0; i < iFilterLen - j - 1; i++) {
			if (bTab[i] > bTab[i + 1]) {
				bTemp = bTab[i];
					bTab[i] = bTab[i + 1];
				bTab[i + 1] = bTemp;
			}
		}
	}
	if ((iFilterLen & 1) > 0) {
		bTemp = bTab[(iFilterLen - 1) / 2];
	} else {
		bTemp = (bTab[iFilterLen / 2] + bTab[iFilterLen / 2 - 1]) / 2;
	}
	return bTemp;
}

void particlePublish() {
	String temps = String(ceil(temperatureC));
	String phs = String(ceil(ph_act));
	String TDSS = String(ceil(tdsValue));
	String turbidityValS = String(ceil(turbidityVoltage));

	Serial.print(ceil(tdsValue));

	Particle.publish("GoogleSendTemps", temps, PRIVATE);
	Particle.publish("GoogleSendPh", phs, PRIVATE);
	Particle.publish("GoogleSendTDS", TDSS, PRIVATE);
	Particle.publish("GoogleSendTurbidity", turbidityValS, PRIVATE);
}
