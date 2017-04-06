#include "myscene.h"
using namespace std;

void MyScene::keyPressEvent(QKeyEvent * event){
    //qDebug() << "Touche pres" << event->key();
    for(i = 0; i < vJoueur.size(); i++){
        if(event->key() == vJoueur.at(i)->ValKeyJump){
            vJoueur.at(i)->BkeyJump = true;
        }
        else{
            if(event->key() == vJoueur.at(i)->ValKeyLeft){
                vJoueur.at(i)->BkeyLeft = true;
                vJoueur.at(i)->BCanRight = true;
            }
            else{
                if(event->key() == vJoueur.at(i)->ValKeyRight){
                    vJoueur.at(i)->BkeyRight = true;
                    vJoueur.at(i)->BCanLeft = true;
                }
                else{
                    switch(event->key()){
                        case Qt::Key_R:
                            BRestart = true;
                            break;
                        case Qt::Key_P:
                            if(!BPause && vJoueur.at(i)->GetVie() > 0){
                                BPause = true;
                                Message->setVisible(true);
                                timer->stop();
                            }
                            else{
                                BPause = false;
                                Message->setVisible(false);
                                timer->start();
                            }
                            break;
                    }
                }
            }
        }
    }
    if(event->key() == Qt::Key_F2){
        if(BMulti){
            BMulti = false;
            vJoueur.at(1)->hitBox->setVisible(false);
            vJoueur.at(1)->tNJoueur->setVisible(false);
            vVie.at(1)->setVisible(false);

        }
        else{
            BMulti = true;
             vJoueur.at(1)->hitBox->setVisible(true);
             vJoueur.at(1)->tNJoueur->setVisible(true);
             vVie.at(1)->setVisible(true);
             vJoueur.at(1)->hitBox->setPos(vJoueur.at(0)->hitBox->x(), vJoueur.at(0)->hitBox->y());
        }
    }
}
void MyScene::keyReleaseEvent(QKeyEvent * event){
    //qDebug() << "Touche release" << event->key();
    for(i = 0; i < vJoueur.size(); i++){
        if(event->key() == vJoueur.at(i)->ValKeyJump){
            vJoueur.at(i)->BkeyJump = false;
        }
        else{
            if(event->key() == vJoueur.at(i)->ValKeyLeft){
                vJoueur.at(i)->BkeyLeft = false;
            }
            else{
                if(event->key() == vJoueur.at(i)->ValKeyRight){
                    vJoueur.at(i)->BkeyRight = false;
                }
            }
        }
    }
}

