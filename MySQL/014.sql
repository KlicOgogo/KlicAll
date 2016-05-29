select name, date, text from `Users`, `Messages` 
where `Messages`.
user_id = `Users`.id and text like '%go%'
