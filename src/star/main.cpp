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

Camera camera(glm::vec3(0.0f, 1.0f, 5.0f));


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
    
    float rad = 36.0 * pi / 180.0, cx = -0.5, cy = 0.0, R = 0.25, r = R/sin((180.0-36-18)*pi/180)*sin(rad/2);
float vertices[] = 
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
    0.0f , 0.0f , 0.0f , 1.0f , 0.0f , 0.0f,//原点
};

cx = 0.5f;
float vertices2[] = 
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
    0.5f , 0.0f , 0.0f ,1.0f , 0.0f , 0.0f,//原点
};

float vertices3[] = 
{
    cx , R , 0.0f, 0.40f , 0.0f , 0.0f , //1
	cx + r * sin(rad),cy + cos(rad) * r,0.0f,0.40f , 0.0f , 0.0f ,//2
    cx + R * sin(2 * rad),cy + R * cos(2 * rad),0.0f,0.40f , 0.0f , 0.0f ,//4
    cx + r * sin(2 * rad),cy - r * cos(2 * rad),0.0f,0.40f , 0.0f , 0.0f ,//6
    cx + R * sin(rad),cy - R * cos(rad),0.0f,0.40f , 0.0f , 0.0f ,//8
    cx ,cy - r,0.0f,0.40f , 0.0f , 0.0f ,//10
    cx - R * sin(rad),cy - R * cos(rad),0.0f,0.40f , 0.0f , 0.0f ,//9
    cx - r * sin(2 * rad),cy - r * cos(2 * rad),0.0f,0.40f , 0.0f , 0.0f ,//7
    cx - R * sin(2 * rad),cy + R * cos(2 * rad),0.0f,0.40f , 0.0f , 0.0f ,//5
	cx - r * sin(rad),cy + cos(rad) * r,0.0f,0.40f , 0.0f , 0.0f ,//3
    0.5f , 0.0f , 0.0f ,0.40f , 0.0f , 0.0f,//原点
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

   //第一个图形
    unsigned int VBO , VAO ;
   // unsigned int EBO ;
	glGenVertexArrays(1 , &VAO);//创建VAO
	glGenBuffers(1, &VBO);//给当前定义的VBO编号，成为VBO对象
    //glGenBuffers(1, &EBO);//设置绘制索引

    glBindVertexArray(VAO);//绑定VAO

	// glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	// glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


	glBindBuffer(GL_ARRAY_BUFFER, VBO);//将当前VBO与顶点VBO绑定
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);//将顶点缓冲与我们设定的顶点数组绑定
    /*GL_STATIC_DRAW ：数据不会或几乎不会改变。
      GL_DYNAMIC_DRAW：数据会被改变很多。
      GL_STREAM_DRAW ：数据每次绘制时都会改变。
	  这里选择不会改变*/
	
	//设置顶点位置指针
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
    
	//设置顶点颜色指针
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);


	glBindVertexArray(0);


    //第二个图形
    unsigned int VBO1 , VAO1 ;
    unsigned int EBO ;
	glGenVertexArrays(1 , &VAO1);
	glGenBuffers(1, &VBO1);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO1);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


	glBindBuffer(GL_ARRAY_BUFFER, VBO1);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);

	

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);


	glBindVertexArray(0);
 

    //第三个图形
    unsigned int indices1[] = {
	     0 , 1 , 10,
         2 , 3 , 10,
         4 , 5 , 10,
         6 , 7 , 10,
         8 , 9 , 10,
	};
    unsigned int indices2[] = {
         1 , 2 , 10,
         3 , 4 , 10,
         5 , 6 , 10,
         7 , 8 , 10,
         9 , 0 , 10,
	};
    //第一边
    unsigned int VBO2 , VAO2 ;
    unsigned int EBO1 ;
	glGenVertexArrays(1 , &VAO2);
	glGenBuffers(1, &VBO2);
    glGenBuffers(1, &EBO1);

    glBindVertexArray(VAO2);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO1);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices1), indices1, GL_STATIC_DRAW);


	glBindBuffer(GL_ARRAY_BUFFER, VBO2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);

	

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
    
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
    //第二边
    unsigned int VBO3 , VAO3 ;
    unsigned int EBO2 ;
	glGenVertexArrays(1 , &VAO3);
	glGenBuffers(1, &VBO3);
    glGenBuffers(1, &EBO2);

    glBindVertexArray(VAO3);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO2);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices2), indices2, GL_STATIC_DRAW);


	glBindBuffer(GL_ARRAY_BUFFER, VBO3);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices3), vertices3, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
    
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);

    float factor = 0.0;
    float fov = 45.0f; // 视锥体的角度
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
   
    glBindVertexArray(VAO); // 不需要每次都绑定，对于当前程序其实只需要绑定一次就可以了
    glDrawArrays(GL_LINE_LOOP, 0, 10);

    glBindVertexArray(VAO1);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glDrawElements(GL_TRIANGLES, 30, GL_UNSIGNED_INT, 0);
    

    glBindVertexArray(VAO2);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO1);
    glDrawElements(GL_TRIANGLES, 15, GL_UNSIGNED_INT , 0);

    glBindVertexArray(VAO3);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO2);
    glDrawElements(GL_TRIANGLES, 15, GL_UNSIGNED_INT , 0);

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


