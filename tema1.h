#pragma once

#include "components/simple_scene.h"


namespace m1
{
    class Tema1 : public gfxc::SimpleScene
    {
     public:
         Tema1();
        ~Tema1();

        void Init() override;

     private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;
        void CreateDuck();
        
     protected:
        glm::mat3 modelMatrix;
        glm::mat3 modelMatrixScore;
        float translateX, translateY;
        float scaleX, scaleY;
        float angularStep;
        float wingRX, wingRY;
        float rotation;
        bool directionUp;
        bool directionRight;
        bool angleWings;
        float Xmin, Ymin, Xmax, Ymax;
        float speedX, speedY;
        bool alive;
        float seconds;
        int vieti, gloante;
        float score;
        
    };
}   // namespace m1
