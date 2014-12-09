#ifndef TP_Codename_WORMS_CObjets_h
#define TP_Codename_WORMS_CObjets_h


/*!
@CObjets
@Classe permettant la cr�ation d'un objet.
*/
class CObjets : public CEntity{
protected:
	//Donn�es membres:
	CExplosion* m_Explosif;  // Nuclear DATA
public:

	/*!
	@method Constructeur.
	@brief Initialise les donn�es membres.
	@param _iRayon : le rayon d'explosion
	@param _RectPos : le rect de l'objet
	@return Adresse m�moire de l'objet.
	@discussion Classe h�ritant de CEntity, elle prend donc les param�tres de CEntity.
	*/
	CObjets(SDL_Texture* _textureExplosion, SDL_Rect _RectPos, SDL_Texture* _Texture) :CEntity(_RectPos, _Texture){
		m_Explosif = new CExplosion(new CSprite("", _Texture, 12, 1, 30, 0), new CPosition(_RectPos.x, _RectPos.y));
	}

	/*!
	@Destructeur:
	@Permet de d�truire les objets cr��s en m�moire
	*/
	~CObjets(){
	}

	/*!
	@method Draw
	@brief Fonction virtuel pour dessiner l'entit�e sur un Renderer
	@param _Renderer : Le renderer sur lequel dessiner
	@return Aucun
	*/
	virtual void Draw(SDL_Renderer*) = 0;

	/*!
	@Accesseur virtuel IsItExploded
	@brief Permet de savoir si l'objet est explos� ou non.
	@return bool.
	*/
	virtual bool IsExploded(){return false;};
	
	virtual void Detonate(){}
};

#endif
