dat<-read.table("zad5.txt")
dat
plot(dat,type="p",main="Диаграмма рассеяния",xlab="X", ylab="Y")
> cl<-kmeans(dat,2)
plot(dat,col=ifelse(cl2$cluster==3,"red",ifelse((cl2$cluster==1),"blue","green")))
legend("topleft",legend=c("1","2", "3"),fill=c("blue","green","red"))
plot(dat,pch=ifelse(cl2$cluster==1,1,ifelse(cl2$cluster==2,2,3)))
legend("topleft",legend=c("1","2", "3"),pch=c(1,2,3))