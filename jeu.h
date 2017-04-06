#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QtWidgets>

class FenetreJeu : public QMainWindow {
    Q_OBJECT
public:
    FenetreJeu();
    ~FenetreJeu();
    QGroupBox * BuildGroupBoxControle();

public slots:

private:
    QWidget * widget_general;
    QMenu * menuFichier;
    QGraphicsScene * myscene;
};
#endif

