#version 410 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;

out vec2 outTexCoord;

uniform mat4 MVP;
uniform vec3 offset;

void main() {
    vec3 pos = position.xyz + offset;
    gl_Position = MVP * vec4(pos, 1.0f);
    outTexCoord = texCoord;
}