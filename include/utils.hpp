#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <bits/stdc++.h>
#include "object.hpp"




/**
 *  @brief A function to convert strings to vector of ints to make it easier to compare
 * different strings with UTF-8 coding.
 **/
std::vector<std::vector<int>> string_to_vector(std::string string_to_convert);

/**
 *  @brief A function to find the first element of the vector with the first letter 
 * which is equal to the searching letter (in a form of vector of ints).
 **/
int find_name_first_letter(std::vector<Object> objects,std::vector<int> letter_to_look);

/**
 *  @brief A function to find the first element of the vector with the type 
 * which is equal to the searching type.
 **/
int find_type_itr(std::vector<Object> objects,std::string type_to_look, int * type_counter);

/**
 *  @brief A function to compare distance between two objects.
 **/
bool compareDistance(Object o1, Object o2);

bool compareSortingCounter(Object o1, Object o2);

/**
 *  @brief A function to compare creation time between two objects.
 **/
bool compareTime(Object o1, Object o2);

/**
 *  @brief A function to compare two string.
 **/
bool compare_strings(std::string s1, std::string s2);

/**
 *  @brief A function to compare names of two objects.
 **/
bool compareAlpha_name(Object o1, Object o2);

/**
 *  @brief A function to compare types of two objects.
 **/
bool compareAlpha_type(Object o1, Object o2);
