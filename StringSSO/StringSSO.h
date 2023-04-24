#pragma once
#include <iostream>

class StringSSO
{
    static const unsigned SMALL_STRING_MAX_SIZE = 25;

    private:
        char* data = nullptr;
        size_t count;
        size_t capacity;
        
    public:
        StringSSO();
        StringSSO(const char* string);
    ~StringSSO();
};