select * from employees


--demo for explanation
SELECT employee_id, last_name, manager_id --count(*)
   FROM employees
    --where last_name='King'
    start with manager_id is null
      CONNECT BY PRIOR employee_id = manager_id -- "глава"

-- level
SELECT employee_id, last_name, manager_id, LEVEL
   FROM employees
    start with manager_id is null
   CONNECT BY PRIOR employee_id = manager_id;

--notes
select t.*, level from
(
  select 1 id,'a' name, null ref from dual
  union
  select 2,'b', 1 from dual
  union 
  select 3, 'c', 1 from dual
  ) t
 --start with ref is null
  connect by prior id=ref
  
  -- siblings
  SELECT last_name, employee_id, manager_id, LEVEL
      FROM employees
      START WITH employee_id = 100
      CONNECT BY PRIOR employee_id = manager_id
      ORDER siblings BY last_name;

--nocycle
select * from employees

UPDATE employees SET manager_id = 145
   WHERE employee_id = 100;

SELECT DEPARTMENT_ID,last_name "Employee", 
   LEVEL, SYS_CONNECT_BY_PATH(last_name, '/') "Path"
   FROM employees
  --WHERE department_id = 80
   START WITH EMPLOYEE_ID = 100
   CONNECT BY PRIOR employee_id = manager_id AND LEVEL <= 4;

SELECT employee_id, MANAGER_ID, FIRST_NAME, last_name "Employee", 
CONNECT_BY_ISCYCLE "Cycle",
   LEVEL, SYS_CONNECT_BY_PATH(last_name, '/') "Path"
   FROM employees
  --WHERE level <= 3 AND department_id = 80
   START WITH EMPLOYEE_ID = 100
   CONNECT BY NOCYCLE PRIOR employee_id = manager_id and LEVEL<=4;

--глава для работников 110 отдела 
SELECT last_name "Employee", CONNECT_BY_ROOT last_name "Manager",
   SYS_CONNECT_BY_PATH(last_name, '/') "Path", level
   FROM employees
   WHERE LEVEL > 1 and department_id = 110
   start with EMPLOYEE_ID=100
   CONNECT BY PRIOR employee_id = manager_id;


-- оформление
select lpad('+',level*2)||last_name tree from employees
start with manager_id is NULL
connect by manager_id=prior employee_id
order siblings by last_name



--применение


select rownum from dual
where rownum>1002
connect by rownum<(select max(snum) from sal)
minus
select snum from sal



select * from sal where rownum>5


--paging
select * from
(
select rownum rn from dual
connect by rownum < (select max(snum) from sal)
) t where t.rn>(select min(snum) from sal)


select * from sal

SELECT regexp_substr(a, '[^,]+', 1, level) as str
            FROM (SELECT 'f1,f2,f3' a FROM dual     ) 
            CONNECT BY regexp_substr(a, ',', 1,level-1) is not null;
           
           
           
           
            
 SELECT regexp_substr('f1,f2,f3', '[^,]+', 1, 2) from dual










 
 


  