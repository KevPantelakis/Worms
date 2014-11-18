/*
Nom : CTrajectory
Discussion : Classe repr�sentant la trajectoire d'un point
*/


class CTrajectory{
private:
	long m_lTrajectoryStartTime;
	C2DVector* m_StartPos;
	C2DVector* m_TrajectoryInitSpeed;
public:
	//Constructeur...
	CTrajectory(C2DVector* _StartPos, C2DVector* _InitSpeed){
		m_lTrajectoryStartTime = SDL_GetTicks();
		m_StartPos = _StartPos;
		m_TrajectoryInitSpeed = _InitSpeed;
	}

	//Destructeur...
	~CTrajectory(){
		delete m_StartPos;
		delete m_TrajectoryInitSpeed;
	}

	/*
	Method : GetPosition
	Brief : Fonction qui retourne la variation de la position dans la trajectoire selon le temps
	Params : 
	  _time : Temps pass� depuis le d�but de la trajectoire
	Return : Vecteur repr�sentant la position au temps pass� en param�tre
	*/
	C2DVector GetPosition(){
		double dTimeVariation = (SDL_GetTicks() - m_lTrajectoryStartTime);
		double dTimeVarExp2 = dTimeVariation * dTimeVariation;
		return C2DVector(m_TrajectoryInitSpeed->getX() * dTimeVariation + CPhysics::GetWind()->getX()
			/ 2 * dTimeVarExp2 + m_StartPos->getX(),
			m_TrajectoryInitSpeed->getY() * dTimeVariation + (CPhysics::GetWind()->getY() + CPhysics::GetGravity())
			/ 2 * dTimeVarExp2 + m_StartPos->getY());
	}

	/*
	Method : Bounce
	Brief : Proc�dure qui ajuste la trajectoire suite � un rebond
	Params : 
		_Surface : Pointeur vers la surface impliqu�e dans le rebond
	*/
	void Bounce(SDL_Surface* _Surface){
	}
};