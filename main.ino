int pin_x_axis = A0;
int pin_y_axis = A1;
int pin_pressed = 8;

int pin_right_led = 3;    //0 - 3 poz in brightness function 
int pin_left_led = 6;     //1 - 3
int pin_up_led = 5;       //1 - 2 poz
int pin_bottom_led = 10;  //0 - 2

int global_tab[4] = {0,0,0,0};

int brightness(int vertical, int horizontal, int tab[4]){
  if(vertical <= 520 && vertical > 500){
    tab[0] = 0;  
    tab[2] = 0;
  }
  else if(vertical <= 500){
    tab[0] = ((500 - vertical) / 2);  
    tab[2] = 0;
  }
  else if(vertical > 520){
    tab[0] = (vertical - 518) / 2;
    tab[2] = 1;
  }

  if(horizontal <= 520 && horizontal > 500){
    tab[1] = 0;
    tab[3] = 0;
  }
  else if(horizontal <= 500){
    tab[1] = (500 - horizontal) / 2;
    tab[3] = 0;
  }
  else if(horizontal > 520){
    tab[1] = (horizontal - 518) / 2;
    tab[3] = 1;
  }
  else{
    Serial.println("ERROR !!!!!!!!!!!!!!!!!!!!!");
  }

  // Ograniczenie wartości do zakresu 0-255 dla PWM
  if (tab[0] > 255) tab[0] = 255;
  if (tab[0] < 0) tab[0] = 0;

  if (tab[1] > 255) tab[1] = 255;
  if (tab[1] < 0) tab[1] = 0;
}

void setup(){
  pinMode(pin_pressed, INPUT_PULLUP);
  pinMode(pin_right_led, OUTPUT);
  pinMode(pin_up_led, OUTPUT);
  pinMode(pin_left_led, OUTPUT);
  pinMode(pin_bottom_led, OUTPUT);
  Serial.begin(9600);
}

void loop(){
  int vertical = analogRead(pin_y_axis);  // Zmieniono na analogRead
  int horizontal = analogRead(pin_x_axis);  // Zmieniono na analogRead
  int pressed = digitalRead(pin_pressed);

  Serial.print("HORIZONTAL: ");
  Serial.print(horizontal, DEC);
  Serial.print(" VERTICAL: ");
  Serial.print(vertical, DEC);
  Serial.print(" PRESSED: ");
  
  if(pressed == LOW){
    Serial.println("LOW");
    digitalWrite(pin_bottom_led, HIGH);
    digitalWrite(pin_up_led, HIGH);
    digitalWrite(pin_left_led, HIGH);
    digitalWrite(pin_right_led, HIGH);
  }
  else{
    brightness(vertical, horizontal, global_tab);
    
    // Debugowanie wartości
    Serial.print("global_tab[0]: ");
    Serial.println(global_tab[0]);
    Serial.print("global_tab[1]: ");
    Serial.println(global_tab[1]);

    // Sprawdzamy, czy tab[2] = 0 (dolna dioda)
    if(global_tab[2] == 0){
      analogWrite(pin_bottom_led, global_tab[0]);
      analogWrite(pin_up_led, 0);  // Wyłączenie górnej diody, gdy nie jest aktywna
    }
    else if (global_tab[2] == 1){
      analogWrite(pin_up_led, global_tab[0]);  // Włączamy górną diodę z odpowiednią jasnością
      analogWrite(pin_bottom_led, 0);  // Wyłączenie dolnej diody, gdy nie jest aktywna
    }

    // Sprawdzamy, czy tab[3] = 0 (prawa dioda)
    if(global_tab[3] == 0){
      analogWrite(pin_right_led, global_tab[1]);
      analogWrite(pin_left_led, 0);  // Wyłączenie lewej diody, gdy nie jest aktywna
    }
    else if (global_tab[3] == 1){
      analogWrite(pin_left_led, global_tab[1]);  // Włączamy lewą diodę z odpowiednią jasnością
      analogWrite(pin_right_led, 0);  // Wyłączenie prawej diody, gdy nie jest aktywna
    }
  }
  delay(2);
}
