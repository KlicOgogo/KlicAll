select datediff(now(), (select date from `Messages` order by date limit 1));
