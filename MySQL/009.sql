select name, date from `Messages`, `Users`
where user_id=`Users`.id and length(`Messages`.text) > 140;
