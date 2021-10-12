#include "moverecorder.h"

void MoveRecorder::push(const std::vector<Recorder> &rec)
{
    m_moveRecorder.push(rec);
}

const std::vector<Recorder> &MoveRecorder::pop()
{
    if (!m_moveRecorder.empty())
    {
        const std::vector<Recorder> & temp = m_moveRecorder.top();
        m_moveRecorder.pop();
        return temp;
    }
}

int MoveRecorder::size()
{
    return m_moveRecorder.size();
}

//MoveRecorder::~MoveRecorder()
//{
//    m_moveRecorder.~stack();
//}
