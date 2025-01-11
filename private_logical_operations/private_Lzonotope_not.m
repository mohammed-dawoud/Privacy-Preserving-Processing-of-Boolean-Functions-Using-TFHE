function Z = private_Lzonotope_not(Z1)
% private_Lzonotope_not - overloads ~ operator, computes not of a logical zonotope
%
% Syntax:  
%    Z = not(Z1)
%
% Inputs:
%    Z1 - zonotope
%
% Outputs:
%    Z - zonotope object enclosing the and zonotope 
%
% Example: 
%
% Other m-files required: none
% Subfunctions: none
% MAT-files required: none
%
% See also: none

% Author:        Amr Alanwar
% Written:       8-Sept-2022
% Last update:   
%                
%                
% Last revision: ---

%------------- BEGIN CODE --------------

if (~isempty(Z1.c))
    
    rows = size(Z1.c,1);
    mask=ones(rows,1);
    
    newcen=private_bitxor(Z1.c,mask);
    
    % %the client encrypt the centers and pass the encrypted data to the cloud
    % cint = bit2int(Z1.c,rows);
    % maskint=bit2int(mask,rows);
    % client_encryptor(maskint,cint);
    % 
    % %start cloud execution
    % cloud_operator('xor');
    % %end cloud execution
    % 
    % %the client decrypt the result received from the cloud
    % newcenint=client_decryptor();
    % newcen=int2bit(newcenint,rows);

    Z = logicalZonotope(newcen,Z1.G);
else
    rows = size(Z1.G{1},1);
    Z = logicalZonotope(ones(rows,1),Z1.G);
end

%Z =unique(Z);
end

%------------- END OF CODE --------------