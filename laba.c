#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define n 1 //1 - первая задача, 2 - вторая

#if n==1

typedef struct Node{
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

    Node * current2 = L2;
    while(current2){    //проходимся по элементам второго списка
        Node * current = L1,  * previous = NULL;

        while(current){     //проходимся по элементам первого списка

            if(current -> degree == current2 -> degree){
                if(previous){
                    previous -> next = current -> next;}
                else{
                    L1 = current -> next;}  //на случай если нужно удалить нулевой элемент
                    
                free(current);
                break;
            }
            previous = current;
            current = current -> next;
        }
        current2 = current2 -> next;
    }

    puts("Многочлены после удаления: ");
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
        print(L1);
        menu(L1);
        break;
    case 2:
        L1 = delete(L1);
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
    L1 = create(L1);//создаем список для многочлена L1
    menu(L1);
    
    return 0;
}

#elif n==2
#endif
