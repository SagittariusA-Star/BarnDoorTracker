#include <AccelStepper.h>
#include <MultiStepper.h>

#include <FiniteStateMachine.h>
#include <math.h>

// Debug mode; 0 = off, 1 = on. 
#define DEBUG 0

// Input pins
#define PIN_IN_DIR  8
#define PIN_IN_STEP 9

// Output pins
#define PIN_OUT_DIR       A3
#define PIN_OUT_SIDEREAL  A4
#define PIN_OUT_FAST      A5

// Physical constants
#define SIDEREAL_DAY 86164.0916 // seconds
#define OMEGA 7.2921157e-5
#define FAST_SPEED 3000 // steps per sec

// Hardware constants
#define THREAD_DENSITY 10 // threads per cm 
#define BOARD_LEN      31 // cm 
#define DEG_PER_STEP   1.8 // deg
#define MICROSTEPS     8
#define dPHI           0.225
#define MIN_ANGLE      0 // deg
#define MAX_ANGLE      30 // deg

AccelStepper motor(AccelStepper::DRIVER, PIN_IN_STEP, PIN_IN_DIR);

int read_dir;
int read_sidereal;
int read_fast;

long pos;
double current_time;
double tracking_speed;

void off_state_enter(){
  // Empty
}

void off_state_exit(){
  // Empty
}

void off_state_update(){
  if (DEBUG) {
    Serial.println("Motor turned off!");
  }
  motor.stop();
}

void fast_state_enter(){
  // Empty
}

void fast_state_exit(){
  // Empty
}

void fast_state_update(){
  if (DEBUG) {
    Serial.println("Motor running in fast mode!");
  }
  if (read_dir < 16){
    motor.setSpeed(FAST_SPEED);
    motor.runSpeed();
  }
  else {
    motor.setSpeed(-FAST_SPEED);
    motor.runSpeed();
  }
}

void tracking_state_enter(){
  // Empty
}

void tracking_state_exit(){
  // Empty
}

void tracking_state_update(){
  if (DEBUG) {
    Serial.println("Motor running in tracking mode!");
  }
  //current_time = millis() ∕ 1000.0;
  
  tracking_speed = (THREAD_DENSITY * BOARD_LEN * OMEGA * (360.0 / (double) dPHI) * cos(0.5 * OMEGA * current_time));
  if (DEBUG) {
    Serial.print("Tracking speed: ");
    Serial.print(tracking_speed);
    Serial.print("\n");
  }
  
  if (read_dir < 16){
    motor.setSpeed(tracking_speed);
    motor.runSpeed();
  }
  else {
    motor.setSpeed(-tracking_speed);
    motor.runSpeed();
  }
}

static State off_state(off_state_enter, off_state_update, off_state_exit);
static State tracking_state(tracking_state_enter, tracking_state_update, tracking_state_exit);
static State fast_state(fast_state_enter, fast_state_update, fast_state_exit);
static FSM   tracker = FSM(off_state);

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
  read_dir      = analogRead(PIN_OUT_DIR);
  read_sidereal = analogRead(PIN_OUT_SIDEREAL);
  read_fast     = analogRead(PIN_OUT_FAST);
  if (read_sidereal < 16){
    tracker.transitionTo(tracking_state);
  }
  else if (read_fast < 16) {
    tracker.transitionTo(fast_state);
  }
  else{
    tracker.transitionTo(off_state);
  }
  tracker.update();
  //delay(3000);
}
