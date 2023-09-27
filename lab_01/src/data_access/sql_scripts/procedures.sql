CREATE OR REPLACE PROCEDURE BA.rate_product(prod_id INT, score INT)
AS
$$
    BEGIN
        UPDATE BA.products
        SET sum_rating = sum_rating + score, count_rating = count_rating + 1
        WHERE product_id = prod_id;
    END;
 $$ language plpgsql;

CREATE OR REPLACE PROCEDURE BA.make_request(cl_id INT, prod_id INT, summ numeric(15,2), dur INT)
AS
$$
    BEGIN
        INSERT INTO BA.requests(client_id, product_id, sum, duration, date, state, manager_id) VALUES
        (cl_id, prod_id, summ, dur, now(), 0, NULL);
    END;
 $$ language plpgsql;


CREATE OR REPLACE PROCEDURE BA.confirm_request(req_id INT, m_id INT)
AS
$$
    BEGIN
        UPDATE BA.requests
        SET manager_id = m_id, state = 1
        WHERE request_id = req_id;
    END;
 $$ language plpgsql;

CREATE OR REPLACE PROCEDURE BA.reject_request(req_id INT, m_id INT)
AS
$$
    BEGIN
        UPDATE BA.requests
        SET manager_id = m_id, state = 2
        WHERE request_id = req_id;
    END;
 $$ language plpgsql;