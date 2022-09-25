m = modbus('tcpip', '192.168.1.123', 80,'Timeout',3);
value=65;
address=36;
modbuswrite(m,address,value);
double(modbusread(m,address))
delete(m)