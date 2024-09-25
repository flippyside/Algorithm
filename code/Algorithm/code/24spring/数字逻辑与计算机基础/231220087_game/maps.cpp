#include "maps.h"
#include "Basic/scenemap.h"



// stage 0
std::shared_ptr<Path> createDefaultPath0(){
    auto path0 = std::make_shared<Path>(0);
    path0->addInCoordinate_rel(0,0,Direction::down);
    path0->addInCoordinate_rel(1,0,Direction::right);
    path0->addInCoordinate_rel(1,1,Direction::right);
    path0->addInCoordinate_rel(1,2,Direction::right);
    path0->addInCoordinate_rel(1,3,Direction::right);
    path0->addInCoordinate_rel(1,4,Direction::down);
    path0->addInCoordinate_rel(2,4,Direction::down);
    path0->addInCoordinate_rel(3,4,Direction::down);
    path0->addInCoordinate_rel(4,4,Direction::right);
    path0->addInCoordinate_rel(4,5,Direction::right);
    path0->addInCoordinate_rel(4,6,Direction::right);
    path0->addInCoordinate_rel(4,7,Direction::right);
    path0->addInCoordinate_rel(4,8,Direction::right);
    path0->addInCoordinate_rel(4,9,Direction::right);
    path0->addInCoordinate_rel(4,10,Direction::right);
    path0->addInCoordinate_rel(4,11,Direction::down);
    path0->addInCoordinate_rel(5,11,Direction::down);
    path0->addInCoordinate_rel(6,11,Direction::down);
    path0->addInCoordinate_rel(7,11,Direction::down);
    path0->addInCoordinate_rel(8,11,Direction::down);
    path0->addInCoordinate_rel(9,11,Direction::right);
    path0->addInCoordinate_rel(9,12,Direction::right);
    path0->addInCoordinate_rel(9,13,Direction::right);
    path0->addInCoordinate_rel(9,14,Direction::right);

    return path0;
}
std::shared_ptr<Scenemap> createDefaultMap0(){
    Path p = *createDefaultPath0();
    p.setType(0);
    auto map = std::make_shared<Scenemap>();
    map->addPath(p);
    map->addRTable(0, 1);
    map->addRTable(0, 2);
    map->addRTable(0, 3);
    map->addRTable(0, 4);
    map->addRTable(0, 5);
    map->addRTable(1, 5);
    map->addRTable(2, 5);
    map->addRTable(3, 5);
    map->addRTable(3, 6);
    map->addRTable(3, 7);
    map->addRTable(3, 8);
    map->addRTable(3, 9);
    map->addRTable(3, 10);
    map->addRTable(3, 11);
    map->addRTable(3, 12);
    map->addRTable(4, 12);
    map->addRTable(5, 12);
    map->addRTable(6, 12);
    map->addRTable(7, 12);
    map->addRTable(8, 12);
    map->addRTable(8, 13);
    map->addRTable(8, 14);
    map->addRTable(2, 0);
    map->addRTable(2, 1);
    map->addRTable(2, 2);
    map->addRTable(2, 3);
    map->addRTable(3, 3);
    map->addRTable(4, 3);
    map->addRTable(5, 3);
    map->addRTable(5, 4);
    map->addRTable(5, 5);
    map->addRTable(5, 6);
    map->addRTable(5, 7);
    map->addRTable(5, 8);
    map->addRTable(5, 9);
    map->addRTable(5, 10);
    map->addRTable(6, 10);
    map->addRTable(7, 10);
    map->addRTable(8, 10);
    map->addRTable(9, 10);

    return map;
}

// stage 1
std::shared_ptr<Path> linePath0(){
    auto path0 = std::make_shared<Path>(0);
    for (int y = 0; y <= 14; ++y) {
        path0->addInCoordinate_rel(1, y, Direction::right);
    }
    return path0;
}
std::shared_ptr<Path>linePath1(){
    auto path0 = std::make_shared<Path>(0);
    for (int y = 0; y <= 14; ++y) {
        path0->addInCoordinate_rel(4, y, Direction::right);
    }
    return path0;
}
std::shared_ptr<Path>linePath2(){
    auto path0 = std::make_shared<Path>(0);
    for (int y = 0; y <= 14; ++y) {
        path0->addInCoordinate_rel(8, y, Direction::right);
    }
    return path0;
}
std::shared_ptr<Scenemap> createDefaultMap1(){

    Path p0 = *linePath0();
    Path p1 = *linePath1();
    Path p2 = *linePath2();
    p0.setType(0);
    //p1.setType(1);
    p2.setType(1);

    auto map = std::make_shared<Scenemap>();
    map->addPath(p0);
    //map->addPath(p1);
    map->addPath(p2);

    for(int y = 0; y <= 14; y++){
        map->addRTable(0, y);
         map->addRTable(2, y);
        // map->addRTable(3, y);
        //  map->addRTable(5, y);
        map->addRTable(7, y);
         map->addRTable(9, y);
    }
    return map;
}

