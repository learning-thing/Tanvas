#pragma once
#include <raylib.h>
#include <vector>
#include <math.h>
#include <string>
#include <fstream>
#include <iostream>
#include <vec2.hpp>

class DataLoader {
    private:
        std::string filename;
        std::string line;
        int lineIndex = 0;
        u_int charpos = 0;
        u_int valIndex = 0;
        char curr_char;
        float vvals[4];
        std::string ts;

    public:
        std::vector<vec2> vecs;
        std::vector<float> timestamps;
        DataLoader(std::string fileName)  : filename(fileName) {
            
        }
        
        DataLoader() {};

        int load() {//Read form the file
            std::clog << "Trying to open: " << filename << "\n";
            std::ifstream data(filename.c_str());
            if (!data.is_open()) {
                std::cerr << "error opening " << filename << "\n";
                return 1;
            }
            while (getline(data, line)) {//Parse every line
                std::clog << lineIndex << " Line: " << line << "\n";
                if (lineIndex==0) {
                    lineIndex++;
                    continue;
                }
                charpos = 0;//reset char position to 0 at the new line
                valIndex = 0;
                bool first_neg = (line[0] == '-');
                for (int i = 0; i < line.length(); i++) {//
                    charpos++;
                    curr_char = line[charpos];
                    if (curr_char==',' || i==line.length()-1) {
                        vvals[valIndex] = strtof(ts.c_str(), 0);
                        valIndex++;//next time, next value
                        ts = "";//reset temporary string
                        continue;
                    }

                    ts.append(1, curr_char);
                }

                std::clog << "read: " << charpos << ": " << vvals[0] << " "  <<  vvals[1] << " ";
                if (first_neg)
                    vecs.push_back( vec2(-vvals[0], vvals[1]) );
                else {
                    vecs.push_back( vec2(vvals[0], vvals[1]) );
                }

                lineIndex++;
            }
            //after parsing a line
            data.close();
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
            std::ofstream outputFile(filename);
            for (int i = 0; i < vecs.size(); i++) {
                outputFile << vecs[i].x();
                outputFile << ",";
                outputFile << vecs[i].y();
                outputFile << "\n";
            }
            outputFile.close();
            return 0;
        }
};