void MyScene::initTerrain(){

    LoadLevel();

    NewJoueur();

    NewJoueur(Qt::Key_Up, Qt::Key_Left, Qt::Key_Right);
    vJoueur.at(1)->hitBox->setVisible(false);
    vJoueur.at(1)->tNJoueur->setVisible(false);
    vVie.at(1)->setVisible(false);

    Info = new QGraphicsTextItem("Level: 0");
    Info->setZValue(1);
    this->addItem(Info);

    Message = new QGraphicsTextItem("PAUSE\npressez P pour reprendre...");
    Message->setScale(1.4);
    Message->setZValue(1);
    this->addItem(Message);
    Message->setVisible(false);

    BRestart = false;
    BPause = false;
    BMulti = false;

    compteur = 0;
    knock = 0;

}
void MyScene::AddFinish(int x, int y){
    //AddElement(x, y, 4, 8, Qt::black);
    QGraphicsRectItem * element = new QGraphicsRectItem(0, 0, 4, 8);
    element->setPos(x, y);
    element->setBrush(Qt::black);
    this->addItem(element);
    vTerrain.push_back(element);
    numFinish = vTerrain.size()-1;
}
void MyScene::AddGround(int x, int width, QBrush color){
    //AddElement(x, 380, width, 40, color, true);
    QGraphicsRectItem * element = new QGraphicsRectItem(0, 0, width, 40);
    element->setPos(x, 380);
    element->setBrush(color);
    this->addItem(element);
    vTerrain.push_back(element);
    vNumElementGround.push_back(vTerrain.size()-1);
}
void MyScene::AddElement( int x, int y, QString path){
    QGraphicsPixmapItem * element = new QGraphicsPixmapItem(QPixmap(path));
    element->setPos(x, y);
    element->setScale((float)1/6);
    this->addItem(element);
    vTerrain.push_back(element);
}
void MyScene::AddMobileElement(int marge, float vitesse, int sens, int x, int y, QString path){
    std::vector<float> tmp;
    tmp.clear();
    AddElement(x, y, path);
    tmp.push_back(vTerrain.size()-1);
    tmp.push_back(marge);
    tmp.push_back(0);
    tmp.push_back(sens);
    tmp.push_back(vitesse);
    tmp.push_back(0);//already moove
    vMTerrain.push_back(tmp);
}
void MyScene::AddPlateforme( int x, int y, int type, int sens, int marge, float vitesse){
    switch(type){
        //plateforme fixe
        case 1://plateforme de base, 80x6px, darkGray
            AddElement(x, y, ":/images/p80-6");
            break;
        case 2://plateforme de base, 40x6px, darkGray
            AddElement(x, y, ":/images/p40-6");
            break;
        case 3://plateforme de base, 20x6px, darkGray
            AddElement(x, y, ":/images/p20-6");
            break;
        case 4://bloc de base, 8x8px, Gray
            AddElement(x, y, ":/images/p8-8");
            break;
        //plateforme a deplacement horizontale
        case 11://plateforme en mouvement horizontale, 80x6px, yellow
            AddMobileElement(marge, vitesse, sens, x, y, ":/images/p80-6");
            break;
        case 12://plateforme en mouvement horizontale, 40x6px, yellow
            AddMobileElement(marge, vitesse, sens, x, y, ":/images/p40-6");
            break;
        case 13://plateforme en mouvement horizontale, 20x6px, yellow
            AddMobileElement(marge, vitesse, sens, x, y, ":/images/p20-6");
            break;
        //plateforme a deplacement verticale
        case 21://plateforme en mouvement verticale, 80x6px, white
            AddMobileElement(marge, vitesse, sens, x, y, ":/images/p80-6");
            break;
        case 22://plateforme en mouvement verticale, 40x6px, white
            AddMobileElement(marge, vitesse, sens, x, y, ":/images/p40-6");
            break;
        case 23://plateforme en mouvement verticale, 20x6px, white
            AddMobileElement(marge, vitesse, sens, x, y, ":/images/p20-6");
            break;
    }
    //qDebug() <<"ajout element";
}
void MyScene::AddMur( int x, int y, int type){
    switch(type){
        case 1://mur de base, 6x50px, darkGray
            AddElement(x, y, ":/images/m6-50");
            break;
        case 2://mur de base, 12x50px, darkGray
            AddElement(x, y, ":/images/m12-50");
            break;
        case 3://mur de base, 12x25px, darkGray
            AddElement(x, y, ":/images/m12-25");
            break;
        case 4://mur de base, 6x25px, darkGray
            AddElement(x, y, ":/images/m6-25");
            break;
    }
}
void MyScene::AddKnocker(int x, int y, int type, int sens, int marge, float vitesse){
    switch(type){
        //plateforme fixe
        case 1://plateforme de base, 8x8px, darkRed
            AddElement(x, y, ":/images/k8-16");
            vNumKnocker.push_back(vTerrain.size()-1);
            break;
        case 2://plateforme de base, 16x16px, darkRed
            AddElement(x, y, ":/images/k8-16");
            vNumKnocker.push_back(vTerrain.size()-1);
            break;
        case 3://plateforme de base, 20x6px, darkRed
            AddElement(x, y, ":/images/k20-6");
            vNumKnocker.push_back(vTerrain.size()-1);
            break;
        case 4://bloc de base, 40x6px, darkRed
            AddElement(x, y, ":/images/k40-6");
            vNumKnocker.push_back(vTerrain.size()-1);
            break;
        //plateforme a deplacement horizontale
        case 11://plateforme en mouvement horizontale, 8x8px, darkRed
            AddMobileElement(marge, vitesse, sens, x, y, ":/images/k8-16");
            vNumKnocker.push_back(vTerrain.size()-1);
            break;
        case 12://plateforme en mouvement horizontale, 40x6px, darkRed
            AddMobileElement(marge, vitesse, sens, x, y, ":/images/k40-6");
            vNumKnocker.push_back(vTerrain.size()-1);
            break;
        case 13://plateforme en mouvement horizontale, 20x6px, darkRed
            AddMobileElement(marge, vitesse, sens, x, y, ":/images/k20-6");
            vNumKnocker.push_back(vTerrain.size()-1);
            break;
        //plateforme a deplacement verticale
        case 21://plateforme en mouvement horizontale, 8x8px, darkRed
            AddMobileElement(marge, vitesse, sens, x, y, ":/images/k8-16");
            vNumKnocker.push_back(vTerrain.size()-1);
            break;
    }
}
void MyScene::AddBackGround(int x, int y, QColor color){
    QGraphicsRectItem * view;
    view = new QGraphicsRectItem(0, 0, x, y);
    view->setBrush(color);
    this->addItem(view);
}
void MyScene::AddBackGround(QString path){
    QGraphicsPixmapItem * view;
    view = new QGraphicsPixmapItem(QPixmap(path));
    this->addItem(view);
}
void MyScene::GeneratePath(){
    QStringList tmpList = cSLevel.split('/');
    QString tmp = tmpList.at(tmpList.size()-1);
    tmp.replace(QString::number(cLevel-1), QString::number(cLevel));
    qDebug() << tmpList.size();
    //tmpList.at(tmpList.size()-1) = tmp;
    cSLevel = tmpList.join('/');

}

