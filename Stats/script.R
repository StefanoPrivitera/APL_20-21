
#!/usr/bin/env Rscript
args = commandArgs(trailingOnly=TRUE)
port2 <- args;
client <- function(port2){ 

    con <- socketConnection(host="localhost", port = as.integer(port2), blocking=TRUE, server=FALSE, open="r+") #mi connnetto alla blockchain
    write_resp <- writeLines("5", con) #richiamo l'opzione 5 
    server_resp <- readLines(con, 1)
    close(con)
    return(server_resp)

}

json<-client(port2)
library("rjson")
result <- fromJSON(json)
result=result[-1]
node<-sapply(result, `[[`, 5) #per tutte le righe del json 
a <- table(node)
barplot(a, main="Blocchi risolti", xlab="Nodi") 