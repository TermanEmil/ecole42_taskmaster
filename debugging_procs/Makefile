SRC			=	$(shell find src -name '*.c')
SRC_FILES	=	$(notdir $(SRC))
BINS		=	$(SRC_FILES:.c=)

./%: src/%.c
	gcc $< -o $@

make: $(BINS)
	@echo $(BINS)
	
fclean:
	rm -rf $(BINS)

re: fclean make