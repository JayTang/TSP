#ifndef CYCLE_H_INCLUDED
#define CYCLE_H_INCLUDED
#include <vector>
using namespace std;
class Path {
public:
    int row, column;
    Path(int r, int c) : row(r), column(c) {}
    bool operator<(const Path& p) const {
        if (row > p.row)
            return false;
        return true;
    }
    ~Path() {}
};
class A{
private :
    class node {
    public:
        int num;
        node *pre, *next;
    };
public:
    node *nodelist;
    vector<Path> PathGroup;

    A(int);
    ~A();
    int size;
    bool AddPath(int, int);
    bool RemovePath(int, int);
};
#endif // CYCLE_H_INCLUDED
