#include "fulcrum.hpp"

#include "_scene_base.hpp"
#include "_object_base.hpp"
#include "_shader_manager.hpp"
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xatom.h>
#include <X11/cursorfont.h>

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/file.h>
#include <unistd.h>
#include <errno.h>
/***********************************************************************
			scene test class
************************************************************************/
const unsigned int shader_one = 1;
class game_object : public _object_base {
public:
	game_object (void);
	~game_object (void);
};
game_object::game_object (void) : _object_base() {}
game_object::~game_object (void) {}
game_object* object_out_test;
unsigned int shader_out_test;
void init_object (void) {
	object_out_test = new game_object();
	object_out_test->generate_model();
	object_out_test->set_position_in_world( vec3( 0.0F, 0.0F, -20.0F ) );
}
//
class game_camera : public _camera_base {
public:
	game_camera (void);
	~game_camera (void);
	void update (void) override;
};
game_camera::game_camera (void) : _camera_base() {}
game_camera::~game_camera (void) {}
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
	//
	string shader_file_name = "ver.sdr fag.sdr";
	const unsigned int game_shader = 1;
	shader_load( shader_file_name, game_shader );
	//
	set_ambient_color( glm::vec4(0.058F, 0.082F, 0.07F, 1.0F) );
	//
	_light_base* light_one = new _light_base();
	light_one->set_diffuse_color( glm::vec3(0.0F, 1.0F, 0.0F) );
	/* light_one->set_diffuse_color( glm::vec3(0.36F, 0.05F, 0.67F) ); */
	light_one->set_specular_color( glm::vec3(0.9F, 0.9F, 0.9F) );
	light_one->set_position_in_world( glm::vec3( 0.0F, 0.0F, 0.0F) );
	/* light_one->rotate( 8.0F, vec3( 0.0F, 1.0F, 0.0F ) ); */
	light_one->translate( vec3(0.0F, 0.0F, -400.0F) );
	add_light( light_one );

	_light_base* light_two = new _light_base();
	light_two->set_diffuse_color( glm::vec3(0.F, 0.F, 1.F) );
	light_two->set_specular_color( glm::vec3(0.9F, 0.9F, 0.9F) );
	light_two->set_position_in_world( glm::vec3( 0.0F, 0.0F, 0.0F) );
	/* light_two->rotate( 8.0F, vec3( 0.0F, 1.0F, 0.0F ) ); */
	light_two->translate( vec3(0.0F, 6.0F, 400.0F) );
	add_light( light_two );
	/* std::cout<<"dot: "<<glm::dot( glm::vec3(0.0F, 0.0F, -4.0), glm::vec3(0.0F, 0.0F, -1.0) )<<std::endl; */
	//
	game_camera* camera_one = new game_camera();
	camera_one->set_ID( 301 );
	camera_one->perspective( 45.0F,1.0F, 1.0F, 1000.0F );
	camera_one->set_position_in_world( vec3( 0.0F, 0.0F, 0.0F ) );
	camera_one->rotate( 0.0F, vec3( 0.0F, 1.0F, 0.0F ) );
	camera_one->_camera_base::translate( vec3( 0.0F, 2.F, 5.0F ) );
	camera_one->_camera_base::translate( vec3( 0.0F, 2.F, 5.0F ) );
	camera_one->_camera_base::rotate( -10.0F, vec3( 1.0F, 0.F, 0.0F ) );
	add_camera( camera_one );
	//
	for(int i = 0; i < 5; ++i) {
		game_object* object_one = new game_object();
		object_one->generate_model();
		object_one->set_position_in_world( glm::vec3( 0.0F, 0.0F, 0.0F ) );
		object_one->translate( vec3( 0.0F, 0.0F, 7.0F * i ) );
		btCollisionShape* shape = new btSphereShape( 1.0F );
		object_one->init_rigid_body( (btScalar(i)+1.0F), btVector3( 0.6F, 0.6F, 0.6F ), shape );
		object_one->get_rigidbody()->setDamping( i * 0.05F, i * 0.01F );
		object_one->get_rigidbody()->setAngularFactor( btVector3(2.0F, 2.0F, 2.0F) );
		object_one->get_rigidbody()->setLinearFactor( btVector3(1.0F, 1.0 ,1.0) );
		/* object_one->rotate( 180.0F, vec3( 0.0F, 1.0F, 0.0F ) ); */
		/* object_one->rotate( 180.0F, vec3( 0.0F, 1.0F, 0.0F ) ); */
		add_object( object_one, game_shader );
	}
	for(float i = 0; i < 5.0F; ++i) {
		game_object* object_one = new game_object();
		object_one->generate_model();
		object_one->set_position_in_world( glm::vec3( 0.0F, 0.0F, 0.0F ) );
		object_one->translate( vec3( 10.0F, 0.0F, 7.0F * i ) );
		btCollisionShape* shape = new btSphereShape( 1.0F );
		object_one->init_rigid_body( btScalar(i), btVector3( 0.6F, 0.6F, 0.6F ), shape );
		object_one->get_rigidbody()->setDamping( i * 0.05F, i * 0.01F );
		object_one->get_rigidbody()->setAngularFactor( btVector3(2.0F, 2.0F, 2.0F) );
		object_one->get_rigidbody()->setLinearFactor( btVector3(1.0F, 1.0 ,1.0) );
		/* object_one->rotate( 180.0F, vec3( 0.0F, 1.0F, 0.0F ) ); */
		add_object( object_one, game_shader );
	}

	game_object* object_two = new game_object();
	object_two->generate_model();
	object_two->catch_contrtoller();
	object_two->set_position_in_world( glm::vec3( 0.0F, .0F, 0.0F ) );
	object_two->rotate( 180.0F, vec3( 0.0F, 1.0F, 0.0F ) );
	/* object_two->rotate( 180.0F, vec3( 0.0F, 0.0F, 1.0F ) ); */
	object_two->catch_camera( camera_one->get_ID() );
	/* object_two->translate( vec3( 0.0F, 1.0F, -0.0F ) ); */
	/* object_two->realse_camera(); */
	btCollisionShape* shape = new btSphereShape( 1.0F );
	object_two->init_rigid_body( 1.0F, btVector3( 0.6F, 0.6F, 0.6F ), shape );
	object_two->get_rigidbody()->setMassProps( 1, btVector3(0.918, 0.918, 0.918) );
	object_two->get_rigidbody()->setDamping( 0.192F, 0.392F );
	object_two->get_rigidbody()->setAngularFactor( btVector3(2.0F, 2.0F, 2.0F) );
	object_two->get_rigidbody()->setLinearFactor( btVector3(1.0F, 1.0 ,1.0) );
	add_object ( object_two, game_shader );

}
game_scene* scene_out_test;
/* _camera_base* camera_out_test; */
void init_scene ( void ) {
	scene_out_test = new game_scene();
	scene_out_test->initilize_scene();
	scene_out_test->edit_scene();
	scene_out_test->load_scene();
	//
	/* camera_out_test =  new _camera_base(); */
	/* camera_out_test->_object_base::set_position_in_world( glm::vec3( 0.0F, 0.0F, -30.0F ) ); */

	/* float diffuseColor[] = {0.36, 0.05, 0.67, 1.0}; */
	/* float ambientColor[] = {0.058, 0.082, 0.070, 1.0}; */
	/* float specularColor[] = {0.9, 0.9, 0.9, 1.0}; */
	/* float lightPosition[] = {0.0, 0.0, -100.0}; */

	/* glUseProgram(scene_out_test->get_test_shader()->get_shader()); */
	/* glUniform3fv( scene_out_test->get_test_shader()->light_position_in_world, 1, lightPosition); */
	/* glUniform4fv( scene_out_test->get_test_shader()->ambient_color, 1, ambientColor); */
	/* glUniform4fv( scene_out_test->get_test_shader()->specular_color, 1, specularColor); */
	/* glUniform4fv( scene_out_test->get_test_shader()->diffuse_color, 1, diffuseColor); */

	/* glUseProgram(0); */
}
void drawObject ( void ) {
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	glUseProgram( scene_out_test->get_test_shader()->get_shader() );

	glUniformMatrix4fv( scene_out_test->get_test_shader()->object_transforms, 1, GL_FALSE, glm::value_ptr( object_out_test->get_matrix_in_world() ) );
	/* glUniformMatrix4fv( scene_out_test->get_test_shader()->object_transforms, 1, GL_FALSE, glm::value_ptr( object_out_test->get_matrix_in_world() ) ); */
	glUniformMatrix3fv( scene_out_test->get_test_shader()->normal_transforms, 1, GL_FALSE, glm::value_ptr( glm::mat3( object_out_test->get_matrix_in_world() ) ) );
	object_out_test->draw();
	//shadertest
	glUseProgram( 0 );
}
/***********************************************************************
			scene test class
************************************************************************/


