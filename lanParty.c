#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct Jucator
{
    char *nume, *prenume;
    int xp;
} Jucator;

typedef struct Echipa
{
    int nrJucatori;
    char *numeEchipa;
    struct Echipa *next;
    Jucator *J;
} Echipa;



float scorEchipa(Echipa *p)
{
    float suma=0, medie;
    int i;

    if(p==NULL) return 100000;

    for(i=0; i<p->nrJucatori; i++)

        suma += p->J[i].xp;

    medie = suma/p->nrJucatori;

    return medie;
}


void  afisare(FILE *f, Echipa *c)
{
    while(c != NULL)
    {
        fprintf(f, "%s\n", c->numeEchipa );
        c = c->next;
    }
}


void creareLista(char *nume, int *nrEchipe, Echipa **head)
{
    FILE *f1=fopen(nume, "rt");
    if(f1 == NULL)
    {
        printf("nu-i frumos");
        exit(1);
    }

    Echipa *p, *q;
    int i, j;

    fscanf(f1, "%d", nrEchipe);
    p = (Echipa*)malloc(sizeof(Echipa));

    fscanf(f1, "%d", &p->nrJucatori);

    p->numeEchipa = (char*)malloc(sizeof(char)*41);
    fscanf ( f1, "%[^\n]s", p->numeEchipa);

    p->J = (Jucator*)malloc(sizeof(Jucator)*(p->nrJucatori));

    for(i=0; i<(p->nrJucatori); i++)
    {
        p->J[i].nume = (char*)malloc(sizeof(char)*20);
        p->J[i].prenume = (char*)malloc(sizeof(char)*20);

        fscanf(f1, "%s", p->J[i].nume);
        fscanf(f1, "%s", p->J[i].prenume);
        fscanf(f1, "%d", &p->J[i].xp);
    }
    p->next = NULL;
    *head = p;

    for( j=1; j<(*nrEchipe); j++)
    {
        q = (Echipa*)malloc(sizeof(Echipa));
        fscanf(f1, "%d", &q->nrJucatori);
        q->J = (Jucator*)malloc(sizeof(Jucator) * q->nrJucatori);
        q->numeEchipa = (char*)malloc(sizeof(char)*41);
        fscanf( f1, "%[^\n]s", q->numeEchipa);


        for(i=0; i<(q->nrJucatori); i++)
        {
            q->J[i].nume = (char*)malloc(sizeof(char)*20);
            q->J[i].prenume = (char*)malloc(sizeof(char)*20);
            fscanf(f1, "%s", q->J[i].nume);
            fscanf(f1, "%s", q->J[i].prenume);
            fscanf(f1, "%d", &q->J[i].xp);
        }

        q->next = *head;
        *head = q;


    }
    fclose(f1);

}


float gasireMinim(Echipa *head)
{
    Echipa *p;

    float min = scorEchipa(head);

    for(p=head; p!=NULL; p=p->next)
        if( min > scorEchipa(p))
            min = scorEchipa(p);

    return min;
    printf("%f", min);
}


void cateEchipeRaman(int *nrEchipe)
{
    int m=1;

    while(m<<1 <= (*nrEchipe))
        m = m<<1;

    (*nrEchipe) = m;

}


void eliberareMemorie(Echipa *E)
{
    for(int i=0; i<E->nrJucatori; i++)
    {
        free(E->J[i].nume);
        free(E->J[i].prenume);
    }
     free(E->numeEchipa);
     free(E->J);
     free(E);
}

Echipa *stergeElem(Echipa **head, Echipa **poz, int *numEchipa)
{
    Echipa *p, *q, *k;

    if(*poz == NULL)
        return NULL;
    else
    {
        if(scorEchipa(*head) == gasireMinim(*head))
        {
            p = *head;
            *head = (*head)->next;
            eliberareMemorie(p);
            (*numEchipa)--;
            return *head;
        }
        p = *poz;

        while(p != NULL)
        {
            if(scorEchipa(p) == gasireMinim(*head))
            {
                q = p;
                p = p->next;
                k = *head;


                while(k->next != q)
                    k = k->next;

                k->next = q->next;
                (*numEchipa)--;
                eliberareMemorie(q);
                return p;
            }

            p = p->next;

        }
    }
}


void sterge(Echipa **head, int nrEchipeInitial, int nrEchipe)
{
    struct Echipa *copy;

    copy = *head;

    while(nrEchipe != nrEchipeInitial )
    {
        copy = stergeElem(head, &copy , &nrEchipeInitial);

        if ( copy == NULL )
            copy = *head;
    }
}


