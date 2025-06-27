#include <xc.h>
#include "timers.h"

void init_timer2(void)
{
    
    
    
    // enable timer2 interrupt
    TMR2IE = 1;

    
    //no of ticks in PR2
    PR2 = 250;
    
    //SWITCHING TIMER 2 OFF
    TMR2ON = 0;
}
