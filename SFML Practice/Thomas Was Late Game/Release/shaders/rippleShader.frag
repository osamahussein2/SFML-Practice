// attributes from vertShader.vert

// The first type we can see is varying. These are variables which are in scope between both shaders.
varying vec4 vColor;
varying vec2 vTexCoord;

// uniforms
uniform sampler2D uTexture;
uniform float uTime;

void main() {
	float coef = sin(gl_FragCoord.y * 0.1 + 1 * uTime);
	//vTexCoord.y += coef * 0.03;

	gl_FragColor = vColor * texture2D(uTexture, vec2(vTexCoord.x, vTexCoord.y + coef * 0.03));
}
