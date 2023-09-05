#ifndef __FILE_MANAGE__
#define __FILE_MANAGE__

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <sstream>
#include <algorithm>
#include <locale>
#include "object.hpp"
#include "sorter.hpp"



std::vector<Object> read_csv(std::string file_name);
void write_csv(std::string file_name, std::vector<Object> data_to_write);
int interface();

#endif