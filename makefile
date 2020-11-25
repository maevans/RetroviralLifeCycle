# RetroviralLifeCyle
output = VirusMain

# TARGET
all: $(output)

# ---
# DETECT OS
ifeq ($(OS), Windows_NT)                                    # WINDOWS
CCFLAGS = -O3 -Wall
LIBS = -lglut32cu -lglu32 -lopengl32
else
	ifeq ($(shell uname),Darwin)                            # MAC OSX
		CCFLAGS = -O3 -Wall -Wno-deprecated-declarations
		LIBS = -framework GLUT -framework OpenGL
else                                                        # Linux/Unix/Solaris
CCFLAGS = -O3 -Wall
LIBS = -lglut -lGLU -lGL -lm
endif

# DEPENDENCY
VirusMain.o: VirusMain.cpp

# COMPILE
.c.o:
	gcc -c $(CCFLAGS) $<
.cpp.o:
	g++ -c $(CCFLAGS) $<

#  LINK LIBS
output:VirusMain.o
	gcc -O3 -o $@ $^   $(LIBS)

# CLEAN
clean:
	rm *.o output
