select name, count(*) from `Users`, `Messages`
where `Messages`.date >= '2016-05-09 00:00:00' and 
`Messages`.date < '2016-05-10 00:00:00' 
and `Messages`.user_id = `Users`.id
group by `Users`.name;

