select*from `Users`
where (select count(*) from `Messages` where user_id = `Users`.id) > 3;
