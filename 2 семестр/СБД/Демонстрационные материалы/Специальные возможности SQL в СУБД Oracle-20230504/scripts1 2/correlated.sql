--������� ���������� � ����������, ��������� ������ 03.10.2006
SELECT cname
FROM Cust outer
WHERE to_date('03.01.2006','dd.mm.yyyy') IN (SELECT odate    FROM Ord inner
                     WHERE outer.cnum = inner.cnum);

SELECT distinct cname
FROM Cust first, Ord second
WHERE first.cnum = second.cnum AND second.odate = to_date('03.01.2006','dd.mm.yyyy');

--��������, � ������� ������ ������ ���������

SELECT snum, sname
FROM Sal main
WHERE 1 < (SELECT COUNT (*)
           FROM Cust
           WHERE snum = main.snum);
           
--�����

SELECT *
FROM Ord main
WHERE NOT snum = (SELECT snum
                  FROM Cust
                  WHERE cnum = main.cnum);
                  
                  
--����� ������ ��������� ������� ��� ������� ���������
SELECT *
FROM Ord outer
WHERE amt > (SELECT AVG (amt)
             FROM Ord inner
             WHERE inner.cnum = outer.cnum);

select cnum, avg(amt) from ord group by cnum;

--in having

Select odate, SUM (amt)
FROM ord a
GROUP BY odate
HAVING SUM (amt) > (SELECT 2000.00 + MAX (amt)
                     FROM Ord b
                     WHERE a.odate = b.odate);

select * from ord