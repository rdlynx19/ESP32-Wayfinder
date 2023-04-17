/*
Way Finder Implementation
Micro Project
*/

#include "AudioTools.h"
#include "AudioLibs/AudioRealFFT.h" 
#include "BluetoothA2DPSink.h"
#include "MD_Parola.h"
#include "MD_MAX72xx.h"
#include "SPI.h"

#define HARDWARE_TYPE MD_MAX72XX::GENERIC_HW

#define MAX_DEVICES 1
#define CS_PIN 5


MD_MAX72XX mx = MD_MAX72XX(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);

BluetoothA2DPSink a2dp_sink;
AudioRealFFT fft;
//
//int clock_pin = 18;
//int data_pin = 23;

//hex value for Various Animation required for the LED MATRIX
byte start1[]={0x00, 0x38, 0x08, 0x38, 0x08, 0x38, 0x00, 0x00};
byte start2[]={0x00, 0x38, 0x08, 0x38, 0x20, 0x38, 0x00, 0x00};
byte start3[]={0x00, 0x10, 0x30, 0x10, 0x10, 0x10, 0x38, 0x00};

byte exitRight[]={0xa8, 0x54, 0x2a, 0x15, 0x15, 0x2a, 0x54, 0xa8};
byte keepRight1[]={0x00, 0x00, 0x00, 0x00, 0xf0, 0xf0, 0x30, 0x30};
byte keepRight2[]={0x00, 0x00, 0xfc, 0xfc, 0x0c, 0x0c, 0x0c, 0x0c};
byte keepRight3[]={0xff, 0xff, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03};

byte exitLeft[]={0x15, 0x2a, 0x54, 0xa8, 0xa8, 0x54, 0x2a, 0x15};
byte keepLeft1[]={0x00, 0x00, 0x00, 0x00, 0x0f, 0x0f, 0x0c, 0x0c};
byte keepLeft2[]={0x00, 0x00, 0x3f, 0x3f, 0x30, 0x30, 0x30, 0x30};
byte keepLeft3[]={0xff, 0xff, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0};

byte then[]={0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8};
byte circle[]={0x3c, 0x42, 0x99, 0xa5, 0xa5, 0x99, 0x42, 0x3c};
byte uturn[]={0x18, 0x24, 0x42, 0x42, 0x42, 0x47, 0x42, 0x40};
byte rerouting[]={0x3c, 0x42, 0xa5, 0x81, 0x99, 0xa5, 0x42, 0x3c};
byte continueStraight[]={0x18, 0x3c, 0x7e, 0xff, 0x3c, 0x3c, 0x3c, 0x3c};

