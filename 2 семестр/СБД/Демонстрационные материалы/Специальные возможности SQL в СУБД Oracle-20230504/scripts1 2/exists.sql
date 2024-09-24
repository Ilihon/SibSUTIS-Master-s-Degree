--Извлекать информацию о заказчиках, если и только если, один из них из Сан Хосе.
SELECT cnum, cname, city
FROM Cust
WHERE EXISTS (SELECT *
              FROM Cust
              WHERE city = 'San Jose');







--Продавцы, у которых несколько заказчиков
SELECT distinct snum
FROM cust outer
WHERE EXISTS (SELECT *
              FROM Cust inner
              WHERE inner.snum = outer.snum AND
                    inner.cnum <> outer.cnum);
                    
--Продавцы, у которых не больше одного заказчика
SELECT DISTINCT snum
FROM Cust outer
WHERE NOT EXISTS (SELECT *
                  FROM Cust inner
                  WHERE inner.snum = outer.snum AND
                        inner.cnum <> outer.cnum);
select * from cust

--Продавцы, у которых существуют заказчики с числом заказов больше единицы
SELECT *
FROM Sal first
WHERE EXISTS (SELECT *
              FROM Cust second
              WHERE first.snum = second.snum AND
                    1 < (SELECT COUNT (*)
                         FROM Ord
                         WHERE Ord.cnum = second.cnum));

