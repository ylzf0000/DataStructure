#pragma once
#include <string>
class String
{
public:
    String();
    ~String();
    String &operator<<(char c);
    int Length() const { return m_length; }
    int Capacity() const { return m_capacity; }
private:
    char *m_data;
    int m_length = 0;
    int m_capacity = 1000;
};

#define CSREF(x) const std::string &x

// return -1 means the search fails.
int naiveSearch(CSREF(str), CSREF(pattern));
int kmp(CSREF(str), CSREF(pattern), int next[]);
int getNext(CSREF(pattern), int next[]);
int getNextval(CSREF(pattern), int nextval[]);