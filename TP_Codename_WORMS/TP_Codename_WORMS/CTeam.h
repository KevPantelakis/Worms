//
//  CTeam.h
//  
//  Created by Kevin Pantelakis on 2014-11-11.
//
#define MAXWORMS 6
/*!
@class CTeam
@discussion Classe repr�sentant une �quipe.
*/
class CTeam{
private:
	string m_strTeamName;
	CWorm* m_pTabWorm[6];
	SDL_Color m_TeamColor;
	Uint8 m_pNumberOfWorm;
	Uint8 m_uiNbOfPlayingWorms;
	Uint8 m_uiWormTurn;
	bool m_boFocus;

public:

	CTeam(string _strTeamName, SDL_Color _Color){
		m_boFocus = false;
		m_uiWormTurn = 0;
		m_pNumberOfWorm = 0;
		m_uiNbOfPlayingWorms = 0;
	}

	void NextWormTurn(){
		Uint8 temp = (m_uiWormTurn) % m_uiNbOfPlayingWorms;
		if (m_pTabWorm[temp]->isFocused()){
			m_pTabWorm[temp]->setFocus(false);
		}
		m_pTabWorm[(temp + 1) % m_uiNbOfPlayingWorms]->setFocus(true);
		m_uiWormTurn++;
	}

	void draw(SDL_Renderer* _Renderer){
		for (int i = 0; i < m_uiNbOfPlayingWorms; i++)
			m_pTabWorm[i]->Draw(_Renderer);
	}

	void AddWorm(CWorm* _Worm){
		m_pTabWorm[m_pNumberOfWorm] = _Worm;

		if (!m_pNumberOfWorm)
			m_pTabWorm[m_pNumberOfWorm]->setFocus(true);
		else
			m_pTabWorm[m_pNumberOfWorm]->setFocus(false);

		m_pNumberOfWorm++;
	}


	/*!
	@Accesseurs
	*/
	void setNbPlayingWorm(Uint8 _uiNumber){ m_uiNbOfPlayingWorms = _uiNumber; }

	void setFocus(bool _boFocus){ m_boFocus = _boFocus; }

	void setTeamColor(SDL_Color _Color) { m_TeamColor = _Color; }

	void setTeamName(string _strName){ m_strTeamName = _strName; }

	bool IsFocussed(){ return m_boFocus; }

	Uint8 getNumberOfPlayingWorms(){ return m_uiNbOfPlayingWorms; }

	string getTeamName(){ return m_strTeamName; }

	CWorm* getPlayingWorm(){ return m_pTabWorm[m_uiWormTurn % m_uiNbOfPlayingWorms]; }



};