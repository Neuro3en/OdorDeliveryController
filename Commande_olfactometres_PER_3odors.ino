int PushButton1 = 17; // define the 3 pins at which the pressbuttons will be connected
int PushButton2 = 18;
int PushButton3 = 19;
int LED1 = 6;
int LED2 = 5;
int LEDfam = 4;
int LEDcs = 3;
int LEDus = 2;
int Shock = 14;

int Familiarization = 15000; // define the time variables vith standard values   // 50s par abeille 12 abeilles par 10min
int CsAlone = 3000; 
int CsUs = 1000;
int UsAlone = 2000; 
int PostFamiliariazation = 19000; 
int Clignotementsur200 = 50; // clignotement de la derniere LED pendant 10sec (10000ms) 

int FlushValve; // define the valves variables
int MainValve;
int BalanceValve = 11;
int Speaker = 13;
int X; // define the odor loading variable
int ProgramNumber = 1;

void setup() {
  // put your setup code here, to run once:
    pinMode(PushButton1, INPUT_PULLUP);
    pinMode(PushButton2, INPUT_PULLUP);
    pinMode(PushButton3, INPUT_PULLUP);
  for (int thisPin = 2; thisPin < 17; thisPin++) {
    pinMode(thisPin, OUTPUT); 
    // 2, 3, 4, 5, 6  // initiate LEDS
    // 7 and 8 and 15 are Flush Valves 
    // 9 and 10 and 16 are Main Valves
    // 11 is the Balance Valve
    // 13 is the speaker
    // 14 is the shock
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  int ButtonState1 = digitalRead(PushButton1);
  int ButtonState2 = digitalRead(PushButton2);
  int ButtonState3 = digitalRead(PushButton3);

  // if the button 1 is pressed, use the first programmed parameters
  if (ButtonState1 == LOW) {
    if (ProgramNumber == 1) {
      ProgramNumber = 2;
      tone(Speaker, 587.33, 20);      // Speaker plays a tone of an D5 for 20ms
      Familiarization = 15000; // in milliseconds !!!!
      CsAlone = 3000; 
      CsUs = 1000;
      UsAlone = 2000; 
      PostFamiliariazation = 19000; 
      FlushValve = 7;
      MainValve = 9;
      Clignotementsur200 = 50; 
      digitalWrite(LED1, HIGH); // Switch ON the program 1 LED
      digitalWrite(LED2, LOW);  // Switch OFF the program 2 LED
     }
      
    else if (ProgramNumber == 2) {
      ProgramNumber = 3;
      tone(Speaker, 587.33, 20);      // Speaker plays a tone of an D5 for 20ms
      Familiarization = 15000; // in milliseconds !!!!
      CsAlone = 3000; 
      CsUs = 1000;
      UsAlone = 2000; 
      PostFamiliariazation = 19000; 
      FlushValve = 8;
      MainValve = 10;
      Clignotementsur200 = 50; 
      digitalWrite(LED1, LOW); // Switch OFF the program 1 LED
      digitalWrite(LED2, HIGH);  // Switch ON the program 2 LED
    }

    else if (ProgramNumber == 3) {
      ProgramNumber = 1;
      tone(Speaker, 587.33, 20);      // Speaker plays a tone of an D5 for 20ms
      Familiarization = 15000; // in milliseconds !!!!
      CsAlone = 3000; 
      CsUs = 1000;
      UsAlone = 2000; 
      PostFamiliariazation = 19000; 
      FlushValve = 15;
      MainValve = 16;
      Clignotementsur200 = 50; 
      digitalWrite(LED1, HIGH); // Switch ON the program 1 LED
      digitalWrite(LED2, HIGH);  // Switch ON the program 2 LED
    }
    delay(500);
  }

  // if button 2 is pressed, start the active sequence
  if (ButtonState2 == LOW) {
//    while(1 == 1) {
      X = Familiarization - 5000;     // The odor must be uploaded during 5s before launching
      digitalWrite(LEDfam, HIGH);         // Switch ON the Familiarization LED
      delay(X);
      digitalWrite(FlushValve, HIGH); // Switch the Flush Valve to NC (charge the cannon with the odor)
      delay(5000);                    // during 5s
      
      tone(Speaker, 659.25, 20);           // Speaker plays a tone of an E5 for 20ms
      digitalWrite(BalanceValve, HIGH);    // switch the balance valve to NC
      digitalWrite(MainValve, HIGH);  // switch the Main valve to NC
      digitalWrite(LEDfam, LOW);      // Switch OFF the Familiarization LED
      digitalWrite(LEDcs, HIGH);      // Switch ON the Cs LED
      delay(CsAlone);
      
      tone(Speaker, 698.46, 20);      // Speaker plays a tone of an F5 for 20ms
      digitalWrite(LEDus, HIGH);      // Switch ON the Us LED
      digitalWrite(Shock, HIGH);      // Trigger shock 
      delay(CsUs);

      tone(Speaker, 783.99, 20);        // Speaker plays a tone of an G5 for 20ms
      digitalWrite(Shock, LOW);         // Stop trigger Shock (even if its pulsed)
      digitalWrite(FlushValve, LOW);    // switch the flush valve to NO
      digitalWrite(BalanceValve, LOW);  // switch the balance valve to NO 
      digitalWrite(MainValve, LOW);     // switch the Main valve to NO
      digitalWrite(LEDcs, LOW);         // Switch OFF the Cs LED
      delay(UsAlone);

      tone(Speaker, 880, 20);          // Speaker plays a tone of an A5
      digitalWrite(LEDus, LOW);           // Switch OFF the Us LED
      delay(PostFamiliariazation);

      int k = 1;
      tone(Speaker, 880, 20);          // Speaker plays a tone of an A5
      while (k < 101){
        digitalWrite(LEDus, HIGH);         // Switch OFF the Cs LED
        delay(Clignotementsur200);                   // Wait for the ITI
        digitalWrite(LEDus, LOW);
        delay(Clignotementsur200);
        k=k+1;
      }
      tone(Speaker, 880, 20);          // Speaker plays a tone of an A5
//    }
  }
  delay(1); // delay for stability

  // if the button 3 is pressed, use the second programmed parameters
  if (ButtonState3 == LOW) {
    tone(Speaker, 987.77, 20);      // Speaker plays a tone of an B5 for 20ms
    
  }
}
