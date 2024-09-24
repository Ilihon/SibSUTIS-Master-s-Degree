-- определение типов

--ассоциативный массив
TYPE birthdays_tt IS TABLE OF DATE 
INDEX BY PLS_INTEGER;

TYPE vcmax_aat IS TABLE OF VARCHAR2(32767)
    INDEX BY BINARY_INTEGER;

-- Nested table types
TYPE boolean_ntt IS TABLE OF BOOLEAN;

--varray
TYPE t_vla IS varray(100) OF varchar2(32) 



DECLARE
family_birthdays birthdays_tt;



--объявление и инициаилизация (явная)
DECLARE
TYPE company_aat IS TABLE OF varchar2(10) INDEX BY PLS_INTEGER;
premier_sponsor_list company_aat;
select_sponsor_list company_aat;
BEGIN
...
END;

DECLARE
TYPE company_aat IS TABLE OF varchar2(10);
premier_sponsor_list company_aat := company_aat();
BEGIN
...
END;

DECLARE
TYPE company_aat IS TABLE OF company%ROWTYPE;
premier_sponsor_list company_aat;
BEGIN
premier_sponsor_list:= company_aat();
END;

CREATE OR REPLACE TYPE color_tab_t
AS TABLE OF VARCHAR2(30);

DECLARE
my_favorite_colors color_tab_t := color_tab_t();
his_favorite_colors color_tab_t:= color_tab_t('PURPLE');
her_favorite_colors color_tab_t:= color_tab_t('PURPLE', 'GREEN');

begin
null;
end;


----------- Неявная инициализация присваиванием
DECLARE
   earth_colors     color_tab_t := color_tab_t ('BRICK', 'RUST', 'DIRT');
   wedding_colors   color_tab_t;
BEGIN
   wedding_colors := earth_colors;
   wedding_colors (3) := 'CANVAS';
END;

DECLARE
TYPE tt1 IS TABLE OF employees%ROWTYPE;
TYPE tt2 IS TABLE OF employees%ROWTYPE;
t1 tt1 := tt1();
t2 tt2 := tt2();
BEGIN
/* Ошибка "PLS-00382: expression is of wrong type" */
t1 := t2;
END;


DROP TABLE color_models

--select * from color_models

--неявная инициализация выборкой в переменную
CREATE TABLE color_models 
(model_type VARCHAR2 (12),
colors color_tab_t)
NESTED TABLE colors
   STORE AS color_model_colors_tab


BEGIN
   INSERT INTO color_models
       VALUES ('RGB', color_tab_t ('RED', 'GREEN', 'BLUE')
              );
END;

select * from color_models

DECLARE
   l_colors   color_tab_t;
BEGIN
   /* Retrieve all the nested values in a single fetch.
   || This is the cool part.
   */
   SELECT colors
     INTO l_colors
     FROM color_models
    WHERE model_type = 'RGB';
END;
/

DECLARE
   color_tab   color_tab_t;
BEGIN
   SELECT colors
     INTO color_tab
     FROM color_models
    WHERE model_type = 'RGB';

   FOR element IN 1 .. color_tab.COUNT
   LOOP
      IF color_tab (element) = 'RED'
      THEN
         color_tab (element) := 'FUSCHIA';
      END IF;
   END LOOP;

   /* Here is the cool part of this example. Only one insert
   || statement is needed -- it sends the entire nested table
   || back into the color_models table in the database. */

   INSERT INTO color_models
       VALUES ('FGB', color_tab
              );
END;


select * from color_models
/* VARRAY - аналогично, отличия.*/



-----------Заполнение данными (необходимость инициализации nested и varray + extend)

--простое присваивание значения
countdown_test_list (43) := 'Internal pressure';
company_names_table (last_name_row + 10) := 'Johnstone Clingers';

--вставка составного типа

/*DECLARE
   TYPE emp_copy_t IS TABLE OF employees%ROWTYPE;

   l_emps     emp_copy_t := emp_copy_t ();
   l_emprec   employees%ROWTYPE;
BEGIN
   l_emprec.first_name := 'Steven';
   l_emprec.salary := 10000;
   l_emps.EXTEND;
   l_emps (l_emps.LAST) := l_emprec;
END;
*/
--- агрегатное присваивание
DECLARE
   TYPE name_t IS TABLE OF VARCHAR2 (100)
                     INDEX BY PLS_INTEGER;

   old_names   name_t;
   new_names   name_t;
