#ifndef WINTXT_H
#define WINTXT_H

//! \brief une fen�tre texte est un tableau 2D de caract�res
class WinTXT
{
private:

    int dimx;       //!< \brief largeur
    int dimy;       //!< \brief heuteur
    char* win;      //!< \brief stocke le contenu de la fen�tre dans un tableau 1D mais on y accede en 2D
    char** col;
    char current_col[20];
    char* end_col;

public:

    WinTXT (int dx, int dy);
    ~WinTXT();
    void clear (char c=' ');
    void print (int x, int y, char c);
    void print (int x, int y, char* c);
    void print (int x, int y, const char* c);
    void draw (int x=0, int y=0);
    void pause();
    char getCh();

    void setCol(const char* code);

};

void termClear ();

#endif
