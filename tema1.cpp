#include "lab_m1/tema1/tema1.h"

#include <vector>
#include <iostream>

#include "lab_m1/tema1/transform2D.h"
#include "lab_m1/tema1/object2D.h"
#include "object2D.h"

using namespace std;
using namespace m1;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


Tema1::Tema1()
{
}


Tema1::~Tema1()
{
}


void Tema1::Init()
{
    glm::ivec2 resolution = window->GetResolution();
    auto camera = GetSceneCamera();
    camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
    camera->SetPosition(glm::vec3(0, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);


    // Initialize tx and ty (the translation steps)
    translateX = 0;
    translateY = 0;

    // Initialize sx and sy (the scale factors)
    scaleX = 1;
    scaleY = 1;

    // Initialize angularStep
    angularStep = 0;

    // Initialize the point around wings rotate
    wingRX = 90;
    wingRY = 50;

    // Initialize the limits for the bird's flight
    Xmin = 0;
    Ymin = 200;
    Ymax = 720;
    Xmax = 1280;

    // Initialize variables
    directionUp = true;
    directionRight = true;
    speedY = (rand() % 70) + 100;
    speedX = sqrt(62500 - speedY * speedY); // se misca cu viteza constanta de 200
    translateX = rand() % 1280;
    translateY = 0;
    rotation = 0;
    alive = true;
    seconds = 0;
    vieti = 3;
    gloante = 3;
    score = 0;
    
    CreateDuck();
 
 }


void Tema1::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0, 0, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}


void Tema1::Update(float deltaTimeSeconds)
{

    modelMatrix = glm::mat3(1);
    
    RenderMesh2D(meshes["iarba"], shaders["VertexColor"], modelMatrix);
    RenderMesh2D(meshes["frameScor"], shaders["VertexColor"], modelMatrix);
    RenderMesh2D(meshes["scor"], shaders["VertexColor"], transform2D::Translate(Xmax - 230, window->GetResolution().y - 100) * transform2D::Scale(score, 1));

    if (gloante >= 1)
        RenderMesh2D(meshes["glont1"], shaders["VertexColor"], modelMatrix);
    if (gloante >= 2)
        RenderMesh2D(meshes["glont2"], shaders["VertexColor"], modelMatrix);
    if (gloante == 3)
        RenderMesh2D(meshes["glont3"], shaders["VertexColor"], modelMatrix);


    if (vieti >= 1)
        RenderMesh2D(meshes["viata1"], shaders["VertexColor"], modelMatrix);
    if (vieti >= 2)
        RenderMesh2D(meshes["viata2"], shaders["VertexColor"], modelMatrix);
    if (vieti == 3)
        RenderMesh2D(meshes["viata3"], shaders["VertexColor"], modelMatrix);

    if (alive)
        seconds += deltaTimeSeconds;

    if (vieti > 0 && score < 2.5) {
        if (seconds < 10) {
            if (alive) {
                if (directionUp == false) {
                    translateY -= deltaTimeSeconds * speedY;
                    if (translateY < Ymin)
                        directionUp = true;

                }
                else {
                    translateY += deltaTimeSeconds * speedY;
                    if (translateY > (Ymax - 100))
                        directionUp = false;
                }

                if (directionRight == false) {
                    rotation = M_PI;
                    translateX -= deltaTimeSeconds * speedX;
                    if (translateX < Xmin)
                        directionRight = true;

                }
                else {
                    rotation = 0;
                    translateX += deltaTimeSeconds * speedX;
                    if (translateX > (Xmax - 100))
                        directionRight = false;
                }

                if (directionRight == true)
                    modelMatrix = transform2D::Translate(translateX, translateY) * transform2D::Rotate(rotation);
                else
                    modelMatrix = transform2D::Translate(translateX + 250, translateY + 140) * transform2D::Rotate(rotation);

            }
            else {
                translateY -= deltaTimeSeconds * 150;
                modelMatrix = transform2D::Translate(translateX, translateY + 200) * transform2D::Rotate(-M_PI_2);
                if (translateY < -150) {
                    speedX = (rand() % 100) + 300 * score;
                    speedY = (rand() % 100) + 300 * score;
                    translateX = rand() % 1280;
                    translateY = 0;
                    rotation = 0;
                    alive = true;
                    seconds = 0;
                    gloante = 3;
                }
            }

        }
        else {
            translateY += deltaTimeSeconds * 200;
            modelMatrix = transform2D::Translate(translateX + 100, translateY - 150) * transform2D::Rotate(M_PI_2);
            if (translateY > (Ymax + 150)) {
                speedX = (rand() % 100) + 300 * score;
                speedY = (rand() % 100) + 300 * score;
                translateX = rand() % 1280;
                translateY = 0;
                rotation = 0;
                alive = true;
                seconds = 0;
                vieti--;
                gloante = 3;
            }

        }

    }
    
 
    RenderMesh2D(meshes["cap"], shaders["VertexColor"], modelMatrix);
    RenderMesh2D(meshes["corp"], shaders["VertexColor"], modelMatrix);
    RenderMesh2D(meshes["cioc"], shaders["VertexColor"], modelMatrix);


    if (angularStep >= 0.4)
       angleWings = false;
    if (angularStep < 0)
       angleWings = true;

    if (angleWings)
        angularStep += 0.02;
    else
        angularStep -= 0.02;

    modelMatrix *= transform2D::Translate(wingRX, wingRY);
    modelMatrix *= transform2D::Rotate(angularStep);
    modelMatrix *= transform2D::Translate(-wingRX, -wingRY);

    RenderMesh2D(meshes["aripa1"], shaders["VertexColor"], modelMatrix);

    modelMatrix *= transform2D::Translate(wingRX, wingRY);
    modelMatrix *= transform2D::Rotate(angularStep);
    modelMatrix *= transform2D::Translate(-wingRX, -wingRY);

    RenderMesh2D(meshes["aripa2"], shaders["VertexColor"], modelMatrix);

    
}


