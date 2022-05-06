#ifndef _ITEM_
#define _ITEM_
#include "ItemMem.h"
#include "Entity.h"
#include "../inc/Box2D/box2d.h"

class Item : public Entity{
    public:
    Item (b2World& _pWorld, b2Vec2 _pos, ItemMem *parentItemMem, int _nb_item);
    ~Item();
    b2World &pWorld;
    ItemMem *parentItemMem;
    int nb_item;


};

#endif