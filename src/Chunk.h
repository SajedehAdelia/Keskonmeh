#ifndef _CHUNK
#define _CHUNK
#include <vector>
#include <map>
#include "BlockMem.h"
#include "../inc/RPTypes.h"
#include "../inc/Box2D/box2d.h"

int const CHUNKDIMX = 10;
int const CHUNKDIMY = 10;

class Chunk{
private:
   BlockMem * blocks_tab[2][CHUNKDIMX*CHUNKDIMY];
   char tab_test[2][CHUNKDIMX*CHUNKDIMY];
   b2Body* pBody;
   int2 coord;

   
   /**
    * @brief Permet de garder une trace des fixtures
    * lors de la destruction d'un block, on doit être capable de donner
    * l'adresse d'une fixture pour la retirer
    */
   b2Fixture* fixtures_tab[CHUNKDIMX*CHUNKDIMY];

    

public:


  Chunk(std::string path, std::map<int, BlockMem> & blocks_list);

  Chunk(std::map<int, BlockMem> & blocks_list);

  Chunk();

  ~Chunk();

  void load(std::string path, std::map<int, BlockMem> & blocks_list);

  void exporter(std::string path);

  void testaffichage();

  void testgeneration();

  void generateplain(int height, bool side, std::map<int, BlockMem> &  blocks_list); //height:hauteur du sol au chunk d'avant. side: 1 si le chunk d'avant est à gauche du nouveau, 0 si à droite.

   /**
    * @brief Récupère un pointeur sur BlockMem aux coordonnées indiquées
    * 
    * @param coord Coordonnées dans le chunk. La coordonnée z correspond à la profondeur (0 ou 1)
    * @return BlockMem* Pointeur sur BlockMem
    */
   BlockMem * get_block(int3 coord) const;

   /**
   * @brief Place un bloc aux coordonnées indiquées
   * 
   * @param coord coordonnées à laquelle placer le bloc (z: profondeur 0 ou 1)
   * @param block pointeur sur BlockMem
   */
   void set_block(int3 coord, BlockMem * const block);

   /**
    * @brief Essaye de poser un bloc aux coordonnées indiquées
    * Si le bloc pointé possède l'attribut [remplacable] alors le bloc sera substitué
    * Sinon rien en change
    * 
    * @param coord coordonnées à laquelle placer le bloc (z: profondeur 0 ou 1)
    * @param block pointeur sur BlockMem
    * @return true Le bloc a pu être placé
    * @return false Le bloc n'a pas été placé
    */
   bool place_block(int3 coord, BlockMem * const block);

  /**
   * @brief Crée la boite de collision du chunk.
   * Un chunk possède un unique static_body [pBody] qu'on ratache au monde aux bonnes coordonnées
   * Pour chaque block solide dans le chunk, on créer une fixture qu'on attache au body
   * 
   * @param pWorld monde Box2D passé par référence
   */
   void generate_physical_body(b2World& pWorld, int2 chunk_coord);

};

#endif