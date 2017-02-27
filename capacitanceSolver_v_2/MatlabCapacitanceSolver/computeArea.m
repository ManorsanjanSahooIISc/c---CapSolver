function area=computeArea(node1_xyz,node2_xyz,node3_xyz)

node2_xyz(1:3)=node2_xyz(1:3)-node1_xyz(1:3);
node3_xyz(1:3)=node3_xyz(1:3)-node1_xyz(1:3);

area_array(1) = crossMultiplication(node2_xyz(2:3),node3_xyz(2:3));
area_array(2) = crossMultiplication([node2_xyz(3) node2_xyz(1)],[node3_xyz(3) node3_xyz(1)]);
area_array(3) = crossMultiplication(node2_xyz(1:2),node3_xyz(1:2));
    
area=norm(area_array)/2;
return;