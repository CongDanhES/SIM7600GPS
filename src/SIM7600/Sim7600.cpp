#include "Sim7600.hpp"

SIM7600::SIM7600(/* args */)
{
}

SIM7600::~SIM7600()
{
}

void SIM7600::GPS_Hotstart(HardwareSerial *serial)
{
    serial->println(AT_CGPSHOT);
}

void SIM7600::GPS_Info(HardwareSerial *serial){
    serial->println(AT_CGPSINFO);
}

void SIM7600::GPS_Receiver(HardwareSerial *serial, HardwareSerial *debug)
{
    if(serial->available()){
        rxData = serial->read();
        if(rxData == '\n'||rxData == '\r'){

            /*
                AT+CGPSINFO
            */

            if(rxBuffer[0] == '+'){
                debug->println((char*)rxBuffer);
                char *token = strtok((char *)rxBuffer, ":");
                if(strcmp(token, "+CGPSINFO") == 0){
                    decodeGPSData((char*)rxBuffer + strlen("+CGPSINFO: "));
                }
            }

            /*
                AT+CGPS=1
            */

            // check if command is AT+CGPS=1
            if((strcmp((char* )rxBuffer, AT_CGPSHOT)) == 0){
                isATCGPS_ON = 1;
                // debug->println((const char*)rxBuffer);
            }

            // if the data is OK or ERROR
            if((strcmp((char* )rxBuffer, "OK"))== 0||(strcmp((char* )rxBuffer, "ERROR")) == 0){
                if(isATCGPS_ON){
                    // debug->println((const char*)rxBuffer);
                    debug->println("HOTSTART is active");
                    isGPSActive = 1;
                    isATCGPS_ON = 0;
                }
            }
            // debug->println((char*)rxBuffer);
            // reset buffer
            resetBuffer();
        }
        else{
            rxBuffer[rxCount] = rxData;
            rxCount++;
        }
    }
}

void SIM7600::resetBuffer(){
    rxCount = 0;
    memset(rxBuffer, 0 ,sizeof(rxBuffer));
}


void SIM7600::decodeGPSData(char *gpsData) {
    char *token;
    
    // Latitude
    token = strtok(gpsData, ",");
    if (token == NULL) return;
    double latitude = atof(token);
    String lat= (String)(token);
    // debug->println("Lat: "+ lat);

    
    // N/S indicator
    token = strtok(NULL, ",");
    if (token == NULL) return;
    char latDir = token[0];
    String strLat = lat+ latDir; 

    // Longitude
    token = strtok(NULL, ",");
    if (token == NULL) return;
    double longitude = atof(token);
    String lon= (String)(token);

    // E/W indicator
    token = strtok(NULL, ",");
    if (token == NULL) return;
    char lonDir = token[0];
    String strLon= lon+lonDir;

    // Date (DDMMYY)
    token = strtok(NULL, ",");
    if (token == NULL) return;
    int date = atoi(token);
    String strDate= (String)(token);

    // Time (HHMMSS)
    token = strtok(NULL, ",");
    if (token == NULL) return;
    float time = atof(token);
    String strTime = (String)(token);

    // Altitude
    token = strtok(NULL, ",");
    if (token == NULL) return;
    float altitude = atof(token);
    String strAlt= (String)(token);

    // Speed
    token = strtok(NULL, ",");
    if (token == NULL) return;
    float speed = atof(token);
    String strSpeed= (String)(token);

    // setGPSData(latitude, longitude, date, time, altitude, speed);
    setGPS_String(strLat, strLon, strDate, strTime, strAlt, strSpeed);
    isGPSData = 1;
}


void SIM7600::setGPS_String(String lat, String lon, String date, String time, String alt, String spd){
    setLattitude(lat);
    setLongitude(lon);
    setDate(date);
    setTime(time);
    setAltitude(alt);
    setSpeed(spd);
}
