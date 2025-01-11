function Z = private_Lzonotope_and(Z1,Z2,varargin)
% private_Lzonotope_and - overloads and operator, computes the AND of two logical zonotopes
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
%
% Other m-files required: none
% Subfunctions: none
% MAT-files required: none
%
% See also: none

% Author:        Amr Alanwar
% Written:       8-Aug-2022
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
    
   newcen=private_bitand(Z1.c,Z2.c);
 
%  Z1cint = bit2int(Z1.c,rows);
%  Z2cint = bit2int(Z2.c,rows);
% 
%  %the client encrypt the centers and pass the encrypted data to the cloud
%  client_encryptor(Z1cint,Z2cint);
% 
%  %start cloud execution
%  cloud_operator('and');
%  %end cloud execution
% 
% %the client decrypt the result received from the cloud
%  newcenint=client_decryptor();
%  newcen=int2bit(newcenint,rows);
 
 %newcen = (Z1.c & Z2.c);
else
newcen =[];
end

if(~isempty(Z1.G) & ~isempty(Z2.G))
    %c2 * G1
    index =1;
    if(~isempty(Z2.c))
        for i=1:length(Z1.G)
            
            newGen{index}=private_bitand(Z2.c,Z1.G{i});
            
            % %the client encrypt the center of the second zonotope and pass the encrypted data to the cloud
            % Z1gint = bit2int(Z1.G{i},rows);
            % Z2cint = bit2int(Z2.c,rows);
            % client_encryptor(Z2cint,Z1gint);
            % %start cloud execution
            % cloud_operator('and');
            % %end cloud execution
            % 
            % %the client decrypt the result received from the cloud
            % newGenint=client_decryptor();
            % newGen{index}=int2bit(newGenint,rows);
            
            %newGen{index} = (Z2.c & Z1.G{i});
            index=index+1;
        end
    end
    if(~isempty(Z1.c))
        for i=1:length(Z2.G)
            
            newGen{index} = private_bitand(Z1.c,Z2.G{i});
            % %the client encrypt the center of the first zonotope and pass the encrypted data to the cloud
            % Z2gint = bit2int(Z2.G{i},rows);
            % Z1cint = bit2int(Z1.c,rows);
            % client_encryptor(Z1cint,Z2gint);
            % %start cloud execution
            % cloud_operator('and');
            % %end cloud execution
            % 
            % %the client decrypt the result received from the cloud
            % newGenint=client_decryptor();
            % newGen{index}=int2bit(newGenint,rows);
            
            %newGen{index} = (Z1.c & Z2.G{i});
            index=index+1;
        end
    end
    %G1 * G1
    for i=1:length(Z1.G)
        %[rows,cols]=size(Z1.G{i});
        for k=1:length(Z2.G)
            newGen{index} = bitand(Z1.G{i},Z2.G{k});
            index=index+1;
        end
    end

    Z = logicalZonotope(newcen,newGen);
elseif(isempty(Z1.G) & isempty(Z2.G))
    Z = logicalZonotope(newcen,{});

elseif (isempty(Z2.G))
    %c2 * G1

    index =1;
    newGen ={};
    if(~isempty(Z2.c))
        for i=1:length(Z1.G)
            
            newGen{index} = private_bitand(Z2.c,Z1.G{i});

            % %the client encrypt the center of the second zonotope and pass the encrypted data to the cloud
            % Z1gint = bit2int(Z1.G{i},rows);
            % Z2cint = bit2int(Z2.c,rows);
            % client_encryptor(Z2cint,Z1gint);
            % %start cloud execution
            % cloud_operator('and');
            % %end cloud execution
            % 
            % %the client decrypt the result received from the cloud
            % newGenint=client_decryptor();
            % newGen{index}=int2bit(newGenint,rows);
            
            %newGen{index} = (Z2.c & Z1.G{i});
            index=index+1;
        end
    end

    Z = logicalZonotope(newcen,newGen);
elseif (isempty(Z1.G))
    %c2 * G1
    newGen = Z2.G;

    index =length(newGen)+1;
    if(~isempty(Z1.c))
        for i=1:length(Z2.G)
            
            newGen{index} =  private_bitand(Z1.c,Z2.G{i});

            % %the client encrypt the center of the first zonotope and pass the encrypted data to the cloud
            % Z2gint = bit2int(Z2.G{i},rows);
            % Z1cint = bit2int(Z1.c,rows);
            % client_encryptor(Z1cint,Z2gint);
            % %start cloud execution
            % cloud_operator('and');
            % %end cloud execution
            % 
            % %the client decrypt the result received from the cloud
            % newGenint=client_decryptor();
            % newGen{index}=int2bit(newGenint,rows);

            %newGen{index} =  (Z1.c & Z2.G{i});
            index=index+1;
        end
    end

    newGen{index} = (Z2.c) ;


    Z = logicalZonotope(newcen,newGen);

end
Z = unique(Z);
end

%------------- END OF CODE --------------