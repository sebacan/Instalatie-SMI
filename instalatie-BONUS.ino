#include <IRremote.h>

const int receiver = 5;
IRrecv irrecv(receiver);
decode_results results;
const byte releuPin = 6;
const byte releuPin2=9;
volatile byte stat = 0;
const int buzzerPin = 4;


volatile int mod = 0;
volatile int track = 0; 
volatile int n;

int k=0;

const int length[8] = {73,69,71,29,51,77,64,63}; // numarul de note din fiecare piesa
const char * notes[8] = \
 {"ggagsed deggsgg ggagsed deggsgg DCbCDbCbabCabagabgagsgasgsesgeseddeggsgg ", \
 "ddaagfedcdefga ddaagfedcdefga avgavCDagfdefgfgavaagfedfedgfgavCDagfed" , \
 "cfffgagavCavafggfcfffgagavCavafggffaCDCvagfgavCcfagfccfffgagavCavafggf " , \
 "faagfvvagaCCbCaDCvagfeagffef ", \
 "aavCagfgagdgavCaggfgagff vavCDDaaCagfecavCagfgagff ", \
 "cffefaagCCCvagacffefaagCffeedcCCCfvaagCCCfvaagDDDCvavgavCffgaDDDCvavgavCffgf ",\
 "ggdgadbabCbaggsesgabsedd DCbCbabgasedggsgagdbbabCbabCbagsgCbagg ", \
 "egbbbaCbagabgegasedeaaeesgsedgabbbaCbag DD bb baCdagabgegasede "};

const byte beats[8][77] = {
{2,2,1,1,1,1,4,2,2,2,2,2,2,4,2,2,2,2,1,1,1,1,4,2,2,2,2,2,2,4,2,2,3,1,1,1,1,1,3,1,1,1,1,1,3,1,1,1,1,1,3,1,1,1,1,1
,3,1,1,1,1,1,3,1,2,2,2,2,2,2,4,2,2 }, \
{2,2,2,2,2,2,2,2,2,2,2,2,2,4,2,2,2,2,2,2,2,2,2,2,2,2,2,2,4,2,2,2,2,2,2,2,2,2,2,2,2,2,2,4,2,2,4,2,2,2,2,2,2,4,1,1
,2,4,2,2,2,2,2,2,2,2,2,2,8 } , \
{2,2,2,2,2,1,1,1,1,2,2,2,1,1,2,2,6,2,2,2,2,2,1,1,1,1,2,2,2,1,1,2,2,6,1,1,3,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,4,4,2,2
,2,2,1,1,1,1,2,2,2,1,1,2,2,6,2 } , \
{ 2,3,1,2,2,2,2,2,2,2,2,2,2,6,2,3,1,2,2,2,2,2,2,2,2,2,2,6,2 }, \
{ 2,3,1,2,2,4,4,3,1,2,2,8,3,1,2,2,3,1,4,2,2,3,1,6,2,3,1,2,2,2,2,2,2,2,2,2,2,6,2,2,2,2,2,4,4,2,2,3,1,8,8}, \
{2,2,3,1,2,2,2,2,2,2,3,1,2,2,4,2,2,3,1,2,2,2,2,2,2,3,1,2,2,4,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,4,2,1,1
,3,1,2,2,4,3,1,2,2,2,2,4,2,1,1,3,1,2,2,4,8},  \
{ 2,3,1,2,2,4,4,3,1,2,2,8,3,1,2,2,3,1,4,2,2,3,1,6,2,3,1,2,2,2,2,2,2,2,2,2,2,6,2,2,2,2,2,4,4,2,2,3,1,8,8}, \
{2,2,3,1,2,2,2,2,2,2,3,1,2,2,4,2,2,3,1,2,2,2,2,2,2,3,1,2,2,4,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,4,2,1,1
,3,1,2,2,4,3,1,2,2,2,2,4,2,1,1,3,1,2,2,4,8}};

const int tempo[8] = {150,150,150,150,150,150,150,150}; 


void playTone(int tone, int duration) {
 for (long i = 0; i < duration * 1000L; i += tone * 2) {
 digitalWrite(buzzerPin, HIGH);
 delayMicroseconds(tone);
 digitalWrite(buzzerPin, LOW);
 delayMicroseconds(tone);
 }
}

void playNote(char note, int duration)
{
 const char names[] = { 'c', 'd', 'e', 'f', 's', 'g', 'a', 'v', 'b', 'C', 'D', 'E' }; // note
 const int tones[] = { 1915, 1700, 1519, 1432, 1352, 1275, 1136, 1073, 1014, 956, 852, 758 };
// frecvente
 for (int i = 0; i < 12; i++)
 {
 if (names[i] == note) playTone(tones[i], duration);
 } }

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  irrecv.enableIRIn();
  pinMode(releuPin, OUTPUT);
  pinMode(releuPin2, OUTPUT);
 pinMode(buzzerPin, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
Serial.println(results.value,HEX);

        for (n = 0; n < length[track]; n++)
        {

        if (notes[track][n] == ' ')
        {delay(beats[track][n] * tempo[track]); // pauză
        digitalWrite(releuPin,LOW);
        digitalWrite(releuPin2,HIGH);
        }
         else playNote(notes[track][n], beats[track][n] * tempo[track]);
        { digitalWrite(releuPin,HIGH);
          digitalWrite(releuPin2,LOW);
        }

        Serial.println(results.value,HEX);

        
          
         if (irrecv.decode(&results))
         {
         switch(results.value)
         {
          case 0xE13DDA28:track=0;n=0;delay(1000);break;
          case 0xAD586662:track=1;n=0;delay(1000);break;
          case 0x273009C4:track=2;n=0;delay(1000);break;
          case 0xF5999288:track=3;n=0;delay(1000);break;
          case 0x731A3E02:track=4;n=0;delay(1000);break;
          case 0x2C452C6C:track=5;n=0;delay(1000);break;
          case 0x4592E14C:track=6;n=0;delay(1000);break;
          case 0x6825E53E:track=7;n=0;delay(1000);break;
          case 0xB9F56762:delay(10000);
                          digitalWrite(releuPin,LOW);
                          digitalWrite(releuPin2,LOW);
          
                          
         }
          irrecv.resume();
         }
          delay(tempo[track]/2);   //break between musical notes
          digitalWrite(releuPin,LOW);

          if(results.value!=0xB9F56762)
          digitalWrite(releuPin2,HIGH);
          else
          digitalWrite(releuPin2,LOW);

        }

}


