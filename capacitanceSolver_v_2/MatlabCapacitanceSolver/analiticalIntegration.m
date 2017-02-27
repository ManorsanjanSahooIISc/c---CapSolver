function MoM_entry = analiticalIntegration(node1_xyz, node2_xyz, node3_xyz, point_xyz)

dummy = [0 0 0];
MoM_entry = 0;
copy_node1 = node1_xyz;
copy_node2 = node2_xyz;
copy_node3 = node3_xyz;

area_source = computeArea(node1_xyz,node2_xyz,node3_xyz);

node2_xyz(1:3) = node2_xyz(1:3)-node1_xyz(1:3);  
node3_xyz(1:3) = node3_xyz(1:3)-node1_xyz(1:3);
node1_xyz(1:3) = point_xyz(1:3)-node1_xyz(1:3);	% Forms V01

% Finds unit vector n with direction and find d 
area_array(1) = crossMultiplication(node2_xyz(2:3), node3_xyz(2:3));
area_array(2) = crossMultiplication([node2_xyz(3) node2_xyz(1)], [node3_xyz(3) node3_xyz(1)]);
area_array(3) = crossMultiplication(node2_xyz(1:2), node3_xyz(1:2));

unit_n(1:3) = -area_array(1:3)/(area_source*2);
dot_prod = node1_xyz.*unit_n;
d = sum(dot_prod);

% Finding the point r' on the plane of the source triangle 
centroid_on_plane(1:3) = point_xyz(1:3)-(d*unit_n(1:3));
d = abs(d);
dummy = [0 0 0];
MoM_entry = 0;

% Calculate the contribution of each edge 
for i = 1:3
   flag = 1;
   % Prepare process nodes for the loop
   if(i == 1)
   	process_nodes(1,1:3) = copy_node1(1:3);
   	process_nodes(2,1:3) = copy_node2(1:3);
   elseif(i == 2) 
    process_nodes(1,1:3) = copy_node2(1:3);
    process_nodes(2,1:3) = copy_node3(1:3);
   else
    process_nodes(1,1:3) = copy_node3(1:3);
    process_nodes(2,1:3) = copy_node1(1:3);
   end;
   length_side = norm(process_nodes(1,:)-process_nodes(2,:));
   
   % Find R_plus 
   control(1:3) = process_nodes(1,1:3)-point_xyz(1:3);
   R_plus = computeDistance(control, dummy);
   
   % Find R_minus
   control(1:3) = process_nodes(2,1:3)-point_xyz(1:3);
   R_minus = computeDistance(control,dummy);
   
   % Find P_plus and P_minus 
   P_plus(1:3) = process_nodes(1,1:3)-centroid_on_plane(1:3);
   P_minus(1:3) = process_nodes(2,1:3)-centroid_on_plane(1:3);
   
   % Find unit_l 
   distance = computeDistance(process_nodes(1,1:3),process_nodes(2,1:3));
   unit_l(1:3) = (process_nodes(1,1:3)-process_nodes(2,1:3))/distance;
   
   % Find L_plus and L_minus 
   L_plus = dot(P_plus,unit_l);
   L_minus = dot(P_minus,unit_l);
   
   % Find unit_u 
   unit_u = cross(unit_l,unit_n);%*u_flag;

   % Find P0 and R0 
   P0 = dot(P_plus,unit_u);
   if(P0<0) 
      P0 = P0*-1;
   end;
   if(P0<1.0e-10*length_side)
      flag = 0;
   end;
   
   %Find unit_p
   if(flag)
    R0 = sqrt((P0*P0)+(d*d));
    unit_p(1:3) = P_plus(1:3)-(L_plus*unit_l(1:3));
	distance = computeDistance(unit_p,dummy);
   	unit_p = unit_p/distance;
    T1 = P0*log((R_plus+L_plus)/(R_minus+L_minus));
    if(P0<1.0e-6*length_side)
         if(R0<1.0e-4*length_side)
            T1=0;
         end;
   end;
      
   % Calculate the part terms used in integration
   T2 = atan(P0*L_plus/(R0*R0+d*R_plus));
   T3 = atan(P0*L_minus/(R0*R0+d*R_minus));
   T4 = dot(unit_p,unit_u);
   MoM_entry = MoM_entry+(T4*(T1-d*(T2-T3)));
   end
end

MoM_entry = (MoM_entry);
return;