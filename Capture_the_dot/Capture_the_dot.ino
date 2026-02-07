#include <MUIU8g2.h>
#include <U8g2lib.h>
#include <U8x8lib.h>

#include<Arduino.h>
#include<U8g2lib.h>
#include<Wire.h>

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);

/*This pins are corresponded to a ESP-32. You can choose any compatable pins as per your choise.
 # For connecting the 4 Pin OLED to a arduino Arduino:
 SCK : A5
 SDA : A4 
 # For connecting the 4 Pin OLED display to a ESP-32:
 SCK/SCL : GPIO 22 
 SDA : GPIO 21 
 
 */

const int y_up = 34; //Forward_Button.
const int y_down = 33; //Backward_Button.
const int x_left = 32; //Left_Button.
const int x_right = 35; //Right_Button.
const int BUZZER_PIN = 19; //Can be avoided using as per requirment.
const int LED = 25; //Can be avoided using as per requirment.
int x_pos = 0;
int y_pos = 11;

int x_random = 0;
int y_random = 0;

int point = 0;


void setup() {
  u8g2.begin();
  pinMode(y_up, INPUT);
  pinMode(y_down, INPUT);
  pinMode(x_left, INPUT);
  pinMode(x_right, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED, OUTPUT);

  x_random = random(0,118);
  y_random = random(11,54);
}

void playBuzzerSound() {   //Remove this function if not using a Buzzer.
  digitalWrite(BUZZER_PIN, HIGH);
  delay(50);
  digitalWrite(BUZZER_PIN, LOW);
}

void flashLED() { //Remove this function if not using a LED.
  digitalWrite(LED, HIGH);
  delay(50);
  digitalWrite(LED, LOW);
}

void loop() {
  // Y-axis
  if(y_pos > 11) {
    if(digitalRead(y_up) == HIGH) {
      y_pos -= 1; 
    }
  }
  if(y_pos < 54) {
    if(digitalRead(y_down) == HIGH) {
      y_pos += 1;
    }
  }

  // X-axis
  if(x_pos > 0) {
    if(digitalRead(x_left) == HIGH) {
      x_pos -= 1;
    }
  }
  if(x_pos < 118) {
    if(digitalRead(x_right) == HIGH) {
      x_pos += 1;
    }
  }
  

  u8g2.clearBuffer();

  // Display Points
  u8g2.setFont(u8g2_font_torussansbold8_8r); //8 pixel
  u8g2.drawStr(40, 10, "Points:");
  u8g2.setCursor(95, 10);
  u8g2.print(point);

  //Creat Horizontle Line
  u8g2.drawHLine(0, 11, 128);

  //Creat controlling square
  u8g2.drawBox(x_random, y_random, 5, 5);

  // Creat Dots
  u8g2.drawBox(x_pos, y_pos, 10, 10);

  //Capture dots
  if(abs(x_pos - x_random) <= 5 && abs(y_pos - y_random) <= 5) {
    u8g2.setDrawColor(0);
    u8g2.drawBox(x_random, y_random, 5, 5);
    u8g2.setDrawColor(1);
    x_random = random(0,118);
    y_random = random(11, 54);
    point += 10;
    playBuzzerSound(); //Remove if not using a Buzzer.
    flashLED(); // Remove if not using a LED.

  }


  u8g2.sendBuffer();
  delay(10); /* Change "10" if you want to change the speed of the dot(you control)
                less "value" == More speed */
}
