-- 9. Names of all people who starred in a movie released in 2004, ordered by birth year
--SELECT name, id FROM people JOIN stars ON people.id = stars.person_id WHERE stars.movie_id = (SELECT id FROM movies WHERE year = 2004) ORDER BY people.birth;
SELECT name, id FROM people WHERE id IN (SELECT person_id FROM stars WHERE movie_id IN (SELECT id FROM movies WHERE year = 2004)) ORDER BY people.birth;
