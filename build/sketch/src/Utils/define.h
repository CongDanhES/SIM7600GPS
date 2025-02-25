#line 1 "C:\\TTD\\CONG DANH\\GPS\\src\\Utils\\define.h"
#ifndef DEFINE_H
#define DEFINE_H    

#include "config.h"
#include <STM32FreeRTOS.h>

// USART1: PB10-PB11
HardwareSerial Sim7600_port(SIM7600_PORT);

// USART1: PA2-PA3
HardwareSerial Debug_port(DEBUG_PORT);

#include "src/SIM7600/Sim7600.hpp"
SIM7600 sim7600;
#endif // DEFINE_H