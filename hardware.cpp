// This header has all the (extern) declarations of the globals.
// "extern" means "this is instantiated somewhere, but here's what the name
// means.
#include "globals.h"

#include "hardware.h"

// We need to actually instantiate all of the globals (i.e. declare them once
// without the extern keyword). That's what this file does!

// Hardware initialization: Instantiate all the things!
uLCD_4DGL uLCD(p9,p10,p11);             // LCD Screen (tx, rx, reset)
//SDFileSystem sd(p5, p6, p7, p8, "sd");  // SD Card(mosi, miso, sck, cs)
Serial pc(USBTX,USBRX);                 // USB Console (tx, rx)
MMA8452 acc(p28, p27, 100000);        // Accelerometer (sda, sdc, rate)
DigitalIn ActionButton(p21);                 // Pushbuttons (pin)
DigitalIn MenuButton(p22);
DigitalIn OmniButton(p23);
DigitalIn DropButton(p24);
AnalogOut DACout(p18);                  // Speaker (pin)
PwmOut speaker(p26);
Speaker mySpeaker(p26);
wave_player waver(&DACout);



// Some hardware also needs to have functions called before it will set up
// properly. Do that here.
int hardware_init()
{
    // Crank up the speed
    uLCD.baudrate(3000000);
    pc.baud(115200);
        
    //Initialize pushbuttons
    ActionButton.mode(PullUp); 
    MenuButton.mode(PullUp);
    OmniButton.mode(PullUp);
    DropButton.mode(PullUp);
    
    return ERROR_NONE;
}

GameInputs read_inputs() 
{
    GameInputs in;
    
    in.b1 = ActionButton;
    in.b2 = MenuButton;
    in.b3 = OmniButton;
    in.b4 = DropButton;
    
    /*double *Ax = &in.ax;
    double *Ay = &in.ay;
    acc.readXGravity(Ax);
    acc.readYGravity(Ay);
    in.ax = *Ax;
    in.ay = *Ay;*/
    
    acc.readXYZGravity(&in.ax,&in.ay,&in.az);
    
    return in;
}