void MyScene::NewJoueur(int up, int left, int right){
    vJoueur.push_back(new Entitie_Joueur(0, 0, up, left, right));
    this->addItem(vJoueur.at(vJoueur.size()-1)->hitBox);
    vJoueur.at(vJoueur.size()-1)->SetPos(60, 368);

    vVie.push_back(new QGraphicsTextItem("Vie JX: 10"));
    vVie.at(vVie.size()-1)->setPlainText(QString("Vie J"+QString::number(vVie.size())+": 10"));
    vVie.at(vVie.size()-1)->setZValue(1);
    this->addItem(vVie.at(vVie.size()-1));

    vJoueur.at(vJoueur.size()-1)->tNJoueur->setPlainText("J"+QString::number(vVie.size()));
    this->addItem(vJoueur.at(vJoueur.size()-1)->tNJoueur);
    vJoueur.at(vJoueur.size()-1)->tNJoueur->setScale(0.8);

    vJoueur.at(vJoueur.size()-1)->BkeyJump = false;
    vJoueur.at(vJoueur.size()-1)->BkeyLeft = false;
    vJoueur.at(vJoueur.size()-1)->BkeyRight =false;

    vJoueur.at(vJoueur.size()-1)->BCanLeft = true;
    vJoueur.at(vJoueur.size()-1)->BCanRight = true;
    vJoueur.at(vJoueur.size()-1)->BCanJump = true;
    vJoueur.at(vJoueur.size()-1)->BCanFall = false;
    vJoueur.at(vJoueur.size()-1)->BCanKnockBack = false;
    vJoueur.at(vJoueur.size()-1)->BCanTakeDamage = true;
}

