#include <xc.h>
#include "timers.h"

void init_timer2(void)
{
    //no of ticks in PR2
    PR2 = 250;
    
    // enable timer2 interrupt
    TMR2IE = 1;

    
    
    
    
    //SWITCHING TIMER 2 OFF
    TMR2ON = 0;
}
