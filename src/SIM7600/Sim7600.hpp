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
        // double latitude;
        // double longitude;
        // float date;  // DDMMYY
        // float time;  // HHMMSS
        // float altitude;
        // float speed;
        // float course;

        String Lat_str;
        String Lon_str;
        String Date_str;
        String Time_str;
        String Alt_str;      
        String Speed_str;       // Speed over ground. Unit: knots.
        String Course_str;      // Degrees. Unit: degrees.
    } gpsData;
public:
    
    // flag for GPS mode
    volatile bool isGPSActive = 0;
    volatile bool isGPSData = 0;

    // RX buffer for SIM7600
    uint16_t rxCount = 0;
    uint8_t rxData = 0;
    uint8_t rxBuffer[100];

    // flag for ATcommand
    volatile bool isATCGPS_ON = 0;
    volatile bool isATCGPS_OFF = 0;
    volatile bool isATCGPSINFO = 0;

    SIM7600();
    ~SIM7600();
    void GPS_Hotstart(HardwareSerial *serial);
    void GPS_Info(HardwareSerial *serial);
    void GPS_Receiver(HardwareSerial *serial, HardwareSerial *debug);
    void decodeGPSData(char *data);
    void resetBuffer();

    // get GPS Info:
    // double getLatitude() { return gpsData.latitude; }
    // double getLongitude() { return gpsData.longitude; }
    // float getDate() { return gpsData.date; }
    // float getTime() { return gpsData.time; }
    // float getAltitude() { return gpsData.altitude; }
    // float getSpeed() { return gpsData.speed; }
    // float getCourse() { return gpsData.course; }

    String getLatitude_str() { return gpsData.Lat_str; }
    String getLongitude_str() { return gpsData.Lon_str; }
    String getDate_str() { return gpsData.Date_str; }
    String getTime_str() { return gpsData.Time_str; }
    String getAltitude_str() { return gpsData.Alt_str; }
    String getSpeed_str() { return gpsData.Speed_str; }
    String getCourse_str() { return gpsData.Course_str; }

    void setLattitude(String lat){gpsData.Lat_str = lat;}
    void setLongitude(String lon){gpsData.Lon_str = lon;}
    void setDate(String date){gpsData.Date_str = date;}
    void setTime(String time){gpsData.Time_str = time;} 
    void setAltitude(String alt){gpsData.Alt_str = alt;}
    void setSpeed(String spd){gpsData.Speed_str = spd;}
    void setCourse(String course){gpsData.Course_str = course;}


    // void setGPSData(double lat, double lon, float date, float time, float alt, float spd);
    void setGPS_String(String lat, String lon, String date, String time, String alt, String spd);

};



#endif // SIM7600_HPP