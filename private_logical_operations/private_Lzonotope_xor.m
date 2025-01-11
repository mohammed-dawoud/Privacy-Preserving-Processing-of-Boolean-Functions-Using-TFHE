function Z = private_Lzonotope_xor(Z1,Z2,varargin)
% private_Lzonotope_xor - overloads xor operator, computes the XOR of two logical zonotopes
%
% Syntax:  
%    Z = and(Z1,Z2)
%
% Inputs:
%    Z1 - zonotope
%    Z2 - zonotope, 
%
% Outputs:
%    Z - zonotope object enclosing the and zonotope 
%
% Example: 
%    zono1 = zonotope([4 2 2;1 2 0]);
%    zono2 = zonotope([3 1 -1 1;3 1 2 0]);
%
%    res = zono1 & zono2
%
%    figure
%    hold on
%    plot(zono1,[1,2],'r');
%    plot(zono2,[1,2],'b');
%    plot(res,[1,2],'g');
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
if ~isa(Z1,'logicalZonotope') 
Z1=logicalZonotope.enclosePoints(Z1);
end

if ~isa(Z2,'logicalZonotope') 
Z2=logicalZonotope.enclosePoints(Z2);

end

 % rows1 = size(Z1.c,1);
 % rows2 = size(Z2.c,1);
 % rows=rows1;
 %    if rows2>rows
 %    rows=rows2;
 %    end


if(~isempty(Z1.c) & ~isempty(Z2.c))

 newCen = private_bitxor(Z1.c,Z2.c);

 % %the client encrypt the centers and pass the encrypted data to the cloud   
 % Z1cint = bit2int(Z1.c,rows);
 % Z2cint = bit2int(Z2.c,rows);
 % client_encryptor(Z1cint,Z2cint);
 % 
 % %start cloud execution
 % cloud_operator('xor');
 % %end cloud execution
 % 
 % %the client decrypt the result received from the cloud
 % newcenint=client_decryptor();
 % newCen=int2bit(newcenint,rows);


 %newCen = xor( Z1.c,Z2.c );
 
elseif (isempty(Z1.c) & isempty(Z2.c))
    newCen =[];
elseif isempty(Z1.c)
    newCen = Z2.c ;
elseif isempty(Z2.c)
    newCen = Z1.c ;
end

if(isempty(Z1.G))
    newGen = Z2.G;
elseif(isempty(Z2.G))
    newGen = Z1.G;
elseif(isempty(Z2.G) & isempty(Z2.G))
    newGen ={};
elseif(~isempty(Z2.G) & ~isempty(Z2.G))
    g1Len = length(Z1.G);
    g2Len = length(Z2.G);
    newGen = Z1.G;
    index =1;
    for i=g1Len+1:g1Len+g2Len
        newGen{i} =  Z2.G{index};
        index = index +1;
    end
end

Z=logicalZonotope(newCen,newGen);
Z =unique(Z);

end

%------------- END OF CODE --------------