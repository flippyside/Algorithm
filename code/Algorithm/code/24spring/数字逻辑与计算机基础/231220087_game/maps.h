#ifndef MAPS_H
#define MAPS_H
#include <memory>
class Path;
class Scenemap;

// stage 0
std::shared_ptr<Path> createDefaultPath0();
std::shared_ptr<Scenemap> createDefaultMap0();

// stage 1
std::shared_ptr<Path> linePath0();
std::shared_ptr<Path>linePath1();
std::shared_ptr<Path>linePath2();

// stage 2
std::shared_ptr<Scenemap> createDefaultMap1();
std::shared_ptr<Path> createDefaultPath2();
std::shared_ptr<Path> createDefaultPath1();
std::shared_ptr<Scenemap> createDefaultMap2();



#endif
