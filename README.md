<h2>C++</h2>

Prerequisiti:<br>
	&emsp;-Installare Openssl<br>
Compilare:<br>
	&emsp;-Spostarsi nella cartella “BlockChain”<br>
	
	#g++ main.cpp Miner.cpp Blocco.cpp BlockChain.cpp Server.cpp uint256_t/uint128_t.cpp uint256_t/uint256_t.cpp Node.cpp Gossiper.cpp -o main -lssl -lcrypto -std=c++11 -pthread
Uso:<br> 
	
	#./main
&emsp;-Inserire porta da esporre es 9999<br>
&emsp;-Inserire porta di un nodo attivo es 8888 (se è il primo nodo inserire la stessa a quella esposta es 9999)<br>
&emsp;-Aprire più istanze per aggiungere nodi<br>
 <br>

<h2>Python</h2>

Prerequisiti:<br>
	&emsp;-Installare Tkinter per Python3<br> 
Uso:<br>
	&emsp;-Spostarsi nella cartella “DnsHandler”<br>

	#python3 parser.py 
<br>
		
<h2>R</h2>

Uso:<br>
	&emsp;-Spostarsi nella cartella “Stats”<br>
		#Rscript script.R “numero porta es. 9999 passato da argv”
	
&emsp;-es. 
	
	#Rscript script.R 9999 
	 
	
