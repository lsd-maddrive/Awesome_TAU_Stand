# C source files
PROJECT_CSRC 	= src/main.c \
				  tests/first_test.c\
				  src/serial.c \
				  src/modbusTCP/modbusFunc.c \
				  src/modbusTCP/modbusGet.c \
				  src/modbusTCP/modbusRegister.c \
				  src/modbusTCP/modbusTCP.c 
# C++ source files
PROJECT_CPPSRC 	= 
# Directories to search headers in
PROJECT_INCDIR	= include \
                  tests \
                  include/modbusTCP\ 
# Additional libraries
PROJECT_LIBS	= -lm
# Compiler options
PROJECT_OPT     = -DCHPRINTF_USE_FLOAT=1 -specs=nano.specs -specs=nosys.specs

# Additional .mk files are included here
