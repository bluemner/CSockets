# =====================================
# Description: Server & Client makefile
# Author: Brandon Bluemner
# =====================================
COMPILER = gcc
COMPILER_FLAGS = -Wall

All: client server
 
client: client.c
	$(COMPILER) $(COMPILER_FLAGS) client.c -o ../bin/udp_client
server: server.c
	$(COMPILER) $(COMPILER_FLAGS) server.c -o ../bin/udp_server
	