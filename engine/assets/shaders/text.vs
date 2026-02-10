#version 330 core
layout (location = 0) in vec2 pos;
layout (location = 1) in vec2 tex_pos;

out vec2 TexCoords;

uniform mat4 MVP;

void main(){
    gl_Position = MVP*vec4(pos, 0.0, 1.0);
    TexCoords = tex_pos;
}
