#include "graphics.h"

#include "globals.h"

#define YELLOW 0xFFFF00
#define BROWN  0xD2691E
#define DIRT   BROWN
#define _ 0x000000 //BLACK 
#define X 0xFFFFFF //WHITE
#define G 0x00FF00 //GREEN
#define F 0x228B22 //Forest GREEN
#define V 0X006400 //DARK GREEN
#define R 0xFF0000 //RED
#define B 0x0000FF //BLUE
#define O 0xFFA500 //ORANGE
#define Y 0xFFFF00 //YELLOW
#define D 0xD2691E //BROWN
#define L 0xD3D3D3 // Light Gray
#define W 0x808080 // Gray


// PLAYER SPRITES
int NPC1_sprite[11 * 11] = {
F,V,F,B,B,V,F,V,R,R,R,
V,F,V,B,B,B,V,V,R,R,R,
F,V,F,B,B,B,B,V,R,R,R,
V,F,V,D,O,O,O,V,V,Y,V,
F,V,D,O,O,O,O,O,F,Y,V,
V,F,B,B,B,O,O,B,V,Y,V,
F,V,F,B,B,B,B,V,F,Y,V,
V,F,V,D,D,D,D,V,V,Y,V,
F,V,B,B,B,B,B,B,F,Y,V,
V,B,B,B,B,B,B,B,B,Y,V,
V,F,X,X,V,F,X,X,V,Y,V,

};

int NPC2_sprite[11 * 11] = {
F,V,F,V,F,V,F,V,B,B,B,
V,F,V,D,D,D,V,V,B,R,B,
F,V,D,D,D,D,D,V,B,B,B,
V,F,V,D,O,O,O,V,V,Y,V,
F,V,D,O,O,O,O,O,F,Y,V,
V,F,D,X,X,O,O,X,V,Y,V,
F,V,F,D,X,X,X,V,F,Y,V,
V,F,V,B,B,B,B,V,V,Y,V,
F,V,D,D,D,D,D,D,F,Y,V,
V,D,D,D,D,D,D,D,D,Y,V,
V,F,_,_,V,F,_,_,V,Y,V,

};

int Player_sprite[11 * 11] = {
F,V,_,_,_,_,_,_,F,V,V,
V,_,_,_,_,O,_,_,V,F,V,
F,V,_,O,_,O,O,V,F,V,V,
V,F,V,O,O,O,O,O,V,F,V,
F,V,R,R,R,O,O,V,R,V,V,
V,R,R,B,B,B,B,R,O,F,V,
F,O,O,B,B,R,B,R,O,V,V,
V,F,O,D,D,D,D,D,V,F,V,
F,V,X,X,V,X,D,V,F,V,V,
V,F,D,D,F,D,D,V,V,F,V,
V,F,_,_,V,D,_,_,V,F,V,
};

int Player_HasKey_sprite[11 * 11] = {
F,V,_,_,_,_,_,_,F,V,V,
V,_,_,_,_,O,_,_,V,F,V,
F,V,_,O,_,O,O,V,F,V,V,
V,F,V,O,O,O,O,O,V,F,V,
F,V,R,R,R,O,O,V,R,V,V,
V,R,R,B,B,B,B,R,O,F,V,
F,O,O,B,B,R,B,R,O,V,V,
V,F,O,D,D,D,D,D,Y,F,V,
F,V,X,X,V,X,D,V,Y,Y,V,
V,F,D,D,F,D,D,V,Y,F,V,
V,F,_,_,V,D,_,_,V,F,V,
};

//OBJECT SPRITES
int Diamond_sprite[6 * 6] = {
F,V,F,V,F,V,
V,B,B,B,B,F,
B,X,B,X,X,B,
B,X,X,X,X,B,
F,B,X,X,B,F,
V,F,B,B,F,V,
};

/*int DiamondICON_sprite[6 * 6] = {
_,_,_,_,_,_,
_,B,B,B,B,_,
B,B,X,X,B,B,
B,X,B,B,X,B,
_,B,X,X,B,_,
_,_,B,B,_,_,
};*/

