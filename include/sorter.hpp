#ifndef __SORTER__
#define __SORTER__


#include <string>
#include <vector>
#include "object.hpp"

/**
 *  @brief A class for storing and sorting data.
 **/
class Sorter
{
private:
    std::vector<Object> raw_data;
    std::string AlphaNumeric_Cyrillic = "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЬЪЭЮЯ!";
public:
    Sorter(std::vector<Object> raw_data);
    std::vector<Object> by_distance();
    std::vector<Object> by_name();
    std::vector<Object> by_type(int min_num);
    std::vector<Object> by_time();    
};

#endif