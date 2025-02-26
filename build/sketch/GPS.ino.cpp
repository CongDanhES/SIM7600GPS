#include <Arduino.h>
#line 1 "C:\\TTD\\CONG DANH\\GPS\\GPS.ino"
#include "src/Utils/define.h"

TaskHandle_t SIM7600Task_Handle;
TaskHandle_t DebugTask_Handle;
TaskHandle_t GPSActiveTask_Handle;

void SIM7600Task(void *pvParameters);
void DebugTask(void *pvParameters);
void GPSActiveTask(void *pvParameters);

#line 11 "C:\\TTD\\CONG DANH\\GPS\\GPS.ino"
void setup();
#line 66 "C:\\TTD\\CONG DANH\\GPS\\GPS.ino"
void loop();
#line 11 "C:\\TTD\\CONG DANH\\GPS\\GPS.ino"
void setup(){
    pinMode(LED, OUTPUT);
    Sim7600_port.begin(115200);
    Debug_port.begin(115200);

    xTaskCreate(DebugTask, "DebugTask", 256, nullptr, 1, &DebugTask_Handle);
    xTaskCreate(SIM7600Task, "SIM7600Task", 256, nullptr, 1, &SIM7600Task_Handle);
    xTaskCreate(GPSActiveTask, "GPSActiveTask", 256, nullptr, 1, &GPSActiveTask_Handle);
    vTaskStartScheduler();
}

void SIM7600Task(void *pvParameters){
    while (1)
    {
        sim7600.GPS_Receiver(&Debug_port);
        vTaskDelay(pdMS_TO_TICKS(1));
    }
}

void DebugTask(void *pvParameters){
    while (1)
    {
        if(sim7600.isGPSData == 1){
            Debug_port.print("Latitude: ");
            Debug_port.println(sim7600.getLatitude());
            Debug_port.print("Longitude: ");
            Debug_port.println(sim7600.getLongitude());
            Debug_port.print("Date: ");
            Debug_port.println(sim7600.getDate());
            Debug_port.print("Time: ");
            Debug_port.println(sim7600.getTime());
            Debug_port.println("-----------------------");
        }
        else{
            Debug_port.println("GPS data is not available");
        }
        vTaskDelay(pdMS_TO_TICKS(10000));
    }
}

void GPSActiveTask(void *pvParameters){
    while (1)
    {
        if(sim7600.isGPSActive == 0){
            sim7600.GPS_Hotstart();
            vTaskDelay(pdMS_TO_TICKS(5000));
        }
        else {
            sim7600.GPS_Info();
            vTaskDelay(pdMS_TO_TICKS(5000));
        }
    }
}


void loop(){
    
}
