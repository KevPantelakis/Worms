#define BUFFER 1024
class CSound : public CRessource{
private:
	Mix_Music* m_pSound0;		 // Musique � jouer
	Mix_Music* m_pSound1;		 // Musique � jouer
	Mix_Music* m_pSound2;		 // Musique � jouer
	static bool m_boInitialized; // Indique si la musique � �t� initialis�.
public:

	/*!
	@method Constructeur.
	@brief Initialise les donn�es membres.
	@param _Name Texture du son.
	@param _Path emplacement de la musique.
	@return Adresse m�moire de l'objet.
	@discussion Classe h�ritant de Ressource, elle prend donc les param�tres de CRessource.
	*/
	CSound(const char* _Name, const char* _Path1, const char* _Path2, const char* _Path3) : CRessource(_Name){
		if (!m_boInitialized){
			Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, BUFFER);
			Mix_AllocateChannels(0);
			m_boInitialized = true;
		}
		m_pSound0 = Mix_LoadMUS(_Path1);
		m_pSound1 = Mix_LoadMUS(_Path2);
		m_pSound2 = Mix_LoadMUS(_Path3);
	}

	~CSound(){
		if (m_pSound1 != nullptr){
			Mix_FreeMusic(m_pSound1);
			m_pSound1 = nullptr;
		}
		if (m_pSound0 != nullptr){
			Mix_FreeMusic(m_pSound0);
			m_pSound0 = nullptr;
		}
		if (m_pSound2 != nullptr){
			Mix_FreeMusic(m_pSound2);
			m_pSound2 = nullptr;
		}
	}

	/*!
	@method Play
	@brief methode pour faire jouer la musique
	@param _inbrOfLoop : nombre de fois que le musique doit �tre jouer
	@return Aucun
	*/
	void Play(int _inbrOfLoop){
		if (!Mix_PlayingMusic())
			Mix_PlayMusic(m_pSound1, 1);
		else
			Mix_ResumeMusic();
	}
	
	void ContinuePlaying(){
		if (!Mix_PlayingMusic()){
		switch (rand() % 3) {
			case 0:
				Mix_PlayMusic(m_pSound0, 1);
				break;
			case 1:
				Mix_PlayMusic(m_pSound1, 1);
				break;
			case 2:
				Mix_PlayMusic(m_pSound2, 1);
				break;
		}
		}
	}

	/*!
	@method Pause
	@brief methode pour mettre la musique en pause
	@param Aucun
	@return Aucun
	*/
	void Pause(){
		if (Mix_PlayingMusic())
			Mix_PauseMusic();
	}
};
bool CSound::m_boInitialized = false;