Display                 *dpy;
Window                  root;
GLint                   att[] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None };
XVisualInfo             *vi;
Colormap                cmap;
XSetWindowAttributes    swa;
Window                  win;
GLXContext              glc;
XWindowAttributes       gwa;
XEvent                  xev;
KeySym key;             /* a dealie-bob to handle KeyPress Events */
char text[255];         /* a char buffer for KeyPress Events */

void initprog () {
	std::string shaderSourceNames ("testvert.vert testfrag.frag");
	shadertest = shaderManage.CreateShader(shaderSourceNames);
	std::string uniforNames ("tranMa perspectiveMa normalMa diffuseColor ambientColor specularColor lightPosition lightColor diffMaterial lightPosMa cameraPosMa");
	shaderManage.GetUniformLocation (uniforNames);

	tranUnif = shaderManage.UniformName ("tranMa");
	persUnif = shaderManage.UniformName ("perspectiveMa");
	norMaUnif = shaderManage.UniformName ("normalMa");
	diffColorUnif = shaderManage.UniformName ("diffuseColor");
	ambientColorUnif = shaderManage.UniformName ("ambientColor");
	specularColorUnif = shaderManage.UniformName ("specularColor");
	lightPosUnif = shaderManage.UniformName ("lightPosition");
	diffMaterialUnif = shaderManage.UniformName ("diffMaterial");
	lightColorUnif = shaderManage.UniformName ("lightColor");
	lightPosMaUnif = shaderManage.UniformName ("lightPosMa");
	cameraPosMaUnif = shaderManage.UniformName ("cameraPosMa");

	float diffuseColor[] = {0.36, 0.05, 0.67, 1.0};
	float ambientColor[] = {0.058, 0.082, 0.070, 1.0};
	float specularColor[] = {0.9, 0.9, 0.9, 1.0};
	float lightPosition[] = {0.0, 0.0, 100.0};

	glUseProgram(shadertest);
	glUniform3fv(lightPosUnif, 1, lightPosition);
	glUniform4fv(ambientColorUnif, 1, ambientColor);
	glUniform4fv(specularColorUnif, 1, specularColor);
	glUniform4fv(diffColorUnif, 1, diffuseColor);

	trantest.Perspective(45.0, 1.0, 1.0, 100.0);
	glUniformMatrix4fv(persUnif, 1, GL_FALSE, trantest.GetPerspectiveMatrix());
	glUseProgram(0);
}