typedef struct Dumnezeu
{
    Echipa *E1;
    struct Dumnezeu *next;
} nodStiva;


nodStiva* creareElem(Echipa *elem)
{
    nodStiva* Ra;
    Ra = (nodStiva*)malloc(sizeof(nodStiva));
    Ra->E1 = elem;
    Ra->next = NULL;
    return Ra;
}


int isEmpty(nodStiva *top)
{
    return (top==NULL);
}

void push(nodStiva **top, Echipa *elem)
{
    nodStiva *aux;
    if(*top == NULL)
        *top = creareElem(elem);
    else
    {
        aux = creareElem(elem);
        aux->next = *top;
        *top = aux;
    }
}


Echipa* pop(nodStiva **top)
{
    if(isEmpty(*top) == 1)
        return NULL;

    nodStiva *temp = *top;
    Echipa *aux;
    aux = (*top)->E1;
    *top = (*top)->next;
    free(temp);
    return aux;
}

void deleteStack(nodStiva **top)
{
    nodStiva *temp;
    while((*top)!=NULL)
    {
        temp = *top;
        *top = (*top)->next;
        free(temp);
    }
}


typedef struct Q
{
    nodStiva *front, *rear;
} Queue;


int qIsEmpty(Queue *q)
{
    return (q->front==NULL);
}

Queue *createQueue()
{
    Queue *q;
    q=(Queue*)malloc(sizeof(Queue));
    q->front = NULL;
    q->rear = NULL;
    return q;
}


void enQueue(Queue *q, Echipa *E)
{
    nodStiva *newStack = creareElem(E);


    if(q->rear == NULL)
        q->rear = newStack;
    else
    {
        q->rear->next = newStack;
        q->rear = newStack;
    }

    if(q->front==NULL)
        q->front=q->rear;
}


Echipa* deQueue(Queue *q)
{
    if(qIsEmpty(q))
        return NULL;

    nodStiva *newStack = NULL;
    Echipa* aux;

    newStack = q->front;
    aux = newStack->E1;
    q->front = (q->front)->next;
    free(newStack);
    return aux;
}




void deleteStackSiMemorie(nodStiva **top)
{
    nodStiva *temp;
    while((*top)!=NULL)
    {
        temp = *top;
        *top = (*top)->next;
        eliberareMemorie(temp->E1);
        free(temp);
    }
}



Echipa* creareMeciuri(Echipa *head, nodStiva *sCastig, nodStiva *sPierz, int counter, FILE *file)
{
    Queue *q;

    q=createQueue();

   while(head != NULL)
    {   
        enQueue(q, head);
        head = head->next;
    }

    Echipa *e1, *e2;
    Echipa *headNou = NULL, *p = NULL, *l = NULL, *k = NULL;

   while(counter != 1)
        {

            while(!qIsEmpty(q))
                {
                    
                    e1 = deQueue(q);
                    e2 = deQueue(q);

                    if(counter == 8)
                    {
                            p = e1;
                            if(headNou == NULL) 
                                p->next = NULL;
                            else p->next = headNou;
                            l = e2;
                            l->next = p;
                            headNou = l;
                    }

                    fprintf(file, "%-25s -- %25s\n", e1->numeEchipa , e2->numeEchipa);

                    if(scorEchipa(e1) >= scorEchipa(e2))
                    {
                        for(int i=0; i<e1->nrJucatori; i++)
                            (e1->J[i].xp)++;

                        push(&sCastig, e1);
                        push(&sPierz, e2);
                    }

                    else
                    {
                        for(int i=0; i<e2->nrJucatori; i++)
                            (e2->J[i].xp)++;

                        push(&sCastig, e2);
                        push(&sPierz, e1);
                    }

                }

                if(counter > 8) deleteStackSiMemorie(&sPierz);
                else deleteStack(&sPierz);

                counter=counter/2;

                while(!isEmpty(sCastig))
                 {
                    k = pop(&sCastig);

                    if(k != NULL)
                         {fprintf(file , "%-25s --- %.2f\n", k->numeEchipa, scorEchipa(k));
                          enQueue(q, k);}

                    else printf("noewertewr");
                 }

                while(!isEmpty(sCastig))
                    enQueue(q, pop(&sCastig));	//nu cred ca am nevoie de asta, dar e bine sa fim siguri

        }
        free(q);  

   return headNou;
}


typedef struct Nod
{
    Echipa *E2;
    struct Nod *left, *right;
} BSTnode;


int height(BSTnode *root)
{
    int hs = 0, hd = 0;
    if(root == NULL) return 0;
    hs = height(root->left);
    hd = height(root->right);
    if(hs>hd) return 1+hs;
    else return 1+hd;
}


