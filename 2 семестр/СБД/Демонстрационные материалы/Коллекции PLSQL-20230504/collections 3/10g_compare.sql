DECLARE
   TYPE clientele IS TABLE OF VARCHAR2 (64);

   group1   clientele := clientele ('Customer 1', 'Customer 2');
   group2   clientele := clientele ('Customer 1', 'Customer 3');
   group3   clientele := clientele ('Customer 3', 'Customer 1');
BEGIN
  

   IF group2 != group3
   THEN
      DBMS_OUTPUT.put_line ('Group 2 != Group 3');
   ELSIF group2 = group3
   THEN
      DBMS_OUTPUT.put_line ('Group 2 = Group 3');	  
   END IF;
END;
/