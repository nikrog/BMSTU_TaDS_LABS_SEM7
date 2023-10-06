copy BA.products2 (ptype, name, bank_id, rate, min_time, max_time,
                         min_sum, max_sum, currency, sum_rating, count_rating)
    from '/db_data/products.csv' delimiter ',';

CREATE UNIQUE INDEX pname_idx ON BA.products2 (name);

CREATE INDEX pname_idx2 ON BA.products2 USING HASH (name) ;

SELECT date FROM BA.requests
WHERE date > '2023-05-06 15:20:55.000000';

SELECT * FROM BA.products2
WHERE name LIKE 'J%';

SELECT * FROM BA.products2
WHERE name = 'Elizabeth Pacheco7';

SELECT NOW();

DELETE FROM BA.products2
WHERE product_id > 100010