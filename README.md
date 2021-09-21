Il presente elaborato vuole sviluppare un’applicazione p2p ispirandosi alla blockchain Bitcoin.
<br>Il sistema è composto da 3 moduli software:
<br>&emsp;-C++ per la realizzazione della blockchain (Sviluppato da entrambi gli studenti)
<br>&emsp;-Python per il block explorer (Sviluppato da Nicola Pollino)
<br>&emsp;-R per le statistiche e i plot (Sviluppato da Stefano Privitera)
<br>Lo scopo è quello di creare un database decentralizzato che possa contenere dei record dns
<br><br>Modulo C++
<br>Essendo un sistema distribuito individuiamo nei nodi partecipanti la figura di attori principali, i quali:
<br>&emsp;1)Implementano un’applicazione peer to peer
<br>&emsp;2)Costituiscono un overlay network (lista di nodi attivi)
<br>&emsp;3)Detengono un insieme di informazioni organizzate in blocchi concatenati
<br>&emsp;4)Vengono interrogati
<br>&emsp;5)Propagano i record dns agli altri nodi
<br>&emsp;6)Collaborano per avere una copia aggiornata dei blocchi
<br>&emsp;7)Competono per aggiungere un nuovo blocco alla catena (mining) 
<br><br>Modulo Python
<br>L’applicativo permette di:
<br>&emsp;1)Propagare i record dns alla blockchain, contattando tutti i nodi attivi
<br>&emsp;2)Interrogare i nodi per la ricerca di record dns
<br><br>Modulo R
<br>Statistiche su blocchi risolti<br>
<h1>Usage<h1>
<h2>C++</h2>

Prerequisiti:<br>
	&emsp;-Installare Openssl<br>
Compilare:<br>
	&emsp;-Spostarsi nella cartella “BlockChain”<br>
	
	g++ main.cpp Miner.cpp Blocco.cpp BlockChain.cpp Server.cpp uint256_t/uint128_t.cpp uint256_t/uint256_t.cpp Node.cpp Gossiper.cpp -o main -lssl -lcrypto -std=c++11 -pthread
Uso:<br> 
	
	./main
&emsp;-Inserire porta da esporre es 9999<br>
&emsp;-Inserire porta di un nodo attivo es 8888 (se è il primo nodo inserire la stessa a quella esposta es 9999)<br>
&emsp;-Aprire più istanze per aggiungere nodi<br>
 <br>

<h2>Python</h2>

Prerequisiti:<br>
	&emsp;-Installare Tkinter per Python3<br> 
Uso:<br>
	&emsp;-Spostarsi nella cartella “DnsHandler”, mentre core c++ è in run<br>

	python3 parser.py 
<br>
		
<h2>R</h2>

Uso:<br>
	&emsp;-Spostarsi nella cartella “Stats”<br>
		Rscript script.R “numero porta es. 9999 passato da argv”, mentre core c++ è in run 
	
&emsp;-es. 
	
	Rscript script.R 9999 
	 
&emsp; Attendere qualche secondo
