#include "userChooseMenu.h"
#include <cstdlib>

auto pat_menu = [](PATIENT pat){
    int way = 0 ;
    while(way!=6){
        std::cout << "\n1) Переглянути свою медкарту\n"
                     "2) Записатися до доктора\n"
                     "3) Передати інформацію щодо травми\n"
                     "4) Переглянути/доповнити свою загальну інформацію\n"
                     "5) Негайний виклик швидкої\n"
                     "6) Вихід\n";
        std::cin >> way;
        pat_choose(pat, way);
        //system("CLS");
    }
};

auto admin_menu = [](ADMIN adm){
    int way = 0;
    if(!adm.check_calls()){
        std::cout << "У вас є екстрені виклики";
        adm.show_calls();
    }
    while(way!=4){
        std::cout << "\n1) Перевірити/доповнити медкарту пацієнта\n"
                     "2) Переглянути/створити файл записів на прийом\n"
                     "3) Переглянути інформацію про травми\n"
                     "4) Вихід\n";
        std::cin >> way;
        adm_choose(adm, way);
        //system("CLS");
    }
};