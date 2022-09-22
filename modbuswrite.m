function[]=modbuswrite(matlab,address,value)
Register=[0 0 0 1 1 0 1 1 2 2 1 1 2 2 0 1 1 1 1 1 1 1 1 1 1 1 1 0 0 0 0 0];
if Register(address+1)==0
    write(matlab,'holdingregs',address+1,double(value),'uint16');
end
if Register(address+1)==1
    U=single(value);
    Y=typecast(U,'uint16');
    write(matlab,'holdingregs',address+1,[double(Y(1)) double(Y(2))],'uint16');
end
if Register(address+1)==2
    L=uint32(value);
    K=typecast(L,'uint16');
    write(matlab,'holdingregs',address+1,[double(K(1)) double(K(2))],'uint16');
end
end