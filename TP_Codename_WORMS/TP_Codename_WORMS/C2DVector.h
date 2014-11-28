//
//  C2DVector.h
//  TP_Codename_WORMS
//
//  Cr�� par Kevin Pantelakis.
//  Mise � jour par Kevin Pantelakis le 2014-11-27
//  
// S'arranger que le vecteur prennne (avec trois n) les angles en degr�s.

/*!
@class C2DVector
@discussion Classe qui un Vecteur � 2 coordon�es
*/
class C2DVector{
private:
	int	m_XOrigine,		// Cordonn�e X de d�part
		m_YOrigine,		// Cordonn�e Y de d�part
		m_XFin,			// Cordonn�e X de Fin
		m_YFin;			// Cordonn�e Y de Fin
	double	m_Norme,	// Norme du vecteur.
		m_Orientation,	// Orientation.
		m_ComposanteX,	// Composante X.
		m_ComposanteY;	// Composante Y.

public:

	/*!
	@method Constructeur.
	@brief Initialise les donn�es membres.
	@param _Norme: Norme du vecteur
	@param _AngleRad: Angle du vecteur
	@param _XDepart: Position X de d�part du vecteur
	@param _YDepart: Position Y de D�part du vecteur
	@return Adresse m�moire de l'objet.
	@discussion Initialise un vecteur avec sa norme son orientation et sa position de d�part.
	*/
	C2DVector(double _Norme, double _AngleRad, int _XDepart, int _YDepart){
		m_XOrigine = _XDepart;
		m_YOrigine = _YDepart;
		m_Norme = _Norme;
		m_Orientation = _AngleRad;
		m_ComposanteX = _Norme * cos(_AngleRad);
		m_ComposanteY = _Norme * sin(_AngleRad);
		if (m_ComposanteX < 0.5)
			m_ComposanteX = 0;
		m_XFin = _XDepart + (m_ComposanteX);
		m_YFin = _YDepart + (m_ComposanteY);
	}

	/*!
	@method Constructeur.
	@brief Initialise les donn�es membres.
	@param _XDepart: Position X de d�part du vecteur
	@param _YDepart: Position Y de D�part du vecteur
	@param _Xfin: Position X de fin du vecteur
	@param _Yfin: Position Y de fin du vecteur
	@return Adresse m�moire de l'objet.
	@discussion Initialise un vecteur avec sa position de d�part et sa position de fin.
	*/
	C2DVector(int _XDepart, int _YDepart, int _Xfin, int _Yfin){
		m_XOrigine = _XDepart;
		m_YOrigine = _YDepart;
		m_XFin = _Xfin;
		m_YFin = _Yfin;
		m_Norme = sqrt(pow(_Xfin - _XDepart, 2) + pow(_Yfin - _YDepart, 2));
		m_ComposanteX = _Xfin - _XDepart;
		m_ComposanteY = _Yfin - _YDepart;
		if ((m_ComposanteX == 0) && (m_ComposanteY > 0))
			m_Orientation = M_PI / 2;
		else if ((m_ComposanteX == 0) && (m_ComposanteY < 0))
			m_Orientation = 1.5 * M_PI;
		else if ((m_ComposanteX > 0) && (m_ComposanteY == 0))
			m_Orientation = 0;
		else if ((m_ComposanteX < 0) && (m_ComposanteY == 0))
			m_Orientation = M_PI;
		else{
			m_Orientation = atan(m_ComposanteY / m_ComposanteX);
			if ((m_ComposanteX < 0) || ((m_ComposanteX < 0) && (m_ComposanteY < 0)))
				m_Orientation = M_PI + m_Orientation;
			else if (m_ComposanteY < 0)
				m_Orientation = (2 * M_PI) + m_Orientation;
		}
	}

	/*!
	@method Constructeur.
	@brief Initialise les donn�es membres.
	@param _XDepart: Position X de d�part du vecteur.
	@param _YDepart: Position Y de D�part du vecteur.
	@param _Compx: Composante X du vecteur.
	@param _CompY: Composante y du vecteur.
	@return Adresse m�moire de l'objet.
	@discussion Initialise un vecteur avec sa position de d�part et ses composantes.
	*/
	C2DVector(int _XDepart, int _YDepart, double _CompX, double _CompY){
		m_XOrigine = _XDepart;
		m_YOrigine = _YDepart;
		m_ComposanteX = _CompX;
		m_ComposanteY = _CompY;
		m_XFin = _XDepart + (m_ComposanteX);
		m_YFin = _YDepart + (m_ComposanteY);
		m_Norme = sqrt(pow(m_ComposanteX, 2) + pow(m_ComposanteY, 2));
		if ((m_ComposanteX == 0) && (m_ComposanteY > 0))
			m_Orientation = M_PI / 2;
		else if ((m_ComposanteX == 0) && (m_ComposanteY < 0))
			m_Orientation = 1.5 * M_PI;
		else if ((m_ComposanteX > 0) && (m_ComposanteY == 0))
			m_Orientation = 0;
		else if ((m_ComposanteX < 0) && (m_ComposanteY == 0))
			m_Orientation = M_PI;
		else{
			m_Orientation = atan(m_ComposanteY / m_ComposanteX);
			if ((m_ComposanteX < 0) || ((m_ComposanteX < 0) && (m_ComposanteY < 0)))
				m_Orientation = M_PI + m_Orientation;
			else if (m_ComposanteY < 0)
				m_Orientation = (2 * M_PI) + m_Orientation;
		}
	}

