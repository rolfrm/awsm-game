all:
	make -C libawsm
	cp libawsm/libawsm.so ./
	make -f makefile.game
	make -f makefile.demo	
clean:
	make -f makefile.game clean
