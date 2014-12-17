#ifndef TP_Codename_WORMS_CMines_h
#define TP_Codename_WORMS_CMines_h


/*!
@CMines
@Classe permettant la cr�ation d'une mines
*/
class CMines : public CObjets{
private:

public:
	/*!
	@method Constructeur.
	@brief Initialise les donn�es membres.
	@param _iRayon: le rayond d'explosion de l'objet
	@param _RectPos: la pos du rectangle de l'objet
	@param _pTexture : texture de l'image � afficher
	@return Adresse m�moire de l'objet.
	@discussion Classe h�ritant de CObjets, elle prend donc les param�tres du constructeur CObjets
	*/
	CMines(SDL_Rect _RectPos, SDL_Texture* _Texture, CExplosion* _Explosion) :CObjets(_RectPos, _Texture, _Explosion){
	}

	/*!
	@Destructeur:
	@Permet de d�truire les objets cr��s en m�moire
	*/
	~CMines(){
	}

	/*!
	@method Draw
	@param _Renderer : Renderer pour rendre la texture de la mine
	@return null
	*/
	void Draw(SDL_Renderer* _pRenderer){
			//SDL_RenderCopy(_pRenderer, m_pTexture, NULL, &m_RectPosition);
		if ((!m_Angle) && (m_EntityState == Immobile))
			m_Angle = CPhysics::EvaluateSlope({m_RectPosition.x, m_RectPosition.y + m_RectPosition.h, m_RectPosition.w, m_RectPosition.h});
		SDL_RenderCopyEx(_pRenderer, m_pTexture, NULL, &m_RectPosition, RadToDeg(m_Angle), NULL, SDL_FLIP_NONE);
	}

	/*!
	@method HandleEvent
	@param _Event : Un SDL_Event pour traiter les evenement
	@return null
	*/
	void HandleEvent(SDL_Event _Event){
		m_boFocus = true;
	}

	/*!
	@M�thode:
	@ReactToExplosion
	@Permet de calculer les dommages subit par l'explosion
	*/
	void ReactToExplosion(int _iX, int _iY, int _iRayon){
		//Objet a droite de l'explosion
		if (m_RectPosition.x >= _iX && !m_boIsexploded){
			if (m_RectPosition.y >= _iY && !m_boIsexploded){
				if (sqrt((pow((m_RectPosition.x - _iX), 2) + pow((m_RectPosition.y - _iY), 2))) < _iRayon)
					m_boIsexploded = true;
				else
				if (sqrt((pow((m_RectPosition.x - _iX), 2) + pow((m_RectPosition.y + 8 - _iY), 2))) < _iRayon)
					m_boIsexploded = true;
			}

			if (m_RectPosition.y <= _iY && !m_boIsexploded){
				if (sqrt((pow((m_RectPosition.x - _iX), 2) + pow((_iY - m_RectPosition.y), 2))) < _iRayon)
					m_boIsexploded = true;
				else
				if (sqrt((pow((m_RectPosition.x - _iX), 2) + pow((_iY - m_RectPosition.y + 8), 2))) < _iRayon)
					m_boIsexploded = true;
			}

		}
		//Objet a gauche de l'explosion
		if (m_RectPosition.x <= _iX && !m_boIsexploded){
			if (m_RectPosition.y >= _iY && !m_boIsexploded){
				if (sqrt((pow((_iX - m_RectPosition.x + 24), 2) + pow((m_RectPosition.y - _iY), 2))) < _iRayon)
					m_boIsexploded = true;
				else
				if (sqrt((pow((_iX - m_RectPosition.x + 24), 2) + pow((m_RectPosition.y + 8 - _iY), 2))) < _iRayon)
					m_boIsexploded = true;
			}

			if (m_RectPosition.y <= _iY && !m_boIsexploded){
				if (sqrt((pow((_iX - m_RectPosition.x + 24), 2) + pow((_iY - m_RectPosition.y), 2))) < _iRayon)
					m_boIsexploded = true;
				else
				if (sqrt((pow((_iX - m_RectPosition.x + 24), 2) + pow((_iY - m_RectPosition.y + 8), 2))) < _iRayon)
					m_boIsexploded = true;
			}
		}
	}

	/*!
	@method Acesseurs
	@brief Servent a acceder/modifier aux donn�es membres.
	*/

	void setExplosion(bool _boSet){
		m_boIsexploded = _boSet;
	}

	void setPos(int _ix, int _iy){
		m_RectPosition.x = _ix;
		m_RectPosition.y = _iy;
	}


};

#endif
