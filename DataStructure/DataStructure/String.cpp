#include "String.h"

String::String()
{
    m_data = new char[m_capacity];
}

String::~String()
{
    delete[] m_data;
}

String & String::operator<<(char c)
{
    m_data[m_length++] = c;
    return *this;
}

int naiveSearch(CSREF(str), CSREF(pattern))
{
    int i = 0, j = 0, k = i;
    while (i < str.length() && j < pattern.length())
    {
        if (str[i] == pattern[j])
        {
            ++i;
            ++j;
        }
        else
        {
            j = 0;
            i = ++k;
        }
    }
    if (j >= pattern.length())
        return k;
    return -1;
}

int kmp(CSREF(str), CSREF(pattern), int next[])
{
    int i = 0, j = 0;
    int sl = str.length();
    int pl = pattern.length();
    while (i < sl && j < pl)
    {
        if (j == -1 || str[i] == pattern[j])
        {
            ++i; ++j;
        }
        else
        {
            j = next[j];
        }
    }
    if (j >= pattern.length())
        return i - pattern.length();
    return -1;
}

int getNext(CSREF(pattern), int next[])
{
    int i = 0, j = -1;
    next[0] = -1;
    while (i < pattern.length())
    {
        if (j == -1 || pattern[i] == pattern[j])
        {
            next[++i] = ++j;
        }
        else
        {
            j = next[j];
        }
    }
    return 0;
}

int getNextval(CSREF(pattern), int nextval[])
{
    auto a = nextval;
    int i = 0, j = -1;
    nextval[0] = -1;
    while (i < pattern.length())
    {
        if (j == -1 || pattern[i] == pattern[j])
        {
            ++i; ++j;
            if (pattern[i] != pattern[j])
                nextval[i] = j;
            else
                nextval[i] = nextval[j];
        }
        else
        {
            j = nextval[j];
        }
    }
    return 0;
}
