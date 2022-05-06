#include<iostream>
using namespace std;
#include <string>
#include <fstream>
#include <strstream>

#include "Keskonmeh.h"

int main()
{
    Keskonmeh appli;
    for(int i = 0 ; i<MAPDIMX; i++)
    {
        std::cout<<"affichage chunk"<<i<<std::endl;
        //appli.map->chunks_tab[0][i].testaffichage();
        
    }
        std::ifstream file("../data/test_block_mem"); //on ouvre le fichier path en mode lecture
        if(file.is_open())
        {
            return false;
        }

        while(!file.eof())
        {
            char line[20];
            file.getline(line,20);
            std::cout<<line[0]<<std::endl;

        }
            
    return 0; 
}