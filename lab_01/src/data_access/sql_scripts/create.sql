DROP SCHEMA BA cascade;

CREATE SCHEMA BA;

CREATE TABLE IF NOT EXISTS BA.Users
(
    user_id INT GENERATED ALWAYS AS IDENTITY PRIMARY KEY,
    login VARCHAR(100) UNIQUE,
    password VARCHAR(100),
    permission INT
);

CREATE TABLE IF NOT EXISTS BA.Banks
(
    bank_id INT GENERATED ALWAYS AS IDENTITY PRIMARY KEY,
    name VARCHAR(100) UNIQUE,
    license_num INT,
    address VARCHAR(150),
    email VARCHAR(100),
    phone VARCHAR(15),
    website VARCHAR(100)
);

CREATE TABLE IF NOT EXISTS BA.Managers
(
    manager_id INT GENERATED ALWAYS AS IDENTITY PRIMARY KEY,
    user_id INT,
    bank_id INT,
    FOREIGN KEY (user_id) REFERENCES BA.Users (user_id) ON DELETE CASCADE,
    FOREIGN KEY (bank_id) REFERENCES BA.Banks (bank_id) ON DELETE CASCADE
);

CREATE TABLE IF NOT EXISTS BA.Products
(
    product_id INT GENERATED ALWAYS AS IDENTITY PRIMARY KEY,
    ptype INT NOT NULL,
    name VARCHAR(100) UNIQUE,
    bank_id INT,
    rate numeric(6,2),
    min_time INT,
    max_time INT,
    min_sum numeric(15, 2),
    max_sum numeric(15, 2),
    currency INT NOT NULL,
    sum_rating INT,
    count_rating INT,
    FOREIGN KEY (bank_id) REFERENCES BA.Banks (bank_id) ON DELETE CASCADE
);

CREATE TABLE IF NOT EXISTS BA.Clients
(
    client_id INT GENERATED ALWAYS AS IDENTITY PRIMARY KEY,
    name VARCHAR(50),
    surname VARCHAR(50),
    patronymic VARCHAR(50),
    passport_num BIGINT UNIQUE,
    birth_date INT,
    address VARCHAR(150),
    email VARCHAR(100),
    phone VARCHAR(15),
    user_id INT,
    FOREIGN KEY (user_id) REFERENCES BA.Users (user_id) ON DELETE CASCADE
);

CREATE TABLE IF NOT EXISTS BA.Requests
(
    request_id INT GENERATED ALWAYS AS IDENTITY PRIMARY KEY,
    client_id INT,
    product_id INT,
    sum numeric(15, 2),
    duration INT,
    date TIMESTAMP,
    state INT,
    manager_id INT,
    FOREIGN KEY (manager_id) REFERENCES BA.Managers (manager_id) ON DELETE CASCADE,
    FOREIGN KEY (client_id) REFERENCES BA.Clients (client_id) ON DELETE CASCADE,
    FOREIGN KEY (product_id) REFERENCES BA.Products (product_id) ON DELETE CASCADE
);

CREATE TABLE IF NOT EXISTS BA.Products2
(
    product_id INT GENERATED ALWAYS AS IDENTITY PRIMARY KEY,
    ptype INT NOT NULL,
    name VARCHAR(100),
    bank_id INT,
    rate numeric(6,2),
    min_time INT,
    max_time INT,
    min_sum numeric(15, 2),
    max_sum numeric(15, 2),
    currency INT NOT NULL,
    sum_rating INT,
    count_rating INT,
    FOREIGN KEY (bank_id) REFERENCES BA.Banks (bank_id) ON DELETE CASCADE
);