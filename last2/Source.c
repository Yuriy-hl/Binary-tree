#include <stdlib.h>
#include <stdio.h>
#pragma warning (disable:4996)
int BUFF = 0;
int maxheight = 0;
int balancecoef = 0;
typedef struct branch {
    int num;
    struct branch* leftbranch;
    struct branch* rightbranch;
} Sbranch;

void nbranch(Sbranch* last, int number) {
    Sbranch* new;
    new = (Sbranch*)malloc(sizeof(Sbranch));
    new->num = number;
    new->rightbranch = 0;
    new->leftbranch = 0;
    Sbranch* search;
    search = last;
    while (search != 0) {
        if (number > search->num) {
            if (search->rightbranch == 0) {
                search->rightbranch = new;
                break;
            }
            search = search->rightbranch;
        }
        else {
            if (search->leftbranch == 0) {
                search->leftbranch = new;
                break;
            }
            search = search->leftbranch;
        }
    }

}

int search(Sbranch* head, int number) {
    int marker = 0;
    Sbranch* point = head;
    while (point != 0) {
        if (number == point->num) {
            marker = 1;
            break;
        }
        if (number > point->num) {
            point = point->rightbranch;
        }
        else {
            point = point->leftbranch;
        }
    }
    return marker;
}

void printreee1(Sbranch* head, int space) {
    if (head == 0)
        return;
    space += 10;

    printreee1(head->rightbranch, space);
    printf("\n");
    for (int i = 10; i < space; i++)
        printf(" ");
    printf("%d\n", head->num);

    printreee1(head->leftbranch, space);
}

void printtree(Sbranch* root) {
    printreee1(root, 0);
}

void heightt(Sbranch* top, int height) {
    if (top == 0)
        return;
    height += 1;
    if (height > maxheight) {
        maxheight = height;
    }
    heightt(top->rightbranch, height);
    heightt(top->leftbranch, height);
}
int branchheight(Sbranch* top) {
    int mheight;
    heightt(top, 0);
    mheight = maxheight;
    maxheight = 0;
    return mheight;
}
int heightdif(Sbranch* top) {
    return branchheight(top->leftbranch) - branchheight(top->rightbranch);
}
void LRotation(Sbranch** head) {
    Sbranch* lasthead = (*head);
    Sbranch* left = (*head)->rightbranch->leftbranch;
    *head = (*head)->rightbranch;
    (*head)->leftbranch = lasthead;
    lasthead->rightbranch = left;
}

void RRotation(Sbranch** head) {
    Sbranch* lasthead = (*head);
    Sbranch* right = (*head)->leftbranch->rightbranch;
    *head = (*head)->leftbranch;
    (*head)->rightbranch = lasthead;
    lasthead->leftbranch = right;
}

void LR_Rotation(Sbranch** head) {
    LRotation(&(*head)->leftbranch);
    RRotation(head);
}

void RL_Rotation(Sbranch** head) {
    RRotation(&(*head)->rightbranch);
    LRotation(head);
}

void balance(Sbranch** head) {
    if (*head == 0) {
        return;
    }
    if (heightdif(*head) < -1) {
        balancecoef = 0;
        if (((*head)->rightbranch != 0) && (heightdif((*head)->rightbranch) > 0)) {
            RL_Rotation(head);
        }
        else {
            LRotation(head);
        }

    }
    if (heightdif(*head) > 1) {
        balancecoef = 0;
        if (((*head)->leftbranch != 0) && (heightdif((*head)->leftbranch) < 0)) {
            LR_Rotation(head);
        }
        else {
            RRotation(head);
        }

    }
    balance(&((*head)->rightbranch));
    balance(&((*head)->leftbranch));
}

int main(void) {
    FILE* input;
    input = fopen("zadanie2.txt", "r");
    fscanf(input, "%i", &BUFF);
    Sbranch* head;
    head = (Sbranch*)malloc(sizeof(Sbranch));
    head->num = BUFF;
    head->rightbranch = 0;
    head->leftbranch = 0;
    while (fscanf(input, "%i", &BUFF) != EOF) {
        if (search(head, BUFF) == 0) {
            nbranch(head, BUFF);
        }
    }
    while (balancecoef != 1) {
        balancecoef = 1;
        balance(&head);
    }
    printtree(head);
}