void inorder(FILE *file, BSTnode *root)
{
    if(root != NULL)
    {
        inorder(file, root->right);
        fprintf(file, "%-20s -- %.2f\n", root->E2->numeEchipa, scorEchipa(root->E2));
        inorder(file, root->left);
    }

}

BSTnode *createRoot(Echipa *elem)
{
    BSTnode *head = (BSTnode*)malloc(sizeof(BSTnode));
    head->E2 = elem;
    head->left = NULL;
    head->right = NULL;
    return head;
}

BSTnode *rightRotation( BSTnode *z)
{

BSTnode *x = z->left;
BSTnode *y = x->right;

x->right = z;
z->left = y;

return x;
}


BSTnode *leftRotation( BSTnode *z)
{
BSTnode *x = z->right;
BSTnode *y = x->left;

x->left = z;
z->right = y;

return x;
}

BSTnode *LRRotation(BSTnode *z)
{ 
z->left= leftRotation(z->left);
return rightRotation(z);
}

BSTnode *RLRotation(BSTnode *z)
{ 
z->right = rightRotation(z->right);  
return leftRotation(z);
}


BSTnode *insert(BSTnode *root, Echipa *elem, char nume[3])
{
    if(root == NULL) return createRoot(elem);

    if(scorEchipa(elem) < scorEchipa(root->E2)) 
        root->left = insert(root->left, elem, nume);

    else if(scorEchipa(elem) > scorEchipa(root->E2))
        root->right = insert(root->right, elem, nume);

   if(nume == "AVL")
    {
        if(root->left != NULL)
        {
            int k = (height(root->left) - height(root->right));
    
            if (k > 1 && scorEchipa(elem) < scorEchipa(root->left->E2)) 
                return rightRotation(root); 
    
    
            if (k > 1 && scorEchipa(elem) > scorEchipa(root->left->E2))
                return LRRotation(root);
        }
        
        if(root->right != NULL)
        {
            int k = (height(root->left) - height(root->right));
    
            if (k < -1 && scorEchipa(elem) > scorEchipa(root->right->E2))
                return leftRotation(root);
    
            if (k < -1 && scorEchipa(elem) < scorEchipa(root->right->E2))
                return RLRotation(root);
    
        }
    }
    

    return root;
}
        

BSTnode *createBST(FILE *file, BSTnode *root, Echipa *head)
{
    Echipa *p;

    for(p=head; p != NULL; p=p->next)
        root = insert(root, p, "BST");

    inorder(file, root);

    return root;
}


void printLevel(BSTnode *root, int level)
{
if (root == NULL) return;
if (level == 1) printf("%f ", scorEchipa(root->E2));
else if (level > 1) 
  {
    printLevel(root->left, level-1);
    printLevel(root->right, level-1);
  }
}



void createAVL(BSTnode *root, Echipa *head)
{

    Echipa *p;

    for(p=head; p != NULL; p=p->next)
        root = insert(root, p, "AVL");

}

void eliberareArbore(BSTnode *root)
{
    if(root == NULL) return;
    eliberareArbore(root->left);
    eliberareArbore(root->right);

    BSTnode *temp;
    temp = root;
    free(temp);
}


int main(int argc, char *argv[])
{
    Echipa *head;
    int nrEchipe, nrEchipeInitial;
    float minim;

    FILE *f1 = fopen(argv[1], "rt");
    if(f1 == NULL)
    {
        printf("sad reacts only\n");
    }

    int v[5];

    for(int i=0; i<5; i++)
        fscanf(f1, "%d", &v[i]);

    if(v[0] == 1)
        creareLista(argv[2], &nrEchipe, &head);


    FILE *f2 = fopen(argv[3], "wt");
    if(f2 == NULL)
    {
        printf("sad reacts only\n");
    }

    nrEchipeInitial = nrEchipe;

    cateEchipeRaman(&nrEchipe);

    if(v[1] == 1)
        sterge(&head, nrEchipeInitial, nrEchipe);


    nodStiva *sCastig = NULL, *sPierN = NULL;
    afisare(f2, head);

    if(v[2] == 1)
        head = creareMeciuri(head, sCastig, sPierN, nrEchipe, f2);


    BSTnode *root = NULL;

    if(v[3] == 1)
        root = createBST(f2, root, head);


    if(v[4] == 1)
        {
            createAVL(root, head);
            printLevel(root, 2);
        }


    eliberareArbore(root);

    Echipa *p;

    while(head != NULL)
    {
        p = head;
        
        head = head->next;
        eliberareMemorie(p);
    }

        
    fclose(f1);
    fclose(f2);


    return 0;
}

