#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <tool/shader.h>
#include <tool/camera.h>
#include <tool/gui.h>

#include <iostream>

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#define pi 3.14159265

#pragma comment(linker,"/subsystem:\"windows\" /entry:\"mainCRTStartup\"")
using namespace std;
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 800;

glm::vec3 cameraPos   = glm::vec3(0.0f, 0.0f,  3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);

float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

float lastX = SCR_WIDTH / 2.0f; // 鼠标上一帧的位置
float lastY = SCR_HEIGHT / 2.0f;

int tim = -1;
float speed1 = 0.0000f , speed2 = 0.0008f;
float angle1 = 35.0f , angle2 = 125.0f;
float rad = 36.0 * pi / 180.0, cx = -0.5, cy = 0.0, R = 0.25, r = R/sin((180.0-36-18)*pi/180)*sin(rad/2);

Camera camera(glm::vec3(0.0f, 1.0f, 5.0f));

glm::vec3 Positions[] = {
      glm::vec3( -0.0f,  0.0f,  0.0f),
      glm::vec3( -2.0f,  0.0f,  0.0f),
};

void show(float *vert , int size){
  cout<<"begin = \n";
  for(int j = 0 ; j < size/4; j+=6){
    cout<<vert[j] <<" "<<vert[j+1] << " "<<vert[j+2]<<" "<<vert[j+3]<<" "<<vert[j+4]<<" "<<vert[j+5]<<endl;
  }
  cout<<"end = \n";
}

void move(float size){

     Positions[0].x += sin(angle1*pi/180.0)/5*speed1;
     Positions[0].y += cos(angle1*pi/180.0)/5*speed1;
     Positions[0].z += 0.0f;

     Positions[1].x += sin(angle2*pi/180.0)/5*speed2;
     Positions[1].y += cos(angle2*pi/180.0)/5*speed2;
     Positions[1].z += 0.0f;

     float sz2 = R*1.1f , sz1 = R*size;
     //cout<<sz2<<" "<<sz1<<endl;
     float le1 , le2 , le3 , le4 , le5;
     le1 = fabs((Positions[0].x ) - (-2.5f));
     le2 = fabs((2.5f) - (Positions[0].x) );
     le3 = fabs((Positions[0].y) - (-2.5f));
     le4 = fabs((2.5f) - (Positions[0].y));
     le5 = fabs (sqrt( (Positions[0].x - Positions[1].x)*(Positions[0].x - Positions[1].x) + (Positions[0].y - Positions[1].y)*(Positions[0].y - Positions[1].y)   ) );
    if(tim >= 0){
      tim++;
      if(tim == 10){
        speed1 = 0.0007f;
        speed2 = 0.0007f;
        tim = -1;
      }
    }
    if(le5 < (sz1 + sz2) + 0.015f){
      cout<<"touch\n";
        speed1 = 0.0028f;
        speed2 = 0.0028f;
        tim = 0;
      angle1 = angle2;
      angle2 = (angle2 + 180.0f);
      if(angle1 >= 360.0f){
        cout<<"happen1\n";
        angle1 -= 360.0f;
      }
      if(angle2 >= 360.0f){
        cout<<"happen2\n";
        angle2 -= 360.0f;
      }
      return;
    }
    if(le1 < sz1+ 0.015f || le2 < sz1+ 0.015f){
         cout<<"yes2\n";
         angle1 = 360.0f - angle1;
     }
     if(le3 < sz1+ 0.015f || le4 < sz1+ 0.015f){
         if(angle1 < 180.0f){
            angle1 = angle1 - (angle1 - 90.0f)*2;
         }
         else{
            angle1 = angle1 - (angle1 - 270.0f)*2;
         }
     }


     le1 = fabs((Positions[1].x ) - (-2.5f));
     le2 = fabs((2.5f) - (Positions[1].x));
     le3 = fabs((Positions[1].y) - (-2.5f));
     le4 = fabs((2.5f) - (Positions[1].y));
     le5 = fabs (sqrt( (Positions[0].x - Positions[1].x)*(Positions[0].x - Positions[1].x) + (Positions[0].y - Positions[1].y)*(Positions[0].y - Positions[1].y)   ) );
    if(le1 < sz2+ 0.015f || le2 < sz2+ 0.015f){
         angle2 = 360.0f - angle2;
     }
     if(le3 < sz2+ 0.015f || le4 < sz2+ 0.015f){
         if(angle1 < 180.0f){
            angle2 = angle2 - (angle2 - 90.0f)*2;
         }
         else{
            angle2 = angle2 - (angle2 - 270.0f)*2;
         }
     }

  }

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

