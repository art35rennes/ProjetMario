#ifndef MYSCENE_H
#define MYSCENE_H

#include <QPainter>
#include <QtWidgets>
#include <QString>
#include <QKeyEvent>
#include <time.h>
#include <math.h>
#include "entitie_joueur.h"
#include <iostream>
#include <fstream>

#include <algorithm>

using namespace std;

class MyScene : public QGraphicsScene {
        Q_OBJECT
    public :

        MyScene(QObject *parent = 0);

        void CheckTerrain();
        void initTerrain();

        void AddElement(int x, int y, QString path);
        void AddPlateforme(int x, int y, int type, int sens = 1,
                            int marge = 0, float vitesse = 1);

        void AddGround(int x, int width, QBrush color = Qt::green);
        void AddMur(int x, int y, int type);
        void AddKnocker(int x, int y, int type, int sens = 1, int marge = 20, float vitesse = 1);
        void AddMobileElement(int marge, float vitesse, int sens, int x, int y, QString path);
        void AddFinish(int x, int y);
        void AddBackGround(int x, int y, QColor color = QColor(18,123,215));
        void AddBackGround(QString path);

        void GeneratePath();
        void LoadLevel();

        void NewJoueur(int up = Qt::Key_Z, int left = Qt::Key_Q, int right = Qt::Key_D);

    public slots:
        void update();

    protected:
        void keyPressEvent(QKeyEvent * event);
        void keyReleaseEvent(QKeyEvent * event);

    private:
        QTimer *timer;
        QString cSLevel;

        std::vector<Entitie_Joueur*> vJoueur;
        QGraphicsTextItem* Message;
        QGraphicsTextItem* Info;
        std::vector<QGraphicsTextItem*> vVie;

        std::vector<unsigned int> vNumElementGround;
        std::vector<unsigned int> vNumKnocker;
        std::vector<QGraphicsItem*> vTerrain;
        std::vector<std::vector<float>> vMTerrain;

        int compteur, knock, cLevel, numFinish;
        float vx, vy;
        bool BPause, BRestart, BMulti;
        unsigned int i,j,k,l;
};


#endif
