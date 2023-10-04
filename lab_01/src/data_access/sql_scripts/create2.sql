CREATE TABLE IF NOT EXISTS BA.Users2
(
    user_id SERIAL PRIMARY KEY,
    login VARCHAR(100) UNIQUE,
    password VARCHAR(100),
    permission INT
);