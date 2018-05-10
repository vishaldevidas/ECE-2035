#include "map.h"

#include "globals.h"
#include "graphics.h"

unsigned int numBuckets = 10;

/**
 * The Map structure. This holds a HashTable for all the MapItems, along with
 * values for the width and height of the Map.
 */
struct Map {
    HashTable* items;
    int w, h;
};

/**
 * Storage area for the maps.
 * This is a global variable, but can only be access from this file because it
 * is static.
 */
static Map map;
static Map house;
static int active_map;
/**
 * The first step in HashTable access for the map is turning the two-dimensional
 * key information (x, y) into a one-dimensional unsigned integer.
 * This function should uniquely map (x,y) onto the space of unsigned integers.
 */
static unsigned XY_KEY(int X, int Y){
    // TODO: Fix me!
    return ((X + Y)*(X + Y + 1)/2 + Y);
}

/**
 * This is the hash function actually passed into createHashTable. It takes an
 * unsigned key (the output of XY_KEY) and turns it into a hash value (some
 * small non-negative integer).
 */
unsigned map_hash(unsigned key)
{
    // TODO: Fix me!
    return key%numBuckets;
}

void maps_init()
{
    // TODO: Implement!    
    // Initialize hash table
    // Set width & height
//    if(!active_map){
    map.items = createHashTable(map_hash, numBuckets);
    map.w = 50;
    map.h = 50;
//    }
//    else{
    house.items = createHashTable(map_hash, numBuckets);
    house.w = 10;
    house.h = 9;
//    }
    
}

Map* get_active_map()
{
    // There's only one map
    if(!active_map)
    return &map;
    else
    return &house;
}

Map* set_active_map(int m)
{
    active_map = m;
    if(!active_map)
    return &map;
    else
    return &house;
}

void print_map()
{
    // As you add more types, you'll need to add more items to this array.
    char lookup[] = {'W', 'P'};
    for(int y = 0; y < map_height(); y++)
    {
        for (int x = 0; x < map_width(); x++)
        {
            MapItem* item = get_here(x,y);
            if (item) pc.printf("%c", lookup[item->type]);
            else pc.printf(" ");
        }
        pc.printf("\r\n");
    }
}

int map_width()
{
    if(!active_map)
    return map.w;
    else
    return house.w;
}

int map_height()
{
   if(!active_map)
    return map.h;
    else
    return house.h;
}

int map_area()
{
    if(!active_map)
    return (map.h)*(map.w);
    else
    return (house.h)*(house.w);
}

MapItem* get_north(int x, int y)
{
    unsigned int key = XY_KEY(x,y-1);
    if(!active_map)
    return (MapItem*)getItem(map.items,key);
    else
    return (MapItem*)getItem(house.items,key);
}

MapItem* get_south(int x, int y)
{
    unsigned int key = XY_KEY(x,y+1);
    return (MapItem*)getItem(map.items,key);
}

MapItem* get_east(int x, int y)
{
    unsigned int key = XY_KEY(x+1,y);
    if(!active_map)
    return (MapItem*)getItem(map.items,key);
    else
    return (MapItem*)getItem(house.items,key);
}

MapItem* get_west(int x, int y)
{
    unsigned int key = XY_KEY(x-1,y);
    if(!active_map)
    return (MapItem*)getItem(map.items,key);
    else
    return (MapItem*)getItem(house.items,key);
}

MapItem* get_here(int x, int y)
{
    unsigned int key = XY_KEY(x,y);
    if(!active_map)
    return (MapItem*)getItem(map.items,key);
    else
    return (MapItem*)getItem(house.items,key);
}


void map_erase(int x, int y)
{
    unsigned int key = XY_KEY(x,y);
    if(!active_map)
    free((MapItem*)removeItem(map.items,key));
    else
    free((MapItem*)removeItem(house.items,key));
}

void add_wall(int x, int y, int dir, int len)
{
    for(int i = 0; i < len; i++)
    {
        MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
        w1->type = WALL;
        w1->draw = draw_wall;
        //w1->drawMove = NULL;
        w1->walkable = false;
        w1->data = NULL;
        unsigned key = (dir == HORIZONTAL) ? XY_KEY(x+i, y) : XY_KEY(x, y+i);
        void* val = insertItem(get_active_map()->items, key, w1);
        if (val) free(val); // If something is already there, free it
    }
}