void MyScene::CheckTerrain(){

    for(l = 0; l < vJoueur.size(); l++){
        vJoueur.at(l)->BCanJump = true;
        vJoueur.at(l)->BCanFall = true;
        vJoueur.at(l)->BCanKnockBack = false;
        vJoueur.at(l)->BWin = false;

        int numElementGround;
        //verification mouvement element
        for(i = 0; i < vMTerrain.size(); i++){

            if(vMTerrain.at(i)[2] < vMTerrain.at(i)[1]){
                int sens;
                if((int)vMTerrain.at(i)[3] == 1 || (int)vMTerrain.at(i)[3] == 2)
                    sens = 1;
                else
                    sens = -1;

                if(vMTerrain.at(i)[3] == 1 || vMTerrain.at(i)[3] == -1){
                    if(!vMTerrain.at(i)[5]){
                        vTerrain.at(vMTerrain.at(i)[0])->setX(vTerrain.at(vMTerrain.at(i)[0])->x() + sens * vMTerrain.at(i)[4]);
                        vMTerrain.at(i)[5] = 1;
                        vMTerrain.at(i)[2]++;
                    }
                    else
                        vMTerrain.at(i)[5] = 0;
                }
                else{
                    if(!vMTerrain.at(i)[5]){
                        vTerrain.at(vMTerrain.at(i)[0])->setY(vTerrain.at(vMTerrain.at(i)[0])->y() + sens * vMTerrain.at(i)[4]);
                        vMTerrain.at(i)[5] = 1;
                        vMTerrain.at(i)[2]++;
                    }
                    else
                        vMTerrain.at(i)[5] = 1;
                }

                if(vTerrain.at(vMTerrain.at(i)[0])->collidesWithItem(vJoueur.at(l)->hitBox)){
                    if(vMTerrain.at(i)[3] == 1 || vMTerrain.at(i)[3] == -1)
                        vJoueur.at(l)->hitBox->setX(vJoueur.at(l)->hitBox->x() + sens * vMTerrain.at(i)[4]);
                    else
                        vJoueur.at(l)->hitBox->setY(vJoueur.at(l)->hitBox->y() + sens * vMTerrain.at(i)[4]);

                    for(k = 0; k < vNumKnocker.size(); k++){
                        if(vNumKnocker.at(k) == vMTerrain.at(i)[0]){
                            vJoueur.at(l)->BCanKnockBack = true;
                        }
                    }
                }
            }
            else{
                vMTerrain.at(i)[2] = 0;
                vMTerrain.at(i)[3] = vMTerrain.at(i)[3] * -1;
            }
        }
        //Verification collision

        for(j = 0; j < vNumElementGround.size(); j++){
            numElementGround = vNumElementGround.at(j);
            for(i = 0; i < vTerrain.size(); i++){
                if(vTerrain.at(i)->collidesWithItem(vJoueur.at(l)->hitBox) && (int)i != numElementGround){
                    //qDebug() << "collision" << compteur << vTerrain.at(i);
                    if(vJoueur.at(l)->BkeyLeft){
                        vJoueur.at(l)->BCanLeft =false;
                    }
                    if(vJoueur.at(l)->BkeyRight){
                        vJoueur.at(l)->BCanRight = false;
                    }
                    if(vJoueur.at(l)->GetJumpLvl() != 0){
                        if(sin(vJoueur.at(l)->GetT()) > sin(vJoueur.at(l)->GetT()-0.1)){
                            //si on ne veut pas pouvoir traverser les objet depuis le dessous c'est ici que cela ce passe
                        }
                        else{
                            vJoueur.at(l)->SetJumpLvl(0);
                        }
                    }

                    if(vTerrain.at(i)->x() > vJoueur.at(l)->hitBox->x())
                        vJoueur.at(l)->BCanLeft = true;
                    else
                        vJoueur.at(l)->BCanRight = true;

                    if(vTerrain.at(i)->y() - vJoueur.at(l)->hitBox->y() >= 9.9 && vTerrain.at(i)->y() - vJoueur.at(l)->hitBox->y() <= 13){
                        vJoueur.at(l)->BCanRight = true;
                        vJoueur.at(l)->BCanLeft = true;
                        vJoueur.at(l)->SetNbSaut(0);
                    }
                    vJoueur.at(l)->BCanFall = false;
                    if(vTerrain.at(i)->y() - vJoueur.at(l)->hitBox->y() < 9.9){
                        vJoueur.at(l)->BCanFall = true;
                        vJoueur.at(l)->BCanJump = false;
                    }

                    for(k = 0; k < vNumKnocker.size(); k++){
                        if(vNumKnocker.at(k) == i){
                            vJoueur.at(l)->BCanKnockBack = true;
                        }
                    }
                    //qDebug() << "collision" << compteur << "Distance: " << vTerrain.at(i)->y() - Joueur->hitBox->y();
                    compteur++;
                }
            }
        }
        for(j = 0; j < vNumElementGround.size(); j++){//verification collision avec element de type ground uniquement
            //qDebug() << "collision" << compteur << "Distance: " << vTerrain.at(j)->y() - Joueur->hitBox->y();
            numElementGround = vNumElementGround.at(j);
            if(vTerrain.at(numElementGround)->collidesWithItem(vJoueur.at(l)->hitBox)){
                //qDebug() << "collision sol";
                vJoueur.at(l)->SetNbSaut(0);
                vJoueur.at(l)->BCanFall = false;
                vJoueur.at(l)->BCanJump = true;
                vJoueur.at(l)->SetTFall(0);
            }
            if(vTerrain.at(numElementGround)->y() - vJoueur.at(l)->hitBox->y() < 10.0){
                vJoueur.at(l)->BCanFall = true;
                vJoueur.at(l)->BCanJump = false;
            }
        }
        if(vTerrain.at(numFinish)->collidesWithItem(vJoueur.at(l)->hitBox)){
            vJoueur.at(l)->BWin = true;
        }
        if(vJoueur.at(l)->hitBox->y() > 408)
            vJoueur.at(l)->SetVie(0);
     }
}

