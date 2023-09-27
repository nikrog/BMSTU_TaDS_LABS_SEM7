#ifndef PPO_CONSTANTS_H
#define PPO_CONSTANTS_H

#include <string>

#define NONE -1
#define EMPTY std::string("")
#define DEF_TIME 0
#define DEF_TIME2 "0"
#define MIN_PASSWORD_LEN 5
#define MIN_LOGIN_LEN 1
#define MIN_TIME 1
#define MAX_TIME 7300
#define MIN_SUM 0
#define MAX_SUM 1000000000
#define MIN_SCORE 1
#define MAX_SCORE 5

typedef int date_t;
typedef std::string timereq_t;

const std::string USER_NOT_FOUND_ERROR = " Пользователь не найден!";
const std::string USER_ADD_ERROR = " Ошибка при добавлении пользователя!";
const std::string USER_DELETE_ERROR = " Ошибка при удалении пользователя!";
const std::string USER_UPDATE_ERROR = " Ошибка при обновлении данных пользователя!";
const std::string MANAGER_NOT_FOUND_ERROR = " Менеджер не найден!";
const std::string MANAGER_ADD_ERROR = " Ошибка при добавлении менеджера!";
const std::string MANAGER_DELETE_ERROR = " Ошибка при удалении менеджера!";
const std::string MANAGER_UPDATE_ERROR = " Ошибка при обновлении данных менеджера!";
const std::string BANK_NOT_FOUND_ERROR = " Банк не найден!";
const std::string BANK_ADD_ERROR = " Ошибка при добавлении банка!";
const std::string BANK_DELETE_ERROR = " Ошибка при удалении банка!";
const std::string BANK_UPDATE_ERROR = " Ошибка при обновлении данных банка!";
const std::string CLIENT_NOT_FOUND_ERROR = " Клиент не найден!";
const std::string CLIENT_ADD_ERROR = " Ошибка при добавлении клиента!";
const std::string CLIENT_DELETE_ERROR = " Ошибка при удалении клиента!";
const std::string CLIENT_UPDATE_ERROR = " Ошибка при обновлении данных клиента!";
const std::string PRODUCT_NOT_FOUND_ERROR = "Банковский продукт не найден!";
const std::string PRODUCT_ADD_ERROR = " Ошибка при добавлении банковского продукта!";
const std::string PRODUCT_DELETE_ERROR = " Ошибка при удалении банковского продукта!";
const std::string PRODUCT_UPDATE_ERROR = " Ошибка при обновлении данных банковского продукта!";
const std::string PRODUCT_GET_ERROR = " Ошибка при получении банковского продукта!";
const std::string REQUEST_NOT_FOUND_ERROR = " Заявка не найдена!";
const std::string REQUEST_ADD_ERROR = " Ошибка при добавлении заявки!";
const std::string REQUEST_DELETE_ERROR = " Ошибка при удалении заявки!";
const std::string REQUEST_UPDATE_ERROR = " Ошибка при обновлении данных заяки!";
const std::string REQUEST_GET_ERROR = " Ошибка при получении заявки!";
const std::string REQUEST_MAKE_ERROR = " Ошибка при попытке сделать заявку!";
const std::string REQUEST_CONFIRM_ERROR = " Ошибка при одобрении заявки!";
const std::string REQUEST_REJECT_ERROR = " Ошибка при отклонении заявки!";
const std::string PRODUCT_RATE_ERROR = " Ошибка при оценке продукта!";
const std::string DATABASE_CONNECT_ERROR = " Ошибка подключения к БД!";

const std::string LOGIN_INPUT_MESSAGE = "Введите логин: ";
const std::string PASSWORD_INPUT_MESSAGE = "Введите пароль: ";
const std::string NAME_INPUT_MESSAGE = "Введите имя: ";
const std::string SURNAME_INPUT_MESSAGE = "Введите фамилию: ";
const std::string PATRONYMIC_INPUT_MESSAGE = "Введите отчество: ";
const std::string ADDRESS_INPUT_MESSAGE = "Введите адрес проживания: ";
const std::string BIRTHDATE_INPUT_MESSAGE = "Введите дату рождения (YYYYMMDD): ";
const std::string EMAIL_INPUT_MESSAGE = "Введите email: ";
const std::string PASSPORTNUM_INPUT_MESSAGE = "Введите номер паспорта: ";
const std::string PHONE_INPUT_MESSAGE = "Введите номер телефона: ";
const std::string CLIENT_ID_INPUT_MESSAGE = "Введите ID клиента: ";
const std::string PRODUCT_ID_INPUT_MESSAGE = "Введите ID продукта: ";
const std::string MANAGER_ID_INPUT_MESSAGE = "Введите ID менеджера: ";
const std::string REQUEST_ID_INPUT_MESSAGE = "Введите ID заявки: ";
const std::string USER_ID_INPUT_MESSAGE = "Введите ID пользователя: ";
const std::string PROD_NAME_INPUT_MESSAGE = "Введите название продукта: ";
const std::string PROD_TYPE_INPUT_MESSAGE = "Введите тип продукта (0 - Депозит, 1 - Кредит): ";
const std::string BANK_ID_INPUT_MESSAGE = "Введите ID банка: ";
const std::string BANK_NAME_INPUT_MESSAGE = "Введите название банка: ";
const std::string RATE_INPUT_MESSAGE = "Введите процентную ставку: ";
const std::string MIN_TIME_INPUT_MESSAGE = "Введите минимальный срок: ";
const std::string MAX_TIME_INPUT_MESSAGE = "Введите максимальный срок: ";
const std::string DURATION_INPUT_MESSAGE = "Введите желаемый срок: ";
const std::string MIN_SUM_INPUT_MESSAGE = "Введите минимальную сумму: ";
const std::string MAX_SUM_INPUT_MESSAGE = "Введите максимальную сумму: ";
const std::string SUM_INPUT_MESSAGE = "Введите желаемую сумму: ";
const std::string DATE_INPUT_MESSAGE = "Введите дату заявки: ";
const std::string STATE_INPUT_MESSAGE = "Введите статус заявки: ";
const std::string CURRENCY_INPUT_MESSAGE = "Введите валюту (0 - Рубль, 1 - Доллар, 2 - Евро, 3 - Юань): ";
const std::string SCORE_INPUT_MESSAGE = "Оценить продукт (1 - 5 баллов): ";

const std::string AUTH_SUCCESS = " Авторизация прошла успешно!";
const std::string LOGIN_ERROR = " Неверный логин!\n";
const std::string PASSWORD_ERROR = " Неверный пароль!\n";
const std::string LOGIN_OR_PASSWORD_ERROR = " Неверный логин или пароль!";
const std::string CHANGE_SUCCESS = " Информация успешно обновлена!";
const std::string ADD_SUCCESS = " Информация успешно добавлена!";
const std::string INPUT_INT_ERROR = " Неправильно введено целое число!";
const std::string INPUT_FLOAT_ERROR = " Неправильно введено вещественное число!";

#endif //PPO_CONSTANTS_H
