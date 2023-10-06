ALTER TABLE BA.clients
    ADD CONSTRAINT checkPassport check (passport_num > 0 AND length(passport_num::text) = 10);

ALTER TABLE BA.clients
    ADD CONSTRAINT checkBirthDate check (birth_date <= 20230101 AND birth_date >= 19100101);

ALTER TABLE BA.clients
    ADD CONSTRAINT checkPhone check (phone LIKE '+7%' AND length(phone) = 12);

ALTER TABLE BA.products
    ADD CONSTRAINT checkPtype check (ptype >= 0 AND ptype < 2);

ALTER TABLE BA.products
    ADD CONSTRAINT checkRate check (rate BETWEEN -99.99 AND 99.99);

ALTER TABLE BA.products
    ADD CONSTRAINT checkMinTime check (min_time > 0);

ALTER TABLE BA.products
    ADD CONSTRAINT checkMaxTime check (max_time > 0 AND max_time >= min_time);

ALTER TABLE BA.products
    ADD CONSTRAINT checkMinSum check (min_sum > 0);

ALTER TABLE BA.products
    ADD CONSTRAINT checkMaxSum check (max_sum > 0 AND max_sum >= min_sum);

ALTER TABLE BA.products
    ADD CONSTRAINT checkCurrency check (currency >= 0 AND currency < 4);

ALTER TABLE BA.products
    ADD CONSTRAINT checkSumRating check (sum_rating >= 0);

ALTER TABLE BA.products
    ADD CONSTRAINT checkCountRating check (count_rating >= 0);

ALTER TABLE BA.requests
    ADD CONSTRAINT checkSum check (sum > 0);

ALTER TABLE BA.requests
    ADD CONSTRAINT checkDuration check (duration > 0);

ALTER TABLE BA.requests
    ADD CONSTRAINT checkDate check (date >= '1970-01-01 00:00:00');

ALTER TABLE BA.requests
    ADD CONSTRAINT checkState check (state >= 0 AND state < 6);

ALTER TABLE BA.banks
    ADD CONSTRAINT checkLicenseNum check (license_num > 0);

ALTER TABLE BA.banks
    ADD CONSTRAINT checkPhone check (phone LIKE '+7%' AND length(phone) = 12);