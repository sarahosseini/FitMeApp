// Title : FitMe
// Group : 1
// Date : November 21, 2017
// Waterloo SE 101 Project

//include all needed header files for the screen
#include <Elegoo_GFX.h>    // Core graphics library
#include <Elegoo_TFTLCD.h> // Hardware-specific library
#include <TouchScreen.h>

#define LCD_CS A3 // Chip Select goes to Analog 3
#define LCD_CD A2 // Command/Data goes to Analog 2
#define LCD_WR A1 // LCD Write goes to Analog 1
#define LCD_RD A0 // LCD Read goes to Analog 0

#define LCD_RESET A4 // Can alternately just connect to Arduino's reset pin

#if defined(__SAM3X8E__)
#undef __FlashStringHelper::F(string_literal)
#define F(string_literal) string_literal
#endif

#define STATUS_X 10
#define STATUS_Y 65
#define TEXT_X 10
#define TEXT_Y 10
#define TEXT_W 220
#define TEXT_H 50
#define TEXT_TSIZE 2.5
#define TEXT_TCOLOR ILI9341_WHITE
#define TEXT_LEN 12
char textfield[TEXT_LEN + 1] = "";
uint8_t textfield_i = 0;

#define YP A3  // must be an analog pin, use "An" notation!
#define XM A2  // must be an analog pin, use "An" notation!
#define YM 9   // can be a digital pin
#define XP 8   // can be a digital pin
#define BUTTON_X 40
#define BUTTON_Y 100
#define BUTTON_W 60
#define BUTTON_H 30
#define BUTTON_SPACING_X 20
#define BUTTON_SPACING_Y 20
#define BUTTON_TEXTSIZE 2

#define TS_MINX 120
#define TS_MAXX 900

#define TS_MINY 70
#define TS_MAXY 920

TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

#define LCD_CS A3
#define LCD_CD A2
#define LCD_WR A1
#define LCD_RD A0
#define LCD_RESET A4

#define  BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

// Color definitions
#define ILI9341_BLACK       0x0000      /*   0,   0,   0 */
#define ILI9341_NAVY        0x000F      /*   0,   0, 128 */
#define ILI9341_DARKGREEN   0x03E0      /*   0, 128,   0 */
#define ILI9341_DARKCYAN    0x03EF      /*   0, 128, 128 */
#define ILI9341_MAROON      0x7800      /* 128,   0,   0 */
#define ILI9341_PURPLE      0x780F      /* 128,   0, 128 */
#define ILI9341_OLIVE       0x7BE0      /* 128, 128,   0 */
#define ILI9341_LIGHTGREY   0xC618      /* 192, 192, 192 */
#define ILI9341_DARKGREY    0x7BEF      /* 128, 128, 128 */
#define ILI9341_BLUE        0x001F      /*   0,   0, 255 */
#define ILI9341_GREEN       0x07E0      /*   0, 255,   0 */
#define ILI9341_CYAN        0x07FF      /*   0, 255, 255 */
#define ILI9341_RED         0xF800      /* 255,   0,   0 */
#define ILI9341_MAGENTA     0xF81F      /* 255,   0, 255 */
#define ILI9341_YELLOW      0xFFE0      /* 255, 255,   0 */
#define ILI9341_WHITE       0xFFFF      /* 255, 255, 255 */
#define ILI9341_ORANGE      0xFD20      /* 255, 165,   0 */
#define ILI9341_GREENYELLOW 0xAFE5      /* 173, 255,  47 */
#define ILI9341_PINK        0xF81F

Elegoo_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);

// Size definitions
#define BOXSIZE 1500
#define PENRADIUS 10
int oldcolor, currentcolor;

