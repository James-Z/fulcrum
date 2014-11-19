#ifndef __BASE_HPP_
#define __BASE_HPP_

class _base {
public:
	_base (void) {}
	virtual ~_base (void) {}

	virtual void start (void) = 0;
	virtual void update (void) = 0;
	virtual void exit (void) = 0;
	virtual void resume (void) = 0;
	virtual void pause (void) = 0;
	virtual void destroy (void) = 0;
};

#endif

