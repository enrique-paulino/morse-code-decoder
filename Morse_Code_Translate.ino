#define PIR_MOTION_SENSOR 2

const int buzzer = 2; // the number of the buzzer pin, D3
const int button = 4;  // the number of the pushbutton pin, D4

int buttonState;          // the state of the button
int lastButtonState;          // the state of the button

int startPressed = 0;    // the moment the button was pressed
int endPressed = 0;      // the moment the button was released
int holdTime = 0;        // how long the button was hold

bool buttonPressed = false;

float baseTime = 1000.0;
float tolerance = baseTime / 2.0;

String message = "";
 

void setup() {
  pinMode(button, INPUT);
  pinMode(buzzer, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  buttonState = digitalRead(button); // Gets current button state (pressed / not pressed)
  
  if (buttonState == 0) {
     if ((millis()-startPressed)%1000 == 0) {
      digitalWrite(buzzer, 1);
     }
     else {
      digitalWrite(buzzer, 0);
     }
     
  }
  else {
    digitalWrite(buzzer, 0);
  }
  
  
  if (buttonState != lastButtonState) {
    if (buttonState == HIGH) { // Button let go
      buttonPressed = false;
      endPressed = millis();
      holdTime = endPressed - startPressed;

      analyse_input(holdTime); // Converts input to . - or /
      
      if (message.endsWith("  ")) {
        Serial.println(message); // Send letter to the Raspberry PI
        delay(1000);
        message = "";
      }
      
    }
    else { // Button pressed
      //Serial.println("BUTTON PRESSED");
      startPressed = millis(); 
      buttonPressed = true;     
    }

    lastButtonState = buttonState;
    
  }

}


void analyse_input(int buttonInput) {

  if ((buttonInput >= (baseTime - tolerance)) and (buttonInput <= (baseTime + tolerance))) { // DOT
    message += '.';
  }
  else if ((buttonInput >= ((baseTime * 3) - tolerance)) and (buttonInput <= ((baseTime * 3) + tolerance))) { // DASH
    message += '-';
  }
  else if ((buttonInput >= ((baseTime * 7) - tolerance)) and (buttonInput <= ((baseTime * 7) + tolerance))) { // SPACE (between words)
    message += '/';
  }
  else if (buttonInput <= tolerance) { // SPACE (between letters)
    message += ' ';
  }
  
  holdTime = 0;
}
