#ifndef _CIRCULAR_LINKED_LIST_H_
#define _CIRCULAR_LINKED_LIST_H_
#include <vector>

using namespace std;

template <class T>
class CircularLinkedList
{
private:
    vector<T> list;
    int position;
public:

    CircularLinkedList() : position(0) {};

    ~CircularLinkedList(void) {};

    void add(const T &value)
    {
        this->list.push_back(value);
    };


    T getCurrent()
    {
        T &result = this->list.at(this->position);
        return result;
    };

    T next()
    {
        this->position++;
        if (this->position >= (int) this->list.size())
        {
            this->position = 0;
        }

        return getCurrent();
    };

    int size()
    {
        return list.size();
    }

    int getPos()
    {
        return position;
    }

    vector<T> getVector()
    {
        return list;
    }
};

#endif