//buttons
Elegoo_GFX_Button buttons[15];
char buttonlabels[15][5] = {"Next", " ", " ", "1", "2", "3", "4", "5", "6", "7", "8", "9", " ", "0", " " };
uint16_t buttoncolors[15] = {ILI9341_DARKGREEN, ILI9341_BLACK, ILI9341_BLACK,
                             ILI9341_BLUE, ILI9341_BLUE, ILI9341_BLUE,
                             ILI9341_BLUE, ILI9341_BLUE, ILI9341_BLUE,
                             ILI9341_BLUE, ILI9341_BLUE, ILI9341_BLUE,
                             ILI9341_BLACK, ILI9341_BLUE, ILI9341_BLACK
                            };

//touch screen
#define MINPRESSURE 10
#define MAXPRESSURE 1000

// for now the time elapsed is a constant in minutes
#define TIME_DIFF 30

// Global variables
int counter = 0;
int i = 0;

int age[5];
int inputAge = 0;
int ageIdx = 0;

int weight[5];
int weightIdx = 0;
int inputWeight = 0;

int height[5];
int heightIdx = 0;
int inputHeight = 0;

int steps[6];
unsigned int inputSteps = 0;
int stepsIdx = 0;

double avgStrLen = 0.0;
double distanceWalkedKM = 0.0;
double distanceMiles = 0.0;
double elapsedTime = 0.0;
double CalBurntMile = 0.0;
double calories = 0.0;
double calPerStep = 0.0;
double avgSpeedMi = 0.0;
double avgSpeedKm = 0.0;

// setup function for the screen
void setup(void) {
  Serial.begin(9600);

  tft.reset();

  uint16_t identifier = tft.readID();
  if (identifier == 0x9325) {
    Serial.println(F("Found ILI9325 LCD driver"));
  } else if (identifier == 0x9328) {
    Serial.println(F("Found ILI9328 LCD driver"));
  } else if (identifier == 0x4535) {
    Serial.println(F("Found LGDP4535 LCD driver"));
  } else if (identifier == 0x7575) {
    Serial.println(F("Found HX8347G LCD driver"));
  } else if (identifier == 0x9341) {
    Serial.println(F("Found ILI9341 LCD driver"));
  } else if (identifier == 0x8357) {
    Serial.println(F("Found HX8357D LCD driver"));
  } else if (identifier == 0x0101)
  {
    identifier = 0x9341;
    Serial.println(F("Found 0x9341 LCD driver"));
  } else {
    Serial.print(F("Unknown LCD driver chip: "));
    identifier = 0x9328;
  }

  tft.begin(identifier);
  tft.setRotation(2);

  //change colour of background
  tft.fillScreen(BLACK);


  tft.fillRect(BOXSIZE * 6, 400, BOXSIZE, BOXSIZE, GREEN);
  tft.drawRect(BOXSIZE * 5, 400, BOXSIZE, BOXSIZE, WHITE);
  currentcolor = WHITE;

  pinMode(13, OUTPUT);

  //set colours and size for text
  tft.setTextColor(WHITE);
  tft.setTextSize(TEXT_TSIZE);

  //print welcome message
  tft.println("HELLO!");
  tft.println(" ");
  tft.println("Welcome to FitMe by RPS.Co.");
    tft.println(" ");
  tft.println("Our goal is to make sure you become the person you want to  become by getting   the body you want.");
    tft.println(" ");
  tft.println("To ensure this, we  need to ask a few   questions first.");
  

  //wait for user to read message
  delay(5000);
  Serial.begin(9600);

  digitalWrite(13, HIGH);
  TSPoint p = ts.getPoint();
  digitalWrite(13, LOW);

  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);

  if (p.y < BOXSIZE) {
    oldcolor = GREEN;

    if (p.x < BOXSIZE * 3) {
      //  currentcolor = BLACK;
      tft.fillScreen(BLACK);
      //  tft.fillCircle(p.x, p.y, PENRADIUS, currentcolor);
      tft.setCursor(0, 0);
      tft.setTextSize(TEXT_TSIZE);
      tft.println("Enter your Age");
    }

  }

  memset(age, -1, sizeof(int)*5);
  memset(weight, -1, sizeof(int)*5);
  memset(height, -1, sizeof(int)*5);
  memset(steps, -1, sizeof(int)*8);

}

