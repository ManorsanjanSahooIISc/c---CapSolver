function preCondMat = getPreCondMat(momMatrix, numPatches)


preCondMat = zeros(numPatches,numPatches);
for i = 1:numPatches
    
    for j = 1:numPatches
    
        if(i==j)
            preCondMat(i,j) = momMatrix(i,j);
        end
     
    end
    
end
end
