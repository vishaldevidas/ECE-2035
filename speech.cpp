#include "speech.h"

#include "globals.h"
#include "hardware.h"

/**
 * Draw the speech bubble background.
 */
static void draw_speech_bubble();

/**
 * Erase the speech bubble.
 */
static void erase_speech_bubble();

/**
 * Draw a single line of the speech bubble.
 * @param line The text to display
 * @param which If TOP, the first line; if BOTTOM, the second line.
 */
#define TOP    0
#define BOTTOM 1
static void draw_speech_line(const char* line, int which);

/**
 * Delay until it is time to scroll.
 */
static void speech_bubble_wait();

void draw_speech_bubble()
{
    uLCD.filled_rectangle(3,94,123,114,BLACK);
}

void erase_speech_bubble()
{
    uLCD.filled_rectangle(3,94,123,114,BLACK);
}

void draw_speech_line(const char* line, int which)
{
    if(!which)
    uLCD.locate(1,12);
    if(which)
    uLCD.locate(1,13);
    if(line)
    uLCD.printf("%s",line);
    
}

void speech_bubble_wait()
{   
    wait(1);
}

void speech(const char* line1, const char* line2)
{
    draw_speech_bubble();
    draw_speech_line(line1, TOP);
    draw_speech_line(line2, BOTTOM);
    speech_bubble_wait();
    //erase_speech_bubble();
}

void long_speech(const char* lines[], int n)
{
    
}
