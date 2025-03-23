#version 460 core
layout (location = 0) in vec3 aPos;
layout(location = 1) in vec3 Normal;
layout(location = 2) in vec2 aTexCoord;

out vec2 TexCoord;
out vec3 outFragPos;
out vec3 outNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;


void main(){
  gl_Position = projection * view * model * vec4(aPos, 1.0f);
  gl_PointSize = 10.0f;
  outFragPos = vec3(model * vec4(aPos, 1.0f));
  TexCoord = aTexCoord;
  outNormal = mat3(transpose(inverse(model)))*Normal;
}