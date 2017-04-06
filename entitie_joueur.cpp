#include "entitie_joueur.h"

Entitie_Joueur::Entitie_Joueur(int x, int y, int KeyJump, int KeyLeft,
                               int KeyRight, int Vie, int Vitesse, int sizeX, int sizeY, QBrush couleur){
    hitBox = new QGraphicsRectItem(x, y, sizeX, sizeY);
    hitBox->setBrush(QBrush(couleur));
    hitBox->setBrush(QColor(31, 205, 11));
    hitBox->setZValue(1);

    tNJoueur = new QGraphicsTextItem("JX");
    tNJoueur->setPos(hitBox->x()+3, hitBox->y()-4);
    tNJoueur->setZValue(1);

    vie = Vie;
    vitesse = Vitesse;
    ValKeyJump = KeyJump;
    ValKeyLeft = KeyLeft;
    ValKeyRight = KeyRight;
    jump = 0;
    t = 0.0;
    tFall = 0.0;
    tKnockBack = 0.0;
    YLastJump = 0;
    nbSaut = 0;
}

//*******Divers**********
void Entitie_Joueur::Moove(int Sens){
    hitBox->setX(Sens*vitesse + hitBox->x());
}
void Entitie_Joueur::Jump(int hauteur){
    if(t == 0 && jump == 0)
        YLastJump = hitBox->y();

     t += 0.1;
     jump  = hauteur*sin(0.75*t);
     hitBox->setY(YLastJump-jump);
     if(t >= ((float)4/3)*3.14){
         jump = 0.0;
         t = 0.00;
         hitBox->setY(YLastJump);
         nbSaut++;
     }
     //qDebug() << YLastJump-jump << YLastJump <<jump;
}
void Entitie_Joueur::KnockBack(int hauteur){
    if(t == 0 && jump == 0)
        YLastJump = hitBox->y();

     tKnockBack += 0.05;
     jump  = hauteur*sin(4*tKnockBack);
     hitBox->setY(YLastJump-jump);
     if(tKnockBack >= 3.14/4){
         jump = 0.0;
         tKnockBack = 0.00;
         hitBox->setY(YLastJump);
         t = 0;
     }
     //qDebug() << YLastJump-jump << YLastJump <<jump;
}
void Entitie_Joueur::Reset(){
    hitBox->setPos(60, 368);
    vie = 10;
    jump = 0;
    t = 0.0;
    tFall = 0.0;
    tKnockBack = 0.0;
    YLastJump = 0;
    nbSaut = 0;
    hitBox->setBrush(QColor(31, 205, 11));
}
int Entitie_Joueur::GetcollisionFrom(){
    return collisionFrom;
}
void Entitie_Joueur::SetcollisionFrom(int val){
    collisionFrom = val;
}

//******Get*********
int Entitie_Joueur::GetVie(){
    return vie;
}
int Entitie_Joueur::GetX(){
    return hitBox->x();
}
int Entitie_Joueur::GetY(){
    return hitBox->y();
}
void Entitie_Joueur::GetPos(){
    qDebug() << "X: " << hitBox->x() << " Y: " << hitBox->y();
}
int Entitie_Joueur::GetSizeY(){
    return sizeY;
}
int Entitie_Joueur::GetSizeX(){
    return sizeX;
}
float Entitie_Joueur::GetJumpLvl(){
    return jump;
}
float Entitie_Joueur::GetT(){
    return t;
}
QBrush Entitie_Joueur::GetColor(){
    return color;
}
int Entitie_Joueur::GetYLastJump(){
    return YLastJump;
}
float Entitie_Joueur::GetTFall(){
    return tFall;
}
int Entitie_Joueur::GetNbSaut(){
    return nbSaut;
}
float Entitie_Joueur::GetVitesse(){
    return vitesse;
}
float Entitie_Joueur::GetTKnockBack(){
    return tKnockBack;
}

//******Set**********
void Entitie_Joueur::SetSizeY(int y){
    sizeY = y;
}
void Entitie_Joueur::SetSizeX(int x){
    sizeX = x;
}
void Entitie_Joueur::SetColor(QBrush couleur){
    hitBox->setBrush(QBrush(couleur));
}
void Entitie_Joueur::SetKey(int KeyJump, int KeyLeft, int KeyRight){
    ValKeyJump = KeyJump;
    ValKeyLeft = KeyLeft;
    ValKeyRight = KeyRight;
}
void Entitie_Joueur::SetVie(int NewVie){
    vie = NewVie;
}
void Entitie_Joueur::SetPos(int x, int y){
    hitBox->setX(x);
    hitBox->setY(y);
}
void Entitie_Joueur::SetJumpLvl(int val){
    jump = val;
    t = 0;
}
void Entitie_Joueur::SetT(int val){
    t = val;
}
void Entitie_Joueur::SetYLastJump(int y){
    YLastJump = y;
}
void Entitie_Joueur::SetTFall(float val){
    tFall = val;
}
void Entitie_Joueur::SetNbSaut(int val){
    nbSaut = val;
}
void Entitie_Joueur::SetTKnockBack(float val){
    tKnockBack = val;
}
