% clear all;
% close all;
clc;
format long; tic;
%% ........................READ MESH..........................%%
%...................Load node & patch list....................%
nodeList = load('nodelist_3D.txt');
patchList = load('patchlist_3D.txt');

%% .................Finding no. of patch and conductor .......%%
[numPatches, dummy] = size(patchList);
numConductors = max(patchList(:,4));

%% .................MOM Matrix Generation.....................%%
%momMattrix = momFiller(nodeList, patchList, numPatchs);
momMatrix = load('matMOM_3D.txt');

%% ............ Doing GMRES...............%%
iterativeSolverChargeDensity = zeros(numPatches,numConductors);
b = getRhsForGMRES(numPatches, patchList, numConductors);
tol = 10^-9;
preCondMat = getPreCondMat(momMatrix, numPatches);
restart = 20;
maxIteration = 200;
for i = 1:numConductors
    l = iterativeSolverChargeDensity(:,i);
    m = b(:,i);
[l, error, iter, flag] = doGMRES(momMatrix, l, m, preCondMat, restart, maxIteration, tol);
iterativeSolverChargeDensity(:,i) = l;
end
 save('R100.txt','iterativeSolverChargeDensity','-ASCII');

 %% ......Error Calculation..................%%
 directSolverChargeDensity = load('chargeDensity.txt');
%  errorInChargeDensity = directSolverChargeDensity - iterativeSolverChargeDensity; 
 %% ...............Capacitance  Matrix.........................%%
 capMatrix = capacitanceMatrix(numConductors, patchList, nodeList, numPatches, iterativeSolverChargeDensity);

 trueCapicatance = load('AnswerCapacitanceMatrix.txt');
relativeError = norm(trueCapicatance - capMatrix) / norm(trueCapicatance);
errorPercentage = relativeError * 100;
%% ..............Error Calculation............................%%
% trueCapicatance = load('AnswerCapacitanceMatrix.txt');
% relativeError = norm(trueCapicatance - capMatrix) / norm(trueCapicatance);
% errorPercentage = relativeError * 100;
% save('momMatrixml.txt','momMattrix','-ASCII');
toc;
%%_______________________________END___________________________________%%