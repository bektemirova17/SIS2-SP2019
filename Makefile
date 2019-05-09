PROJECT = proc
GOAL = proc
CFLAGS = -Wall
DATAFILE = /etc/hosts

run: tags $(GOAL) $(DATAFILE)
	./$(GOAL) $(DATAFILE)

tags: $(GOAL).c
	ctags $(GOAL).c

clean:
	rm -f $(GOAL) $(OUTPUT) tags

submit: $(GOAL).c Makefile README.txt
	tar -czf $(PROJECT).tgz $(GOAL).c Makefile README.txt
