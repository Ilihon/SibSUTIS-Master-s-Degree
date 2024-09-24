--��������� ���������� � ����������, ���� � ������ ����, ���� �� ��� �� ��� ����.
SELECT cnum, cname, city
FROM Cust
WHERE EXISTS (SELECT *
              FROM Cust
              WHERE city = 'San Jose');







--��������, � ������� ��������� ����������
SELECT distinct snum
FROM cust outer
WHERE EXISTS (SELECT *
              FROM Cust inner
              WHERE inner.snum = outer.snum AND
                    inner.cnum <> outer.cnum);
                    
--��������, � ������� �� ������ ������ ���������
SELECT DISTINCT snum
FROM Cust outer
WHERE NOT EXISTS (SELECT *
                  FROM Cust inner
                  WHERE inner.snum = outer.snum AND
                        inner.cnum <> outer.cnum);
select * from cust

--��������, � ������� ���������� ��������� � ������ ������� ������ �������
SELECT *
FROM Sal first
WHERE EXISTS (SELECT *
              FROM Cust second
              WHERE first.snum = second.snum AND
                    1 < (SELECT COUNT (*)
                         FROM Ord
                         WHERE Ord.cnum = second.cnum));

