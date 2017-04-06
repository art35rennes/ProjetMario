#ifndef CLASS_H
#define CLASS_H

#include <QPainter>
#include <QtWidgets>
#include <QString>
#include <QKeyEvent>
#include <time.h>
#include <math.h>
//#include "plateforme.h"

class Entitie_Joueur{

    public:
        Entitie_Joueur();
        Entitie_Joueur(int x, int y = 0, int KeyJump = Qt::Key_Z, int KeyLeft = Qt::Key_Q, int KeyRight = Qt::Key_D,
                       int Vie = 10, int Vitesse = 2, int sizeX = 5, int sizeY = 12, QBrush couleur = Qt::darkMagenta);

        int GetVie();
        int GetX();
        int GetY();
        int GetSizeY();
        int GetSizeX();
        QBrush GetColor();
        void GetPos();
        float GetJumpLvl();
        float GetT();
        int GetcollisionFrom();
        int GetYLastJump();
        float GetTFall();
        int GetNbSaut();
        float GetVitesse();
        float GetTKnockBack();

        void SetKey(int KeyJump, int KeyLeft, int KeyRight);
        void SetVie(int NewVie);
        void SetPos(int x, int y);
        void SetSizeY(int y);
        void SetSizeX(int x);
        void SetColor(QBrush couleur);
        void SetJumpLvl(int val);
        void SetT(int val);
        void SetcollisionFrom(int val);
        void SetYLastJump(int y);
        void SetTFall(float val);
        void SetNbSaut(int val);
        void SetTKnockBack(float val);

        void Moove(int Sens);
        void Jump(int hauteur = 35);
        void KnockBack(int hauteur = 15);
        void Reset();

        QGraphicsRectItem *hitBox;
        QGraphicsTextItem *tNJoueur;

        bool BkeyLeft, BkeyRight, BkeyJump;
        bool BCanLeft, BCanRight, BCanJump, BCanFall, BCanKnockBack, BCanTakeDamage, BWin;
        int ValKeyLeft, ValKeyRight, ValKeyJump; //code ascii des touche de controle

    private:

        QBrush color;

        int collisionFrom; //0: none 1: up, 2: right, 3: down, 4: left
        int vie;
        float vitesse;

        int YLastJump, nbSaut;
        float jump, t, tFall, tKnockBack;

        int sizeX, sizeY;



};
#endif // CLASS_H
