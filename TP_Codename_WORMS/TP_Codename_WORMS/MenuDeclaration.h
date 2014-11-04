/*!
 * Fichier pour la déclaration des Menu et de leurs fonction
 */


/*!
@discussion Déclaration de la Window.
*/
CWindow* Window = new CWindow(WIDTH,HEIGHT);
CGestionnaireRessources* GestionnaireDeResources = new CGestionnaireRessources();

void LoadResources(){
	GestionnaireDeResources->Ajouter(new CFont("Font", "C:\\Users\\1303126\\Documents\\GitHub\\Worms\\Ressources\\Archeologicaps.ttf", 18));
	GestionnaireDeResources->Ajouter(new CSprite("SpriteBtnFleche", IMG_LoadTexture(Window->getRenderer(), "C:\\Users\\1303126\\Documents\\GitHub\\Worms\\Ressources\\Btn2.png"), 2, 4, 10, 0));
	GestionnaireDeResources->Ajouter(new CSprite("SpriteBtnClick", IMG_LoadTexture(Window->getRenderer(), "C:\\Users\\1303126\\Documents\\GitHub\\Worms\\Ressources\\Btn1.png"), 2, 4, 10, 0));
}



/*!
 @discussion Déclaration du Menu Principal.
 */
CMenu* MenuPrincipal;
CButton* ButtonNewGame = new CButton("BtnNewGame", "Play", (CFont*)GestionnaireDeResources->Obtenir("Font"), {0,0,0,0}, (CSprite*)GestionnaireDeResources->Obtenir("SpriteBtnClick"));
CButton* ButtonQuit = new CButton("BtnQuit", "Quit", (CFont*)GestionnaireDeResources->Obtenir("Font"), { 0, 0, 0, 0 }, (CSprite*)GestionnaireDeResources->Obtenir("SpriteBtnClick"));

/*!
@discussion Déclaration du Menu nouvelle partie.
*/
CMenu* MenuNewGame;

/*!
@discussion Déclaration du Menu Créarion d'une nouvelle équipe.
*/
CMenu* MenuNewTeam;

/*!
@discussion Déclaration du Menu pause.
*/
CMenu* MenuPause;

void CreateMenuPrincipal(){
	MenuPrincipal = new CMenu(Window->getRenderer(), { 0, 0, WIDTH, HEIGHT });
	MenuPrincipal->AddElement(ButtonNewGame, WIDTH - 200, HEIGHT - 130, 100, 30);
	MenuPrincipal->AddElement(ButtonQuit, WIDTH - 200, HEIGHT - 170, 100, 30);
}