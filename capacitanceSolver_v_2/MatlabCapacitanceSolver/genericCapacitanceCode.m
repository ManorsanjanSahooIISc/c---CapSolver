clear all;
close all;
clc;
format long; tic;
%% ........................READ MESH..........................%%
%...................Load node & patch list....................%
nodeList = load('../workingDirectoryPath/nodeList8.txt');
patchList = load('../workingDirectoryPath/patchList8.txt');

%% .................Finding no. of patch and conductor .......%%
[numPatchs, dummy] = size(patchList);
numConductors = max(patchList(:,4));

%% .................MOM Matrix Generation.....................%%
momMattrix = momFiller(nodeList, patchList, numPatchs);

%% ................Charge Density Calculation.................%%
chargeDensityMatrix = momSolver(numPatchs, momMattrix, patchList, numConductors);

%% ...............Capacitance  Matrix.........................%%
capMatrix = capacitanceMatrix(numConductors, patchList, nodeList, numPatchs, chargeDensityMatrix);

%% ..............Error Calculation............................%%
 trueCapicatance = load('AnswerCapacitanceMatrix.txt');
 relativeError = norm(trueCapicatance - capMatrix) / norm(trueCapicatance);
 errorPercentage = relativeError * 100;
save('matMOM_3DAnaOne.txt','momMattrix','-ASCII');
save ('chargeDensity.txt','chargeDensityMatrix','-ASCII');
toc;
%%_______________________________END___________________________________%%