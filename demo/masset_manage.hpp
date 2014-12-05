#ifndef _MASSET_MANAGE_HPP_
#define _MASSET_MANAGE_HPP_

#include "_asset_manager.hpp"
#include <memory>

class masset_manage : public _asset_manager {
public:
	masset_manage ( void ) : _asset_manager() {
		read_file( "lowpolyspaceship1.dae", FILE_FORMAT::DAE );
		read_file( "circle.dae", FILE_FORMAT::DAE );
		read_file( "one.dae", FILE_FORMAT::DAE );
		read_file( "stone_a.dae", FILE_FORMAT::DAE );
		read_file( "stone_a_l.dae", FILE_FORMAT::DAE );
	}
	~masset_manage ( void ) { }
};

static masset_manage* masset_manager = new masset_manage();

#endif

