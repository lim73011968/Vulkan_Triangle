#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
//the vulkan header has been replaced becuase the GLFW will call it automatically
#include <iostream>
#include <cstdlib>

//this is a constant definition
//uint32_t is 32bit integer
const uint32_t WIDTH = 800;
const uint32_t HEIGHT = 600;

class HelloTriangleApplication {
public:
    void run() {
	//add this method initWindow() to run
	initWindow();
        initVulkan();
        mainLoop();
        cleanup();
    }

private:
    //write a private member that creates the actual window
    GLFWwindow* window;
    //a private member that hold the instance
    VkInstance instance;

    void initWindow(){
	//the very first call is glfwInit();
	//why?? you may ask because we have to tell the glfw it is not an OpenGL and should tell glfw to NOT create OpenGL Context
	glfwInit();
	//not sure what these 2 does
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	//this as you know creates an actual window
	//detail of this line
	//window = glfwCreateWindow(the width, the height, the title, which monitor to open the window, this is only relevent to OpenGL);
	window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr);
    }

    void initVulkan() {
	//a self made function that creates an instance
	createInstance();
    }

    void mainLoop() {
	//run the application untill the window is closed or an error occurs
	    while (!glfwWindowShouldClose(window)) {
	    glfwPollEvents();
	}
    }
    //we need to clean up resources
    void cleanup() {
	//this destroyes the window
	glfwDestroyWindow(window);

	glfwTerminate();
    }

    void createInstance() {
	//VkApplicationInfo-Structure specifiying application information
	//this whole code is kind of optional but it provieds some useful information to the driver
	VkApplicationInfo appInfo{};
	appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	appInfo.pApplicationName = "Hello Triangle";
	appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.pEngineName = "No Engine";
	appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.apiVersion = VK_API_VERSION_1_0;

	//the code below is not optional and tells the Vulkan driver which global extensions and validation layers we want to use. 
	//You don't have to know what global extension and validation layers are 
	//because they will be mentioned in next chapter
	
	VkInstanceCreateInfo createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	createInfo.pApplicationInfo = &appInfo;

	//---------EXTENSION PART---------
	    
	//how many extension do we need??
	uint32_t glfwExtensionCount = 0;
	//a storage for extension names
	const char** glfwExtensions;

	//this basically fills in two variable we mentioned
	//1. glfwExtensions
	//2. glfwExtensionCount
	//Asks GLFW: "How many extensions do we need??? and which one??"
	glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

	//we put the "count" and the "name tag" inside the VkInstanceCreateInfo createInfo we mentioned earlier
	createInfo.enabledExtensionCount = glfwExtensionCount;
	createInfo.ppEnabledExtensionNames = glfwExtensions;

	//we are not touching this for now
	createInfo.enabledLayerCount = 0;

	//this is like giving information "Which stuff I am going to use to make Vulkan Project!!!"  
	//1.the first parameter is the pointer to the createInfo. See the code we have been putting information about "Extensions" in the createInfo.
	//2.the second paramter is the callback which we don't have to know cause it will always stay nullptr.
	//3.remember the "Vkinstance instance;" we mentioned earlier outside private and public??? we are going to put the created instance inside that variable.
	VkResult result = vkCreateInstance(&createInfo, nullptr, &instance);

	//the error checker
	if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS) {
	    throw std::runtime_error("failed to create instance!");
	}
    }
};

int main() {
    HelloTriangleApplication app;

    try {
        app.run();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
