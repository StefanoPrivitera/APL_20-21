import socket
import json
import sys
import base64
from Oggetto import Oggetto
HOST = '127.0.0.1'  # The server's hostname or IP address
# PORT = int(input("A quale porta ti vuoi collegare?"))

import tkinter #libreria per la gui
from tkinter import *
top = tkinter.Tk() #inizializzazione finestra principale


from tkinter import messagebox #gestione messaggi
top.geometry("400x300") #dimensione finestra

def pushDNS():
    top = tkinter.Tk() #inizializzazione finestra Push DNS
    Lport = Label(top, text = "Inserisci numero di porta ") #etichetta numero di porta
    Lport.pack( side = LEFT)  #posizione etichetta
    Eport = Entry(top, bd = 3) #campo testo di Numero di porta con bd=3 (dimensione del bordo che contiene il testo)
    Eport.pack(side = LEFT) #posizione campo testo
    Ldns = Label(top, text = "Inserisci dns") #etichetta dns
    Ldns.pack( side = LEFT) #posizione etichetta
    Edns = Entry(top, bd = 2) #campo testo di DNS con bd=2 (dimensione del bordo che contiene il testo)
    Edns.pack(side = LEFT) #posizione campo testo
    Lip = Label(top, text = "Inserisci ip") #etichetta ip
    Lip.pack( side = LEFT) #posizone etichetta
    Eip = Entry(top, bd = 1) #campo testo di IP con bd=1 (dimensione del bordo che contiene il testo)
    Eip.pack(side = LEFT) #posizone campo testo
    top.geometry("800x200") #dimensione finestra
    def callPush():
        if(Eport.get()!="" and Edns.get()!="" and Eip.get()!=""): #verifichiamo che i campi non siano vuoti
            PORT = int(Eport.get()) #numero di porta salvata nella variabile PORT
            ob = Oggetto(HOST, PORT) #creo oggetto con i parametri HOST e PORT
            ob.pushAll(Edns.get(), Eip.get()) #push ip e dns al nodo selezionato (HOST e PORTA)
            msg = messagebox.showinfo( "Status Push", "Successo") #messaggio di successo
            top.destroy() #chiusura automatica finestra
        else:
            msg = messagebox.showinfo( "Status Push", "Fallito, accertati di aver inserito correttamente porta, dns e ip") #messaggio di errore
    
    Bpush = Button(top, text = "Invio", command = callPush) #creazione del bottone che richiama la funzione callPush
    Bpush.place(x = 330,y = 130) #posizione del bottone

def printDNS():
    top = tkinter.Tk() #iniziializzazione finestra Print Dns
    Lport = Label(top, text = "Inserisci numero di porta ") #etichetta numero di porta
    Lport.pack( side = LEFT) #posizione etichetta
    Eport = Entry(top, bd = 3) #campo testo di Numero di porta con bd=3 (dimensione del bordo che contiene il testo)
    Eport.pack(side = LEFT) #posizione campo testo
    top.geometry("800x200") #dimensione finestra
    def callPrint():
        if(Eport.get()!=""): #verifica che il campo Porta non sia vuoto
            PORT = int(Eport.get()) #numero di porta salvata nella variabile PORT
            ob = Oggetto(HOST, PORT) #creo oggetto con i parametri HOST e PORT
            dns = ob.printDNS() #stampa tutti gli ip registrati in un dns
            msg = messagebox.showinfo( "Status Print: Successo", dns) #messaggio di successo
            top.destroy() #chiusura automatica finestra
        else:
            msg = messagebox.showinfo( "Status Push", "Fallito, accertati di aver inserito correttamente la porta") #messaggio di errore
    Bprint = Button(top, text = "Invio", command = callPrint) #creazione del bottone che richiama la funzione callPrint
    Bprint.place(x = 330,y = 130) #posizione del bottone

def searchDNS():
    top = tkinter.Tk() #iniziializzazione finestra Search Dns
    Lport = Label(top, text = "Inserisci numero di porta ") #etichetta numero di porta
    Lport.pack( side = LEFT) #posizione etichetta
    Eport = Entry(top, bd = 3) #campo testo di Numero di porta con bd=3 (dimensione del bordo che contiene il testo)
    Eport.pack(side = LEFT) #posizione campo testo
    Ldns = Label(top, text = "Inserisci dns") #etichetta DNS
    Ldns.pack( side = LEFT) #posizione etichetta
    Edns = Entry(top, bd = 2) #campo testo di DNS con bd=2 (dimensione del bordo che contiene il testo)
    Edns.pack(side = LEFT) #posizione campo testo
    top.geometry("800x200") #dimensione finestra
    def callSearch():
        if(Eport.get()!="" and Edns.get()!=""): #verifichiamo che i campi non siano vuoti
            PORT = int(Eport.get()) #numero di porta salvata nella variabile PORT
            ob = Oggetto(HOST, PORT) #numero di porta salvata nella variabile PORT
            dnsjson = ob.printDNS() #stampa tutti gli ip registrati in un dns
            if not (dnsjson.get(Edns.get()) is None): #controllo se il dns cercato è presente nella blockchain
                msg = messagebox.showinfo( "Status Search Dns", dnsjson.get(Edns.get())) #messaggio di successo, vengono stampati gli ip trovati per il dns cercato
                top.destroy() #chiusura automatica finestra
            else:
                msg = messagebox.showinfo( "Status Search Dns", "L'host non è stato trovato") #messaggio di errore, non è stato trovato alcun dns
                top.destroy() #chiusura automatica finestra
        else:
            msg = messagebox.showinfo( "Status Search Dns", "Fallito, accertati di aver inserito correttamente la porta e il dns da ricercare") #messaggio di errore, uno o tutti e due i campi sono vuoti 
    Bsearch = Button(top, text = "Invio", command = callSearch) #bottone che richiama la funzione callSearch
    Bsearch.place(x = 330,y = 130) #posizione bottone


Bpush = Button(top, text = "Pusha DNS e IP", command = pushDNS) #bottone che richiama la funzione pushDns
Bpush.place(x = 130,y = 130) #posizione bottone
Bprint = Button(top, text = "Print DNS e IP", command = printDNS) #bottone che richiama la funzione printDns
Bprint.place(x = -10,y = 130) #posizione bottone
Bsearch = Button(top, text = "Search DNS", command = searchDNS) #bottone che richiama la funzione searchDns
Bsearch.place(x = 300,y = 130) #posizione bottone
top.mainloop() #finestra principale resta in loop
    
    
