#version 330 core

in vec2 TexCoord;

out vec4 color;

uniform float offsetx;

uniform sampler2D texture1;

void main(){
    
	vec4 tex1 = texture( 
		texture1, vec2(TexCoord.x + offsetx, TexCoord.y));
	if( tex1.a < 0.5) {
		discard;
	}
	color = tex1;
}