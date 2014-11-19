#ifndef _CAMERAS_HPP_
#define _CAMERAS_HPP_

#include "_camera_base.hpp"

const int CAMERA_MAIN = 1;

class camera_main : public _camera_base {
public:
	camera_main (void);
	~camera_main (void);
};

#endif

