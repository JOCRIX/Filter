unsigned long previousMicros = 0; 

#define b0 19
#define b1 20
#define b2 21
#define b3 37
#define b4 38
#define b5 39
#define b6 40
#define b7 41
#define b8 42
#define b9 2


// constants won't change:
const long samplePeriod = 124;
long test1 = 0, test2 = 0;
int state = 0;

float y0fil = 0;
float y1fil = 0;
float x0fil = 0;
uint8_t outPins[10] = { b0, b1, b2, b3, b4, b5, b6, b7, b8, b9 };


void setup() {
  Serial.begin(500000);
  pinMode(b0, OUTPUT);
  pinMode(b1, OUTPUT);
  pinMode(b2, OUTPUT);
  pinMode(b3, OUTPUT);
  pinMode(b4, OUTPUT);
  pinMode(b5, OUTPUT);
  pinMode(b6, OUTPUT);
  pinMode(b7, OUTPUT);
  pinMode(b8, OUTPUT);
  pinMode(b9, OUTPUT);
  digitalWrite(b0, 0);
  digitalWrite(b1, 0);
  digitalWrite(b2, 0);
  digitalWrite(b3, 0);
  digitalWrite(b4, 0);
  digitalWrite(b5, 0);
  digitalWrite(b6, 0);
  digitalWrite(b7, 0);
  digitalWrite(b8, 0);
  digitalWrite(b9, 0);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, 0);
}

void loop() {

  unsigned long currentMicros = micros();

  if (currentMicros - previousMicros >= samplePeriod) {

    previousMicros = currentMicros;
    x0fil = (float)(analogRead(1));
    y0fil = x0fil * 0.1453631 + y1fil * 0.8546369;
    y1fil = y0fil;

    SetOutput(y0fil);
  //  previousMicros = currentMicros;
    /*
    if (state == 0) {
      test1 = currentMicros;
      state = 1;


    } else if (state == 1) {
      test2 = currentMicros;
        Serial.println(test2 - test1);

        test1 = 0;
        test2 = 0;
      state = 0;

    }
*/
  }
 
}

void SetOutput(float filterOut) {

  uint16_t outputVal = round(filterOut * 0.25);
  uint8_t outVals[10];

    for (uint8_t i = 2; i < 12; i++) {
    outVals[i] = outputVal & (1 << i);
  ////  Serial.print(outVals[i]);
  }
/*
  for (uint8_t i = 0; i < 10; i++) {
    outVals[i] = outputVal & (1 << i);
  ////  Serial.print(outVals[i]);
  }*/
  //Serial.println();
  for (uint8_t j = 0; j < 10; j++) {
    digitalWrite(outPins[j], outVals[j]);
  }
}
