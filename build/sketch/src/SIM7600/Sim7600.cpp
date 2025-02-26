#line 1 "C:\\TTD\\CONG DANH\\GPS\\src\\SIM7600\\Sim7600.cpp"
#include "Sim7600.hpp"

SIM7600::SIM7600(HardwareSerial *serial)
{
    SIM7600_Serial = serial;
}

SIM7600::~SIM7600()
{
}

void SIM7600::GPS_Hotstart()
{
    SIM7600_Serial->println(AT_CGPSHOT);
}

void SIM7600::GPS_Info(){
    SIM7600_Serial->println(AT_CGPSINFO);
}

void SIM7600::GPS_Receiver(HardwareSerial *debug)
{
    if(SIM7600_Serial->available()){
        rxData = SIM7600_Serial->read();
        if(rxData == ',') checkGPSData++;
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
                AT+CGPSHOT
            */

            // check if command is AT_CGPSHOT
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
    checkGPSData = 0;
}

void SIM7600::decodeGPSData(char *gpsData) {
    char *token;
    String gpsFields[9];  // Array to store latitude, longitude, date, time, etc.
    int fieldIndex = 0;

    if(checkGPSData !=8) return;
    if((strcmp(gpsData, ",,,,,,,,")) == 0) {
        isGPSData = 0;
        isGPSActive = 0;
        SIM7600_Serial->println("GPS data is not available");
        return;
    }

    // Split the input string by commas
    token = strtok(gpsData, ",");
    while (token != nullptr && fieldIndex < 9) {
        if (!isValidField(token)) {
            SIM7600_Serial->println("Invalid GPS data field");
            return;
        }
        gpsFields[fieldIndex++] = token;  // Store each field
        token = strtok(nullptr, ",");
    }


    // Combine latitude and direction
    String strLat = gpsFields[0] + gpsFields[1];  // Latitude + N/S

    // Combine longitude and direction
    String strLon = gpsFields[2] + gpsFields[3];  // Longitude + E/W

    // Set GPS data
    setGPS_String(strLat, strLon, gpsFields[4], gpsFields[5]);
    isGPSData = 1;
}

void SIM7600::setGPS_String(String lat, String lon, String date, String time){
    gpsData.Lattitude = lat;
    gpsData.Longitude = lon;
    gpsData.Date = date;
    gpsData.Time = time;
}

bool SIM7600::isValidField(const char *field) {
    while (*field) {
        if (!isalnum(*field) && *field != '.' && *field != '-') {
            return false;
        }
        field++;
    }
    return true;
}
