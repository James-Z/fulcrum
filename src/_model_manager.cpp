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

void _model_manager::generate_vertex_data (void) {
	GLfloat size = 3.0F;
	GLfloat length = 1.0F * size;
	_data.clear();

	triangles temp_triangle;
	temp_triangle.x.x = 0.0F; temp_triangle.x.y = 1.0F; temp_triangle.x.z = 0.0F;
	temp_triangle.y.x = 0.0F; temp_triangle.y.y = 0.0F; temp_triangle.y.z = 0.0F;
	temp_triangle.z.x = 2.0F; temp_triangle.z.y = 0.0F; temp_triangle.z.z = 0.0F;
	_data.push_back( temp_triangle );

	/* temp_triangle.x.x = -length; temp_triangle.x.y = length; temp_triangle.x.z = 0.0F; */
	/* temp_triangle.y.x = -length; temp_triangle.y.y = -length; temp_triangle.y.z = 0.0F; */
	/* temp_triangle.z.x = length; temp_triangle.z.y = -length; temp_triangle.z.z = 0.0F; */
	/* _data.push_back( temp_triangle ); */


	_triangle_number = _data.size();
	_vertex_number = _triangle_number * 3;
	_float_number = _vertex_number * 3;
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

