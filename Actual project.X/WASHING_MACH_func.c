#include<xc.h>
#include"WASH_MACH_func_header.h"
#include"main.h"
#include"timers.h"
#include"clcd.h"

char *washing_programs[] = {"Daily", "Heavy" , "Delicates", "Whites", "Stain wash" , "Ecocottons", "Woolens" , "Bed sheets", "Rinse+Dry" , "Dry only", "Wash only" , "Aqua store"};
unsigned char program_index = 0;

char *water_level[] = {"Auto","Low","Medium","High","Max"};
unsigned char level = 0;

unsigned char operational_mode ;
extern unsigned char reset_flag ;

unsigned char sec,min;
unsigned char Total_time, Wash_time , Rinse_time , Spin_time , Time;

void powering_on(void){
    
    for(unsigned char i=0;i<16;i++){
        clcd_putch(BLOCK,LINE1(i));
        __delay_ms(100);
    }
      clcd_putch(BLOCK,LINE1(1));
      clcd_putch(BLOCK,LINE1(2));
    clcd_print("Powering on",LINE2(2));
    clcd_print("Washing  machine",LINE3(0));
    
    for(unsigned char i=0;i<16;i++){
        clcd_putch(BLOCK,LINE4(i));
        __delay_ms(100);
    }
    __delay_ms(2000);
    
}
void washing_program_displaying(unsigned char key){
    if( reset_flag == RESET_WASHING_PROG_screen)
    {
        clear_screen();
        reset_flag = RESET_NOTHING;
    }
    if(key == SW4){
        clear_screen();
        program_index++;
        if(program_index == 12){
            program_index = 0;
        }
    }
    clcd_print("Washing Program:",LINE1(0));
    clcd_putch('>',LINE2(0));
    
    if(program_index <= 9 ){
        clcd_print(washing_programs[ program_index], LINE2(2));
        clcd_print(washing_programs[ program_index + 1], LINE3(2));
        clcd_print(washing_programs[ program_index + 2], LINE4(2));
    }
    else if(program_index == 10 ){
        clcd_print(washing_programs[ program_index], LINE2(2));
        clcd_print(washing_programs[ program_index + 1], LINE3(2));
        clcd_print(washing_programs[0], LINE4(2));
    }
    else if(program_index == 11 ){
        clcd_print(washing_programs[ program_index], LINE2(2));
        clcd_print(washing_programs[ 0 ], LINE3(2));
        clcd_print(washing_programs[ 1 ], LINE4(2));
    }
}
void water_lvl_screen_display(unsigned char key){
    if(reset_flag == RESET_WATER_LEVEL_screen){
        clear_screen();
        reset_flag = RESET_NOTHING;
    }
    
    if(key == SW4){
        clear_screen();
        level ++;
        if(level == 5 ){
            level = 0;
        }
    }
    clcd_print("WATER LEVEL:",LINE1(0));
    clcd_putch('*',LINE2(0));
    if(level <= 2){
    clcd_print(water_level[level],LINE2(1));
    clcd_print(water_level[level+1],LINE3(1));
    clcd_print(water_level[level+2],LINE4(1));
    }
    else if(level == 3){
        clcd_print(water_level[level], LINE2(1));
        clcd_print(water_level[level+1], LINE3(1));
        clcd_print(water_level[0], LINE4(1));
    }
    else if(level == 4){
        clcd_print(water_level[level], LINE2(1));
        clcd_print(water_level[0], LINE3(1));
        clcd_print(water_level[1], LINE4(1));
    }
}

void set_time(void){
    switch(program_index){
        case 0: // daily
            switch (level) {
                case 1:
                    min = 0;
                    sec = 33;
                    break;
                case 0:
                case 2:
                    min = 0;
                    sec = 41;
                    break;
                case 3:
                case 4:
                    min = 0;
                    sec = 45;
                    break;
            }
            break;
        case 1: //heavy
            switch (level) {
                case 1:
                    min = 0;
                    sec = 43;
                    break;
                case 0:
                case 2:
                    min = 0;
                    sec = 50;
                    break;
                case 3:
                case 4:
                    min = 0;
                    sec = 57;
                    break;
            }
            break;
        case 2: // delicates
            switch (level) {
                case 0:
                case 1:
                case 2:
                    min = 0;
                    sec = 26;
                    break;
                case 3:
                case 4:
                    min = 0;
                    sec = 31;
                    break;
            }
            break;
        case 3: // whites
            switch (level) {
                case 1:
                case 0:
                case 2:
                case 3:
                case 4:
                    min = 1;
                    sec = 16;
                    break;
            }
            break;
        case 4: // stain wash
            switch (level) {
                case 1:
                case 0:
                case 2:
                case 3:
                case 4:
                    min = 1;
                    sec = 36;
                    break;
            }
            break;
        case 5: //eco-cottons
            switch (level) {
                case 1:
                case 0:
                case 2:
                    min = 0;
                    sec = 31;
                    break;
                case 3:
                case 4:
                    min = 0;
                    sec = 36;
                    break;
            }
            break;
        case 6: // woolens
            switch (level) {
                case 1:
                case 0:
                case 2:
                case 3:
                case 4:
                    min = 0;
                    sec = 29;
                    break;
            }
            break;
        case 7: // bedsheet
            switch (level) {
                case 1:
                    min = 0;
                    sec = 46;
                    break;
                case 0:
                case 2:
                    min = 0;
                    sec = 53;
                    break;
                case 3:
                case 4:
                    min = 1;
                    sec = 0;
                    break;
            }
            break;
        case 8: // rinse+dry
            switch (level) {
                case 1:
                    min = 0;
                    sec = 18;
                    break;
                case 0:
                case 2:
                case 3:
                case 4:
                    min = 0;
                    sec = 20;
                    break;
            }
            break;
        case 9: // dry only
            switch (level) {
                case 1:
                case 0:
                case 2:
                case 3:
                case 4:
                    min = 0;
                    sec = 6;
                    break;
            }
            break;
        case 10: //wash only
            switch (level) {
                case 1:
                    min = 0;
                    sec = 16;
                    break;
                case 0:
                case 2:
                    min = 0;
                    sec = 21;
                    break;
                case 3:
                case 4:
                    min = 0;
                    sec = 26;
                    break;
            }
            break;
        case 11: //aqua store
            switch (level) {
                case 1:
                case 0:
                case 2:
                case 3:
                case 4:
                    min = 0;
                    sec = 50;
                    break;
            }
            break;
    }
}