// stage 2
std::shared_ptr<Path> createDefaultPath2(){
    auto p = std::make_shared<Path>(0);
    p->addInCoordinate_rel(0,0,Direction::down);
    p->addInCoordinate_rel(1,0,Direction::down);
    p->addInCoordinate_rel(2,0,Direction::down);
    p->addInCoordinate_rel(3,0,Direction::down);
    p->addInCoordinate_rel(4,0,Direction::down);
    p->addInCoordinate_rel(5,0,Direction::down);
    p->addInCoordinate_rel(6,0,Direction::right);
    p->addInCoordinate_rel(6,1,Direction::right);
    p->addInCoordinate_rel(6,2,Direction::right);
    p->addInCoordinate_rel(6,3,Direction::down);
    p->addInCoordinate_rel(7,3,Direction::down);
    p->addInCoordinate_rel(8,3,Direction::down);
    p->addInCoordinate_rel(9,3,Direction::right);
    p->addInCoordinate_rel(9,4,Direction::right);
    p->addInCoordinate_rel(9,5,Direction::right);
    p->addInCoordinate_rel(9,6,Direction::right);
    p->addInCoordinate_rel(9,7,Direction::right);
    p->addInCoordinate_rel(9,8,Direction::right);
    p->addInCoordinate_rel(9,9,Direction::right);
    p->addInCoordinate_rel(9,10,Direction::right);
    p->addInCoordinate_rel(9,11,Direction::right);
    p->addInCoordinate_rel(9,12,Direction::right);
    p->addInCoordinate_rel(9,13,Direction::up);
    p->addInCoordinate_rel(8,13,Direction::up);
    p->addInCoordinate_rel(7,13,Direction::up);
    p->addInCoordinate_rel(6,13,Direction::right);
    p->addInCoordinate_rel(6,14,Direction::right);
    p->addInCoordinate_rel(6,15,Direction::right);
    p->addInCoordinate_rel(6,16,Direction::right);
    p->addInCoordinate_rel(6,17,Direction::right);
    p->addInCoordinate_rel(6,18,Direction::down);
    p->addInCoordinate_rel(7,18,Direction::down);
    p->addInCoordinate_rel(8,18,Direction::down);
    p->addInCoordinate_rel(9,18,Direction::down);
    p->addInCoordinate_rel(10,18,Direction::down);
    p->addInCoordinate_rel(11,18,Direction::down);
    p->addInCoordinate_rel(12,18,Direction::down);
    p->addInCoordinate_rel(13,18,Direction::down);
    p->addInCoordinate_rel(14,18,Direction::right);
    p->addInCoordinate_rel(14,19,Direction::right);

    return p;
}
std::shared_ptr<Path> createDefaultPath1(){
    auto p = std::make_shared<Path>(0);
    p->addInCoordinate_rel(0,0,Direction::right);
    p->addInCoordinate_rel(0,1,Direction::right);
    p->addInCoordinate_rel(0,2,Direction::right);
    p->addInCoordinate_rel(0,3,Direction::right);
    p->addInCoordinate_rel(0,4,Direction::right);
    p->addInCoordinate_rel(0,5,Direction::right);
    p->addInCoordinate_rel(0,6,Direction::down);
    p->addInCoordinate_rel(1,6,Direction::down);
    p->addInCoordinate_rel(2,6,Direction::down);
    p->addInCoordinate_rel(3,6,Direction::down);
    p->addInCoordinate_rel(4,6,Direction::down);
    p->addInCoordinate_rel(5,6,Direction::down);
    p->addInCoordinate_rel(6,6,Direction::down);
    p->addInCoordinate_rel(7,6,Direction::down);
    p->addInCoordinate_rel(8,6,Direction::down);
    p->addInCoordinate_rel(9,6,Direction::down);
    p->addInCoordinate_rel(10,6,Direction::down);
    p->addInCoordinate_rel(11,6,Direction::down);
    p->addInCoordinate_rel(12,6,Direction::right);
    p->addInCoordinate_rel(12,7,Direction::right);
    p->addInCoordinate_rel(12,8,Direction::right);
    p->addInCoordinate_rel(12,9,Direction::right);
    p->addInCoordinate_rel(12,10,Direction::right);
    p->addInCoordinate_rel(12,11,Direction::up);
    p->addInCoordinate_rel(11,11,Direction::up);
    p->addInCoordinate_rel(10,11,Direction::up);
    p->addInCoordinate_rel(9,11,Direction::up);
    p->addInCoordinate_rel(8,11,Direction::up);
    p->addInCoordinate_rel(7,11,Direction::up);
    p->addInCoordinate_rel(6,11,Direction::up);
    p->addInCoordinate_rel(5,11,Direction::up);
    p->addInCoordinate_rel(4,11,Direction::up);
    p->addInCoordinate_rel(3,11,Direction::right);
    p->addInCoordinate_rel(3,12,Direction::right);
    p->addInCoordinate_rel(3,13,Direction::right);
    p->addInCoordinate_rel(3,14,Direction::right);
    p->addInCoordinate_rel(3,15,Direction::right);
    p->addInCoordinate_rel(3,16,Direction::down);
    p->addInCoordinate_rel(4,16,Direction::down);
    p->addInCoordinate_rel(5,16,Direction::down);
    p->addInCoordinate_rel(6,16,Direction::down);
    p->addInCoordinate_rel(7,16,Direction::down);
    p->addInCoordinate_rel(8,16,Direction::down);
    p->addInCoordinate_rel(9,16,Direction::down);
    p->addInCoordinate_rel(10,16,Direction::down);
    p->addInCoordinate_rel(11,16,Direction::right);
    p->addInCoordinate_rel(11,17,Direction::right);
    p->addInCoordinate_rel(11,18,Direction::down);
    p->addInCoordinate_rel(12,18,Direction::down);
    p->addInCoordinate_rel(13,18,Direction::down);
    p->addInCoordinate_rel(14,18,Direction::right);
    p->addInCoordinate_rel(14,19,Direction::right);
    return p;
}
std::shared_ptr<Scenemap> createDefaultMap2(){
    Path p1 = *createDefaultPath1();
    Path p2 = *createDefaultPath1();

    p1.setType(0);
    p2.setType(1);

    auto map = std::make_shared<Scenemap>(20,15,50);
    map->addPath(p1);
    map->addPath(p2);
    map->addRTable(1, 1);
    map->addRTable(1, 2);
    map->addRTable(1, 3);
    map->addRTable(1, 4);
    map->addRTable(1, 5);
    map->addRTable(2, 5);
    map->addRTable(3, 5);
    map->addRTable(4, 5);
    map->addRTable(5, 5);
    map->addRTable(6, 5);
    map->addRTable(7, 5);
    map->addRTable(8, 5);
    map->addRTable(2, 1);
    map->addRTable(3, 1);
    map->addRTable(4, 1);
    map->addRTable(4, 2);
    map->addRTable(4, 3);
    map->addRTable(4, 4);
    map->addRTable(5, 4);
    map->addRTable(6, 4);
    map->addRTable(7, 4);
    map->addRTable(8, 4);
    map->addRTable(7, 0);
    map->addRTable(7, 1);
    map->addRTable(7, 2);
    map->addRTable(7, 3);
    map->addRTable(8, 3);
    map->addRTable(9, 3);
    map->addRTable(10, 3);
    map->addRTable(10, 4);
    map->addRTable(10, 5);
    map->addRTable(11, 5);
    map->addRTable(12, 5);
    map->addRTable(13, 5);
    map->addRTable(13, 6);
    map->addRTable(13, 7);
    map->addRTable(13, 8);
    map->addRTable(13, 9);
    map->addRTable(13, 10);
    map->addRTable(13, 11);
    map->addRTable(10, 7);
    map->addRTable(10, 8);
    map->addRTable(10, 9);
    map->addRTable(10, 10);
    map->addRTable(7, 7);
    map->addRTable(7, 8);
    map->addRTable(7, 9);
    map->addRTable(7, 10);
    map->addRTable(6, 10);
    map->addRTable(5, 10);
    map->addRTable(4, 10);
    map->addRTable(3, 10);
    map->addRTable(2, 11);
    map->addRTable(2, 12);
    map->addRTable(2, 13);
    map->addRTable(2, 14);
    map->addRTable(2, 15);
    map->addRTable(4, 12);
    map->addRTable(5, 12);
    map->addRTable(6, 12);
    map->addRTable(7, 12);
    map->addRTable(4, 15);
    map->addRTable(4, 13);
    map->addRTable(4, 14);
    map->addRTable(10, 12);
    map->addRTable(11, 12);
    map->addRTable(12, 12);
    map->addRTable(10, 13);
    map->addRTable(10, 14);
    map->addRTable(9, 14);
    map->addRTable(8, 14);
    map->addRTable(7, 14);
    map->addRTable(7, 15);
    map->addRTable(8, 15);
    map->addRTable(9, 15);
    map->addRTable(10, 15);
    map->addRTable(11, 15);
    map->addRTable(12, 15);
    map->addRTable(12, 16);
    map->addRTable(12, 17);
    map->addRTable(13, 17);
    map->addRTable(14, 17);
    map->addRTable(7, 17);
    map->addRTable(8, 17);
    map->addRTable(9, 17);
    map->addRTable(10, 17);
    map->addRTable(5, 17);
    map->addRTable(5, 18);
    map->addRTable(5, 19);
    map->addRTable(6, 19);
    map->addRTable(7, 19);
    map->addRTable(8, 19);
    map->addRTable(9, 19);
    map->addRTable(10, 19);
    map->addRTable(11, 19);
    map->addRTable(12, 19);
    map->addRTable(13, 19);


    return map;
}







