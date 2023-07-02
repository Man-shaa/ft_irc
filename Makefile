NAME		=	ft_irc

OBJ_DIR		=	objs
SRC_DIR		=	$(shell find srcs -type d)
INC_DIR		=	$(shell find includes -type d)

vpath %.cpp $(foreach dir, $(SRC_DIR), $(dir):)
vpath %.hpp $(foreach dir, $(INC_DIR), $(dir):)

SRCS	 	=	main.cpp	\
				Channel.cpp	\
				Client.cpp	\
				Command.cpp	\
				Server.cpp	\
				Mode.cpp	\
				Topic.cpp

OBJS		=	$(SRCS:%.cpp=${OBJ_DIR}/%.o)

RM			=	rm -rf

CC			=	c++

CFLAGS		=	-Werror -Wall -Wextra -std=c++98 -g3 -D_GLIBCXX_DEBUG
# -D_GLIBCXX_DEBUG pour afficher les valeurs de std::string los de debug gdb, sinon <incomplete type> 

all:	${NAME}

$(NAME): ${OBJS} ${INC_DIR}
		${CC} ${CFLAGS} ${OBJS} -o ${NAME}

$(OBJ_DIR)/%.o: %.cpp ${INC_DIR} | $(OBJ_DIR)
		$(CC) $(CFLAGS) -c $< -o $@ -I ${INC_DIR}

$(OBJ_DIR) :
		mkdir -p $@

clean:
		${RM} $(OBJ_DIR)

fclean:		clean
		${RM} ${NAME}

re:			fclean
		$(MAKE) all

.PHONY:		all clean fclean re