// 键盘输入监听
void processInput(GLFWwindow *window)
{
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
        glfwSetWindowShouldClose(window, true);
    }
  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
  {
    camera.ProcessKeyboard(FORWARD, deltaTime);
  }
  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
  {
    camera.ProcessKeyboard(BACKWARD, deltaTime);
  }
  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
  {
    camera.ProcessKeyboard(LEFT, deltaTime);
  }
  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
  {
    camera.ProcessKeyboard(RIGHT, deltaTime);
  }
}

// 鼠标移动监听
void mouse_callback(GLFWwindow *window, double xpos, double ypos)
{

  float xoffset = xpos - lastX;
  float yoffset = lastY - ypos;

  lastX = xpos;
  lastY = ypos;

  camera.ProcessMouseMovement(xoffset, yoffset);
}
void mouse_button_calback(GLFWwindow *window, int button, int action, int mods)
{

  if (action == GLFW_PRESS)
    switch (button)
    {
    case GLFW_MOUSE_BUTTON_LEFT:
      // cout << "mouse left" << endl;
      break;
    case GLFW_MOUSE_BUTTON_MIDDLE:
      // cout << "mouse middle" << endl;
      break;
    case GLFW_MOUSE_BUTTON_RIGHT:
      // cout << "mouse right" << endl;
      break;
    }
}

void cursor_position_callback(GLFWwindow *window, double x, double y)
{
  float xpos = float((x - SCR_WIDTH / 2) / SCR_WIDTH) * 2;
  float ypos = float(0 - (y - SCR_HEIGHT / 2) / SCR_HEIGHT) * 2;

  // cout << "xpos " << xpos << endl;
  // cout << "ypos " << ypos << endl;
  return;
}

void scroll_callback(GLFWwindow *window, double x, double y)
{
  // cout << "x " << x << endl;
  // cout << "y " << y << endl;
  return;
}


std::string Shader::dirName;

