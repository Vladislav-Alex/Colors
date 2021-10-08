#include "moverecorder.h"

MoveRecorder::MoveRecorder()
{

}

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

//int &MoveRecorder::top()
//{
////    if (!m_moveRecorder.empty())
//    //        return m_moveRecorder.top().count;
//}

int MoveRecorder::size()
{
    return m_moveRecorder.size();
}