/*void add_plant(int x, int y)
{
    MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
    w1->type = PLANT;
    w1->draw = draw_plant;
    w1->drawMove = NULL;
    w1->walkable = true;
    w1->data = NULL;
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), w1);
    if (val) free(val); // If something is already there, free it
}*/
void add_tree(int x, int y)
{
    MapItem* tree = (MapItem*) malloc(sizeof(MapItem));
    tree->type = TREE;
    tree->draw = draw_tree;
    tree->drawMove = NULL;
    tree->walkable = false;
    tree->data = FALSE;
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), tree);
    if (val) free(val);   
}
void add_appleTree(int x, int y)
{
    MapItem* appleTree = (MapItem*) malloc(sizeof(MapItem));
    appleTree->type = APPLETREE;   
    appleTree->draw = draw_tree;
    appleTree->drawMove = NULL;
    appleTree->walkable = false;
    appleTree->data = FULL;
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), appleTree);
    if (val) free(val);   
}
 void add_ncp1(int x, int y)
{
    MapItem* npc = (MapItem*) malloc(sizeof(MapItem));
    npc->type = NPC1;
    npc->draw = draw_npc1;
    npc->drawMove = NULL;
    npc->walkable = false;
    npc->data = 0;
    void* val = insertItem(get_active_map()->items, XY_KEY(x,y), npc);
    if (val) free(val);
}

 void add_ncp2(int x, int y)
{
    MapItem* npc = (MapItem*) malloc(sizeof(MapItem));
    npc->type = NPC2;
    npc->draw = draw_npc2;
    npc->drawMove = NULL;
    npc->walkable = false;
    npc->data = 0;
    void* val = insertItem(get_active_map()->items, XY_KEY(x,y), npc);
    if (val) free(val);
}
void add_door1(int x, int y)
{
    MapItem* door1 = makeDoor(x,y-1,draw_door11);
    MapItem* door2 = makeDoor(x,y,draw_door12);
    MapItem* door3 = makeDoor(x,y+1,draw_door13);
    MapItem* door4 = makeDoor(x+1,y-1,draw_door14);
    MapItem* door5 = makeDoor(x+1,y,draw_door15);
    MapItem* door6 = makeDoor(x+1,y+1,draw_door16);
}

void add_house(int x, int y)
{
    MapItem* house = (MapItem*) malloc(sizeof(MapItem));
    house->type = HOUSE;
    house->draw = draw_house;
    house->drawMove = NULL;
    house->walkable = false;
    house->data = 0;
    void* val = insertItem(get_active_map()->items, XY_KEY(x,y), house);
    if (val) free(val);
}

void add_fire(int x, int y)
{
    MapItem* fire = (MapItem*) malloc(sizeof(MapItem));
    fire->type = FIRE;
    fire->draw = draw_fire;
    fire->drawMove = NULL;
    fire->walkable = true;
    fire->data = 0;
    void* val = insertItem(get_active_map()->items, XY_KEY(x,y), fire);
    if (val) free(val);
}

void add_book(int x,int y)
{   
    MapItem* book = (MapItem*) malloc(sizeof(MapItem));
    book->type = BOOK;
    book->draw = draw_BOOK;
    book->drawMove = NULL;
    book->walkable = false;
    book->data = 0;
    void* val = insertItem(get_active_map()->items, XY_KEY(x,y), book);
    if (val) free(val);
}

void add_chest(int x,int y)
{   
    MapItem* chest = (MapItem*) malloc(sizeof(MapItem));
    chest->type = CHEST;
    chest->draw = draw_chest;
    chest->drawMove = NULL;
    chest->walkable = false;
    chest->data = 0;
    void* val = insertItem(get_active_map()->items, XY_KEY(x,y), chest);
    if (val) free(val);
}

void add_diamond(int x,int y)
{   
    MapItem* diamond = (MapItem*) malloc(sizeof(MapItem));
    diamond->type = DIAMOND;
    diamond->draw = draw_diamond;
    diamond->drawMove = NULL;
    diamond->walkable = false;
    diamond->data = 0;
    void* val = insertItem(get_active_map()->items, XY_KEY(x,y), diamond);
    if (val) free(val);
}

void add_Open_door1(int x, int y)
{
    MapItem* door1 = makeDoor(x,y-1,draw_Open_door11);
    MapItem* door2 = makeDoor(x,y,draw_Open_door12);
    door2->walkable = true;
    MapItem* door3 = makeDoor(x,y+1,draw_Open_door13);
    MapItem* door4 = makeDoor(x+1,y-1,draw_door14);
    MapItem* door5 = makeDoor(x+1,y,draw_door15);
    door5->walkable = true;
    MapItem* door6 = makeDoor(x+1,y+1,draw_door16);
}

MapItem* makeDoor(int x, int y, DrawFunc draw){
    MapItem* door = (MapItem*) malloc(sizeof(MapItem));
    door->type = DOOR1;
    door->draw = draw;
    door->drawMove = NULL;
    door->walkable = false;
    door->data = 0;
    void* val = insertItem(get_active_map()->items, XY_KEY(x,y), door);
    if (val) free(val);
    
    return door;
}


