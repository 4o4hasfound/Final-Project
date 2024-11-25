#include "Render/RenderWindow.hpp"
//#include "Render/RenderWindow.hpp"
//
//RenderWindow::RenderWindow(int width, int height, const std::string& windowName)
//	: m_window(glfwCreateWindow(width, height, windowName.c_str(), NULL, NULL)), m_windowName(windowName), m_size(width, height), m_viewport(m_size) {
//	if (m_window == NULL) {
//		Logger::Log<Debug>("Error while loading glfw window!");
//		return;
//	}
//	glfwMakeContextCurrent(m_window);
//	gladLoadGL();
//	setupWindow();
//}
//
//RenderWindow::RenderWindow(const std::string& windowName)
//	: m_window(glfwCreateWindow(
//		glfwGetVideoMode(glfwGetPrimaryMonitor())->width,
//		glfwGetVideoMode(glfwGetPrimaryMonitor())->height, 
//		windowName.c_str(),
//		glfwGetPrimaryMonitor(),
//		NULL
//	)), m_windowName(windowName), m_size(
//		glfwGetVideoMode(glfwGetPrimaryMonitor())->width,
//		glfwGetVideoMode(glfwGetPrimaryMonitor())->height
//	), m_viewport(m_size) {
//	if (m_window == NULL) {
//		Logger::Log<Debug>("Error while loading glfw window!");
//		return;
//	}
//	glfwMakeContextCurrent(m_window);
//	gladLoadGL();
//	setupWindow();
//}
//
//RenderWindow::~RenderWindow() {
//
//}
//
//void RenderWindow::clear(const vec4 color) {
//	glClearColor(color.r, color.b, color.g, color.a);
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//}
//
//void RenderWindow::clear(float r, float g, float b, float a) {
//	glClearColor(r, g, b, a);
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//}
//
//void RenderWindow::draw(Drawable& target) {
//	target.draw(this);
//}
//
//void RenderWindow::draw(Drawable& target, Texture* texture) {
//	if (!texture) {
//		target.draw(this);
//		return;
//	}
//	target.draw(this, texture);
//}
//
//void RenderWindow::swapBuffer() {
//	glfwSwapBuffers(m_window);
//}
//
//void RenderWindow::pollEvents() const {
//	glfwPollEvents();
//}
//
//bool RenderWindow::shouldClose() {
//	return glfwWindowShouldClose(m_window);
//}
//
//void RenderWindow::setViewPort(const ViewPort& viewport) {
//	m_viewport = viewport;
//}
//
//const ViewPort& RenderWindow::getViewPort() const {
//	return m_viewport;
//}
//
//void RenderWindow::setViewPortPosition(const vec2& position) {
//	m_viewport.position = position;
//}
//
//const vec2& RenderWindow::getViewPortPosition() const {
//	return m_viewport.position;
//}
//
//void RenderWindow::setViewPortSize(const vec2& _size) {
//	m_viewport.size = _size;
//}
//
//const vec2& RenderWindow::getViewPortSize() const {
//	return m_viewport.size;
//}
//
//void RenderWindow::terminate() {
//	glfwTerminate();
//}
//
//void RenderWindow::madeCurrentContext() {
//	glfwMakeContextCurrent(m_window);
//}
//
//GLFWwindow* RenderWindow::getWindow() {
//	return m_window;
//}
//int RenderWindow::getWidth() const {
//	return m_size.x;
//}
//int RenderWindow::getHeight() const {
//	return m_size.y;
//}
//vec2 RenderWindow::getSize() const {
//	return m_size;
//}
//
//bool RenderWindow::keyPressed(int glfwKey) const {
//	return glfwGetKey(m_window, glfwKey) == GLFW_PRESS;
//}
//
//bool RenderWindow::keyReleased(int glfwKey) const {
//	return glfwGetKey(m_window, glfwKey) == GLFW_RELEASE;
//}
//
//bool RenderWindow::keyRepeated(int glfwKey) const {
//	return glfwGetKey(m_window, glfwKey) == GLFW_REPEAT;
//}
//
//bool RenderWindow::mousePressed(int glfwKey) const {
//	return glfwGetMouseButton(m_window, glfwKey) == GLFW_PRESS;
//}
//
//bool RenderWindow::mouseReleased(int glfwKey) const {
//	return glfwGetMouseButton(m_window, glfwKey) == GLFW_RELEASE;
//}
//
//bool RenderWindow::mouseRepeated(int glfwButton) const {
//	return glfwGetMouseButton(m_window, glfwButton) == GLFW_REPEAT;
//}
//
//void RenderWindow::windowResizeCallback(GLFWwindow* window, int width, int height) {
//	RenderWindow* ptr = reinterpret_cast<RenderWindow*>(glfwGetWindowUserPointer(window));
//	if (!ptr) {
//		return;
//	}
//	vec2 changeRatio = vec2(width, height) / ptr->m_size;
//	ptr->m_size.x = width;
//	ptr->m_size.y = height;
//	ptr->m_viewport.size.x *= changeRatio.x;
//	ptr->m_viewport.size.y *= changeRatio.y;
//	ptr->madeCurrentContext();
//	glViewport(0, 0, ptr->m_size.x, ptr->m_size.y);
//}
//
//void RenderWindow::setupWindow() {
//	glfwSetWindowUserPointer(m_window, reinterpret_cast<void*>(this));
//	glfwSetWindowSizeCallback(m_window, &RenderWindow::windowResizeCallback);
//	glViewport(0, 0, m_size.x, m_size.y);
//	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//	glEnable(GL_BLEND);
//	glfwSwapInterval(0);
//
//	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
//		Logger::Log<Debug>("Fail to initialize GLAD");
//	}
//}

RenderWindow::RenderWindow(int width, int height, const std::string& windowName)
	: m_size(width, height), m_display(al_create_display(width, height)) {
	if (!m_display) {
		m_size = vec2(0);
		Logger::Log<Error>("Failed to create window");
		return;
	}
	al_set_window_title(m_display, windowName.c_str());
}

RenderWindow::RenderWindow(const vec2& size, const std::string& windowName)
	: m_size(size), m_display(al_create_display(size.x, size.y)) {
	if (!m_display) {
		m_size = vec2(0);
		Logger::Log<Error>("Failed to create window");
		return;
	}
	al_set_window_title(m_display, windowName.c_str());
}

RenderWindow::RenderWindow(const std::string& windowName) {
	al_set_new_display_flags(ALLEGRO_FULLSCREEN);
	ALLEGRO_MONITOR_INFO info;
	al_get_monitor_info(0, &info);
	m_size = vec2(
		info.x2 - info.x1,
		info.y2 - info.y1
	);
	m_display = al_create_display(m_size.x, m_size.y);
	if (!m_display) {
		m_size = vec2(0);
		Logger::Log<Error>("Failed to create window");
		return;
	}
	al_set_window_title(m_display, windowName.c_str());
}

RenderWindow::~RenderWindow() {
	if (m_display) {
		al_destroy_display(m_display);
	}
}

void RenderWindow::clear(const vec3& color) {
	al_clear_to_color(al_map_rgb(color.r, color.g, color.b));
}

void RenderWindow::clear(float r, float g, float b) {
	al_clear_to_color(al_map_rgb(r, g, b));
}

ALLEGRO_DISPLAY* RenderWindow::getDisplay() const {
	return m_display;
}

void RenderWindow::flipDisplay() const {
	al_flip_display();
}
