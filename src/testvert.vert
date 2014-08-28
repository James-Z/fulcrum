#version 330

in vec4 vertex;
in vec3 normal;
in vec2 texturecoord0;

uniform mat3 cameraPosMa;
uniform mat3 normalMa;
uniform mat3 lightPosMa;

uniform vec3 lightPosition;

smooth out vec3 vVaryingNormal;
smooth out vec3 vVaryingLightDir;
smooth out vec3 vVaryingCameraDir;

uniform mat4 tranMa;
uniform mat4 perspectiveMa;

void main()
{
	vec4 temVertex;
	temVertex.xyz= vertex.xyz;
	temVertex.w= 1.0;
	temVertex.xyz= temVertex.xyz* temVertex.w;
	vec4 temp= tranMa* temVertex;

	vec3 cameraPos = vec3(0.0, 0.0, -3.0);
	cameraPos = cameraPosMa * cameraPos;
	vVaryingNormal= normalMa* normal;
	vec3 temLightPos= lightPosMa* lightPosition;
	vec3 modelVertex= temp.xyz/ temp.w;
	vVaryingLightDir= normalize(temLightPos- modelVertex);
	vVaryingCameraDir = normalize(cameraPos - modelVertex);

	mat4 perspectiveMatrix= perspectiveMa;

	temp= perspectiveMatrix* temp;

	gl_Position= temp;
}

