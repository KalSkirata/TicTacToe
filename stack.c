#include<stdio.h>
#include<stdlib.h>
#include "stack.h"

/**
* Stack use to store the availables moves
**/

int push(stack **s, int x, int y){
        stack *element = malloc(sizeof(s));
        if(!element) return -1;     /* Si l'allocation a échouée. */
        element->x = x;
        element->y = y;
        element->prec = *s;
        *s = element;       /* Le pointeur pointe sur le dernier élément. */
        return 0;
}

int* pop(stack **s){
        int data[2]={-1,-1};
        stack *tmp;
        if(!*s) return data;     /* Retourne -1 si la pile est vide. */
        tmp = (*s)->prec;
        data[0] = (*s)->x;
        data[1] = (*s)->y;
        //printf("pop(%d %d) \n", data[0], data[1]);
        free(*s);
        *s = tmp;       /* Le pointeur pointe sur le dernier élément. */
        return data;     /* Retourne la valeur soutirée de la pile. */
}

void clear(stack **s){
        stack *tmp;
        while(*s){
             tmp = (*s)->prec;
             free(*s);
             *s = tmp;
        }
}

void display(stack *s){
	while(s){
		printf("%d %d\n",s->x,s->y);
		s = s->prec;
	}
}

int length(stack *s){
        int n=0;
        while(s){
              n++;
              s = s->prec;
        }
        return n;
}

int* popById(int id, stack **s){
	int i, *res;
	//printf("%s : length(*s)-id=%d \n", __func__, length(*s)-id);
	for(i=0; i<length(*s)-id; i++){
		//printf("%s : i = %d \n", __func__, i);
		res=pop(s);			
	}
	return res;
}

void copyStack(stack* src, stack *dst, int size){
	int i, *data;
	for(i=0; i<size; i++){
		data = pop(&src);
		push(&dst, *(data), *(data+1));
	}
}
