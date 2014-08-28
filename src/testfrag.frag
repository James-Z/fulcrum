#version 330

smooth in vec3 vVaryingNormal;
smooth in vec3 vVaryingLightDir;
smooth in vec3 vVaryingCameraDir;

uniform vec4 diffuseColor;
uniform vec4 ambientColor;
uniform vec4 specularColor;
uniform vec4 lightColor;

out vec4 outputColor;

//out vec4 oStraightColor;
//out vec4 oGreyscale;
//out vec4 oLumAdjColor;

void main () {
	vec4 theColor;
	if( (dot(vVaryingNormal, vVaryingCameraDir) < 0.0 && dot(vVaryingNormal, vVaryingLightDir) < 0.0)
		|| (dot(vVaryingNormal, vVaryingCameraDir) > 0.0 && dot(vVaryingNormal, vVaryingLightDir) > 0.0)) {

		float tempDot= dot(normalize(vVaryingNormal), normalize(vVaryingLightDir));
		if(tempDot < 0.0) 
			tempDot = -tempDot;
		float diff= max(0.0, tempDot);
		theColor.rgb= diff * diffuseColor.rgb;
		theColor.a= diffuseColor.a;
	}
	theColor+= ambientColor;
	//vec3 vRecflection= normalize(reflect(-normalize(vVaryingLightDir), normalize(vVaryingNormal)));
	
	outputColor = theColor;

	//oStraightColor = theColor;

	//float grey = dot(theColor.rgb, vec3(0.3, 0.59, 0.11));
	//oGreyscale = vec4(grey, grey, grey, 1.0f);

	//oLumAdjColor= vec4(theColor - 0.4f);
	//oLumAdjColor.a= 1.0f;
}