// Print something in the mini status bar with either flashstring
void status(const __FlashStringHelper *msg) {
  tft.fillRect(STATUS_X, STATUS_Y, 240, 8, ILI9341_BLACK);
  tft.setCursor(STATUS_X, STATUS_Y);
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(1);
  tft.print(msg);
}
// or charstring
void status(char *msg) {
  tft.fillRect(STATUS_X, STATUS_Y, 240, 8, ILI9341_BLACK);
  tft.setCursor(STATUS_X, STATUS_Y);
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(1);
  tft.print(msg);
}

int firsttime = 1;
int screen = 1;

void something(int a);

//create buttons function
void createButtons(void)
{
  // create buttons
  for (uint8_t row = 0; row < 5; row++) {
    for (uint8_t col = 0; col < 3; col++) {
      buttons[col + row * 3].initButton(&tft, BUTTON_X + col * (BUTTON_W + BUTTON_SPACING_X),
                                        BUTTON_Y + row * (BUTTON_H + BUTTON_SPACING_Y), // x, y, w, h, outline, fill, text
                                        BUTTON_W, BUTTON_H, ILI9341_WHITE, buttoncolors[col + row * 3], ILI9341_WHITE,
                                        buttonlabels[col + row * 3], BUTTON_TEXTSIZE);
      buttons[col + row * 3].drawButton();
    }

  }

  tft.drawRect(TEXT_X, TEXT_Y, TEXT_W, TEXT_H, ILI9341_WHITE);
}

// called continuously in a loop by the main function
void loop(void)
{

  digitalWrite(13, HIGH);
  TSPoint p = ts.getPoint();
  digitalWrite(13, LOW);

  // if sharing pins, you'll need to fix the directions of the touchscreen pins
  //pinMode(XP, OUTPUT);
  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);


  if (firsttime != 0) {
    tft.fillScreen(BLACK);
    firsttime = 0;
    tft.setCursor(0, 0);
    tft.setTextSize(TEXT_TSIZE);

    tft.println("Enter your age!");
    delay(3000);
  }

  // call different screens based on input
  ageScreen();
  weightScreen();
  heightScreen();
  startWalking();
  calorieCount();
}

int once = 1;

// reset function to for invalid inputs
void callReset(void) {

  tft.fillScreen(BLACK);
  tft.println("Invalid input!!!");
  tft.println("");
  tft.println("Please enter data   again...");
  delay(3000);
  counter = 0;

  inputAge = 0;
  ageIdx = 0;

  i = 0;

  weightIdx = 0;
  inputWeight = 0;

  heightIdx = 0;
  inputHeight = 0;

  inputSteps = 0;
  stepsIdx = 0;

  calPerStep = 0.0;
  calories = 0.0;
  CalBurntMile = 0.0;
  avgStrLen = 0.0;

  textfield_i = 0;
  memset(textfield, 0, TEXT_LEN);
  memset(age, -1, sizeof(int)*5);
  memset(weight, -1, sizeof(int)*5);
  memset(height, -1, sizeof(int)*5);
  memset(steps, -1, sizeof(int)*8);

  screen = 1;
  once = 1;
  firsttime = 1;

  tft.fillScreen(BLACK);
  tft.setCursor(0, 0);

  // tft.setCursor(TEXT_X, TEXT_Y + 10);
  tft.setTextColor(TEXT_TCOLOR, ILI9341_BLACK);
  tft.setTextSize(TEXT_TSIZE);

}



