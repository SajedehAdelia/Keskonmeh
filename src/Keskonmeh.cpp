#include "Keskonmeh.h"
#include <iostream>

#include <string>
//#include <filesystem>

Keskonmeh::Keskonmeh() : blocks_list(load_blocks()), items_list(load_items()), 
    map(blocks_list, items_list), 
    player(items_list, map.physicalWorld, b2Vec2(15, 18))
{
    last_update = std::chrono::steady_clock::now();
    dt = 1/120.;
    difficulty = 1;
}

std::map<int, ItemMem> Keskonmeh::load_items() {
    std::map<int, ItemMem> items_buffer;

    std::string path = "data/item";

    /*
    for (const auto & entry : std::filesystem::directory_iterator(path)) {
        ItemMem item;
        
        //Charge les données du fichier dans block
        //Si aucune erreur: enregistrer dans blocks_list
        if(item.load(entry.path())) {
            items_buffer[item.id] = item;
        }
    }
    */
    ItemMem item;
    if(item.load("data/item/grass.kkm"))
        items_buffer[item.getId()] = item;
    
    if(item.load("data/item/pickaxe.kkm"))
        items_buffer[item.getId()] = item;

    if(item.load("data/item/stone.kkm"))
        items_buffer[item.getId()] = item;

    if(item.load("data/item/sword.kkm"))
        items_buffer[item.getId()] = item;

    return items_buffer;
}


std::map<int, BlockMem> Keskonmeh::load_blocks() {
    std::map<int, BlockMem> blocks_buffer;
    std::string path = "data/block";

    /*
    for (const auto & entry : std::filesystem::directory_iterator(path)) {
        BlockMem block;
        //Charge les données du fichier dans block
        //Si aucune erreur: enregistrer dans blocks_list
        if(block.load(entry.path()))
            blocks_list[block.id] = block;
        std::cout << block.id << " " << blocks_list[block.id].name << " " << &blocks_list[block.id] << std::endl;
    }
    */

    BlockMem block;
    if(block.load("data/block/air.kkm"))
        blocks_list[block.id] = block;

    if(block.load("data/block/grass.kkm"))
        blocks_list[block.id] = block;

    if(block.load("data/block/stone.kkm"))
        blocks_list[block.id] = block;

    return blocks_buffer;
}

void Keskonmeh::update() {
    std::chrono::duration<double> elapsed_time = std::chrono::steady_clock::now() - last_update;
    
    if(elapsed_time.count() >= dt ) {
        map.update_physics(dt);
        last_update = std::chrono::steady_clock::now();
    }

    b2Vec2 tmp = player.get_pos();
    float2 player_pos = float2(tmp.x, tmp.y);
    map.scroll_chunks(player_pos);
    //player.body->SetTransform(b2Vec2(player_pos.x, player_pos.y), 0.f);
}


void Keskonmeh::do_player_action(float3 action_offset) {
    //On récupère l'item sélectionné
    int item_count;
    ItemMem* selected_item = player.inventory.get_slot(player.selected_slot, item_count);

    b2Vec2 tmp = player.get_pos();
    float2 player_pos = float2(tmp.x, tmp.y);

    int3 action_pos = int3(player_pos.x + action_offset.x, player_pos.y + action_offset.y, action_offset.z);

    if(selected_item == NULL)
        return;
    //Si il est placable (= bloc)
    if(selected_item->type == ITEM_PLACABLE) {
        if(map.place_block(action_pos, &blocks_list[selected_item->dropped_block_id]))
            player.inventory.remove_item(player.selected_slot, 1);
    }
    //S'il permet de casser des blocs
    if(selected_item->type == ITEM_PICKAXE) {
        //On récupère le block
        BlockMem* broken_block = map.get_block(action_pos);
        //S'il est minable
        if(broken_block->minable) {
            //On récupère l'item associé (on réutilise la variable selected_item)
            selected_item = &items_list[broken_block->item_id];
            
            //On remplace par de l'air
            map.set_block(action_pos, &blocks_list[AIR]);
            //On ajoute le block à l'inventaire
            player.inventory.fill_in(selected_item, 1);
        }
    }
}