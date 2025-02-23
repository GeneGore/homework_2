#include <iostream>
#include <stdexcept>
#include <sstream>
#include <vector>
#include <array>
#include <algorithm>
#include <iterator>
#include <cstdint>

using namespace std;

class my{

    using vecIP = std::vector<uint8_t>;

    std::vector<vecIP> IPs_vec;

    vecIP parseVecIp(const std::string& ip_str){
        vecIP vec;
        std::istringstream iss(ip_str);
        std::string token;

        while (std::getline(iss, token, '.')){
            vec.push_back(std::stoi(token));
        }
        return vec;
    }

    void printOneAddress(const vecIP& ip){

        if (ip.size() != 4)
            throw std::length_error("Broken IP address!");

        for(const uint8_t& val : ip)
            std::cout<<static_cast<int>(val)<<"\t";

        std::cout<<std::endl;
    }

    bool checkOneOktet(const vecIP& address, uint8_t val, size_t pos){

        if (pos >= address.size())
            throw std::out_of_range("Out of range!");

        return address[pos] == val;
    }

public:
    void run(){

//        std::cout<<"Initial list:"<<std::endl;

        std::string line;

        while (std::getline(std::cin, line)) {

            std::istringstream lineStream(line);
            std::string ip_str;

            std::getline(lineStream, ip_str, '\t');
            IPs_vec.push_back(parseVecIp(ip_str));

//            std::cout<<"my line "<<ip_str<<std::endl;
        }

        auto lambdaCompare = [](const vecIP& vec_l, const vecIP& vec_r){

            uint32_t value_left{0}, value_right{0};
            uint32_t mask;

            for(int i=0; i<4; ++i){

                mask = vec_l[i];
                value_left |= mask<<8*(3-i);

                mask = vec_r[i];
                value_right |= mask<<8*(3-i);
            }

            return value_left > value_right;
        };


        std::sort(IPs_vec.begin(), IPs_vec.end(), lambdaCompare);

//        std::cout<<"----------------sorted--------------------"<<std::endl;
        for(const vecIP& ip : IPs_vec)
            printOneAddress(ip);

//        std::cout<<"----------------1.X.X.X--------------------"<<std::endl;
        for(const vecIP& ip : IPs_vec){

            if(checkOneOktet(ip, 1, 0))
                printOneAddress(ip);
        }

//        std::cout<<"----------------46.70.X.X--------------------"<<std::endl;
        for(const vecIP& ip : IPs_vec){

            if(checkOneOktet(ip, 46, 0) && checkOneOktet(ip, 70, 1))
                printOneAddress(ip);
        }

//        std::cout<<"----------------46.46.46.46--------------------"<<std::endl;
        bool bGotcha;
        for(const vecIP& ip : IPs_vec){

            bGotcha = false;
            for(int i = 0; i < 4; ++i){
                if(checkOneOktet(ip, 46, i)){
                    bGotcha = true;
                    break;
                }
            }

            if(bGotcha)
                printOneAddress(ip);
        }
    }
};

class gpt{

    using IpAddress = std::array<int, 4>;

    IpAddress parseIp(const std::string& ip_str) {
        IpAddress ip{};
        std::istringstream iss(ip_str);
        std::string token;
        int index = 0;
        while (std::getline(iss, token, '.')) {
            ip[index++] = std::stoi(token);
        }
        return ip;
    }

public:
    void run() {
        std::vector<IpAddress> ip_addresses;
        std::string line;

        // Чтение данных из стандартного ввода
        while (std::getline(std::cin, line)) {
            std::istringstream lineStream(line);
            std::string ip_str;
            // Считываем первое поле до табуляции
            std::getline(lineStream, ip_str, '\t');
            ip_addresses.push_back(parseIp(ip_str));
        }

        // Сортировка в обратном порядке (от большего к меньшему)
        std::sort(ip_addresses.begin(), ip_addresses.end(), std::greater<IpAddress>()); //это работает! ТАК std::greater<std::array<int, 4>>() МОЖНО БЫЛО?

        // Функция для вывода IP-адресов
        auto printIp = [](const IpAddress& ip) {
            std::cout << ip[0] << '.' << ip[1] << '.' << ip[2] << '.' << ip[3] << "\n";
        };
    std::cout<<"------------------------------------"<<std::endl;
        // 1. Вывод полного списка адресов
        for (const auto& ip : ip_addresses) {
            printIp(ip);
        }
    std::cout<<"-----------------1-------------------"<<std::endl;
        // 2. Фильтрация: первый октет равен 1
        for (const auto& ip : ip_addresses) {
            if (ip[0] == 1)
                printIp(ip);
        }
    std::cout<<"---------------46 && 70---------------------"<<std::endl;
        // 3. Фильтрация: первый октет равен 46 и второй равен 70
        for (const auto& ip : ip_addresses) {
            if (ip[0] == 46 && ip[1] == 70)
                printIp(ip);
        }
    std::cout<<"-------------------- 46 || 46 || 46 || 46----------------"<<std::endl;
        // 4. Фильтрация: любой октет равен 46
        for (const auto& ip : ip_addresses) {
            if (ip[0] == 46 || ip[1] == 46 || ip[2] == 46 || ip[3] == 46)
                printIp(ip);
        }

    }

};


int main(){

    //Здесь два рабочих варианта. Я хотел бы узнать, какой лучше, и почему

    my my_var; //это мой обычный стиль
    my_var.run();

//    std::cout<<"==============================================="<<std::endl;

//    gpt gpt_var; //это предложил chatgpt
//    gpt_var.run();

}
