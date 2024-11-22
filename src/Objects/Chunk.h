#ifndef CHUNK_H
#define CHUNK_H

#include "Cube.h"
#include <functional>
#include <tuple>
#include <unordered_set>
#include <vector>

struct GridKey {
    int x, y, z;

    // Equality operator for GridKey
    bool operator==(const GridKey& other) const
    {
        return x == other.x && y == other.y && z == other.z;
    }
};

namespace std {
template <>
struct hash<GridKey> {
    std::size_t operator()(const GridKey& key) const
    {
        return std::hash<int>()(key.x) ^ (std::hash<int>()(key.y) << 1) ^ (std::hash<int>()(key.z) << 2);
    }
};
}

class Chunk {
private:
    enum FaceType {
        FRONT_FACE,
        BACK_FACE,
        LEFT_FACE,
        RIGHT_FACE,
        TOP_FACE,
        BOTTOM_FACE
    };
    std::unordered_set<GridKey> grid;

public:
    std::vector<float> vertices;
    std::vector<unsigned int> indices;
    Chunk();
    bool isNeighborPresent(int x, int y, int z);
    void addFace(const Cube& cube, int x, int y, int z, FaceType faceType);
};

#endif
