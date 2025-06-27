#include<xc.h>
#include "main.h"
#include"clcd.h"
#include"digital_keypad.h"
#include"timers.h"
#include"WASH_MACH_func_header.h"

#pragma config WDTE = OFF
unsigned char key;  
unsigned char reset_flag = RESET_WASHING_PROG_screen ;
unsigned char operational_mode = WASHING_PROGRAM_screen ;


static void init_config(void){
    
    init_clcd();    
    
    init_digital_keypad();
    
    init_timer2();
    
    GIE = 1;
    PEIE = 1;
    BUZZER_DDR = 0;
    FAN_DDR = 0;
    BUZZER = OFF ;
    FAN = OFF ;
    
    
}

void main(void){
    init_config();
    
    clcd_print("Press RB4 to",LINE1(2));
    clcd_print("Power on the",LINE2(2));
    clcd_print("WASHING  MACHINE",LINE3(0));
    while (1) {
        key = read_digital_keypad(STATE);
        if (key == SW5) {
            break;
        }
        __delay_ms(50);
    }
    
    clear_screen();
    powering_on();
    
    while(1){
        key = read_digital_keypad(STATE);
        for(int delay = 500;delay--;);
        if(key == LPSW4 && operational_mode == WASHING_PROGRAM_screen)
        {
            operational_mode = WATER_LEVEL_screen;
            reset_flag = RESET_WATER_LEVEL_screen;
        }
        else if(key == LPSW4 && operational_mode == WATER_LEVEL_screen)
        {
            operational_mode = START_STOP_screen;
            clear_screen();
            
            clcd_print("RB4: START",LINE2(0));
            clcd_print("RB5: STOP",LINE3(0)); 
            set_time();
        }
        else if ( RB4 == 0  && operational_mode == PAUSE)
        {
            
            operational_mode = START_screen;
            TMR2ON = ON ;   
            FAN = ON;    
        }
        switch(operational_mode)
        {
            case WASHING_PROGRAM_screen:
                washing_program_displaying(key);
                break;
            case WATER_LEVEL_screen:
                water_lvl_screen_display(key);
                break;
            case START_STOP_screen:
            {
                clcd_print("PRESS SWITCH:",LINE1(0));
                if (key == SW5) {
                    operational_mode = START_screen;
                    reset_flag = RESET_START_screen;

                }
                else if (key == SW6) {
                    operational_mode = WASHING_PROGRAM_screen;
                    reset_flag = RESET_WASHING_PROG_screen;
                }
            }
                break;
            case START_screen:
                run_program(key);
                break;
        }
        
        
    }
    return;
}