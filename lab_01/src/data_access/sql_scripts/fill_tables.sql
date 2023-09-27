INSERT INTO BA.users (login, password, permission) VALUES
('admin', 'admin', 3);

INSERT INTO BA.users (login, password, permission) VALUES
('manager', '11111', 2);

INSERT INTO BA.users (login, password, permission) VALUES
('client', '22221', 1);

INSERT INTO BA.users (login, password, permission) VALUES
('client2', '22222', 1);

INSERT INTO BA.banks (name, license_num, address, email, phone, website) VALUES
('Альфа банк', 1234, 'Москва', 'alphabank@alpha.ru', '+74953459872', 'alphabank.ru')
RETURNING bank_id;

INSERT INTO BA.banks (name, license_num, address, email, phone, website) VALUES
('Райфайзен банк', 1235, 'Москва', 'raifaizen@raif.ru', '+74953459873', 'raiffaizen.ru');

INSERT INTO BA.banks (name, license_num, address, email, phone, website) VALUES
('Россельхоз банк', 6667, 'Москва', 'rosselhoz@rsb.ru', '+74953479973', 'rosselhoz.ru');

INSERT INTO BA.banks (name, license_num, address, email, phone, website) VALUES
('ПСБ', 345669, 'Москва', 'promsvyaz@psb.ru', '+74953473673', 'psb.ru');

INSERT INTO BA.banks (name, license_num, address, email, phone, website) VALUES
('Локо-банк', 345669, 'Москва', 'locko@bank.ru', '+74953473689', 'lockobank.ru');

INSERT INTO BA.banks (name, license_num, address, email, phone, website) VALUES
('ВТБ', 7654, 'Москва', 'vtb@bank.ru', '+74953476589', 'vtb.ru');

INSERT INTO BA.banks (name, license_num, address, email, phone, website) VALUES
('Сбербанк', 4556, 'Москва', 'sberbank@sber.ru', '+74953473633', 'sberbank.ru');

INSERT INTO BA.banks (name, license_num, address, email, phone, website) VALUES
('Тинькофф', 546463, 'Москва', 'tinkoff@tink.ru', '+74924473689', 'tinkoff.ru');

INSERT INTO BA.clients (name, surname, patronymic, passport_num, birth_date, address, email, phone, user_id) VALUES
('b', 'b', 'b', 7777912345, 19860203, 'Street 9', 'b@mail.ru', '+79183456781', 4);

INSERT INTO BA.clients (name, surname, patronymic, passport_num, birth_date, address, email, phone, user_id) VALUES
('a', 'a', 'a', 7776933333, 19990623, 'Street 6', 'a@mail.ru', '+79183456745', 3);

INSERT INTO BA.managers (user_id, bank_id) VALUES
(2, 1);

INSERT INTO BA.products (ptype, name, bank_id, rate, min_time, max_time,
                         min_sum, max_sum, currency, sum_rating, count_rating)  VALUES
(0, 'test', 1, 7.5, 10, 750, 10000, 1000000, 0, 0, 0);

INSERT INTO BA.products (ptype, name, bank_id, rate, min_time, max_time,
                         min_sum, max_sum, currency, sum_rating, count_rating)  VALUES
(1, 'test_credit', 1, 12.5, 1, 750, 100000, 3000000, 0, 21, 5);

copy BA.products (ptype, name, bank_id, rate, min_time, max_time,
                         min_sum, max_sum, currency, sum_rating, count_rating)
    from '/db_data/products.csv' delimiter ',';


