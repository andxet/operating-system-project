Progetto Sistemi Operativi 2011/2012

Scopo del progetto è realizzare un sistema di supporto a un centralino telefonico di HelpDesk, finalizzato allo smistamento e alla gestione delle telefonate pendenti, che realizzi la seguente specifica.
La realizzazione dovrà fare uso degli strumenti studiati durante il corso,teoria e laboratorio, sia per creare e gestire processi sia per sincronizzare l'esecuzione di processi tramite semafori, code di messaggi, memoria condivisa e segnali.

Processi
Vi sono due tipi di processi: processi cliente e processi helpdesk.
Ogni processo cliente ha una richiesta da porgere al sistema di HelpDesk, il quale però è attivo per una quantità di tempo giornaliera limitata e potrà quindi accettare e gestire un numero limitato di richieste.
Un processo cliente che si rivolga al servizio di HelpDesk deve poter distinguere fra i momenti in cui tale servizio è attivo e i momenti in cui non lo è e, in quest'ultimo caso, terminare immediatamente.
L'attesa di un processo cliente si svolge in due fasi: 
	1. ingresso nella “sala di attesa” del sistema di HelpDesk, possibile solo se il sistema è attivo. Si noti che la sala d'attesa deve avere una capienza limitata. Vi si può entrare solo se c'è un posto libero.
	2. La sala di attesa è organizzata in un insieme di code, una per ciascun operatore. Tutte le richieste in coda devono essere servite anche se l'orario di lavoro è concluso.
Il numero dei processi helpdesk è limitato e predefinito. Vengono creati tutti all'avvio dell'esecuzione del sistema di HelpDesk. Ogni processo helpdesk servirà una richiesta per volta, estraendola dalla coda delle richieste.
Di tanto in tanto un processo helpdesk potrà fare una pausa. Potrà fare pausa solo se nessun altro processo analogo è in pausa. Per evitare che i clienti in coda presso il processo in pausa attendano troppo tempo di essere serviti, i processi helpdesk vanno organizzati in una sequenza circolare. Il processo successivo, secondo la sequenza, a quello in pausa alternerà la gestione di una delle richieste sulla propria coda e di una delle richieste sulla coda del processo in pausa fino alla sua ripresa del servizio.
Processi aggiuntivi per la simulazione:
Occorrerà realizzare un generatore di processi clienti.
Sincronizzazione
	L'ingresso in sala d'attesa va gestito tramite un semaforo. La sala d'attesa stessa è invece da realizzare come un insieme di code di messaggi: il singolo cliente deposita in una delle code la propria richiesta e poi rimane in attesa di una risposta sulla medesima coda. La sequenza circolare di processi helpdesk va realizzata tramite un'area di memoria condivisa. Il tempo di lavoro limitato va, invece, realizzato tramite alarm. Per la sincronizzazione dei processi helpdesk in pausa ed i loro successori dovrete sviluppare una vostra soluzione originale.
Make e makefile
	La compilazione di tutti i programmi deve essere fatta tramite un unico makefile.
Requisiti di terminazione
La soluzione non deve produrre processi zombie né lasciare processi vivi e sospesi al suo termine. Non devono rimanere strutture di IPC di sorta allocate. L'interruzione del sistema di HelpDesk con control-C deve causare una terminazione pulita di tutta l'esecuzione.
