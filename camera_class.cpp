#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <learnopengl/filesystem.h>
#include <learnopengl/shader_m.h>
#include <learnopengl/camera.h>

#include <vector>
#include <map>

#include <iostream>

using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 1920;
const unsigned int SCR_HEIGHT = 1080;

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

// int drawPos = 0;

// data
int numVaos = 2;

int poolSize = 200;


// float alphaPool[362];

class lineEffect
{
	public:
		int color = 1;	
		float drawTime = 3.0;
		int drawPos = 0;
		int numVertices;

		clock_t oldTT, currentTT;
};



float alphaPool[] = { 
	1.0,
	1.0,
	0.0,
	0.0,
	1.0,
	1.0,
	0.0,
	0.0,
	1.0,
	1.0,
	0.0,
	0.0,
	1.0,
	1.0,
	0.0,
	0.0,
	1.0,
	1.0,
	0.0,
	0.0,
	1.0,
	1.0,
	0.0,
	0.0,
	1.0,
	1.0,
	0.0,
	0.0,
	1.0,
	1.0,
	0.0,
	0.0,
	1.0,
	1.0,
	0.0,
	0.0,
	1.0,
	1.0,
	0.0,
	0.0,
	1.0,
	1.0,
	0.0,
	0.0,
	1.0,
	1.0,
	0.0,
	0.0,
	1.0,
	1.0,
	0.0,
	0.0,
	1.0,
	1.0,
	0.0,
	0.0,
	1.0,
	1.0,
	0.0,
	0.0,
	1.0,
	1.0,
	0.0,
	0.0,
	1.0,
	1.0,
	0.0,
	0.0,
	1.0,
	1.0,
	0.0,
	0.0,
	1.0,
	1.0,
	0.0,
	0.0,
	1.0,
	1.0,
	0.0,
	0.0,
	1.0,
	1.0,
	0.0,
	0.0,
	1.0,
	1.0,
	0.0,
	0.0,
	1.0,
	1.0,
	0.0,
	0.0,
	1.0,
	1.0,
	0.0,
	0.0,
	1.0,
	1.0,
	0.0,
	0.0,
		1.0,
		1.0,
		0.0,
		0.0,
		1.0,
		1.0,
		0.0,
		0.0,
		1.0,
		1.0,
		0.0,
		0.0,
		1.0,
		1.0,
		0.0,
		0.0,
		1.0,
		1.0,
		0.0,
		0.0,
		1.0,
		1.0,
		0.0,
		0.0,
		1.0,
		1.0,
		0.0,
		0.0,
		1.0,
		1.0,
		0.0,
		0.0,
		1.0,
		1.0,
		0.0,
		0.0,
		1.0,
		1.0,
		0.0,
		0.0,
		1.0,
		1.0,
		0.0,
		0.0,
		1.0,
		1.0,
		0.0,
		0.0,
		1.0,
		1.0,
		0.0,
		0.0,
		1.0,
		1.0,
		0.0,
		0.0,
		1.0,
		1.0,
		0.0,
		0.0,
		1.0,
		1.0,
		0.0,
		0.0,
		1.0,
		1.0,
		0.0,
		0.0,
		1.0,
		1.0,
		0.0,
		0.0,
		1.0,
		1.0,
		0.0,
		0.0,
		1.0,
		1.0,
		0.0,
		0.0,
		1.0,
		1.0,
		0.0,
		0.0,
		1.0,
		1.0,
		0.0,
		0.0,
		1.0,
		1.0,
		0.0,
		0.0,
		1.0,
		1.0,
		0.0,
		0.0,
		1.0,
		1.0,
		0.0,
		0.0
					  };

