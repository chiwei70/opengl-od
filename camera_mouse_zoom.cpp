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

// test for rotate
float xx, yy, zz;
float rZ = 0.0;
float rY = 0.0;
float rX = 0.0;


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

	glm::mat4 projection;
	glm::mat4 view;
	glm::mat4 model;
	//1 ���������в���
	string effectFileName;
	if (argc == 2) {
		effectFileName = argv[1];

		//
		ifstream fin(effectFileName.c_str());
		// ifstream fin("pline.dat");
		char str[100];
		string line, sub;

		int count = 0;
		// 1 ��ȡ�߶�����
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
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_DOUBLEBUFFER);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_DST_ALPHA);

	// build and compile our shader zprogram
	// ------------------------------------
	Shader ourShader("7.3.camera.vs", "7.3.camera.fs");
	Shader flyShader("7.3.fly.vs", "7.3.fly.fs");

	// ���ļ��л�ȡ����
	// 1 �����߶���������VAO VBO
	// 2 ��ȡ��������
	ifstream fin("e:/fdb/pline.dat");
	//ifstream fin("pline.dat");
	char str[100];
	string line, sub;

	// 1 ��ȡ�߶�����
	fin.getline(str, 100);
	line = str;
	int numPolylines = atoi(line.c_str());
	cout << numPolylines << " polylines" << endl;

	//����vector���涥������
	// vector<float> *verData[] = new vector<float>(numPolylines);
	vector<lineEffect*>lineEffects;
	vector<vector<float>*>verDataP;// = new vector<float>(numPolylines);
	vector<int> color;// = new int(numPolylines);
	map<int, vector<int>*>colorGroup;//һ����ɫ��Ӧһ��vector��һ��polyline��
	map<int, vector<int>*>::iterator it;
	glm::vec3* colorData = new glm::vec3[numPolylines];//����gpu
	


	for (int i = 0; i < numPolylines; i++) {
		//lineEffect���󣬼�¼���Բ���
		lineEffects.push_back(new lineEffect());
		//���� To do: verDataP���Է���lineEffect������ 2021/6/20
		verDataP.push_back(new vector<float>());
	}

	// 2 ��ȡ��������
	for (int i = 0; i < numPolylines; i++) {
		// ���vector
		//verData[i].clear();
		// ��ȡ�� i ������
			//// ��ȡ��ɫ
		fin.getline(str, 100);
		line = str;
		int colorV = atoi(line.c_str());
		color.push_back(colorV);
		lineEffects[i]->color = colorV;

		

		//�����ĸ���ɫ��
		it = colorGroup.find(colorV);

		if (it != colorGroup.end()) {//���������ɫ
			if (it->first != colorV)
				cout << "What's wrong? color != " << colorV << endl;
			it->second->push_back(i);

		}
		else {//���������ɫ
			vector<int>* newPolylineGroup = new vector<int>;//����һ��Polyline��
			colorGroup.insert(pair<int, vector<int>*>(colorV, newPolylineGroup));//������ɫ��
			newPolylineGroup->push_back(i);
		}

		// ��ȡ����ʱ��
		fin.getline(str, 100);
		line = str;
		lineEffects[i]->drawTime = atof(line.c_str());


		// ��ȡ�������
		fin.getline(str, 100);
		line = str;
		// int numVertices = atoi(line.c_str());
		lineEffects[i]->numVertices = atoi(line.c_str());
		cout << lineEffects[i]->numVertices << " vertex" << endl;

		// ��ȡ numVertexs ����������
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
				sub = line.substr(pos + 1, len - pos - 1);
				line = sub;

				pos = line.find(",");
				len = line.length();
				sub = line.substr(0, pos);
				verDataP[i]->push_back(atof(sub.c_str()));// y

				sub = line.substr(pos + 1, len - pos - 1);
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

	// ������Ч����ɫ���ݣ�Ҫ����Ƶ�˳��һ��
	int i = 0;
	for (it = colorGroup.begin(); it != colorGroup.end(); ++it) {
		int currentColor = it->first;
		int num = it->second->size();//�м�����
		//��ɫ��Ϣ���浽 colorData
		if (currentColor == 1) {
			for (int j = 0; j < num; j++) {
				colorData[i] = glm::vec3(1.0f, 0.0f, 0.0f);
				i++;
			}
		}
		else if (currentColor == 2) {
			for (int j = 0; j < num; j++) {
				colorData[i] = glm::vec3(1.0f, 1.0f, 0.0f);
				i++;
			}
		}
		else if (currentColor == 3) {
			for (int j = 0; j < num; j++) {
				colorData[i] = glm::vec3(0.0f, 1.0f, 0.0f);
				i++;
			}
		}
		else if (currentColor == 4) {
			for (int j = 0; j < num; j++) {
				colorData[i] = glm::vec3(0.0f, 1.0f, 1.0f);
				i++;
			}
		}
		else if (currentColor == 5) {
			for (int j = 0; j < num; j++) {
				colorData[i] = glm::vec3(0.0f, 0.0f, 1.0f);
				i++;
			}
		}
		else if (currentColor == 6) {
			for (int j = 0; j < num; j++) {
				colorData[i] = glm::vec3(1.0f, 0.0f, 1.0f);
				i++;
			}
		}
		else if (currentColor == 7) {
			for (int j = 0; j < num; j++) {
				colorData[i] = glm::vec3(1.0f, 1.0f, 1.0f);
				i++;
			}
		}
		else if (currentColor == 8) {
			for (int j = 0; j < num; j++) {
				colorData[i] = glm::vec3(0.5f, 0.5f, 0.5f);
				i++;
			}
		}
		else if (currentColor == 9) {
			for (int j = 0; j < num; j++) {
				colorData[i] = glm::vec3(0.75f, 0.75f, 0.75f);
				i++;
			}
		}
		else if (currentColor == 10) {
			for (int j = 0; j < num; j++) {
				colorData[i] = glm::vec3(1.0f, 0.0f, 0.0f);
				i++;
			}
		}
		else if (currentColor == 252) {
			for (int j = 0; j < num; j++) {
				colorData[i] = glm::vec3(0.5f, 0.5f, 0.5f);
				i++;
			}
		}
		else {
			for (int j = 0; j < num; j++) {
				colorData[i] = glm::vec3(1.0f, 1.0f, 1.0f);
				i++;
			}
		}
		
	}

	// set up vertex data (and buffer(s)) and configure vertex attributes
// ------------------------------------------------------------------
	//float quadVertices[] = {
	//	// positions          // colors           // texture coords
	//	 0.05f,  0.05f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
	//	 0.05f, -0.05f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
	//	-0.05f, -0.05f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
	//	-0.05f,  0.05f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
	//};

	//float quadVertices[] = {
	//	// positions          // colors           // texture coords
	//	 0.05f,  0.0f, -0.05f,    1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
	//	 0.05f,  0.0f,  0.05f,    0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
	//	-0.05f,  0.0f,  0.05f,    0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
	//	-0.05f,  0.0f, -0.05f,    1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
	//};
	float quadVertices[] = {
		-0.025f, 0.0f, -0.05f,  1.0f, 0.0f, 0.0f,
		-0.025f, 0.0f, 0.05f,  1.0f, 0.0f, 0.0f,
		0.075f,  0.0f, 0.0f, 1.0f, 0.0f, 0.0f
	};
	//unsigned int indices[] = {
	//0, 1, 3, // first triangle
	//1, 2, 3  // second triangle
	//};


	// ���������Чλ������
	glm::mat4* modelMatrices;
	modelMatrices = new glm::mat4[numPolylines];
	

	for (int i = 0; i < numPolylines; i++)
	{
		model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
		
		model = glm::translate(model, glm::vec3((float)i, 0.0, 0.0));


		// model = glm::rotate(model, 0.0f, glm::vec3(0, 1, 0));


		// model = glm::rotate(model, 0.0f, glm::vec3(0, 0, 1));

		modelMatrices[i] = model;
	}
	
	// configure instanced array
	unsigned int instanceVBO, colorVBO;
	glGenBuffers(1, &instanceVBO);
	glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
	glBufferData(GL_ARRAY_BUFFER, numPolylines * sizeof(glm::mat4), &modelMatrices[0], GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &colorVBO);
	glBindBuffer(GL_ARRAY_BUFFER, colorVBO);
	glBufferData(GL_ARRAY_BUFFER, numPolylines * sizeof(glm::vec3), &colorData[0], GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// ������Ч
	unsigned int quadVAO, quadVBO;// , EBO;//���Ʒ�����Ч������
	glGenVertexArrays(1, &quadVAO);
	glGenBuffers(1, &quadVBO);
	// glGenBuffers(1, &EBO);

	glBindVertexArray(quadVAO);

	glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);

	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));


	//// also set instance data
	//glEnableVertexAttribArray(3);
	//glBindBuffer(GL_ARRAY_BUFFER, instanceVBO); // this attribute comes from a different vertex buffer
	//glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	//glVertexAttribDivisor(3, 1); // tell OpenGL this is an instanced vertex attribute.

	glEnableVertexAttribArray(3);
	glBindBuffer(GL_ARRAY_BUFFER, colorVBO); // this attribute comes from a different vertex buffer
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
	glVertexAttribDivisor(3, 1);

	glEnableVertexAttribArray(4);
	glBindBuffer(GL_ARRAY_BUFFER, instanceVBO); // this attribute comes from a different vertex buffer
	glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)0);
	glVertexAttribDivisor(4, 1);

	glEnableVertexAttribArray(5);
	glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(glm::vec4)));
	glVertexAttribDivisor(5, 1);

	glEnableVertexAttribArray(6);
	glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(2 * sizeof(glm::vec4)));
	glVertexAttribDivisor(6, 1);

	glEnableVertexAttribArray(7);
	glVertexAttribPointer(7, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(3 * sizeof(glm::vec4)));
	glVertexAttribDivisor(7, 1);


	// glBindBuffer(GL_ARRAY_BUFFER, 0);

	//glEnableVertexAttribArray(7);
	//glBindBuffer(GL_ARRAY_BUFFER, colorVBO); // this attribute comes from a different vertex buffer
	//glVertexAttribPointer(7, 3, GL_FLOAT, GL_FALSE, sizeof(float), (void*)0);
	

	glBindVertexArray(0);




	//// load and create a texture 
	//// -------------------------
	//unsigned int texture;
	//glGenTextures(1, &texture);
	//glBindTexture(GL_TEXTURE_2D, texture); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
	//// set the texture wrapping parameters
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//// set texture filtering parameters
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//// load image, create texture and generate mipmaps
	//int width, height, nrChannels;
	//// The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
	//// unsigned char *data = stbi_load(FileSystem::getPath("resources/textures/container.jpg").c_str(), &width, &height, &nrChannels, 0);
	//unsigned char* data = stbi_load(FileSystem::getPath("resources/textures/arrow2.png").c_str(), &width, &height, &nrChannels, 0);
	//if (data)
	//{
	//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	//	glGenerateMipmap(GL_TEXTURE_2D);
	//}
	//else
	//{
	//	std::cout << "Failed to load texture" << std::endl;
	//}
	//// stbi_image_free(data);
	//unsigned char* data1 = stbi_load(FileSystem::getPath("resources/textures/awesomeface1.png").c_str(), &width, &height, &nrChannels, 0);
	//if (data1)
	//{
	//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data1);
	//	glGenerateMipmap(GL_TEXTURE_2D);
	//}
	//else
	//{
	//	std::cout << "Failed to load texture" << std::endl;
	//}
	//unsigned char* data2 = stbi_load(FileSystem::getPath("resources/textures/awesomeface2.png").c_str(), &width, &height, &nrChannels, 0);
	//if (data2)
	//{
	//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data2);
	//	glGenerateMipmap(GL_TEXTURE_2D);
	//}
	//else
	//{
	//	std::cout << "Failed to load texture" << std::endl;
	//}
	/*glBindTexture(GL_TEXTURE_2D, 0);*/



	// ����VAO��VBO���� VAOs VBOs  ������Ч VAOFlys VBOFlys 
	unsigned int* VAOs = new unsigned int[numPolylines];
	unsigned int* VBOs = new unsigned int[numPolylines];
	glGenVertexArrays(numPolylines, VAOs);
	glGenBuffers(numPolylines, VBOs);



	for (int i = 0; i < numPolylines; i++) {
		int tSize = verDataP[i]->size();
		cout << tSize / 7 << " polylines" << endl;

		//��
		glBindVertexArray(VAOs[i]);
		glBindBuffer(GL_ARRAY_BUFFER, VBOs[i]);
		glBufferData(GL_ARRAY_BUFFER, verDataP[i]->size() * sizeof(float), &(*verDataP[i])[0], GL_DYNAMIC_DRAW);
		//  position attribute
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		//  color attribute
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		//������Ч
		//glBindVertexArray(VAOFlys[i]);
		//glBindBuffer(GL_ARRAY_BUFFER, VBOFlys[i]);
		//glBufferData(GL_ARRAY_BUFFER, verDataP[i]->size() * sizeof(float), &(lineEffects[i])->flyRect[0], GL_DYNAMIC_DRAW);
		//  position attribute
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		////  color attribute
		//glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(3 * sizeof(float)));
		//glEnableVertexAttribArray(1);

		glBindVertexArray(0);

	}







	// tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
	// -------------------------------------------------------------------------------------------
	// ourShader.use();




	// render loop
	// -----------
	int count = 0;
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

		ourShader.use();
		
		for (int k = 0; k < 1; k++) {//�������ܣ��ظ�����
			// ��һ��ѭ������������ɫ
			glEnable(GL_LINE_SMOOTH);
			int counterPolylines = 0;


			for (it = colorGroup.begin(); it != colorGroup.end(); ++it) {
				int currentColor = it->first;
				if (currentColor == 1) {
					ourShader.setVec3("myColor", glm::vec3(1.0, 0.0, 0.0));
					glLineWidth(3.0f);
				}
				else if (currentColor == 2) {
					ourShader.setVec3("myColor", glm::vec3(1.0, 1.0, 0.0));
					glLineWidth(3.0f);
				}
				else if (currentColor == 3) {
					ourShader.setVec3("myColor", glm::vec3(0.0, 1.0, 0.0));
					glLineWidth(3.0f);
				}
				else if (currentColor == 4) {
					ourShader.setVec3("myColor", glm::vec3(0.0, 1.0, 1.0));
					glLineWidth(3.0f);
				}
				else if (currentColor == 5) {
					ourShader.setVec3("myColor", glm::vec3(0.0, 0.0, 1.0));
					glLineWidth(1.0f);
				}
				else if (currentColor == 6) {
					ourShader.setVec3("myColor", glm::vec3(1.0, 0.0, 1.0));
					glLineWidth(1.0f);
				}
				else if (currentColor == 7) {
					ourShader.setVec3("myColor", glm::vec3(1.0, 1.0, 1.0));
					glLineWidth(1.0f);
				}
				else if (currentColor == 8) {
					ourShader.setVec3("myColor", glm::vec3(0.5, 0.5, 0.5));
					glLineWidth(1.0f);
				}
				else if (currentColor == 9) {
					ourShader.setVec3("myColor", glm::vec3(0.75, 0.75, 0.75));
					glLineWidth(1.0f);
				}
				else if (currentColor == 10) {
					ourShader.setVec3("myColor", glm::vec3(1.0, 0.0, 0.0));
					glLineWidth(1.0f);
				}
				else if (currentColor == 252) {
					ourShader.setVec3("myColor", glm::vec3(0.5, 0.5, 0.5));
					glLineWidth(1.0f);
				}
				else {
					ourShader.setVec3("myColor", glm::vec3(1.0, 1.0, 1.0));
					glLineWidth(1.0f);
				}



				projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 1000.0f);
				view = camera.GetViewMatrix();


				float lastDX = 0.0;
				float lastDY = 0.0;
				float lastDZ = 0.0;
				float deltaX = 0.0;
				float deltaY = 0.0;
				float deltaZ = 0.0;
				for (int j = 0; j < it->second->size(); j++) {//һ���ߣ���������
					//for (int j = 0; j < 2; j++) {
					int currentPolyline = it->second->at(j);
					int currentPolylineSize = verDataP[currentPolyline]->size() / 7;

					//���������Чλ������
					
					// calculate the model matrix for each object and pass it to shader before drawing
					model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
					float* x = &(*verDataP[currentPolyline])[0] + (currentPolylineSize - lineEffects[currentPolyline]->drawPos -1) * 7;
					float* y = &(*verDataP[currentPolyline])[0] + (currentPolylineSize - lineEffects[currentPolyline]->drawPos - 1) * 7 + 1;
					float* z = &(*verDataP[currentPolyline])[0] + (currentPolylineSize - lineEffects[currentPolyline]->drawPos - 1) * 7 + 2;

					if ((lineEffects[currentPolyline]->drawPos) >= (currentPolylineSize-1))
					{
						deltaX = lastDX;
						deltaY = lastDY;
						deltaZ = lastDZ;
					}
					else
					{
						float* x1 = &(*verDataP[currentPolyline])[0] + (currentPolylineSize - lineEffects[currentPolyline]->drawPos - 2) * 7;
						float* y1 = &(*verDataP[currentPolyline])[0] + (currentPolylineSize - lineEffects[currentPolyline]->drawPos - 2) * 7 + 1;
						float* z1 = &(*verDataP[currentPolyline])[0] + (currentPolylineSize - lineEffects[currentPolyline]->drawPos - 2) * 7 + 2;

						deltaX = *x1 - *x;
						deltaY = *y1 - *y;
						deltaZ = *z1 - *z;
						lastDX = deltaX;
						lastDY = deltaY;
						lastDZ = deltaZ;
					}
					

					//cout << *x << " " << *y << "  " << *z << "    " << *x1 << "  " << *y1 << "  " << *z1 << endl;

					model = glm::translate(model, glm::vec3(*x, *y, *z));
					// model = glm::translate(model, glm::vec3(0.0, 0.0, 0.0));
					// float rotAngle = (90.0);
					//��ǰ������һ�㣬����������Ч�ķ������һ�㣬��������һ��ķ���


					float radius = sqrt(deltaX * deltaX + deltaY * deltaY + deltaZ * deltaZ);
					float radiusXY = sqrt(deltaX * deltaX + deltaY * deltaY);
					float radiusXZ = sqrt(deltaX * deltaX + deltaZ * deltaZ);
					float radiusYZ = sqrt(deltaY * deltaY + deltaZ * deltaZ);
					// cout << deltaX << "  " << deltaY << "  " << deltaZ << "    "<<radius<<"  "<<radiusXY<<"  "<<radiusXZ<<"  "<<radiusYZ<<endl;


					float rotAngle;
 
					//1 ������ y ����ת��������ЧҲӦ����ת
					if (deltaZ <= 0)//�ڵ�1��2���ޣ���acos{
						rotAngle = acos(deltaX / radiusXZ);
					else // �ڵ�3��������
						rotAngle = -acos(deltaX / radiusXZ);

					// rotAngle = rY;
					model = glm::rotate(model, rotAngle, glm::vec3(0, 1, 0));

					//2 ������ z ����ת
					rotAngle = atan(deltaY / radiusXZ);
					// rotAngle = rZ;
					// cout << "z " << rotAngle << endl;
					model = glm::rotate(model, rotAngle, glm::vec3(0, 0, 1));

					if (counterPolylines >= numPolylines) {
						cout << "what's wrong? counterPolylines = " << counterPolylines << endl;
						counterPolylines = 0;
					}
					else {
						modelMatrices[counterPolylines] = model;
						counterPolylines++;
					}
						



					//������
					ourShader.use();

					// pass projection matrix to shader (note that in this case it could change every frame)
					// glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 1000.0f);
					ourShader.setMat4("projection", projection);

					// camera/view transformation
					// glm::mat4 view = camera.GetViewMatrix();
					ourShader.setMat4("view", view);

					// calculate the model matrix for each object and pass it to shader before drawing
					glm::mat4 modelNew = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
					modelNew = glm::translate(modelNew, glm::vec3(0.0, 0.0, 0.0));
					ourShader.setMat4("model", modelNew);



					// render boxes
					glBindVertexArray(VAOs[currentPolyline]);

					for (int k = 0; k < 1; k++)//һ���߻�������
					{
						// �޸�alpha���ݣ�ͨ��͸����ʵ�ֶ���Ч��
						// To do: Ҳ�����޸���ɫʵ�ֶ���Ч�� 2021/6/20
						float* pAlpha = &(*verDataP[currentPolyline])[0] + 6;
						for (int m = 0; m < verDataP[currentPolyline]->size() / 7; m++) {
							// ĿǰalphaPool��362��float����Ӧ181��������߶κ���
							// ��Ҫӳ������Ӧ��ͬ�Ķ�����
							int pos = (m + lineEffects[currentPolyline]->drawPos) * (poolSize / 2) / (verDataP[currentPolyline]->size() / 7);
							if (pos > poolSize - 1) {
								cout << "                         pos = " << pos << " is biger than 799!" << endl;
								pos = poolSize - 1;
							}
							// cout << "drawPos =	"<< lineEffects[currentPolyline]->drawPos <<"  m = "<<m<<"  pos = " << pos <<"  "<< verDataP[currentPolyline]->size() / 6 <<" vertices!"<< endl;
							*(pAlpha + m * 7) = alphaPool[pos];
						}

						glBufferData(GL_ARRAY_BUFFER, verDataP[currentPolyline]->size() * sizeof(float), &(*verDataP[currentPolyline])[0], GL_DYNAMIC_DRAW);
						// cout << "glBufferData currentPolyline = " << currentPolyline << endl;



						glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)0);
						glEnableVertexAttribArray(0);

						glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(3 * sizeof(float)));
						glEnableVertexAttribArray(1);

						

						//����
						glDrawArrays(GL_LINE_STRIP, 0, verDataP[currentPolyline]->size() / 7);
						// cout << "glDrawArrays currentPolyline = " << currentPolyline << endl;

						

					}

					// cout << (double)(1000. * (double)(t2 - t1) / CLOCKS_PER_SEC) << "  " << (double)(1000. * (double)(t3 - t2) / CLOCKS_PER_SEC) << "  " << (double)(1000. * (double)(t4 - t3) / CLOCKS_PER_SEC) << "  " << (double)(1000. * (double)(t5 - t4) / CLOCKS_PER_SEC) << endl;



					//1������һ��
					// static clock_t oldTT, currentTT;

					lineEffects[currentPolyline]->currentTT = clock();
					double time = (double)(1000 * (lineEffects[currentPolyline]->currentTT - lineEffects[currentPolyline]->oldTT) / CLOCKS_PER_SEC);

					//����೤ʱ�����һ֡
					float tt = lineEffects[currentPolyline]->drawTime * 1000 / (verDataP[currentPolyline]->size() / 7);
					if (time >= tt) {
						(lineEffects[currentPolyline]->drawPos)++;
						lineEffects[currentPolyline]->oldTT = lineEffects[currentPolyline]->currentTT;
					}
					// drawPos���Խ�磬����
					if (lineEffects[currentPolyline]->drawPos >= (verDataP[currentPolyline]->size() / 7))
						lineEffects[currentPolyline]->drawPos = 0;
				}

				

			}
			// ourShader.unUse();
				// ������һ���γɵ� ������Ч λ�����飬����ʵ��
			glDisable(GL_BLEND);
			glDisable(GL_DEPTH);
			flyShader.use();
			//
			flyShader.setMat4("projection", projection);
			flyShader.setMat4("view", view);

			glBindVertexArray(quadVAO);

			glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
			glBufferData(GL_ARRAY_BUFFER, numPolylines * sizeof(glm::mat4), &modelMatrices[0], GL_DYNAMIC_DRAW);

			glDrawArraysInstanced(GL_TRIANGLES, 0, 3, numPolylines);

			glBindVertexArray(0);
			glEnable(GL_BLEND);
			glEnable(GL_DEPTH);

			// flyShader.unUse();



		}

		// ourSha der.unUse();


		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		// cout << "glfwSwapBuffers " << endl;


		static clock_t oldT, currentT;
		static clock_t firstT;
		static int counter = 0;

		if (counter == 0)
			firstT = clock();

		currentT = clock();
		double tt1 = (double)(1000. * (double)(currentT - oldT) / CLOCKS_PER_SEC);
		double tt2 = (double)(1000. * (double)(currentT - firstT) / CLOCKS_PER_SEC);
		if (counter > 0)
			cout << "after swapbuffers, use " << tt1 << "  " << (int)(1000 / tt1) << " fps" << "    average fps = " << (int)(1000 * counter / tt2) << endl;

		oldT = currentT;
		counter++;

		if (counter >= 100)
			counter = 0;

		count++;
		if (count > 99)
			count = 0;

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
	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
		rZ +=3.1415926/900.0;
	if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
		rZ -= 3.1415926/900.0;
	if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS)
		rZ = 0.0;
	if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)
		rY += 3.1415926 / 900.0;
	if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)
		rY -= 3.1415926 / 900.0;
	if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS)
		rY = 0.0;

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