#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <string.h>

const static int width = 640;
const static int height = 480;

SDL_Window *window = NULL;
SDL_Surface *surface = NULL;
SDL_Surface *hello_world = NULL;

bool init();
bool load_media();
void close();

int main()
{
  return 0;
}

bool init()
{
  bool success = true;

  if (SDL_Init(SDL_INIT_VIDEO) == false)
  {
    SDL_Log("SDL could not initialize! SDL error: %s\n", SDL_GetError());
    success = false;
  } else {

  }

  return success;
}