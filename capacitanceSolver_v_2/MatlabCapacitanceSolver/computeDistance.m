
%%-----------------Compute Distance by NORM--------------%%
function distance=computeDistance(point1_xyz,point2_xyz)
distance_xyz(1:3)=point1_xyz(1:3)-point2_xyz(1:3);
distance=norm(distance_xyz);
return;
