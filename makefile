.PHONY: make clean new

COMPILER = g++
PROG = IG_Steeple
FLAGS =  -lfreeglut -lglu32 -lopengl32 -Wl,--subsystem,windows
GLUT_LIB = -L"C:\freeglut\lib"
GLUT_INCLUDE = -I"C:\freeglut\include"

make: $(PROG).exe
	
$(PROG).exe: main.o calculations.o shapes.o
	$(COMPILER) obj/main.o obj/calculations.o obj/shapes.o -o bin/$(PROG).exe $(GLUT_LIB) $(FLAGS)

main.o: main.cc
	$(COMPILER) -c main.cc -o obj/main.o $(GLUT_INCLUDE)
	
calculations.o: calculations.cc
	$(COMPILER) -c calculations.cc -o obj/calculations.o $(GLUT_INCLUDE)

shapes.o: shapes.cc
	$(COMPILER) -c shapes.cc -o obj/shapes.o $(GLUT_INCLUDE)

clean:
	rm -f obj/*.o
	rm -f bin/$(PROG).exe
	
new: clean make