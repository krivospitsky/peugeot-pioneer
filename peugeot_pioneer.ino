#define fw 2
#define vol_up 3
#define source 4
#define vol_dn 5
#define back 6
#define wh_1 7
#define wh_2 8
#define connect_shift 13
#define pioneer_out 10


int wh_1_Last = HIGH;
int n = HIGH;


void setup() {
  Serial.begin(9600);
  pinMode(fw, INPUT_PULLUP);
  pinMode(vol_up, INPUT_PULLUP);
  pinMode(source, INPUT_PULLUP);
  pinMode(vol_dn, INPUT_PULLUP);
  pinMode(back, INPUT_PULLUP);
  pinMode(wh_1, INPUT_PULLUP);
  pinMode(wh_2, INPUT_PULLUP);
  pinMode(connect_shift, INPUT);
  TCCR1B = TCCR1B & B11111000 | B00000001;
  pinMode(pioneer_out, OUTPUT);   
}

void loop() {
  if (digitalRead(fw)==0){
    Serial.print("fw\n");
    analogWrite(pioneer_out, 69);
    return;
  }

  if (digitalRead(back)==0){
    Serial.print("back\n");
    analogWrite(pioneer_out, 87);
    return;
  }

  if (digitalRead(vol_up)==0){
    delay(100);
    if (digitalRead(vol_up)==0 && digitalRead(vol_dn)==0){
      Serial.print("mute\n");
      analogWrite(pioneer_out, 31);
      delay(150);
      return;
    }
    Serial.print("vol_up\n");
    analogWrite(pioneer_out, 94);
    return;
  }

  if (digitalRead(vol_dn)==0){
    delay(100);
    if (digitalRead(vol_up)==0 && digitalRead(vol_dn)==0){
      Serial.print("mute\n");
      analogWrite(pioneer_out, 31);
      delay(150);
      return;
    }
    Serial.print("vol_dn\n");  
      analogWrite(pioneer_out, 115);
    return;
  }

  
  if (digitalRead(source)==0){
    Serial.print("source\n");
    analogWrite(pioneer_out, 17);
    return;
  }

  n = digitalRead(wh_1);
  if ((wh_1_Last == LOW) && (n == HIGH)) {
    if (digitalRead(wh_2) == LOW) {
      Serial.print ("wh_1\n");
      pinMode(connect_shift, OUTPUT);
      analogWrite(pioneer_out, 74);
      delay(100);
      analogWrite(pioneer_out, 166);
      pinMode(connect_shift, INPUT);
      wh_1_Last = n;
      return;
    } else {
      Serial.print ("wh_2\n");
      pinMode(connect_shift, OUTPUT);
      analogWrite(pioneer_out, 87);
      delay(100);
      analogWrite(pioneer_out, 166);
      pinMode(connect_shift, INPUT);
      wh_1_Last = n;
      return;
    }
  } 
  wh_1_Last = n;

  analogWrite(pioneer_out, 166);
}
