#include "sorter.hpp"
#include "file_management.hpp"
#include "utils.hpp"


Sorter::Sorter(std::vector<Object> raw_data){
    Sorter::raw_data = raw_data;
}

std::vector<Object> Sorter::by_distance()
{   
    std::vector<Object> sorted_by_distance = raw_data;
    Object hundred,thousand,ten_thousands,big_distance;
    hundred.name = "Расстояние от 0 для следующих строк больше: 0";
    hundred.distance = 0;
    thousand.name = "Расстояние от 0 для следующих строк больше: 100";
    thousand.distance = 100;
    ten_thousands.name = "Расстояние от 0 для следующих строк больше:1000";
    ten_thousands.distance = 1000;
    big_distance.name = "Расстояние от 0 для следующих строк больше:10000";
    big_distance.distance = 10000;
    sorted_by_distance.push_back(hundred);
    sorted_by_distance.push_back(thousand);
    sorted_by_distance.push_back(ten_thousands);
    sorted_by_distance.push_back(big_distance);
    std::sort(sorted_by_distance.begin(),sorted_by_distance.end(),compareDistance);
    return sorted_by_distance;
}

std::vector<Object> Sorter::by_time()
{  
    std::vector<Object> sorted_by_time = raw_data;
    Object today,yesterday,this_week,this_month,this_year,earlier;
    
    time_t now;
    now = time (NULL);
    struct tm * timeinfo;
    timeinfo = localtime (&now);

    today.timestamp = now;
    today.name = "Следующие строки были созданы не раньше, чем сегодня, t<"+std::to_string(today.timestamp);


    struct tm t1 = *timeinfo;
    t1.tm_sec = 0;  
    t1.tm_min = 0;
    t1.tm_hour = 0;
    yesterday.timestamp = std::mktime(&t1);
    yesterday.name = "Следующие строки были созданы не раньше, чем вчера, t<"+std::to_string(yesterday.timestamp);


    struct tm t2 = *timeinfo;
    t2.tm_sec = 0;  
    t2.tm_min = 0;
    t2.tm_hour = 0;
    t2.tm_mday -= 1;
    this_week.timestamp = std::mktime(&t2);
    this_week.name = "Следующие строки были созданы не раньше, чем на этой неделе, t<"+std::to_string(this_week.timestamp);


    struct tm t3 = *timeinfo;
    t3.tm_sec = 0;  
    t3.tm_min = 0;
    t3.tm_hour = 0;
    t3.tm_mday -= t3.tm_mday-1;
    this_month.timestamp = std::mktime(&t3);
    this_month.name = "Следующие строки были созданы не раньше, чем в этом месяце, t<"+std::to_string(this_month.timestamp);
    
    struct tm t4 = *timeinfo;
    t4.tm_sec = 0;  
    t4.tm_min = 0;
    t4.tm_hour = 0;
    t4.tm_mday = 0;
    this_year.timestamp = std::mktime(&t4);
    this_year.name = "Следующие строки были созданы не раньше, чем в этом году, t<"+std::to_string(this_year.timestamp);

    struct tm t5 = *timeinfo;
    t5.tm_sec = 0;  
    t5.tm_min = 0;
    t5.tm_hour = 0;
    t5.tm_mday = 0; 
    t5.tm_mon = 0;
    t5.tm_yday = 0;
    earlier.timestamp = std::mktime(&t5);
    earlier.name = "Следующие строки были созданы раньше, чем в этом году, t<"+std::to_string(earlier.timestamp);
    sorted_by_time.push_back(today);
    sorted_by_time.push_back(yesterday);
    sorted_by_time.push_back(this_week);
    sorted_by_time.push_back(this_month);
    sorted_by_time.push_back(this_year);
    sorted_by_time.push_back(earlier);
    std::sort(sorted_by_time.begin(),sorted_by_time.end(),compareTime);
    return sorted_by_time;
}

std::vector<Object> Sorter::by_name()
{   
    std::vector<Object> sorted_by_name = raw_data;
    std::sort(sorted_by_name.begin(),sorted_by_name.end(),compareAlpha_name);
    std::vector<std::vector<int>> Alpha_Letters = string_to_vector(AlphaNumeric_Cyrillic);
    for (size_t i = 0; i < Alpha_Letters.size(); i++){
        Object grouping_str;
        int itr = find_name_first_letter(sorted_by_name,Alpha_Letters.at(i));
        std::string ltr= "";
        ltr += Alpha_Letters.at(i)[0];
        ltr += Alpha_Letters.at(i)[1];
        if (Alpha_Letters.at(i)[0]==33)
            grouping_str.name = "## Латиница и прочие символы.";
        else
            grouping_str.name = "## Следующая буква: "+ ltr;
        if (itr!=-1){
            sorted_by_name.insert(sorted_by_name.begin()+itr, grouping_str);
        }
    }
    return sorted_by_name;
}

std::vector<Object> Sorter::by_type(int min_num)
{   
    std::vector<Object> sorted_by_type = raw_data;
    std::sort(sorted_by_type.begin(),sorted_by_type.end(),compareAlpha_type);
    std::vector<std::string> types;
    types.push_back(sorted_by_type.at(0).type);
    for (size_t i = 0; i < sorted_by_type.size(); i++)
    {
        if (sorted_by_type.at(i).type!=types.back()){
            types.push_back(sorted_by_type.at(i).type);
        }
    }
    std::for_each   (types.begin(), types.end(),
                    [&sorted_by_type,&min_num]
                    (const std::string& type){
                        int type_counter = 0;
                        int itr = find_type_itr(sorted_by_type,type,&type_counter);
                        std::for_each(sorted_by_type.begin(), sorted_by_type.end(),
                        [&type, &type_counter, & min_num](Object& obj){
                            if (obj.type==type && type_counter>=min_num) 
                                obj.sorting_counter=-1;
                            else if (obj.type==type && type_counter<=min_num)
                                obj.sorting_counter=1;
                        });
                    });
    std::sort(sorted_by_type.begin(),sorted_by_type.end(),compareAlpha_type);
    for (size_t i = 0; i < types.size(); i++)
    {
        Object grouping_str;
        int type_counter = 0;
        int itr = find_type_itr(sorted_by_type,types.at(i),&type_counter);
        if (type_counter>=min_num){
            grouping_str.name = "Группа типа: "+types.at(i)+". Количество элементов: "+std::to_string(type_counter);
            grouping_str.type = types.at(i);
            sorted_by_type.insert(sorted_by_type.begin()+itr, grouping_str);
        }
        else{
            grouping_str.name = "Группа 'прочее'. количество элементов каждого типа: меньше "+std::to_string(min_num);
            sorted_by_type.insert(sorted_by_type.begin()+itr, grouping_str);
            break;
        }
    }
    return sorted_by_type;
}