int Apple_sprite[10 * 8] = {
_,_,_,_,_,D,_,_,
_,_,_,_,D,_,_,_,
_,R,R,D,_,R,R,_,
R,R,R,R,R,R,R,R,
R,R,R,R,R,R,R,R,
R,R,R,R,R,R,R,R,
R,R,R,R,R,R,R,R,
_,R,_,R,R,_,R,_,
};

int KEY_sprite[10 * 8] = {
_,_,_,Y,Y,_,_,_,
_,_,_,Y,Y,Y,Y,_,
_,_,_,Y,Y,Y,_,_,
_,_,_,Y,Y,Y,Y,_,
_,_,_,Y,Y,_,_,_,
_,_,X,Y,Y,X,_,_,
_,_,Y,_,_,Y,_,_,
_,_,Y,Y,Y,Y,_,_,
};

int book_sprite[10 * 8] = {
_,_,_,_,_,_,_,_,
_,_,_,D,D,D,D,D,
_,_,D,B,B,B,D,X,
_,D,B,B,B,D,X,D,
D,D,D,D,D,X,D,_,
D,X,X,X,X,D,_,_,
D,D,D,D,D,_,_,_,
_,_,_,_,_,_,_,_,
};

int tick_sprite[10 * 8] = {
_,_,_,_,_,_,_,_,
_,_,_,_,_,_,F,F,
_,_,_,_,_,F,F,_,
_,_,_,_,F,F,_,_,
_,F,_,F,F,_,_,_,
_,F,F,F,_,_,_,_,
_,_,F,_,_,_,_,_,
_,_,_,_,_,_,_,_,
};

int cross_sprite[10 * 8] = {
_,_,_,_,_,_,_,_,
_,R,_,_,_,_,R,_,
_,R,R,_,_,R,R,_,
_,_,_,R,R,_,_,_,
_,_,_,R,R,_,_,_,
_,R,R,_,_,R,R,_,
_,R,_,_,_,_,R,_,
_,_,_,_,_,_,_,_,
};

int ghostMode_sprite[10 * 8] = {
_,_,_,X,X,X,_,_,
_,_,X,X,X,X,X,_,
_,X,X,_,X,_,X,X,
_,X,X,X,X,X,X,X,
_,X,X,X,X,X,X,X,
_,X,X,X,X,X,X,X,
_,X,X,X,X,X,X,X,
_,X,X,_,X,_,X,X,
};

int BOOK_sprite[11 * 11] = {
F,V,F,V,F,V,F,V,F,V,V,
V,F,V,V,V,D,D,D,D,D,D,
F,V,F,V,D,B,B,B,B,D,X,
V,F,V,D,B,B,B,B,D,X,X,
F,V,D,B,B,B,B,D,X,X,D,
V,D,B,B,B,B,D,X,X,D,V,
D,D,D,D,D,D,X,X,D,V,V,
D,X,X,X,X,X,X,D,V,F,V,
D,D,D,D,D,D,D,V,F,V,V,
V,F,V,V,V,F,V,V,V,F,V,
V,F,V,F,V,F,V,F,V,F,V,
};

//MAP ITEMS SPRITES
int Wall_sprite[11 * 11] = {
W,W,W,W,W,W,W,W,W,W,W,
W,L,W,L,L,W,L,L,W,L,W,
W,W,W,W,W,W,W,W,W,W,W,
W,L,L,W,L,L,W,L,L,W,W,
W,W,W,W,W,W,W,W,W,W,W,
W,L,W,L,L,W,L,L,W,L,W,
W,W,W,W,W,W,W,W,W,W,W,
W,L,L,W,L,L,W,L,L,W,W,
W,W,W,W,W,W,W,W,W,W,W,
W,L,W,L,L,W,L,L,W,L,W,
W,W,W,W,W,W,W,W,W,W,W,
};
//DOOR1 SPRITE
int DOOR11_sprite[11 * 11] = {
W,W,W,W,W,W,W,W,W,W,W,
W,W,W,W,W,W,W,W,W,W,W,
W,W,W,W,L,L,W,L,L,W,W,
L,L,W,W,W,W,W,W,W,W,W,
W,W,W,W,W,W,L,L,W,L,L,
L,L,W,L,W,W,W,W,W,W,W,
W,W,W,W,W,W,W,L,W,L,L,
L,L,W,L,L,W,W,W,W,W,W,
W,W,W,W,W,W,W,W,W,L,L,
L,L,W,L,W,D,W,W,W,W,W,
W,W,W,W,D,D,D,W,W,L,L,
};

