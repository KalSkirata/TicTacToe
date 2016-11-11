CC = gcc
CFLAGS = -Wall -g
INCLUDES = -I./
SRCS = ttt.c board.c move.c stack.c
OBJS = $(SRCS:.c=.o)
MAIN = ttt


.PHONY: depend clean

$(MAIN): $(OBJS) 
	$(CC) $(CFLAGS) $(INCLUDES) -o $(MAIN) $(OBJS)
        
.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $<  -o $@

clean:
	$(RM) *.o *~ $(MAIN)