BEGIN
   /* Assign values to old_names table */
   old_names (1) := 'Smith';
   old_names (2) := 'Harrison';

   /* Assign values to new_names table */
   new_names (111) := 'Hanrahan';
   new_names (342) := 'Blimey';

   /* Transfer values from new to old */
   old_names := new_names;

   /* This statement will display 'Hanrahan' */
   DBMS_OUTPUT.put_line (
      old_names.FIRST || ': ' || old_names (old_names.FIRST)
   );
END;

set serveroutput on

-- присваивание из БД
set serveroutput on

DECLARE
TYPE emp_copy_t IS TABLE OF varchar2(100);
l_emps emp_copy_t := emp_copy_t();


BEGIN
l_emps.EXTEND;
SELECT last_name 
INTO l_emps(1) 
FROM employees
WHERE employee_id =100;

dbms_output.put_line(l_emps(1));
END;

--последовательное заполнение коллекции
DECLARE
TYPE emp_copy_t IS TABLE OF varchar2(100);
l_emps emp_copy_t := emp_copy_t();
BEGIN
FOR emp_rec IN (SELECT last_name FROM employees)
LOOP
l_emps.EXTEND;
l_emps (l_emps.LAST) := emp_rec;
END LOOP;
END;

DECLARE
TYPE emp_copy_nt IS TABLE OF employees%ROWTYPE;
l_emps emp_copy_nt;
BEGIN
SELECT * BULK COLLECT INTO l_emps FROM employees;
END;

/*
--непоследовательное заполнение

DECLARE
   TYPE emp_copy_t IS TABLE OF employees%ROWTYPE
                         INDEX BY PLS_INTEGER;

   l_emps   emp_copy_t;
BEGIN
   FOR emp_rec IN (SELECT *
                     FROM employees)
   LOOP
      l_emps (emp_rec.employee_id) := emp_rec;
   END LOOP;
END;
*/

--кэширование  10000 => 2с vs 0.1с
DROP TABLE hairstyles;

CREATE TABLE hairstyles (
   code INTEGER,
   description VARCHAR2(100)
   );

INSERT INTO hairstyles VALUES (1000, 'CREWCUT');
INSERT INTO hairstyles VALUES (1001, 'BOB');
INSERT INTO hairstyles VALUES (1002, 'SHAG');
INSERT INTO hairstyles VALUES (1003, 'BOUFFANT');
INSERT INTO hairstyles VALUES (1004, 'PAGEBOY');

CREATE OR REPLACE PACKAGE justonce
IS
   FUNCTION description (code_in IN hairstyles.code%TYPE)
      RETURN hairstyles.description%TYPE;
END justonce;
/

CREATE OR REPLACE PACKAGE BODY justonce
IS
   TYPE desc_t IS TABLE OF hairstyles.description%TYPE
      INDEX BY BINARY_INTEGER;
   descriptions   desc_t;

   FUNCTION description (code_in IN hairstyles.code%TYPE)
      RETURN hairstyles.description%TYPE
   IS
      return_value   hairstyles.description%TYPE;

      FUNCTION desc_from_database RETURN hairstyles.description%TYPE
      IS
         CURSOR desc_cur IS
            SELECT description FROM hairstyles WHERE code = code_in;
         desc_rec   desc_cur%ROWTYPE;
      BEGIN
         OPEN desc_cur;
         FETCH desc_cur INTO desc_rec;
         RETURN desc_rec.description;
      END;
   BEGIN
      RETURN descriptions (code_in);
   EXCEPTION
      WHEN NO_DATA_FOUND 
	  THEN
         descriptions (code_in) := desc_from_database;
         RETURN descriptions (code_in);
   END;
END justonce;
/

BEGIN
   DBMS_OUTPUT.PUT_LINE (justonce.description (1000));
   DBMS_OUTPUT.PUT_LINE (justonce.description (1002));
   DBMS_OUTPUT.PUT_LINE (justonce.description (1004));
