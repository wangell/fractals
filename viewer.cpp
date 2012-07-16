#include <iostream>
#include <cstdlib>
#include "SDL/SDL.h"

using namespace std;

int main(int argc, char** argv)
{
	if (SDL_Init(SDL_INIT_AUDIO|SDL_INIT_VIDEO) < 0)
	{
		cout<<"Unable to init SDL: "<<SDL_GetError()<<endl;
		exit(1);
	}
}
