#pragma once
#include <vec2.hpp>
#include <EASTL/vector.h>
#include "loadSave.hpp"

class point {
    public:
        vec2 pos = vec2(100);
        float size = 10;
        bool connected;
        point(vec2 startpos, bool connected_to_last) : pos(startpos), connected(connected_to_last) {

        }
};

class Canvas {
    private:
        eastl::vector<point> points;
        vec2 winDimensions = vec2(1080, 720);
        DataLoader dl;
        vec2 dragstart;
        vec2 pos = winDimensions/2;
        long double zoom = 10;
        float frameCount = 0;
        float got = 0;
        

        void draw() {//Draw the canvas
            for (int i = 0; i < points.size(); i++)  {
                Vector2 spos = (pos+points[i].pos*zoom).toRayVec();
                Vector2 epos;
                if (i<points.size()-2) {
                    epos = (pos+points[i+1].pos*zoom).toRayVec();
                    //if (points[i+1].connected && ( (points[i+1].pos-points[i].pos).length() )<=.1)
                    if (points[i+1].connected)

                        DrawLineV(spos, epos, WHITE);
                } else {
                    epos = (pos+points[i].pos*zoom).toRayVec();
                }
            }
        }
    public:
        Canvas(std::string canvasFile) {
            std::clog << "Passing canvas file: " << canvasFile << "\n";
            
        }
        void update() {
            if (IsWindowResized()) {
                winDimensions = vec2(GetScreenWidth(), GetScreenHeight());
                pos = vec2(winDimensions)/2;
                zoom = 100.0;//Reset zoom (I'm too lazy to figre out how to keep everything in place wile resizing the window)
            }
            if (IsKeyPressed(KEY_R)) {//Clear the Canvas (I should definetely add an "input()" function for readability)
                points.clear();
            }

            if (frameCount == 10) frameCount = 0;//not sure if I still need it, but some thing I wanna update at a certain amount of frames
            frameCount++;

            draw();//Call the drawing
            vec2 MouseVec = vec2(GetMouseX(), GetMouseY() );//Current mouse position
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {//add points
                point p((( MouseVec-pos   )/zoom), false);
                p.size/=zoom;
                points.push_back(p);
                
                std::clog << "Adding point\n";
                got++;
            }

            //Hold to add
            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && (((MouseVec-pos)/zoom)-points[points.size()-2].pos).length()>=.002 ) {//Add when we exceed a certain distance while holding down leftclick
                point p((( MouseVec-pos   )/zoom), true);//add a point at the position divideed by the zoom
                p.size/=zoom;
                points.push_back(p);
                
                got++;//keep track of added points
                std::clog << "Adding point: " << got << "\n";
            }

            //backwards
            if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
                if (points.size() >= 1)
                    points.pop_back();
                    
            }

            long double zoomPower = abs(zoom)*.1;//always modify zoom by 10%
            //Zoom in by step
            float scroll = GetMouseWheelMoveV().y;
            if (scroll>0) {
                pos -= (  vec2(GetMouseX(), GetMouseY()) - pos )/10;
                zoom+=zoomPower;
            }
            if (scroll<0) {
                pos += (  vec2(GetMouseX(), GetMouseY()) - pos )/10;
                if (zoom>1) {
                    zoom-=zoomPower;
                } else {
                    if (zoom>0.000001) {
                        zoom-=zoomPower;
                    }
                }
            }

            //Dragging the Canvas
            if (IsMouseButtonPressed(MOUSE_BUTTON_MIDDLE)) {//Get the position where we begin to drag
                dragstart = MouseVec;
            }


            float zoomSpeed = GetFrameTime()*40;
            if (IsKeyDown(KEY_UP)) {
                zoom+=zoomPower;
                pos -= (  vec2(GetMouseX(), GetMouseY()) - pos )/10;

            }
            if (IsKeyDown(KEY_DOWN)) {
                pos += (  vec2(GetMouseX(), GetMouseY()) - pos )/10;
                if (zoom>1) {
                    zoom-=zoomPower*zoomSpeed;
                } else {
                    if (zoom>0.0000001) {
                        zoom-=zoomPower*zoomSpeed;
                    }
                }
            }
            
        }
        Canvas() {
            
        }
        ~Canvas() {
            std::clog << "Closing canvas\n";
            
        }

        
    };

