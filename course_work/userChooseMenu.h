#include "users.h"
#include <limits>
#include <vector>
#include <algorithm>

std::vector<std::string> bodyparts = {
        "Head",
        "Body",
        "Right hand",
        "Left hand",
        "Right foot",
        "Left foot"
};

void info_case(PATIENT pat){
    bool check_info;
    std::cin >> check_info;
    std::string find_nick;
    std::fstream info_path("Config/PatsInfo.txt", std::ios::in|std::ios::out);
    while(!info_path.eof()){
        info_path >> find_nick;
        if(find_nick == pat.get_name()){
            if(check_info){
                std::cout << "Уводьте вашу додаткову інформацію:";

                info_path.ignore(std::numeric_limits<char>::max(), ';');
                info_path.seekp(-2, std::ios::cur);
                std::string new_info;
                std::cin.ignore();
                std::getline(std::cin, new_info);
                info_path << new_info << ";";

            }else{
                info_path.ignore(3);
                std::string get_info;
                std::getline(info_path, get_info, ';');
                std::cout << get_info;
            }
            return;
        }
        info_path.ignore(std::numeric_limits<char>::max(), ';');
    }
    info_path.close();
    info_path.open("Config/PatsInfo.txt", std::ios::in|std::ios::out);
    info_path.seekp(0, std::ios::end);

    std::cout << "Логін не знайдено, тому відповідний логін був створений,\nуведіть інформацію:";
    std::string new_info;
    std::cin.ignore();
    std::getline(std::cin,new_info);
    info_path << "\n" <<  pat.get_name() << " : " << new_info << ";";
}

template<typename T>
T show_docs(){
    std::ifstream path("Config/ADMIN.txt");
    T admnicks;
    std::string nickname;
    while(!path.eof()){
        path >> nickname;
        admnicks.push_back(nickname);
        path.ignore(std::numeric_limits<char>::max(), '\n');
    }
    for(const auto& doc : admnicks){
        std::cout << doc << " ";
    }
    std::cout << std::endl;
    return admnicks;
}

void pat_choose(PATIENT pat, int way){
    switch(way){
        case 1:{
            if(pat.get_medbook().empty()){
                std::cout << "Медкнижка не була створена доктором\n";
            }
            std::cout << pat.get_medbook();
            break;
        }
        case 2:{
            std::cout << "Виберіть доктора зі списку(цифрою від 1):\n";
            auto admnicks(show_docs<std::vector<std::string>>());
            if(admnicks.empty()){std::cout << "Докторів на вибір нема\n";break;}
            int num;
            std::cin >> num;
            if(num > admnicks.size() || num <= 0){
                std::cout << "Уведено неправильне значення\n";break;}
            pat.sign_up(admnicks[num-1]);
        }
        case 3:{
            std::cout << "Переглянувши зображення тіла, виберіть місце ураження:";
            ShellExecute(NULL, "open", "Config\\Human_Rentgen.jpg", NULL, NULL, SW_SHOWNORMAL);

            std::string part;
            std::cin.ignore();
            std::getline(std::cin, part);
            auto check = std::find(bodyparts.begin(), bodyparts.end(), part);
            if(check != std::end(bodyparts)){
                std::cout << "Детальніше опишіть свою травму, причини, наслідки і тд:";
                std::getline(std::cin, part);

                std::fstream inj_base("PatientsVisits/Injuries.txt", std::ios::in|std::ios::out);
                inj_base.seekp(0,std::ios::end); //робимо наче push_back
                inj_base << pat.get_name() << ": " << *check <<":\n" << part << "\n";
                inj_base.close();
            }else{std::cout << "Уведено частину тіла якої немає не зображенні\n";}
            break;
        }
        case 4:{
            std::cout << "Переглянути чи доповнити інформацію?"
                         "(0 - перше, 1 - друге):";
            info_case(pat);
        }
        case 5:{
            std::cout << "Виберіть доктора на ваш виклик(від 1):" << std::endl;
            auto docs(show_docs<std::vector<std::string>>());
            int num;
            std::cin >> num;
            if(num > docs.size() || num <= 0){
                std::cout << "Уведено неправильне значення";break;}
            std::cout << "Доктор " << docs[num-1] << " збирається до вас, укажіть адрес:\n";
            ADMIN doctor(docs[num-1]);
            std::string address;
            std::cin.ignore();
            std::getline(std::cin, address);
            doctor.put_call(address, pat.get_name());
            std::cout << "Адрес підтверджено\n";break;
        }
        default : break;
    }
}

auto get_pats(){
    std::vector<std::string> pats;
    std::string tmp;
    std::ifstream pats_path("Config/PATIENTS.txt");
    while(!pats_path.eof()){
        pats_path >> tmp;
        pats.push_back(tmp);
        pats_path.ignore(std::numeric_limits<char>::max(), '\n');
    }
    return pats;
}

void adm_choose(ADMIN adm, int way){
    switch(way){
        case 1:{
            auto pats(get_pats());
            if(pats.empty()){std::cout << "Пацієнтів немає";break;}
            std::cout << "Виберіть пацієнта(від 1):\n";
            for(const auto& pat : pats){
                std::cout << pat << " ";
            }
            std::cout << std::endl;
            int choose;
            std::cin >> choose;
            if(choose > pats.size() || choose <= 0){
                std::cout << "Вибрано неправильне значення";
                break;
            }
            PATIENT needed_pat(pats[choose-1]);
            adm.write_medbook(&needed_pat);
        }
        case 2:{
            std::string path = "PatientsVisits\\" + adm.get_name() + ".txt";
            std::fstream vispath(path, std::ios::in);
            if(!vispath) {
                std::cout << "Файл записів не створений, створюється...";
                vispath.open(path, std::ios::out);
            }
            vispath.close();
            system(path.c_str());
            break;
        }
        case 3:{
            system("PatientsVisits\\Injuries.txt");
        }
        default: break;
    }
}