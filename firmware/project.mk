# C source files
PROJECT_CSRC 	= src/main.c \
				  tests/first_test.c \
				  src/lld_i2c.c \
				  tests/i2c_test.c\
				  test/sensor_m3421_test.c\
				  src/sensor_m3421.c\
				  src/terminal_write.c\
				  
				  
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
