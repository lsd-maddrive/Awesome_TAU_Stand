m = modbus('tcpip', '192.168.1.123', 80,'Timeout',3);
value=888888;
address=8;
modbuswrite(m,address,value);
modbusread(m,address)
delete(m)