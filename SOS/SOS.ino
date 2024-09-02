#define LETTER_LENGTH 3

int redLED = 13;
int shortWAIT = 150;
int longWAIT = 500;
int afterWAIT = 1000;
int repeatNumber = 3;

void setup() {
  pinMode(redLED, OUTPUT);
}

void Signal(int waitTime){
    digitalWrite(redLED, HIGH);
    delay(waitTime);
    digitalWrite(redLED, LOW);
    delay(waitTime);
}

int S[LETTER_LENGTH] = {shortWAIT, shortWAIT, shortWAIT};
int O[LETTER_LENGTH] = {longWAIT, longWAIT, longWAIT};

void writeLetter(int *letter){
  for( int i = 0; i < LETTER_LENGTH; i++){
    Signal(letter[i]);
  }
}

void loop() {
 writeLetter(S);
 writeLetter(O);
 writeLetter(S);
 delay(afterWAIT);

}
