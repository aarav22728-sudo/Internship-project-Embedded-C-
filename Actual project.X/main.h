/* 
 * File:   main.h
 * Author: user
 *
 * Created on June 18, 2025, 10:17 PM
 */

#ifndef MAIN_H
#define	MAIN_H

#include<xc.h>
#include"clcd.h"
#include"digital_keypad.h"
#include"timers.h"
#include"WASH_MACH_func_header.h"

#define WASHING_PROGRAM_screen    0x01
#define WATER_LEVEL_screen        0x02
#define START_STOP_screen         0x03
#define START_screen              0x04

#define RESET_WASHING_PROG_screen  0x11
#define RESET_NOTHING              0x88
#define RESET_START_screen         0x55
#define RESET_WATER_LEVEL_screen   0x44
#define PAUSE                      0x77

#define BUZZER                    RC1
#define FAN                       RC2
#define BUZZER_DDR                TRISC1
#define FAN_DDR                   TRISC2


#define ON             1
#define OFF            0

#endif	/* MAIN_H */

