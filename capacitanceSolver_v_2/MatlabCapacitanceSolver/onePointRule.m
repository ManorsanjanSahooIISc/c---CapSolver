function integral_val=onePointRule(source_centroid,observer_centroid)
d = computeDistance(source_centroid,observer_centroid);
integral_val=1/d;
%integral_val=integral_vall*compute_area(node1_xyz,node2_xyz,node3_xyz);
end