int DOOR12_sprite[11 * 11] = {
F,V,F,D,D,D,D,W,W,W,W,
V,F,V,D,D,D,D,W,W,L,L,
F,V,F,D,D,D,D,W,W,W,W,
V,F,V,D,D,D,D,W,W,L,L,
F,V,F,D,D,D,Y,W,W,W,W,
V,F,V,D,D,Y,Y,W,W,L,L,
F,V,F,D,Y,Y,Y,W,W,W,W,
V,F,V,Y,Y,Y,D,W,W,L,L,
F,V,F,Y,Y,D,D,W,W,W,W,
V,F,V,Y,D,D,D,W,W,L,L,
F,V,F,D,D,D,D,W,W,W,W,
};

int DOOR13_sprite[11 * 11] = {
F,V,F,D,D,D,D,W,W,L,L,
V,F,V,D,D,D,D,W,W,W,W,
F,V,F,D,D,D,W,W,W,L,L,
V,F,V,D,D,D,W,W,W,W,W,
F,V,F,D,D,W,W,L,W,L,L,
V,F,V,D,D,W,W,W,W,W,W,
F,V,F,D,W,W,L,L,W,L,L,
V,F,V,D,W,W,W,W,W,W,W,
F,V,F,W,W,W,L,L,W,L,L,
V,F,W,W,W,W,W,W,W,W,W,
W,W,W,L,L,W,L,L,W,L,L,
};

int DOOR14_sprite[11 * 11] = {
W,W,F,V,F,V,F,V,F,V,V,
W,W,V,V,V,F,V,V,V,F,V,
W,W,W,V,F,V,F,V,F,V,V,
W,W,W,W,F,V,F,V,F,V,V,
L,L,W,W,W,V,F,V,F,V,V,
W,W,W,W,W,F,V,V,V,F,V,
L,L,W,L,W,W,F,V,F,V,V,
W,W,W,W,W,W,V,V,V,F,V,
L,L,W,L,L,W,W,V,F,V,V,
W,L,L,W,L,W,W,V,V,F,V,
W,W,W,W,W,W,W,W,V,F,V,
};

int DOOR15_sprite[11 * 11] = {
L,L,W,L,L,W,W,W,F,V,V,
W,W,W,W,W,W,W,W,V,F,V,
L,L,W,L,L,W,W,W,F,V,V,
W,W,W,W,W,W,W,W,V,F,V,
L,L,W,L,L,W,W,W,F,V,V,
W,W,W,W,W,W,W,W,V,F,V,
L,L,W,L,L,W,W,W,F,V,V,
W,W,W,W,W,W,W,W,V,F,V,
L,L,W,L,L,W,W,W,F,V,V,
W,W,W,W,W,W,W,W,V,F,V,
L,L,W,L,L,W,W,W,V,F,V,
};

int DOOR16_sprite[11 * 11] = {
W,L,L,W,L,L,W,W,F,V,V,
W,W,W,W,W,W,W,W,V,F,V,
W,L,L,W,L,W,W,V,F,V,V,
W,W,W,W,W,W,W,V,V,F,V,
W,L,L,W,W,W,F,V,F,V,V,
W,W,W,W,W,W,V,V,V,F,V,
W,L,L,W,W,V,F,V,F,V,V,
W,W,W,W,W,F,V,V,V,F,V,
W,L,W,W,F,V,F,V,F,V,V,
W,W,W,V,V,F,V,V,V,F,V,
W,W,V,F,V,F,V,F,V,F,V,
};

