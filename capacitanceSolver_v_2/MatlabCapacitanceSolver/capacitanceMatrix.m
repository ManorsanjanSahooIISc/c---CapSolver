%%------------------CAPACITANCE MATRIX -----------------------%%

function capacitanceMatrix = capacitanceMatrix(numConductor, patchList, nodeList, numPatchs, chargeDensityMatrix)

%% ------------------AREA CALCULATION..........---------.......%%
Area = zeros(numPatchs, 1);
for i = 1:numPatchs
    Area(i) = computeArea(nodeList(patchList(i,1),1:3),nodeList(patchList(i,2),1:3),nodeList(patchList(i,3),1:3)); 
end

%% .............SOLVE CAPACITANCE MATRIX.....................%%
capacitanceMatrix = zeros(numConductor, numConductor);
for j = 1:numConductor
    for k = 1:numConductor
      chargeSum = 0;
        for i = 1:numPatchs
            
            if(patchList(i,4) == k)
                charge = Area(i,1) * chargeDensityMatrix(i,j);
                chargeSum = chargeSum + charge;
            end
        end
        %Since Q = CV, as we have taken V =1v, Q = C%
        capacitanceMatrix(k,j) = chargeSum;
    end
end
%...........................%%...............................%