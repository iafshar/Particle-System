#include "Window.h"

// Window Properties
int Window::width;
int Window::height;
const char* Window::windowTitle = "Model Environment";

// Objects to render
System* Window::grid;
Cube* Window::cube;

// Camera Properties
Camera* Cam;

// Interaction Variables
bool LeftDown, RightDown;
int MouseX, MouseY;

wxSpinCtrlDouble *positionXCtrl;
wxSpinCtrlDouble *positionYCtrl;
wxSpinCtrlDouble *positionZCtrl;

wxSpinCtrlDouble *positionXVCtrl;
wxSpinCtrlDouble *positionYVCtrl;
wxSpinCtrlDouble *positionZVCtrl;

wxSpinCtrlDouble *velocityXCtrl;
wxSpinCtrlDouble *velocityYCtrl;
wxSpinCtrlDouble *velocityZCtrl;

wxSpinCtrlDouble *velocityXVCtrl;
wxSpinCtrlDouble *velocityYVCtrl;
wxSpinCtrlDouble *velocityZVCtrl;

wxSpinCtrlDouble *lifespanCtrl;
wxSpinCtrlDouble *lifespanVCtrl;

wxSpinCtrlDouble *gravityCtrl;
wxSpinCtrlDouble *airDensityCtrl;
wxSpinCtrlDouble *dragCtrl;

wxSpinCtrlDouble *radiusCtrl;

wxSpinCtrlDouble *elasticityCtrl;
wxSpinCtrlDouble *frictionCtrl;

wxSpinCtrlDouble *rateCtrl;

bool on = false;
int Window::count = 0;

// The shader program id
GLuint Window::shaderProgram;

bool MyApp::OnInit()
{
    Window *frame = new Window();
    frame->Show(true);

    return true;
}

