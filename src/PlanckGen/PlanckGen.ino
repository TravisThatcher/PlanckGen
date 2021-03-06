#include <MozziGuts.h>
#include <mozzi_fixmath.h>
#include <AutoMap.h>
#include <EventDelay.h>

#define KNOB_PIN 1

#define BUTTON_PIN 5  // set the digital input pin for the button
#define CONTROL_RATE 128

int MODE = 0;
boolean SAMPLE = false;
int counter = 0;
int readCounter = 0;
const int samplebuflength = 800;

int varsamplebuflength = samplebuflength;

byte samplebuf[samplebuflength];

AutoMap Mapper(0,1024, 0, samplebuflength);

int button_state = LOW;

void setup(){
  pinMode(BUTTON_PIN, INPUT);  
  startMozzi(CONTROL_RATE);
  readCounter = samplebuflength/2;
}

void addSample(int signal){
  if(SAMPLE){
    samplebuf[counter]=signal;
  }
  counter++;
  if(counter>varsamplebuflength){
    counter = 0; 
  }
}

void updateControl(){

  int knob = mozziAnalogRead(KNOB_PIN); 
  varsamplebuflength = Mapper(knob);

  button_state = digitalRead(BUTTON_PIN);
  if(button_state == HIGH){
    SAMPLE = true; 
  }else{
    SAMPLE = false; 
  }

}


int updateAudio(){

  int asig = getAudioInput();  
  int sample = asig;
  addSample(sample);
  if(readCounter>varsamplebuflength){
    readCounter = 0; 
  }
  if(SAMPLE){
    //      asig = samplebuf[counter%varsamplebuflength];
    asig = samplebuf[readCounter];
  }
  readCounter++;
  return asig;
}


void loop(){
  audioHook();
}





