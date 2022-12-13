//www.elegoo.com
//2016.12.9

#include <LiquidCrystal.h>
#include <Keypad.h>
#include <Arduino_FreeRTOS.h>

int tempPin = 0;
char setTemp[2] = {'0','0'};
int i;
//                BS  E  D4 D5  D6 D7

const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
//define the symbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {29, 28, 27, 26}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {25, 24, 23, 22}; //connect to the column pinouts of the keypad

int tempval;

//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

void setup()
{
    xTaskCreate(
    thermostat
    , "Thermostat"
    , 128
    , NULL
    , 3
    , NULL );
    vTaskStartScheduler();
}
void loop() { 
}

void thermostat() {
  for(;;) {
    pinMode(4, OUTPUT);
    lcd.begin(16, 2);
    Serial.begin(19200);
      int tempReading = analogRead(tempPin);
    // This is OK
    double tempK = log(10000.0 * ((1024.0 / tempReading - 1)));
    tempK = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * tempK * tempK )) * tempK );       //  Temp Kelvin
    float tempC = tempK - 273.15;            // Convert Kelvin to Celcius
    float tempF = (tempC * 9.0)/ 5.0 + 32.0; // Convert Celcius to Fahrenheit
    /*  replaced
      float tempVolts = tempReading * 5.0 / 1024.0;
      float tempC = (tempVolts - 0.5) * 10.0;
      float tempF = tempC * 9.0 / 5.0 + 32.0;
    */
    
    char customKey = customKeypad.getKey();
    if (customKey){
      //Serial.println(customKey);
    }
    
    if (customKey && (customKey != '#')){
        setTemp[i] = customKey;
        i++;
    } else if (customKey == '#') {
      i = 0;
      tempval = ((int)setTemp[0] - 48) * 10 + ((int)setTemp[1] - 48);
    }
    
    lcd.setCursor(0, 0);
    lcd.print("Temp         F  ");
    
    lcd.setCursor(6, 0);
    lcd.print(tempF);
    
    lcd.setCursor(0, 1);
    lcd.print("Set Temp       F");
  
    lcd.setCursor(10, 1);
    lcd.print(setTemp[0]);
  
    lcd.setCursor(11,1);
    lcd.print(setTemp[1]);
  
    if(tempval < tempF) {
      digitalWrite(4, HIGH);
    }
    else {
      digitalWrite(4, LOW);
    }
    Serial.println(tempval);
    vTaskDelay(100 / portTICK_PERIOD_MS);
  }
}
