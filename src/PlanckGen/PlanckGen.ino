#include <MozziGuts.h>
#include <mozzi_fixmath.h>

#define KNOB_PIN 1

#define BUTTON_PIN 5  // set the digital input pin for the button
#define CONTROL_RATE 128

int MODE = 0;
boolean SAMPLE = false;
int counter = 0;
const int samplebuflength = 400;
int samplebuf[samplebuflength];
int varsamplebuflength = samplebuflength;
int button_state = HIGH;

void setup(){
  pinMode(BUTTON_PIN, INPUT);
  
  startMozzi(CONTROL_RATE);
}

void addSample(int signal){
  if(SAMPLE){
    samplebuf[counter]=signal;
  }
  counter++;
  if(counter>samplebuflength){
     counter = 0; 
  }
}

void updateControl(){
  
  int knob = mozziAnalogRead(KNOB_PIN); 
  varsamplebuflength = knob>>2;
  if(varsamplebuflength > 400){
     varsamplebuflength = 400; 
  }
  if(varsamplebuflength<0){
   varsamplebuflength=0; 
  }
  
  button_state = digitalRead(BUTTON_PIN);
  if(button_state == HIGH){
    SAMPLE = false; 
  }else{
    SAMPLE = true;
  }

}


int updateAudio(){

  int asig = getAudioInput();  
  int sample = asig;
  addSample(sample);
  //asig = asig+samplebuf[counter%varsamplebuflength];
  //asig >>=2;
  // or signal only
  asig = samplebuf[counter%varsamplebuflength];
  return asig;
}


void loop(){
  audioHook();
}




