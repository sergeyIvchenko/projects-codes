#include "menus.h"
#include <limits>

#define patspath "Config/PATIENTS.txt"
#define admspath "Config/ADMIN.txt"

enum access_way{patient = 0, doctor};

template<typename T>
void create_user(T&& user, const std::string& path){
    std::fstream cnf_file(path, std::ios::in | std::ios::out);
    if(cnf_file.rdbuf()->in_avail()) {
        cnf_file.seekp(0, std::ios::end);
        cnf_file << "\n" << user.get_name() << " " << user.get_password();
    }
    else {cnf_file << user.get_name() << " " << user.get_password();}
    cnf_file.close();
}

template<typename T>
int find_user(T&& user, const std::string& path){
    std::ifstream cnf_file(path);
    std::string tmp;
    while(!cnf_file.eof()){
        cnf_file >> tmp;
        if(tmp == user.get_name()){
            cnf_file >> tmp;
            if(tmp == user.get_password()){cnf_file.close();return true;}
            else{std::cout << "Не правильний пароль\n";return 2;}
        }else{
            cnf_file.ignore(std::numeric_limits<char>::max(), '\n');
        }
    }
    cnf_file.close();
    return false;
}

template<typename T, typename func>
void login(std::string nick, std::string pass, const std::string& path, func menu){
    T user(nick, pass);
    if (!find_user(user, path) || find_user(user,path) == 2) {
        std::cout << "Даного логіну не існує, створити новий?"
                     "(0 - ні, інше - так):";
        bool trycreate;
        std::cin >> trycreate;
        if (trycreate) { create_user(user, path); }
        else return;
    }
    menu(user);
}

void start_menu(){
    std::cout << "Визначте тип користування\n"
                 "0 - пацієнт, 1 - доктор" << std::endl;
    int way;
    std::cin >> way;
    while((way != patient) && (way != doctor)){
        std::cout << "Уведено некоректне значення, спробуйте ще раз" << std::endl;
        std::cin >> way;
    }
    std::string nick, pass;
    std::cout << "Уведіть логін та пароль через пробіл"
                 "(і нік і пароль не повинні мати пробілів):";
    std::cin >> nick >> pass;
    switch(way){
        case patient: {
            login<PATIENT>(nick,pass, patspath, pat_menu);
            break;
        }
        case doctor: {
            login<ADMIN>(nick,pass, admspath, admin_menu);
            break;
        }
        default: break;
    }
}