// screen 1; age
void ageScreen()
{
  if (screen == 1) {

    digitalWrite(13, HIGH);
    TSPoint p = ts.getPoint();
    digitalWrite(13, LOW);

    // if sharing pins, you'll need to fix the directions of the touchscreen pins
    //pinMode(XP, OUTPUT);
    pinMode(XM, OUTPUT);
    pinMode(YP, OUTPUT);

    if (once) {
      tft.fillScreen(BLACK);
      textfield_i = 0;
      memset(textfield, 0, TEXT_LEN);
      createButtons();
      once = 0;
      i = 0;
    }

    if (inputAge == 0) {
      if (p.z > MINPRESSURE && p.z < MAXPRESSURE) {
        // scale from 0->1023 to tft.width
        p.x = map(p.x, TS_MINX, TS_MAXX, tft.width(), 0);
        p.y = (tft.height() - map(p.y, TS_MINY, TS_MAXY, tft.height(), 0));
      }

      for (uint8_t b = 0; b < 15; b++) {
        if (buttons[b].contains(p.x, p.y)) {
          //Serial.print("Pressing: "); Serial.println(b);
          buttons[b].press(true);  // tell the button it is pressed
        } else {
          buttons[b].press(false);  // tell the button it is NOT pressed
        }
      }

      // now we can ask the buttons if their state has changed
      for (uint8_t b = 0; b < 15; b++) {
        if (buttons[b].justReleased()) {
          // Serial.print("Released: "); Serial.println(b);
          buttons[b].drawButton();
        }

        if (buttons[b].justPressed()) {
          buttons[b].drawButton(true);

          // if a numberpad button, append the relevant # to the textfield
          if (b >= 3 && (b != 12 || b != 14)) {
            if (textfield_i < TEXT_LEN) {
              textfield[textfield_i] = buttonlabels[b][0];
              textfield_i++;

              // Dont save anything greater than 3 digits
              if (i < 3) {

                if (b == 13) {
                  age[i] = 0;
                } else {
                  age[i] = b - 2;
                }

                i++;
              }

            }
          }

          // update the text field
          Serial.println(textfield);
          tft.setCursor(TEXT_X + 2, TEXT_Y + 10);
          tft.setTextColor(TEXT_TCOLOR, ILI9341_BLACK);
          tft.setTextSize(TEXT_TSIZE);
          tft.print(textfield);

          // Next button pressed
          if (b == 0) {
            tft.fillScreen(BLACK);

            // find how many digits were entered
            for (int j = 0; j < 5 ; j++) {
              if (age[j] == -1) {
                ageIdx = j - 1;

                break;
              }
            }
            if (ageIdx != 1) {
              //Error - report incorrect age
              callReset();
              return;

            } else {
              // Age can be two digits only
              inputAge = (age[0] * 10) + age[1];

              //clear screen
              tft.fillScreen(BLACK);
              tft.setCursor(0, 0);

              //tft.setCursor(TEXT_X, TEXT_Y + 10);
              tft.setTextColor(TEXT_TCOLOR, ILI9341_BLACK);
              tft.setTextSize(TEXT_TSIZE);

              tft.println("Your age is : ");
              tft.println(inputAge);
              delay(2000);

            }
            // now switching screens to next one;
            screen = 2;
            once = 1;

          } // b ==0
        }
      }
    }
  } // screen = 1
}


