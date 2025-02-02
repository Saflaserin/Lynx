#include <LiquidCrystal.h>
#include <Servo.h>

Servo myservo;

int IR1 = 7; 
int IR2 = 9; 
int Slot = 4; 

int flag1 = 0; 
int flag2 = 0; 
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);

  pinMode(IR1, INPUT);
  pinMode(IR2, INPUT);
  
  myservo.attach(8);
  myservo.write(100); 

  lcd.setCursor(0, 0);
  lcd.print("Parking System");
  delay(2000);
  lcd.clear();
}

void loop() {
  
  if (digitalRead(IR1) == LOW && flag1 == 0) {
    if (Slot > 0) 
      flag1 = 1; 
      myservo.write(0);
      Slot--; 
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Car Entered!");
      delay(2000);
    } else {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Sorry :( ");
      lcd.setCursor(0, 1);
      lcd.print("Parking Full");
      delay(3000);
    }
  }

  
  if (digitalRead(IR2) == LOW && flag2 == 0) {
    flag2 = 1; 
    if (Slot < 4) { 
      myservo.write(0);
      Slot++; 
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Car Exited!");
      delay(2000);
    }
  }

  
  if (flag1 == 1 || flag2 == 1) {
    delay(1000); 
    myservo.write(100); 
    flag1 = 0;
    flag2 = 0;
  }

  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("WELCOME!");
  lcd.setCursor(0, 1);
  lcd.print("Slots Left: ");
  lcd.print(Slot);

  delay(500);