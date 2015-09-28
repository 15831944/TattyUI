#ifndef FCQUADTREE_H
#define FCQUADTREE_H

#include <vector>
#include <TattyUI/test/fangcun/fcRectangle.h>

enum fcQuadTreeMax
{
    FC_QUADTREE_MAX_OBJECTS = 10,
    FC_QUADTREE_MAX_DEPTH = 5
};

enum fcQuadSubNode
{
    FC_TOP_RIGHT = 0,
    FC_TOP_LEFT = 1,
    FC_BOTTOM_LEFT = 2,
    FC_BOTTOM_RIGHT = 3,

    FC_PARENT = -1
};

// �����
// --!http://gamedevelopment.tutsplus.com/tutorials/quick-tip-use-quadtrees-to-detect-likely-collisions-in-2d-space--gamedev-374
class fcRay;
class fcCircle;
class fcQuadTree
{
public:
    fcQuadTree(int depth, fcRectangle bounds);

    void clear();

    void split();

    int getIndex(fcCircle* circle);

    void insert(fcCircle* circle);

    // ��circles�д�ż������Ķ���
    void retrieve(std::vector<fcCircle*>& circles, fcRay* ray);

    // ��ǰ���
    int depth;
    // ָ���ĸ��ӽڵ��ָ������
    std::vector<fcQuadTree*> nodes;
    // ���߽�
    fcRectangle bounds;
    // ��ǰ����������
    std::vector<fcCircle*> objects;
};

#endif