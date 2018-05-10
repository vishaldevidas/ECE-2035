// Project includes
#include "globals.h"
#include "hardware.h"
#include "map.h"
#include "graphics.h"
#include "speech.h"

// Functions in this file
int get_action (GameInputs inputs);
int update_game (int action);
void draw_game (int init);
void init_main_map ();
void init_house_map();
int Do_Action(MapItem* item);
void ncp1_action(MapItem* item);
void ncp2_action(MapItem* item);

int DEBUG = 0;

int main ();

/**
 * The main game state. Must include Player locations and previous locations for
 * drawing to work properly. Other items can be added as needed.
 */
struct {
    int x,y;    // Current locations
    int px, py; // Previous locations
    int quest;
    int has_key; //
    int has_book;
    int map;
    int applesGot;
    int lives;
    int HP;
    bool ncp1Meeting;
    bool ncp2Meeting;
    bool ghostMode; // Omnipotient Mode;
    bool menu;
} Player;

/**
 * Given the game inputs, determine what kind of update needs to happen.
 * Possbile return values are defined below.
 */
#define NO_ACTION 0
#define ACTION_BUTTON 1
#define MENU_BUTTON 2
#define OMNI_BUTTON 3 // my addition
#define DROP_BUTTON 8
#define GO_LEFT 4
#define GO_RIGHT 5
#define GO_UP 6
#define GO_DOWN 7
int get_action(GameInputs inputs)
{
    //uLCD.printf("%d,%d",inputs.ax,inputs.ay);
    if(!inputs.b1) return ACTION_BUTTON;
    if(!inputs.b2) return MENU_BUTTON;
    if(!inputs.b3) return OMNI_BUTTON;
    if(!inputs.b4) return DROP_BUTTON;
    if((inputs.ax)*(inputs.ax) > (inputs.ay)*(inputs.ay)){ 
        if(inputs.ax > 0.2)
        return GO_RIGHT;
        if(inputs.ax < -0.2)
        return GO_LEFT;
    }
    if((inputs.ax)*(inputs.ax) < (inputs.ay)*(inputs.ay)){ 
        if(inputs.ay > 0.2)
        return GO_UP;
        if(inputs.ay < -0.2)
        return GO_DOWN;
    } 
    return NO_ACTION;
}

/**
 * Update the game state based on the user action. For example, if the user
 * requests GO_UP, then this function should determine if that is possible by
 * consulting the map, and update the Player position accordingly.
 * 
 * Return values are defined below. FULL_DRAW indicates that for this frame,
 * draw_game should not optimize drawing and should draw every tile, even if
 * the player has not moved.
 */
#define NO_RESULT 0
#define GAME_OVER 1
#define FULL_DRAW 2
#define FAIL 3
int update_game(int action)
{
    // Save player previous location before updating
    Player.px = Player.x;
    Player.py = Player.y;
    
    // Do different things based on the each action.
    // You can define functions like "go_up()" that get called for each case.
    switch(action)
    {
        case GO_UP: MapItem* itemN = get_north(Player.x,Player.y);
                    if(itemN->walkable || Player.ghostMode) Player.y = Player.y-1;
                    return FULL_DRAW;
                    
        case GO_LEFT: MapItem* itemW = get_west(Player.x,Player.y);
                    if(itemW->walkable || Player.ghostMode) Player.x = Player.x-1; 
                    return FULL_DRAW;
                               
        case GO_DOWN: MapItem* itemS = get_south(Player.x,Player.y);
                    if(itemS->walkable || Player.ghostMode) Player.y = Player.y+1;
                    return FULL_DRAW;   
                    
        case GO_RIGHT: MapItem* itemE = get_east(Player.x,Player.y);
                    if(itemE->walkable || Player.ghostMode) Player.x = Player.x+1;
                    return FULL_DRAW;  
                    
        case ACTION_BUTTON: if(Player.menu) return FAIL;
                            int action;
                            action = Do_Action(get_north(Player.x,Player.y));
                            if(action == GAME_OVER) return action;
                            action = Do_Action(get_west(Player.x,Player.y));
                            if(action == GAME_OVER) return action;
                            action = Do_Action(get_south(Player.x,Player.y));
                            if(action == GAME_OVER) return action;
                            action = Do_Action(get_east(Player.x,Player.y));
                            if(action == GAME_OVER) return action;
                            
                            if(NO_ACTION) return action;
                            return FULL_DRAW;
                    
        case MENU_BUTTON: if(!Player.menu){
                          menu(Player.quest);
                          Player.menu = true;
                          }//else{
//                            Player.menu = !Player.menu;
//                            draw_game(FULL_DRAW);
//                            return FULL_DRAW;
//                         }
                          break;
                    
        case OMNI_BUTTON: Player.ghostMode = !Player.ghostMode;
                            if(Player.ghostMode)print_ghost();
                            else clear_ghost();
                          break;
        case DROP_BUTTON: if(Player.applesGot > 0){
                            Player.applesGot--;
                          }
                          break;
    }
    return NO_RESULT;
}