Window::Window() 
   : wxFrame(NULL, wxID_ANY, "Particle System")
{
    wxMenu *menuFile = new wxMenu;
    menuFile->Append(ID_Hello, "&Hello...\tCtrl-H",
                     "Help string shown in status bar for this menu item");
    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT);
 
    wxMenu *menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);
 
    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append(menuFile, "&File");
    menuBar->Append(menuHelp, "&Help");
 
    SetMenuBar( menuBar );
 
    CreateStatusBar();
    SetStatusText("Welcome to wxWidgets!");
 
    Bind(wxEVT_MENU, &Window::OnHello, this, ID_Hello);
    Bind(wxEVT_MENU, &Window::OnAbout, this, wxID_ABOUT);
    Bind(wxEVT_MENU, &Window::OnExit, this, wxID_EXIT);

    wxPoint xc(1,0);
    positionXCtrl = new wxSpinCtrlDouble(this,wxID_ANY,wxEmptyString,xc,wxDefaultSize,wxSP_ARROW_KEYS,-100,100,0,0.1,wxS("InitialPositionX"));
    positionXCtrl->Show(true);

    wxPoint yc(1,30);
    positionYCtrl = new wxSpinCtrlDouble(this,wxID_ANY,wxEmptyString,yc,wxDefaultSize,wxSP_ARROW_KEYS,-2,100,-2,0.1,wxS("InitialPositionY"));
    positionYCtrl->Show(true);
    
    wxPoint zc(1,60);
    positionZCtrl = new wxSpinCtrlDouble(this,wxID_ANY,wxEmptyString,zc,wxDefaultSize,wxSP_ARROW_KEYS,-100,100,0,0.1,wxS("InitialPositionZ"));
    positionZCtrl->Show(true);

    wxPoint xv(100,0);
    positionXVCtrl = new wxSpinCtrlDouble(this,wxID_ANY,wxEmptyString,xv,wxDefaultSize,wxSP_ARROW_KEYS,0.1,100,0.1,0.1,wxS("InitialPositionXVariance"));
    positionXVCtrl->Show(true);

    wxPoint yv(100,30);
    positionYVCtrl = new wxSpinCtrlDouble(this,wxID_ANY,wxEmptyString,yv,wxDefaultSize,wxSP_ARROW_KEYS,0.1,100,0.1,0.1,wxS("InitialPositionYVariance"));
    positionYVCtrl->Show(true);
    
    wxPoint zv(100,60);
    positionZVCtrl = new wxSpinCtrlDouble(this,wxID_ANY,wxEmptyString,zv,wxDefaultSize,wxSP_ARROW_KEYS,0.1,100,0.1,0.1,wxS("InitialPositionZVariance"));
    positionZVCtrl->Show(true);

    wxPoint xvc(1,100);
    velocityXCtrl = new wxSpinCtrlDouble(this,wxID_ANY,wxEmptyString,xvc,wxDefaultSize,wxSP_ARROW_KEYS,-100,100,5,0.1,wxS("InitialvelocityX"));
    velocityXCtrl->Show(true);

    wxPoint yvc(1,130);
    velocityYCtrl = new wxSpinCtrlDouble(this,wxID_ANY,wxEmptyString,yvc,wxDefaultSize,wxSP_ARROW_KEYS,-2,100,10,0.1,wxS("InitialvelocityY"));
    velocityYCtrl->Show(true);
    
    wxPoint zvc(1,160);
    velocityZCtrl = new wxSpinCtrlDouble(this,wxID_ANY,wxEmptyString,zvc,wxDefaultSize,wxSP_ARROW_KEYS,-100,100,0,0.1,wxS("InitialvelocityZ"));
    velocityZCtrl->Show(true);

    wxPoint xvv(100,100);
    velocityXVCtrl = new wxSpinCtrlDouble(this,wxID_ANY,wxEmptyString,xvv,wxDefaultSize,wxSP_ARROW_KEYS,0.1,100,2.0,0.1,wxS("InitialvelocityXVariance"));
    velocityXVCtrl->Show(true);

    wxPoint yvv(100,130);
    velocityYVCtrl = new wxSpinCtrlDouble(this,wxID_ANY,wxEmptyString,yvv,wxDefaultSize,wxSP_ARROW_KEYS,0.1,100,2.0,0.1,wxS("InitialvelocityYVariance"));
    velocityYVCtrl->Show(true);
    
    wxPoint zvv(100,160);
    velocityZVCtrl = new wxSpinCtrlDouble(this,wxID_ANY,wxEmptyString,zvv,wxDefaultSize,wxSP_ARROW_KEYS,0.1,100,2.0,0.1,wxS("InitialvelocityZVariance"));
    velocityZVCtrl->Show(true);

    wxPoint lc(1,200);
    lifespanCtrl = new wxSpinCtrlDouble(this,wxID_ANY,wxEmptyString,lc,wxDefaultSize,wxSP_ARROW_KEYS,0,100,8.0,0.1,wxS("lifespan"));
    lifespanCtrl->Show(true);
    
    wxPoint lvc(100,200);
    lifespanVCtrl = new wxSpinCtrlDouble(this,wxID_ANY,wxEmptyString,lvc,wxDefaultSize,wxSP_ARROW_KEYS,0.1,100,2.0,0.1,wxS("lifespanVariance"));
    lifespanVCtrl->Show(true);

    wxPoint gc(1,240);
    gravityCtrl = new wxSpinCtrlDouble(this,wxID_ANY,wxEmptyString,gc,wxDefaultSize,wxSP_ARROW_KEYS,-100,100,-9.8,0.1,wxS("gravity"));
    gravityCtrl->Show(true);

    wxPoint pc(1,270);
    airDensityCtrl = new wxSpinCtrlDouble(this,wxID_ANY,wxEmptyString,pc,wxDefaultSize,wxSP_ARROW_KEYS,0,100,1.225,0.1,wxS("airDensity"));
    airDensityCtrl->Show(true);

    wxPoint dc(1,300);
    dragCtrl = new wxSpinCtrlDouble(this,wxID_ANY,wxEmptyString,dc,wxDefaultSize,wxSP_ARROW_KEYS,0,10,0.6,0.1,wxS("drag"));
    dragCtrl->Show(true);

    wxPoint rc(1,340);
    radiusCtrl = new wxSpinCtrlDouble(this,wxID_ANY,wxEmptyString,rc,wxDefaultSize,wxSP_ARROW_KEYS,0.1,100,7.0,0.1,wxS("radius"));
    radiusCtrl->Show(true);

    wxPoint ec(1,380);
    elasticityCtrl = new wxSpinCtrlDouble(this,wxID_ANY,wxEmptyString,ec,wxDefaultSize,wxSP_ARROW_KEYS,0,1,0.8,0.05,wxS("elasticityConstant"));
    elasticityCtrl->Show(true);

    wxPoint fc(1,410);
    frictionCtrl = new wxSpinCtrlDouble(this,wxID_ANY,wxEmptyString,fc,wxDefaultSize,wxSP_ARROW_KEYS,0,2,0.3,0.05,wxS("frictionConstant"));
    frictionCtrl->Show(true);


    wxPoint cr(1,450);
    rateCtrl = new wxSpinCtrlDouble(this,wxID_ANY,wxEmptyString,cr,wxDefaultSize,wxSP_ARROW_KEYS,1,50,10,1,wxS("creationRate"));
    rateCtrl->Show(true);
    
}

