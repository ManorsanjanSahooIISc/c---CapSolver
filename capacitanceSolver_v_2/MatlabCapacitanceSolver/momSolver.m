
%%--------------------MOM SOLVER-------------------------%%

function chargeDensity = momSolver(numPatch, momMatrix, patch, numConductor)

potential = zeros(numPatch, numConductor);
    for condNo = 1:numConductor
       
        for patchNo = 1:numPatch
            
            if (patch(patchNo,4) == condNo)
                potential(patchNo,condNo) = 1;
            end
        end
   end
chargeDensity = inv(momMatrix) * potential;

%% -------------Elapsed time is 0.255368 seconds--------%%