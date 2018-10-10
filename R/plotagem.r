library(ggplot2)

result <- read.table("C:\\Users\\Derek Alves\\Desktop\\R\\Graficos.txt",header=F)
result = unlist(result)

i = j = 1
x = y1 = y2 = rep(0, length(result)/3)

while(i<=length(result)){
  x[j] = result[i]
  y1[j] = result[i+1]
  y2[j] = result[i+2]
  i = i + 3
  j = j + 1
}

dat1 <- data.frame(
  Number = x,
  lista = y1,
  tree = y2
)

p <- qplot(ylab = "Number of comparations", xlab = "Elements") +
  ggtitle("Lista vs ABB") + 
  theme(plot.title = element_text(size=18, face="bold",hjust=0.5)) +
  #geom_line(data = dat1, aes(x = Number, y = lista), size = 1, color = '#ce0606') + 
  geom_point(data = dat1, aes(x = Number, y = lista), size = 2, color = '#000000') + 
  #geom_line(data = dat1, aes(x = Number, y = tree), size = 1, color = '#003366') + 
  geom_point(data = dat1, aes(x = Number, y = tree), size = 2, color = '#0000CD')

print(p)
