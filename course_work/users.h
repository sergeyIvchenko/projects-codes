#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <utility>

class USER{
public:
    USER() = default;
    explicit USER(std::string name): name(std::move(name)){};
    USER(std::string name, std::string password):name(std::move(name)),password(std::move(password)){};
    std::string get_name(){return name;}
    std::string get_password(){return password;}
protected:
    std::string name;
    std::string password;
};

class PATIENT : public USER{
    friend class ADMIN;
public:
    PATIENT() = default;
    PATIENT(std::string name) : USER(std::move(name)){};
    PATIENT(std::string name, std::string password) : USER(std::move(name), std::move(password)){};
    std::string get_medbook() {return medbook;}
    void sign_up(const std::string& docnick){
        std::string path = "PatientsVisits\\" + docnick + ".txt";
        std::fstream docvisits(path, std::ios::in|std::ios::out);
        if(docvisits) {docvisits.seekp(0, std::ios::end);}
        else{std::cout << "Доктор не створив записи"; return;}

        std::cout << "Уведіть час на який робити запис:";
        std::string date;
        std::getline(std::cin, date);
        docvisits << "\n" << this->name << " " << date;
        docvisits.close();
    }
private:
    std::string medbook;
};

class ADMIN : public USER{
public:
    ADMIN() = default;
    ADMIN(std::string name) : USER(std::move(name)) {};
    ADMIN(std::string name, std::string password) : USER(std::move(name),std::move(password)){};
    static void write_medbook(PATIENT* patient){
        std::string path = "medbooks\\";
        path += patient->get_name() + ".txt";
        std::fstream patbook(path, std::ios::in);
        if(!patbook) {
            patbook.open(path, std::ios::out);
        }
        patbook.close();
        system(path.c_str());

        std::ifstream book(path);
        std::stringstream get_book;
        get_book << book.rdbuf();
        patient->medbook = get_book.str();
        book.close();
    }
    void put_call(const std::string& address,const std::string& nick){
        emergency_calls.insert(std::pair<std::string, std::string>(address,nick));
    }
    void show_calls(){
        for(const auto& call : emergency_calls){
            std::cout << call.first << " " << call.second << std::endl;
        }
    }
    bool check_calls(){
        return emergency_calls.empty();
    }
private:
        std::map<std::string, std::string> emergency_calls;
};