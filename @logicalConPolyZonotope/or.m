function Z = or(Z1,Z2)
% and - overloads | operator, computes the or of two logical poly zonotopes
%
% Syntax:  
%    Z = or(Z1,Z2)
%
% Inputs:
%    Z1 - logical poly zonotope
%    Z2 - logical poly zonotope, 
%
% Outputs:
%    Z - logical poly zonotope object enclosing the or logical poly zonotope 
%
% Example: 
%
% Other m-files required: none
% Subfunctions: none
% MAT-files required: none
%
% See also: none

% Author:        Amr Alanwar
% Written:       7-Jan-2023
% Last update:   
%                
%                
% Last revision: ---

%------------- BEGIN CODE --------------
if ~isa(Z1,'logicalConPolyZonotope')
    Z1=logicalZonotope.enclosePoints(Z1);
    Z1=logicalPolyZonotope(Z1.c,Z1.G,eye(length(Z1.G)));
end

if ~isa(Z2,'logicalConPolyZonotope')
    Z2=logicalZonotope.enclosePoints(Z2);
    Z2=logicalPolyZonotope(Z2.c,Z2.G,eye(length(Z2.G)));
end


Z = nand(not(Z1),not(Z2));
%Z = nand(nand(Z1,Z1),nand(Z2,Z2));


end

%------------- END OF CODE --------------