
#include "utils.hpp"

auto l(auto a, auto b){ 
    if (a<b) {return a;}
    else {return b;}
}

std::vector<std::vector<int>> string_to_vector(std::string string_to_convert){

    std::vector<std::vector<int>> letters;
    std::vector<int> letter;
    for (size_t i = 0; i < string_to_convert.length(); i++)
    {   
        letter.push_back(string_to_convert[i]);
        if ((string_to_convert[i] & 0xC0) == 0x80){
            letters.push_back(letter);
            letter.clear();
        }
        if (string_to_convert[i]>0){
            letters.push_back(letter);
            letter.clear();
        }
    }
    return letters;

}

int find_name_first_letter(std::vector<Object> objects,std::vector<int> letter_to_look){
    int max_size_of_letter = 2;
    std::vector<int> first_letter;
    for (size_t m = 0; m < objects.size(); m++)
    {
        first_letter.clear();
        for (size_t i = 0; i < max_size_of_letter; i++)
            {   
                first_letter.push_back(objects.at(m).name[i]);
                if ((objects.at(m).name[i] & 0xC0) == 0x80){break;}
                if (objects.at(m).name[i]>0){break;}
            }
        if (first_letter == letter_to_look){
            return m;
        }
    }
    return -1;
}

int find_type_itr(std::vector<Object> objects,std::string type_to_look, int * type_counter){
    bool trigger = false;
    int return_val = -1;
    for (size_t i = 0; i < objects.size(); i++){
        if (objects.at(i).type==type_to_look && !trigger){
            trigger = true;
            return_val = i;
        }
        else if (objects.at(i).type!=type_to_look){
            trigger = false;}
        if (trigger==true) *type_counter += 1 ;
    }
    return return_val;
}

bool compareDistance(Object o1, Object o2){
    return (o1.distance<o2.distance);
}

bool compareSortingCounter(Object o1, Object o2){
    return (o1.sorting_counter<o2.sorting_counter);
}

bool compareTime(Object o1, Object o2){
    return (o1.timestamp>o2.timestamp);
}

bool compare_strings(std::string s1, std::string s2){
    int size = l(s1.length(),s2.length());
    int l1,l2;
    for (size_t i = 0; i < size; i++){
        if (s1[i]!=s2[i]){
            if (i>0){
                if (int(s1[i])==-127 && int(s1[i-1]==-48))
                    return (float(s1[i])+20.5<float(s2[i])); // работа с буквой Ё
                if (int(s1[i])==-111&&int(s1[i-1]==-47))
                    return (float(s1[i])+36.5<float(s2[i])); // работа с буквой ё
                if (int(s2[i])==-127&&int(s2[i-1]==-48))
                    return (float(s1[i])<float(s2[i])+20.5); // работа с буквой Ё
                if (int(s2[i])==-111&&int(s2[i-1]==-47))
                    return (float(s1[i])<float(s2[i])+36.5); // работа с буквой ё
            }
            l1 = int(s1[i]);
            l2 = int(s2[i]);
            return (s1[i]<s2[i]);
        }
    }
    return (s1.length()<s2.length());
}

bool compareAlpha_name(Object o1, Object o2){
    return compare_strings(o1.name,o2.name);
}

bool compareAlpha_type(Object o1, Object o2){
    if (o1.sorting_counter==o2.sorting_counter){
        return compare_strings(o1.type,o2.type);
    }
    else {
        return (o1.sorting_counter<o2.sorting_counter);
    }
}
    
