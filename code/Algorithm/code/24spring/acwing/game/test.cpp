#include <iostream>     // 输入输出流
#include <iomanip>      // 输入输出格式控制
#include <fstream>      // 文件输入输出流
#include <vector>       // 向量容器
#include <list>         // 链表容器
#include <map>          // 映射容器
#include <vector>
#include <unordered_map>
#include "scenemap.h"

using namespace std;

int main(){
    Scenemap m;
    Path p(1);
    
    p.addCoordinate(0,0,Direction::down);
    p.addCoordinate(1,0,Direction::down);
    p.addCoordinate(2,0,Direction::right);
    p.addCoordinate(2,1,Direction::right);
    p.addCoordinate(2,2,Direction::right);
    p.addCoordinate(2,3,Direction::down);
    p.addCoordinate(3,3,Direction::down);
    p.addCoordinate(4,3,Direction::down);
    p.addCoordinate(5,3,Direction::down);

    m.addPath(p);
    m.addRTable(1,1);
    m.addRTable(1,2);
    m.addRTable(1,3);
    m.printRTable();

    Path tmp = m.getPath(2);
    tmp.print();

}