int DOOR11_Open_sprite[11 * 11] = {
W,W,W,W,W,W,W,W,W,W,W,
W,W,W,W,W,W,W,W,W,W,W,
W,W,W,W,L,L,W,L,L,W,W,
L,L,W,W,W,W,W,W,W,W,W,
W,W,W,W,W,W,L,L,W,L,L,
L,L,W,L,W,W,W,W,W,W,W,
W,W,W,W,W,W,W,L,W,L,L,
L,L,W,L,L,W,W,W,W,W,W,
W,W,W,W,W,W,W,W,W,L,L,
L,L,W,L,W,F,W,W,W,W,W,
W,W,W,W,F,V,F,W,W,L,L,
};

int DOOR12_Open_sprite[11 * 11] = {
F,V,F,V,F,V,F,W,W,W,W,
V,F,V,F,V,F,V,W,W,L,L,
F,V,F,V,F,V,F,W,W,W,W,
V,F,V,F,V,F,V,W,W,L,L,
F,V,F,V,F,V,V,W,W,W,W,
V,F,V,F,V,V,F,W,W,L,L,
F,V,F,V,F,V,V,W,W,W,W,
V,F,V,F,V,F,F,W,W,L,L,
F,V,F,V,F,V,F,W,W,W,W,
V,F,V,Y,V,F,V,W,W,L,L,
F,V,F,V,F,V,F,W,W,W,W,
};

int DOOR13_Open_sprite[11 * 11] = {
F,V,F,V,F,V,F,W,W,L,L,
V,F,V,F,V,F,V,W,W,W,W,
F,V,F,V,F,V,W,W,W,L,L,
V,F,V,F,V,F,W,W,W,W,W,
F,V,F,V,F,W,W,L,W,L,L,
V,F,V,F,V,W,W,W,W,W,W,
F,V,F,V,W,W,L,L,W,L,L,
V,F,V,F,W,W,W,W,W,W,W,
F,V,F,W,W,W,L,L,W,L,L,
V,F,W,W,W,W,W,W,W,W,W,
W,W,W,L,L,W,L,L,W,L,L,
};

int Grass_sprite[11 * 11] = {
F,V,F,V,F,V,F,V,F,V,V,
V,F,V,V,V,F,V,V,V,F,V,
F,V,F,V,F,V,F,V,F,V,V,
V,F,V,V,V,F,V,V,V,F,V,
F,V,F,V,F,V,F,V,F,V,V,
V,F,V,V,V,F,V,V,V,F,V,
F,V,F,V,F,V,F,V,F,V,V,
V,F,V,V,V,F,V,V,V,F,V,
F,V,F,V,F,V,F,V,F,V,V,
V,F,V,V,V,F,V,V,V,F,V,
V,F,V,F,V,F,V,F,V,F,V,
};

// MAP ITEM SPRITES

int APPLETREE2_sprite[11 * 11] = {
F,V,F,G,G,G,G,G,G,V,V,
V,F,G,G,G,G,G,R,R,G,V,
F,G,G,G,G,G,G,R,R,G,G,
G,G,G,R,R,G,G,G,G,G,G,
G,G,G,R,R,G,G,G,G,G,G,
V,G,G,G,G,G,G,G,G,G,V,
V,G,G,D,D,D,D,D,G,G,V,
V,F,V,V,D,D,D,V,V,F,V,
F,V,F,V,D,D,D,V,F,V,V,
V,F,V,D,D,D,D,D,V,F,V,
V,F,V,D,V,D,V,D,V,F,V,
};

/*int PLANT_sprite[11 * 11] = {
F,V,F,V,F,V,F,V,F,V,V,
V,F,V,V,V,F,V,V,V,F,V,
F,V,F,V,F,V,F,V,F,V,V,
V,F,V,V,V,F,V,V,V,F,V,
F,V,F,V,F,V,F,V,F,V,V,
V,G,F,G,F,G,G,F,F,G,V,
F,F,G,F,G,F,F,G,G,F,V,
V,G,F,F,G,F,F,F,F,G,V,
F,F,G,G,F,G,F,G,G,V,G,
G,F,G,F,G,G,G,G,F,G,V,
V,G,F,G,F,G,F,F,G,F,V,
};*/

