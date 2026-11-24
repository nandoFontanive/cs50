-- Keep a log of any SQL queries you execute as you solve the mystery.
-- Who the thief is
-- What city the thief escaped to New York City
-- Who the thief’s accomplice is who helped them escape

-- July 28, 2025 Humphrey Street
-- crime at 10:15 am

SELECT * FROM interviews WHERE transcript LIKE ("%bakery%") AND day = 28;
-- Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away. If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame.
SELECT license_plate FROM bakery_security_logs WHERE month = 7 AND day = 28 AND hour = 10 AND minute LIKE ("2%");
-- plates found using the above: G412CB7 L93JTIZ 322W7JE 0NTHK55
SELECT * FROM people WHERE license_plate IN (SELECT license_plate FROM bakery_security_logs WHERE month = 7 AND day = 28 AND hour = 10 AND minute LIKE ("2%"));
-- found this, exiting the bakery, thief is prolly here
|   id   |  name  |  phone_number  | passport_number | license_plate |
+--------+--------+----------------+-----------------+---------------+
| 396669 | Iman   | (829) 555-5269 |      7049073643 | L93JTIZ       |
| 398010 | Sofia  | (130) 555-0289 |      1695452385 | G412CB7       |
| 514354 | Diana  | (770) 555-1861 |      3592750733 | 322W7JE       |
| 560886 | Kelsey | (499) 555-9472 |      8294398571 | 0NTHK55       |


-- I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at Emma's bakery, I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money.
SELECT * FROM atm_transactions WHERE month = 7 AND day = 28 AND transaction_type = "withdraw" AND atm_location = "Leggett Street";
+-----+----------------+------+-------+-----+----------------+------------------+--------+
| id  | account_number | year | month | day |  atm_location  | transaction_type | amount |
+-----+----------------+------+-------+-----+----------------+------------------+--------+
| 246 |       28500762 | 2025 |     7 |  28 | Leggett Street | withdraw         |     48 |
| 264 |       28296815 | 2025 |     7 |  28 | Leggett Street | withdraw         |     20 |
| 266 |       76054385 | 2025 |     7 |  28 | Leggett Street | withdraw         |     60 |
| 267 |       49610011 | 2025 |     7 |  28 | Leggett Street | withdraw         |     50 |
| 269 |       16153065 | 2025 |     7 |  28 | Leggett Street | withdraw         |     80 |
| 288 |       25506511 | 2025 |     7 |  28 | Leggett Street | withdraw         |     20 |
| 313 |       81061156 | 2025 |     7 |  28 | Leggett Street | withdraw         |     30 |
| 336 |       26013199 | 2025 |     7 |  28 | Leggett Street | withdraw         |     35 |
+-----+----------------+------+-------+-----+----------------+------------------+--------+

SELECT * FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE month = 7 AND day = 28 AND transaction_type = "withdraw" AND atm_location = "Leggett Street");
+----------------+-----------+---------------+
| account_number | person_id | creation_year |
+----------------+-----------+---------------+
|       49610011 |    686048 |          2010 |
|       26013199 |    514354 |          2012 |
|       16153065 |    458378 |          2012 |
|       28296815 |    395717 |          2014 |
|       25506511 |    396669 |          2014 |
|       28500762 |    467400 |          2014 |
|       76054385 |    449774 |          2015 |
|       81061156 |    438727 |          2018 |
+----------------+-----------+---------------+

SELECT * FROM people WHERE id IN (SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE month = 7 AND day = 28 AND transaction_type = "withdraw" AND atm_location = "Leggett Street"));
+--------+---------+----------------+-----------------+---------------+
|   id   |  name   |  phone_number  | passport_number | license_plate |
+--------+---------+----------------+-----------------+---------------+
| 395717 | Kenny   | (826) 555-1652 |      9878712108 | 30G67EN       |
| 396669 | Iman    | (829) 555-5269 |      7049073643 | L93JTIZ       |
| 438727 | Benista | (338) 555-6650 |      9586786673 | 8X428L0       |
| 449774 | Taylor  | (286) 555-6063 |      1988161715 | 1106N58       |
| 458378 | Brooke  | (122) 555-4581 |      4408372428 | QX4YZN3       |
| 467400 | Luca    | (389) 555-5198 |      8496433585 | 4328GD8       |
| 514354 | Diana   | (770) 555-1861 |      3592750733 | 322W7JE       |
| 686048 | Bruce   | (367) 555-5533 |      5773159633 | 94KL13X       |
+--------+---------+----------------+-----------------+---------------+
-- thief is prolly in table above, may be Bruce Taylor Diana Kenny Benista


-- As the thief was leaving the bakery, they called someone who talked to them for less than a minute. In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ...
SELECT * FROM flights WHERE origin_airport_id = 8 AND day = 29;
-- flight ID is 36
SELECT * FROM people WHERE id IN (SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE month = 7 AND day = 28 AND transaction_type = "withdraw" AND atm_location = "Leggett Street")) AND passport_number IN (SELECT passport_number FROM passengers WHERE flight_id = 36);
+--------+--------+----------------+-----------------+---------------+
|   id   |  name  |  phone_number  | passport_number | license_plate |
+--------+--------+----------------+-----------------+---------------+
| 395717 | Kenny  | (826) 555-1652 |      9878712108 | 30G67EN       |
| 449774 | Taylor | (286) 555-6063 |      1988161715 | 1106N58       |
| 467400 | Luca   | (389) 555-5198 |      8496433585 | 4328GD8       |
| 686048 | Bruce  | (367) 555-5533 |      5773159633 | 94KL13X       |
+--------+--------+----------------+-----------------+---------------+
--thief and accomplice are prolly on table above

SELECT * FROM phone_calls WHERE day = 28 AND duration < 60 AND caller IN (SELECT phone_number FROM people WHERE id IN (SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE month = 7 AND day = 28 AND transaction_type = "withdraw" AND atm_location = "Leggett Street")));
+-----+----------------+----------------+------+-------+-----+----------+
| id  |     caller     |    receiver    | year | month | day | duration |
+-----+----------------+----------------+------+-------+-----+----------+
| 233 | (367) 555-5533 | (375) 555-8161 | 2025 |     7 |  28 |       45 |
| 254 | (286) 555-6063 | (676) 555-6554 | 2025 |     7 |  28 |       43 |
| 255 | (770) 555-1861 | (725) 555-3243 | 2025 |     7 |  28 |       49 |
| 279 | (826) 555-1652 | (066) 555-9701 | 2025 |     7 |  28 |       55 |
| 281 | (338) 555-6650 | (704) 555-2131 | 2025 |     7 |  28 |       54 |
+-----+----------------+----------------+------+-------+-----+----------+
-- table above prolly has both thief and accomplice


SELECT name, phone_number FROM people WHERE phone_number IN (SELECT receiver FROM phone_calls WHERE day = 28 AND duration < 60 AND caller IN (SELECT phone_number FROM people WHERE id IN (SELECT person_id FROM bank_accounts WHERE account_num
ber IN (SELECT account_number FROM atm_transactions WHERE month = 7 AND day = 28 AND transaction_type = "withdraw" AND atm_location = "Leggett Street"))));
+--------+----------------+
|  name  |  phone_number  |
+--------+----------------+
| James  | (676) 555-6554 |
| Anna   | (704) 555-2131 |
| Philip | (725) 555-3243 |
| Robin  | (375) 555-8161 |
| Doris  | (066) 555-9701 |
+--------+----------------+

