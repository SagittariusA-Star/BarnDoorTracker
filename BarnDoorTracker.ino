#include <AccelStepper.h>
#include <MultiStepper.h>

#include <FiniteStateMachine.h>
#include <math.h>

// Debug mode; 0 = off, 1 = on. 
#define DEBUG 1

// Input pins
#define PIN_IN_DIR  8
#define PIN_IN_STEP 9

// Output pins
#define PIN_OUT_DIR       A3
#define PIN_OUT_SIDEREAL  A4
#define PIN_OUT_FAST      A5

// Physical constants
#define SIDEREAL_DAY 3600 * 23 + 60 * 56 + 4.0916 # seconds
#define OMEGA 2 * M_PI / SIDEREAL_DAY
#define FAST_SPEED 3000 // steps per sec

// Hardware constants
#define THREAD_DENSITY 10 # threads per cm 
#define BOARD_LEN      31 # cm 
#define DEG_DER_STEP   1.8 # deg
#define MICROSTEPS     8
#define dPHI           DEG_PER_STEP / MICROSTEPS
#define MIN_ANGLE      0 // deg
#define MAX_ANGLE      30 // deg

AccelStepper motor(AccelStepper::DRIVER, PIN_IN_STEP, PIN_IN_DIR);

int read_dir, read_sidereal, read_fast;

void setup() {
  pinMode(PIN_OUT_DIR, OUTPUT);
  pinMode(PIN_OUT_SIDEREAL, OUTPUT);
  pinMode(PIN_OUT_FAST, OUTPUT);

  motor.setMaxSpeed(FAST_SPEED);

  if (DEBUG) {
    Serial.begin(9600);
  }
}

void loop() {
  read_dir = analogRead(PIN_
}

void off_mode() {
  
}

void fast_mode() {
  
}

void tracking_mode() {
  
}
