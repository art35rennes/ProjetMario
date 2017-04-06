/**************************************************************HELP**************************************************************/
*	B: ajout d'un élément background.
*		-B,SizeX(int),SizeY(int)
*		-B,PathImageBackGround(string)
*
*	G: ajout d'un élément ground (y fixé à 370).
*		-G,PosX(int),Width(int)
*
*	K: ajout d'un élément de 'knocker'. L'élément peut être mobile ou non (1er cas, immobile).
*		-K,PosX(int),PosY(int),Type(int)
*		-K,PosX(int),PosY(int),Type(int),Sens,Marge(int)
*		-K,PosX(int),PosY(int),Type(int),Sens,Marge(int),Vitesse(float)
*
*	P: ajout d'un élément de type plateforme. L'élément peut être mobile ou non (1er cas, immobile).
*		-P,PosX(int),PosY(int),Type(int)
*		-P,PosX(int),PosY(int),Type(int),Sens,Marge(int)
*		-P,PosX(int),PosY(int),Type(int),Sens,Marge(int),Vitesse(float)
*
*	M: ajout d'un élément de type mur.
*		-M,PosX(int),PosY(int),Type(int)
*
*	F: ajout de l'objectif de fin.
*		-F,PosX(int),PosY(int)
*
*
*	Liste des types:
*
*
*   Plateforme:
*
* -1: 80x6 px, immobile	-11: 80x6 px, mvt horizontale (Sens: 1 ou -1)	-21: 80x6 px, mvt verticale (Sens: 2 ou -2)
* -2: 40x6 px, immobile	-12: 40x6 px, mvt horizontale (Sens: 1 ou -1)	-22: 40x6 px, mvt verticale (Sens: 2 ou -2)
* -3: 20x6 px, immobile	-13: 20x6 px, mvt horizontale (Sens: 1 ou -1)	-23: 20x6 px, mvt verticale (Sens: 2 ou -2) 
* -4: 8x8 px, immobile	
*
*   Knocker:
*
* -1: 8x16 px, immobile	-11: 8x16 px, mvt horizontale (sens 1 ou -1)	-21: 8x16 px, mvt verticale (sens 2 ou -2)
* -2: 16x16 px, immobile-12: 6x40 px, mvt horizontale (sens 1 ou -1)
* -3: 20x6 px, immobile	-13: 6x20 px, mvt horizontale (sens 1 ou -1)
* -4: 40x6 px, immobile	
*
*   Mur:
*
* -1: 6x50 px
* -2: 12x50 px
* -3: 12x25 px
* -4: 6x25 px
*
/**************************************************************END***************************************************************/