// Constructors and desctructors
bool Window::initializeProgram() {
    // Create a shader program with a vertex shader and a fragment shader.
    shaderProgram = LoadShaders("shaders/shader.vert", "shaders/shader.frag");

    // Check the shader program.
    if (!shaderProgram) {
        std::cerr << "Failed to initialize shader program" << std::endl;
        return false;
    }

    return true;
}

bool Window::initializeObjects() {

    srand((unsigned) time(NULL));
    grid = new System;
    cout << "Grid Constructed" << endl;

    cube = new Cube(glm::vec3(-100,-500,-400),glm::vec3(100,-2,400));
    return true;
}

void Window::cleanUp() {
    // Deallcoate the objects.
    delete grid;
    // Delete the shader program.
    glDeleteProgram(shaderProgram);
}

// for the Window
GLFWwindow* Window::createWindow(int width, int height) {
    // Initialize GLFW.
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return NULL;
    }

    // 4x antialiasing.
    glfwWindowHint(GLFW_SAMPLES, 4);

    // Apple implements its own version of OpenGL and requires special treatments
    // to make it uses modern OpenGL.
    // Ensure that minimum OpenGL version is 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // Enable forward compatibility and allow a modern OpenGL context
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // Create the GLFW window.
    GLFWwindow* window = glfwCreateWindow(width, height, windowTitle, NULL, NULL);

    // Check if the window could not be created.
    if (!window) {
        std::cerr << "Failed to open GLFW window." << std::endl;
        glfwTerminate();
        return NULL;
    }

    // Make the context of the window.
    glfwMakeContextCurrent(window);

    // Set swap interval to 1.
    glfwSwapInterval(0);

    // set up the camera
    Cam = new Camera();
    Cam->SetAspect(float(width) / float(height));

    // initialize the interaction variables
    LeftDown = RightDown = false;
    MouseX = MouseY = 0;

    // Call the resize callback to make sure things get drawn immediately.
    Window::resizeCallback(window, width, height);

    return window;
}

void Window::resizeCallback(GLFWwindow* window, int width, int height) {
#ifdef __APPLE__
    // In case your Mac has a retina display.
    glfwGetFramebufferSize(window, &width, &height);
#endif
    Window::width = width;
    Window::height = height;
    // Set the viewport size.
    glViewport(0, 0, width, height);

    Cam->SetAspect(float(width) / float(height));
}

// update and draw functions
void Window::idleCallback() {
    // Perform any updates as necessary.
    Cam->Update();

    grid->position.x = positionXCtrl->GetValue();
    grid->position.y = positionYCtrl->GetValue();
    grid->position.z = positionZCtrl->GetValue();

    grid->positionVarianceX = positionXVCtrl->GetValue();
    grid->positionVarianceY = positionYVCtrl->GetValue();
    grid->positionVarianceZ = positionZVCtrl->GetValue();

    grid->initialV.x = velocityXCtrl->GetValue();
    grid->initialV.y = velocityYCtrl->GetValue();
    grid->initialV.z = velocityZCtrl->GetValue();

    grid->velocityVarianceX = velocityXVCtrl->GetValue();
    grid->velocityVarianceY = velocityYVCtrl->GetValue();
    grid->velocityVarianceZ = velocityZVCtrl->GetValue();

    grid->pLifespan = lifespanCtrl->GetValue();

    grid->lifespanVariance = lifespanVCtrl->GetValue();

    grid->airDensity = airDensityCtrl->GetValue();
    grid->g = gravityCtrl->GetValue();
    grid->dragC = dragCtrl->GetValue();

    grid->pRadius = radiusCtrl->GetValue();

    grid->restitutionC = elasticityCtrl->GetValue();
    grid->fdynC = frictionCtrl->GetValue();

    grid->creationRate = rateCtrl->GetValue();

    grid->shootParticle(on,count);
    grid->update();
    
    
}

