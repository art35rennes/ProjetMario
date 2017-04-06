#include "jeu.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FenetreJeu w;
    w.setFixedSize(300, 200);//950, 480
    w.show();

    return a.exec();
}
