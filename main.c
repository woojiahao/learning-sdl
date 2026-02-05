#include <SDL3/SDL.h>
#include <string.h>
#include <stdbool.h>

const static int width = 1024;
const static int height = 512;

SDL_Window *window = NULL;
SDL_Surface *hello_world = NULL;
SDL_FRect rect;
SDL_Renderer *rect_renderer = NULL;

bool init();
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

      SDL_SetRenderDrawColor(rect_renderer, 255, 255, 255, 255);
      SDL_RenderClear(rect_renderer);

      rect = (SDL_FRect){.x = 0, .y = 0, .w = 16, .h = 16};
      SDL_SetRenderDrawColor(rect_renderer, 255, 0, 0, 255);
      SDL_RenderRect(rect_renderer, &rect);
      SDL_RenderFillRect(rect_renderer, &rect);

      rect = (SDL_FRect){.x = 0, .y = 16, .w = 16, .h = 16};
      SDL_SetRenderDrawColor(rect_renderer, 0, 255, 0, 255);
      SDL_RenderRect(rect_renderer, &rect);
      SDL_RenderFillRect(rect_renderer, &rect);

      rect = (SDL_FRect){.x = 0, .y = 16, .w = 16, .h = 16};
      SDL_SetRenderDrawColor(rect_renderer, 0, 255, 0, 255);
      SDL_RenderRect(rect_renderer, &rect);
      SDL_RenderFillRect(rect_renderer, &rect);

      rect = (SDL_FRect){.x = 16, .y = 0, .w = 16, .h = 16};
      SDL_SetRenderDrawColor(rect_renderer, 0, 0, 255, 255);
      SDL_RenderRect(rect_renderer, &rect);
      SDL_RenderFillRect(rect_renderer, &rect);

      SDL_RenderPresent(rect_renderer);
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
      rect_renderer = SDL_CreateRenderer(window, NULL);
      if (rect_renderer == NULL)
      {
        SDL_Log("Could not create renderer! SDL error: %s\n", SDL_GetError());
        return false;
      }
    }
  }

  return true;
}

void close()
{
  SDL_DestroyWindow(window);
  window = NULL;
  rect_renderer = NULL;
  SDL_Quit();
}