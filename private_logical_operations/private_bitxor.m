function newPoint = private_bitxor(point1,point2)
%PRIVATE_BITXOR Summary of this function goes here
%   Detailed explanation goes here


 rows1 = size(point1,1);
 rows2 = size(point2,1);
 rows=rows1;
    if rows2>rows
    rows=rows2;
    end

 p1int = bit2int(point1,rows);
 p2int = bit2int(point2,rows);
 
 %the client encrypt the points and pass the encrypted data to the cloud
 client_encryptor(p1int,p2int);
 
 %start cloud execution
 cloud_operator('xor');
 %end cloud execution

%the client decrypt the result received from the cloud
 newPointint=client_decryptor();
 newPoint=int2bit(newPointint,rows);
end

