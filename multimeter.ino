#include <LiquidCrystal.h>
#define VOLTAGE_INPUT A2
#define RESISTANCE_INPUT A1
#define CURRENT_INPUT A0



LiquidCrystal lcd(2,3,4,5,6,7);
float V = 0.00, I = 0.00, R =0.00; //the values to be read
float v_ref = 5.00; 
void voltmeter() { 
  const float R1 = 10000.00; 
  const float R2 = 4700.00; 
  float adc_value = 0.00; 
  float voltage = 0.00;

  for (int i = 0; i < 20 ; i++) //looping to obtain average of read values
  { 
    adc_value = adc_value + analogRead(VOLTAGE_INPUT);//Voltohmmeter connected to pin A2
    delay(5); 
  } 
  adc_value = adc_value / 20; 
  voltage = ((adc_value * v_ref) / 1024.0); 
  V = voltage / (R2 / (R1 + R2)); 
  
} 

void ohmmeter() { 
  float v_out = 0.0;
  float R1 = 10000;
  float adc_value = analogRead(RESISTANCE_INPUT);//which is A1
  v_out = ((adc_value * v_ref) / 1024.0);
  R = R1*(v_ref/v_out-1);
}

void ammeter()
{
  const int sensitivity = 185; 
  int adc_value = 0; 
  float voltage = 0.00; 
  float pure_voltage = 0.00; 
  float offset_voltage = 2.47; 
  for (int i = 0; i < 20 ; i++) 
  { 
    adc_value = adc_value + analogRead(CURRENT_INPUT); 
    delay(5); 
  } 
  adc_value /= 40; 
  voltage = (((adc_value * v_ref) / 1024) - 2.5)/sensitivity; 

  I = voltage / sensitivity; 
}

void display_values(float v, float i, float r) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("V=");
  lcd.print(v);
  lcd.print("V");
  lcd.print("|");
  lcd.setCursor(8, 0);
  lcd.print("I=");
  lcd.print(i);
  lcd.print("A");

  lcd.setCursor(0, 1);
  lcd.print("R=");
  lcd.print(r);
  lcd.print(" Ohm");
}

void setup() { 
  Serial.begin(9600); 
  lcd.begin(16, 2);

}

void loop() { 
  voltmeter();
  Serial.print("V=");
  Serial.print(V); 
  Serial.println("v"); 
  ohmmeter();
  Serial.print("R= ");
  Serial.print(R); 
  Serial.println(" ohm"); 
  ammeter();
  Serial.print("I= ");
  Serial.print(I); 
  Serial.println(" A"); 
  display_values(V,I,R);
  delay(2000); 
} 