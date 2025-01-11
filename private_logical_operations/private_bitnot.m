function newPoint = private_bitnot(point1)
%PRIVATE_BITNOT Summary of this function goes here
%   Detailed explanation goes here


 rows = size(point1,1);

 p1int = bit2int(point1,rows);
 
 %the client encrypt the point and pass the encrypted data to the cloud
 client_encryptor(p1int,0);
 
 %start cloud execution
 cloud_operator('not');
 %end cloud execution

%the client decrypt the result received from the cloud
 newPointint=client_decryptor();
 newPoint=int2bit(newPointint,rows);
end

