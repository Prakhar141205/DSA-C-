# Write your MySQL query statement below
select customer_number

from Orders o
group by customer_number 
order by count(customer_number) DESC
LIMIT 1; 
