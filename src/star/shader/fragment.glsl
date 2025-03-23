#version 460 core
out vec4 FracColor;
in vec3 ourColor;


void main(){

    FracColor = vec4(ourColor, 1.0f);

  ////颜色为红 绿 蓝 透明度
}



