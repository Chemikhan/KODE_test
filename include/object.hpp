#ifndef OBJECT
#define OBJECT

#include <string>

struct Object
{
    std::string name = "";
    float x_coord = 0;
    float y_coord = 0;
    float distance = 0;
    std::string type = "";
    time_t timestamp = 0;
    int sorting_counter = 0;
};

#endif
