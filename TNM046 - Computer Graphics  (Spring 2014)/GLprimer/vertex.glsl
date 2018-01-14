
#version 330 core

layout(location = 0) in vec3 Position;
layout(location = 1) in vec3 Normal;
layout(location = 2) in vec2 TexCoord;

out vec3 interpolatedNormal;
out vec2 st;
out vec3 L;
out vec3 interpolatedColor;

uniform float time;
uniform mat4 Tcomp;
uniform mat4 Tlight;

uniform mat4 MV;
uniform mat4 P;

void main(){

    //vec3 transformedNormal = mat3(Tcomp) * Normal;
    //interpolatedNormal = normalize(transformedNormal);  //Pass interpolated normals to fragment shader
    interpolatedNormal = normalize((mat3(MV) * Normal));

    st = TexCoord; //Will also be interpolated across the triangle

    vec3 light = mat3(Tlight) * vec3(1.0, 1.0, 1.0);
    L = normalize(light);

    //gl_Position = Tcomp * vec4(Position, 1.5);
    gl_Position = P *(MV * vec4(Position, 1.0));

}