int Do_Action(MapItem* item){
    switch(item->type){
        case NPC1: ncp1_action(item);
                  return FULL_DRAW;
        case NPC2: ncp2_action(item);
                  return FULL_DRAW;
        case TREE: Player.applesGot++;
                   return FULL_DRAW;
        case BOOK: Player.has_book = 1;
                   map_erase(1, 1);
                   draw_game(FULL_DRAW);
                   Player.quest = 5; 
                   return FULL_DRAW;
        case CHEST: map_erase(31, 21);
                    draw_game(FULL_DRAW);
                    add_diamond(31,21);
                    draw_game(FULL_DRAW);
                    return FULL_DRAW;;
        case DIAMOND: map_erase(31, 21);
                      //print_diamond();
                      draw_game(FULL_DRAW); 
                      return GAME_OVER;
        case HOUSE:
            switch(Player.map){
                case 0: if(Player.ncp2Meeting || DEBUG){
                            init_house_map();
                            set_active_map(1);
                            print_book();
                            Player.map = 1;
                            Player.x = 1;
                            Player.y = 6;
                            draw_game(FULL_DRAW);
                            break;
                        }
                case 1: if(Player.has_book || DEBUG){
                            init_main_map();
                            set_active_map(0);
                            print_book();
                            Player.map = 0;
                            Player.x = 29;
                            Player.y = 16;
                            MapItem* npc2 = get_here(31, 19);
                            npc2->data++;
                            draw_game(FULL_DRAW);
                            break;
                        }
                        else{
                            char* line1;
                            char* line2;
                            line1 = "Get the book!";
                            line2 = "";
                            speech(line1,line2);
                            return FULL_DRAW;
                        }
            }
            return FULL_DRAW;
        case DOOR1: if(Player.has_key){
                        add_Open_door1(19,28);
                        draw_game(FULL_DRAW);
                        clear_item();
                        Player.quest = 3;
                        mySpeaker.PlayNote(500.0,0.1,0.1);
                        mySpeaker.PlayNote(600.0,0.1,0.1);
                    }
                    else{
                        char* line1;
                        char* line2;
                        line1 = "You need a Key";
                        line2 = "to open.";
                        speech(line1,line2);
                    } 
                    return FULL_DRAW;
        default : return NO_RESULT;
    }
}

void ncp1_action(MapItem* item){
    char* line1;
    char* line2;
    switch(item->data){
        case 0:
                line1 = "I know what you";
                line2 = "are looking for.";
                speech(line1,line2);
                line1 = "Bring me 6 appl";
                line2 = "es and I will ";
                speech(line1,line2);
                line1 = "help you in ret";
                line2 = "urn.";
                speech(line1,line2);
                Player.quest = 1;
                item->data++;
                print_apple();
                Player.applesGot = 0;
                Player.ncp1Meeting = true;
                break;
        case 1:
                if(Player.applesGot < 6){
                    line1 = "That's not 6, go";
                    line2 = "get more.";
                    speech(line1,line2);
                }
                else{
                    line1 = "WOW! you did it!";
                    line2 = "";
                    speech(line1,line2);
                    line1 = "I'll keep my pr";
                    line2 = "omise. ";
                    speech(line1,line2);
                    line1 = "here you Go.";
                    line2 = "This will get";
                    speech(line1,line2);
                    line1 = "you there.";
                    line2 = "";
                    speech(line1,line2);
                    item->data++;
                    clear_item();
                    clear_item_count();
                    print_key();
                    Player.has_key = 1;
                    Player.applesGot = NULL;
                    Player.ncp1Meeting = false;
                    mySpeaker.PlayNote(500.0,0.1,0.1);
                    mySpeaker.PlayNote(600.0,0.1,0.1);
                    Player.quest = 2;
                    }
                    break;
        default:
                line1 = "I did what I ";
                line2 = "could.......";
                speech(line1,line2);
                
                
    }
}

