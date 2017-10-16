#ifndef OBJECT_READER_HPP
#define OBJECT_READER_HPP

#include "Object.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>


/**
 * Given a string, splits it on the givem delimiter
 */
std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    std::stringstream ss;
    std::string item;

    ss.str(s);
    auto result = std::back_inserter(elems);
    while (std::getline(ss, item, delim)) {
        *(result++) = item;
    }
    return elems;
}

/**
 * When this code was written, only God and I understood it. Now, only God 
 * understands it.
 */
std::vector<Polygon*> read_obj_file(const std::string &path) {
    std::ifstream file(path);
    std::string line;
    std::vector<std::string> splitted;
    std::vector<Coordinate> vertices;
    std::vector<Polygon*> all_faces;

    const std::string name = split(path, '/').back();

    try {
        while (std::getline(file, line)) {
            splitted = split(line, ' ');
            if (splitted.size() == 0) {
                continue;
            } else if (splitted[0] == "f") {
                auto poly = new Polygon("Face");
                std::vector<int> face;
                std::transform(splitted.begin() + 1, splitted.end(), std::back_inserter(face),
                       [](const std::string &str) { return std::stoi(str); });

                for (auto i : face)
                    poly->add_coordinates(vertices[i-1], WORLD);
                all_faces.push_back(poly);

            } else if (splitted[0] == "v") {
                std::vector<float> point;
                std::transform(splitted.begin() + 1, splitted.end(), std::back_inserter(point),
                       [](const std::string &str) { return std::stod(str); });     

                vertices.push_back(Coordinate(point[0], point[1], point[2]));
            }
        }
    } catch (const std::out_of_range &o) {
        return {};
    }
    return all_faces;
}

#endif // OBJECT_READER_HPP
