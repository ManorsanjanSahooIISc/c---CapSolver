% Get RHS for GMRES.
function potential = getRhsForGMRES(numPatch, patchList, numConductor)
v = zeros(numPatch, numConductor);
    
    for condNo = 1:numConductor
       for patchNo = 1:numPatch
            
            if (patchList(patchNo,4) == condNo)
                v(patchNo,condNo) = 1;
            end
        end
    potential = v;   
%     return potential;
    end