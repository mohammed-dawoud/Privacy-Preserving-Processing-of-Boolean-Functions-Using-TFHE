function Z = private_conLzonotope_not(Z1)
% and - overloads ~ operator, computes not of a logical zonotope
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
    [rows,cols] = size(Z1.c);
    Z = logicalConPolyZonotope(private_bitxor(ones(rows,1),Z1.c),Z1.G,Z1.E,Z1.A,Z1.b,Z1.EC,Z1.id);
else
    [rows,cols] = size(Z1.G{1});
    Z = logicalConPolyZonotope(logical(ones(rows,1)),Z1.G,Z1.E,Z1.A,Z1.b,Z1.EC,Z1.id);
end



end

%------------- END OF CODE --------------