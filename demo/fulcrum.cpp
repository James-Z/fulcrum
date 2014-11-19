
#include <vector>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/file.h>
#include <unistd.h>
#include <errno.h>

#include <GL/glew.h>
/* #include <GL/gl.h> */
#include <GL/glx.h>

#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xatom.h>
#include <X11/cursorfont.h>

#include <SDL2/SDL.h>
/* #include <SDL2/SDL_opengl.h> */

#include "_scene_base.hpp"
#include "_object_base.hpp"
#include "_shader_manager.hpp"
#include "_asset_manager.hpp"

//
#include "game_scene.hpp"

#include <bullet/BulletCollision/CollisionShapes/btConvexHullShape.h>
#include <bullet/BulletCollision/CollisionShapes/btBvhTriangleMeshShape.h>
#include <bullet/BulletCollision/CollisionShapes/btTriangleMesh.h>
#include <bullet/BulletCollision/CollisionShapes/btConvexTriangleMeshShape.h>
#include <bullet/BulletCollision/CollisionShapes/btShapeHull.h>
#include <bullet/BulletCollision/Gimpact/btGImpactShape.h>
#include <bullet/BulletCollision/Gimpact/btGImpactCollisionAlgorithm.h>
//
#include "circle.hpp"
/***********************************************************************
			scene test class
************************************************************************/

//
/* class game_camera : public _camera_base { */
/* public: */
/* 	game_camera (void); */
/* 	~game_camera (void); */
/* 	void update (void) override; */
/* }; */
/* game_camera::game_camera (void) : _camera_base() {} */
/* game_camera::~game_camera (void) {std::cout<<"camera des\n";} */
/* void game_camera::update (void) { */
/* 	/1* _camera_base::translate( vec3( 0.0F, 0.0F, 3.0F ) ); *1/ */
/* } */
//

std::shared_ptr<game_scene> scene_out_test;
void init_scene ( void ) {
	scene_out_test = std::make_shared<game_scene>();
	scene_out_test->initilize_scene();
	scene_out_test->start();
	scene_out_test->load_scene();
}
/***********************************************************************
			scene test class
************************************************************************/

//Screen dimension constants
const int SCREEN_WIDTH = 1366;
const int SCREEN_HEIGHT = 768;
//The window we'll be rendering to
SDL_Window* gWindow = nullptr;
/* SDL_Surface* screen = NULL; */

//OpenGL context
SDL_GLContext gContext;

//Render flag
bool gRenderQuad = true;

//Graphics program
GLuint gProgramID = 0;
GLint gVertexPos2DLocation = -1;
GLuint gVBO = 0;
GLuint gIBO = 0;

//Renders quad to the screen
void close();


bool init () {
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	} else {
		//Use OpenGL 3.1 core
		SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 3 );
		SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 1 );
		SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );

		//Create window
		gWindow = SDL_CreateWindow( "Space : Fulcrum", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE );
		if( gWindow == NULL ) {
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		} else {
			//Create context
			gContext = SDL_GL_CreateContext( gWindow );
			if( gContext == NULL ) {
				printf( "OpenGL context could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			} else {
				//Initialize GLEW
				glewExperimental = GL_TRUE; 
				GLenum glewError = glewInit();
				if( glewError != GLEW_OK ) {
					printf( "Error initializing GLEW! %s\n", glewGetErrorString( glewError ) );
				}

				//Use Vsync
				if( SDL_GL_SetSwapInterval( 1 ) < 0 ) {
					printf( "Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError() );
				}
			}
		}
	}

	return success;
}

