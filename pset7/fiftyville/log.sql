-- Keep a log of any SQL queries you execute as you solve the mystery.

/*  What we will find out:

    -   Identity of thief
    -   What city he escaped to
    -   Identity of thief's accomplice
*/

--  Start with crime reports
SELECT * FROM crime_scene_reports;
--  Fortunetly, immediately found duck theft report at the bottom of table
--  crime_scene_reports.id = 295;

--  Inspect it more closely
SELECT * FROM crime_scene_reports
WHERE id = 295;
/*
    month:  '7'
    day:    '28'
    year:   '2020'
    street: 'Chamberlin Street'
    description: Theft of the CS50 duck took place at 10:15am
                 at the Chamberlin Street courthouse.
                 Interviews were conducted today with
                 three witnesses who were present at
                 the time — each of their interview
                 transcripts mentions the courthouse. */

-- Let's read those Interviews!
SELECT id, name FROM interviews
WHERE year = 2020 AND month = 7 AND day = 28;
/*
id | name
158 | Jose
159 | Eugene
160 | Barbara
161 | Ruth
162 | Eugene
163 | Raymond */

-- 3 interviews are supposed to mention the courthouse!
SELECT id, name, transcript FROM interviews
WHERE id >= 158 AND id <= 163;
/*
These mention curthouse:
161 | Ruth:
    ->  saw car leaving within 10min of theft (10:15am - 10:25am)
162 | Eugene:
    ->  saw thief withdrawing money earlyer at ATM on Fifer Street
163 | Raymond:
    ->  heard thief plan to leave with earliest flight out of
        Fiftyville the next day
    ->  also heard complice was asked to buy flight tickets */

-- Okay clues:  Courthouse securtiy logs, ATM Fifer Steet,
--              earliest flight out of fiftyville the next day

-- Lets look into the courthouse logs
SELECT id, activity, license_plate FROM courthouse_security_logs
WHERE year = 2020
    AND month = 7
    AND day = 28
    AND hour = 10
    AND minute >= 15
    AND minute <= 25;
/*
id | activity | license_plate
260 | exit | 5P2BI95
261 | exit | 94KL13X
262 | exit | 6P58WS2
263 | exit | 4328GD8
264 | exit | G412CB7
265 | exit | L93JTIZ
266 | exit | 322W7JE
267 | exit | 0NTHK55
One of them has to be the thief*/

-- Lets also get their names
SELECT people.id, people.name, courthouse_security_logs.activity, courthouse_security_logs.license_plate FROM courthouse_security_logs
    JOIN people ON people.license_plate = courthouse_security_logs.license_plate
WHERE year = 2020
    AND month = 7
    AND day = 28
    AND hour = 10
    AND minute >= 15
    AND minute <= 25;
/*
id | name | activity | license_plate
221103 | Patrick | exit | 5P2BI95
686048 | Ernest | exit | 94KL13X
243696 | Amber | exit | 6P58WS2
467400 | Danielle | exit | 4328GD8
398010 | Roger | exit | G412CB7
396669 | Elizabeth | exit | L93JTIZ
514354 | Russell | exit | 322W7JE
560886 | Evelyn | exit | 0NTHK55
No name shows up twice, yeah!*/

-- Lets see if any of those withdraw money at the ATM on fiferstreet
SELECT DISTINCT id, name FROM people
WHERE people.id IN (
    SELECT person_id FROM bank_accounts
    WHERE bank_accounts.account_number IN (
        SELECT account_number FROM atm_transactions
        WHERE transaction_type = 'withdraw'
            AND year = 2020
            AND month = 7
            AND day = 28
            AND atm_location = 'Fifer Street'
    )
) AND people.id IN (
    SELECT people.id FROM courthouse_security_logs
        JOIN people ON people.license_plate = courthouse_security_logs.license_plate
    WHERE courthouse_security_logs.year = 2020
        AND courthouse_security_logs.month = 7
        AND courthouse_security_logs.day = 28
        AND courthouse_security_logs.hour = 10
        AND courthouse_security_logs.minute >= 15
        AND courthouse_security_logs.minute <= 25
);
/* sqlite>
id | name
396669 | Elizabeth
467400 | Danielle
514354 | Russell
686048 | Ernest
Four suspects! */


