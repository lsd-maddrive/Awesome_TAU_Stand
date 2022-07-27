# C source files
PROJECT_CSRC 	= src/main.c \
				  tests/first_test.c\
				  tests/state_driver_test.c\
				  src/state_driver.c\
				  src/measurements.c\
				  src/controllers.c\
				  src/sensors/sensorsFunc.c\
				  src/controllers/controllFunc.c\
				
# C++ source files
PROJECT_CPPSRC 	= 
# Directories to search headers in
PROJECT_INCDIR	= include \
                  tests
# Additional libraries
PROJECT_LIBS	= -lm
# Compiler options
PROJECT_OPT     = -DCHPRINTF_USE_FLOAT=1

# Additional .mk files are included here
