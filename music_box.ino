//notas
#define NOTE_C3  131
#define NOTE_CS3 139 
#define NOTE_D3  147 
#define NOTE_DS3 156 
#define NOTE_E3  165 
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208 
#define NOTE_A3  220 
#define NOTE_AS3 233 
#define NOTE_B3  247 
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311 
#define NOTE_E4  330 
#define NOTE_F4  349 
#define NOTE_FS4 370
#define NOTE_G4  392 
#define NOTE_GS4 415
#define NOTE_A4  440 
#define NOTE_AS4 466 
#define NOTE_B4  494

//tempos
#define WHOLE 1 
#define HALF 0.5 
#define QUARTER 0.25 
#define EIGHTH 0.125
#define SIXTEENTH 0.0625

//calculo BPM em tempo
#define BPM_QUARTER 140
const float time_adjust = 60000*4/BPM_QUARTER;

//pinos
#define interruptPin 2
#define buzzerPin 4
#define ledPin 13

typedef struct { 
  int tone;
  float duration;
} note;

//lista de notas acompanhadas de sua duração
const note notes[] {
  {NOTE_E4, QUARTER}, {NOTE_E4, QUARTER}, {NOTE_F4, QUARTER}, {NOTE_G4, QUARTER}, 
  {NOTE_G4, QUARTER}, {NOTE_F4, QUARTER}, {NOTE_E4, QUARTER}, {NOTE_D4, QUARTER}, 
  {NOTE_C4, QUARTER}, {NOTE_C4, QUARTER}, {NOTE_D4, QUARTER}, {NOTE_E4, QUARTER}, 
  {NOTE_E4, QUARTER+EIGHTH}, {NOTE_D4, EIGHTH}, {NOTE_D4, HALF}, 
  
  {NOTE_E4, QUARTER}, {NOTE_E4, QUARTER}, {NOTE_F4, QUARTER}, {NOTE_G4, QUARTER}, 
  {NOTE_G4, QUARTER}, {NOTE_F4, QUARTER}, {NOTE_E4, QUARTER}, {NOTE_D4, QUARTER}, 
  {NOTE_C4, QUARTER}, {NOTE_C4, QUARTER}, {NOTE_D4, QUARTER}, {NOTE_E4, QUARTER}, 
  {NOTE_D4, QUARTER+EIGHTH}, {NOTE_C4, EIGHTH}, {NOTE_C4, HALF},
  
  {NOTE_D4, QUARTER}, {NOTE_D4, QUARTER}, {NOTE_E4, QUARTER}, {NOTE_C4, QUARTER},
  {NOTE_D4, QUARTER}, {NOTE_E4, EIGHTH}, {NOTE_F4, EIGHTH}, {NOTE_E4, QUARTER},
  {NOTE_C4, QUARTER}, {NOTE_D4, QUARTER}, {NOTE_E4, EIGHTH}, {NOTE_F4, EIGHTH},
  {NOTE_E4, QUARTER}, {NOTE_D4, QUARTER}, {NOTE_C4, QUARTER}, {NOTE_D4, QUARTER}, 
  {NOTE_G3, HALF}, {NOTE_E4, QUARTER}, {NOTE_E4, QUARTER}, {NOTE_F4, QUARTER}, 
  {NOTE_G4, QUARTER}, {NOTE_G4, QUARTER}, {NOTE_F4, QUARTER}, {NOTE_E4, QUARTER}, 
  {NOTE_D4, QUARTER}, {NOTE_C4, QUARTER}, {NOTE_C4, QUARTER}, {NOTE_D4, QUARTER}, 
  {NOTE_E4, QUARTER}, {NOTE_D4, QUARTER+EIGHTH}, {NOTE_C4, EIGHTH}, {NOTE_C4, HALF}
};

const int notes_length = sizeof(notes)/sizeof(note);

//variaveis botão
bool state = LOW;
bool currentState = false; 
bool lastState = false;  
unsigned long lastDebounceTime = 0;  
const int debounceDelay = 250; 

void setup() {
  pinMode(buzzerPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), interrupt, FALLING); 
}

void loop() {
  for (int i=0; i<notes_length && state==HIGH; i++) { 
    int tone_to_play = notes[i].tone;
    float duration_to_play = notes[i].duration;
    tone(buzzerPin, tone_to_play); 
    delay(time_adjust * duration_to_play); 
    noTone(buzzerPin);
    delay(2);
  }
}

void interrupt() {
  currentState = !state;
  if (currentState != lastState) {
    lastDebounceTime = millis();
  }
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (currentState != state) {
      state = !state;
    }
  }
  lastState = currentState;
  
  digitalWrite(ledPin, state);

  if (state == LOW) {
    noTone(buzzerPin);
  }
}