END;
/



--строковое индексирование
DECLARE
   SUBTYPE location_t IS VARCHAR2(64);
   TYPE population_type IS TABLE OF NUMBER INDEX BY varchar2(1000);
      
   l_country_population population_type;
   l_continent_population population_type;
   
   l_count PLS_INTEGER;
   l_location location_t;
BEGIN
   l_country_population('Greenland') := 100000;
   l_country_population('Iceland') := 750000;
     
   l_continent_population('Australia') := 30000000;
   l_continent_population('Antarctica') := 1000;
   l_continent_population('antarctica') := 1001; 

   l_count := l_country_population.COUNT;
   DBMS_OUTPUT.PUT_LINE ('COUNT = ' || l_count);
 
   l_location := l_continent_population.FIRST; 
   DBMS_OUTPUT.PUT_LINE ('FIRST row = ' || l_location);
   DBMS_OUTPUT.PUT_LINE ('FIRST value = ' || l_continent_population(l_location));
   
   l_location := l_continent_population.LAST; 
   DBMS_OUTPUT.PUT_LINE ('LAST row = ' || l_location);
   DBMS_OUTPUT.PUT_LINE ('LAST value = ' || l_continent_population(l_location));
END;    
/


-- string tracker packages here
------

CREATE OR REPLACE PROCEDURE make_adjustment (NAME_IN IN VARCHAR2)
IS
BEGIN
   NULL;
END;
/

DECLARE
   c_delimiter   CONSTANT CHAR (1) := '^';

   TYPE strings_t IS TABLE OF employees%ROWTYPE
                        INDEX BY employees.email%TYPE;

   TYPE ids_t IS TABLE OF employees%ROWTYPE
                    INDEX BY PLS_INTEGER;

   by_name       strings_t;
   by_email      strings_t;
   by_id         ids_t;

   ceo_name employees.last_name%TYPE
         := 'King' || c_delimiter || 'Steven';

   PROCEDURE load_arrays
   IS
   BEGIN
      /* Load up all three arrays from rows in table. */
      FOR rec IN (SELECT *
                    FROM employees)
      LOOP
         by_name (rec.last_name || c_delimiter || rec.first_name) := rec;
         by_email (rec.email) := rec;
         by_id (rec.employee_id) := rec;
      END LOOP;
   END;
BEGIN
   load_arrays;

   /* Now I can retrieve information by name or by ID. */

   IF by_name (ceo_name).salary > by_id (100).salary
   THEN
      make_adjustment (ceo_name);
   END IF;
   
END;


--printArray ?

--Работа с коллекциями в SQL
-----------CAST
DECLARE
a NUMBER := -123.45;
a1 VARCHAR2(30);
BEGIN
a1 := CAST (a AS VARCHAR2);

DBMS_OUTPUT.PUT_LINE(substr(a1,1,5));
--
END;

/*
create TYPE some_nt is varray(100) OF VARCHAR2(30) ;
create TYPE some1_nt is table OF VARCHAR2(30) index by pls_integer ;

create TYPE color_nt AS TABLE OF VARCHAR2(30);

create TYPE color_vat AS VARRAY(16) OF VARCHAR2(30);

create TABLE color_models_on_varray (
model_type VARCHAR2(12),
colors color_vat);

INSERT INTO color_models_on_varray
       VALUES ('FGB', color_vat ('FUSCHIA', 'GREEN', 'BLUE')
              );
select * from color_models_on_varray

SELECT COLUMN_VALUE my_colors
FROM TABLE (SELECT colors
FROM color_models_on_varray
WHERE model_type = 'RGB')

SELECT cast(colors  as color_nt)
FROM color_models_on_varray
WHERE model_type = 'RGB'

*/

--COLLECT
/*select * from cust
group by snum
*/

SELECT department_id, CAST (COLLECT (last_name ORDER BY hire_date desc) AS strings_nt) AS by_hire_date
 FROM employees
GROUP BY department_id

select * from employees

