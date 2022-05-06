#include <iostream>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string>
#include "Chunk.h"


Chunk::Chunk()
{

}

Chunk::Chunk(std::map<int, BlockMem> & blocks_list)
{
    for(int i = 0; i < CHUNKDIMX * CHUNKDIMY; i++)
        fixtures_tab[i] = NULL;

    generateplain(CHUNKDIMY/3,true, blocks_list);
}

Chunk::Chunk(std::string path, std::map<int, BlockMem> & blocks_list)
{
    //==========================================
    //    A REFAIRE AVEC DU C++
    //==========================================
    /*
    int fdin;
    char array[path.size()+1];
    strcpy(array, path.c_str());
    if((fdin = open(array, O_RDONLY)) < 0) {
        std::cerr << "Erreur : " << strerror(errno) << std::endl;
    }   

    char buf;
    int i = 0;
    int j = 0;
    int nbread;
    do{

        nbread = read(fdin,&buf,1);
        int b = buf;
        blocks_tab[0][i] = &blocks_list[b];
        tab_test[0][i] = b;
        i++;

    }while(i<CHUNKDIMX*CHUNKDIMY);

    do{

        nbread = read(fdin,&buf,1);
        int b = buf;
        blocks_tab[1][j] = &blocks_list[b];
        tab_test[1][j] = b;
        j++;


    }while(nbread != 0);
    close(fdin);
    */
}

Chunk::~Chunk()
{
    for(int i = 0; i<CHUNKDIMX*CHUNKDIMY; i++)
    {
        //on ne delete pas les pointeurs 
        blocks_tab[0][i] = NULL;
        blocks_tab[1][i] = NULL;
    }

}

void Chunk::exporter(std::string path)
{
    int fdout;
    char array[path.size()+1];
    strcpy(array, path.c_str());
    if((fdout = open(array, O_WRONLY|O_CREAT|O_TRUNC, S_IRUSR|S_IWUSR)) == -1) {
        std::cerr << "Erreur : " << strerror(errno) << std::endl;
    }

    for(int i = 0; i<CHUNKDIMX*CHUNKDIMY; i++)
    {
        write(fdout,&tab_test[0][i],1);
    }

    for(int i = 0; i<CHUNKDIMX*CHUNKDIMY; i++)
    {
        write(fdout,&tab_test[1][i],1);
    }
}

void Chunk::testaffichage()
{
    std::cout<<"sens croissant"<<std::endl;

    for(int j=0;j<CHUNKDIMY;j++)
    {
        for(int i=0;i<CHUNKDIMX;i++)
        {
                std::cout<<tab_test[0][i+CHUNKDIMX*j];
        }
        std::cout<<std::endl;
    }

    std::cout<<"sens décroissant"<<std::endl;

    for(int j=CHUNKDIMY-1;j>=0;j--)
    {
        for(int i=CHUNKDIMX-1;i>=0;i--)
        {
                std::cout<<tab_test[0][i+CHUNKDIMX*j];
        }
        std::cout<<std::endl;
    }
}

void Chunk::testgeneration()
{
    for(int j = 0;j<CHUNKDIMY;j++)
    {
        for(int i = 0; i<5;i++)
        {
            tab_test[0][i+10*j] = 3;
        }

        for(int i = 5;i<CHUNKDIMX;i++)
        {
            tab_test[0][i+10*j] = 4;
        }
    }
    for(int j = 0;j<CHUNKDIMY;j++)
    {
        for(int i = 0; i<5;i++)
        {
            tab_test[1][i+10*j] = 5;
        }

        for(int i = 5;i<CHUNKDIMX;i++)
        {
            tab_test[1][i+10*j] = 6;
        }
    }
}