void MyScene::update(){
    CheckTerrain();

    QList < QGraphicsView* > ListeView = this->views();

    if(BMulti){
        vx = abs(vJoueur.at(0)->hitBox->x()-vJoueur.at(1)->hitBox->x());
        vy = abs(vJoueur.at(0)->hitBox->y()-vJoueur.at(1)->hitBox->y());
        ListeView.at(0)->centerOn(min(vJoueur.at(0)->hitBox->x(), vJoueur.at(1)->hitBox->x())+vx,
                                  min(vJoueur.at(0)->hitBox->y(), vJoueur.at(1)->hitBox->y())+vy);
    }
    else{
        ListeView.at(0)->centerOn(vJoueur.at(0)->hitBox);
    }
    Message->setPos(ListeView.at(0)->mapToScene(30,40));
    Info->setPos(ListeView.at(0)->mapToScene(5,2));

    for(i = 0; i < vJoueur.size(); i++){
        vVie.at(i)->setPos(ListeView.at(0)->mapToScene((i+1)*80,2));
        vJoueur.at(i)->tNJoueur->setPos(vJoueur.at(i)->hitBox->x()-3, vJoueur.at(i)->hitBox->y()-15);
        //qDebug() << i <<vJoueur.at(i)->tNJoueur;
        if(((vJoueur.at(i)->BkeyJump && vJoueur.at(i)->BCanJump) || vJoueur.at(i)->GetT() != 0)
                && vJoueur.at(i)->GetNbSaut() < 1 && !vJoueur.at(i)->BCanKnockBack){//jump
            vJoueur.at(i)->Jump();
            vJoueur.at(i)->BCanFall = false;
        }
        if(vJoueur.at(i)->BCanKnockBack || vJoueur.at(i)->GetTKnockBack() != 0){//knock
            //qDebug() << "on knock back";
            vJoueur.at(i)->KnockBack();
            vJoueur.at(i)->BCanFall=false;
            if(vJoueur.at(i)->BCanTakeDamage){
                //Joueur->SetColor(Qt::magenta);
                vJoueur.at(i)->BCanTakeDamage = false;
                vJoueur.at(i)->SetVie(vJoueur.at(i)->GetVie()-1);
                vJoueur.at(i)->hitBox->setBrush(Qt::magenta);
            }
        }
        if(vJoueur.at(i)->GetTKnockBack() > 3.14/8){
            switch(vJoueur.at(i)->GetVie()){
            case 1:
                vJoueur.at(i)->hitBox->setBrush(QColor(207, 13, 13));
                break;
            case 2:
                vJoueur.at(i)->hitBox->setBrush(QColor(205, 69, 11));
                break;
            case 3:
                vJoueur.at(i)->hitBox->setBrush(QColor(203, 125, 16));
                break;
            case 4:
                vJoueur.at(i)->hitBox->setBrush(QColor(205, 177, 15));
                break;
            case 5:
                vJoueur.at(i)->hitBox->setBrush(QColor(192, 205, 11));
                break;
            case 6:
                vJoueur.at(i)->hitBox->setBrush(QColor(149, 205, 12));
                break;
            case 7:
                vJoueur.at(i)->hitBox->setBrush(QColor(92, 204, 14));
                break;
            case 8:
                vJoueur.at(i)->hitBox->setBrush(QColor(31, 205, 11));
                break;
            case 9:
                vJoueur.at(i)->hitBox->setBrush(QColor(31, 205, 11));
                break;
            case 10:
                vJoueur.at(i)->hitBox->setBrush(QColor(31, 205, 11));
                break;
            }
            vVie.at(i)->setPlainText(QString("Vie J"+QString::number(i+1)+": "+QString::number(vJoueur.at(i)->GetVie())));

        }
        if((!vJoueur.at(i)->BCanKnockBack && vJoueur.at(i)->GetTKnockBack() == 0) || vJoueur.at(i)->GetTKnockBack() == 0)
            vJoueur.at(i)->BCanTakeDamage = true;

        //deplacement personnage
        if(vJoueur.at(i)->BkeyLeft && vJoueur.at(i)->BCanLeft && vJoueur.at(i)->hitBox->x()-vJoueur.at(i)->GetVitesse() >= 0){//deplacement gauche
            vJoueur.at(i)->Moove(-1);
        }else{/*qDebug() << "Left BCan: " << BCanLeft << "Bkey: " << BkeyLeft;*/}

        if(vJoueur.at(i)->BkeyRight && vJoueur.at(i)->BCanRight && vJoueur.at(i)->hitBox->x()+vJoueur.at(i)->GetVitesse() <= 920){//deplacement droite
            vJoueur.at(i)->Moove(1);
        }else{/*qDebug() << "Right BCan: " << BCanRight << "Bkey: " << BkeyRight;*/}

        //chute
        if(vJoueur.at(i)->BCanFall){
            vJoueur.at(i)->BCanRight = true;
            vJoueur.at(i)->BCanLeft = true;
            /*Joueur->hitBox->setY(Joueur->hitBox->y() - (-25.7*Joueur->GetTFall()+107.9));
            Joueur->SetTFall(Joueur->GetTFall()+0.1);*/
            if(vJoueur.at(i)->GetJumpLvl() == 0 && vJoueur.at(i)->GetT() == 0){
                int tmp = true;
                for(float k = 0.0; k <= 2.5 && tmp; k+=0.1){
                    vJoueur.at(i)->hitBox->setY(vJoueur.at(i)->hitBox->y()+0.1);
                }
            }
            //Joueur->hitBox->setY(Joueur->hitBox->y()+10);
        }

        if(vJoueur.at(i)->GetVie() == 0){
            qDebug()<<"game over";
            vVie.at(i)->setPlainText(QString("Vie J"+QString::number(i+1)+": 10"));
            BRestart = true;
        }

        if(vJoueur.at(i)->BWin){
            qDebug() << "You WIN !";
            cLevel++;
            vVie.at(i)->setPlainText(QString("Vie J"+QString::number(i+1)+": 10"));
            Info->setPlainText(QString("Level: ")+QString::number(cLevel));
            vJoueur.at(i)->hitBox->setPos(60, 368);
            GeneratePath();
            LoadLevel();

        }
     }
    if(BRestart){
        Message->setVisible(false);
        for(i = 0; i < vJoueur.size(); i++){
            vJoueur.at(i)->Reset();
            vJoueur.at(i)->BkeyJump = false;
            vJoueur.at(i)->BkeyLeft = false;
            vJoueur.at(i)->BkeyRight =false;

            vJoueur.at(i)->BCanLeft = true;
            vJoueur.at(i)->BCanRight = true;
            vJoueur.at(i)->BCanJump = true;
            vJoueur.at(i)->BCanFall = false;

            BRestart = false;

            compteur = 0;

        }
    }
}
void MyScene::LoadLevel(){
    if(vTerrain.size() != 0){
        qDebug() << "suppression old map";
        for(i = 0; i < vTerrain.size(); i++){
            delete vTerrain.at(i);
        }
        vTerrain.clear();
        vMTerrain.clear();
        vNumKnocker.clear();
        vNumElementGround.clear();
    }

    string path = "../ProjetM/ressources/map/level_" + (QString::number(cLevel)).toStdString() + ".txt";

    ifstream fichierMap(path, ios::in);

    QStringList LigneExplode;
    QString Qligne;
    //qDebug() << "level" << path;

    if(fichierMap){
        string fLigne;
        while(getline(fichierMap, fLigne)){

            Qligne = QString::fromStdString(fLigne);
            LigneExplode = Qligne.split(",");

            if(LigneExplode.at(0) == "P"){
                switch (LigneExplode.size()-1) {
                case 3:
                    AddPlateforme(LigneExplode.at(1).toInt(), LigneExplode.at(2).toInt(), LigneExplode.at(3).toInt());
                    break;
                case 5:
                    AddPlateforme(LigneExplode.at(1).toInt(), LigneExplode.at(2).toInt(), LigneExplode.at(3).toInt(),
                                  LigneExplode.at(4).toInt(), LigneExplode.at(5).toInt());
                    break;
                case 6:
                    AddPlateforme(LigneExplode.at(1).toInt(), LigneExplode.at(2).toInt(), LigneExplode.at(3).toInt(),
                                  LigneExplode.at(4).toInt(), LigneExplode.at(5).toInt(), LigneExplode.at(6).toFloat());
                    break;
                }
            }
            else{
                if(LigneExplode.at(0) == "K"){
                    switch(LigneExplode.size()-1){
                    case 3:
                        AddKnocker(LigneExplode.at(1).toInt(), LigneExplode.at(2).toInt(), LigneExplode.at(3).toInt());
                        break;
                    case 5:
                        AddKnocker(LigneExplode.at(1).toInt(), LigneExplode.at(2).toInt(), LigneExplode.at(3).toInt(),
                                   LigneExplode.at(4).toInt(), LigneExplode.at(5).toInt());
                        break;
                    case 6:
                        AddKnocker(LigneExplode.at(1).toInt(), LigneExplode.at(2).toInt(), LigneExplode.at(3).toInt(),
                                   LigneExplode.at(4).toInt(), LigneExplode.at(5).toInt(), LigneExplode.at(6).toFloat());
                        break;
                    }
                }
                else{
                    if(LigneExplode.at(0) == "M"){
                        AddMur(LigneExplode.at(1).toInt(), LigneExplode.at(2).toInt(), LigneExplode.at(3).toInt());
                    }
                    else{
                        if(LigneExplode.at(0) == "F"){
                            AddFinish(LigneExplode.at(1).toInt(), LigneExplode.at(2).toInt());
                        }
                        else{
                            if(LigneExplode.at(0) == "G"){
                                AddGround(LigneExplode.at(1).toInt(), LigneExplode.at(2).toInt());
                            }
                            else{
                                if(LigneExplode.at(0) == "B"){
                                    if(LigneExplode.size()-1 == 2)
                                        AddBackGround(LigneExplode.at(1).toInt(), LigneExplode.at(2).toInt());
                                    else{
                                        if(LigneExplode.size()-1 == 1)
                                            AddBackGround(LigneExplode.at(1));
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    else{
        qDebug() << "Impossible d'ouvrir le fichier !\n Retour a zero !";
        cLevel++;
        LoadLevel();

    }
    fichierMap.close();
}

MyScene::MyScene(QObject *parent) : QGraphicsScene(parent){
    initTerrain();
    qDebug() << "Version 2j";
    //timer
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(20);
    cLevel=0;

    qDebug() << "Bienvenue dans Fast&Fast";
}
