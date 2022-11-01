function[Res]=modbusread(matlab,address)
Register=[0 3 1 1 1 1 2 2 1 1 2 2 1 1 1 1 1 1 1 1 1 1 1 1 0 3 1 1 1 1 1 1 1 1 0 0 0 0];
if Register(address+1)==0
    Res=read(matlab,'holdingregs',address+1,1,'int16');
end
if Register(address+1)==1
    J=read(matlab,'holdingregs',address+1,2,'uint16');
    K=typecast(uint16(J),'uint16');
    Res=typecast(K,'single');
end
if Register(address+1)==2
    J=read(matlab,'holdingregs',address+1,2,'uint16');
    K=typecast(uint16(J),'uint16');
    Res=typecast(K,'uint32');
end
end