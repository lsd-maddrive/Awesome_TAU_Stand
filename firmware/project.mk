# C source files
PROJECT_CSRC 	= src/main.c \
				  src/lld_i2c.c \
				  src/sensor_m3421.c \
				  src/terminal_write.c \
				  src/current_sensor.c \
				  srs/can_lld.c \
				  srs/absolute_encoder.c \
				  tests/i2c_test.c \
				  tests/sensor_m3421_test.c \
				  tests/current_sensor_test.c \
				  tests/can_test.c \
				  
				  
				  
				  
				  
				  
				  
# C++ source files
PROJECT_CPPSRC 	= 
# Directories to search headers in
PROJECT_INCDIR	= include \
                  
# Additional libraries
PROJECT_LIBS	= -lm
# Compiler options
PROJECT_OPT     = -DCHPRINTF_USE_FLOAT=1

# Additional .mk files are included here
