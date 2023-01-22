void encoder_check() {
  aState = digitalRead(outputA);
  if (aState != aLastState) {
    if (digitalRead(outputB) != aState) {
      exp_humidity = (exp_humidity + 101) % 100;
    } else {
      exp_humidity = (exp_humidity + 99) % 100;
    }
  }
  aLastState = aState;
}

void read_button() {
  int buttonState = digitalRead(buttonPin);
  if (millis() - but_change_time > 200)
    if (buttonState) {
      delay(1000);
      buttonState = digitalRead(buttonPin);
      if (buttonState) flash_light();
      else pattern_light();
    }
}

void flash_light() {}
void pattern_light() {}