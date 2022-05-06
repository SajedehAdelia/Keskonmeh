#ifndef _MAP
#define _MAP

#include "Chunk.h"
#include "../inc/Box2D/box2d.h"
#include "Player.h"
#include "ItemMem.h"

#include <map>
#include <vector>
#include <string>


#include <thread>
#include <chrono>

int const MAPDIMX = 7;
int const MAPDIMY = 7;

class Map{

public:

    //données membres////////////////////////////////
    
    Chunk* chunks_tab[MAPDIMX * MAPDIMY];
    b2World physicalWorld;

    //fonctions membres/////////////////////////////

    Map(std::string path, std::map<int, BlockMem> &  blocks_list, std::map<int, ItemMem> &  items_list); //constructeur avec save

    Map(std::map<int, BlockMem> & blocks_list, std::map<int, ItemMem> &  items_list);//constructeur sans save

    ~Map();


    /**
     * @brief Met à jour les entités et la map physique
     * 
     */
    void update_physics(float dt);

    /**
     * @brief Récupère le bloc aux coordonnées indiquées
     * La fonction s'assure que le bloc se trouve dans le bon chunk
     * 
     * @param coord Coordonnées dans l'espace du monde
     * @return BlockMem* 
     */
    BlockMem* get_block(int3 coord) const;

    /**
     * @brief Place un bloc aux coordonnées indiquées
     * La fonction s'assure que le bloc soit placé dans le bon chunk
     * 
     * @param coord Coordonnées dans l'espace du monde
     * @param block Bloc à placer
     */
    void set_block(int3 coord, BlockMem* block);
    
    /**
     * @brief Essaye de placer un bloc aux coordonnées indiquées
     * La fonction s'assure que le bloc soit placé dans le bon chunk
     * Si le bloc déjà présent n'a pas l'attribut [Remplacable] alors rien ne se passe
     * Sinon le bloc est modifié, les collisions box du chunk également.
     * 
     * @param coord Coordonnées dans l'espace du monde
     * @param block Bloc à placer
     * @return true Le bloc à pu être placé
     * @return false Le bloc n'a pas été placé
     */
    bool place_block(int3 coord, BlockMem* block);

    /**
     * @brief Récupère le chunk contenant les coordonnées indiquées
     * Les coordonnées seront modifiées en les coordonnées au sein du chunk
     * 
     * @param coord IN: Coordonnées dans l'espace du monde OUT: Coordonnées dans le chunk
     * @return Chunk* Pointeur sur chunk
     */
    Chunk* get_chunk(float2& coord) const;

    /**
     * @brief Renvoie les coordonnées du chunk auquel coord appartient.
     * coord est modifié pour devenir les coordonnées au sein du chunk
     * 
     * @param coord IN: Coordonnées dans l'espace du monde OUT: Coordonnées dans le chunk
     * @return int2 Coordonnées du chunk
     */
    int2 get_coord_chunk(float2& coord) const;

    /**
     * @brief Renvoie l'index du chunk dans chunks_tab
     * 
     * @param chunk_coord Les coordonnées du chunk
     * @return int Index du chunk
     */
    int get_index_chunk(const int2& chunk_coord) const;

    

    /**
     * @brief Mettra à jour les pointeurs sur chunk pour se déplacer dans la map.
     * Quand le joueur est à 2 chunks du bord virtuelle de la map, les pointeurs seront déplacés
     * de manière à ce qu'il se retrouve au centre de cette map virtuelle.
     * Pour cela des chunks devront être créés ou chargés depuis les fichiers du jeu
     * /!\ POUR L'INSTANT CETTE FONCTION NE FAIT QUE TOURNER LES CHUNKS DEJA EXSITANT ENTRE EUX /!\
     * 
     */
    void scroll_chunks(float2& player_pos);

    
private:
    int2 central_chunk_coord;

    /**
     * @brief Renvoie les coordonnées du coin supérieur gauche du chunk passé en paramètre
     * 
     * @param chunk_coord Coordonnée du chunk
     * @return int2 Coordonnée du bloc au coin supérieur gauche
     */
    int2 get_upper_left_coord(int2 chunk_coord) const;

    

    

    /// @brief Déplace les pointeurs de chunk vers la gauche (and wrap arround)
    void move_chunks_ptr_left();

    /// @brief Déplace les pointeurs de chunk vers la droite (and wrap arround)
    void move_chunks_ptr_right();

    /// @brief Déplace les pointeurs de chunk vers le haut (and wrap arround)
    void move_chunks_ptr_up();

    /// @brief Déplace les pointeurs de chunk vers le bas (and wrap arround)
    void move_chunks_ptr_down();
};

#endif