void initmodel () {
	triangle[0] = triangle[1] = triangle[2] = triangle[4] = triangle[5] = triangle[6] = triangle[8] = 0.0f;
	triangle[3] = triangle[7] = 2.0f;
	triangle[9] = triangle[10] = triangle[12] = triangle[13] = triangle[15] = triangle[16] = 0.0f;
	triangle[11] = triangle[14] = triangle[17] = -1.0f;

	glGenBuffers(1, &modelbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, modelbuffer);
	glBufferData(GL_ARRAY_BUFFER, (sizeof(float) * 3 * 3 * 2), triangle, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenVertexArrays(1, &vao); 
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, modelbuffer);

		glEnableVertexAttribArray(ATTRIBUTE_INDEX_VERTEX);
		glVertexAttribPointer(ATTRIBUTE_INDEX_VERTEX, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
		glEnableVertexAttribArray(ATTRIBUTE_INDEX_NORMAL);
		glVertexAttribPointer(ATTRIBUTE_INDEX_NORMAL, 3, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(float) * 9));

	glBindVertexArray(0);
}

void drawtriangle () {
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindVertexArray(0);
	glDisableVertexAttribArray(ATTRIBUTE_INDEX_VERTEX);
	glDisableVertexAttribArray(ATTRIBUTE_INDEX_NORMAL);
}

