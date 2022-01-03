/*This source code copyrighted by Lazy Foo' Productions (2004-2020)
and may not be redistributed without written permission.*/

//Using SDL and standard IO
#include <SDL2/SDL.h>
#include <stdio.h>
#include <string>

using namespace std;

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//Start up SDL and create a new window
bool init();

//Load media
bool loadMedia();

//Free media and shut down SDL
void close();

//The window to render to
SDL_Window* gWindow = NULL;

//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

//The image to load and show
SDL_Surface* gHelloWorld = NULL;


bool init()
{
  bool success = true;

  if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
  {
    printf( "SDL could not initialise! SDL_ERROR: %s\n", SDL_GetError() );
    success = false;
  }
  else
  {
    //Create window
		gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
    if( gWindow == NULL )
    {
      printf( "SDL could not create window! SDL_ERROR: %s\n", SDL_GetError() );
      success = false;
    }
    else
    {
      //Get window surface
      gScreenSurface = SDL_GetWindowSurface( gWindow );
    }
  }

  return success;
}

bool loadMedia()
{
  bool success = true;
  const char* filename = "hello_world.bmp";

  gHelloWorld = SDL_LoadBMP( filename );
  if( gHelloWorld == NULL)
  {
    printf("Unable to load image %s! SDL_ERROR: %s\n", filename, SDL_GetError() );
    success = false;
  }

  return success;
}

void close()
{
  //Deallocate surface
  SDL_FreeSurface( gHelloWorld );
  gHelloWorld = NULL;

  //Destroy window
  SDL_DestroyWindow( gWindow );

  //Quit SDL subsystems
  SDL_Quit();
}






int main( int argc, char* args[] )
{
  //Start up SDL and create window
  if( !init() )
  {
    printf("Failed to initialise!\n");
  }
  else
  {
    if( !loadMedia() )
    {
      printf("Failed to load media!\n");
    }
    else
    {
      //Apply the image
      SDL_BlitSurface( gHelloWorld, NULL, gScreenSurface, NULL );

      //Update the surface
      SDL_UpdateWindowSurface( gWindow );

      //Wait 2 seconds
      SDL_Delay(2000);
    }
  }

  //Free resources
  close();

  return 0;
}
