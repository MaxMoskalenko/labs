compile: 
	@g++ main.cpp -o main
	@echo "Compilation success\n"

insertion: compile
	@./main I 1000 a
	@./main I 1000 b
	@./main I 1000 c
	@./main I 10000 a
	@./main I 10000 b
	@./main I 10000 c
	@./main I 100000 a
	@./main I 100000 b
	@./main I 100000 c 

heap: compile
	@./main II 1000 a
	@./main II 1000 b
	@./main II 1000 c
	@./main II 10000 a
	@./main II 10000 b
	@./main II 10000 c
	@./main II 100000 a
	@./main II 100000 b
	@./main II 100000 c 

radix: compile
	@./main III 1000 a
	@./main III 1000 b
	@./main III 1000 c
	@./main III 10000 a
	@./main III 10000 b
	@./main III 10000 c
	@./main III 100000 a
	@./main III 100000 b
	@./main III 100000 c 

cometogether: insertion heap radix
	@echo "And here are the results!!!"


test: compile 
	@./main III 10 b
	
clean: compile
	@rm main