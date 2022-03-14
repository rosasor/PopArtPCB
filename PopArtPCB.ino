/* Rosa Wheelen PopArtPCB */
/* This code is a work in progress! */

/* Neopixels */
#include <Adafruit_NeoPixel.h>
Adafruit_NeoPixel strip(64, 0, NEO_GRB + NEO_KHZ800);

int numGrid = 30;
int numFrames = 2;

/* Buttons */
int state = 0;
int butPin1 = 1;
boolean butState1 = false;
boolean prevButState1 = false;

/* Timer */
int startTime;
int endTime;
int interval = 1000;
float intervalColors = .1;
int whichFrame = 0;

/* Colors */
int rVal = 155;
int gVal = 0;
int bVal = 55;
boolean isBIncreasing;
boolean isBDecreasing;
boolean isRIncreasing;
boolean isRDecreasing;

char index[30] {
  0, 1, 2, 3, 4,
  5, 6, 7, 8, 9,
  10, 11, 12, 13, 14,
  15, 16, 17, 18, 19,
  20, 21, 22, 23, 24,
  25, 26, 27, 28, 29,
};

char colors[6][3] {
  {255, 0, 0},
  {255, 255, 0},
  {0, 255, 0},
  {0, 0, 255},
  {255, 0 , 200},
  {255, 255, 255},
};

char frames[2][30] {
  {
    3, 3, 3, 3, 3,
    3, 3, 1, 3, 3,
    3, 3, 1, 1, 3,
    0, 0, 1, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
  },
  {
    3, 3, 3, 3, 3,
    3, 3, 5, 3, 3,
    3, 3, 5, 5, 3,
    0, 0, 5, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
  },
};

void setup() {
  /* Timer */
  state = 0;
  startTime = millis();

  /* Colors */
  isBIncreasing = true;
  isBDecreasing = false;
  isRIncreasing = true;
  isRDecreasing = false;

  strip.begin();
  strip.show();
  strip.clear();
  strip.setBrightness(255);
}

void loop() {
  endTime = millis();
  butState1 = digitalRead(butPin1);
  butState1 = debounce(butPin1, prevButState1);

  if (butState1 == true && prevButState1 == false) {
    state = state + 1;
    if (state % 3 == 0) {
      state = 0;
    }
  }
  switch (state) {
    case 0:
      strip.clear();
      strip.show();
      break;
    case 1:
      animation();
      break;

    case 2:
      wtf();
      break;
  }
  prevButState1 = butState1;
}

void animation() {
  if (whichFrame > 1) {
    whichFrame = 0;
  }
  if (endTime - startTime >= interval) {
    for (int i = 0; i < numGrid; i++) {
      int whichLed = i;
      int whichIndex = index[whichLed];
      int whichColor = frames[whichFrame][whichLed];

      int r = colors[whichColor][0];
      int g = colors[whichColor][1];
      int b = colors[whichColor][2];

      strip.setPixelColor(whichIndex, r, g, b);
      strip.show();
      startTime = millis();
    }
    whichFrame = whichFrame + 1;
  }
}


void colors() {
  if (bVal > 254) {
    isBDecreasing = true;
    isBIncreasing = false;
  }
  if (bVal < 2) {
    isBIncreasing = true;
    isBDecreasing = false;
  }
  if (rVal > 254) {
    isRDecreasing = true;
    isRIncreasing = false;
  }
  if (rVal < 2) {
    isRIncreasing = true;
    isRDecreasing = false;
  }

  if (endTime - startTime >= intervalColors) {
    for (int i = 0; i < numGrid; i++) {
      int whichLed = i;
      int whichIndex = index[whichLed];

      strip.setPixelColor(whichIndex, rVal, gVal, bVal);
      strip.show();
      startTime = millis();
    }
    if (isBIncreasing) {
      bVal = bVal + 2;
    }
    if (isBDecreasing) {
      bVal = bVal - 2;
    }
    if (isRIncreasing) {
      rVal = rVal + 2;
    }
    if (isRDecreasing) {
      rVal = rVal - 2;
    }
  }
}

boolean debounce (int aButPin, boolean aPrevState) {
  boolean aButtonState = digitalRead(aButPin);
  if (aButtonState != aPrevState) {
    delay(50);
  }
  return aButtonState;
}
