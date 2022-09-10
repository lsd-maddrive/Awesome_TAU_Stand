# C source files
PROJECT_CSRC 	= src/main.c \
				  tests/test_modbusTCP.c\
				  src/lld_i2c.c \
				  tests/i2c_test.c \
				  tests/sensor_m3421_test.c \
				  src/sensor_m3421.c \
				  src/terminal_write.c \
				  tests/current_sensor_test.c \
				  src/current_sensor.c \
				  src/modbusTCP/modbusFunc.c \
				  src/modbusTCP/modbusGet.c \
				  src/modbusTCP/modbusRegister.c \
				  src/modbusTCP/modbusTCP.c \
				  tests/interrupt_test.c \
				  src/incremental_encoder.c \
				  
# C++ source files
PROJECT_CPPSRC 	= 
# Directories to search headers in
PROJECT_INCDIR	= include \
                  tests \
                  include/modbusTCP 

# Additional libraries
PROJECT_LIBS	= -lm
# Compiler options
PROJECT_OPT     = -DCHPRINTF_USE_FLOAT=1 -specs=nano.specs -specs=nosys.specs

# Additional .mk files are included here
