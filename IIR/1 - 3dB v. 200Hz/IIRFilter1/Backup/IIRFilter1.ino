unsigned long previousMicros = 0;

#define b0 19
#define b1 20
#define b2 21
#define b3 37
#define b4 38
#define b5 39
#define b6 40
#define b7 41
#define b8 5
#define b9 4

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
    //x0fil = (float)(analogRead(1) >> 2) ;
    x0fil = (float)analogRead(1);
    x0fil *= 3.3 / 4096;  //Convert ADC reading to voltage (The filter expect a voltage signal as input.)
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
  uint16_t outputVal = round(1024 / 3.3) * filterOut; //Convert filter output to binary and scale to 10 bits.

  bool p0 = outputVal & (1 << 0); //Check bit 0..
  bool p1 = outputVal & (1 << 1);
  bool p2 = outputVal & (1 << 2);
  bool p3 = outputVal & (1 << 3);
  bool p4 = outputVal & (1 << 4);
  bool p5 = outputVal & (1 << 5);
  bool p6 = outputVal & (1 << 6);
  bool p7 = outputVal & (1 << 7);
  bool p8 = outputVal & (1 << 8);
  bool p9 = outputVal & (1 << 9);

<<<<<<< HEAD
    for (uint8_t i = 2; i < 12; i++) {
    outVals[i - 2] = outputVal & (1 << i);
  ////  Serial.print(outVals[i]);
  }
/*
=======
  digitalWrite(b0, p0);
  digitalWrite(b1, p1);
  digitalWrite(b2, p2);
  digitalWrite(b3, p3);
  digitalWrite(b4, p4);
  digitalWrite(b5, p5);
  digitalWrite(b6, p6);
  digitalWrite(b7, p7);
  digitalWrite(b8, p8);
  digitalWrite(b9, p9);

  //delay(1000);

  /*
  for (uint8_t i = 0; i < 10; i++) {
    digitalWrite(outPins[i], (outputVal & (1 << i)));

    //outVals[i] = outputVal & (1 << i);
    ////  Serial.print(outVals[i]);
  }*/
  /*
>>>>>>> 07e32d255bd7d328bdba1417fd14c137b0b1b3ba
  for (uint8_t i = 0; i < 10; i++) {
    outVals[i] = outputVal & (1 << i);
  ////  Serial.print(outVals[i]);
  }*/
  //Serial.println();
  /* for (uint8_t j = 0; j < 10; j++) {
    digitalWrite(outPins[j], outVals[j]);
  }*/
}
