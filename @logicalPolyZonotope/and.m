function Z = and(Z1,Z2,varargin)
% and - overloads & operator, computes the AND of two logical poly zonotopes
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
% Written:       7-Jan-2023
% Last update:
%
%
% Last revision: ---

%------------- BEGIN CODE --------------

if ~isa(Z1,'logicalPolyZonotope')
    Z1=logicalZonotope.enclosePoints(Z1);
    Z1=logicalPolyZonotope(Z1.c,Z1.G,eye(length(Z1.G)));
end

if ~isa(Z2,'logicalPolyZonotope')
    Z2=logicalZonotope.enclosePoints(Z2);
    Z2=logicalPolyZonotope(Z2.c,Z2.G,eye(length(Z2.G)));
end

if(~isempty(Z1.c) && ~isempty(Z2.c))
    newcen = Z1.c & Z2.c;
end




h1=length(Z1.G);
p1=size(Z1.E,1);

h2=length(Z2.G);
p2=size(Z2.E,1);
zeroVec = logical(zeros(size(Z1.c)));
newE =[];
index =1;
newGen ={};

% there is no generators in Z2 to multiply with Z1



%c2 * G1
if(~isempty(Z2.c) && ~isempty(Z1.G))
    for i=1:length(Z1.G)
        vecAnd = Z2.c & Z1.G{i};
        if isequal(vecAnd,zeroVec)
            continue;
        end
        newGen{index} = vecAnd;
        newE = [newE [Z1.E(:,i);zeros(p2,1)]];
        index=index+1;
    end
end

%c1 * G2
if(~isempty(Z1.c) && ~isempty(Z2.G))
    for i=1:length(Z2.G)
        vecAnd = Z1.c & Z2.G{i};
        if isequal(vecAnd,zeroVec)
            continue;
        end
        newGen{index} = vecAnd;
        newE = [newE [zeros(p1,1);Z2.E(:,i)]];        
        index=index+1;
    end
end
%G1 * G2
if(~isempty(Z1.G) && ~isempty(Z2.G))
    for i=1:length(Z1.G)
        for k=1:length(Z2.G)
            vecAnd = (Z1.G{i} & Z2.G{k});
            if isequal(vecAnd,zeroVec)
                continue;
            end
            newGen{index} = vecAnd;
            newE = [newE [Z1.E(:,i);Z2.E(:,k)]]; 
            index=index+1;
        end
    end
end


Z = logicalPolyZonotope(newcen,newGen,newE);
Z = unique(Z);


end

%------------- END OF CODE --------------