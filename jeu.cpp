#include "jeu.h"
#include "myscene.h"



FenetreJeu::FenetreJeu() : QMainWindow() {

    // le widget dans lequel tout s'affiche
    widget_general = new QWidget;
    QHBoxLayout * qbl_general = new QHBoxLayout;
    widget_general->setLayout(qbl_general);
    this->setCentralWidget(widget_general);

    QGraphicsView * myview;
    myscene = new MyScene(this);

    myview = new QGraphicsView(myscene, this);
    myview->setBackgroundBrush(Qt::red);
    myview->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    myview->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    qbl_general->addWidget(myview);

}
FenetreJeu::~FenetreJeu() {
}
