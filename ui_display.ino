#include <ezButton.h>

#include <Encoder.h>

#include <U8g2lib.h>

#include <Arduino.h>

#include <ArrayList.h>
#include "DFRobotDFPlayerMini.h"
#include "SoftwareSerial.h"
//FIX FWD AND BACK BUTTONS
//FIX SD CARD REMOVED SCREEN

Encoder *knob;


class logoClass
{

public:
  int Width;
  int Height;
  const unsigned char* Pic;

  logoClass(const unsigned char* pic, int width, int height)
  {
    Width = width;
    Height = height;
    Pic =  pic;

  }


};




// ' Record_logo', 16x15px

// ' Player_box', 128x9px
const unsigned char epd_bitmap__Player_box [] PROGMEM = {
    0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x80, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0xFE, 0xFF, 0xFF, 0xFF, 
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 
  0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
  0xFF, 0xFF, 0xFF, 0x7F, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0xFE, 0xFF, 0xFF, 0xFF, 
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 
  0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
  0xFF, 0xFF, 0xFF, 0x7F, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xFF, 0xFF, 0xFF, 0xFF, 
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
};
logoClass playerBox(epd_bitmap__Player_box, 128, 9);
// ' Play_button', 4x6px
const unsigned char epd_bitmap__Play_button [] PROGMEM = {
	 0x0C, 0x08, 0x00, 0x00, 0x08, 0x0C,
};
logoClass playButton(epd_bitmap__Play_button, 4, 6);
// ' Pause_button', 6x6pxsketch.ino

const unsigned char epd_bitmap__Pause_button [] PROGMEM = {
	0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C,
};
logoClass pauseButton(epd_bitmap__Pause_button, 6,6);
// ' item_boxes', 128x16px
const unsigned char epd_bitmap__item_boxes [] PROGMEM = {
	0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0xC0, 0xFD, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xBF, 0xFE, 0xFF, 0xFF, 0xFF, 
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 
  0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
  0xFF, 0xFF, 0xFF, 0x7F, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0xFE, 0xFF, 0xFF, 0xFF, 
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 
  0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
  0xFF, 0xFF, 0xFF, 0x7F, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0xFE, 0xFF, 0xFF, 0xFF, 
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 
  0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
  0xFF, 0xFF, 0xFF, 0x7F, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0xFE, 0xFF, 0xFF, 0xFF, 
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 
  0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
  0xFF, 0xFF, 0xFF, 0x7F, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0xFD, 0xFF, 0xFF, 0xFF, 
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xBF, 
  0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0xC0,
};
logoClass itemBoxes(epd_bitmap__item_boxes, 128, 16);
// ' Forward_button', 5x6px
const unsigned char epd_bitmap__Forward_button [] PROGMEM = {
	 0x1A, 0x16, 0x0E, 0x0E, 0x16, 0x1A,
};
logoClass forwardButton(epd_bitmap__Forward_button, 5,6);

// ' Back_button', 5x6px
const unsigned char epd_bitmap__Back_button [] PROGMEM = {
	0x0B, 0x0D, 0x0E, 0x0E, 0x0D, 0x0B,
};
logoClass backButton(epd_bitmap__Back_button, 5 , 6);

SoftwareSerial mySoftwareSerial(0, 1);  // RX, TX
DFRobotDFPlayerMini myDFPlayer;
bool rein = false;


// Array of all bitmaps for convenience. (Total bytes used to store images in PROGMEM = 608)
int LEN = 6;
logoClass epd_bitmap_allArray[6] = {
	playerBox,
	playButton,
	pauseButton,
	itemBoxes,
	forwardButton,
	backButton
};

//this not be a const in the future, will be dependent on files
//read off of MicroSD card.
int Song_count = 0;
//place holder stuff

//selected index
int item_selected = 0;
//shown on item box above
int prev_item;
//shown on item box below
int next_item;

int current_UI = 1;
//this will be our indcator of the UI screen
//we are on so we can change the behavior of
//the selector depending on the
//current screen.
int play_index = 74;
char buffer[32];
int str_width = 0;

//rotary encoder pins
int Song_selected = 0;

