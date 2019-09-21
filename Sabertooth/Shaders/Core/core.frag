#version 330 core

in vec2 TexCoord;

out vec4 color;

uniform float offsetx;

uniform float id;

uniform sampler2D texture0;

uniform sampler2D texture1;

uniform sampler2D texture2;

void main(){
    vec4 tex1;
	if (id==0){
		tex1 = texture(texture0, vec2(TexCoord.x + offsetx, TexCoord.y));
	}else{
		if(id==1)
			tex1 = texture(texture1, vec2(TexCoord.x + offsetx, TexCoord.y));
		else
			tex1 = texture(texture2, vec2(TexCoord.x + offsetx, TexCoord.y));
	}
	if( tex1.a < 0.5) {
		discard;
	}
	color = tex1;
}