void Window::displayCallback(GLFWwindow* window) {
    // Clear the color and depth buffers.
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Render the object.
    cube->draw(Cam->GetViewProjectMtx(), Window::shaderProgram);
    grid->draw(Cam->GetViewProjectMtx(), Window::shaderProgram);
    // skin->Draw(Cam->GetViewProjectMtx() * skel->getWorldMatrix(0), Window::shaderProgram);
    // Gets events, including input such as keyboard and mouse or window resizing.
    glfwPollEvents();
    // Swap buffers.
    glfwSwapBuffers(window);
}

// helper to reset the camera
void Window::resetCamera() {
    Cam->Reset();
    Cam->SetAspect(float(Window::width) / float(Window::height));
}

// callbacks - for Interaction
void Window::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    /*
     * TODO: Modify below to add your key callbacks.
     */

    // Check for a key press.
    if (action == GLFW_PRESS) {
        switch (key) {
            case GLFW_KEY_ESCAPE: {
                // Close the window. This causes the program to also terminate.
                glfwSetWindowShouldClose(window, GL_TRUE);
                break;
            }
            case GLFW_KEY_R: {
                grid->vAir = glm::vec3(0);
                break;
            }
            case GLFW_KEY_DOWN: {
                grid->vAir += glm::vec3(0,0,-0.1);
                break;
            }
            case GLFW_KEY_UP: {
                grid->vAir += glm::vec3(0,0,0.1);
                break;
            }
            case GLFW_KEY_RIGHT: {
                grid->vAir += glm::vec3(0.1,0,0);
                break;
            }
            case GLFW_KEY_LEFT: {
                grid->vAir += glm::vec3(-0.1,0,0);
                break;
            }
            case GLFW_KEY_EQUAL: {
                grid->vAir += glm::vec3(0,0.1,0);
                break;
            }
            case GLFW_KEY_MINUS: {
                grid->vAir += glm::vec3(0,-0.1,0);
                break;
            }
            case GLFW_KEY_SPACE: {
                on = !on;
                
                break;
            }
            default: {
                break;
            }
        }
    }
}

void Window::mouse_callback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT) {
        LeftDown = (action == GLFW_PRESS);
    }
    if (button == GLFW_MOUSE_BUTTON_RIGHT) {
        RightDown = (action == GLFW_PRESS);
    }
}

void Window::cursor_callback(GLFWwindow* window, double currX, double currY) {
    int maxDelta = 100;
    int dx = glm::clamp((int)currX - MouseX, -maxDelta, maxDelta);
    int dy = glm::clamp(-((int)currY - MouseY), -maxDelta, maxDelta);

    MouseX = (int)currX;
    MouseY = (int)currY;

    // Move camera
    // NOTE: this should really be part of Camera::Update()
    if (LeftDown) {
        const float rate = 1.0f;
        Cam->SetAzimuth(Cam->GetAzimuth() + dx * rate);
        Cam->SetIncline(glm::clamp(Cam->GetIncline() - dy * rate, -90.0f, 90.0f));
    }
    if (RightDown) {
        const float rate = 0.005f;
        float dist = glm::clamp(Cam->GetDistance() * (1.0f - dx * rate), 0.01f, 1000.0f);
        Cam->SetDistance(dist);
    }
}

void Window::OnExit(wxCommandEvent& event)
{
    Close(true);
}
 
void Window::OnAbout(wxCommandEvent& event)
{
    wxMessageBox("This is a wxWidgets Hello World example",
                 "About Hello World", wxOK | wxICON_INFORMATION);
}
 
void Window::OnHello(wxCommandEvent& event)
{
    wxLogMessage("Hello world from wxWidgets!");
}