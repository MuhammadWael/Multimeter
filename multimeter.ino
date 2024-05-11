#include <LiquidCrystal.h>
#define VOLTAGE_INPUT A2
#define RESISTANCE_INPUT A1
#define CURRENT_INPUT A3
#define CURRENT2_INPUT A0

//for displaying ohm 
byte ohmSymbol[8] = {
  B00000,
  B01110,
  B10001,
  B10001,
  B10001,
  B01010,
  B11011,
  B00000
};

LiquidCrystal lcd(2,3,4,5,6,7);
float V = 0.00, I = 0.00, R =0.00, I2 = 0.00; //the values to be read
float v_ref = 5.00; 
void voltmeter() { 
  const float R1 = 10000.00; 
  const float R2 = 4700.00; 
  float adc_value = 0.00; 
  float voltage = 0.00;

  for (int i = 0; i < 20 ; i++) //looping to obtain average of read values
  { 
    adc_value += analogRead(VOLTAGE_INPUT);//Voltohmmeter connected to pin A2
    delay(5); 
  } 
  adc_value /= 20; 
  voltage = ((adc_value * v_ref) / 1024.0); 
  V = voltage / (R2 / (R1 + R2)); 
  
} 

void ohmmeter() { 
  float v_out = 0.0;
  float R1 = 10000;
  float adc_value = 0;
  for (int i = 0; i < 20 ; i++) //looping to obtain average of read values
  { 
    adc_value += analogRead(RESISTANCE_INPUT);//connected to pin A1
    delay(5); 
  } 
  adc_value /= 20;
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
  adc_value /= 20; 
  voltage = (((adc_value * v_ref) / 1024) - 2.5)/sensitivity; 

  I = voltage / sensitivity; 
}

void ammeter2()
{
  int adc_value = 0; 
  float voltage = 0.0; 
  for (int i = 0; i < 20 ; i++) 
  { 
    adc_value = adc_value + analogRead(CURRENT2_INPUT); 
    delay(5); 
  } 
  adc_value /= 20; 
 voltage = ((adc_value * v_ref) / 1024.0); 

  I2 = voltage*1000 / (220); 
}

void display_values(float v, float i, float r,float i2) {
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

  lcd.createChar(0, ohmSymbol);
  lcd.setCursor(0, 1);
  lcd.print("R=");
  lcd.print((int)r);
  lcd.write(byte(0));

  lcd.setCursor(7, 1);
  lcd.print("I2=");
  lcd.print(i2);
  lcd.print("mA");
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
  ammeter2();
  Serial.print("I2= ");
  Serial.print(I2); 
  Serial.println(" A"); 
  display_values(V,I,R,I2);
  delay(2000); 
} 
