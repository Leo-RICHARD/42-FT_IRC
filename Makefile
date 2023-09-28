NAME		=	ircserv

SRCS		=	main.cpp \
			irc.cpp \
			Server.cpp \
			Client.cpp \
			Channel.cpp \
			parser.cpp \
			split.cpp \
			PASScommand.cpp \
			NICKcommand.cpp \
			USERcommand.cpp \
			QUITcommand.cpp \
			JOINcommand.cpp \
			PARTcommand.cpp \
			MODEcommand.cpp \
			INVITEcommand.cpp \
			KICKcommand.cpp \
			PRIVMSGcommand.cpp \
			NOTICEcommand.cpp \
			PINGcommand.cpp \
			TOPICcommand.cpp \
			utils.cpp \

HEADER		=	ft_irc.hpp \
			Server.hpp \
			Client.hpp \
			Channel.hpp \
			numericMessages.hpp \

OBJS		=	${addprefix objs/,${notdir ${SRCS:.cpp=.o}}}

CC		=	c++

CFLAGS		=	-Wall -Wextra -Werror -std=c++98 -fsanitize=address -g3

RM		=	rm -f

all:
			@mkdir -p objs
				@${MAKE} ${NAME}

objs/%.o:		srcs/%.cpp ${addprefix headers/,${HEADER}}
				${CC} ${CFLAGS} -c $< -o $@ -I headers

${NAME}:		${OBJS} ${addprfix headers/,${HEADER}}
				${CC} ${CFLAGS} ${OBJS} -o ${NAME}

clean:
				@${RM} ${OBJS}
				@rm -rf objs

fclean:			clean
				@${RM} ${NAME}

re:			fclean all

.PHONY:			clean fclean re alle