void Tema1::FrameEnd()
{
}



/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Tema1::OnInputUpdate(float deltaTime, int mods)
{
   
}


void Tema1::OnKeyPress(int key, int mods)
{
    // Add key press event
}


void Tema1::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event
}


void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
    int x = mouseX;
    int y = Ymax - mouseY;
    
    if (gloante > 0) {
       if (x > translateX && x < translateX + 230 && y > translateY && y < translateY + 120) {
             printf("HIT\n");
             alive = false;
             score += 0.1;
       }
        else
             printf("MISS\n");
    }

    gloante--;
}

void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}

void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Tema1::OnWindowResize(int width, int height)
{
}

void Tema1::CreateDuck() 
{
    Mesh* iarba = object2D::CreateRectangle("iarba", glm::vec3(0, 0, 0), (float)window->GetResolution().x, 200, glm::vec3(0.5, 1, 0), true);
    AddMeshToList(iarba);

    Mesh* aripa1 = object2D::CreateTriangle("aripa1", glm::vec3(60, 50, 0), glm::vec3(120, 50, 0), glm::vec3(100, 140, 0), glm::vec3(0.4, 0.2, 0.1), true);
    AddMeshToList(aripa1);

    Mesh* aripa2 = object2D::CreateTriangle("aripa2", glm::vec3(60, 50, 0), glm::vec3(120, 50, 0), glm::vec3(100, -40, 0), glm::vec3(0.4, 0.2, 0.1), true);
    AddMeshToList(aripa2);

    Mesh* corp = object2D::CreateTriangle("corp", glm::vec3(0, 0, 0), glm::vec3(0, 100, 0), glm::vec3(200, 50, 0), glm::vec3(0.4, 0.2, 0.1), true);
    AddMeshToList(corp);

    Mesh* cap = object2D::CreateCircle("cap", 200, 50, 30, glm::vec3(0.3, 0.7, 0), true);
    AddMeshToList(cap);

    Mesh* cioc = object2D::CreateTriangle("cioc", glm::vec3(220, 40, 0), glm::vec3(220, 60, 0), glm::vec3(250, 50, 0), glm::vec3(1, 1, 0), true);
    AddMeshToList(cioc);

    Mesh* viata1 = object2D::CreateCircle("viata1", 50, window->GetResolution().y - 50, 30, glm::vec3(1, 0, 0), true);
    AddMeshToList(viata1);

    Mesh* viata2 = object2D::CreateCircle("viata2", 120, window->GetResolution().y - 50, 30, glm::vec3(1, 0, 0), true);
    AddMeshToList(viata2);

    Mesh* viata3 = object2D::CreateCircle("viata3", 190, window->GetResolution().y - 50, 30, glm::vec3(1, 0, 0), true);
    AddMeshToList(viata3);

    Mesh* glont1 = object2D::CreateRectangle("glont1", glm::vec3(30, window->GetResolution().y - 150, 0), 30, 50, glm::vec3(0, 0.5, 0), true);
    AddMeshToList(glont1);

    Mesh* glont2 = object2D::CreateRectangle("glont2", glm::vec3(80, window->GetResolution().y - 150, 0), 30, 50, glm::vec3(0, 0.5, 0), true);
    AddMeshToList(glont2);

    Mesh* glont3 = object2D::CreateRectangle("glont3", glm::vec3(130, window->GetResolution().y - 150, 0), 30, 50, glm::vec3(0, 0.5, 0), true);
    AddMeshToList(glont3);

    Mesh* frameScor = object2D::CreateRectangle("frameScor", glm::vec3(Xmax - 230, window->GetResolution().y - 100, 0), 200, 80, glm::vec3(0, 0, 0.5), false);
    AddMeshToList(frameScor);

    Mesh* scor = object2D::CreateRectangle("scor", glm::vec3(0, 0, 0), 80, 80, glm::vec3(0, 0, 0.5), true);
    AddMeshToList(scor);
}