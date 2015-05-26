OBJS=*.o
OBJ_SCM_DIR=scmobj
OBJ_CARD_DIR=cardobj
OBJ_COMMON_DIR=comobj

all : $(BIN_SCM ) $(BIN_CARD)
.PHONY : all

$(ROOT_DIR)/$(BIN_DIR)/$(BIN_SCM):$(OBJ_SCM_DIR)/$(OBJS) $(OBJ_COMMON_DIR)/$(OBJS)
	$(CC) -o $@ $^

$(ROOT_DIR)/$(BIN_DIR)/$(BIN_CARD):$(OBJ_CARD_DIR)/$(OBJS) $(OBJ_COMMON_DIR)/$(OBJS)
	$(CC) -o $@ $^