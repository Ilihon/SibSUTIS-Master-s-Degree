select sname, (select max(amt) from ord b where a.snum=b.snum) max_ord
from sal a;



select sname, max(amt)
from sal, ord
where sal.snum=ord.snum
group by sname