// screen 2; weight
void weightScreen(void)
{
  if (screen == 2) {

    digitalWrite(13, HIGH);
    TSPoint p = ts.getPoint();
    digitalWrite(13, LOW);

    // if sharing pins, you'll need to fix the directions of the touchscreen pins
    //pinMode(XP, OUTPUT);
    pinMode(XM, OUTPUT);
    pinMode(YP, OUTPUT);

    if (once) {
      tft.fillScreen(BLACK);
      tft.setCursor(0, 0);
      tft.setTextSize(TEXT_TSIZE);

      tft.println("Enter your weight:");
      tft.println("(In pounds)");
      delay(3000);
      tft.fillScreen(BLACK);
      memset(textfield, 0, TEXT_LEN);
      textfield_i = 0;
      createButtons();
      once = 0;
      i = 0;
    }

    if (inputWeight == 0) {
      if (p.z > MINPRESSURE && p.z < MAXPRESSURE) {
        // scale from 0->1023 to tft.width
        p.x = map(p.x, TS_MINX, TS_MAXX, tft.width(), 0);
        p.y = (tft.height() - map(p.y, TS_MINY, TS_MAXY, tft.height(), 0));
      }

      for (uint8_t b = 0; b < 15; b++) {
        if (buttons[b].contains(p.x, p.y)) {
          //Serial.print("Pressing: "); Serial.println(b);
          buttons[b].press(true);  // tell the button it is pressed
        } else {
          buttons[b].press(false);  // tell the button it is NOT pressed
        }
      }

      // now we can ask the buttons if their state has changed
      for (uint8_t b = 0; b < 15; b++) {
        if (buttons[b].justReleased()) {
          // Serial.print("Released: "); Serial.println(b);
          buttons[b].drawButton();
        }

        if (buttons[b].justPressed()) {
          buttons[b].drawButton(true);

          // if a numberpad button, append the relevant # to the textfield
          if (b >= 3 && (b != 12 || b != 14)) {
            if (textfield_i < TEXT_LEN) {
              textfield[textfield_i] = buttonlabels[b][0];
              textfield_i++;
              //textfield[textfield_i] = 0; // zero terminate

              if (i < 4) {
                if (b == 13) {
                  weight[i] = 0;
                } else {
                  weight[i] = b - 2;
                }

                i++;
              }
            }
          }

          // update the current text field
          Serial.println(textfield);
          tft.setCursor(TEXT_X + 2, TEXT_Y + 10);
          tft.setTextColor(TEXT_TCOLOR, ILI9341_BLACK);
          tft.setTextSize(TEXT_TSIZE);
          tft.print(textfield);

          // Next button pressed
          if (b == 0) {
            //tft.fillScreen(BLUE);

            for (int k = 0; k < 5; k++) {
              if (weight[k] == -1) {
                weightIdx = k - 1;
                break;
              }
            }

            // convert to number from array
            inputWeight = 0;
            for (int ii = 0; ii <= weightIdx; ii++) {
              inputWeight = (inputWeight * 10) + weight[ii];
            }

            // check for errors & call reset()
            if ((inputWeight > 400) || (inputWeight < 50)) {

              callReset();
              return;
            }

            tft.fillScreen(BLACK);
            tft.setCursor(0, 0);


            //   tft.setCursor(TEXT_X, TEXT_Y + 10);
            tft.setTextColor(TEXT_TCOLOR, ILI9341_BLACK);
            tft.setTextSize(TEXT_TSIZE);


            tft.println("Your weight is : ");
            tft.println(inputWeight);
            tft.println("in pounds");
            delay(2000);
            //  }
            // now switching screens to next one;
            screen = 3;
            once = 1;

          } // b ==0
        }
      }
    }
  } // screenClear = 0
}





