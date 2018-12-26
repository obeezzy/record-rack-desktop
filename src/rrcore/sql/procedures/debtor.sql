USE ###DATABASENAME###;

DELIMITER //
CREATE PROCEDURE AddDebtor(
	IN iClientId INTEGER,
    IN iNote VARCHAR(200),
    IN iUserId INTEGER
)
BEGIN
	SET @noteId := 0;
	IF iNote IS NOT NULL THEN
		INSERT INTO note (note, table_name, created, last_edited, user_id)
			VALUES (iNote, 'debtor', CURRENT_TIMESTAMP(), CURRENT_TIMESTAMP(), iUserId);
		SELECT LAST_INSERT_ID() INTO @noteId;
    END IF;

	INSERT INTO debtor (client_id, note_id, archived, created, last_edited, user_id)
		VALUES (iClientId, iNote, FALSE, CURRENT_TIMESTAMP(), CURRENT_TIMESTAMP(), iUserId);
	SELECT LAST_INSERT_ID() AS id;
END //
DELIMITER ;

--

DELIMITER //
CREATE PROCEDURE AddDebtPayment(
	IN iDebtTransactionId INTEGER,
    IN iTotalAmount DECIMAL(19,2),
    IN iAmountPaid DECIMAL(19,2),
    IN iBalance DECIMAL(19,2),
    IN iCurrency VARCHAR(4),
    IN iDueDate DATETIME,
    IN iNote VARCHAR(200),
    IN iUserId INTEGER
)
BEGIN
	SET @noteId := 0;
	IF iNote IS NOT NULL THEN
		INSERT INTO note (note, table_name, created, last_edited, user_id)
			VALUES (iNote, 'debt_payment', CURRENT_TIMESTAMP(), CURRENT_TIMESTAMP(), iUserId);
		SELECT LAST_INSERT_ID() INTO @noteId;
    END IF;
    
	INSERT INTO debt_payment (debt_transaction_id, total_amount, amount_paid, balance, currency, due_date, note_id, 
		archived, created, last_edited, user_id) VALUES (iDebtTransactionId, iTotalAmount, iAmountPaid, iBalance, 
		iCurrency, iDueDate, @noteId, FALSE, CURRENT_TIMESTAMP(), CURRENT_TIMESTAMP(), iUserId);
	SELECT LAST_INSERT_ID() AS id;
END //
DELIMITER ;

--

DELIMITER //
CREATE PROCEDURE AddDebtTransaction(
	IN iDebtorId INTEGER,
    IN iTransactionTable VARCHAR(20),
    IN iTransactionId INTEGER,
    IN iNote VARCHAR(200),
    IN iUserId INTEGER
)
BEGIN
	SET @noteId := 0;
    IF iNote IS NOT NULL THEN
		INSERT INTO note (note, table_name, transaction_id, created, last_edited, user_id)
			VALUES (iNote, 'debt_transaction', CURRENT_TIMESTAMP(), CURRENT_TIMESTAMP(), iUserId);
		SELECT LAST_INSERT_ID() INTO @noteId;
    END IF;

	INSERT INTO debt_transaction (debtor_id, transaction_table, transaction_id, note_id, archived, created, last_edited, user_id)
		VALUES (iDebtorId, iTransactionTable, iTransactionId, @noteId, FALSE, CURRENT_TIMESTAMP(), CURRENT_TIMESTAMP(), iUserId);

	SELECT LAST_INSERT_ID() AS id;
END //
DELIMITER ;