int FIRE_sprite[11 * 11] = {
F,V,F,V,Y,V,F,V,F,V,F,
V,F,V,F,V,Y,V,F,Y,Y,V,
F,Y,F,Y,F,Y,F,Y,F,V,Y,
Y,F,V,Y,Y,Y,Y,Y,V,Y,V,
F,Y,Y,Y,O,O,O,Y,Y,V,F,
V,Y,Y,O,O,O,O,O,Y,Y,V,
Y,O,O,O,O,R,O,O,O,Y,Y,
Y,O,O,O,R,O,O,R,O,O,Y,
Y,O,R,O,O,R,O,R,O,O,Y,
Y,O,O,R,R,R,R,O,O,O,Y,
Y,O,O,R,R,R,R,O,O,O,Y,
};

int house_sprite[11 * 11] = {
F,V,F,V,F,D,F,V,F,V,V,
V,F,V,V,D,B,D,V,V,F,V,
F,V,F,D,B,B,B,D,F,V,V,
V,F,D,B,B,B,B,B,D,F,V,
F,D,D,D,D,D,D,D,D,D,V,
D,F,D,D,D,D,D,D,D,F,D,
F,V,D,D,D,D,D,D,D,V,V,
V,F,D,D,D,D,D,D,D,F,V,
F,V,D,D,D,Y,D,D,D,V,V,
V,F,D,D,D,Y,D,D,D,F,V,
V,F,D,D,D,Y,D,D,D,F,V,
};

int chest_sprite[11 * 11] = {
F,V,F,V,F,V,F,V,F,V,V,
V,F,V,V,V,F,V,V,V,F,V,
Y,Y,F,V,F,V,F,V,F,Y,Y,
Y,Y,D,D,Y,Y,Y,D,D,Y,Y,
Y,Y,D,D,Y,Y,Y,D,D,Y,Y,
Y,_,_,_,Y,Y,Y,_,_,_,Y,
Y,Y,D,D,D,Y,D,D,D,Y,Y,
Y,Y,Y,D,D,Y,D,D,Y,Y,Y,
F,V,F,V,F,V,F,V,F,V,V,
V,F,V,V,V,F,V,V,V,F,V,
V,F,V,F,V,F,V,F,V,F,V,
};

void draw_player(int u, int v, int key)
{
    //uLCD.filled_rectangle(u, v, u+11, v+11, RED);
    if(!key)
    uLCD.BLIT(u, v, 11, 11, Player_sprite);
    else
    uLCD.BLIT(u, v, 11, 11, Player_HasKey_sprite);
}

void draw_npc1(int u, int v)
{
    uLCD.BLIT(u, v, 11, 11, NPC1_sprite);
}

void draw_npc2(int u, int v)
{
    uLCD.BLIT(u, v, 11, 11, NPC2_sprite);
}

void draw_img(int u, int v, const char* img)
{
    int colors[11*11];
    for (int i = 0; i < 11*11; i++)
    {
        if (img[i] == 'R') colors[i] = RED;
        else if (img[i] == 'Y') colors[i] = YELLOW;
        else if (img[i] == 'G') colors[i] = GREEN;
        else if (img[i] == 'D') colors[i] = DIRT;
        else if (img[i] == '5') colors[i] = LGREY;
        else if (img[i] == '3') colors[i] = DGREY;
        else colors[i] = BLACK;
    }
    uLCD.BLIT(u, v, 11, 11, colors);
    wait_us(250); // Recovery time!
}

void draw_nothing(int u, int v)
{
    // Fill a tile with blackness
    //uLCD.filled_rectangle(u, v, u+10, v+10, BLACK);
    uLCD.BLIT(u, v, 11, 11, Grass_sprite);
}

void draw_wall(int u, int v)
{
    //uLCD.filled_rectangle(u, v, u+10, v+10, BROWN);
    uLCD.BLIT(u, v, 11, 11, Wall_sprite);
}

void draw_chest(int u,int v)
{
    uLCD.BLIT(u, v, 11, 11, chest_sprite);
}

/*void draw_plant(int u, int v)
{
    //uLCD.filled_rectangle(u, v, u+10, v+10, GREEN);
    uLCD.BLIT(u, v, 11, 11, PLANT_sprite);
}*/

