#ifndef RUNNER_CAMERA_H
#define RUNNER_CAMERA_H

#include "GC-simple-render/Camera.h"

namespace sr
{
    class Window;
    class Geometry;
    class Text;
}

namespace run
{
    class LevelGenerator;
    class Background;
    class BoundaryCage;
    
    class Camera : public sr::Camera
    {
    public :
        Camera(sr::CameraType type) : sr::Camera(type) {}
        
        static void Draw(sr::Window* pWindow, sr::Geometry* geometry);
        static void Draw(sr::Window* pWindow, sr::Text* text);
        static void Draw(sr::Window* pWindow, run::LevelGenerator* pLevelGenerator);
        static void Draw(sr::Window* pWindow, run::Background* pBackground);
        static void Draw(sr::Window* pWindow, run::BoundaryCage* pBoundaryCage);
    };

}

#endif