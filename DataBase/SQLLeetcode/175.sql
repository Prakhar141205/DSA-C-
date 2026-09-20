-- Just on the basis of column name never assume that these two columns are same in two tables

SELECT p.firstName, p.lastName, a.city, a.state 
FROM Person p
LEFT JOIN Address a 
ON p.personID = a.personID ;