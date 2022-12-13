#include <Arduino_FreeRTOS.h>
#include <queue.h>

#define d4 853  //293 hz
#define e4 760  //329 hz
#define c4 958  //261 hz
#define c3 1923 //130 hz
#define g3 1276 //196 hz
#define R 0 

int i;

void TaskBlink(void *pvParameters);
void TaskMusic(void *pvParameters);
void RT3p0(void *pvParameters);
void RT3p1(void *pvParameters);
void TaskFFT(void *pvParameters);

int melody[] = {d4, e4, c4, c3, g3, R, R, R, R, R, R, R, R, R, R, R, R, R, R, R, R, R, R, R, R};
int n = 64;
double rando[64];
QueueHandle_t data_queue;
QueueHandle_t time_queue;

void setup() {
  Serial.begin(19200);
  // put your setup code here, to run once:
  xTaskCreate(
    TaskBlink
    , "Blink"
    , 128
    , NULL
    , 3
    , NULL );

  xTaskCreate(
    TaskMusic
    , "Music"
    , 128
    , NULL
    , 2
    , NULL );

  xTaskCreate(
    RT3p0
    , "FreeRTOS queue starter"
    , 128
    , NULL
    , 1
    , NULL );

  xTaskCreate(
    TaskFFT
    , "FFT Task 4"
    , 128
    , NULL
    , 1
    , NULL );

  vTaskStartScheduler();
}

void loop() {
  // put your main code here, to run repeatedly:
}

void TaskBlink(void *pvParameters) {
  pinMode(5, OUTPUT);
  for(;;) {
    digitalWrite(5, HIGH);
    vTaskDelay(100/portTICK_PERIOD_MS);
    digitalWrite(5, LOW);
    vTaskDelay(200/portTICK_PERIOD_MS);
  }
}

void TaskMusic(void *pvParameters) {
  pinMode(6,OUTPUT);
  TCNT4 = 0;
  i = 0;
  TCCR4A = 0b01000000;
  TCCR4B = 0b00001011;
  for(int j = 0; j < 3; j++) {
    for(int k = 0; k < 24; k++) {
      OCR4A = melody[k];
      vTaskDelay(200/portTICK_PERIOD_MS);
    }
  }
  vTaskDelete(NULL);
}

void RT3p0(void *pvParameters) {
  for(int i = 0; i < 64; i++) {
    rando[i] = i;
    Serial.println(rando[i]);
  }
  data_queue = xQueueCreate(5, sizeof(double) * 64);
  time_queue = xQueueCreate(1, sizeof(int));
  vTaskDelay(1000 / portTICK_PERIOD_MS);
  xTaskCreate(RT3p1, "Value sender", 128, NULL, 1, NULL);
  vTaskSuspend(NULL);
}

void RT3p1(void *pvParameters) {
  for(int i = 0; i < 5; i++) {
    Serial.println("Sending");
    //vTaskDelay(1000 / portTICK_PERIOD_MS);
    xQueueSendToBack(data_queue, rando, 0);
      
    double data2[64];
    Serial.println("Check");
    //vTaskDelay(1000 / portTICK_PERIOD_MS);
    xQueueReceive(data_queue, data2, 0);
  }
  vTaskSuspend(NULL);
}

void TaskFFT(void *pvParameters) {
  for (;;) {
    int times = 100;
    double* rando;
    for(int i = 0; i < 5; i++) {
      Serial.println("Start PT4 Loop");
      while(xQueueReceive(data_queue, rando, 0) != pdPASS) {
        vTaskDelay(100/portTICK_PERIOD_MS);
      }
      Serial.println("PT4 received");
      Serial.println((uint32_t) rando, HEX);
      
      vTaskDelay(100/portTICK_PERIOD_MS);

      Serial.println("PT4 sent");
      xQueueSendToBack(time_queue, times, 0);
    }
    vTaskSuspend(NULL);
  }
}
