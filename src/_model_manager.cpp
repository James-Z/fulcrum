#include "_model_manager.hpp"

_model_manager::_model_manager (void) : _data(), _float_number(0), _vertex_number(0), _triangle_number(0), _vbo(0), _vao(0) {
	/* _data = new GLfloat[18]; */
}


_model_manager::~_model_manager (void) {
	glDeleteBuffers(1, &_vbo);
	_data.clear();
	/* glDisableVertexAttribArray( ATTRIBUTE_INDEX_VERTEX ); */
	/* glDisableVertexAttribArray( ATTRIBUTE_INDEX_NORMAL ); */
}

void _model_manager::initialize_vbo (void) {
	glGenBuffers( 1, &_vbo );
	glBindBuffer( GL_ARRAY_BUFFER, _vbo );
	/* glBufferData( GL_ARRAY_BUFFER,  ( sizeof( float ) * _float_number * 2 ), glm::value_ptr( _data.begin()->x ), GL_STATIC_DRAW ); */
	glBufferData( GL_ARRAY_BUFFER,  ( sizeof( float ) * _float_number * 2 ), _data.data(), GL_STATIC_DRAW );
	glBindBuffer( GL_ARRAY_BUFFER, 0 );
}

void _model_manager::initialize_vao (void) {
	glGenVertexArrays( 1, &_vao );
	glBindVertexArray( _vao );

	glBindBuffer( GL_ARRAY_BUFFER, _vbo );

	glEnableVertexAttribArray( ATTRIBUTE_INDEX_VERTEX );
	glVertexAttribPointer( ATTRIBUTE_INDEX_VERTEX, 3, GL_FLOAT, GL_FALSE, 0, (void*)0 );

	glEnableVertexAttribArray( ATTRIBUTE_INDEX_NORMAL );
	glVertexAttribPointer( ATTRIBUTE_INDEX_NORMAL, 3, GL_FLOAT, GL_FALSE, 0, (void*)( sizeof( float ) * _float_number ) );

	glBindVertexArray(0);
}

void _model_manager::draw (void) {
	glBindVertexArray( _vao );
	glDrawArrays( GL_TRIANGLES, 0, _vertex_number );
	glBindVertexArray(0);
}

void _model_manager::edit_modedl (void) {
}

void _model_manager::generate_vertex_data (void) {

	_data.clear();
	cube a; a.generate_cube( glm::vec3( -0.5F, 0.5F, 0.5F ), 1.0F );
	/* _data = a.get_data(); */
	a.generate_another_cube( CUBE_SIDE::RIGHT );
	a.move_to( CUBE_SIDE::LEFT );
	a.generate_another_cube( CUBE_SIDE::LEFT );
	a.move_to( CUBE_SIDE::RIGHT );
	a.generate_another_cube( CUBE_SIDE::BACK );
	_data = a.get_data();

	if( !_data.empty() ) {
		_triangle_number = _data.size();
		_vertex_number = _triangle_number * 3;
		_float_number = _vertex_number * 3;
	} else {
		std::cerr<<"no model data generate!\n";
	}
}

void _model_manager::generate_normal_data (void) {
	if( !_data.empty() ) {
		triangles temp_triangle;
		auto iter = _data.begin();
		for( int i = 0; i < _triangle_number; ++i, ++iter) {
			glm::vec3 const & a = iter->x;
			glm::vec3 const & b = iter->y;
			glm::vec3 const & c = iter->z;
			temp_triangle.x = temp_triangle.y = temp_triangle.z = glm::normalize( glm::cross( c - a, b - a ) );
			_data.push_back( temp_triangle );
		}
	} else {
		std::cerr<<"normal can't be generated,there is no data in this model!"<<std::endl;
	}
}

