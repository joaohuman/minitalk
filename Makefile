CC = gcc
CFLAGS = -Wall -Wextra -Werror
SRC_SERVER = 	server.c \
				utils.c
SRC_CLIENT = 	client.c \
				utils.c
SRC_SERVER_B = 	server_bonus.c \
				utils.c
SRC_CLIENT_B = 	client_bonus.c \
				utils.c
OBJ_SERVER = $(SRC_SERVER:.c=.o)
OBJ_CLIENT = $(SRC_CLIENT:.c=.o)
OBJ_SERVER_B = $(SRC_SERVER_B:.c=.o)
OBJ_CLIENT_B = $(SRC_CLIENT_B:.c=.o)

all: server client

server: $(OBJ_SERVER)
	$(CC) $(CFLAGS) $(OBJ_SERVER) -o server

client: $(OBJ_CLIENT)
	$(CC) $(CFLAGS) $(OBJ_CLIENT) -o client

bonus: $(OBJ_SERVER_B) $(OBJ_CLIENT_B)
	make OBJ_SERVER="$(OBJ_SERVER_B)" OBJ_CLIENT="$(OBJ_CLIENT_B)" all

clean:
	rm -rf $(OBJ_SERVER) $(OBJ_CLIENT) $(OBJ_CLIENT_B) $(OBJ_SERVER_B)

fclean: clean
	rm -rf server client

re: fclean all

.PHONY: all fclean re clean bonus
