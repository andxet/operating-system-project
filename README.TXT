Readme.txt

-->IMPORTANTE 4 PERET: Ho cambiato che quando viene istanziato l'HD lo stato dello HD->inPausa di default è 0, se al posto di 0 c'è un valore quello per forza è la key dell'operatore che è in pausa
	
	Se servo un processo del mio collega devo incrementare il semaforo suo! --> OK fatto
	Se ho 2 op e l'op 1 va in pausa le richieste devono essere svolte dall'op 2, ma se l'op2 non ha ancora ricevuto richieste o la sua coda è vuota lui è bloccato ad aspettare un messaggio sulla sua coda perciò non può servire i miei client
	


Poblemi:

Controllare:


************************************************
Note Finali :
	- Per ora ho inserito il limitatore di processi client per evitare di sovraccaricare tutto, dopo pusho una nuova versione con una nostra prinft personalizzata che viene controllata dal log.

Per ora sembra girare correttamente senza che gli operatori vadano in pausa... provate e ditemi :D

Problema trovato!!! e risolto...
	Ho notato che gli operatori continuavano a svolgere richieste che gli erano arrivate anche se l'HD era chiuso, questo è causato dal fatto che le richieste che ricevevano erano di processi che si erano addormentati sul semaforo, perciò non erano ancora nella coda di messaggi e perciò le devo eliminare.
	Per scartare queste richieste dovrei sapere al momento della chiusura dell HD quanti processi ho nella mia coda, dopodiche quando termino di servire quelli che sono in coda tutti gli altri che mi entrano dal semaforo gli devo dare la risposta che l'HD è chiuso.
	
	Per implementarlo ci sono 2 soluzioni :
	1: La + pesante; Consiste nel controllare ad ogni ciclo lo stato dell'HD, come lo becco che è chiuso entro in un'altra procedura per l'evasione dei messaggi che memorizza quante richieste devo ancora eseguire e poi eseguite quelle si blocca per poi reimpostare una volta finito il valore di default del semaforo
	2: La + fika; Quando il server cambia stato, invia anche a tutti gli operatori un SEGNALE, gli op quando ricevono il segnale attivano la procedura secondaria che è come quella di sopra.
	
	Ormai i processi che sono addormentati su quel semaforo sono obbligato a farli entrare e a dargli una risposta non valida
