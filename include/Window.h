#pragma once

#include "Camera.h"
#include "Cube.h"
#include "Shader.h"
#include "System.h"

#include <wx/wxprec.h>
#include <wx/spinctrl.h>
 
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif
using namespace std;

class MyApp : public wxApp
{
public:
    virtual bool OnInit();
};

class Window : public wxFrame {
public:
    Window();
    // Window Properties
    static int width;
    static int height;
    static const char* windowTitle;
    
    static int count;
    // Objects to render
    static System* grid;
    static Cube* cube;

    // Shader Program
    static GLuint shaderProgram;

    // Act as Constructors and desctructors
    static bool initializeProgram();
    static bool initializeObjects();
    static void cleanUp();

    // for the Window
    static GLFWwindow* createWindow(int width, int height);
    static void resizeCallback(GLFWwindow* window, int width, int height);

    // update and draw functions
    static void idleCallback();
    static void displayCallback(GLFWwindow*);

    // helper to reset the camera
    static void resetCamera();

    // callbacks - for interaction
    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void mouse_callback(GLFWwindow* window, int button, int action, int mods);
    static void cursor_callback(GLFWwindow* window, double currX, double currY);
private:
    void OnHello(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
};

enum
{
    ID_Hello = 1
};