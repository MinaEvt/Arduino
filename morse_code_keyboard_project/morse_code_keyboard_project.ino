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


bool isLetter(char c){
  return c >= 'A' && c <= 'Z';
}

bool isDigit(char c){
  return  c >= '0' && c <= '9';
}

int getMorseIndex(char c){
  if(isLetter(c))
    return c - 'A';//letter to its Morse code by subtracting 'A' to get the index
  else if(isDigit(c))
    return c - '0' + 26;//digit to its Morse code by subtracting '0' and adding 26 to get the index
  else 
  return -1;//error value
}

//blink morse code for character
void morseBlink(char c){
  
  int index = getMorseIndex(c);
  if(index == -1) return;//invalid character

  const char* morsecode = morseCodeTable[index];
  while(*morsecode){
    if(*morsecode == '.')
      dot();
    else if (*morsecode == '-')
      dash();
    morsecode++;
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