int main(int argc, char *argv[]) {
    Shader::dirName = argv[1];
	glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	GLFWwindow* window = glfwCreateWindow( SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if(window == NULL){
		cout << "Failed to create GLFW window" << endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);//寻找glad
	
    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
    glEnable(GL_DEPTH_TEST);

	 // 1.注册窗口变化监听
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
     // 2.鼠标事件
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetMouseButtonCallback(window, mouse_button_calback);
    glfwSetScrollCallback(window, scroll_callback);
    
    Shader ourShader("./shader/vertex.glsl", "./shader/fragment.glsl");
    
float vertices[] = 
{
	 -2.5f , 2.5f , 0.0f , 1.0f , 0.0f , 0.0f,
   2.5f , 2.5f , 0.0f , 0.0f , 1.0f , 0.0f,
   2.5f , -2.5f , 0.0f , 0.0f , 0.0f , 1.0f,
   -2.5f , -2.5f , 0.0f , 0.5f , 0.5f , 0.5f,
};
cx = 0.0f;
float vertices1[] = 
{
    cx , R , 0.0f, 1.0f , 0.0f , 0.0f , //1
	  cx + r * sin(rad),cy + cos(rad) * r,0.0f,1.0f , 0.0f , 0.0f ,//2
    cx + R * sin(2 * rad),cy + R * cos(2 * rad),0.0f,1.0f , 0.0f , 0.0f ,//4
    cx + r * sin(2 * rad),cy - r * cos(2 * rad),0.0f,1.0f , 0.0f , 0.0f ,//6
    cx + R * sin(rad),cy - R * cos(rad),0.0f,1.0f , 0.0f , 0.0f ,//8
    cx ,cy - r,0.0f,1.0f , 0.0f , 0.0f ,//10
    cx - R * sin(rad),cy - R * cos(rad),0.0f,1.0f , 0.0f , 0.0f ,//9
    cx - r * sin(2 * rad),cy - r * cos(2 * rad),0.0f,1.0f , 0.0f , 0.0f ,//7
    cx - R * sin(2 * rad),cy + R * cos(2 * rad),0.0f,1.0f , 0.0f , 0.0f ,//5
	  cx - r * sin(rad),cy + cos(rad) * r,0.0f,1.0f , 0.0f , 0.0f ,//3
    cx , 0.0f , 0.0f , 1.0f , 0.0f , 0.0f,//原点
};


  unsigned int indices[] = {
	     0 , 1 , 10,
         1 , 2 , 10,
         2 , 3 , 10,
         3 , 4 , 10,
         4 , 5 , 10,
         5 , 6 , 10,
         6 , 7 , 10,
         7 , 8 , 10,
         8 , 9 , 10,
         9 , 0 , 10,
	};
  unsigned int indices1[] = {
	     0 , 1 , 10,
         1 , 2 , 10,
         2 , 3 , 10,
         3 , 4 , 10,
         4 , 5 , 10,
         5 , 6 , 10,
         6 , 7 , 10,
         7 , 8 , 10,
         8 , 9 , 10,
         9 , 0 , 10,
	};
  //矩形方框
  unsigned int VBO , VAO ;
	glGenVertexArrays(1 , &VAO);
	glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);



	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);


	glBindVertexArray(0);



    //第一个五角星
  unsigned int VBO1 , VAO1 ;
  unsigned int EBO ;
	glGenVertexArrays(1 , &VAO1);
	glGenBuffers(1, &VBO1);
  glGenBuffers(1, &EBO);

  glBindVertexArray(VAO1);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_DYNAMIC_DRAW);


	glBindBuffer(GL_ARRAY_BUFFER, VBO1);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_DYNAMIC_DRAW);

	

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);


	glBindVertexArray(0);
 

  float factor = 0.0;
  float fov = 90.0f; // 视锥体的角度
  glm::vec3 view_translate = glm::vec3(0.0, 0.0, -5.0);
  ImVec4 clear_color = ImVec4(25.0 / 255.0, 25.0 / 255.0, 25.0 / 255.0, 1.0);



	while (!glfwWindowShouldClose(window))
  {

    float currentFrame = (glfwGetTime());
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    processInput(window);

    glClearColor(0.2f , 0.3f , 0.3f , 1.0f);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    factor = glfwGetTime();
    ourShader.setFloat("factor", -factor * 0.3);
    

    ourShader.use();

    float radius = 10.0f;
    float camX = sin(glfwGetTime()) * radius;
    float camZ = cos(glfwGetTime()) * radius;

    glm::mat4 view = camera.GetViewMatrix();
    glm::mat4 projection = glm::mat4(1.0f);
    projection = glm::perspective(glm::radians(fov), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
    glm::mat4 model = glm::mat4(1.0f);

    ourShader.setMat4("view", view);
    ourShader.setMat4("projection", projection);
    ourShader.setMat4("model", model);
   
    glBindVertexArray(VAO);
    glDrawArrays(GL_LINE_LOOP ,  0 ,  4);

    glBindVertexArray(VAO1);
    glBindBuffer(GL_ARRAY_BUFFER, VBO1);
	  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_DYNAMIC_DRAW); 
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_DYNAMIC_DRAW);
    float size = 0.9f + fabs(sin(glfwGetTime()));
    for (unsigned int i = 0; i < 2; i++)
      {     
            float sizes;
            sizes = size;
            if(i == 1){
              sizes = 1.1f;
            }
            // calculate the model matrix for each object and pass it to shader before drawing
            glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
            model = glm::translate(model, Positions[i]);
            model = glm::rotate(model, (float)glfwGetTime() , glm::vec3(0.0f, 0.0f, 0.5f));//旋转角度
            model = glm::scale(model, glm::vec3(sizes));//放大倍数
            ourShader.setMat4("model", model);

            glDrawElements(GL_TRIANGLES, 30, GL_UNSIGNED_INT, 0);
      }
    move(size);
    glfwSwapBuffers(window);
    glfwPollEvents();

  }
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);


  glDeleteVertexArrays(1, &VAO1);
  glDeleteBuffers(1, &VBO1);

	glfwTerminate();

	return 0;
}