int main( int argc, char* args[] ) {
	//Start up SDL and create window
	if( !init() ) {
		printf( "Failed to initialize!\n" );
	} else {
		//Main loop flag
		bool quit = false;

		//Event handler
		SDL_Event e;
		
		//Enable text input
		SDL_StartTextInput();
		GLenum err = glewInit ();
		if(err != GLEW_OK) {
			std::cout<<glewGetErrorString (err)<<std::endl;
			exit (1);
		}
		init_scene();
		glViewport ( 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT );
		//While application is running
		int* x = new int( 0 );
		int* y = new int( 0 );
		int tempx = 0;
		float factor = 10.0F;
		while( !quit ) {
			//Handle events on queue
			while( SDL_PollEvent( &e ) != 0 ) {
				//User requests quit
				SDL_GetMouseState( x, y );
				/* std::cout<<"\nx = "<<*x<<" y = "<<*y; */

				SDL_ShowCursor( 0 );
				if( *x != (1366/2)) {
					if(e.type == SDL_MOUSEMOTION) {
						/* SDL_PixelFormat* fmt = screen->format; */
						/* If the mouse is moving to the left */
						if(e.motion.xrel < 0) {
							/* std::cout<<"go to left\n"<<e.motion.xrel; */
							int tx = 1366/2 - *x;
							/* std::cout<<"go to left\n"<<tx; */
							scene_out_test->get_controller()->message( MOTION_STATE::LEFT_ROTATION , (float)tx/factor );
							/* If the mouse is moving to the right */
						} else if(e.motion.xrel > 0) {
							/* std::cout<<"go to right\n"; */
							int tx = *x - 1366/2;
							scene_out_test->get_controller()->message( MOTION_STATE::RIGHT_ROTATION, (float)tx/factor );
							/* If the mouse is moving up */
						}
						if(e.motion.yrel < 0) {
							int tx = 768/2 - *y;
							scene_out_test->get_controller()->message( MOTION_STATE::DOWN_ROTATION, (float)tx/factor );
							/* If the mouse is moving down */
						} else if(e.motion.yrel > 0) {
							int tx = *y - 768/2;
							scene_out_test->get_controller()->message( MOTION_STATE::UP_ROTATION, (float)tx/factor );
							/* std::cout<<"go to down\n"; */
						}
					}
				} else {
					scene_out_test->get_controller()->message( MOTION_STATE::Y_TURN_STOP );
					scene_out_test->get_controller()->message( MOTION_STATE::X_TURN_STOP );
					/* std::cout<<"STOP ooo SToooOP!\n"; */
				}
				/* SDL_SetRelativeMouseMode(SDL_FALSE); */
				SDL_WarpMouseInWindow( gWindow, 1366/2, 768/2 );
				/* SDL_SetRelativeMouseMode(SDL_TRUE); */

				if( e.type == SDL_QUIT ) {
					quit = true;
				} else if( e.type == SDL_KEYDOWN ) {
					switch( e.key.keysym.sym ) {
						case SDLK_ESCAPE:
							quit = true;
							break;
						case SDLK_w:
							scene_out_test->get_controller()->message( MOTION_STATE::FORWORD );
							break;
						case SDLK_s:
							scene_out_test->get_controller()->message( MOTION_STATE::BACKWARD );
							break;
					}
					switch( e.key.keysym.sym ) {
						case SDLK_a:
							scene_out_test->get_controller()->message( MOTION_STATE::RIGHT_WARD );
							break;
						case SDLK_d:
							scene_out_test->get_controller()->message( MOTION_STATE::LEFT_WARD );
							break;
					}
					switch( e.key.keysym.sym ) {
						case SDLK_q:
							scene_out_test->get_controller()->message( MOTION_STATE::CLOCK_WISE_ROTATION );
							break;
						case SDLK_e:
							scene_out_test->get_controller()->message( MOTION_STATE::ANTI_CLOCK_WISE_ROTATION );
							break;
					}
					switch( e.key.keysym.sym ) {
						case SDLK_r:
							scene_out_test->get_controller()->message( MOTION_STATE::UP_WARD );
							break;
						case SDLK_f:
							scene_out_test->get_controller()->message( MOTION_STATE::DOWN_WARD );
							break;
					}
					switch( e.key.keysym.sym ) {
						case SDLK_SPACE:
							break;
					}
				} else if( e.type == SDL_KEYUP ) {
					switch( e.key.keysym.sym ) {
						case SDLK_w:
							scene_out_test->get_controller()->message( MOTION_STATE::Z_MOVE_STOP );
							break;
						case SDLK_s:
							scene_out_test->get_controller()->message( MOTION_STATE::Z_MOVE_STOP );
							break;
					}
					switch( e.key.keysym.sym ) {
						case SDLK_a:
							scene_out_test->get_controller()->message( MOTION_STATE::X_MOVE_STOP );
							break;
						case SDLK_d:
							scene_out_test->get_controller()->message( MOTION_STATE::X_MOVE_STOP );
							break;
					}
					switch( e.key.keysym.sym ) {
						case SDLK_q:
							scene_out_test->get_controller()->message( MOTION_STATE::Z_TURN_STOP );
							break;
						case SDLK_e:
							scene_out_test->get_controller()->message( MOTION_STATE::Z_TURN_STOP );
							break;
					}
					switch( e.key.keysym.sym ) {
						case SDLK_r:
							scene_out_test->get_controller()->message( MOTION_STATE::Y_MOVE_STOP );
							break;
						case SDLK_f:
							scene_out_test->get_controller()->message( MOTION_STATE::Y_MOVE_STOP );
							break;
					}
					switch( e.key.keysym.sym ) {
						case SDLK_SPACE:
							break;
					}
				}
			}
				scene_out_test->update_scene();
				scene_out_test->render_scene();

			//Render quad
			
			//Update screen
			SDL_GL_SwapWindow( gWindow );
		}
	delete x;
	x = nullptr;
	delete y;
	y = nullptr;
	}

	//Free resources and close SDL
	//Destroy window	
	SDL_DestroyWindow( gWindow );
	gWindow = nullptr;
	delete masset_manager;

	//Quit SDL subsystems
	SDL_Quit();

	return 0;
}

