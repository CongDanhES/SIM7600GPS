#line 1 "C:\\TTD\\CONG DANH\\GPS\\src\\SIM7600\\Sim7600.hpp"
#ifndef SIM7600_HPP
#define SIM7600_HPP

#include "Arduino.h"
#include <string.h>

#define AT                  "AT"
#define AT_CGPS_ON          "AT+CGPS=1"
#define AT_CGPS_OFF         "AT+CGPS=0"  
#define AT_CGPSINFO         "AT+CGPSINFO"
#define AT_CGPSHOT          "AT+CGPSHOT"

class SIM7600
{
private:
    /* data */
    struct GPSData
    {
        String Lattitude;
        String Longitude;
        String Date;
        String Time;
    } gpsData;
    HardwareSerial *SIM7600_Serial;
public:
    
    // flag for GPS mode
    bool isGPSActive = 0;
    bool isGPSData = 0;

    // RX buffer for SIM7600_Serial
    uint16_t rxCount = 0;
    uint8_t rxData = 0;
    uint8_t rxBuffer[100];
    uint8_t checkGPSData = 0;

    // flag for ATcommand
    bool isATCGPS_ON = 0;
    bool isATCGPS_OFF = 0;
    bool isATCGPSINFO = 0;
    uint8_t timeout = 0;

    SIM7600(HardwareSerial *serial);
    ~SIM7600();
    void GPS_Hotstart();
    void GPS_Info();
    void GPS_Receiver(HardwareSerial *debug);
    void decodeGPSData(char *data);
    void resetBuffer();

    // Getter
    String getLatitude() { return gpsData.Lattitude; }
    String getLongitude() { return gpsData.Longitude ; }
    String getDate() { return gpsData.Date; }
    String getTime() { return gpsData.Time; }

    // void setGPSData(double lat, double lon, float date, float time, float alt, float spd);
    void setGPS_String(String lat, String lon, String date, String time);
    bool isValidField(const char *field);
};



#endif // SIM7600_HPP