/*void draw_tree(int u, int v, int state)
{
    switch(state){
        case 1: uLCD.BLIT(u, v, 11, 11, APPLETREE1_sprite);
                break;
        case 2: uLCD.BLIT(u, v, 11, 11, APPLETREE2_sprite);
                break;
        default: uLCD.BLIT(u, v, 11, 11, TREE_sprite);
    }
}*/

void draw_tree(int u, int v)
{
    uLCD.BLIT(u, v, 11, 11, APPLETREE2_sprite);
}

/*void draw_appleTree1(int u, int v)
{
    uLCD.BLIT(u, v, 11, 11, APPLETREE1_sprite);
}*/

void draw_diamond(int u, int v)
{
    uLCD.BLIT(u, v, 6, 6, Diamond_sprite);
}

void draw_fire(int u, int v)
{
    uLCD.BLIT(u, v, 11, 11, FIRE_sprite);
}

void draw_BOOK(int u,int v)
{
    uLCD.BLIT(u, v, 11, 11, BOOK_sprite);
}

void draw_upper_status(int lives, int HP)
{
    // Draw bottom border of status bar
    uLCD.line(0, 9, 128, 9, GREEN);
    uLCD.filled_rectangle(30,2,128,5,BLACK);
    uLCD.rectangle(90,2,103,5,GREEN);
    uLCD.rectangle(107,2,127,5,RED);
    switch(lives){
        case 3: uLCD.filled_rectangle(100,2,103,5,GREEN);
        case 2: uLCD.filled_rectangle(95,2,98,5,GREEN);
        case 1: uLCD.filled_rectangle(90,2,93,5,GREEN);
                break;
        default: uLCD.filled_rectangle(90,2,128,5,BLACK);
    }
    if(lives > 0){
    uLCD.filled_rectangle((107+((100-HP)/25)*4),2,127,5,RED);
    }
    // Add other status info drawing code here
}

void draw_lower_status(int u,int v,int uP,int vP)
{
    // Draw top border of status bar
    uLCD.line(0, 118, 128, 118, GREEN);
    if(u != uP || v != vP)
    uLCD.filled_rectangle(25,119,128,128,BLACK);
    uLCD.locate(11,15);
    uLCD.printf("[%d,%d]",u,v);
    
    // Add other status info drawing code here
}

void draw_border()
{
    uLCD.filled_rectangle(0,     9, 127,  14, WHITE); // Top
    uLCD.filled_rectangle(0,    13,   2, 114, WHITE); // Left
    uLCD.filled_rectangle(0,   114, 127, 117, WHITE); // Bottom
    uLCD.filled_rectangle(124,  14, 127, 117, WHITE); // Right
}

void print_apple()
{
    uLCD.BLIT(0, 0, 8, 10, Apple_sprite);
}

void print_key()
{
    uLCD.BLIT(0, 0, 8, 10, KEY_sprite);
}

void print_book()
{
    uLCD.BLIT(0, 0, 8, 10, book_sprite);
}

/*void print_diamond()
{
    uLCD.BLIT(2, 2, 6, 6, DiamondICON_sprite);
}*/

void checkBook(int has)
{
    if(has)
    uLCD.BLIT(10, 0, 8, 10, tick_sprite);
    else
    uLCD.BLIT(10, 0, 8, 10, cross_sprite);
}

void print_ghost()
{
    uLCD.BLIT(0,122,8,10,ghostMode_sprite);   
}

void clear_ghost()
{
    uLCD.filled_rectangle(0,122,10,128, BLACK);
}
void clear_item()
{
    uLCD.filled_rectangle(0,0,7,8, BLACK);
}
 void clear_item_count()
{
    uLCD.filled_rectangle(0,0,28,8, BLACK);
}

void draw_door11(int u, int v){
    uLCD.BLIT(u, v-1, 11, 11, DOOR11_sprite);
}

void draw_door12(int u, int v){
    uLCD.BLIT(u, v, 11, 11, DOOR12_sprite);
}
void draw_door13(int u, int v){
    uLCD.BLIT(u, v+1, 11, 11, DOOR13_sprite);
}
void draw_door14(int u, int v){
    uLCD.BLIT(u+1, v-1, 11, 11, DOOR14_sprite);
}
void draw_door15(int u, int v){
    uLCD.BLIT(u+1, v, 11, 11, DOOR15_sprite);
}
void draw_door16(int u, int v){
    uLCD.BLIT(u+1, v+1, 11, 11, DOOR16_sprite);
}

