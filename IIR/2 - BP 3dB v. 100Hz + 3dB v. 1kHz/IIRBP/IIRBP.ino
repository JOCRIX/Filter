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

float y0fil = 0, y1fil = 0, y2fil = 0, y3fil = 0, y4fil = 0, y5fil = 0, y6fil = 0, y7fil = 0, y8fil = 0, y9fil = 0, y10fil = 0;

float x0fil = 0, x1fil = 0, x2fil = 0, x3fil = 0, x4fil = 0, x5fil = 0, x6fil = 0, x7fil = 0, x8fil = 0, x9fil = 0, x10fil = 0;

float b0f = 0.0004519;
float b1f = 0.007442;
float b2f = -0.08589;
float b3f = 0.1608;
float b4f = -0.09249;
float b5f = -0.03386;
float b6f = 0.05398;
float b7f = -0.01356;
float b8f = -0.001149;
float b9f = 7.47E-19;

float a0f = 1.0;
float a1f = -7.546;
float a2f = 25.84;
float a3f = -52.96;
float a4f = 72.12;
float a5f = -68.24;
float a6f = 45.46;
float a7f = -21.06;
float a8f = 6.492;
float a9f = -1.202;
float a10f = 0.1015;


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

    y0fil = x1fil * b0f + x2fil * b1f + x3fil * b2f + x4fil * b3f + x5fil * b4f + x6fil * b5f + x7fil * b6f + x8fil * b7f + x9fil * b8f + x10fil * b9f;
    y0fil += -1*y1fil * a1f - y2fil * a2f - y3fil * a3f - y4fil * a4f - y5fil * a5f - y6fil * a6f - y7fil * a7f - y8fil * a8f - y9fil * a9f - y10fil * a10f;    
   // y0fil = y0fil * (1 / a0f);

    y1fil = y0fil;
    y2fil = y1fil;
    y3fil = y2fil;
    y4fil = y3fil;
    y5fil = y4fil;
    y6fil = y5fil;
    y7fil = y6fil;
    y8fil = y7fil;
    y9fil = y8fil;
    y10fil = y9fil;

    x1fil = x0fil;
    x2fil = x1fil;
    x3fil = x2fil;
    x4fil = x3fil;
    x5fil = x4fil;
    x6fil = x5fil;
    x7fil = x6fil;
    x8fil = x7fil;
    x9fil = x8fil;
    x10fil = x9fil;

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
  uint16_t outputVal = round(1024 / 3.3) * filterOut;  //Convert filter output to binary and scale to 10 bits.

  Serial.println(outputVal);

  bool p0 = outputVal & (1 << 0);  //Check bit 0..
  bool p1 = outputVal & (1 << 1);
  bool p2 = outputVal & (1 << 2);
  bool p3 = outputVal & (1 << 3);
  bool p4 = outputVal & (1 << 4);
  bool p5 = outputVal & (1 << 5);
  bool p6 = outputVal & (1 << 6);
  bool p7 = outputVal & (1 << 7);
  bool p8 = outputVal & (1 << 8);
  bool p9 = outputVal & (1 << 9);
  /*
    for (uint8_t i = 2; i < 12; i++) {
    outVals[i - 2] = outputVal & (1 << i);
  ////  Serial.print(outVals[i]);
  }*/

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
