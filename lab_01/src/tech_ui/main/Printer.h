#ifndef PPO_PRINTER_H
#define PPO_PRINTER_H

#include <iostream>
#include <string>

const std::string MENU_ENTRIES = "\n\n\
0.  Выйти из программы.\n\
1.  Выйти из аккаунта.\n\
2.  Войти в аккаунт.\n\
3.  Добавить клиента.\n\
4.  Добавить менеджера.\n\
5.  Посмотреть информацию о клиенте.\n\
6.  Вывести список всех клиентов.\n\
7.  Вывести список всех банковских продуктов.\n\
8.  Добавить банковский продукт.\n\
9.  Посмотреть все заявки на банковские продукты.\n\
10. Создать заявку на банковский продукт.\n\
11. Посмотреть мои заявки на банковские продукты.\n\
12. Одобрить заявку на банковский продукт.\n\
13. Отклонить заявку на банковский продукт.\n\
14. Оценить банковский продукт.\n\
15. Вывести список всех банков.\n\
16. Изменить информацию о банковском продукте.\n\
Введите команду: ";


const std::string NOT_COMMAND = "Данной команды не существует!\nВведите заново!\n";
const std::string NOT_ROLE = "Эту команду невозможно выполнить в текущем статусе!\n";
const std::string UNAUTH_SUCCESS = "\nУспешный выход из аккаунта!\n";

class AppPrinter {
public:
     AppPrinter() = default;
     ~AppPrinter() = default;
     void print_menu();
     void print_not_a_command();
     void print_not_role();
     void print_unauth_success();
};


#endif //PPO_PRINTER_H
