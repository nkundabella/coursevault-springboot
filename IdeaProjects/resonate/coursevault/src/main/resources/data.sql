CREATE OR REPLACE FUNCTION delete_expired_codes() 
RETURNS TRIGGER AS $$
BEGIN
  DELETE FROM verification_codes WHERE expiry_date < NOW();
  RETURN NEW;
END;
$$ LANGUAGE plpgsql^

DROP TRIGGER IF EXISTS trigger_delete_expired_codes ON verification_codes^

CREATE TRIGGER trigger_delete_expired_codes
AFTER INSERT ON verification_codes
FOR EACH STATEMENT
EXECUTE FUNCTION delete_expired_codes()^