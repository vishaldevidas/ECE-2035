#ifndef GRAPHICS_H
#define GRAPHICS_H


/**
 * Draws the player. This depends on the player state, so it is not a DrawFunc.
 */
void draw_player(int u, int v, int key);
void draw_npc1(int u, int v);
void draw_npc2(int u, int v);

/**
 * Takes a string image and draws it to the screen. The string is 121 characters
 * long, and represents an 11x11 tile in row-major ordering (across, then down,
 * like a regular multi-dimensional array). The available colors are:
 *      R = Red
 *      Y = Yellow
 *      G = Green
 *      D = Brown ("dirt")
 *      5 = Light grey (50%)
 *      3 = Dark grey (30%)
 *      Any other character is black
 * More colors can be easily added by following the pattern already given.
 */
void draw_img(int u, int v, const char* img);

/**
 * DrawFunc functions. 
 * These can be used as the MapItem draw functions.
 */
void draw_nothing(int u, int v);
void draw_wall(int u, int v);
//void draw_plant(int u, int v);
void draw_tree(int u, int v);
void draw_BOOK(int u,int v);
void draw_fire(int u,int v);

void draw_door11(int u, int v);
void draw_door12(int u, int v);
void draw_door13(int u, int v);
void draw_door14(int u, int v);
void draw_door15(int u, int v);
void draw_door16(int u, int v);
void draw_Open_door11(int u, int v);
void draw_Open_door12(int u, int v);
void draw_Open_door13(int u, int v);
void draw_house(int u, int v);
void draw_chest(int u,int v);
//void draw_tree(int u, int v, int state);

/**
 * Draw the upper status bar.
 */
void draw_upper_status(int lives,int HP);

/**
 * Draw the lower status bar.
 */ 
void draw_lower_status(int u,int v, int uP, int vP);

/**
 * Draw the border for the map.
 */
void draw_border();

void draw_diamond(int u, int v);
void print_apple();
void print_diamond();
void print_key();
void print_book();
void print_ghost();
void checkBook(int has);
void clear_item();
void clear_ghost();
void clear_item_count();

void DisplayStartGame();
void DisplayGameOver();
void DisplayGameFail();
void menu(int quest);
#endif // GRAPHICS_H