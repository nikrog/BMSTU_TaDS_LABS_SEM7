CREATE OR REPLACE FUNCTION BA.FireManager()
RETURNS TRIGGER
AS
    '
    BEGIN
        RAISE NOTICE ''Old =  %'', OLD.manager_id;
        RAISE NOTICE ''New =  %'', NEW.manager_id;
        UPDATE BA.requests
        SET manager_id = NULL
        WHERE manager_id = old.manager_id;

        RETURN OLD;
    END;
    ' LANGUAGE plpgsql;

DROP TRIGGER IF EXISTS BeforeFireManager on BA.managers;
CREATE TRIGGER BeforeFireManager BEFORE DELETE ON BA.managers
FOR EACH ROW EXECUTE PROCEDURE BA.FireManager();

-- DELETE FROM BA.managers WHERE manager_id = 12;