  select t_resources.t_name, t_users.t_nick
  from t_resources
  inner join t_users on t_users.t_id = t_resources.t_userid
  
  select t_resources.t_name, t_users.t_nick
  from t_resources,  t_users 
  where t_users.t_id = t_resources.t_userid
----------------------------------------  
   select t_resources.t_name, t_users.t_nick
  from t_resources
  left join t_users on t_users.t_id = t_resources.t_userid;
  
   select t_resources.t_name, t_users.t_nick
  from t_resources,  t_users 
  where  t_resources.t_userid=t_users.t_id(+);
  
 ------------------------------------------------------------ 
    select t_resources.t_name, t_users.t_nick
  from t_resources
  right join t_users on t_users.t_id = t_resources.t_userid
  
     select t_resources.t_name, t_users.t_nick
  from t_resources,  t_users 
  where  t_resources.t_userid(+)=t_users.t_id;
 --------------------------------------------------------------- 
      select t_resources.t_name, t_users.t_nick
  from t_resources
  full join t_users on t_users.t_id = t_resources.t_userid
  
       select t_resources.t_name, t_users.t_nick
  from t_resources,  t_users 
  where  t_resources.t_userid=t_users.t_id(+)
     union 
       select t_resources.t_name, t_users.t_nick
  from t_resources,  t_users 
  where  t_resources.t_userid(+)=t_users.t_id;
  -------------------------------------------------
  
  
  
  
    select *   from t_resources,  t_users 
 
  