obj = main.o pso.o particle.o
obj_debug = main_debug.o pso_debug.o particle_debug.o

pso : $(obj)
	g++ -o pso obj/release/*.o
	
pso_opt : $(obj)
	g++ -o pso_opt obj/release/*.o -O3
	
pso_debug : $(obj_debug)
	g++ -g -o pso_debug obj/debug/*.o 
	
main.o : src/main.cpp
	g++ -c src/main.cpp -o obj/release/main.o

main_debug.o : src/main.cpp
	g++ -g -c src/main.cpp -o obj/debug/main.o

pso.o : src/pso.cpp
	g++ -c src/pso.cpp -o obj/release/pso.o

pso_debug.o : src/pso.cpp
	g++ -g -c src/pso.cpp -o obj/debug/pso.o

particle.o : src/particle.cpp
	g++ -c src/particle.cpp -o obj/release/particle.o
	
particle_debug.o : src/particle.cpp
	g++ -g -c src/particle.cpp -o obj/debug/particle.o
	
clean : 
	rm obj/release/*.o obj/debug/*.o
