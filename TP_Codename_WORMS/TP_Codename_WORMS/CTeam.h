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
	CListeDC<CWorm*>* m_pListeWorm;
	SDL_Color m_TeamColor;
	unsigned short m_usrtNbWorms;

public:


	CTeam(string _strTeamName,SDL_Color _Color){
	
	}

};