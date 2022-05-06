#include "SDLEngine.h"

#include <iostream>

using namespace std;

int main(void) {

    SDLEngine app(900, 400, false);


    while(app.is_running) {
        app.update();
        app.clear_screen();
        app.draw_screen();
    }
  
    return 0;
}

