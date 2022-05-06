#include "Item.h"


Item ::Item(b2World& _pWorld, b2Vec2 _pos, ItemMem *_parentItemMem, int _nb_item) : Entity(pWorld, b2Vec2(1, 1), _pos) {
    parentItemMem = _parentItemMem;
    nb_item = _nb_item;
    pWorld = _pWorld;
}



