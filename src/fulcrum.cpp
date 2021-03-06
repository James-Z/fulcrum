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
class game_object : public _object_base {
	std::shared_ptr<btTriangleMesh> triangle_mesh;
	std::shared_ptr<btGImpactMeshShape> tmpshape;
public:
	game_object (void);
	~game_object (void);
};
game_object::game_object (void) : _object_base() {
	load_model_data_from_assets( masset_manager->get_model_data( "lowpolyspaceship.dae" ) );
	set_position_in_world( glm::vec3( 0.0F, .0F, 0.0F ) );
	/* catch_camera( camera_one->get_ID() ); */
	set_material_diffuse_color( glm::vec4( 0.6, 0.6, 0.6, 1.0 ) );
	set_material_specular_color( glm::vec4( 0.6, 0.6, 0.6, 1.0 ) );
	/* realse_camera(); */
	////////////////////
	/* tmpshape1 = std::make_shared<btConvexHullShape>(); */
	/* int it = 0; */
	/* for ( auto i = get_model_data().begin(); it < get_model_data().size()/2; ++it,++i ) { */
	/* 	tmpshape1 ->addPoint( btVector3(i->x.x, i->x.y, i->x.z) ); */
	/* 	tmpshape1->addPoint( btVector3(i->y.x, i->y.y, i->y.z) ); */
	/* 	tmpshape1->addPoint( btVector3(i->z.x, i->z.y, i->z.z) ); */

	/* } */
	/* // */
	/* tmpshape->setLocalScaling( btVector3(0.95, 0.95, 0.95) ); */

	/* triangle_mesh = std::make_shared<btTriangleMesh>(); */
	triangle_mesh = std::make_shared<btTriangleMesh>();
	auto i = get_model_data().begin();
	for ( int it = 0; it < get_model_data().size()/2; ++i, ++it ) {
		triangle_mesh->addTriangle(	btVector3(i->x.x, i->x.y, i->x.z),
				btVector3(i->y.x, i->y.y, i->y.z),
				btVector3(i->z.x, i->z.y, i->z.z) );
	}
	btVector3 aabbMin(-1000,-1000,-1000),aabbMax(1000,1000,1000);
	tmpshape = std::make_shared<btGImpactMeshShape>( triangle_mesh.get() );//, true, aabbMin, aabbMax );
	/* tmpshape = new btGImpactMeshShape( triangle_mesh );//, true, aabbMin, aabbMax ); */
	tmpshape->updateBound();

	//
	/* init_rigid_body( 1.0F, btVector3( 0.6F, 0.6F, 0.6F ), tmpshape.get() ); */
	init_rigid_body( 1.0F, btVector3( 0.6F, 0.6F, 0.6F ), tmpshape );
	get_rigidbody()->setMassProps( 1, btVector3(0.918, 0.918, 0.918) );
	get_rigidbody()->setDamping( 0.618F, 0.618F );
	get_rigidbody()->setAngularFactor( btVector3(1.0F, 1.0F, 1.0F) );
	get_rigidbody()->setLinearFactor( btVector3(1.0F, 1.0 ,1.0) );
	std::cout<<"game is gen\n";
}
game_object::~game_object (void) {}
//
class game_camera : public _camera_base {
public:
	game_camera (void);
	~game_camera (void);
	void update (void) override;
};
game_camera::game_camera (void) : _camera_base() {}
game_camera::~game_camera (void) {std::cout<<"camera des\n";}
void game_camera::update (void) {
	/* _camera_base::translate( vec3( 0.0F, 0.0F, 3.0F ) ); */
}
//
class game_scene : public _scene_base {
public:
	game_scene (void);
	~game_scene (void);
	void edit_scene (void) override;
};
game_scene::game_scene (void) : _scene_base() {}
game_scene::~game_scene (void) {}

