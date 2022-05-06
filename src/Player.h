#ifndef _PLAYER_
#define _PLAYER_

#include "../inc/RPTypes.h"
#include "../inc/Box2D/box2d.h"
#include "Inventory.h"
//#include "Item.h"
#include "ItemMem.h"
#include "Entity.h"
#include "Chunk.h"
#include <string>
#include <map>


class Player : public Entity {
public:
    int life;
    float exp;
    float base_damage, base_mining_speed;
    
    //Inventaire
    Inventory inventory;
    int selected_slot;


    Player(std::map<int, ItemMem> & items_list, b2World& pWorld, b2Vec2 pos);

    b2Vec2 get_pos() const;

    void drop_item(b2World& _pWorld, b2Vec2 _pos, int index, int quantity);

    
    /**
     * @brief Récupère l'index du slot sélectionné
     * 
     * @return int l'index du slot sélectionné
     */
    int get_selected_slot() const;

    /**
     * @brief Change le slot sélectionné. dir = false: vers la gauche  |  dir = true: vers la droite
     * 
     * @param dir 
     */
    void cycle_slot(bool dir);


private:
    int level;
    
    
    ItemMem itemMem;
    //Item p_item;
 


};

#endif