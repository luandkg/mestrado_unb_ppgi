# Lista de subpastas que têm Makefile
SUBDIRS = sd sd 

# Regra principal: compilar todos
all:
	@for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir; \
	done

# Limpeza em todos os subprojetos
clean:
	@for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir clean; \
	done

.PHONY: all clean
