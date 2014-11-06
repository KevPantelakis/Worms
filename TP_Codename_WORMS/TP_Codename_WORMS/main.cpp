

#if defined(__APPLE__) && defined(__MACH__) /* __APPLE & __MACH__ sont les deux Macro défini par LLVM */
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_mixer/SDL_mixer.h>
#include <SDL2_ttf/SDL_ttf.h>
#elif defined _WIN32 /* _Win32 Pour les configuration windows 32 & 64 bit */
#include <SDL2\SDL.h>
#include <SDL2\SDL_image.h>
#include <SDL2\SDL_ttf.h>
#include <SDL2\SDL_mixer.h>
#endif

#define WIDTH 1280
#define HEIGHT 720


#include "CWorms.h"




int main(int argc, char** argv) {
	SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO);// Initialisation des composantes
	TTF_Init();				 // SDL et autres librairies.
	Mix_Init(0);
	
	CWorms* Worms = new CWorms();
	Worms->Init();
	
	Worms->Start();

	delete Worms;
	SDL_Quit();
	TTF_Quit();
	Mix_Quit();
	
	return 0;
}