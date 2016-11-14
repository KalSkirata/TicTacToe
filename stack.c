#include<stdio.h>
#include<stdlib.h>
#include "stack.h"

int push(stack **s, int x, int y){
        stack *element = malloc(sizeof(s));
        if(!element) return -1;     /* Si l'allocation a échouée. */
        element->x = x;
        element->y = y;
        element->prec = *s;
        *s = element;       /* Le pointeur pointe sur le dernier élément. */
        return 0;
}

void clear(stack **s){
        stack *tmp;
        while(*s)
          {
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

int length(stack *s)
{
        int n=0;
        while(s)
          {
              n++;
              s = s->prec;
          }
        return n;
}
