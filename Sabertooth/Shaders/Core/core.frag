#version 330 core

in vec2 TexCoord;

out vec4 color;

uniform float offsetx;

uniform float offsety;

uniform float id;

uniform sampler2D texture0;


void main(){
    vec4 tex1 = texture(texture0, vec2(TexCoord.x + offsetx, TexCoord.y + offsety));
	if( tex1.a < 0.5) {
		discard;
	}
	color = tex1;
}