int main(int   argc, char* argv[])
{
	//1 处理命令行参数
	string effectFileName;
	if (argc == 2) {
		effectFileName = argv[1];

		//
		ifstream fin(effectFileName.c_str());
		// ifstream fin("pline.dat");
		char str[100];
		string line, sub;

		int count = 0;
		// 1 获取线段数量
		while (1) {

			fin.getline(str, 100);
			line = str;
			float alphaV = atof(line.c_str());
			alphaPool[count] = alphaV;
			count++;
			if (count >= poolSize)
				break;

			cout << alphaV << endl;
		}
	}
		


	//for (int n = 0; n < 181; n++) {
	//	alphaPool[n] = (float)(181-n)*(181-n)*(181-n)/((float)181*181*181);
	//}

	//for (int n = 0; n < 181; n++) {
	//	alphaPool[181 + n] = (float)(181 - n) * (181 - n) * (181 - n) / ((float)181 * 181 * 181);
	//}

	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	// glfw window creation
	// --------------------
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "CityMaker 9 - bigV", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	// tell GLFW to capture our mouse
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}



	// configure global opengl state
	// -----------------------------
	//glEnable(GL_DEPTH_TEST);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_DST_ALPHA);

	// build and compile our shader zprogram
	// ------------------------------------
	Shader ourShader("7.4.camera.vs", "7.4.camera.fs");

	

	// 从文件中获取数据
	// 1 根据线段数量建立VAO VBO
	// 2 获取顶点数据
	ifstream fin("e:/fdb/pline.dat");
	//ifstream fin("pline.dat");
	char str[100];
	string line, sub;
	

	// 1 获取线段数量
	fin.getline(str, 100);
	line = str;
	int numPolylines = atoi(line.c_str());
	cout << numPolylines << " polylines" << endl;

	//创建vector保存顶点数据
	// vector<float> *verData[] = new vector<float>(numPolylines);
	vector<lineEffect *>lineEffects;
	vector<vector<float> *>verDataP;// = new vector<float>(numPolylines);
	vector<int> color;// = new int(numPolylines);
	map<int, vector<int>*>colorGroup;//一种颜色对应一个vector（一组polyline）
	map<int, vector<int>*>::iterator it;
	//vector<int>* currentGroup;

	

	for (int i = 0; i < numPolylines; i++) {
		//lineEffect对象，记录各自参数
		lineEffects.push_back(new lineEffect());
		//数据 To do: verDataP可以放入lineEffect对象中 2021/6/20
		verDataP.push_back(new vector<float>());
	}

	// 2 获取顶点数据
	for (int i = 0; i < numPolylines; i++) {
		// 清空vector
		//verData[i].clear();
		// 获取第 i 组数据
			//// 获取颜色
			fin.getline(str, 100);
			line = str;
			int colorV = atoi(line.c_str());
			color.push_back(colorV);
			lineEffects[i]->color = colorV;

			//属于哪个颜色组
			it = colorGroup.find(colorV);

			if (it != colorGroup.end()) {//如果是老颜色
				if (it->first != colorV)
					cout << "What's wrong? color != " << colorV << endl;
				it->second->push_back(i);

			}
			else {//如果是新颜色
				vector<int>* newPolylineGroup = new vector<int>;//创建一个Polyline组
				colorGroup.insert(pair<int, vector<int>*>(colorV, newPolylineGroup));//加入颜色组
				newPolylineGroup->push_back(i);
			}

			// 获取绘制时间
			fin.getline(str, 100);
			line = str;
			lineEffects[i]->drawTime = atof(line.c_str());
			

			// 获取顶点个数
			fin.getline(str, 100);
			line = str;
			// int numVertices = atoi(line.c_str());
			lineEffects[i]->numVertices = atoi(line.c_str());
			cout << lineEffects[i]->numVertices << " vertex" << endl;

			


			// 获取 numVertexs 个顶点数据
			for (int j = 0; j < lineEffects[i]->numVertices; j++) {
				fin.getline(str, 100);
				line = str;
				int pos = line.find(",");
				int len = line.length();
				if (pos <= len && pos >= 0) {
					sub = line.substr(0, pos);
					verDataP[i]->push_back(atof(sub.c_str()));// x
					// cout << sub.c_str() << "  ";

					// cout << "pos = " << pos << "  len = " << len << " "<<line.c_str()<<"  ";
					sub = line.substr(pos + 1, len - pos-1);
					line = sub;

					pos = line.find(",");
					len = line.length();
					sub = line.substr(0, pos);
					verDataP[i]->push_back(atof(sub.c_str()));// y

					sub = line.substr(pos + 1, len - pos -1);
					verDataP[i]->push_back(atof(sub.c_str()));// z
					// cout << sub.c_str() << endl;
					// rgba
					verDataP[i]->push_back(0.0);// r
					verDataP[i]->push_back(1.0);// g
					verDataP[i]->push_back(0.0);// b
					verDataP[i]->push_back(1.0);// a
				}
			}
	}
	fin.close();




	// 创建VAO、VBO
	// unsigned int VBOss[numPolylines], VAOss[numPolylines];
	unsigned int* VAOs = new unsigned int[numPolylines];
	unsigned int* VBOs = new unsigned int[numPolylines];

	glGenVertexArrays(numPolylines, VAOs);
	glGenBuffers(numPolylines, VBOs);

	for (int i = 0; i < numPolylines; i++) {
		int tSize = verDataP[i]->size();
		cout << tSize / 7 << " polylines" << endl;
		glBindVertexArray(VAOs[i]);
		glBindBuffer(GL_ARRAY_BUFFER, VBOs[i]);
		glBufferData(GL_ARRAY_BUFFER, verDataP[i]->size() * sizeof(float), &(*verDataP[i])[0], GL_DYNAMIC_DRAW);
		// position attribute
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		// color attribute
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
	}


	// tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
	// -------------------------------------------------------------------------------------------
	ourShader.use();




	// render loop
	// -----------
	int startPos;
	int endPos;
	float blend = 0.3;
	while (!glfwWindowShouldClose(window))
	{
		clock_t t1, t2, t3, t4, t5, t6, t7, t8;
		
		t1 = clock();
		// per-frame time logic
		// --------------------
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// input
		// -----
		processInput(window);

		// render
		// ------
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		// activate shader
		ourShader.use();

		// pass projection matrix to shader (note that in this case it could change every frame)
		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 1000.0f);
		ourShader.setMat4("projection", projection);

		// camera/view transformation
		glm::mat4 view = camera.GetViewMatrix();
		ourShader.setMat4("view", view);

		// calculate the model matrix for each object and pass it to shader before drawing
		glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
		model = glm::translate(model, glm::vec3(0.0, 0.0, 0.0));
		ourShader.setMat4("model", model);

		t2 = clock();

		// model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));


		for (int k = 0; k < 1; k++) {//测试性能，重复绘制
			// 第一层循环，多少种颜色
			glEnable(GL_LINE_SMOOTH);

			
			for(it = colorGroup.begin(); it !=colorGroup.end(); ++it){
				int currentColor = it->first;
				if (currentColor == 1) {
					ourShader.setVec3("inColor", glm::vec3(1.0, 0.0, 0.0));
					glLineWidth(3.0f);
				}
				else if (currentColor == 2) {
					ourShader.setVec3("inColor", glm::vec3(1.0, 1.0, 0.0));
					glLineWidth(3.0f);
				}
				else if (currentColor == 3) {
					ourShader.setVec3("inColor", glm::vec3(0.0, 1.0, 0.0));
					glLineWidth(3.0f);
				}
				else if (currentColor == 4) {
					ourShader.setVec3("inColor", glm::vec3(0.0, 1.0, 1.0));
					glLineWidth(3.0f);
				}
				else if (currentColor == 5) {
					ourShader.setVec3("inColor", glm::vec3(0.0, 0.0, 1.0));
					glLineWidth(1.0f);
				}
				else if (currentColor == 6) {
					ourShader.setVec3("inColor", glm::vec3(1.0, 0.0, 1.0));
					glLineWidth(1.0f);
				}
				else if (currentColor == 1) {
					ourShader.setVec3("inColor", glm::vec3(1.0, 1.0, 1.0));
					glLineWidth(1.0f);
				}
				else if (currentColor == 252) {
					ourShader.setVec3("inColor", glm::vec3(0.5, 0.5, 0.5));
					glLineWidth(1.0f);
				}
				else {
					ourShader.setVec3("inColor", glm::vec3(1.0, 1.0, 1.0));
					glLineWidth(1.0f);
				}


				t3 = clock();

				for (int j = 0; j < it->second->size(); j++) {
				//for (int j = 0; j < 2; j++) {
					int currentPolyline = it->second->at(j);
					// render boxes
					glBindVertexArray(VAOs[currentPolyline]);

					for (int k = 0; k < 1; k++)//一根线绘制两遍
					{
						// 修改alpha数据，通过透明度实现动画效果
						// To do: 也可以修改颜色实现动画效果 2021/6/20
						float* pAlpha = &(*verDataP[currentPolyline])[0] +6;
						for (int m = 0; m < verDataP[currentPolyline]->size() / 7; m++) {
							// 目前alphaPool是362个float，对应181个顶点的线段合适
							// 需要映射以适应不同的定点数
							int pos = (m + lineEffects[currentPolyline]->drawPos) * (poolSize/2) / (verDataP[currentPolyline]->size() / 7 );
							if (pos > poolSize-1) {
								cout << "                         pos = " << pos << " is biger than 799!" << endl;
								pos = poolSize-1;
							}
							// cout << "drawPos =	"<< lineEffects[currentPolyline]->drawPos <<"  m = "<<m<<"  pos = " << pos <<"  "<< verDataP[currentPolyline]->size() / 6 <<" vertices!"<< endl;
							*(pAlpha +  m * 7) = alphaPool[pos];
						}

						glBufferData(GL_ARRAY_BUFFER, verDataP[currentPolyline]->size() * sizeof(float), &(*verDataP[currentPolyline])[0], GL_DYNAMIC_DRAW);
						// cout << "glBufferData currentPolyline = " << currentPolyline << endl;



						glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)0);
						glEnableVertexAttribArray(0);

						glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(3 * sizeof(float)));
						glEnableVertexAttribArray(1);
					
						t4 = clock();

						//绘制
						glDrawArrays(GL_LINE_STRIP, 0, verDataP[currentPolyline]->size() / 7);
						// cout << "glDrawArrays currentPolyline = " << currentPolyline << endl;

						t5 = clock();

					}

					// cout << (double)(1000. * (double)(t2 - t1) / CLOCKS_PER_SEC) << "  " << (double)(1000. * (double)(t3 - t2) / CLOCKS_PER_SEC) << "  " << (double)(1000. * (double)(t4 - t3) / CLOCKS_PER_SEC) << "  " << (double)(1000. * (double)(t5 - t4) / CLOCKS_PER_SEC) << endl;



					//1秒增加一段
					// static clock_t oldTT, currentTT;

					lineEffects[currentPolyline]->currentTT = clock();
					double time = (double)(1000 * (lineEffects[currentPolyline]->currentTT - lineEffects[currentPolyline]->oldTT) / CLOCKS_PER_SEC);

					//计算多长时间更新一帧
					float tt = lineEffects[currentPolyline]->drawTime * 1000 / (verDataP[currentPolyline]->size() / 7);
					if (time >= tt) {
						(lineEffects[currentPolyline]->drawPos)++;
						lineEffects[currentPolyline]->oldTT = lineEffects[currentPolyline]->currentTT;
					}
					// drawPos如果越界，重置
					if (lineEffects[currentPolyline]->drawPos >= (verDataP[currentPolyline]->size() / 7))
						lineEffects[currentPolyline]->drawPos = 0;
				}
					

			}


			

		}


	

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		// cout << "glfwSwapBuffers " << endl;


		static clock_t oldT, currentT;
		static clock_t firstT;
		static int counter = 0;

		if(counter==0)
			firstT = clock();

		currentT = clock();
		double tt1 = (double)(1000. * (double)(currentT - oldT) / CLOCKS_PER_SEC);
		double tt2 = (double)(1000. * (double)(currentT - firstT) / CLOCKS_PER_SEC);
		if(counter>0)
			cout << "after swapbuffers, use " << tt1 << "  "<<(int)(1000/tt1)<<" fps"<< "    average fps = "<< (int)(1000 * counter / tt2)<<endl;
		
		oldT = currentT;
		counter++;
		
		if (counter >= 100)
			counter = 0;


		glfwPollEvents();
	}

	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------
	glDeleteVertexArrays(numPolylines, VAOs);
	glDeleteBuffers(numPolylines, VBOs);

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();
	return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		camera.ProcessKeyboard(UP, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
		camera.ProcessKeyboard(DOWN, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		camera.ProcessMouseMovement(0, 1);
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		camera.ProcessMouseMovement(0, -1);
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		camera.ProcessMouseMovement(-1, 0);
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		camera.ProcessMouseMovement(1, 0);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}


// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}