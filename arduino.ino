#include <LiquidCrystal.h>

//KanaLiquidCrystal lcd(12, 11, 5, 4, 3, 2);
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
String incomingByte;   // String to store the incoming data.
char aznable[5];
char casper[3];
int AnalogPin = A0;
int sensorValue = 0;
int PWM6 = 0;

//Arduino Uno code designed to work with the かつらぎ C++ program. Running V1.0.

void setup() {
        Serial.begin(115200);   
        lcd.begin(16, 2);
        lcd.print("\xba\xdd\xc6\xc1\xca\xb6\xc2\xd7\xb7");
        pinMode(13, OUTPUT);
        pinMode(7, OUTPUT);
        pinMode(6, OUTPUT);  
        delay(250);
}
void loop() {
        if (Serial.available() > 0) {
                incomingByte = Serial.readString();
                incomingByte.toCharArray(aznable, 6);
                if(aznable[0] == 'R' && aznable[1] == 'A' && aznable[2] == '0'){
                for (int i = 0; i <= 0; i++) {
                    sensorValue = analogRead(AnalogPin);
                    delay(50);
                    Serial.print(sensorValue);
                    sensorValue = 0;
                    Serial.flush();}   
                }
                lcd.setCursor(0, 1);
                for (int i = 0; i <= 0; i++) {
                    lcd.print(aznable);   
                    delay(10);   
                }
                if(aznable[0] == 'W' && aznable[1] == '1' && aznable[2] == '3' && aznable[3] == '1'){
                  digitalWrite(13,HIGH);
                } else
                if(aznable[0] == 'W' && aznable[1] == '1' && aznable[2] == '3' && aznable[3] == '0'){
                  digitalWrite(13,LOW);
                } 
                if(aznable[0] == 'W' && aznable[1] == '0' && aznable[2] == '7' && aznable[3] == '1'){
                  digitalWrite(7,HIGH);
                } else
                if(aznable[0] == 'W' && aznable[1] == '0' && aznable[2] == '7' && aznable[3] == '0'){
                  digitalWrite(7,LOW);
                }
                if(aznable[0] == 'S' && aznable[1] == 'V'){
                  //Char to String.
                  String AZ1(aznable[2]);
                  String AZ2(aznable[3]);
                  String AZ3(aznable[4]);
                  //Concatrenate strings.
                  String casper = AZ1 + AZ2 + AZ3;
                  //Convert to Integer.
                  PWM6 = casper.toInt();
                  //Use int value as PWM.
                  analogWrite(6,PWM6);//aznable[1] + aznable[2] + aznable[3]
                }
                Serial.flush();
        } Serial.flush();             
}
