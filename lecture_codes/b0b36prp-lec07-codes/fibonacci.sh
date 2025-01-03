#!/bin/sh

create_graph() {
   R --vanilla --slave <<RSCRIPT
   m<-read.table("$1", header=F, sep="\t")
   v<-as.matrix(m)
   pdf("$2", family="Times", onefile=FALSE, width=8.5, height=6)
   pcol=c('yellowgreen', 'cornflowerblue')
   y_max = round(max(m[,2:3]), -1)
   x_range = range(m[,1])
   plot(v[, 2], type='o', col=pcol[1], ylim=c(0, y_max), axes=T, ann=FALSE, cex.axis=1.0)
   x_tiks = 1:(x_range[2] - x_range[1] + 1)
   lines(x_tiks, v[,3], type="o", pch=22, lty=2, pcol[2])
   legend("topright", c('Recursion', 'Iteration'), cex=1.5, col=pcol, pch=21:24, lty=1:4, horiz=T, box.lwd=0, box.col='white', bg='white')
RSCRIPT
}
#title(xlab= expression(n))
#title(ylab='No. of Operations')

create_graph $@
