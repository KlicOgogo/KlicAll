select name from `Users`
where (select count(*) from `Messages` 
where user_id = `Users`.id 
and date(date) = curdate() > 3);
