#include <SDL3/SDL.h>
#include <string.h>
#include <stdbool.h>

#define PIXEL_GRID_WIDTH 64
#define PIXEL_GRID_HEIGHT 32
#define TRANSLATION_FACTOR 16

#define WINDOW_WIDTH (PIXEL_GRID_WIDTH * TRANSLATION_FACTOR)
#define WINDOW_HEIGHT (PIXEL_GRID_HEIGHT * TRANSLATION_FACTOR)

typedef bool PixelGrid[PIXEL_GRID_WIDTH][PIXEL_GRID_HEIGHT];

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

bool init();
void close();
void draw_pixel(int x, int y);

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

    int iterations = 0;
    int x = 0;

    while (quit == false)
    {
      iterations++;
      while (SDL_PollEvent(&e) == true)
      {
        if (e.type == SDL_EVENT_QUIT)
        {
          quit = true;
        }
      }

      SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
      SDL_RenderClear(renderer);

      for (int offset = 5; offset < 50; offset += 5)
      {
        for (int y = 0; y < PIXEL_GRID_HEIGHT; y++)
        {
          SDL_FRect rect = (SDL_FRect){.x = ((x + y + offset) % PIXEL_GRID_WIDTH) * TRANSLATION_FACTOR, .y = y * TRANSLATION_FACTOR, .w = TRANSLATION_FACTOR, .h = TRANSLATION_FACTOR};
          SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
          SDL_RenderFillRect(renderer, &rect);
        }
      }

      SDL_RenderPresent(renderer);
      if (iterations % 25 == 0)
      {
        x = (x + 1) % PIXEL_GRID_WIDTH;
      }
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
    window = SDL_CreateWindow("SDL3 Tutorial: Hello SDL3", WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_HIGH_PIXEL_DENSITY | SDL_WINDOW_OPENGL);
    if (window == NULL)
    {
      SDL_Log("Window could not be created! SDL error: %s\n", SDL_GetError());
      return false;
    }
    else
    {
      renderer = SDL_CreateRenderer(window, NULL);
      if (renderer == NULL)
      {
        SDL_Log("Could not create renderer! SDL error: %s\n", SDL_GetError());
        return false;
      }
      else
      {
        SDL_SetRenderLogicalPresentation(
            renderer,
            WINDOW_WIDTH,
            WINDOW_HEIGHT,
            SDL_LOGICAL_PRESENTATION_INTEGER_SCALE);
      }
    }
  }

  return true;
}

void close()
{
  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);
  window = NULL;
  renderer = NULL;
  SDL_Quit();
}

void draw_pixel(int x, int y)
{
  SDL_FRect rect = (SDL_FRect){.x = x * TRANSLATION_FACTOR, .y = y * TRANSLATION_FACTOR, .w = TRANSLATION_FACTOR, .h = TRANSLATION_FACTOR};
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  SDL_RenderFillRect(renderer, &rect);
}