#include <U8g2lib.h>
#include <Wire.h>
#include <Arduino.h>




U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);
U8G2LOG ulog;



uint8_t word_[16*8];
int bytesRead;
char input[16*8];
int length_;


void setup() {
  Serial.begin(9600);
  u8g2.begin();
  u8g2.setFont(u8g2_font_ncenB08_tr);
   ulog.begin(u8g2, 16, 8, word_);
  ulog.setRedrawMode(1);
  ulog.setLineHeightOffset(0);
  
}

void loop() {


  while(Serial.available() > 0)
  {
    length_ = Serial.readBytesUntil('\n', input, sizeof(input) - 1);
    if(input[length_] !=  ' ')
    {
      
      input[length_] = ' ';  
      
    }
    input[length_  + 1] = '\0'; 
    
    ulog.print(input);
   }
 
}



 


    
  
