NAME=		philo

VPATH=		src/

OBJDIR=		obj

INCDIR=		inc

SRC=		main.c						\
			parsing.c					\
			threading.c					\
			philo_init.c				\
			philo_utils.c



OBJ=		${addprefix ${OBJDIR}/,		\
			${SRC:.c=.o}}

INC=		${INCDIR}/philo.h

CC=			cc

CFLAGS=		-Wall -Wextra -Werror

all:		${OBJDIR} ${NAME}

${NAME}:	${OBJ} ${INC}
			${CC} ${OBJ} -o ${NAME} -lpthread

${OBJDIR}:
			mkdir -p obj

${OBJDIR}/%.o:	%.c ${INC} Makefile
			${CC} ${CFLAGS} -c $< -o $@


clean:
			rm -rf ${OBJDIR}

fclean:		clean
			${RM} ${NAME}

re:			fclean all

.PHONY:		all clean fclean re