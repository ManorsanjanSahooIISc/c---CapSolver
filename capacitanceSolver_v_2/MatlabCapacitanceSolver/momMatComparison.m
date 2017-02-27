clear all;
close all;
clc;
momCpp = load('cppMOM_3D_AnaOne.txt');
momMatlab = load('matMOM_3D_AnaOne.txt');
err = momCpp-momMatlab;
normError = err./momMatlab;
% mesh(normError);
culprit = find(normError>10^-1);
relativeError = norm(momCpp - momMatlab) / norm(momMatlab);
errorPercentage = relativeError * 100;