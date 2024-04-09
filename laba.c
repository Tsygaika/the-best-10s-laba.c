#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define n 2 //1 - первая задача, 2 - вторая

#if n == 1

typedef struct Node{    //структура элемента списка
    int degree;
    int coeff;
    struct Node *next;  //указатель на следующий элемент списка
}Node;

Node * addElem();
void menu();

Node* create(Node * L1){    //создание списка
    printf("Введите максимальную степень многочлена: ");
    int min_degree, max_degree;
    scanf("%d", &max_degree);
    printf("Введите минимальную степень многочлена: ");
    scanf("%d", &min_degree);
    if(min_degree > max_degree){puts("Минимальная степень должна быть не больше, максимальной");exit(-1);}
    
    int coeff;
    for(int i =  min_degree; i <= max_degree; i++ ){
        printf("Коэффициент перед x^%d: ", i);
        scanf("%d", &coeff);
        if(coeff == 0){continue;}
        L1 = addElem(L1, coeff, i);
    }
    return L1;
}

Node * addElem(Node* head, int coeff, int degree){  //добавление нового элемента
    Node* newNode = (Node*)malloc(sizeof(Node));    //создаем элемент списка и добавляем в него значения
    newNode->coeff = coeff;
    newNode -> degree = degree;
    newNode->next = NULL;

    if (head == NULL){ //для добавления нулевого элемента
        head = newNode;
        return head;}
    
    Node* current = head;
    while (current->next != NULL){  //двигаемся в конец списка для добавления элемента
        current = current->next;}
    current->next = newNode;
    return head;
}

void print(Node * L1){  //вывод многочлена
    if(!L1){printf("Пустой многочлен");}

    Node * current = L1;
    while(current){
        printf("(%d)*x^%d",current -> coeff, current -> degree);
        if(current -> next){printf(" + ");}
        current = current -> next;
    }
    puts("");
}

Node * delete(Node * L1){   //функция для удаления слагаемых
    Node * L2 = NULL;
    L2 = create(L2);    //создаем второй многочлен

    puts("Многочлены до удаления: ");
    printf("L1: ");
    print(L1);
    printf("L2: ");
    print(L2);

    Node * current = L1, * previous = NULL, * current2;
    while(current){    //проходимся по элементам первого списка
        //printf("deg1 =%d; ",current -> degree);
        current2 = L2;

        while(current2){     //проходимся по элементам второго списка
            //printf("deg2 =%d; ",current2 -> degree);
            if(current -> degree == current2 -> degree){    //если такая степень есть в L2, то переходим к следующему элементу в L1
                previous = current;
                current = current -> next;
                break;
            }
            current2 = current2 -> next;
        }

        if(!current2){  //если мы не нашли такую же степень, то current2 = NULL
            if(previous){
                previous -> next = current -> next; //меняем в предыдущем указатель на следующий
                free(current);
                current = previous -> next;}    //и переходим к следующему элементу после удаленного
            else{   //если удаляем первый элемент
                L1 = current -> next;   //то список теперь начинается со следующего
                free(current);
                current = L1;
            }
        }
    }

    puts("\nМногочлены после удаления: ");
    printf("L1: ");
    print(L1);
    printf("L2: ");
    print(L2);

    Node *tmp = L2;     //очищаем список L2
    while(tmp){
        current2 = tmp->next;
        free(tmp);
        tmp = current2;
    }
    L2 = NULL;

    return L1;
}

void menu(Node * L1){
    puts("\nВыберите функцию:\n1)Вывести список\n2)Функция удаления слагаемых");
    int choice;
    scanf("%d", &choice);
    switch (choice){
    case 1:
        printf("Список: ");
        print(L1);  //функция вывода
        menu(L1);
        break;
    case 2:
        L1 = delete(L1);    //функция удаления элементов многочлена
        menu(L1);   
        break;
    default:
        puts("Такой функции нет");
        exit(-1);
        break;
    }
}

int main(){
    Node * L1 = NULL;
    L1 = create(L1);    //создаем список для многочлена L1
    menu(L1);
    
    return 0;
}


#elif n==2

