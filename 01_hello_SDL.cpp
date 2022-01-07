/*This source code copyrighted by Lazy Foo' Productions (2004-2020)
and may not be redistributed without written permission.*/

//Using SDL and standard IO
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
//#include <SDL_mixer.h>
//#include <SDL_ttf.h>
#include <stdio.h>
#include <string>

using namespace std;

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//Key press surfaces
enum KeyPressSurface
{
  KEY_PRESS_DEFAULT,
  KEY_PRESS_LEFT,
  KEY_PRESS_RIGHT,
  KEY_PRESS_SPACE,
  KEY_PRESS_TOTAL
};

//Start up SDL and create a new window
bool init();

//Load media
bool loadMedia();

//Free media and shut down SDL
void close();

//Load an image
SDL_Surface* loadSurface( const char* path );

//The window to render to
SDL_Window* gWindow = NULL;

//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

//The images which correspond to a keypres
SDL_Surface* gKeyPressSurfaces[ KEY_PRESS_TOTAL ];

//Current displayed image
SDL_Surface* gCurrentSurface = NULL;



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
      //Initialise PNG loading
      int imgFlags = IMG_INIT_PNG; // 2
      if( !( IMG_Init( imgFlags ) & imgFlags ) )
      {
        printf( "SDL_image could not initialise! IMG_ERROR: %s\n", IMG_GetError() );
        success = false;
      }
      else
      {
        //Get window surface
        gScreenSurface = SDL_GetWindowSurface( gWindow );
      }
    }
  }

  return success;
}

bool loadMedia()
{
  bool success = true;
  const char* filename = "hello_world.bmp";
  const char* run_right_ = "run_right.bmp";
  const char* run_left_ = "run_left.bmp";
  const char* balloon_ = "balloon.bmp";
  const char* pop_ = "pop.bmp";

  gKeyPressSurfaces[ KEY_PRESS_DEFAULT ] = loadSurface( filename );
  gKeyPressSurfaces[ KEY_PRESS_LEFT ] = loadSurface( run_left_ );
  gKeyPressSurfaces[ KEY_PRESS_RIGHT ] = loadSurface( run_right_ );
  gKeyPressSurfaces[ KEY_PRESS_SPACE ] = loadSurface( pop_ );

  for (int i = 0; i < KEY_PRESS_TOTAL; i++)
  {
    if( gKeyPressSurfaces[ i ] == NULL )
    {
      printf( "Failed to load image %i\n", i);
      success = false;
    }
  }
  
  return success;
}

void close()
{
  //Deallocate surface
  SDL_FreeSurface( gCurrentSurface );
  gCurrentSurface = NULL;

  //Destroy window
  SDL_DestroyWindow( gWindow );

  //Quit SDL subsystems
  SDL_Quit();
}

SDL_Surface* loadSurface( const char* filename )
{
  //Final optimised image
  SDL_Surface* optimisedSurface = NULL;

  //Load image at specified path
  //SDL_Surface* loadedSurface = SDL_LoadBMP( filename );
  //
 
  //Load an image with SDL_Image
  SDL_Surface* loadedSurface = IMG_Load( filename );

  if( loadedSurface == NULL )
  {
    //printf("Unable to load image %s! SDL_ERROR: %s\n", filename, SDL_GetError() );
    printf("Unable to load image %s! IMG_ERROR: %s\n", filename, IMG_GetError() );
  }
  else
  {
    //Convert surface to screen format
    optimisedSurface = SDL_ConvertSurface( loadedSurface, gScreenSurface->format, 0 );
    if( optimisedSurface == NULL)
    {
      printf( "Unable to optimise image %s! SDL_ERROR: %s\n", filename, SDL_GetError() );
    }

    SDL_FreeSurface( loadedSurface );
  }
 
  //TODO: What should I return if this call fails? 
  return optimisedSurface;
}





int main( int argc, char* args[] )
{
  // Main loop flag
  bool quit = false;

  //Event handler
  SDL_Event e;

  //Screen-sized rectangle
  SDL_Rect stretchRect;

  stretchRect.x = 0;
  stretchRect.y = 0;
  stretchRect.w = SCREEN_WIDTH;
  stretchRect.h = SCREEN_HEIGHT;


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
      //Event loop
      while( !quit )
      {
        while( SDL_PollEvent( &e ) != 0 )
        {
          //User requests quit
          if( e.type == SDL_QUIT )
          {
            quit = true;
          }
          else if( e.type == SDL_KEYDOWN )
          {
            //Select surfaces based on key press
            switch( e.key.keysym.sym )
            {
              case SDLK_LEFT:
                gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_LEFT ];
                break;
                  
              case SDLK_RIGHT:
                gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_RIGHT ];
                break;
              
              case SDLK_SPACE:
                gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SPACE ];
                break;

              default:
                gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_DEFAULT ];
                break;
            }
          }

        }

        //Apply the image
        //SDL_BlitSurface( gCurrentSurface, NULL, gScreenSurface, NULL );
        SDL_BlitScaled( gCurrentSurface, NULL, gScreenSurface, &stretchRect );
        //Update the surface
        SDL_UpdateWindowSurface( gWindow );
      }
    }
  }

  //Free resources
  close();

  return 0;
}