void InitOGL () {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glEnable (GL_DEPTH_TEST);
	glDepthRange(0.0f, 1.0f);
	glFrontFace(GL_CCW);
	//cull face 
	//glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glViewport (0, 0, gwa.width, gwa.height);
	initprog ();
	initmodel ();
}

float rotation = 0.0F;

void DrawAQuad () {
	init_object();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(shadertest);
	
	trantest.PushMatrix ();
	glUniformMatrix4fv(cameraPosMaUnif, 1, GL_FALSE, trantest.GetCurrentMatrix());
	trantest.Camera ();
	trantest.ApplyCameraTransform(offsetx, offsety, offsetz);
	glUniformMatrix3fv(lightPosMaUnif, 1, GL_FALSE, trantest.GetNormalMatrix());
	
	trantest.PushMatrix();
	trantest.Rotate(ration, 0.0f, 1.0f, 0.0f);
	glUniformMatrix4fv(tranUnif, 1, GL_FALSE, trantest.GetCurrentMatrix());
	glUniformMatrix3fv(norMaUnif, 1, GL_FALSE, trantest.GetNormalMatrix());
	trantest.Translate(0.0F, 0.0F, 30.0F);
	glUniformMatrix4fv(tranUnif, 1, GL_FALSE, glm::value_ptr( object_out_test->get_matrix_in_world() ) );
	glUniformMatrix3fv(norMaUnif, 1, GL_FALSE, glm::value_ptr( glm::mat3( object_out_test->get_matrix_in_world() ) ) );
	object_out_test->draw();
		/* trantest.PushMatrix(); */
		/* 	trantest.Rotate(rotation, 0.0f, 1.0f, 0.0f); */
		/* 	trantest.Rotate(rotation, 0.0f, 0.0f, 1.0f); */
		/* 	glUniformMatrix4fv(tranUnif, 1, GL_FALSE, trantest.GetCurrentMatrix()); */
		/* 	glUniformMatrix3fv(norMaUnif, 1, GL_FALSE, trantest.GetNormalMatrix()); */
		/* 	drawtriangle(); */
		/* trantest.PopMatrix(); */
	trantest.PopMatrix();

	trantest.PopMatrix();
	//shadertest
	glUseProgram(0);
}

