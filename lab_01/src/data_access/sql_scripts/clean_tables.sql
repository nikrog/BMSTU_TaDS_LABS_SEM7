DELETE FROM BA.Requests WHERE request_id > 0;
DELETE FROM BA.Products WHERE product_id > 0;
DELETE FROM BA.Clients WHERE client_id > 0;
DELETE FROM BA.Managers WHERE manager_id > 0;
DELETE FROM BA.Users WHERE user_id > 0;
DELETE FROM BA.Banks WHERE bank_id > 0;

TRUNCATE TABLE BA.requests RESTART IDENTITY;

