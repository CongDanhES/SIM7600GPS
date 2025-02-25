# 1 "C:\\TTD\\CONG DANH\\GPS\\GPS.ino"
# 2 "C:\\TTD\\CONG DANH\\GPS\\GPS.ino" 2

TaskHandle_t SIM7600Task_Handle;
TaskHandle_t DebugTask_Handle;
TaskHandle_t GPSActiveTask_Handle;

void SIM7600Task(void *pvParameters);
void DebugTask(void *pvParameters);
void GPSActiveTask(void *pvParameters);

void setup(){
    pinMode(63, 0x1);
    Sim7600_port.begin(115200);
    Debug_port.begin(115200);

    xTaskCreate(DebugTask, "DebugTask", 256, 
# 16 "C:\\TTD\\CONG DANH\\GPS\\GPS.ino" 3 4
                                            __null
# 16 "C:\\TTD\\CONG DANH\\GPS\\GPS.ino"
                                                , 1, &DebugTask_Handle);
    xTaskCreate(SIM7600Task, "SIM7600Task", 256, 
# 17 "C:\\TTD\\CONG DANH\\GPS\\GPS.ino" 3 4
                                                __null
# 17 "C:\\TTD\\CONG DANH\\GPS\\GPS.ino"
                                                    , 1, &SIM7600Task_Handle);
    xTaskCreate(GPSActiveTask, "GPSActiveTask", 256, 
# 18 "C:\\TTD\\CONG DANH\\GPS\\GPS.ino" 3 4
                                                    __null
# 18 "C:\\TTD\\CONG DANH\\GPS\\GPS.ino"
                                                        , 1, &GPSActiveTask_Handle);

    vTaskStartScheduler();
}

void SIM7600Task(void *pvParameters){
    while (1)
    {
        sim7600.GPS_Receiver(&Sim7600_port, &Debug_port);
        vTaskDelay(( ( TickType_t ) ( ( ( TickType_t ) ( 1 ) * ( TickType_t ) ((TickType_t)1000) ) / ( TickType_t ) 1000 ) ));
    }
}

void DebugTask(void *pvParameters){
    while (1)
    {
        if(sim7600.isGPSData == 1){
            Debug_port.print("Latitude: ");
            Debug_port.println(sim7600.getLatitude_str());
            Debug_port.print("Longitude: ");
            Debug_port.println(sim7600.getLongitude_str());
            Debug_port.print("Date: ");
            Debug_port.println(sim7600.getDate_str());
            Debug_port.print("Time: ");
            Debug_port.println(sim7600.getTime_str());
            Debug_port.print("Altitude: ");
            Debug_port.println(sim7600.getAltitude_str());
            Debug_port.print("Speed: ");
            Debug_port.println(sim7600.getSpeed_str());
            Debug_port.println("-----------------------");

        }
        else{
            Debug_port.println("GPS data is not available");
        }
        vTaskDelay(( ( TickType_t ) ( ( ( TickType_t ) ( 10000 ) * ( TickType_t ) ((TickType_t)1000) ) / ( TickType_t ) 1000 ) ));
    }
}

void GPSActiveTask(void *pvParameters){
    while (1)
    {
        if(sim7600.isGPSActive == 0){
            sim7600.GPS_Hotstart(&Sim7600_port);
            vTaskDelay(( ( TickType_t ) ( ( ( TickType_t ) ( 5000 ) * ( TickType_t ) ((TickType_t)1000) ) / ( TickType_t ) 1000 ) ));
        }
        else {
            sim7600.GPS_Info(&Sim7600_port);
            vTaskDelay(( ( TickType_t ) ( ( ( TickType_t ) ( 5000 ) * ( TickType_t ) ((TickType_t)1000) ) / ( TickType_t ) 1000 ) ));
        }
    }
}



void loop(){

}
