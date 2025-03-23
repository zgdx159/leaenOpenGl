#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <tool/shader.h>
#include <tool/camera.h>


#define STB_IMAGE_IMPLEMENTATION
#include <tool/stb_image.h>

#include <tool/gui.h>

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>


#include<geometry/BoxGeometry.h>
#include<geometry/PlaneGeometry.h>
#include<geometry/SphereGeometry.h>
#include<geometry/BufferGeometry.h>
#include<geometry/CylinderGeometry.h>


#include <iostream>
//本代码包含旋转和缩放
#pragma comment(linker,"/subsystem:\"windows\" /entry:\"mainCRTStartup\"")
using namespace std;
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

glm::vec3 lightPosition(1.0f, 1.5f, 0.0f);//光源位置
glm::vec3 cameraPos   = glm::vec3(0.0f, 0.0f,  3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);
float ligx = 1.0f , ligy = 1.5f , ligz = 0.0f;

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
  if(glfwGetKey(window , GLFW_KEY_DOWN) == GLFW_PRESS){
    ligy = ligy - 0.001f;
  }
  if(glfwGetKey(window , GLFW_KEY_UP) == GLFW_PRESS){
    ligy = ligy + 0.001f;
  }
  if(glfwGetKey(window , GLFW_KEY_LEFT) == GLFW_PRESS){
    ligx = ligx - 0.001f;
  }
  if(glfwGetKey(window , GLFW_KEY_RIGHT) == GLFW_PRESS){
    ligx = ligx + 0.001f;
  }
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
    const char *glsl_version = "#version 460";
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
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return -1;
  }
    
    //创建imgui上下文
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO(); 
    (void)io;
    //设置样式
    ImGui::StyleColorsDark();
    //设置平台
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version); 
    
    //设置渲染是否透明
    // glEnable(GL_PROGRAM_POINT_SIZE);
    // glEnable(GL_BLEND);
    // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    // 1.注册窗口变化监听
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
     // 2.鼠标事件
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetMouseButtonCallback(window, mouse_button_calback);
    glfwSetScrollCallback(window, scroll_callback);

	

    
    Shader ourShader("./shader/vertex.glsl", "./shader/fragment.glsl");
    Shader lightshader("./shader/light_vert.glsl", "./shader/light_frag.glsl");

    PlaneGeometry planeGeometry(1.0 , 1.0 , 1.0 , 1.0);//平面 传递长和宽 以及分点数
    SphereGeometry sphereGeometry(0.1 , 80.0  , 80.0);//球体 //传递半径大小 上球面分点和下球面分点
    BoxGeometry boxGeometry(1.0 , 1.0 , 1.0);//方块 传递长宽高 和面的分段数
    CylinderGeometry cylinderGeometry(0.5 , 0.5 , 0.75);
    SphereGeometry sphereGeometry1(0.5 , 80.0  , 80.0);

     float vertices[] = {
        //顶点坐标------------//纹理地址
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };
    
    unsigned int indices[] = {
	    // 注意索引从0开始!
        0, 1, 2 , // 第一个三角形
        0 , 2 , 3,
	  };

    glm::vec3 cubePositions[] = {
        glm::vec3( 0.0f,  0.0f,  0.0f),
        glm::vec3( 2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3( 2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3( 1.3f, -2.0f, -2.5f),
        glm::vec3( 1.5f,  2.0f, -2.5f),
        glm::vec3( 1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
    };

   unsigned int VBO , VAO ;
    //unsigned int EBO ;
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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
    
	// //设置顶点颜色指针
	// glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	// glEnableVertexAttribArray(1);

    //设置顶点纹理坐标指针
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);
 
    // 设置线框绘制模式
    //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    //生成纹理
    unsigned int texture1 , texture2 ;
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);//绑定纹理
    
    float borderColor[] = {0.3f, 0.1f, 0.7f, 1.0f};
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
    
    //设置环绕和过滤方式
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    //图像y轴翻转
    stbi_set_flip_vertically_on_load(true);
    
    //加载图片
    int width , height , nrChannels;
    unsigned char *data = stbi_load("./static/texture/container.jpg", &width, &height, &nrChannels, 0);
    if(data){
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    stbi_image_free(data);
    
    
    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    data = stbi_load("./static/texture/awesomeface.png", &width, &height, &nrChannels, 0);
    if(data){
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    stbi_image_free(data);
    
    ourShader.use();
    ourShader.setInt("ourtexture1", 0);
    ourShader.setInt("ourtexture2", 1);

    float factor = 0.0;

    float fov = 90.0f; // 视锥体的角度
    glm::vec3 view_translate = glm::vec3(0.0, 0.0, -5.0);
    ImVec4 clear_color = ImVec4( 20.0f/255.0f, 30.0f/255.0f, 5.0f/255.0f, 1.0);
   
    int f = 0;

    //光照信息
    // glm::vec3 lightPosition(1.0f, 1.5f, 0.0f);//光源位置
    ourShader.setVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));//传递光源颜色
    ourShader.setFloat("ambientStrength", 0.1f);//传递环境光比例

	while (!glfwWindowShouldClose(window))
  {
    float currentFrame = (glfwGetTime());
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
    processInput(window);

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::Begin("ImGui");
    ImGui::Text("%.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    ImGui::SliderFloat("light.x", &ligx, 0.0f, 3.0f);//滑动条改变值
    ImGui::SliderFloat("light.y", &ligy, 0.0f, 3.0f);
    ImGui::SliderFloat("light.z", &ligz, -3.0f, 3.0f);
    ImGui::RadioButton("at" , &f,(int)0);
    ImGui::SameLine();
    ImGui::RadioButton("mt" , &f , (int)1);
    ImGui::ColorEdit3("background color", (float *)&clear_color);
    ImGui::End();
    if (f == 1)
    { 
         lightPosition.x = ligx;
         lightPosition.y = ligy;
         lightPosition.z = ligz;
    }
    // 渲染指令
    // ...
    glClearColor(clear_color.x , clear_color.y , clear_color.z , 1.0f);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    
    factor = glfwGetTime();
    //ourShader.setFloat("factor", -factor * 0.3);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture1);//激活纹理(默认是激活的)
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture2);//激活纹理(默认是激活的)

    ourShader.use();

    float radius = 10.0f;
    float camX = sin(glfwGetTime()) * radius;
    float camZ = cos(glfwGetTime()) * radius;
    glm::vec3  lightPos;
    if(f == 0){
         lightPos = glm::vec3(lightPosition.x * glm::sin(glfwGetTime()) , lightPosition.y , lightPosition.z);
    }
    else{
         lightPos = glm::vec3(lightPosition.x , lightPosition.y , lightPosition.z);
    }
    glm::mat4 view = camera.GetViewMatrix();
    glm::mat4 projection = glm::mat4(1.0f);
    projection = glm::perspective(glm::radians(fov), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
    glm::mat4 model = glm::mat4(1.0f);
    float rotate = glfwGetTime() * 0.2f;
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
    model = glm::rotate(model, (float)(rotate) , glm::vec3(1.0f, 1.0f, 1.0f));
    model = glm::scale(model, glm::vec3(1.0f));

    ourShader.setVec3("lightPos" , lightPos);
    ourShader.setVec3("viewPos" , camera.Position);
    ourShader.setMat4("view", view);
    ourShader.setMat4("projection", projection);
    ourShader.setMat4("model", model);
    

    glBindVertexArray(cylinderGeometry.VAO);
    glDrawElements(GL_TRIANGLES, cylinderGeometry.indices.size(), GL_UNSIGNED_INT, 0);

    
    radius = 10.0f;
    model = glm::mat4(1.0f);
    rotate = glfwGetTime() * 0.2f;
    model = glm::translate(model, glm::vec3(-1.5f, 0.0f, 0.0f));
    model = glm::rotate(model, (float)(rotate) , glm::vec3(1.0f, 1.0f, 1.0f));
    model = glm::scale(model, glm::vec3(1.0f));

    ourShader.setVec3("lightPos" , lightPos);
    ourShader.setVec3("viewPos" , camera.Position);
    ourShader.setMat4("view", view);
    ourShader.setMat4("projection", projection);
    ourShader.setMat4("model", model);

    glBindVertexArray(sphereGeometry1.VAO);
    glDrawElements(GL_TRIANGLES, sphereGeometry1.indices.size(), GL_UNSIGNED_INT, 0);

    radius = 10.0f;
    model = glm::mat4(1.0f);
    rotate = glfwGetTime() * 0.2f;
    model = glm::translate(model, glm::vec3(1.5f, 0.0f, 0.0f));
    model = glm::rotate(model, (float)(rotate) , glm::vec3(1.0f, 1.0f, 1.0f));
    model = glm::scale(model, glm::vec3(1.0f));

    ourShader.setVec3("lightPos" , lightPos);
    ourShader.setVec3("viewPos" , camera.Position);
    ourShader.setMat4("view", view);
    ourShader.setMat4("projection", projection);
    ourShader.setMat4("model", model);

    glBindVertexArray(boxGeometry.VAO);
    glDrawElements(GL_TRIANGLES, boxGeometry.indices.size(), GL_UNSIGNED_INT, 0);
    

    //绘制光源
    lightshader.use();
    model = glm::mat4(1.0f);
    if(f == 0){
      model = glm::translate(model, glm::vec3(lightPosition.x * glm::sin(glfwGetTime()), lightPosition.y, lightPosition.z));
    }
    else{
      model = glm::translate(model, glm::vec3(lightPosition.x, lightPosition.y, lightPosition.z));
    }
    //model = glm::translate(model, glm::vec3(lightPosition.x * glm::sin(glfwGetTime()), lightPosition.y, lightPosition.z));
    //model = glm::translate(model, glm::vec3(lightPosition.x, lightPosition.y, lightPosition.z));
    lightshader.setMat4("model", model);
    lightshader.setMat4("view" , view);
    lightshader.setMat4("projection" , projection);
    glBindVertexArray(sphereGeometry.VAO);
    glDrawElements(GL_TRIANGLES, sphereGeometry.indices.size(), GL_UNSIGNED_INT, 0);


    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glfwSwapBuffers(window);
    glfwPollEvents();
    
  }
  boxGeometry.dispose();
  planeGeometry.dispose();
  sphereGeometry.dispose();
  sphereGeometry1.dispose();

  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
	

	glfwTerminate();

	return 0;
}


