-- Продавцы, в городе которых есть заказчики
SELECT *
FROM Sal
WHERE city = ANY (SELECT city
                  FROM Cust);
SELECT *
from Sal
WHERE city IN (SELECT city
               FROM Cust);
               
 --Продавцы, для которых есть заказчики с именами  старшими по алфавиту относительно них.           
SELECT *
FROM Sal
WHERE sname < ANY (SELECT cname
                   FROM Cust);
               
SELECT *
FROM Sal outer
WHERE EXISTS (SELECT *
              FROM Cust inner
              WHERE outer.sname < inner.cname);
--разница в обработке NULL значений

--Заказчики с рейтингом большим, хоть одного заказчика из Рима

SELECT *
FROM Cust
WHERE rating > any  (SELECT rating
                    FROM Cust
                    WHERE city = 'Rome');


SELECT *
FROM Cust
WHERE rating > some (SELECT rating
                    FROM Cust
                    WHERE city = 'Rome');

-- все Заказы где стоимость приобретений, больше чем, по крайней мере, один из Заказов на 6-е Октября
SELECT *
FROM Ord
WHERE amt > ANY (SELECT amt
                 FROM Ord
                 WHERE odate = to_date('06.01.2006', 'dd.mm.yyyy'));

SELECT *
FROM Ord
WHERE amt > some (SELECT amt
                 FROM Ord
                 WHERE odate = to_date('06.01.2006', 'dd.mm.yyyy'));
select * from ord

--ALL
SELECT *
FROM Cust
WHERE rating = ALL (SELECT rating
                    FROM Cust
                    WHERE city = 'Rome');

SELECT *
FROM Cust outer
WHERE NOT EXISTS (SELECT *
                  FROM Cust inner
                  WHERE outer.rating <= inner.rating
                        AND inner.city = 'Rome');

SELECT *
FROM Cust
WHERE rating <> ALL (SELECT rating
                     FROM Cust
                     WHERE city = 'San Jose');
                     
--обработка пустых значений
SELECT *
FROM Cust
WHERE rating > ANY (SELECT rating
                    FROM Cust
                    WHERE city = 'Boston');

SELECT *
FROM Cust
WHERE rating > all (SELECT rating
                    FROM Cust
                    WHERE city = 'Boston');
                    
-----exists  и count
SELECT *
FROM Cust outer
WHERE NOT EXISTS (SELECT *
                  FROM cust inner
                  WHERE outer.rating <= inner.rating
                        AND inner.city = 'Rome');

SELECT *
FROM Cust outer
WHERE 1 > (SELECT COUNT (*)
           FROM Cust inner
           WHERE outer.rating <= inner.rating
                 AND inner.city = 'Rome');

