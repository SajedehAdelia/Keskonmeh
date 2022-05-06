#include "../src/Inventory.h"

#include <iostream>

using namespace std;

int main(void) {
    int i;
    int failed_test = 0;

    cout << "Test du module [Inventory]" << endl;
    cout << endl;

    Inventory inv(5);
    cout << "Constructeur d'inventaire de taille 5" << endl;
    cout << endl;

//Get size
    cout << "On récupère la taille de l'inventaire" << endl;
    cout << "---" << endl;
    int inv_size = inv.get_size();
    if(inv_size != 5)
        cout << "  ! La taille lu est de " << inv_size << " au lieu de 5." << endl;
    else
        cout << "  La taille lu est de 5." << endl;
    cout << endl;

//Get slot vide
    cout << "On lit tous les slots, qui devraient être vide" << endl;
    cout << "---" << endl;
    int item_count;
    ItemMem* item_read;
    
    for(i = 0; i<5; i++) {
        item_read = inv.get_slot(0, item_count);
        if(item_read != NULL)
            failed_test++;
    }
    if(failed_test > 0)
        cout << " ! ";
    cout << failed_test << " slot(s) contenai(en)t un item";
    if(failed_test > 0)
        cout << " alors que l'inventaire doit être initalisé vide";
    cout << endl;
    cout << endl;

//set item
    cout << "On insère respectivement 1, 15 item dans le slot 0 et 4" << endl;
    cout << "---" << endl;
    
    ItemMem item;
    
    item.load("data/item/stone.kkm");
    cout << "  Un item de Stone a été chargé" << endl;

    inv.set_item(&item, 0, 1);
    item_read = inv.get_slot(0, item_count);
    cout << item_count << " " << item_read->getName()  << " ajoutée à l'index 0" << endl;
    inv.set_item(&item, 4, 15);
    item_read = inv.get_slot(4, item_count);
    cout << item_count  << " " << item_read->getName() << " ajoutée à l'index 4" << endl;
    
//fill in
    cout << "On essaye d'insérer 4 nouveaux item dans l'inventaire" << endl;
    ItemMem* item_tab[4];
    for(int i = 0; i < 4; i ++) {
        item_tab[i] = new ItemMem;
        item_tab[i]->id = 10 + i;
        item_tab[i]->name = 
        inv.fill_in(item_tab[i], 1);
    }

    for(int i = 0; i < 4; i ++) {
        delete item_tab[i];
    }
    delete [] item_tab;

/*
    - inv.get_slot(int index, int& count_out) const;
    x inv.set_item(ItemMem * const item, int index, int quantity);
    inv.fill_in(ItemMem *const item, int quantity);
    inv.empty_slot(unsigned int index);
    inv.remove_item(int index, int quantity);
    inv.get_first_empty_slot();
    x inv.get_size();
*/
    return 0;
}