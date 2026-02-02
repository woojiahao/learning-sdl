#include <SDL3/SDL.h>
#include <string.h>
#include <stdbool.h>

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
  if (init() == false)
  {
    SDL_Log("Unable to initialize program\n");
    return 1;
  }
  else
  {
    bool quit = false;

    SDL_Event e;
    SDL_zero(e);

    while (quit == false)
    {
      while (SDL_PollEvent(&e) == true)
      {
        if (e.type == SDL_EVENT_QUIT)
        {
          quit = true;
        }
      }

      SDL_FillSurfaceRect(surface, NULL, SDL_MapSurfaceRGB(surface, 0xFF, 0xFF, 0xFF));
      SDL_UpdateWindowSurface(window);
    }

    close();
  }
  return 0;
}

bool init()
{
  if (SDL_Init(SDL_INIT_VIDEO) == false)
  {
    SDL_Log("SDL could not initialize! SDL error: %s\n", SDL_GetError());
    return false;
  }
  else
  {
    window = SDL_CreateWindow("SDL3 Tutorial: Hello SDL3", width, height, 0);
    if (window == NULL)
    {
      SDL_Log("Window could not be created! SDL error: %s\n", SDL_GetError());
      return false;
    }
    else
    {
      surface = SDL_GetWindowSurface(window);
    }
  }

  return true;
}

void close()
{
  SDL_DestroyWindow(window);
  window = NULL;
  surface = NULL;
  SDL_Quit();
}