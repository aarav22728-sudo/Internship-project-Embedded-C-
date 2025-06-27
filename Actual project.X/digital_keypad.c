#include <xc.h>
#include "digital_keypad.h"

void init_digital_keypad(void)
{
    /* Set Keypad Port as input */
    KEYPAD_PORT_DDR = KEYPAD_PORT_DDR | INPUT_LINES;
}


unsigned char read_digital_keypad(unsigned char mode)
{
    static unsigned char once = 1;
    static unsigned char longpressed = 1;
    static unsigned char pre_key;
    unsigned char key = KEYPAD_PORT & INPUT_LINES;
    if(key != ALL_RELEASED && once ){
        once = 0;
        longpressed = 0;
        pre_key = key;
        
    }
    else if(key == ALL_RELEASED && !once){
        once = 1;
        if(longpressed <30)
        return pre_key;
    }    
    else if (!once && longpressed <= 30){
        longpressed++;
    }
    else if(!once && longpressed == 31 && key == SW4)
    {
        longpressed ++;
        return LPSW4;
    }
    
    return ALL_RELEASED;
}