long knob_pos;
bool switch_state;
bool last_switch_state;
bool playpau_state = false;
bool past_play_buttonst;
bool play_button_st;
bool call_back;
bool call_fwd;


ArrayList<String> names;

ezButton back_butt(5);
ezButton pause_butt(6);
ezButton fwd_butt(7);




//screen constructor
U8G2_SH1106_128X64_NONAME_2_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE); 
void setup() {


  u8g2.begin();
  Serial.begin(115200);
  mySoftwareSerial.begin(9600);
  u8g2.setFont(u8g2_font_ncenB08_tr);
  back_butt.setDebounceTime(50);
  fwd_butt.setDebounceTime(50);
  pause_butt.setDebounceTime(25);
  
  pinMode(3, INPUT);
  pinMode(2, INPUT);
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP);
  pinMode(7, INPUT_PULLUP);
  last_switch_state = digitalRead(4);
  knob = new Encoder(3,2); //A, B


  if(!myDFPlayer.begin(mySoftwareSerial))
  {

    Serial.println(F("It's not workingggg omggg brooooo :/ \n restart it or meet your doom."));
    while(true);
  }


   

  Serial.println(F("SD card loaded."));
  Song_count = myDFPlayer.readFileCounts();
 Serial.println(Song_count);
  for(int i = 0; i < Song_count; i++)
  {
    
   myDFPlayer.next();
   myDFPlayer.pause();
    names.add("Song " + String(i + 1));

  }
   Serial.println(F("All files listed.")); 
   myDFPlayer.pause();
   myDFPlayer.volume(10);
 
  //INPUT_PULLUP takes input when we are connected to ground making reading input easy
/*


  root = SD.open("/");
  
    dir_count = printDirectory(root);
    file_index = 0;

    for(int i = 0; i < names.size(); i++)
    {

      Serial.println(names.get(i));

    }   
     
    Serial.println("All files listed.");
   Song_count = names.size();
    for(int i = Song_count + 1;i < names.size(); i++)
    {

      names.remove(i);


    }
    */
  

}

long old_pos = -999;
bool inserted = true;
bool run = false;


void loop() {


  back_butt.loop();
  fwd_butt.loop();
  pause_butt.loop();

  play_button_st = digitalRead(6);

  readKnob();

     if(back_butt.isPressed() && inserted == true)
    {
        
      skipBackSong();    
      myDFPlayer.previous();
      call_back = true;

    }
   
    if(fwd_butt.isPressed() && inserted == true)
    {


      skipForwardSong();  
      myDFPlayer.next();
      call_fwd = true;
  
    } 
   









   if(pause_butt.isPressed())
   {

      if(playpau_state == false)
      {
      
         playpau_state = true;
      
          myDFPlayer.start();
        
      }
      else {
      
        playpau_state = false;
 
        
        myDFPlayer.pause();
        
      }

      

   }



  

            




if(item_selected == 0){
 prev_item = Song_count - 1;
}
else {
prev_item = item_selected - 1;
}



if(item_selected == Song_count - 1)
{

next_item = 0;

}
else {

next_item = item_selected + 1;

}



  if (myDFPlayer.available()) {
    uint8_t type = myDFPlayer.readType();
    int value = myDFPlayer.read();

     
    if (type == DFPlayerCardRemoved) {
      inserted = false;
      current_UI = 2;
    }
    else {
      inserted = true;
      current_UI = 1;
    }

  }





play_index -= 3;
   //page buffer loop
  
   u8g2.firstPage();
   do
   { 
            
          
            if(current_UI == 1)
            {  

                   
              initUI();   
              drawSongNames(); 
              u8g2.setColorIndex(2);
              u8g2.drawRBox(1,32, epd_bitmap_allArray[3].Width -2, epd_bitmap_allArray[3].Height, 3);
              u8g2.setClipWindow(6, 3 , 74, 14);
              u8g2.setDrawColor(2);
              snprintf(buffer, sizeof(buffer),"Now playing: %s", names.get(Song_selected).c_str());
              u8g2.drawStr(7 + play_index, 11, buffer);
              u8g2.setMaxClipWindow();
              str_width = -1 * u8g2.getStrWidth(buffer);
              if(call_fwd == true)
              {
                  drawForwardBox();
                  call_fwd = false;

              }
              if(call_back == true)
              { 
                 drawBackBox();
                 call_back = false;


              }

            }

              if(current_UI == 2)
              {
                  
                
      
                u8g2.drawStr(0,10,"Please insert your ");
                u8g2.drawStr(0,19, "SD card.");
                u8g2.drawStr(0,28,"Restart to update");
                u8g2.drawStr(0,37,"songs.");
                rein = true;
                

              }  

 
             




           
            
           
            
            
         
    

   } while(u8g2.nextPage());

  

   if(play_index < str_width)
   {

    play_index = 74;

   }

 past_play_buttonst = play_button_st;
   

  }





