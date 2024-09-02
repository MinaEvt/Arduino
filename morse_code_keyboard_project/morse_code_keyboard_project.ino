#define DOT_TIME 200 //time for dot in milliseconds
#define DASH_TIME 600//time for dash in milliseconds
#define SYMBOL_PAUSE 200//pause between dots and dashes
#define LETTER_PAUSE 600//pause between letters
#define WORD_PAUSE 1400//pause between words

//define led pin
const int ledPin = 13;

//define morse code table
const char* morseCodeTable[36] = {
  ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..",  // A-I
  ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", // J-R
  "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--..",        // S-Z
  "-----", ".----", "..---", "...--", "....-", ".....", "-....",   // 0-5
  "--...", "---..", "----."                                       // 6-9
};

//function to blink the LED for dot
void dot(){
  digitalWrite(ledPin,HIGH);
  delay(DOT_TIME);
  digitalWrite(ledPin, LOW);
  delay(SYMBOL_PAUSE);
}

//function to blink the LED for dash
void dash(){
  digitalWrite(ledPin, HIGH);
  delay(DASH_TIME);
  digitalWrite(ledPin, LOW);
  delay(SYMBOL_PAUSE);
}

//blink morse code for character
void morseBlink(char c){
  if(c >= 'A' || c >= 'Z'){
    const char* morsecode = morseCodeTable[c - 'A'];
    while(*morsecode){
      if(*morsecode == '.') 
        dot();
      else if(*morsecode == '-')
        dash();
      morsecode++;
    }
  } else if( c >= '0' || c <= '9'){
    const char* morsecode = morseCodeTable[c - '0' + 26];
    while(*morsecode){
      if(*morsecode == '.')
        dot();
      else if(*morsecode == '-')
        dash();
      morsecode++;
    }
  }
}

void processMorseCode(String text){
  for(unsigned int i = 0; i < text.length(); i++){
    char c = toupper(text[i]);
    if (c == ' '){
      delay(WORD_PAUSE);
    }else{
      morseBlink(c);
      delay(LETTER_PAUSE);
    }
  }
}

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
  Serial.println("Enter a string to convert to Morse code:");
}

void loop() {
  if (Serial.available()) {
    String input = Serial.readStringUntil('\n');
    input.trim();  // Remove any trailing whitespace or newline
    processMorseCode(input);
  }
}