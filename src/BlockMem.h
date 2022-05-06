#ifndef _BLOCK_MEM
#define _BLOCK_MEM
#include <string>
#include <fstream>

//Doit correspondre aux ID présent dans les .kkm
enum {AIR = 0, STONE = 1, GRASS = 2, DIRT = 3};

class BlockMem{

public:
    // SDL_Texture* texture;
    std::string name;
    int item_id, id;
    float mining_time;
    
    /// @brief Indique si le block peut être traversé par des objets physiques
    bool solid;
    /// @brief Indique si le block peut être miné
    bool minable;
    /// @brief Indique si le block peut être remplacé lorsqu'on pose un bloc
    bool remplacable;

    BlockMem();

    /**
     * @brief Initalise le BlockMem avec les valeurs
     * contenue dans le fichier pointé par path
     * 
     * @param path Chemin vers le fichier du block
     * @return true Aucune erreur
     * @return false Erreur lors du chargement
     */
    bool load(std::string path); //0 si échec, 1 si succès

};
#endif