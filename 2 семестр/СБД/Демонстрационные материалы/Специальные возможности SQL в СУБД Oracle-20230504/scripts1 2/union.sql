

select * (select 'x','y' from dual) t1, (select 'a','b' from dual) b;






--all, intersect, minus
SELECT snum, city
FROM Cust

intersect

SELECT snum, city
FROM Sal;
