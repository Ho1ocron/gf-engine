#version 330 core
in vec2 TexCoords;
out vec4 Color;

uniform sampler2D font;
uniform vec3 textColor;

void main(){
    Color = vec4(textColor, 1.0) * texture(font, TexCoords).r;
}
