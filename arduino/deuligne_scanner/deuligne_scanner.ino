/*
 * an arduino sketch to interface with a ps/2 keyboard.
 * Also uses serial protocol to talk back to the host
 * and report what it finds. Used the ps2 library.
 */

#include <ps2.h>
// include the library code:
#include "Wire.h"
#include <Deuligne.h>

// initialize the library with the numbers of the interface pins
Deuligne lcd;

/*
 * Pin 5 is the ps2 data pin, pin 6 is the clock pin
 * Feel free to use whatever pins are convenient.
 */

PS2 kbd(6, 5);
byte codebar[90] = {
  0,0,0,0,0,
  0,0,0,0,0,
  0,0,0,0,0,
  0,0,0,0,0,
  0,0,0,0,0,
  0,0,0,0,0,
  0,0,0,0,0,
  0,0,0,0,0,
  0,0,0,0,0,
  0,0,0,0,0,
  0,0,0,0,0,
  0,0,0,0,0,
  0,0,0,0,0,
  0,0,0,0,0,
  0
}; // data to write on startup





byte code1001[81] = {
  42,2,240,130,240,170,42,11,240,139,240,170,42,11,240,139,240,170,42,2,240,130,240,170,42,11,240,139,240,170,42,11,240,139,240,170,42,11,240,139,240,170,42,11,240,139,240,170,42,11,240,139,240,170,42,11,240,139,240,170,42,11,240,139,240,170,42,11,240,139,240,170,42,7,240,135,240,170,28,240,156
};

byte code1002[81] = {
  42,2,240,130,240,170,42,11,240,139,240,170,42,11,240,139,240,170,42,3,240,131,240,170,42,11,240,139,240,170,42,11,240,139,240,170,42,11,240,139,240,170,42,11,240,139,240,170,42,11,240,139,240,170,42,11,240,139,240,170,42,11,240,139,240,170,42,11,240,139,240,170,42,4,240,132,240,170,28,240,156
};

byte code1003[81] = {
  42,2,240,130,240,170,42,11,240,139,240,170,42,11,240,139,240,170,42,4,240,132,240,170,42,11,240,139,240,170,42,11,240,139,240,170,42,11,240,139,240,170,42,11,240,139,240,170,42,11,240,139,240,170,42,11,240,139,240,170,42,11,240,139,240,170,42,11,240,139,240,170,42,11,240,139,240,170,28,240,156
};

byte code1004[81] = {
  42,2,240,130,240,170,42,11,240,139,240,170,42,11,240,139,240,170,42,5,240,133,240,170,42,11,240,139,240,170,42,11,240,139,240,170,42,11,240,139,240,170,42,11,240,139,240,170,42,11,240,139,240,170,42,11,240,139,240,170,42,11,240,139,240,170,42,11,240,139,240,170,42,8,240,136,240,170,28,240,156
};
byte code1005[81] = {
  42,2,240,130,240,170,42,11,240,139,240,170,42,11,240,139,240,170,42,6,240,134,240,170,42,11,240,139,240,170,42,11,240,139,240,170,42,11,240,139,240,170,42,11,240,139,240,170,42,11,240,139,240,170,42,11,240,139,240,170,42,11,240,139,240,170,42,11,240,139,240,170,42,5,240,133,240,170,28,240,156
};

byte code1006[81] = {
  42,2,240,130,240,170,42,11,240,139,240,170,42,11,240,139,240,170,42,7,240,135,240,170,42,11,240,139,240,170,42,11,240,139,240,170,42,11,240,139,240,170,42,11,240,139,240,170,42,11,240,139,240,170,42,11,240,139,240,170,42,11,240,139,240,170,42,11,240,139,240,170,42,2,240,130,240,170,28,240,156
};

byte code1007[81] = {
  42,2,240,130,240,170,42,11,240,139,240,170,42,11,240,139,240,170,42,8,240,136,240,170,42,11,240,139,240,170,42,11,240,139,240,170,42,11,240,139,240,170,42,11,240,139,240,170,42,11,240,139,240,170,42,11,240,139,240,170,42,11,240,139,240,170,42,11,240,139,240,170,42,9,240,137,240,170,28,240,156
};

byte code1008[81] = {
  42,2,240,130,240,170,42,11,240,139,240,170,42,11,240,139,240,170,42,9,240,137,240,170,42,11,240,139,240,170,42,11,240,139,240,170,42,11,240,139,240,170,42,11,240,139,240,170,42,11,240,139,240,170,42,11,240,139,240,170,42,11,240,139,240,170,42,11,240,139,240,170,42,6,240,134,240,170,28,240,156
};

byte code1009[81] = {
  42,2,240,130,240,170,42,11,240,139,240,170,42,11,240,139,240,170,42,10,240,138,240,170,42,11,240,139,240,170,42,11,240,139,240,170,42,11,240,139,240,170,42,11,240,139,240,170,42,11,240,139,240,170,42,11,240,139,240,170,42,11,240,139,240,170,42,11,240,139,240,170,42,3,240,131,240,170,28,240,156
};