-- Lets find out if any of these took the earliest flight
-- out of fiftyville the next day

-- Search for fiftyville airport info
SELECT * FROM airports
WHERE city='Fiftyville';
-- abbreviation = CSF
-- id = 8

-- Search ealiest flight
SELECT * FROM flights
WHERE origin_airport_id=8
    AND year=2020 AND month = 7 AND day = 29;
-- flights.id = 36
-- destination_airport_id = 4

-- Now identify suspiscious passengers
SELECT * FROM people
    WHERE passport_number IN (
        SELECT passport_number FROM passengers
        WHERE flight_id = '36'
    )
    AND people.id IN (
        SELECT person_id FROM bank_accounts
        WHERE bank_accounts.account_number IN (
            SELECT account_number FROM atm_transactions
            WHERE transaction_type = 'withdraw'
                AND year = 2020
                AND month = 7
                AND day = 28
                AND atm_location = 'Fifer Street'
            )
    ) AND people.id IN (
    SELECT people.id FROM courthouse_security_logs
        JOIN people ON people.license_plate = courthouse_security_logs.license_plate
    WHERE courthouse_security_logs.year = 2020
        AND courthouse_security_logs.month = 7
        AND courthouse_security_logs.day = 28
        AND courthouse_security_logs.hour = 10
        AND courthouse_security_logs.minute >= 15
        AND courthouse_security_logs.minute <= 25
);
/*  The circle of suspects shrinks.
id     | name     | phone_number   | passport_number | license_plate
467400 | Danielle | (389) 555-5198 | 8496433585      | 4328GD8
686048 | Ernest   | (367) 555-5533 | 5773159633      | 94KL13X
*/

-- Thief was on the phone while leaving the crime scene
SELECT people.name, phone_calls.caller, phone_calls.receiver, duration
FROM phone_calls
JOIN people ON people.phone_number = caller
WHERE caller = '(389) 555-5198' OR caller = '(367) 555-5533'
    AND year = 2020
    AND month = 7
    AND day = 28;
/*
name     | caller         | receiver       | duration
Danielle | (389) 555-5198 | (368) 555-3561 | 414
Ernest   | (367) 555-5533 | (375) 555-8161 | 45
Ernest   | (367) 555-5533 | (344) 555-9601 | 120
Ernest   | (367) 555-5533 | (022) 555-4052 | 241
Ernest   | (367) 555-5533 | (704) 555-5790 | 75
Danielle | (389) 555-5198 | (609) 555-5876 | 397
*/

-- Lets regroup data for our main suspects for clarity
/*  Danielle
    -   Left courthouse shortly after incident ocurred
        between 10:15am and 10:25am via car
    -   Withdraw money from ATM on Fifer Street 7/28/20
        - Took earliest flight out of Fiftyville the next day

    Ernest
    -   Left courthouse shortly after incident occured
        between 10:15am and 10:25am via car
    -   Withdraw money from ATM on Fifer Street 7/28/20
        - Took earliest flight out of Fiftyville the next day

SELECT name, phone_number FROM people
WHERE passport_number IN (
    SELECT passport_number FROM flights
    WHERE id=36
)
AND (
    phone_number = '(375) 555-8161'
    OR phone_number = '(344) 555-9601'
    OR phone_number = '(022) 555-4052'
    OR phone_number = '(704) 555-5790'
    OR phone_number = '(368) 555-3561'
    OR phone_number = '(609) 555-5876'
);



SELECT phone_calls.id, people.name, 
        phone_calls.duration, 
        phone_calls.day
FROM people
JOIN phone_calls ON phone_calls.caller = people.phone_number
    
WHERE people.phone_number IN (
    SELECT phone_calls.caller FROM phone_calls
    WHERE  duration < 30
);


SELECT * FROM phone_calls
WHERE duration < 60;