void game_scene::edit_scene (void) {
	get_physics_world()->setGravity( btVector3(0.0F, 0.0F, 0.0F) );
	//
	std::string shader_file_name = "ver.sdr fag.sdr";
	const unsigned int game_shader = 1;
	shader_load( shader_file_name, game_shader );
	//
	set_ambient_color( glm::vec4(0.3F, 0.3F, 0.3F, 1.0F) );
	//
	_light_base* light_one = new _light_base();
	light_one->set_diffuse_color( glm::vec3(1.0F, 1.0F, 1.0F) );
	/* light_one->set_diffuse_color( glm::vec3(0.36F, 0.05F, 0.67F) ); */
	light_one->set_specular_color( glm::vec3(0.9F, 0.9F, 0.9F) );
	light_one->set_position_in_world( glm::vec3( 0.0F, 0.0F, 0.0F) );
	/* light_one->rotate( 8.0F, vec3( 0.0F, 1.0F, 0.0F ) ); */
	light_one->translate( glm::vec3(400.0F, -100.0F, 400.0F) );
	add_light( light_one );

	/* _light_base* light_two = new _light_base(); */
	/* light_two->set_diffuse_color( glm::vec3(0.F, 0.F, 1.F) ); */
	/* light_two->set_specular_color( glm::vec3(0.9F, 0.9F, 0.9F) ); */
	/* light_two->set_position_in_world( glm::vec3( 0.0F, 0.0F, 0.0F) ); */
	/* /1* light_two->rotate( 8.0F, vec3( 0.0F, 1.0F, 0.0F ) ); *1/ */
	/* light_two->translate( glm::vec3(-400.0F, 200.0F, 400.0F) ); */
	/* add_light( light_two ); */
	/* std::cout<<"dot: "<<glm::dot( glm::vec3(0.0F, 0.0F, -4.0), glm::vec3(0.0F, 0.0F, -1.0) )<<std::endl; */
	//
	game_camera* camera_one = new game_camera();
	camera_one->set_ID( 11 );
	camera_one->perspective( 45.0F, 1366.0F / 768.0F, 1.0F, 1000.0F );
	camera_one->set_position_in_world( glm::vec3( 0.0F, 0.0F, 0.0F ) );
	camera_one->rotate( 0.0F, glm::vec3( 0.0F, 1.0F, 0.0F ) );
	camera_one->_camera_base::translate( glm::vec3( 0.0F, 3.F, 8.0F ) );
	camera_one->_camera_base::rotate( -10.0F, glm::vec3( 1.0F, 0.F, 0.0F ) );
	add_camera( camera_one );

	//
	btCollisionDispatcher* dispatcher = static_cast<btCollisionDispatcher*>( this->get_physics_world()->getDispatcher() );
	btGImpactCollisionAlgorithm::registerAlgorithm( dispatcher );
	//
	{
		game_object* object_one = new game_object();
		/* object_one->generate_model(); */
		/* object_one->load_model_data_from_assets( asset->get_model_data( "lowpolyspaceship.dae" ) ); */
		object_one->set_position_in_world( glm::vec3( 0.0F, 0.0F, 0.0F ) );
		object_one->translate( glm::vec3( .0F, 0.0F, -50.5F ) );
		object_one->set_material_diffuse_color( glm::vec4( 0.0, 0.6, 0.6, 1.0 ) );
		object_one->set_material_specular_color( glm::vec4( 0.0, 0.6, 0.6, 1.0 ) );

		
		/* //////////////////// */
		/* object_one->init_rigid_body( 1.0F, btVector3( 0.6F, 0.6F, 0.6F ), tmpshape ); */
		object_one->get_rigidbody()->setDamping( 0.05F, 0.01F );
		object_one->get_rigidbody()->setAngularFactor( btVector3(0.0F, 0.0F, 0.0F) );
		object_one->get_rigidbody()->setLinearFactor( btVector3(0.0F, 0.0 ,0.0) );
		/* add_object( object_one, game_shader ); */
	}

	{
		circle* circle_o = new circle();
		circle_o->catch_contrtoller();
		circle_o->catch_camera( camera_one->get_ID() );
		/* add_object( circle_o, game_shader ); */
	}

}

std::shared_ptr<game_scene> scene_out_test;
void init_scene ( void ) {
	scene_out_test = std::make_shared<game_scene>();
	scene_out_test->initilize_scene();
	scene_out_test->edit_scene();
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

