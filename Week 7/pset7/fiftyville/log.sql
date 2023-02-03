-- Keep a log of any SQL queries you execute as you solve the mystery.

SELECT description FROM crime_scene_reports WHERE day = "28" AND month = "7" AND year = "2020" AND street = "Chamberlin Street"

-- Get the interviews on the day of the crime
SELECT transcript FROM interviews WHERE day = "28" AND month = "7" AND year = "2020" AND transcript like "%courthouse%"

-- Get how the actvity is described in the interviews
SELECT activity FROM courthouse_security_logs

-- The names based on license plates of car exiting the courthouse in a 10 minutes timeframe
SELECT name FROM people JOIN courthouse_security_logs ON people.license_plate = courthouse_security_logs.license_plate WHERE day = "28" AND month = "7" AND year = "2020" AND hour = "10" AND minute >= "15" AND minute < "25" AND activity = "exit"

-- The names of people who made a withdrawal that day on Fifer Street
SELECT DISTINCT name FROM people JOIN bank_accounts ON people.id = bank_accounts.person_id JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number WHERE day = "28" AND month = "7" AND year = "2020" AND transaction_type = "withdraw" AND atm_location = "Fifer Street"

-- The names of people who took the first flight on the 29th of July
SELECT name FROM people JOIN passengers ON people.passport_number = passengers.passport_number WHERE flight_id = (SELECT id FROM flights WHERE day = "29" AND month = "7" AND year = "2020" ORDER BY hour, minute LIMIT 1)

-- The names of people who made a call of less than 1 minute on the day of the crime
SELECT name FROM people JOIN phone_calls ON people.phone_number = phone_calls.caller WHERE day = "28" AND month = "7" AND year = "2020" AND duration < "60"

-- Take the intersection to get the name of the thief
SELECT name FROM people JOIN passengers ON people.passport_number = passengers.passport_number WHERE flight_id = (SELECT id FROM flights WHERE day = "29" AND month = "7" AND year = "2020" ORDER BY hour, minute LIMIT 1) INTERSECT SELECT DISTINCT name FROM people JOIN bank_accounts ON people.id = bank_accounts.person_id JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number WHERE day = "28" AND month = "7" AND year = "2020" AND transaction_type = "withdraw" AND atm_location = "Fifer Street" INTERSECT SELECT name FROM people JOIN phone_calls ON people.phone_number = phone_calls.caller WHERE day = "28" AND month = "7" AND year = "2020" AND duration < "60" INTERSECT SELECT name FROM people JOIN courthouse_security_logs ON people.license_plate = courthouse_security_logs.license_plate WHERE day = "28" AND month = "7" AND year = "2020" AND hour = "10" AND minute >= "15" AND minute < "25" AND activity = "exit"

SELECT city FROM airports WHERE id = (SELECT destination_airport_id FROM flights WHERE day = "29" AND month = "7" AND year = "2020" ORDER BY hour, minute LIMIT 1)

-- The Accomplice
SELECT name FROM people JOIN phone_calls ON people.phone_number = phone_calls.receiver WHERE day = "28" AND month = "7" AND year = "2020" AND duration < "60" AND caller = (SELECT phone_number FROM people WHERE name = "Ernest")

-- 
SELECT name, bakery_security_logs.hour, bakery_security_logs.minute FROM people JOIN bakery_security_logs ON people.license_plate = bakery_security_logs.license_plate WHERE bakery_security_logs.year = 2021 AND bakery_security_logs.month = 7 AND bakery_security_logs.day = 28 AND bakery_security_logs.activity = 'exit' AND bakery_security_logs.hour = 10 AND bakery_security_logs.minute >= 15 AND bakery_security_logs.minute <= 25 ORDER BY bakery_security_logs.minute;
