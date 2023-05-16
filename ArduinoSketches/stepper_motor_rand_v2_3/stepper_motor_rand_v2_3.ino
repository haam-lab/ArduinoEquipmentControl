/* Sketch to control stepper motor for sleep deprivation chambers
 *  A stepper motor can be plugged to either port 1 (M1&M2) or 2 (M3&M4).
 *  Written by Juhee Haam, 1/9/2023 
 *  
 *  - Adafruit Motor Shield v2
 *  - Stepper motor (Stepperoline, Nema17, Bipolar, 1 A, 12 V, 4-wire, 200 steps/rev (1.8 deg/step)
 *      Rated current 1.0A & resistance 3.5ohms
 */
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
// OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
// IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
// DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.

#include <Adafruit_MotorShield.h>
volatile long dur = 5000; //default delay
char temp;
volatile long ii = -1;
char input;
unsigned int defstep1= 50;
unsigned int defstep2= 50;
unsigned int dir= 1;

Adafruit_MotorShield motor_shield1 = Adafruit_MotorShield(); // Create a motor shield object
Adafruit_StepperMotor*stepMotor1 = motor_shield1.getStepper(200, 1); // to motor port #1 (M1 and M2)
Adafruit_StepperMotor*stepMotor2 = motor_shield1.getStepper(200, 2); // to motor port #2 (M3 and M4)

void setup() {
Serial.begin(9600);           
  while (!Serial);
  Serial.println("Connecting to the motor shield");
  if (!motor_shield1.begin()) {         
  // if (!motor_shield1.begin(1000)) {  
    Serial.println("Cannot find the motor shield");
  }
  Serial.println("Motor Shield detected");
  stepMotor1->setSpeed(50);  // Speed in rpm
  stepMotor2->setSpeed(50);  
  ii = 0; // comment this if the default state is OFF
  input = 115; // comment this if the default state is OFF
}

void loop() {
readSerial();


  while ( ii>=0 && input == 115 )   // you can set the total number of frames if needed
  {
    readSerial();
    //Serial.println("Motor ON");
    dir= random(1,3);
    
  // will try with single coil first
  // will turn 180-270 degree in a random direction
    defstep1=random(100,150);
    defstep2=random(100,150);
    Serial.println("1st step size, 2nd step size, dir, and delay:"); 
    Serial.println(defstep1);
    Serial.println(defstep2);
    Serial.println(dir);   
    //Serial.println("Single coil steps");  
    if (dir ==1) 
    {
      stepMotor1->step(defstep1, FORWARD, SINGLE); 
      delay(500);
      stepMotor2->step(defstep1, FORWARD, SINGLE); 
      delay(500);     
      stepMotor1->step(defstep2, BACKWARD, SINGLE);  
      delay(500);   
      stepMotor2->step(defstep2, BACKWARD, SINGLE);  
    } else { 
      stepMotor1->step(defstep1, BACKWARD, SINGLE); 
      delay(500);   
      stepMotor2->step(defstep1, BACKWARD, SINGLE);
      delay(500);    
      stepMotor1->step(defstep2, FORWARD, SINGLE);
      delay(500);   
      stepMotor2->step(defstep2, FORWARD, SINGLE);  
    }
    
    dur=random(180000, 600000); //delay between 3 min and 10 min (in ms) 
    //dur=random(2000, 3000); //delay between 5 s and 7 s (in ms)// just for testing; the actual experimental setting should be between 3 and 10 min
    Serial.println(dur);
    delay(dur);
    Serial.print("The iteration number is ");
    Serial.println(ii, DEC);
    ii = ii + 1;
    }
 }

void readSerial()    // define the function to read serial input
{
  if (Serial.available() > 0) 
  {
    temp = Serial.read(); // type to Serial Monitor "s" or "p"

    if (temp == 112) // 'p'
    {
      ii = -1;
      input = temp; // if a blank was received, do not replace input
      Serial.println("P is pressed: stop");
      //Serial.println(input); // p for pause    
    }
    
    else if (temp == 115)// 's'
    {
      ii = 0;
      input = temp; // if a blank was received, do not replace input
    }  
  }
}
