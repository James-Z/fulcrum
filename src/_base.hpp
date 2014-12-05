#ifndef __BASE_HPP_
#define __BASE_HPP_

#include <string>

class _base {
	bool _active;
	std::string _name;
public:
	_base (void) : _active(true) {}
	virtual ~_base (void) {}

	virtual void start (void) = 0;
	virtual void update (void) = 0;
	virtual void exit (void) = 0;
	virtual void resume (void) = 0;
	virtual void pause (void) = 0;
	virtual void destroy (void) = 0;

	inline void set_name ( const std::string& name ) { _name = name; }
	inline const std::string& get_name (void) { return _name; }
	inline void activate ( const bool force_activate ) { _active = force_activate; }
	inline const bool is_active (void) const { return _active; }
};

#endif

