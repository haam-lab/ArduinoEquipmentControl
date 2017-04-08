// Author: Juhee Haam 3/6/17
// Ver 1.0
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
// OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
// IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
// DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.

// Using an Arduino Uno board, send TTL signals to a camera and another device (equipment2)
// at two different frequencies: camera acquisition at 25 Hz and equipment2 at 50 Hz
// The TTL signal is initiated when you press a button.

unsigned long ii = 0;
int buttonPin = 2 ;  // Plug the button to digital pin#2. See https://www.arduino.cc/en/tutorial/button for the schematic
int Camera = 5;      // Connect the camera to digital pin#5
int Equipment2 = 6;  // Connect Equipment2 to digital pin#6
int proceed = 0;     // Start stopped
int val = 0;

void setup()
{

  Serial.begin(9600);           // Initialize serial output, so you can see the print statement in Serial Monitor.
  pinMode(buttonPin, INPUT);    // Read digital input from #2
  pinMode(Camera, OUTPUT);      // Send digital output to #5 (camera)
  pinMode(Equipment2, OUTPUT);  // Send digital output to #6 (Equipment2)



}

void loop() {
  val = digitalRead(buttonPin);

  if (val == HIGH)
  {
    Serial.println("Button Pressed");
    proceed = 255;                  // When the button is pressed, change the value of proceed to 255
  }
  if (proceed == 255)             // When the button is pressed, the while loop that send TTL signals starts
  {
    while (ii <= 1200000)   // The number here sets the total number of TTL pulses for Equipment2
    {
      digitalWrite(Camera, HIGH);     // A TTL pulse to the camera starts
      digitalWrite(Equipment2, HIGH); // A TTL pulse to the Equipment2 starts

      delay (5); // 3. TTL ON duration in ms

      digitalWrite(Camera, LOW);      // A TTL pulse to the camera stops
      digitalWrite(Equipment2, LOW);  // A TTL pulse to Equipment2 stops

      delay(15); // 4. TTL OFF duration in ms 

      // The second pulse for Equipment2 starts   
      digitalWrite(Equipment2, HIGH); // A TTL pulse to the Equipment2 starts

      delay (5); // 3. TTL ON duration in ms

      digitalWrite(Equipment2, LOW);  // A TTL pulse to Equipment2 stops

      delay(15); // 4. TTL OFF duration in ms

      ii = ii + 2;
      //Serial.println(ii, DEC); // Serial.println delays the cycle. Only uncomment only during a test but not during actual data acquisition. 
    }
  }
  else
  {   // Enter code here if you want to run something when the pushbutton has not been pressed. 
  }

}
