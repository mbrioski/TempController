const int SENSOR_TEMP = A0;
const float CONFORT_TEMP = 24.0;
const float TEMP_TOLERANCE_MID = 1.0;
const float TEMP_TOLERANCE_HIGH = 2.0;
const int LED_TEMP_OK = 2;
const int LED_TEMP_WARN = 3;
const int LED_TEMP_KO = 4;
const int CHECK_TIME = 5000;
                                                                                                                             
void setup() {
  Serial.begin(9600);
  pinMode(LED_TEMP_OK, OUTPUT);
  pinMode(LED_TEMP_KO, OUTPUT);
  digitalWrite(LED_TEMP_KO, LOW);
  digitalWrite(LED_TEMP_WARN, LOW);
  digitalWrite(LED_TEMP_OK, LOW);
  
}

void loop() {
 int sensorVal = analogRead(SENSOR_TEMP);
 float voltage = getVoltage(sensorVal);
 float temperature = getTemperature(voltage);
 if(temperature > CONFORT_TEMP + TEMP_TOLERANCE_HIGH || temperature < CONFORT_TEMP - TEMP_TOLERANCE_HIGH) {
    digitalWrite(LED_TEMP_KO, HIGH);
    digitalWrite(LED_TEMP_WARN, LOW);
    digitalWrite(LED_TEMP_OK, LOW);
 }else if(temperature > CONFORT_TEMP + TEMP_TOLERANCE_MID || temperature < CONFORT_TEMP - TEMP_TOLERANCE_MID) {
  Serial.println("WARNING");
    digitalWrite(LED_TEMP_KO, LOW);
    digitalWrite(LED_TEMP_WARN, HIGH);
    digitalWrite(LED_TEMP_OK, LOW);
 }else {
   digitalWrite(LED_TEMP_KO, LOW);
   digitalWrite(LED_TEMP_WARN, LOW);
   digitalWrite(LED_TEMP_OK, HIGH);
 }
 printOutput(sensorVal, voltage, temperature);
 delay(CHECK_TIME);
}
/**
 * Write output to serial
 */
void printOutput(int sensorVal, float voltage, float temperature) {
 Serial.print("Sensor Value: ");
 Serial.print(sensorVal);
 Serial.print(", Voltage: ");
 Serial.print(voltage);
 Serial.print(", Temparature: ");
 Serial.println(temperature);
}

/**
 * Get voltage from sensor value
 */
float getVoltage(float value) {
  return (value/1024.0) * 5.0;
}
/**
 * Get temperature from voltage
 */
float getTemperature(float voltage) {
  return (voltage - 0.5) * 100;
}