// screen 3; height
void heightScreen(void)
{
  if (screen == 3) {

    digitalWrite(13, HIGH);
    TSPoint p = ts.getPoint();
    digitalWrite(13, LOW);

    // if sharing pins, you'll need to fix the directions of the touchscreen pins
    //pinMode(XP, OUTPUT);
    pinMode(XM, OUTPUT);
    pinMode(YP, OUTPUT);

    if (once) {
      tft.fillScreen(BLACK);
      tft.setCursor(0, 0);
      tft.println("Enter your height :");
      tft.println("(In cms)");

      delay(3000);
      tft.fillScreen(BLACK);
      memset(textfield, 0, TEXT_LEN);
      textfield_i = 0;
      createButtons();
      once = 0;
      i = 0;
    }

    if (inputHeight == 0) {
      if (p.z > MINPRESSURE && p.z < MAXPRESSURE) {
        // scale from 0->1023 to tft.width
        p.x = map(p.x, TS_MINX, TS_MAXX, tft.width(), 0);
        p.y = (tft.height() - map(p.y, TS_MINY, TS_MAXY, tft.height(), 0));
      }

      for (uint8_t b = 0; b < 15; b++) {
        if (buttons[b].contains(p.x, p.y)) {
          //Serial.print("Pressing: "); Serial.println(b);
          buttons[b].press(true);  // tell the button it is pressed
        } else {
          buttons[b].press(false);  // tell the button it is NOT pressed
        }
      }

      // now we can ask the buttons if their state has changed
      for (uint8_t b = 0; b < 15; b++) {
        if (buttons[b].justReleased()) {
          // Serial.print("Released: "); Serial.println(b);
          buttons[b].drawButton();
        }

        if (buttons[b].justPressed()) {
          buttons[b].drawButton(true);

          // if a numberpad button, append the relevant # to the textfield
          if (b >= 3 && (b != 12 || b != 14)) {

            if (textfield_i < TEXT_LEN) {
              textfield[textfield_i] = buttonlabels[b][0];
              textfield_i++;
              //textfield[textfield_i] = 0; // zero terminate

              if (i < 5) {

                // value = 0
                if (b == 13) {
                  height[i] = 0;
                } else {

                  height[i] = b - 2;
                }

                i++;
              }
            }
          }

          // update the current text field
          Serial.println(textfield);
          tft.setCursor(TEXT_X + 2, TEXT_Y + 10);
          tft.setTextColor(TEXT_TCOLOR, ILI9341_BLACK);
          tft.setTextSize(TEXT_TSIZE);
          tft.print(textfield);

          // Next button pressed
          if (b == 0) {
            //tft.fillScreen(BLUE);

            for (int k = 0; k < 5 ; k++) {
              if (height[k] == -1) {
                heightIdx = k - 1;
                break;
              }
            }

            // convert to number from array
            inputHeight = 0;
            for (int ii = 0; ii <= heightIdx; ii++) {
              inputHeight = (inputHeight * 10) + height[ii];
            }

            if ((inputHeight > 240) || (inputHeight < 24)) {
              callReset();
              return;
            }


            tft.fillScreen(BLACK);
            tft.setCursor(0, 0);


           // tft.setCursor(TEXT_X+2, TEXT_Y + 10);
            tft.setTextColor(TEXT_TCOLOR, ILI9341_BLACK);
            tft.setTextSize(TEXT_TSIZE);

            tft.println("Your height is : ");
            tft.println(inputHeight);
            tft.println("in cms");

            delay(2000);
            //  }
            // now switching screens to next one;
            screen = 4;
            once = 1;

          } // b ==0
        }
      }
    }
  } // screenClear = 0
}


