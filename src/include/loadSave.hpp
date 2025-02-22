#pragma once
#include <raylib.h>
#include <EASTL/vector.h>
#include <math.h>
#include <string>
#include <fstream>
#include <iostream>
#include <vec2.hpp>
#include <sstream>

/*Completely broken right now, ignore*/

class DataLoader {
    private:
        std::string filename = "canvas.txt";
        std::string line;
        int lineIndex = 0;
        u_int charpos = 0;
        u_int valIndex = 0;
        char curr_char;
        float vvals[4];
        std::string ts;

    public:
        eastl::vector<vec2> vecs;
        eastl::vector<float> timestamps;
        DataLoader(std::string fileName)  : filename(fileName) {
            
        }
        
        DataLoader() {};

        int load() {//Read form the file
            return 0;
        }

        int clear() {
            std::ofstream outputFile(filename);
            outputFile << "0.0,0.0\n";
            vecs.clear();
            outputFile.close();
            return 0;
        }

        int save() {
            std::clog << "Saving data\n";
            std::ofstream file(filename);
            if (!file.is_open()) {
                std::cerr << "Failed to open file: " << filename << std::endl;
                return -1;
            }
        
            for (const auto& vec : vecs) {
                file << vec.x() << "," << vec.y() << "\n";
            }
        
            file.close();
            return 0;
        }
};

