-- ��������, � ������ ������� ���� ���������
SELECT *
FROM Sal
WHERE city = ANY (SELECT city
                  FROM Cust);
SELECT *
from Sal
WHERE city IN (SELECT city
               FROM Cust);
               
 --��������, ��� ������� ���� ��������� � �������  �������� �� �������� ������������ ���.           
SELECT *
FROM Sal
WHERE sname < ANY (SELECT cname
                   FROM Cust);
               
SELECT *
FROM Sal outer
WHERE EXISTS (SELECT *
              FROM Cust inner
              WHERE outer.sname < inner.cname);
--������� � ��������� NULL ��������

--��������� � ��������� �������, ���� ������ ��������� �� ����

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

-- ��� ������ ��� ��������� ������������, ������ ���, �� ������� ����, ���� �� ������� �� 6-� �������
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
                     
--��������� ������ ��������
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
                    
-----exists  � count
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

