#include "cycle.h"

A::A(int s) {
    size = s;
    nodelist = new node[s]();
    for (int i = 0; i < s; i++)
        nodelist[i].num = i;
}

bool A::AddPath(int r, int c) {
    for (int i = 0; i < PathGroup.size(); i++) {
        if (PathGroup[i].row == c);
        if (PathGroup[i].column == r);
    }

}

bool A::RemovePath(int, int) {

}