void ncp2_action(MapItem* item){
    char* line1;
    char* line2;
    switch(item->data){
        case 0: line1 = "I'm guessing you";
                line2 = "already meet him";
                speech(line1,line2);
                line1 = "Bring me";
                line2 = "the book of spell";
                speech(line1,line2);
                line1 = "and you will get";
                line2 = "what you want.";
                speech(line1,line2);
                Player.quest = 4;
                item->data++;
                print_book();
                Player.has_book = 0;
                Player.ncp2Meeting = true;
                break;
        
        case 1: if(!Player.has_book){
                    line1 = "You need to";
                    line2 = "get the book";
                    speech(line1,line2);
                    line1 = "for me to";
                    line2 = "help you!";
                    speech(line1,line2);
                }
                else{
                    line1 = "Haha!";
                    line2 = "";
                    speech(line1,line2);
                    line1 = "you pass the";
                    line2 = "test. ";
                    speech(line1,line2);
                    line1 = "here you Go.";
                    line2 = "go get the";
                    speech(line1,line2);
                    line1 = "Diamond!!.";
                    line2 = "";
                    speech(line1,line2);
                    item->data++;
                    clear_item();
                    clear_item_count();
                    Player.ncp2Meeting = false;
                    add_chest(31,21);
                    draw_game(FULL_DRAW);
                    mySpeaker.PlayNote(500.0,0.1,0.1);
                    mySpeaker.PlayNote(600.0,0.1,0.1);
                    Player.quest = 6;
                }
                    break;
                
        default:
                line1 = "Go on!";
                line2 = "GET IT!!";
                speech(line1,line2);
    }
}


/**
 * Entry point for frame drawing. This should be called once per iteration of
 * the game loop. This draws all tiles on the screen, followed by the status 
 * bars. Unless init is nonzero, this function will optimize drawing by only 
 * drawing tiles that have changed from the previous frame.
 */
void draw_game(int init)
{
    // Draw game border first
    if(init) draw_border();
    //uLCD.locate(0,15);
    //uLCD.printf("%d",Player.menu);
//    uLCD.printf("%d,: %d",Player.lives,Player.HP);
    // Iterate over all visible map tiles
    for (int i = -5; i <= 5; i++) // Iterate over columns of tiles
    {
        for (int j = -4; j <= 4; j++) // Iterate over one column of tiles
        {
            // Here, we have a given (i,j)
            
            // Compute the current map (x,y) of this tile
            int x = i + Player.x;
            int y = j + Player.y;
            
            // Compute the previous map (px, py) of this tile
            int px = i + Player.px;
            int py = j + Player.py;
                        
            // Compute u,v coordinates for drawing
            int u = (i+5)*11 + 3;
            int v = (j+4)*11 + 15;
            
            // Figure out what to draw
            DrawFunc draw = NULL;
            //DrawMovingFunc drawMove = NULL;
            //int state;
            if (init && i == 0 && j == 0) // Only draw the player on init
            {
                if(x == 20 && y == 28)
                draw_door15(u,v);
                else
                draw_player(u, v, Player.has_key);
                if(x > 19)Player.has_key = 0;
                continue;
            }
            else if (x >= 0 && y >= 0 && x < map_width() && y < map_height()) // Current (i,j) in the map
            {
                MapItem* curr_item = get_here(x, y);
                MapItem* prev_item = get_here(px, py);
                
                if (init || curr_item != prev_item) // Only draw if they're different
                {
                    if (curr_item) // There's something here! Draw it
                    {
                                               
                        draw = curr_item->draw;
                    }
                    else // There used to be something, but now there isn't
                    {
                        draw = draw_nothing;
                    }
                    if(Player.menu)Player.menu = false;
                }
            }
            else if (init) // If doing a  but we're out of bounds, draw the walls.
            {
                draw = draw_wall;
            }

            // Actually draw the tile
            if (draw) draw(u, v);
           // if (drawMove) drawMove(u,v,state);
        }
    }

    // Draw status bars    
    draw_upper_status(Player.lives,Player.HP);
    draw_lower_status(Player.x,Player.y,Player.px,Player.py);
    
    if(Player.applesGot && Player.ncp1Meeting){
        uLCD.locate(2,0);
        uLCD.printf("%d",Player.applesGot);
    }
    if(Player.ncp2Meeting){
        checkBook(Player.has_book);
    }
        
}


