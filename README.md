# LanParty
A C project using different data structures  



Rezumat

Crearea listei s-a facut inserand element cu element la inceputul listei.Stergere echipelor cu scorul minimm se face returnand pointer la echipa imediat dupa cea stearsa.Echipe se baga pe o coada si sunt scoase doua cate doua.Castigatorii sunt separati de pierzatori prind doua stive.Se repeta pana ramane o singura echipa.Se creeaza un nod de in arbor, iar apoi se insereaza una cate una echipele ramase pentru a pastra forma de BST.


scorEchipa(Echipa *p) 
calculeaza media aritmetica a xp-ului jucatorilor din echipa p.



afisare(FILE *f, Echipa *c) 
scrie in fisier numele echipelor aflate in lista la acel moment.


creareLista(char *nume, int *nrEchipe, Echipa **head) 
citeste datele din fisierul de intrare si insereaza cate o echipa la inceputul listei 


gasireMinim(Echipa *head) 
primeste pointer la inceputul listei si cauta echipa cu cea mai mica medie a jucatorilor.


cateEchipeRaman(int *nrEchipe) 
transmite prin referinte numarul de echipe egal cu puterea cea mai mare a lui 2, dar mai mica ca numarul initial de echipe.


eliberareMemorie(Echipa *E)
elibereaza memoria echipelor si jucatorilor respectivi de care nu mai avem nevoie la task ul 4 


stergeElem(Echipa **head, Echipa **poz, int *numEchipa) 
sterge echipa cu punctajul cel mai mic, apoi continua sa acaute minimul in lista.
Daca capul listei are punctajul minim, in sterge si continua de acolo cautarea.


sterge(Echipa **head, int nrEchipeInitial, int nrEchipe) 
sterge cate echipe e nevoie pentru a ramane la final cu un numar egal cu cu cea mai mare putere a lui 2 disponibila


creareElem(Echipa *elem) 
imi creeaza un element pentru stiva


isEmpty verifica daca stiva e goala


push baga element pe stiva


pop scoate elementul din stiva


deleteStack sterge toate elementele din stiva de pierzatori fara a elibera memoria


qIsEmpty verifica daca coada e goala


enQueue baga element in coada


deQueue scoate element din coada


deleteStackSiMemorie(nodStiva **top)
sterge elementele din stiva de pierzatori si elibereaza memoria echiplor si a jucatorilor


creareMeciuri(Echipa *head, nodStiva *sCastig, nodStiva *sPierz, int counter, FILE *file) 
imi ia echipele doua cate doua si separa castigatorii de pierzatori prin doua stive, iar pierzatorii sunt stersi de fiecare data. Se repeta procesul pana ramane o siungura echipa, dar ultimelor 8 echipe nu li se elibereaza memoria deoarece vom avea nevoie de ele.


inorder(FILE *file, BSTnode *root)
scrie in fisier echipele ramase in ordinea descrescatoare a scorurilor


createRoot(Echipa *elem)
creeaza radacina arborelui


insert(BSTnode *root, Echipa *elem, char nume[3])
creeaza un element din arbore si il pune in asa fel incat BSTul/AVLul sa si pastreze proprietatile 


createBST(FILE *file, BSTnode *root, Echipa *head)
se foloseste de cele 3 functii anterioare pentru a creea un BST conform cerintei de la taskul 4


int height(BSTnode *root)
calculeaza inaltimea unui nod


*rightRotation( BSTnode *root)
roteste aroborele la dreapta


*leftRotation( BSTnode *root)
roteste aroborele la stanga


LRRotation(BSTnode *N)
roteste aroborele la stanga si apoi dreapta


RLRotation(BSTnode *N)
roteste aroborele la dreapta si apoi stanga


void printLevel(FILE* file, BSTnode *root, int level)
afiseaza  elementele de pe nivelul respectiv


void *createAVL(FILE *file, BSTnode *root, Echipa *head)
creaza AVL ul
