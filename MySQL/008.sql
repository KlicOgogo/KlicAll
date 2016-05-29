select name, date, text from `Messages`, `Users`
where user_id = `Users`.id
order by date;