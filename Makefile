CC		=	gcc

RM		=	rm -rf

NAME		=	calculator

SRCPATH		=	sources/

SRCS		=	$(SRCPATH)main.c		\
			$(SRCPATH)fonctions.c		\
			$(SRCPATH)parser.c

INCS		=	-I includes/

OBJS		=	$(SRCS.c=.o)

all		:	$(NAME)

$(NAME)		:	$(OBJS)
			$(CC) -o $(NAME) $(SRCS) $(INCS)

clean		:
			$(RM) $(OBJS)

fclean		:	clean
			$(RM) $(NAME)

re		:	fclean all

dbg		:	$(OBJS)
			$(CC) -o $(NAME) $(SRCS) $(INCS) -g