SELECT department_id,
 CAST (COLLECT ( job_id) AS strings_nt)
 AS unique_jobs
 FROM employees
 GROUP BY department_id
 
 --MULTISET
 --CREATE TYPE country_tab_t AS TABLE OF VARCHAR2(60);
 
 select * from birds
 SELECT * FROM bird_habitats
 
 SELECT b.genus, b.species,
CAST(MULTISET(SELECT bh.country FROM bird_habitats bh
WHERE bh.genus = b.genus
and bh.species = b.species
)
AS country_tab_t)
FROM birds b;

group by 

--TABLE

SELECT *
FROM table_name
WHERE collection_column
HAS CONTENTS 'whatever'; 


SELECT *
FROM color_models c
WHERE 'RED' IN
(
SELECT * FROM TABLE(c.colors)
);



/* Referencing the nested table inside a query */
CREATE OR REPLACE TYPE list_of_names_t
   IS TABLE OF VARCHAR2 (100);





DECLARE
   happyfamily   list_of_names_t := list_of_names_t ();
BEGIN
   happyfamily.EXTEND (4);
   happyfamily (1) := 'Eli';
   happyfamily (2) := 'Steven';
   happyfamily (3) := 'Chris';
   happyfamily (4) := 'Veva';

   /* Use TABLE operator to apply SQL operations to
      a PL/SQL nested table */

   FOR rec IN (  SELECT COLUMN_VALUE family_name
                   FROM TABLE (happyfamily)
               ORDER BY family_name)
   LOOP
      DBMS_OUTPUT.put_line (rec.family_name);
   END LOOP;
END;



DECLARE
   happyfamily   list_of_names_t := list_of_names_t ();
  type tcur is ref cursor;
  cv tcur;
  str varchar2(100);
   p1 varchar2(100);
  p2 varchar2(100);
   px varchar2(100);
  v1 varchar2(100);
  v2 varchar2(100);
   vx varchar2(100);
   
   s varchar2(1000);
BEGIN
    v1:='Motica';
    v2:='London'; 
    vx:=' and '; 
    
    p1:='sname=:x';
    p2:='city=:y';  
    px:=' :z ';
     s:='select  sname from sal where '||p1||px|| p2 ;
           dbms_output.put_line(s);
  open cv for s using v1, vx, v2;  
    loop
      
      fetch  cv into str;
     
      EXIT WHEN cv%NOTFOUND;
      
       dbms_output.put_line(str);
     end loop;
    close cv; 
    

END;



select * from sal
select  sname from sal where sname='Motica' and city='London'








/*
--сортировка
CREATE TYPE names_t AS TABLE OF VARCHAR2 (100)
/

CREATE TYPE authors_t AS TABLE OF VARCHAR2 (100);

CREATE TABLE favorite_authors (name VARCHAR2 (200))
/

BEGIN
   INSERT INTO favorite_authors
       VALUES ('Robert Harris'
              );

   INSERT INTO favorite_authors
       VALUES ('Tom Segev'
              );

   INSERT INTO favorite_authors
       VALUES ('Toni Morrison'
              );
END;
/

DECLARE
   scifi_favorites authors_t
         := authors_t ('Sheri S. Tepper', 'Orson Scott Card', 'Gene Wolfe');
BEGIN
   DBMS_OUTPUT.put_line ('I recommend that you read books by:');

   FOR rec IN (SELECT COLUMN_VALUE favs
                 FROM table (scifi_favorites AS names_t))
               UNION
               SELECT name
                 FROM favorite_authors)
   LOOP
      DBMS_OUTPUT.put_line (rec.favs);
   END LOOP;
END;
/

DECLARE
   scifi_favorites authors_t
         := authors_t ('Sheri S. Tepper', 'Orson Scott Card', 'Gene Wolfe');
BEGIN
   DBMS_OUTPUT.put_line ('I recommend that you read books by:');

   FOR rec IN (  SELECT COLUMN_VALUE favs
                   FROM table (CAST (scifi_favorites AS names_t))
               ORDER BY COLUMN_VALUE)
   LOOP
      DBMS_OUTPUT.put_line (rec.favs);
   END LOOP;
END;
/
*/
-- мультимножества