void Chunk::generateplain(int height, bool side, std::map<int, BlockMem> & blocks_list)
{
    for(int i = 0 ; i<height*CHUNKDIMX ; i++)
    {
        blocks_tab[0][i] = &blocks_list[STONE];
        tab_test[0][i] = 's';
    }

    for(int i = height*CHUNKDIMX;  i<(height+1)*CHUNKDIMX ; i++)
    {
        blocks_tab[0][i] = &blocks_list[GRASS];
        tab_test[0][i] = 'g';
    }

    for(int i = (height+1)*CHUNKDIMX ; i<CHUNKDIMY*CHUNKDIMX ; i++)
    {
        blocks_tab[0][i] = &blocks_list[AIR];
        tab_test[0][i] = 'a';
    }
}
/*
void Chunk::generateair(BlockMem * const blocks_list)
{
    for(int i = 0 ; i<CHUNKDIMX*CHUNKDIMY ; i++)
    {
        blocks_tab[0][i] = &blocks_list[0];
    }
}

void Chunk::generateground(BlockMem * const blocks_list)
{
    for(int i = 0 ; i<CHUNKDIMX*CHUNKDIMY ; i++)
    {
        blocks_tab[0][i] = &blocks_list[1];
    }
}
*/


void Chunk::generate_physical_body(b2World& pWorld, int2 chunk_coord) {
    coord = chunk_coord;
    
    b2BodyDef bodyDef;
    bodyDef.type = b2_staticBody;
    
    bodyDef.position.Set(chunk_coord.x, chunk_coord.y);
    pBody = pWorld.CreateBody(&bodyDef);

    b2PolygonShape box;
    for(int i = 0; i < CHUNKDIMX; i++) {
        for(int j = 0; j <CHUNKDIMY; j++) {
            //Si le block est solide on l'ajoute aux boites de collision
            if(blocks_tab[0][i + j * CHUNKDIMX]->solid == true) {
                //la taille des boites sera de 1.1 * 1.1, pour éviter de tomber entre les boites
                //le 3ème paramètre est le centre de la boite, on ajoute donc +0.5.
                //les coordonnées du monde sont inversée par rapport aux coordonnées des tableaux
                //   on doit donc ajouter le terme CHUNKDIMY pour retrouve une map correcte
                box.SetAsBox(0.5, 0.5, b2Vec2(i + 0.5, j + 0.5), 0.);
                //on crée une fixture et on stock son adresse dans fixture_tab
                fixtures_tab[i + j * CHUNKDIMX] = pBody->CreateFixture(&box, 0.);
            }

        }
    }
}


BlockMem* Chunk::get_block(int3 coord) const
{
    assert(coord.z == 0 || coord.z == 1);
    assert(coord.x >= 0 && coord.x < CHUNKDIMX);
    assert(coord.y >= 0 && coord.y < CHUNKDIMY);
    
    return blocks_tab[coord.z][coord.x + coord.y * CHUNKDIMX];
}

void Chunk::set_block(int3 coord, BlockMem * const block) {
    assert(coord.z == 0 || coord.z == 1);
    assert(coord.x >= 0 && coord.x < CHUNKDIMX);
    assert(coord.y >= 0 && coord.y < CHUNKDIMY);

  //Changer le bloc
    blocks_tab[coord.z][coord.x + coord.y * CHUNKDIMX] = block;

  //Gestion collision box
    //Si le bloc est au devant
    if(coord.z == 0) {
        //Si le bloc est solide
        if(block->solid) {
            //S'il n'existe pas déjà une collision box
            if(fixtures_tab[coord.x + coord.y * CHUNKDIMX] == NULL) {
                //Créer une collision box
                b2PolygonShape box;
                box.SetAsBox(0.5, 0.5, b2Vec2(coord.x + 0.5, coord.y + 0.5), 0.);
                fixtures_tab[coord.x + coord.y * CHUNKDIMX] = pBody->CreateFixture(&box, 0.);
            }
        }
        //Sinon, si le bloc n'est pas solide
        else {
            //Mais qu'il existe déjà une collision box
            if(fixtures_tab[coord.x + coord.y * CHUNKDIMX] != NULL) {
                //Retirer la collision box
                pBody->DestroyFixture(fixtures_tab[coord.x + coord.y * CHUNKDIMX]);
                fixtures_tab[coord.x + coord.y * CHUNKDIMX] = NULL;
            }
        }
    }
}

bool Chunk::place_block(int3 coord, BlockMem * const block) {
    assert(coord.z == 0 || coord.z == 1);
    assert(coord.x >= 0 && coord.x < CHUNKDIMX);
    assert(coord.y >= 0 && coord.y < CHUNKDIMY);
    
    //Si le bloc peut être remplacé
    if(blocks_tab[coord.z][coord.x + coord.y * CHUNKDIMX]->remplacable)
        set_block(coord, block);
    else
        return false;
    return true;
}
