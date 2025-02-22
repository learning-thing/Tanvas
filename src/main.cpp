#include <iostream>
#include "raylib.h"
#include "vec2.hpp"
#include "draws.hpp"

int main(int argc, char *argv[]) {
    std::cout << "hello world\n";
    std::string str = "canvas.txt";
    Canvas tc;
    
    InitWindow(1080, 720, "Tanvas");
    
    SetWindowState(FLAG_WINDOW_RESIZABLE);
    SetWindowState(FLAG_VSYNC_HINT);

    while (!WindowShouldClose()) {//main loop
        BeginDrawing();
            ClearBackground(BLACK);

            tc.update();
            DrawFPS(10, 10); 
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