int main ( int argc, char *argv[] ) {
	dpy = XOpenDisplay (NULL);

	if(dpy == NULL) {
		printf("\n\tcannot connect to X server\n\n");
		exit (0);
	}
	
	root = DefaultRootWindow (dpy);
	vi = glXChooseVisual (dpy, 0, att);
	if(vi == NULL) {
		printf ("\n\tno appropriate visual found\n\n");
		exit (0);
	}
	else {
		printf ("\n\tvisual %p selected\n", (void *)vi->visualid); /* %p creates hexadecimal output like in glxinfo */
	}
	
	cmap = XCreateColormap (dpy, root, vi->visual, AllocNone);
	
	swa.colormap = cmap;
	swa.event_mask = ExposureMask | KeyPressMask;

	win = XCreateWindow (dpy, root, 0, 0, 600, 600, 0, vi->depth, InputOutput, vi->visual, CWColormap | CWEventMask, &swa);
	
	XMapWindow (dpy, win);
	XStoreName (dpy, win, "FULCRUM");
	
	glc = glXCreateContext (dpy, vi, NULL, GL_TRUE);
	glXMakeCurrent (dpy, win, glc);

	GLenum err = glewInit ();
        if(err != GLEW_OK) {
		cout<<glewGetErrorString (err)<<endl;
		exit (1);
        }

	//Init OpenGL Program
	XGetWindowAttributes (dpy, win, &gwa);

	init_scene();
	/* InitOGL(); */
	/* init_object(); */
	glViewport (0, 0, gwa.width, gwa.height);

	while(1) {
		++rotation;
		if( XPending( dpy ) ) {
			//
			XNextEvent (dpy, &xev);
			XSelectInput(dpy, win, KeyPressMask | KeyReleaseMask);
			//
			switch(xev.type) {
				case Expose:
				{
					glViewport (0, 0, gwa.width, gwa.height);
					scene_out_test->update_scene();
					scene_out_test->render_scene();
					glXSwapBuffers (dpy, win);
					break;
				}
				case KeyPress:
				{
					/* std::cout<<"key press\n"; */
					XKeyEvent *ke;
					int ks(0);

					ke=&xev.xkey;
					ks=XLookupKeysym(ke,(ke->state&ShiftMask)?1:0);

					switch( ks ) {
						case XK_Escape:
							glXMakeCurrent(dpy, None, NULL);
							glXDestroyContext(dpy, glc);
							XDestroyWindow(dpy, win);
							XCloseDisplay(dpy);
							exit(0);
						case XK_w:
							scene_out_test->_controller_in_scene->move_object( MOTION_STATE::FORWORD );
							break;
						case XK_s:
							scene_out_test->_controller_in_scene->move_object( BACKWARD );
							break;
						default:
							break;
					}
					switch( ks ) {
						case XK_Escape:
							glXMakeCurrent(dpy, None, NULL);
							glXDestroyContext(dpy, glc);
							XDestroyWindow(dpy, win);
							XCloseDisplay(dpy);
							exit(0);
						case XK_a:
							scene_out_test->_controller_in_scene->move_object( CLOCK_WISE_ROTATION );
							break;
						case XK_d:
							scene_out_test->_controller_in_scene->move_object( MOTION_STATE::ANTI_CLOCK_WISE_ROTATION );
							break;
						default:
							break;
					}
					break;	//KeyPress break
				}
				case KeyRelease:
				{
					/* std::cout<<"key release\n"; */
					XKeyEvent *ke;

					ke=&xev.xkey;
					int ks=XLookupKeysym(ke,(ke->state&ShiftMask)?1:0);

					switch(ks) {
						case XK_Escape:
							glXMakeCurrent(dpy, None, NULL);
							glXDestroyContext(dpy, glc);
							XDestroyWindow(dpy, win);
							XCloseDisplay(dpy);
							exit(0);
						case XK_a:
							scene_out_test->_controller_in_scene->move_object( MOTION_STATE::TURN_STOP );
							break;
						case XK_d:
							scene_out_test->_controller_in_scene->move_object( MOTION_STATE::TURN_STOP  );
							break;
						case XK_w:
							scene_out_test->_controller_in_scene->move_object( MOTION_STATE::MOVE_STOP );
							break;
						case XK_s:
							scene_out_test->_controller_in_scene->move_object( MOTION_STATE::MOVE_STOP );
							break;
						default:
							break;

					}
					break;
				}
			}	//switch end key state end
			scene_out_test->update_scene();
			scene_out_test->render_scene();
			glXSwapBuffers(dpy, win);
		} else {	//if end
			scene_out_test->update_scene();
			scene_out_test->render_scene();
			glXSwapBuffers(dpy, win);
		}
	} /* this closes while(1) { */
} /* this is the } which closes int main(int argc, char *argv[]) { */
