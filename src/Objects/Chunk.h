#ifndef CHUNK_H
#define CHUNK_H

#include "Cube.h"
#include <vector>

class Chunk {
public:
    std::vector<float> vertices;
    std::vector<unsigned int> indices;

    Chunk();
    bool isCubeAt();
};

#endif
