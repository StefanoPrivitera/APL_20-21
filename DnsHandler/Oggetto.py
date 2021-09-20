import json
import socket
import sys
import base64

class Oggetto:
    def __init__(self, host, port): #inizializzazione oggetto
        self.host = host  # The server's hostname or IP address
        self.port = port # Porta del server
    
    def printDNS(self):
        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s: #instaurazione connessione socket
            s.connect((self.host, self.port)) #connessione al nodo che ha come parametri un determinato host e una determinata porta
            s.sendall(b'5') #invio scelta = 5 (intera blockchain)
            blockchain = s.recv(2048*1000*1024) #salviamo il contenuto della blockchain del nodo nella variabile blockchain
            blockchain=blockchain.decode("utf-8")[:-1] #decode input
            s.close() #chiusura connessione
        blockjson = json.loads(blockchain) #conversione in json
        dnsjson="" #inizializzazione variabile
        for dict in blockjson: #ricerca ogni "file" nella blockchain
            if dict['file'] != "": #controllo se il file non è vuoto
                dictFile = json.loads(dict['file']) #salvo il singolo contenuto della riga di blockchain analizzata (se è presente il file)
                if(dnsjson!=""): #controllo se dnsjson non è vuoto
                    if not (dnsjson.get(dictFile["host"]) is None): #controllo se dnsjson ha già salvato un host
                        dnsjson[dictFile["host"]].append(({'ip': dictFile["ip"]})) #aggiungo l'ip all'host già salvato su dnsjson
                    else:
                        dnsjson.update({dictFile["host"]: [{'ip': dictFile["ip"]}]}) #aggiungo l'host e l'ip trovato sulla blockchain
                else:
                    dnsjson = json.loads(json.dumps({dictFile["host"]: [{'ip': dictFile["ip"]}]})) #inizializzo dnsjson con il valore host e ip relativo trovato su blockchain
        return dnsjson #ritorno dei dns e relativi ip

    def pushAll(self, dns, ip):
        encoded_string = json.dumps({'host': dns, 'ip': ip}) #codifica della stringa con i parametri dns e ip
        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s: #instaurazione connessione socket
            s.connect((self.host, self.port)) #connessione al nodo che ha come parametri l'host e la porta settata
            s.sendall(b'3') #invio scelta = 3 (lista nodi attivi)
            nodi=s.recv(2048*1000*1024) #salviamo i nodi presenti sulla blockchain
            nodi=nodi.decode("utf-8")[:-1] #decode input
            s.close() #chiusura connessione
        nodi_total = json.loads(nodi) #calcolo dei nodi presenti sulla blockchain
        for dict in nodi_total: #ricerca di ogni singolo nodo 
            with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s: #instaurazione connessione socket
                s.connect((self.host, int(dict))) #connessione nodo con la porta del nodo trovato del json
                s.sendall(b'4') #scelta = 4 (possibilità di scrivere una stringa custom sulla blockchain)
                s.sendall(encoded_string.encode("ascii")) #invio della stringa codificata in ascii
                s.close() #chiusura connessione
            print("pushato al nodo " + dict) #push stringa al nodo X