// screen 4; step counter
void startWalking(void)
{
  if (screen == 4) {
    digitalWrite(13, HIGH);
    TSPoint p = ts.getPoint();
    digitalWrite(13, LOW);

    // if sharing pins, you'll need to fix the directions of the touchscreen pins
    //pinMode(XP, OUTPUT);
    pinMode(XM, OUTPUT);
    pinMode(YP, OUTPUT);

    if (once) {
      tft.fillScreen(BLACK);
      tft.setCursor(0, 0);

      tft.println("Enter steps taken : ");
      tft.println("(from pedometer     reading)");
      
      delay(3000);
      tft.fillScreen(BLACK);
      memset(textfield, 0, TEXT_LEN);
      textfield_i = 0;
      createButtons();
      once = 0;
      i = 0;
    }

    if (inputSteps == 0) {
      if (p.z > MINPRESSURE && p.z < MAXPRESSURE) {
        // scale from 0->1023 to tft.width
        p.x = map(p.x, TS_MINX, TS_MAXX, tft.width(), 0);
        p.y = (tft.height() - map(p.y, TS_MINY, TS_MAXY, tft.height(), 0));
      }

      for (uint8_t b = 0; b < 15; b++) {
        if (buttons[b].contains(p.x, p.y)) {
          //Serial.print("Pressing: "); Serial.println(b);
          buttons[b].press(true);  // tell the button it is pressed
        } else {
          buttons[b].press(false);  // tell the button it is NOT pressed
        }
      }

      // now we can ask the buttons if their state has changed
      for (uint8_t b = 0; b < 15; b++) {
        if (buttons[b].justReleased()) {
          // Serial.print("Released: "); Serial.println(b);
          buttons[b].drawButton();
        }

        if (buttons[b].justPressed()) {
          buttons[b].drawButton(true);

          // if a numberpad button, append the relevant # to the textfield
          if (b >= 3 && (b != 12 || b != 14)) {

            if (textfield_i < TEXT_LEN) {
              textfield[textfield_i] = buttonlabels[b][0];
              textfield_i++;
              //textfield[textfield_i] = 0; // zero terminate

              // value = 0
              if (b == 13) {
                steps[i] = 0;
              } else {
                steps[i] = b - 2;
              }
              i++;

            }
          }

          Serial.println(textfield);
          tft.setCursor(TEXT_X + 2, TEXT_Y + 10);
          tft.setTextColor(TEXT_TCOLOR, ILI9341_BLACK);
          tft.setTextSize(TEXT_TSIZE);
          tft.print(textfield);

          // Next button pressed
          if (b == 0) {

            for (int k = 0; k < 8 ; k++) {
              if (steps[k] == -1) {
                stepsIdx = k - 1;
                break;
              }
            }

            // convert to number from array
            inputSteps = 0;
            for (int ii = 0; ii <= stepsIdx; ii++) {
              inputSteps = (inputSteps * 10) + steps[ii];
            }

            tft.fillScreen(BLACK);
            tft.setCursor(0, 0);

            tft.setTextColor(TEXT_TCOLOR, ILI9341_BLACK);
            tft.setTextSize(TEXT_TSIZE);

            tft.println("You have taken ");
            tft.println(inputSteps);
            tft.println("steps");
            delay(3000);

            screen = 5;
            once = 1;
          }

        }
      }

    }
  }
}


//screen 5 ; count calories and display results
void calorieCount(void) {
  if (screen == 5) {

    if (once) {
      tft.fillScreen(BLACK);
      tft.setCursor(0, 0);

      //calculate ...

      avgStrLen = inputHeight * 0.413;

      distanceWalkedKM = (avgStrLen * inputSteps) / 100000; // in KMs

      distanceMiles = distanceWalkedKM / 1.6;

      elapsedTime = TIME_DIFF; // in mins

      avgSpeedMi = distanceMiles / (elapsedTime / 60); // miles/hr

      avgSpeedKm = avgSpeedMi * 1.6;

      if (avgSpeedMi > 3.1) {
        // running
        CalBurntMile = inputWeight * 0.72;

      } else if (avgSpeedMi < 0.02) {
        // stopped or too slow to calculate
        CalBurntMile  = 0.0;

      } else {
        // walking
        CalBurntMile = (inputWeight * 0.57);
      }

      calPerStep = (CalBurntMile / 2000); // avg 2000 steps for a mile
      calories = (calPerStep * inputSteps);


      //output results to user
      tft.println("Steps taken");
      tft.println(inputSteps);
      tft.println(" ");
    
      tft.println("Calories burnt in   total : ");
      tft.println(calories);
      tft.println(" ");
      tft.println("Calories burnt per  step : ");
      tft.println(calPerStep);
      tft.println(" ");
      tft.println("Time taken (in      mins) : ");
      tft.println(elapsedTime);
      tft.println(" ");
      tft.println("Average speed (in   kms) : ");
      tft.println(avgSpeedKm);

      once = 0;

    }
  }
}

