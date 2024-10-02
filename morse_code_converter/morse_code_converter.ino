#define DOT_TIME 200 //time for dot in milliseconds
#define DASH_TIME 600//time for dash in milliseconds
#define SYMBOL_PAUSE 200//pause between dots and dashes
#define LETTER_PAUSE 600//pause between letters
#define WORD_PAUSE 1400//pause between words

//define led pin
const int ledPin = 12;
const int buttonPin = 13;

//define morse code table
const char* morseCodeTable[36] = {
  ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..",  // A-I
  ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", // J-R
  "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--..",        // S-Z
  "-----", ".----", "..---", "...--", "....-", ".....", "-....",   // 0-5
  "--...", "---..", "----."                                       // 6-9
};

const char* englishTable = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

String morseBuffer = "";
String translatedText = "";

char morseToEnglish(String morse){//find letter coresponding to the morse table
  for (int i = 0; i < 36; i++) {
    if(morse == morseCodeTable[i]){
      return englishTable[i];
    }
  }
  return '?';
}

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  Serial.begin(9600);
  Serial.println("Use the button to input morse code: ");
}

void loop() {
  static unsigned long buttonPressedTime = 0;
  static unsigned long buttonReleasedTime = 0;
  static bool buttonWasPressed = false;

  if(digitalRead(buttonPin) == LOW){//check if the button is pressed
    if(!buttonWasPressed){
      buttonReleasedTime = millis();//record the time the button was pressed
      buttonWasPressed = true;
      digitalWrite(ledPin, HIGH);//turn on the led light
    }
  }else{
    if(buttonWasPressed)
      buttonReleasedTime = millis();//recotd the time the button was released
      unsigned long pressDuration = buttonReleasedTime - buttonPressedTime;

      //determine if it was dot or dash
      if(pressDuration < DOT_TIME){
        //ignoring time that is less than dot time
      } else if(pressDuration < DASH_TIME){
        morseBuffer += ".";
      }else{
        morseBuffer += "-";
      }

      buttonWasPressed = false;
      digitalWrite(ledPin, LOW);
      buttonReleasedTime = millis();
    
      }


    //determine the end of letter or word
  if(!buttonWasPressed && buttonReleasedTime > 0){
    unsigned long releaseDuration = millis() - buttonReleasedTime;

    if(releaseDuration > WORD_PAUSE){
      //end of word
      if(morseBuffer.length() > 0){
        char letter = morseToEnglish(morseBuffer);
        translatedText += letter;
        morseBuffer = "";
      }
      translatedText += " ";
      Serial.println(translatedText);
      buttonReleasedTime = 0;
    }else if(releaseDuration > LETTER_PAUSE){
      //end of letter
      if(morseBuffer.length() > 0){
        char letter = morseToEnglish(morseBuffer);
        translatedText += letter;
        Serial.println(translatedText);
        morseBuffer = "";
      }
      buttonReleasedTime = 0;
    }
  }
}