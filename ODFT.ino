/*
 * Author: Luke Carlson
 * Temperature and Light Module Testing
 */
 
double temperatureC = 0.0;
double photo = 0.0;
double brightC = 0.0;
double baseTemp = 0.0;
double baseBright = 0.0;

int temperaturePin = A0;
int yellowLED = D0;
int redLED = D1;
int internalLED = D7;
int switchy = D2;
//====================================

//1.A: Find the variable of tempature
void flashLED(int pin, int time){
  digitalWrite(pin,HIGH);
  delay(time);
  digitalWrite(pin,LOW);
  delay(time);
}
// returns temperature
double gatherTemperature(){
  double voltage = analogRead(temperaturePin)/4095.0 * 3.3; // measure temperature
  return 104.7*voltage - 53.1;
}
double gatherBrightness() {
  return analogRead(photo);
}
void setup() {
    pinMode(A0, INPUT_PULLUP);
    pinMode(switchy, INPUT_PULLUP);
    //Serial.begin(9600);
    pinMode(yellowLED, OUTPUT);
    pinMode(internalLED, OUTPUT);
    pinMode(temperaturePin, AN_INPUT);
    pinMode(yellowLED,OUTPUT);
    //Particle.function("hello", sayHello);
    //Particle.variable("temper", temperatureC);
    baseTemp = gatherTemperature();
    baseBright = gatherBrightness();
}
void loop() {
    temperatureC = gatherTemperature();       //prints temp
    brightC = gatherBrightness();
    //Serial.printlnf("Temperature: %.2f", temperatureC);
    //======================================================================
    //1.B Find brightness
    //======================================================================
    //2. On switch press --> BV = CV AND LED flash 5 times
    if(digitalRead(switchy) == LOW) { //When switch is pressed
        baseTemp = gatherTemperature();
        baseBright = gatherBrightness();
        for(int i=5; i>1; i--){ //loop 5 times
          flashLED(internalLED, 1000);
          }
      }
    //======================================================================
//if statement for redLED
    if(temperatureC - baseTemp > 2) {
      analogWrite(redLED, 255);
    }
    else {
      analogWrite(redLED, 0);
    }
    //if statement for yellowLED
    if(brightC/baseBright < 0.50) {
      analogWrite(yellowLED, 191);
    }
    else {
      analogWrite(yellowLED, 0);
    }
}

//3. If CT > BV increase redLED brightess
