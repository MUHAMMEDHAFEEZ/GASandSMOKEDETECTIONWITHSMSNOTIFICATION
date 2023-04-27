#include<Servo.h>
Servo myservo;
int pos=0;
int val;
#include<LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
#include<SoftwareSerial.h>
SoftwareSerial mySerial(9, 10);
byte tx=1;

const int Buzzer= 6;
const int DC_Motor= 7;

int gasC_1= 0; //set initial temp 0 for all MQ 3
int smkC_1= 0; //set initial tempC for all MQ 2

const int SensorPin1= A0; //fir input sensor pin
const int SensorPin2= A1;

String textforSMS;
void setup()
{
lcd.begin(14, 2);
delay(100);
pinMode(tx, OUTPUT);
myservo.attach(13);
pinMode(Buzzer, OUTPUT);
pinMode(SensorPin1, INPUT);
pinMode(SensorPin2, INPUT);
pinMode(Buzzer, OUTPUT);
pinMode(DC_Motor, OUTPUT);
mySerial.begin(9600);
Serial.begin(9600); //Start the serial connections with the computer
}

void loop()
{
int gasC_1= analogRead(SensorPin1);
int smkC_1= analogRead(SensorPin2);
gasC_1= analogRead(SensorPin1); // read the value from the LM35 sensor
gasC_1= (5.0 * gasC_1 * 100.0)/ 1024.0; //convert the analog data to temp
smkC_1= analogRead(SensorPin2); // read the value from thr MQ-2 sensor
smkC_1= (5.0* smkC_1 * 100.0)/1024.0; // convert the analog data to temp
delay(50);

if (gasC_1 >=100 || smkC_1 >=100)
{
val= analogRead(pos);
val= map(val, 0, 1023, 0, 180);
myservo.write(val);
delay(50);
digitalWrite(DC_Motor, HIGH);

lcd.clear();
lcd.setCursor(0, 0);
lcd.print("THERE IS FIRE!!!!");
lcd.setCursor(0, 1);
lcd.print("NOT SAFE HERE");
delay(200);
lcd.clear();
lcd.print("SENDING SMS.....");
delay(100);

digitalWrite(Buzzer, HIGH);
delay(100);
digitalWrite(Buzzer, LOW);
delay(100);
digitalWrite(Buzzer, HIGH);
delay(100);

digitalWrite(Buzzer, LOW);
delay(5);

Serial.print("FIRE ALERT! Please be informed that fire has occured!\r");
delay(100);
Serial.println((char)26); // End AT command with a*z, ASCII code 26
delay(100);
Serial.println();
}
else
{
digitalWrite(DC_Motor, LOW);
myservo.write(95);
lcd.clear();
lcd.setCursor(0, 0);
lcd.print(" NO FIRE ");
lcd.setCursor(0, 1);
lcd.print(" ALL SAFE ");
}
}