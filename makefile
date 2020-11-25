# RetroviralLifeCyle
output: VirusMain.o
	g++ VirusMain.o -o output
	
VirusMain.o: VirusMain.cpp
	g++ -c VirusMain.cpp

# TARGET
all: $(output)

# (1)
# ---
# DETECT OS
ifeq ($(OS),Windows_NT)    # WINDOWS
    detected_OS := Windows
else
    detected_OS := $(shell uname)
endif
# ...

# (2)
# ---
#Detect OS
UNAME = `uname`

# Build based on OS name
DetectOS:
    -@make $(UNAME)

# OS is Linux, use GCC
Linux: program.c
    @SHELL_VARIABLE="-D_LINUX_STUFF_HERE_"
    rm -f program
    gcc $(SHELL_VARIABLE) -o program program.c

# OS is Solaris, use c99
SunOS: program.c
    @SHELL_VARIABLE="-D_SOLARIS_STUFF_HERE_"
    rm -f program
    c99 $(SHELL_VARIABLE) -o program program.c
# ...

# (3)
# ---
# DETECT OS
ifeq ($(OS), Windows_NT)                                   # WINDOWS
CCFLAGS = -O3 -Wall
LIBS = -lglut32cu -lglu32 -lopengl32
else
	ifeq "$(shell uname)" "Darwin"                         # MAC OSX
		CCFLAGS = -O3 -Wall -Wno-deprecated-declarations
		LIBS = -framework GLUT -framework OpenGL
else                                                       # Linux/Unix/Solaris
CCFLAGS = -O3 -Wall
LIBS = -lglut -lGLU -lGL -lm
endif

# CLEAN
clean:
	rm *.o output
