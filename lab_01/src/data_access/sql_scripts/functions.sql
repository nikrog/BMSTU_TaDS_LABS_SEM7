CREATE OR REPLACE FUNCTION BA.calc_rating(prod_id int)
RETURNS numeric AS '
    SELECT
    CASE
        WHEN count_rating > 0 THEN sum_rating / CAST (count_rating AS float)
        ELSE 0
    END
    FROM BA.products
    WHERE product_id = prod_id'
LANGUAGE SQL;

--SELECT BA.calc_rating(1) AS avg_rating;
--SELECT BA.calc_rating(2) AS avg_rating;

--SELECT * FROM BA.products
--WHERE BA.calc_rating(product_id) > 4;