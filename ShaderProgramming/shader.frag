#version 430

// Global variables for lighting calculations
layout(location = 1) uniform vec3 viewPos;
layout(location = 2) uniform sampler2D texToon;
layout(location = 3) uniform float time;

// Output for on-screen color
layout(location = 0) out vec4 outColor;

// Interpolated output data from vertex shader
in vec3 fragPos; // World-space position
in vec3 fragNormal; // World-space normal

void toonShadeNoTex(float testColor) {
	// Toon shading (no texture)
	if(testColor > 0.875) {
		outColor = vec4(vec3(1,1,1), 1.0);
	} else if (testColor > 0.625) {
		outColor = vec4(vec3(0.75,0.75,0.75), 1.0);
	} else if (testColor > 0.375) {
		outColor = vec4(vec3(0.5,0.5,0.5), 1.0);
	} else if (testColor > 0.125) {
		outColor = vec4(vec3(0.25,0.25,0.25), 1.0);
	} else {
		outColor = vec4(vec3(0,0,0), 1.0);
	}
}

void toonShadeWithTex(float testColor) {
	// Toon shading (with texture)
	if(testColor > 0.5) {
		outColor = texture(texToon, vec2(1.0, 0.0));
	} else if(testColor > 0.3) {
		outColor = texture(texToon, vec2(0.5, 0.0));
	} else {
		outColor = texture(texToon, vec2(0.0, 0.0));
	}
}

void texShade(float testColor) {
	outColor = texture(texToon, vec2(testColor, testColor));
}

void blinnPhongShade(float testColor) {
	// Blinn-Phong shading
	outColor = vec4(vec3(1,1,1)*testColor, 1.0);
}

void main() {
    // Output the normal as color
	vec3 lightPos = vec3(-2, 1, cos(time));
	vec3 lightDir = lightPos - fragPos;
	vec3 H = lightDir + viewPos;
	float divider = H.length();
	H = H/divider;
	float f = dot(H, fragNormal);
	float testColor = pow(f, 16);

	//texShade(testColor);
	toonShadeWithTex(testColor);

    //outColor = vec4(abs(fragNormal), 1.0);
}