	//Redefinition de l'op�rateur +:
	//
	C2DVector * operator+ (C2DVector * _Vector){
		return new C2DVector(m_XOrigine, m_YOrigine, m_ComposanteX + _Vector->getComposanteX(), m_ComposanteY + _Vector->getComposanteY());
	}


	//Accesseurs...

	int getXfin(){ return m_XFin; }
	int getYfin(){ return m_YFin; }
	int getXDebut(){ return m_XOrigine; }
	int getYDebut(){ return m_YOrigine; }
	double getNorme(){ return m_Norme; }
	double getOrientation(){ return m_Orientation; }
	double getComposanteX(){ return m_ComposanteX; }
	double getComposanteY(){ return m_ComposanteY; }

	void setXYfin(int _x, int _y){
		m_XFin = _x;
		m_YFin = _y;
		m_Norme = sqrt(pow(m_XFin - m_XOrigine, 2) + pow(m_YFin - m_YOrigine, 2));
		if ((m_ComposanteX == 0) && (m_ComposanteY > 0))
			m_Orientation = M_PI / 2;
		else if ((m_ComposanteX == 0) && (m_ComposanteY < 0))
			m_Orientation = 1.5 * M_PI;
		else if ((m_ComposanteX > 0) && (m_ComposanteY == 0))
			m_Orientation = 0;
		else if ((m_ComposanteX < 0) && (m_ComposanteY == 0))
			m_Orientation = M_PI;
		else{
			m_Orientation = atan(m_ComposanteY / m_ComposanteX);
			if ((m_ComposanteX < 0) || ((m_ComposanteX < 0) && (m_ComposanteY < 0)))
				m_Orientation = M_PI + m_Orientation;
			else if (m_ComposanteY < 0)
				m_Orientation = (2 * M_PI) + m_Orientation;
		}
	}
	void setXYDebut(int _x, int _y){
		m_XOrigine = _x;
		m_YOrigine = _y;
	}
	void setComposanteXY(double _CompX, double _CompY){
		m_ComposanteX = _CompX;
		m_ComposanteY = _CompY;
		if (m_ComposanteX < 0.5)
			m_ComposanteX = 0;
		m_XFin = m_XOrigine + (m_ComposanteX);
		m_YFin = m_YOrigine + (m_ComposanteY);
		m_Norme = sqrt(pow(m_XFin - m_XOrigine, 2) + pow(m_YFin - m_YOrigine, 2));
		if ((m_ComposanteX == 0) && (m_ComposanteY > 0))
			m_Orientation = M_PI / 2;
		else if ((m_ComposanteX == 0) && (m_ComposanteY < 0))
			m_Orientation = 1.5 * M_PI;
		else if ((m_ComposanteX > 0) && (m_ComposanteY == 0))
			m_Orientation = 0;
		else if ((m_ComposanteX < 0) && (m_ComposanteY == 0))
			m_Orientation = M_PI;
		else{
			m_Orientation = atan(m_ComposanteY / m_ComposanteX);
			if ((m_ComposanteX < 0) || ((m_ComposanteX < 0) && (m_ComposanteY < 0)))
				m_Orientation = M_PI + m_Orientation;
			else if (m_ComposanteY < 0)
				m_Orientation = (2 * M_PI) + m_Orientation;
		}
	}
	void setNorme(double _Norme){
		m_Norme = _Norme;
		m_ComposanteX = m_Norme * cos(m_Orientation);
		m_ComposanteY = m_Norme * sin(m_Orientation);
		if (m_ComposanteX < 0.5)
			m_ComposanteX = 0;
		m_XFin = m_XOrigine + (m_ComposanteX);
		m_YFin = m_YOrigine + (m_ComposanteY);
	}
	void setOrientation(double _AngleRadian){
		m_Orientation = _AngleRadian;
		m_ComposanteX = m_Norme * cos(m_Orientation);
		m_ComposanteY = m_Norme * sin(m_Orientation);
		if (m_ComposanteX < 0.5)
			m_ComposanteX = 0;
		m_XFin = m_XOrigine + (m_ComposanteX);
		m_YFin = m_YOrigine + (m_ComposanteY);
	}

	/*!
	@method Normalize
	@brief Normalise un vecteur.
	@discussion Donne un vecteur de norme 1 mais avec la m�me orientation.
	*/
	void Normalize(){
		if (m_Norme)
			m_Norme /= (m_Norme / 2);
		m_ComposanteX = cos(m_Orientation);
		m_ComposanteY = sin(m_Orientation);
	}



};