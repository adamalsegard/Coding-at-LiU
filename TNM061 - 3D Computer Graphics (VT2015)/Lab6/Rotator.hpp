#include <GLFW/glfw3.h>
#include <cmath>

#ifndef M_PI
#define M_PI (3.141592653589793)
#endif

class KeyRotator {

public:
	float phi;
	float theta;

private:
	double lastTime;

public:
    void init(GLFWwindow *window);
    void poll(GLFWwindow *window);
};

class KeyTranslator {

public:
	float x;
	float y;
	float z;

private:
	double lastTime;

public:
    void init(GLFWwindow *window);
    void poll(GLFWwindow *window, float theta, float phi);
};


class MouseRotator {

public:
	float phi;
	float theta;

private:
	double lastX;
	double lastY;
	int lastLeft;
	int lastRight;

public:
    void init(GLFWwindow *window);
    void poll(GLFWwindow *window);
};