typedef struct Node{    //структура элемента списка
    char *p;    //указатель на слово
    struct Node *next;  //указатель на следующий элемент
    struct Node *prev;
} Node;

typedef struct DBLLinked{  //структура, содержащая информацию о списке
    unsigned int size;  //кол-во элементов в списке
    Node *head;
    Node *tail; //указатель на конец списка
} DBLLinked;

DBLLinked* createDBLLinked(){   //создание списка
    DBLLinked *tmp = (DBLLinked*) malloc(sizeof(DBLLinked));
    tmp -> size = 0;
    tmp -> head = NULL;
    tmp -> tail = NULL;
    return tmp;
}

void pushBack(DBLLinked *list, char *p){    //добавление элемента в конец
    Node *tmp = (Node*) malloc(sizeof(Node));
    
    tmp->p = p;
    tmp->next = NULL;   //изменяем поля элемента
    tmp->prev = list->tail;

    if (list->tail){   //изменяем указатель в предпоследнем элементе
        list->tail->next = tmp;}

    list->tail = tmp;   //изменяем указатель на конец списка
 
    if (list->head == NULL){    //если список пустой, то указатель на начало = указатель на этот элемент
        list->head = tmp;}

    list->size++;
}

void printDBLLinked(DBLLinked *list){   //вывод списка
    if(list->size == 0){printf("Пустой список"); return;}

    Node *tmp = list->head; //получаем указатель на первый элемент списка
    while(tmp){
        printf("%s", (tmp->p));
        tmp = tmp->next;
        if(tmp){printf(", ");}
    }
    
}

void deleteDBLLinked(DBLLinked **list){ //удаление списка
    Node *tmp = (*list)->head;
    Node *next = NULL;
    while(tmp){
        next = tmp->next;
        free(tmp);
        tmp = next;
    }
    free(*list);
    (*list) = NULL;
}

int check(char* str){ //проверяем строку на не латинские буквы
    int flag = 0;

    for (int i = 0; i < strlen(str); i++){
        if (!(('a' <= str[i] && str[i] <= 'z')  || str[i]==' ')){
            flag = 1;
            break;
        }
    }
    return flag;
}

void func(DBLLinked *list){ //функция из варианта
    printf("\nВведите количество букв (N): ");
    int N;
    scanf("%d", &N);
    if(N < 0){
        puts("Кол-во букв не должно быть меньше 0");
        exit(-1);}

    DBLLinked * list_more = createDBLLinked();  //создаем два списка
    DBLLinked * list_less = createDBLLinked(); 

    Node *tmp = list->head;
    while(tmp){     //проходимся по основному списку и добавляем элемент либо в первый, либо во второй список
        char * word = tmp->p;
        if(strlen(word) > N){
            pushBack(list_more, word);}
        else{
            pushBack(list_less, word);}
        tmp = tmp->next;
    }

    printf("\nСписок со словами, длиной больше N: ");
    printDBLLinked(list_more);
    printf("\nСписок остальных слов: ");
    printDBLLinked(list_less);

    deleteDBLLinked(&list_more);
    deleteDBLLinked(&list_less);    //очищаем списки
    deleteDBLLinked(&list);
}

void main(){
	char str[400];
    printf("Введите строку: ");
    fgets(str, 400, stdin);

    int point = 0;
    for(int i = 0; i < strlen(str); i++){   //проверка на точку в конце
        if(str[i] == '.'){point=1; break;}
    }
    if(!point){
        printf("\nСтрока не содержит точку\n");
        exit(1);}

    char * istr = strtok(str, "."); //обрезаем строку до точки

    if (check(str)){//проверка на латинские буквы
        printf("\nСтрока содержит не только латинские буквы\n");
        exit(1);}
    

    DBLLinked * list = createDBLLinked();   //создаем список
    
    istr = strtok(str," ");   //получаем указатель на первое слово
    while(istr){
        char * p = istr;
        pushBack(list, p);  //добавляем остальные в конец
        istr = strtok(NULL," ");
    }

    printf("Строка преобразована в список: ");
    printDBLLinked(list);

    func(list);
}

#endif