byte code1010[81] = {
  42,2,240,130,240,170,42,11,240,139,240,170,42,2,240,130,240,170,42,11,240,139,240,170,42,11,240,139,240,170,42,11,240,139,240,170,42,11,240,139,240,170,42,11,240,139,240,170,42,11,240,139,240,170,42,11,240,139,240,170,42,11,240,139,240,170,42,11,240,139,240,170,42,9,240,137,240,170,28,240,156
};

char* myStrings[]={"This is string 1", "This is string 2", "This is string 3",
"This is string 4", "This is string 5","This is string 6"};

int index = 0;
int i = 0;

boolean thesame1 = true;
boolean thesame1001 = true;
boolean thesame1002 = true;
boolean thesame1003 = true;
boolean thesame1004 = true;
boolean thesame1005 = true;
boolean thesame1006 = true;
boolean thesame1007 = true;
boolean thesame1008 = true;
boolean thesame1009 = true;
boolean thesame1010 = true;
int led = 13;

long randNumber;

void setup()
{
  Serial.begin(9600);
  pinMode(led, OUTPUT);
  // set up the LCD's number of columns and rows: 
  lcd.init();
  lcd.print("hello, world!");
  randomSeed(analogRead(0));
}

void displayString(){

  char* output = "";
  int nbChars = 0;
  int rand = random(9);

  switch (rand){
    case 0:
      output = "tu vois ce que je veux dire";
      nbChars = 27;
      break;
    case 1:
      output = "leve les bras, balance toi";
      nbChars = 26;
      break;
    case 2:
      output = "attend toi au previsible";
      nbChars = 25;
      break;
    case 3:
      output = "ne sois pas surpris par l'inattendu";
      nbChars = 35;
      break;
    case 4:
      output = "travaille dur, tu seras recompense";
      nbChars = 34;
      break;
    case 5:
      output = "tu n'as rien oublie";
      nbChars = 19;
      break;
    case 6:
      output = "essaye encore!";
      nbChars = 14;
      break;
    case 7:
      output = "continue dans cette voie";
      nbChars = 24;
      break;
    case 8:
      output = "si tu veux etre apprecie,meurs ou voyage";
      nbChars = 40;
      break;
  }

  lcd.clear(); // clear screen
  lcd.print(output);
  delay(1000);

  for (int positionCounter = 0; positionCounter < nbChars; positionCounter++) {
    lcd.scrollDisplayLeft();
    delay(500);
  }

  delay(2000);
}

/*
 * get a keycode from the kbd and report back to the
 * host via the serial line.
 */
void loop()
{
  randNumber = random(10);
  unsigned char code;
  for (;;)
  { /* ever */
    code = kbd.read();
    /* send the data back up */
    codebar [index] = code;
    index++;
    i = 0;
    //    Serial.print(code,DEC);
    //    Serial.print(",");

    if (code == 156 ) 
    {
      Serial.println("go");
      while (i<index)
      {
        //    if (codebar[i] != fortune1[i]) thesame1 = false;
        if (codebar[i] != code1001[i]) 
        {
          //        Serial.println("");
          //        Serial.print("Comparaison pas bonne entre ");
          //        Serial.print(codebar[i],DEC);
          //        Serial.print(" et ");
          //        Serial.print(code1001[i],DEC);
          //        Serial.print(" a l index ");
          //        Serial.println(i);
          thesame1001 = false;
        }         



        if (codebar[i] != code1002[i]) thesame1002 = false;
        if (codebar[i] != code1003[i]) thesame1003 = false;
        if (codebar[i] != code1004[i]) thesame1004 = false;
        if (codebar[i] != code1005[i]) thesame1005 = false;
        if (codebar[i] != code1006[i]) thesame1006 = false;
        if (codebar[i] != code1007[i]) thesame1007 = false;
        if (codebar[i] != code1008[i]) thesame1008 = false;
        if (codebar[i] != code1009[i]) thesame1009 = false;
        if (codebar[i] != code1010[i]) thesame1010 = false;


        if (codebar[i] == 156)
        {
          if (thesame1001) {
            Serial.println("code 1001");
            displayString();
          }
          if (thesame1002)   Serial.println("code 1002");
          if (thesame1003)   Serial.println("code 1003");
          if (thesame1004)   Serial.println("code 1004");
          if (thesame1005)   Serial.println("code 1005");
          if (thesame1006)   Serial.println("code 1006");
          if (thesame1007)   Serial.println("code 1007");
          if (thesame1008)   Serial.println("code 1008");
          if (thesame1009)   Serial.println("code 1009");
          if (thesame1010)   Serial.println("code 1010");
          if (!thesame1001 &&!thesame1002 &&!thesame1003 &&!thesame1004 &&!thesame1005 &&!thesame1006 &&!thesame1007 &&!thesame1008 &&!thesame1009 &&!thesame1010) Serial.println("inconnu !!!");

          //          delay(1000);  
        }      
        i++;
      }
      index = 0;
      thesame1001 = true;
      thesame1002 = true;
      thesame1003 = true;
      thesame1004 = true;
      thesame1005 = true;
      thesame1006 = true;
      thesame1007 = true;
      thesame1008 = true;
      thesame1009 = true;
      thesame1010 = true;
    }
  }
}