//default song select UI
//UI mode = 1 
void initUI()
{
  u8g2.setColorIndex(0);
  u8g2.drawXBMP(0,0,epd_bitmap_allArray[3].Width, epd_bitmap_allArray[3].Height, epd_bitmap_allArray[3].Pic);
  u8g2.drawXBMP(0,16, epd_bitmap_allArray[3].Width, epd_bitmap_allArray[3].Height, epd_bitmap_allArray[3].Pic);
  u8g2.drawXBMP(0,32, epd_bitmap_allArray[3].Width, epd_bitmap_allArray[3].Height, epd_bitmap_allArray[3].Pic);
  u8g2.drawXBMP(0,48, epd_bitmap_allArray[3].Width, epd_bitmap_allArray[3].Height, epd_bitmap_allArray[3].Pic);
  u8g2.drawXBMP(119,5, epd_bitmap_allArray[4].Width, epd_bitmap_allArray[4].Height, epd_bitmap_allArray[4].Pic);
   if(playpau_state == true)
    {
      u8g2.drawXBMP(107,5, epd_bitmap_allArray[2].Width, epd_bitmap_allArray[2].Height, epd_bitmap_allArray[2].Pic);
                  
    }
    else
    {
      u8g2.drawXBMP(107,5, epd_bitmap_allArray[1].Width, epd_bitmap_allArray[1].Height, epd_bitmap_allArray[1].Pic);
                    
    }

  u8g2.drawXBMP(94,5, epd_bitmap_allArray[5].Width, epd_bitmap_allArray[5].Height, epd_bitmap_allArray[5].Pic);
  
}


//draw song names according to selected indexes
void drawSongNames()
{
  u8g2.setColorIndex(2);
  
      
    
    u8g2.setCursor(22, 28 + (16 * 0)); 
    u8g2.print(names.get(prev_item));
   


    u8g2.setCursor(22, 28 + (16 * 1)); 
    u8g2.print(names.get(item_selected));
 

    u8g2.setCursor(22, 28 + (16 * 2)); 
    u8g2.print(names.get(next_item));
  
}


void readKnob()
{

 switch_state = digitalRead(4);
 knob_pos = knob->read();
 

if(switch_state == 0 && switch_state != last_switch_state)
{

  Song_selected = item_selected;
  if(inserted == true)
  {
   myDFPlayer.play(item_selected + 1);
  }
  

}

 if(knob_pos != old_pos)
  {
      
      if(old_pos+4 <= knob_pos)
      {
        old_pos = knob_pos;

        item_selected--;

        if(item_selected < 0)
        {

          item_selected = Song_count - 1;

        }


      }
      else if(old_pos - 4 >= knob_pos)
      {
        old_pos = knob_pos;

        item_selected++;
 
 
        if(item_selected == Song_count)
        {

          item_selected = 0;

        }
 
      }
     
  }

  
  last_switch_state = digitalRead(4);

}

void drawBackBox()
{


u8g2.setColorIndex(2);
u8g2.drawBox(94, 5, epd_bitmap_allArray[5].Width, epd_bitmap_allArray[5].Height);

}

void skipBackSong()
{

Song_selected--;

        if(Song_selected < 0)
        {

          Song_selected = Song_count - 1;

        }


}



void skipForwardSong()
{

Song_selected++;
 
 
        if(Song_selected == Song_count)
        {

          Song_selected = 0;

        }



}








void drawForwardBox()
{

u8g2.setColorIndex(2);
u8g2.drawBox(119, 5, 5, 6);

}






