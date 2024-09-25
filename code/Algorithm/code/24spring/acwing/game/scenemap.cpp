#include "scenemap.h"



Path Scenemap::getPath(int type){
    for (auto& p : allPath) {
        if (p.getType() == type) {
            return p;
        }
    }
    Path emptyPath;
    return emptyPath;
}
void Scenemap::printRTable(){
    std::cout << "RTable:" << std::endl;
    for (const auto& pair : RTable) {
        std::cout << "(" << pair.first << ", " << pair.second << ")" << std::endl;
    }    
}

void Path::print(){
    std::cout << "Path type: " << type << std::endl;
    
    for (const auto& coord : path) {
        std::cout << "(" << coord.x << ", " << coord.y << ") ";
        switch (coord.d) {
            case Direction::up:
                std::cout << "UP";
                break;
            case Direction::down:
                std::cout << "DOWN";
                break;
            case Direction::left:
                std::cout << "LEFT";
                break;
            case Direction::right:
                std::cout << "RIGHT";
                break;
            default:
                std::cout << "UNKNOWN";
        }
        std::cout << "  ";
    }            
    std::cout << std::endl;        
}
void Path::addInCoordinate(int x, int y, Direction d){
    Coordinate coo;
    coo.x = x;
    coo.y = y;
    coo.d = d;
    path.push_back(coo);
    
}