void run_program(unsigned char key)
{   
    door_status_check();
    if (reset_flag == RESET_START_screen) {
        clear_screen();
        clcd_print("PROG:", LINE1(0));
        clcd_print(washing_programs[program_index], LINE1(5));
        clcd_print("TIME:", LINE2(0));

        clcd_putch(min / 10 + '0', LINE2(6));
        clcd_putch(min % 10 + '0', LINE2(7));
        clcd_putch(':', LINE2(8));
        clcd_putch(sec / 10 + '0', LINE2(9));
        clcd_putch(sec % 10 + '0', LINE2(10));

        reset_flag = RESET_NOTHING;

        __delay_ms(5000);
        clear_screen();
        clcd_print("Function:", LINE1(0));
        clcd_print("Time:", LINE2(0));

        clcd_print("RB4:START", LINE3(0));
        clcd_print("RB5:PAUSE", LINE4(0));

        
        Total_time = Time = min * 60 + sec;
        Wash_time = (int) Total_time * 0.46;
        Rinse_time = (int) Total_time * 0.12;
        Spin_time = (int) Total_time * 0.42;

        TMR2ON = 1;
        FAN = ON ;
        }
    if(key == SW6)
    {
        TMR2ON = 0;
        FAN = OFF ;
        operational_mode = PAUSE ;
    }
    Total_time = min * 60 + sec;
    if( program_index <= 7)
    {
        if(Total_time >= (Time - Wash_time)){
            clcd_print("WASH ",LINE1(10));
        }
        else if (Total_time >= (Time - Wash_time - Spin_time)){
            clcd_print("RINSE",LINE1(10));
        }
        else{
            clcd_print("SPIN ",LINE1(10));
        }
    }
    else if( program_index == 8)
    {
        if(Total_time >= (Time - 0.40* Time)){
            clcd_print("RINSE",LINE1(10));
        }
        else{
            clcd_print("SPIN ",LINE1(10));
        }
    }
    else if(program_index == 9){
        clcd_print("SPIN ",LINE1(10));
    }
    else if(program_index == 10){
        clcd_print("WASH ",LINE1(10));
    }
    else if(program_index == 11){
        clcd_print("RINSE",LINE1(10));
    }
    
    clcd_putch(min / 10 + '0', LINE2(6));
    clcd_putch(min % 10 + '0', LINE2(7));
    clcd_putch(':', LINE2(8));
    clcd_putch(sec / 10 + '0', LINE2(9));
    clcd_putch(sec % 10 + '0', LINE2(10));
    
        
    if (sec == 0 && min == 0) {
        clear_screen();
        FAN = OFF ;
        BUZZER = ON ;
        
        clcd_print("Done !!", LINE1(0));
        clcd_print("Remove clothes", LINE2(0));
        __delay_ms(2000);
        
        operational_mode = WASHING_PROGRAM_screen ;
        reset_flag = RESET_WASHING_PROG_screen ;
        BUZZER = OFF ;
        clear_screen();
    }
    

    
}
void door_status_check(void)
{
    if (RB0 == 0){
        FAN = OFF ;
        TMR2ON = 0;
        BUZZER = ON ;
        clear_screen();
        clcd_print("The door's open",LINE1(0));
        clcd_print("Please close It",LINE2(0));
        
        while(RB0 == 0)
        {
            ;
        }
        FAN = ON ;
        TMR2ON = 1;
        BUZZER = OFF ;
        clear_screen();
        
        clcd_print("Function:", LINE1(0));
        clcd_print("Time:", LINE2(0));
        clcd_print("RB4:START", LINE3(0));
        clcd_print("RB5:PAUSE", LINE4(0));  
    }
}

void clear_screen(void)
{
    clcd_write(CLEAR_DISP_SCREEN, INST_MODE);
    __delay_us(500);
}