byte alert1[]={0x00, 0x18, 0x18, 0x18, 0x18, 0x00, 0x18, 0x00};
byte alert2[]={0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
byte alert3[]={0x00, 0x18, 0x18, 0x18, 0x18, 0x00, 0x18, 0x00};

byte turnRight1[]={0x80, 0x40, 0x20, 0x10, 0x10, 0x20, 0x40, 0x80};
byte turnRight2[]={0x20, 0x10, 0x08, 0x04, 0x04, 0x08, 0x10, 0x20};
byte turnRight3[]={0x08, 0x04, 0x02, 0x01, 0x01, 0x02, 0x04, 0x08};

byte turnLeft1[]={0x01, 0x02, 0x04, 0x08, 0x08, 0x04, 0x02, 0x01};
byte turnLeft2[]={0x04, 0x08, 0x10, 0x20, 0x20, 0x10, 0x08, 0x04};
byte turnLeft3[]={0x10, 0x20, 0x40, 0x80, 0x80, 0x40, 0x20, 0x10};

byte arrived1[]={0x00, 0x01, 0x02, 0x04, 0x88, 0x50, 0x20, 0x00};
byte arrived2[]={0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
byte arrived3[]={0x3c, 0x42, 0xa5, 0x81, 0xa5, 0x99, 0x42, 0x3c};
byte arrived4[]={0x00, 0x01, 0x02, 0x04, 0x88, 0x50, 0x20, 0x00};
byte arrived5[]={0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

byte twoHundred[]={0x00, 0xdb, 0x5b, 0xdb, 0x9b, 0x9b, 0xdb, 0x00};
byte fourHundred[]={0x00, 0xe5, 0xa5, 0xa7, 0xa1, 0xa1, 0xe9, 0x00};
byte eightHundred[]={0x00, 0x0f, 0x09, 0x09, 0x0f, 0x09, 0x69, 0x6f};
byte onekm[]={0x00, 0x10, 0x30, 0x10, 0x10, 0x10, 0x38, 0x00};
byte onepointfivekm[]={0x00, 0x43, 0xc2, 0x43, 0x41, 0x41, 0xeb, 0x00};

byte firstexit[]={0x00, 0x02, 0x06, 0x0a, 0x52, 0x62, 0x72, 0x00};
byte secondexit[]={0x70, 0x60, 0x50, 0x08, 0x04, 0x02, 0x02, 0x02};
byte thirdexit[]={0x10, 0x38, 0x54, 0x10, 0x20, 0x40, 0x20, 0x10};
byte fourthexit[]={0x00, 0x1c, 0x0c, 0x14, 0x20, 0x40, 0x40, 0x40};
byte fifthexit[]={0x00, 0x40, 0x60, 0x50, 0x4a, 0x46, 0x4e, 0x40};
byte sixthexit[]={0x18, 0x24, 0x42, 0x42, 0x24, 0x24, 0x2e, 0x24};
byte seventhexit[]={0x18, 0x24, 0x42, 0x42, 0x24, 0x24, 0x2e, 0x24};


float maximum = 0.0;
//float frequency = 0.0;
int freq = 0.0;
int j = 0;
int i = 0;

//byte buffer1[80];
//byte num;
//byte data1;
//byte load;

float arr[10];



// Provide data to FFT
void writeDataStream(const uint8_t *data, uint32_t length) {
  if ( *data>0 ) {
     fft.write(data, length);
  }
 
}
  
  
//to find out the frequency of the input audio wave using FFT Function
void fftResult(AudioFFTBase &fft){

    auto result = fft.result();

    if (result.magnitude>1000){
      //Serial.println(result.frequency);

      // array to store the starting 10 values for the input audio signal
      for ( int k=0; k<10; k++ ) {
        arr[k] = result.frequency;
      }

//        Serial.print(" ");
//        Serial.print(result.magnitude);  
//        Serial.print(" => ");
//        Serial.print(result.frequencyAsNote(diff));

    }
    
}
//function to find the maximum occuring frequncy for a specific signal
//solved the issue of noice
int mostFrequent(float arr[], int n)
{
    // code here
    int maxcount = 0;
    int element_having_max_freq;
    for (int i = 0; i < n; i++) {
        int count = 0;
        for (int j = 0; j < n; j++) {
            if (arr[i] == arr[j])
                count++;
        }
  
        if (count > maxcount) {
            maxcount = count;
            element_having_max_freq = arr[i];
        }
    }
  
    return element_having_max_freq;
}

//display the particular animation using the hex value given to the function when called in the loop function
void display(byte anime[]){
  for(int i=0;i<=7;i++) {
    mx.setRow(0,0,i,anime[i]);
  }
}



void setup() {
  Serial.begin(115200);
  AudioLogger::instance().begin(Serial, AudioLogger::Info);

  // Setup FFT
  auto tcfg = fft.defaultConfig();
  tcfg.length = 4096;
  tcfg.channels = 2;
  tcfg.sample_rate = a2dp_sink.sample_rate();;
  tcfg.bits_per_sample = 16;
  tcfg.callback = &fftResult;
  fft.begin(tcfg);

  // register callback
  a2dp_sink.set_stream_reader(writeDataStream, false);

  // Start Bluetooth Audio Receiver
  Serial.print("starting a2dp-fft...");
  a2dp_sink.set_auto_reconnect(false);
  a2dp_sink.start("a2dp-fft");

//  for (int j=0;j<80;j++){
//  buffer1[j] = 0;
//}


  mx.begin();
  mx.control(MD_MAX72XX::INTENSITY, 0);
  mx.clear();


}


void loop() {
freq = mostFrequent(arr,10);
Serial.println(freq);
/*
Various Frequency of audio signal are associated with specific direction instruction
According to the frequncy received, the coresponding animation will be displayed on the LED MATRIX   
*/

//Range of frequncy for each command to delt with disturbance

  if(freq>=190&&freq<210) //starting of journey
  {
    display(start1);
    delay(1000);
    display(start2);
    delay(1000);
    display(start3);
    delay(1000);
  }
  else if(freq>=210&&freq<230) //Exit Right animation to display
  { 
    display(exitRight);
  
  }
  else if(freq>=230&&freq<250)  //Keep Right animation to display
  { 
    
    display(keepRight1);
    delay(1000);
    display(keepRight2);
    delay(1000);
    display(keepRight3);
    delay(1000);
    
  }
  else if(freq>=250&&freq<270)  //Exit Left animation to display
  { 
    display(exitLeft);
  
  }
  else if(freq>=270&&freq<290)  //Keep Left animation to display
  {
    display(keepLeft1);
    delay(1000);
    display(keepLeft2);
    delay(1000);
    display(keepLeft3);
    delay(1000);
   
  }
  else if(freq>=290&&freq<310) //Thhen animation to display
  {
    display(then);
  }
  else if(freq>=310&&freq<330) //Alert Received
  { 
    display(alert1);
    delay(1000);
    display(alert2);
    delay(1000);
    display(alert3);
    delay(1000);
  }
  else if(freq>=330&&freq<350)//Circular turn to make
  {
    display(circle);
    
  }
  else if(freq>=350&&freq<370) //Turn Left animation to display
  { 
    display(turnLeft1);
    delay(1000);
    display(turnLeft2);
    delay(1000);
    display(turnLeft3);
    delay(1000);
  }
  else if(freq>=370&&freq<390) //Arrived at the destination
  { 
    display(arrived1);
    delay(1000);
    display(arrived2);
    delay(1000);
    display(arrived3);
    delay(1000);
    display(arrived4);
    delay(1000);
    display(arrived5);
    delay(1000);
  }
  else if(freq>=390&&freq<410) //Turn Right animation to display
  {
    display(turnRight1);
    delay(1000);
    display(turnRight2);
    delay(1000);
    display(turnRight3);
    delay(1000);
  }
  else if(freq>=410&&freq<430) //Make a uturn
  {
    display(uturn);
  }
  else if(freq>=430&&freq<450) //Finding a new route
  { 
    display(rerouting);

  }
  else if(freq>=450&&freq<470) //Continue straight on the same road
  {
    display(continueStraight);
  
  }
  else if(freq>=470&&freq<490) //Four Hundred meter to turn
  { 
    display(fourHundred);
    
  }
  else if(freq>=490&&freq<510) //Eight Hundred meter to turn
  { 
    display(eightHundred);

  }
  else if(freq>=510&&freq<530) //One kilometer to turn
  { 
    display(onekm);
  
  }
  else if(freq>=530&&freq<550) //Two Hundred meter to turn
  { 
    display(twoHundred);

  }
  else if(freq>=550&&freq<570) //1.5 kilometer to turn
  { 
    display(onepointfivekm);
   
  }
  else if(freq>=570&&freq<590)//make First Exit
  { 
    display(firstexit);
    
  }
  else if(freq>=590&&freq<610)//make Second Exit
  { 
    display(secondexit);

  }
  else if(freq>=610&&freq<630)//make Third Exit
  { 
    display(thirdexit);
 
  }
  else if(freq>=630&&freq<650)//make Fourth Exit
  { 
    display(fourthexit);
 
  }
  else if(freq>=650&&freq<670)//make Fift Exit
  { 
    display(fifthexit);

  }
  else if(freq>=670&&freq<690)//make Sixth Exit
  { 
    display(sixthexit);

  }
  else if(freq>=690&&freq<710)//make Seventh Exit
  { 
    display(seventhexit);
  
  }
  delay(3000);
  display(continueStraight); //Continue Straight when no instruction is received
//  freq = 0; //reseting the frequncy ater exection of any of the if-else condition
}
