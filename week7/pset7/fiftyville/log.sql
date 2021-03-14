-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Get corresponding description in crime_scene_reports
SELECT description
From crime_scene_reports
WHERE year = 2020 AND month = 7 AND day = 28 AND street = "Chamberlin Street";
-- Theft of the CS50 duck took place at 10:15am at the Chamberlin Street courthouse.
-- Interviews were conducted today with three witnesses who were present at the time — each of their interview transcripts mentions the courthouse.


-- Get names and transcripts of three witnesses from interviews
SELECT name,transcript
FROM interviews
WHERE year = 2020 AND month = 7 AND day = 28 AND transcript LIKE "%courthouse%";
--Ruth | Sometime within ten minutes of the theft, I saw the thief get into a car in the courthouse parking lot and drive away. If you have security footage from the courthouse parking lot, you might want to look for cars that left the parking lot in that time frame.
--Eugene | I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at the courthouse, I was walking by the ATM on Fifer Street and saw the thief there withdrawing some money.
--Raymond | As the thief was leaving the courthouse, they called someone who talked to them for less than a minute. In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket.


-- From Ruth's scripts:

-- Get license plate from courthouse_security_logs
SELECT license_plate
FROM courthouse_security_logs
WHERE year = 2020 AND month = 7 AND day = 28 AND hour = 10 AND minute >=15 AND minute <= 25 AND activity = "exit";
-- 5P2BI95
-- 94KL13X
-- 6P58WS2
-- 4328GD8
-- G412CB7
-- L93JTIZ
-- 322W7JE
-- 0NTHK55

-- Get corresponding names from people
SELECT name FROM people p
INNER JOIN courthouse_security_logs c
ON c.license_plate = p.license_plate
WHERE c.year = 2020 AND c.month = 7 AND c.day = 28 AND c.hour = 10 AND c.minute >=15 AND c.minute <= 25 AND c.activity = "exit";

-- Suspects:
-- Patrick
-- Ernest
-- Amber
-- Danielle
-- Roger
-- Elizabeth
-- Russell
-- Evelyn


--From Eugene's script:

-- Get account number and amount from atm_transactions
SELECT account_number,amount
FROM atm_transactions
WHERE year = 2020 AND month = 7 AND day = 28 AND transaction_type = "withdraw" AND atm_location = "Fifer Street";
-- 28500762 | 48
-- 28296815 | 20
-- 76054385 | 60
-- 49610011 | 50
-- 16153065 | 80
-- 25506511 | 20
-- 81061156 | 30
-- 26013199 | 35

-- Get corresponding names
SELECT name FROM people p
INNER JOIN bank_accounts b
ON b.person_id == p.id
INNER JOIN atm_transactions a
ON a.account_number = b.account_number
WHERE a.year = 2020 AND a.month = 7 AND a.day = 28 AND a.transaction_type = "withdraw" AND a.atm_location = "Fifer Street";

--Suspects:
-- Ernest
-- Russell
-- Roy
-- Bobby
-- Elizabeth
-- Danielle
-- Madison
-- Victoria

-- From above analysis -> Suspects: Ernest, Elizabeth, Danielle, Russell


-- From Raymond's script:

-- Get callers
SELECT name FROM people
WHERE phone_number IN
(SELECT caller FROM phone_calls
WHERE year = 2020 AND month = 7 AND day = 28 AND duration <= 60);
-- Bobby
-- Roger
-- Victoria
-- Madison
-- Russell
-- Evelyn
-- Kathryn
-- Ernest
-- Kimberly
-- From above analysis -> Suspects: Ernest, Russell


--Get the earliest flight
SELECT f.id,hour,minute FROM flights f
INNER JOIN airports a ON a.id = f.origin_airport_id
WHERE a.city = "Fiftyville" AND f.year = 2020 AND f.month = 7 AND f.day = 29;
-- id | hour | minute
-- 18 | 16 | 0
-- 23 | 12 | 15
-- 36 | 8 | 20
-- 43 | 9 | 30
-- 53 | 15 | 20

SELECT pp.name FROM people pp
INNER JOIN passengers pg ON pg.passport_number = pp.passport_number
INNER JOIN flights f ON f.id = pg.flight_id
INNER JOIN airports a ON a.id = f.origin_airport_id
WHERE f.id = 36;
-- Doris
-- Roger
-- Ernest
-- Edward
-- Evelyn
-- Madison
-- Bobby
-- Danielle
-- From above analysis -> Thief: Ernest

-- The thief escape to:
SELECT city FROM airports a
INNER JOIN flights f ON f.destination_airport_id = a.id
WHERE f.id = 36;
-- London

-- Get accomplice:
SELECT name FROM people pp
INNER JOIN phone_calls pc ON pc.receiver = pp.phone_number
WHERE pc.year = 2020 AND pc.month = 7 AND pc.day = 28 AND pc.duration <= 60
AND pc.caller IN
(select phone_number FROM people
WHERE name = "Ernest");
-- Accomplice: Berthold


