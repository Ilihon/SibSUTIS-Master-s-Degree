--nvl
select * from t

select nvl(t_amt, 0) from t where nvl(t_amt,0) <7