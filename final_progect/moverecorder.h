#ifndef MOVERECORDER_H
#define MOVERECORDER_H

#include <stack>
#include <vector>
#include "field.h"

struct Point
{
    int x;
    int y;
};

struct Recorder
{
    Point point;
    Field field;
};

class MoveRecorder
{
public:
    void push(const std::vector<Recorder> &rec);
    const std::vector<Recorder> &pop();
    int size();

private:
    std::stack<std::vector<Recorder>> m_moveRecorder;
};

#endif // MOVERECORDER_H