/**
 * Initialize the main world map. Add walls around the edges, interior chambers,
 * and plants in the background so you can see motion.
 */
void init_main_map()
{
    // "Random" plants
    Map* map = set_active_map(0);
    
    for(int i = map_width() + 7; i < map_area(); i += 39)
    {
        add_tree(i / map_width(), i % map_width());
    }
        
    pc.printf("Adding walls!\r\n");
    add_wall(0,              0,              HORIZONTAL, map_width());
    add_wall(0,              map_height()-1, HORIZONTAL, map_width());
    add_wall(0,              0,              VERTICAL,   map_height());
    add_wall(map_width()-1,  0,              VERTICAL,   map_height());
    add_wall(map_width()-(2*(map_width()/3)-1),0, VERTICAL, (map_height()/2)+2);
    add_wall(map_width()-(2*(map_width()/3)-1),30,VERTICAL,map_height() - (map_height()/2)+2);
    pc.printf("Walls done!\r\n");
    
    add_door1(19,28);
    add_ncp1(10,10);
    add_ncp2(31,19);
    add_house(29,15);
    
    print_map();
}

void init_house_map()
{
    Map* map = set_active_map(1);
    
    add_wall(0,              0,              HORIZONTAL, map_width());
    add_wall(0,              map_height()-1, HORIZONTAL, map_width());
    add_wall(0,              0,              VERTICAL,   map_height());
    add_wall(map_width()-1,  0,              VERTICAL,   map_height());
    add_house(1,7);
    
    for(int i = 5; i < 9; i++){
        add_fire(i,4);
    }
    for(int i = 1; i < 5; i++){
        add_fire(i,2);
    }
    add_book(1,1);
    
    print_map();
}
/**
 * Program entry point! This is where it all begins.
 * This function orchestrates all the parts of the game. Most of your
 * implementation should be elsewhere - this holds the game loop, and should
 * read like a road map for the rest of the code.
 */
int main()
{
    // First things first: initialize hardware
    ASSERT_P(hardware_init() == ERROR_NONE, "Hardware init failed!");
    
    //Start screen
    DisplayStartGame();
    uLCD.cls();

    // Initialize the maps
    maps_init();
    init_main_map();
    
    // Initialize game state
    set_active_map(0);
    if(DEBUG)
    Player.x = Player.y = 25;///////////////////////////////////// 5
    else
    Player.x = Player.y = 5;
    Player.lives = 3;
    Player.HP = 100;
    Player.map = 0;
    Player.menu = false;
    Player.quest = 0;
    // Initial drawing
    draw_game(true);
    Player.ghostMode = false;

    // Main game loop
    while(1)
    {
        // Timer to measure game update speed
        Timer t; t.start();
        int action = get_action(read_inputs());
        //while(action != ACTION_BUTTON || action != MENU_BUTTON) action = get_action(read_inputs());
        int gameUpdate = update_game(action);
        if((get_here(Player.x,Player.y))->type == FIRE){
            Player.HP = Player.HP-25;
            mySpeaker.PlayNote(100.0,0.25,0.1);
            if(Player.HP < 1){
                Player.HP = 100;
                Player.lives--;
                if(Player.lives < 1)gameUpdate = FAIL;
            }
                        
        }
        
        if(gameUpdate == GAME_OVER){
            DisplayGameOver();
            break;
        }else draw_game(gameUpdate);
        if(gameUpdate == FAIL){
            DisplayGameFail();
            break;
        }
        // Actuall do the game update:
        // 1. Read inputs        
        // 2. Determine action (get_action)        
        // 3. Update game (update_game)
        // 3b. Check for game over
        // 4. Draw frame (draw_game)
        
        // 5. Frame delay
        t.stop();
        int dt = t.read_ms();
        if (dt < 100) wait_ms(100 - dt);
    }
}
