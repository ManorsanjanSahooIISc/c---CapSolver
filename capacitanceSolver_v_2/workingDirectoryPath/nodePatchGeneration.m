clear all;
close all;
clc;

l = input ('p_length:');
b = input ('p_breadth:');
d_x = input ('Discretization in x:');
d_y = input ('Discretization in y:');
%z = input ('Enter location of z:');

vertices = zeros((d_x+1)*(d_y+1),3);
patches = zeros((d_x*d_y)*2,4);
nodeIndex = 0;
patchIndex=0;
x=input('Enter starting location of x:');
r=x;
y=input('Enter starting location of y:');
   
for j=1:d_y+1
     
    for i= 1:d_x+1
         nodeIndex=nodeIndex+1;
         vertices(nodeIndex,1)=x;
         vertices(nodeIndex,2)=y;
         vertices(nodeIndex,3)=0;

       %  v(count,3)=z;
         x=x+l/d_x;
    end
    y=y+b/d_y;
     x=r;
end
for j = 1:d_y
    for i = 1:d_x  
         patchIndex=patchIndex+1;
         patches(patchIndex,1)=i+(j-1)*(d_x+1);
         patches(patchIndex,2)=i+1+(j-1)*(d_x+1);
         patches(patchIndex,3)=j*(d_x+1)+i;
         patches(patchIndex,4)=int16(1);
         
         patchIndex=patchIndex+1;
         patches(patchIndex,1)=1+i+(j-1)*(d_x+1); 
         patches(patchIndex,2)=j*(d_x+1)+i+1;
         patches(patchIndex,3)=j*(d_x+1)+i;
         patches(patchIndex,4)=int16(1);
    end
end
save nodelist12800.txt vertices -ASCII;
% save patchList.txt patches -ascii;

findpatchlist = fopen('patchlist12800.txt', 'wt'); % Open for writing
for i=1:size(patches,1)
   fprintf(findpatchlist, '%d ', patches(i,:));
   fprintf(findpatchlist, '\n');
end
fclose(findpatchlist);

%disp (vertices);
%   
%  for i=1:(d_x+1)*(d_y+1)
%      plot(vertices(i,1),vertices(i,2),'r*');
%       hold on;
%       s=sprintf('%d',i);
%       text(vertices(i,1),vertices(i,2),s);
%       hold on;
%       
%  end
  
%  patch('Faces',patches(:,1:3),'Vertices',vertices(:,1:3),'FaceColor','w');
% plist = int8(patches);
