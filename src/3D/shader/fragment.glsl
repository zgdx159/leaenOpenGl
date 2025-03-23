#version 460 core
out vec4 FragColor;

in vec2 TexCoord;
in vec3 outNormal;
in vec3 outFragPos;

uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;

uniform float ambientStrength;
uniform sampler2D ourtexture1;
uniform sampler2D ourtexture2;

void main(){
  vec4 objectcolor = mix(texture(ourtexture1, TexCoord), texture(ourtexture2, TexCoord), 0.1);//纹理

  vec3 ambient = ambientStrength * lightColor;//环境光

  vec3 norm = normalize(outNormal);
  vec3 lightDir = normalize(lightPos - outFragPos);
  float  diff = max(dot(norm, lightDir), 0.0);//结果小于0就用0.0作为值
  vec3 diffuse = diff * lightColor;//漫反射
  

   float specularStrength = 0.7;
   vec3 viewDir = normalize(viewPos - outFragPos);
   vec3 reflectDir = reflect(-lightDir, norm);
   float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
   vec3 specular = specularStrength * spec * lightColor;//镜面反射

  vec3 result = (ambient + diffuse + specular) * vec3(objectcolor);

   //FragColor = mix(texture(ourtexture1, TexCoord), texture(ourtexture2, TexCoord), 0.5);
   FragColor = vec4(result, 1.0);
  //颜色为红 绿 蓝 透明度
}



