int analogPin1 = A0;                   
int analogPin2 = A1;
int LED_PIN_R = 9;
int LED_PIN_G = 10;
int LED_PIN_B = 11;
unsigned long delayStart = 0;
unsigned long DELAY_TIME = 20000; // 1.5 sec
float voltage = 0;
bool delayRunning = false;
bool led_condition=false;
bool detection=false;
bool monitor=false;
bool timeractive=false;

void setup() {

  Serial.begin(9600);           //  setup serial
  pinMode(LED_PIN_R, OUTPUT);   // initialize the digital pin as an output.
  pinMode(LED_PIN_G, OUTPUT);   // initialize the digital pin as an output.
  pinMode(LED_PIN_B, OUTPUT);   // initialize the digital pin as an output.
  monitor=true;
}
void leds_on() {
  
  int r_pwm=0;
  int g_pwm=0;
  int b_pwm=0;
  
  int r_max=255;
  int g_max=244;
  int b_max=229;
   for (r_pwm = 0; r_pwm <= 254; r_pwm++) {
    if (g_pwm<g_max) {g_pwm++;}
    if (b_pwm<b_max) {b_pwm++;}
    analogWrite(LED_PIN_R, r_pwm);
    analogWrite(LED_PIN_G, g_pwm);
    analogWrite(LED_PIN_B, b_pwm);    
    delay(20); // Wait for 20 millisecond(s)
  }
return;
}

void leds_off() {
   for (int brightness = 254; brightness >1; brightness--) {
  
    analogWrite(LED_PIN_R, brightness);
    analogWrite(LED_PIN_G, brightness);
    analogWrite(LED_PIN_B, brightness);
    
    delay(20); // Wait for 20 millisecond(s)
  }
  digitalWrite(LED_PIN_R, LOW); // turn led on
  digitalWrite(LED_PIN_G, LOW); // turn led on
  digitalWrite(LED_PIN_B, LOW); // turn led on 
  led_condition=false;

return;
}
float voltage_poll(int m_pin) {
  float voltage;
  int val = analogRead(m_pin);  // read the input pin
  voltage= round(val * 3.0 / 1023.0);
  Serial.println(voltage);          // debug value
  return voltage;
}

void checkToggleLed(bool motion) { // led task
  int ellapsed=(millis() - delayStart);
  Serial.print("Timer ellapsed:");
  Serial.println(ellapsed);
  if (delayRunning && ((millis() - delayStart) >= DELAY_TIME)) {
    delayStart += DELAY_TIME; // this prevents drift in the delays
    leds_off();
    delayRunning=false;    
    timeractive=false;
  }
}

bool motiondetect() {
  if (voltage_poll(A1) > 1.00) {
    return true;
  }
      
  if (voltage_poll(A1) == 0.00) {
    return false;
  }
 return false;
}
void loop() {

bool motion = motiondetect();

if (motion == true) {
  Serial.println("Motion Detected");
} else {
  Serial.println("No Motion");
}

if ((motion==true) && (timeractive==false)) {
  delayStart = millis();
  delayRunning = true;
  timeractive=true;  
  leds_on();
}

if ((motion==true) && (timeractive==true)) {
  delayStart=millis();
}

if (timeractive==true) {
  checkToggleLed(motion);
}

}
