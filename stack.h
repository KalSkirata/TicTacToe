struct stack{
	int x,y;
	struct stack *prec;
};

typedef struct stack stack;

int push(stack **s, int x, int y);

int* pop(stack **s);

void clear(stack **s);

void display_stack(stack *s);

int length(stack *s);

int* popById(int id, stack **s);
