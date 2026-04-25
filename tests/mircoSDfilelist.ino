#include <ArrayList.h>
#include <SD.h>
#include <U8g2lib.h>
#include <U8glib.h>



 int printDirectory(File rootf);

 void display_sdcard();

const int cs_pin = 42;
const int sd_inpin = 40;
bool rein = false;
bool past_sd_state;
ArrayList<String> names;
int file_index = 0;
int dir_count = 0;

File root;  

U8G2_SH1106_128X64_NONAME_2_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE); 

void setup() {
  Serial.begin(9600);
  u8g2.begin();
  u8g2.setFont(u8g2_font_ncenB08_tr);
   pinMode(sd_inpin, INPUT_PULLUP);
    pinMode(cs_pin, OUTPUT);
  while(!Serial);

  Serial.println("Loading SD card....");
  if(!SD.begin(cs_pin))
  {
      Serial.println("Your card isn't wired correctly or insterted, fix it and reset.");

      while(true);
  }



   past_sd_state = true;

  Serial.println("SD card loaded.");

    root = SD.open("/");
    file_index = printDirectory(root);
    for(int i = 0; i < names.size() - dir_count; i++)
    {

      Serial.println(names.get(i));

    }   
     
    Serial.println("All files listed.");
    Serial.println(file_index);





}

 


void loop() {

   
   if(digitalRead(sd_inpin) && past_sd_state == true)
  {
    SD.end();
    past_sd_state = false;
 
    

  }
  else if(!digitalRead(sd_inpin) && past_sd_state == false)
  {
    names.clear();
    past_sd_state = true;
    SD.begin(cs_pin);
    root = SD.open("/");
    file_index = 0;
    printDirectory(root);
    Serial.println(file_index);
    root.close();


  }
     
  
} 

  


   

 




 int printDirectory(File rootf)
{


  
 while (true)
  {
      File curr = rootf.openNextFile();

      if(!curr)
      {

          break;


      }

     

      
      names.add(curr.name());

      
      if(curr.isDirectory())
      {
         
         names.removeItem(curr.name());
         printDirectory(curr);
        



      }
      else {
      file_index++;
      }
  
      

     

            

  curr.close();

  }

  return file_index;

 } 


 void display_sdcard()
 {
    
      
      Serial.println("Please insert your SD card");
   

 }


