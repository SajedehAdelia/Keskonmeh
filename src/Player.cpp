#include "Player.h"

using namespace std;

Player::Player(std::map<int, ItemMem> & items_list, b2World& pWorld, b2Vec2 pos) : Entity(pWorld, b2Vec2(0.9, 1.8), pos), inventory(9) {
    inventory.set_item(&items_list[1], 0, 10);
    inventory.set_item(&items_list[10], 1, 1);
    selected_slot = 0;
    life = 1;
    base_damage = 1;
    base_mining_speed = 1;
    exp = 0;
    level = 0;
}

b2Vec2 Player::get_pos() const {
    return body->GetPosition();
}

void Player::cycle_slot(bool dir) {
    if(dir)
        selected_slot++;
    else
        selected_slot--;
}

int Player::get_selected_slot() const {
    return selected_slot;
}