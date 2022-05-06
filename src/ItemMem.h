#ifndef _ITEM_MEM_
#define _ITEM_MEM_
#include <string>
#include <fstream>


enum item_type {ITEM_NONE = 0, ITEM_PLACABLE = 1, ITEM_PICKAXE = 2, ITEM_MELEE_ATTACK = 3};
enum {PICKAXE}; 

class ItemMem {
public:
    

    ItemMem();
    int getId () const;
    std::string getName();
   
    /**
     * @brief Initalise l'ItemMem avec les valeurs
     * contenue dans le fichier pointé par path
     * 
     * @param path Chemin vers le fichier de l'item
     * @return true Aucune erreur
     * @return false Erreur lors du chargement
     */
    bool load(std::string path);
    
//private:
    int dropped_block_id;
    int id;

    /**
     * @brief Indique si l'item est placable, utilisable etc.
     */
    char type;
    
    std::string name;
   
};

#endif