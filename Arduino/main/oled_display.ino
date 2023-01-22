void oled_init() {
  oled.display();
  delay(500);
  oled.clearDisplay();

  oled.setTextSize(2);
  oled.setTextColor(WHITE);
  oled.setCursor(1, 10);
  oled.println("HUMIDIFIER");
  oled.setCursor(0, 30);
  oled.setTextSize(1);
  oled.println("INIT SUCCESSFUL");
  oled.display();  // show on OLED
  delay(500);
}

void main_disp_config() {
  oled.clearDisplay();
  oled.setTextSize(1);
  oled.setCursor(2, 10);
  oled.print("Exp Humidity: ");
  oled.print(exp_humidity);
  oled.print("%");
  oled.setCursor(2, 20);
  oled.print("Sen Humidity: ");
  oled.print(sen_humidity);
  oled.print("%");

  oled.setCursor(2, 30);
  oled.print("Temperature : ");
  oled.print(temperature,1);
  oled.print("Cel");
  if (exp_humidity - sen_humidity < 2) {
    oled.setCursor(2, 45);
    oled.print("ENJOY...!");
  }
  else{
    oled.setCursor(2, 45);
    oled.print("WAIT, I AM ON IT...!");
  }
  oled.display();
}