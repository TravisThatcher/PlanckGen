#include <MozziGuts.h>
#include <LowPassFilter.h>
#include <mozzi_fixmath.h>

#define KNOB_PIN 1

const int BUTTON_PIN = 4;  // set the digital input pin for the button

LowPassFilter lpf;
int MODE = 0;
boolean SAMPLE = false;
int counter = 0;
const int samplebuflength = 16384;
int samplebuf[samplebuflength];

void setup(){
  startMozzi();
}


void updateControl(){
  int knob = mozziAnalogRead(KNOB_PIN); 
  byte cutoff_freq = knob>>2; // range 0-255
   button_state = digitalRead(BUTTON_PIN);
   if(button_state == HIGH){
     SAMPLE = false; 
   }else{
     SAMPLE = true;
   }

}


int updateAudio(){
  // subtracting 512 moves the unsigned audio data into 0-centred, 
  // signed range required by all Mozzi units
  if(SAMPLE){
    int asig = getAudioInput()-512;  
    samplebuf[counter]=asig;
  }
  counter++;
  if(counter>=samplebuflength){
    counter=0;
  }
//  asig = lpf.next(asig>>1);
  return samplebuf[counter];
}


void loop(){
  audioHook();
}