void draw_Open_door11(int u, int v){
    uLCD.BLIT(u, v-1, 11, 11, DOOR11_Open_sprite);
}

void draw_Open_door12(int u, int v){
    uLCD.BLIT(u, v, 11, 11, DOOR12_Open_sprite);
}
void draw_Open_door13(int u, int v){
    uLCD.BLIT(u, v+1, 11, 11, DOOR13_Open_sprite);
}

void draw_house(int u, int v){
    uLCD.BLIT(u, v, 11, 11, house_sprite);
}

void DisplayStartGame(){
    
    uLCD.filled_rectangle(10,20,118,108,BLACK);
    uLCD.locate(7,6);
    uLCD.printf("MBED\n");
    uLCD.locate(4,9);
    uLCD.printf("ADVENTURES!");
    
    //draw_player(58,75,1);
    
    float note[18]= {1568.0,1396.9,1244.5,1244.5,1396.9,1568.0,1568.0,1568.0,1396.9,
                 1244.5,1396.9,1568.0,1396.9,1244.5,1174.7,1244.5,1244.5, 0.0
                };
    float duration[18]= {0.48,0.24,0.72,0.48,0.24,0.48,0.24,0.24,0.24,
                     0.24,0.24,0.24,0.24,0.48,0.24,0.48,0.48, 0.0
                    };
    for(int i=0; i < 18; i++){                
        mySpeaker.PlayNote(note[i],duration[i],0.1);
    }
    uLCD.cls();
}

void DisplayGameOver(){
    uLCD.filled_rectangle(10,20,118,108,BLACK);
    uLCD.locate(7,6);
    uLCD.printf("GAME\n");
    uLCD.locate(4,7);
    uLCD.printf("COMPLETED!");
    
    float note[18]= { 0.0,1396.9,1244.5,1244.5,1396.9,1568.0,1568.0,1568.0,1396.9,
                 1244.5,1396.9,1568.0,1396.9,1244.5,1174.7,1244.5,1244.5,1568.0
                };
    float duration[18]= {0.0,0.72,0.72,0.48,0.24,0.48,0.24,0.24,0.24,
                     0.24,0.24,0.24,0.24,0.48,0.24,0.48,0.48, 0.48
                    };
    for(int i=18; i > 0; i--){                
        mySpeaker.PlayNote(note[i],duration[i],0.1);
    }
}

void DisplayGameFail(){
    uLCD.filled_rectangle(10,20,118,108,BLACK);
    uLCD.locate(7,6);
    uLCD.printf("GAME\n");
    uLCD.locate(7,7);
    uLCD.printf("OVER!");
    uLCD.locate(5,9);
    uLCD.printf("you lost");
    
    mySpeaker.PlayNote(400.0,0.25,0.1); 
    mySpeaker.PlayNote(300.0,0.25,0.1);
    mySpeaker.PlayNote(200.0,0.25,0.1);
    mySpeaker.PlayNote(100.0,0.25,0.1);
}

void menu(int quest){
    uLCD.filled_rectangle(10,20,118,108,BLACK);
    uLCD.locate(2,3);
    switch(quest){
        case 0: uLCD.printf("Find the wizard");
                break;
        case 1: uLCD.printf("Connect ");
                uLCD.locate(2,4);
                uLCD.printf("6 apples");
                break;
        case 2: uLCD.printf("Find the gate");
                break;
        case 3: uLCD.printf("Find the second ");
                uLCD.locate(2,4);
                uLCD.printf("wizard");
                break;
        case 4: uLCD.printf("Go find the book");
                break;
        case 5: uLCD.printf("Give the book to ");
                uLCD.locate(2,4);
                uLCD.printf("the wizard");
                break;
        case 6: uLCD.printf("Go get the ");
                uLCD.locate(2,4);
                uLCD.printf("Diamond!!");
                break;
    }
    uLCD.locate(2,10);
    uLCD.printf("action to quit");
    wait(1);
}