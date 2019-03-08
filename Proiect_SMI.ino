#include <IRremote.h>
#include <util/delay.h>

const int receiver = 7;
IRrecv irrecv(receiver);
decode_results results;
const int releuPin1 = 6;
const int releuPin2 = 9;
const int buzzerPin = 4;


volatile int n;

//const int length =55; // numarul de note din fiecare piesa
//const char * notes = {"bbbbbbbDgab CCCCCbbbbbaabaD bbbbbbbDgab CCCCCbbbbDDCag "} ;
//const byte beats[55] = {2, 2, 4, 2, 2, 4, 2, 2, 3, 1, 6, 2, 2, 2, 3, 1, 2, 2, 2, 1, 1, 2, 2, 2, 2, 4, 2, 2, 2, 2, 4, 2, 2, 4, 2, 2, 3, 1, 6, 2, 2, 2, 3, 1, 2, 2, 2, 1, 1, 2, 2, 2, 2, 6, 2};
//const int tempo = 150;

//ramona
 int length = 73;
char notes[] = "ggagsed deggsgg ggagsed deggsgg DCbCDbCbabCabagabgagsgasgsesgeseddeggsgg "; // a space represents a rest
int beats[] = { 2,2,1,1,1,1,4,2,2,2,2,2,2,4,2,2,2,2,1,1,1,1,4,2,2,2,2,2,2,4,2,2,3,1,1,1,1,1,3,1,1,1,1,1,3,1,1,1,1,1,3,1,1,1,1,1,3,1,1,1,1,1,3,1,2,2,2,2,2,2,4,2,2 };

 //nuray
//int length = 63;
//char notes[] = "egbbbaCbagabgegasedeaaeesgsedgabbbaCbag DD bb baCdagabgegasede ";
//int beats[] = { 2,2,2,2,2,2,2,2,2,6,2,2,2,2,2,2,2,2,2,6,2,2,2,2,2,4,2,2,6,2,2,2,2,2,2,2,2,2,4,2,2,4,2,2,4,2,2,2,2,2,2,6,2,2,2,2,2,2,2,2,2,8,8 };

char names[] = { 'c', 'd', 'e', 'f', 's', 'g', 'a', 'v', 'b', 'C', 'D', 'E' };
int tones[] = { 1915, 1700, 1519, 1432, 1352, 1275, 1136, 1073, 1014, 956, 852, 758 };

int durata2 = 1000;
int semnal = 0;
boolean status = 0;
boolean aprins = 0;

unsigned long songMillis = 0;
bool check = false;
int thisNote = -1;

int i;

int tempo = 150;

long cm, cm2;

void doTheThingyThing(){
  for (i = 0; i < length,status; i++) {
    
    if (notes[i] == ' ') {
       cm = millis();
      cm2 = millis();
      Serial.println(cm);
      while(cm2 < (cm + beats[i] * tempo)){
        cm2=millis();
      readThingy();}
    } else {
      if(aprins)
        digitalWrite(releuPin2, LOW);
      else digitalWrite(releuPin2, HIGH);
      aprins = !aprins;
      playNote(notes[i], beats[i] * tempo);

      
    }
    // pause between notes
    cm = millis();
    cm2=millis()-10;
      while(cm2 < (cm + tempo / 2)){cm2=millis();
      readThingy();
      if(!status) break;}
      if(!status) break;
  
}

}



void setup()
{ 
    irrecv.enableIRIn();
    pinMode(releuPin1, OUTPUT);
    pinMode(releuPin2, OUTPUT);
    pinMode(buzzerPin, OUTPUT);
    Serial.begin(9600);
}


void loop() {

     if(status){
        digitalWrite(releuPin1, LOW);
        doTheThingyThing();
        thing();
     }
     else digitalWrite(releuPin1, HIGH);
      
     readThingy();
}

void thing(){
      digitalWrite(releuPin2,HIGH);
      delay(1000);
       digitalWrite(releuPin2,LOW);
      delay(1000);
}

void readThingy(){
   if (irrecv.decode(&results)) {
     if(results.value==0xFFC23D){
        status = !status;
     }
   irrecv.resume();
  }
}

void playTone(int tone, int duration) {
    for (long i = 0; i < duration * 1000L; i += tone * 2) {
        digitalWrite(buzzerPin, HIGH);
        delayMicroseconds(tone);
        digitalWrite(buzzerPin, LOW);
        delayMicroseconds(tone);
    }
}

void playNote(char note, int duration) {
    const char names[] = { 'c', 'd', 'e', 'f', 's', 'g', 'a', 'v', 'b', 'C', 'D', 'E' }; // note
    const int tones[] = { 1915, 1700, 1519, 1432, 1352, 1275, 1136, 1073, 1014, 956, 852, 758 }; // frecvente

    for (int i = 0; i < 12; i++) {
      if (names[i] == note) playTone(tones[i], duration);
    }
}
