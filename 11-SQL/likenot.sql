# https://www.hackerrank.com/challenges/weather-observation-station-9/problem
select city from station where city not like 'A%' and city not like 'E%' and city not like 'U%' and city not like 'I%' and city not like 'O%' group by city;