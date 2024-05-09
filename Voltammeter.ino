#include <LiquidCrystal.h>

LiquidCrystal lcd(2,3,4,5,6,7);
float V = 0.00, I = 0.00; //the values to be read
void calculate_voltage() { 
  const float R1 = 10000.00; 
  const float R2 = 4700.00; 
  float v_ref = 5.00; 
  float resistor_ratio = (R2 / (R1 + R2));
  float adc_value = 0.00; 
  float voltage = 0.00;

  for (int i = 0; i < 20 ; i++) //looping to obtain average of read values
  { 
    adc_value = adc_value + analogRead(A2);//Voltammeter connected to pin A2
    delay(5); 
  } 
  adc_value = adc_value / 20; 
  voltage = ((adc_value * v_ref) / 1024); 
  V = voltage / resistor_ratio; 
  
} 
void setup() { 
  Serial.begin(9600); 
  lcd.begin(16, 2);

} 
void loop() { 
  calculate_voltage();
  Serial.print("V=");
  Serial.print(V); 
  Serial.println(" v"); 
  delay(2000); 
} 
