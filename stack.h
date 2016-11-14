struct stack{
	int x,y;
	struct stack *prec;
};

typedef struct stack stack;

int push(stack **s, int x, int y);

void clear(stack **s);

void display(stack *s);

int length(stack *s);
