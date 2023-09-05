#include "file_management.hpp"


std::string write_object(Object obj)
{
    std::string str;
    if (obj.x_coord==0 && obj.y_coord==0){
        str =   obj.name;
    }
    else{
        str =   obj.name + " " 
        + std::to_string(obj.x_coord)+ " " 
        + std::to_string(obj.y_coord)+ " " 
        + obj.type + " " 
        + std::to_string(obj.timestamp);
    }
    return str;
}

std::vector<Object> read_csv(std::string file_name){
    std::vector<Object> data;
    std::string line, word, temp;
    std::ifstream file;
    std::string file_addr = file_name;
    file.open(file_addr);
    int counter = 0;
    while (std::getline(file, line)) {
        std::vector<std::string> row_string;
        Object row;
        counter +=1;
        std::stringstream str(line);
        while(getline(str, word, ' '))
            row_string.push_back(word);
        row.name = row_string[0];
        row.x_coord = std::stof(row_string[1]);
        row.y_coord = std::stof(row_string[2]);
        row.type = row_string[3];
        row.timestamp = std::stof(row_string[4]);
        row.distance = std::sqrt(std::pow(row.x_coord,2)+std::pow(row.y_coord,2));
        data.push_back(row);
    }
    file.close(); 
    return data;
}

void write_csv(std::string file_name, std::vector<Object> data_to_write){
    std::ofstream file;
    std::string filename = "files/";
    filename += file_name;
    filename += ".csv";
    file.open(filename);
    for(auto content: data_to_write)
    {
        file<<write_object(content)<<std::endl;
    }
    return;
}

int interface(){
    std::string filename;
    int sorting_type,counter,min_num = 0;
    std::cout<<"Введите имя файла, содержащего данные, включая путь до него (\\folder\\file.csv)"<<std::endl;
    std::cin>>filename;
    if (filename=="1")filename = "files/file.csv";
    std::vector<Object> data = read_csv(filename);
    while (data.empty()){
        std::cout<<"Введите имя файла снова, количество попыток: "<<3-counter<<std::endl;
        std::cin>>filename;
        std::vector<Object> data = read_csv(filename);
        counter++;
        if (counter==3){
            return 0;
        }
    }
    Sorter s(data);
    std::cout<<"Введите цифру, соответствующую формату сортировки:"<<std::endl;
    std::cout<< "1-по расстоянию"<<std::endl;
    std::cout<< "2-по времени создания"<<std::endl;
    std::cout<< "3-по имени"<<std::endl;
    std::cout<< "4-по типу"<<std::endl;
    std::cin>>sorting_type;
    switch(sorting_type) {
        case 1:{
            std::vector<Object> sorted_data_by_distance = s.by_distance();
            write_csv("sorted_data_by_distance",sorted_data_by_distance);
            break;}
        case 2:{
            std::vector<Object> sorted_data_by_time = s.by_time();
            write_csv("sorted_data_by_time",sorted_data_by_time);
            break;}
        case 3:{
            std::vector<Object> sorted_data_by_name = s.by_name();
            write_csv("sorted_data_by_name",sorted_data_by_name);
            break;}
        case 4:{
             std::cout<< "Введите минимальное количество элементов для группировки"<<std::endl;
            std::cin>>min_num;
            std::vector<Object> sorted_data_by_type = s.by_type(min_num);
            write_csv("sorted_data_by_type",sorted_data_by_type);
            break;}
        default:
            std::cout<<"Не выбран ни один вариант"<<std::endl;
    }
    return 1;
}