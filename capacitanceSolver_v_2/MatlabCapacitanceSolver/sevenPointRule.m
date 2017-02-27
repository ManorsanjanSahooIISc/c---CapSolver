%% .......Weight(7 values) xsi,eta,gamma calculation....................%% 
%%--------------Function Seven Point---------------------%%
function int_value=sevenPointRule(n1,n2,n3,observer_centroid)

weight=[0.225 0.13239415278851 0.13239415278851 0.13239415278851 0.12593918054483 0.12593918054483 0.12593918054483];
xsi=[0.3333333 0.0597158 0.470142 0.470142 0.7974269 0.1012865 0.1012865];
eta=[0.3333333 0.470142 0.0597158 0.470142 0.1012865 0.7974269 0.1012865];
gamma=1-xsi-eta;
for i=1:7
    rsource(i,:)=n1*xsi(i)+n2*eta(i)+n3*gamma(i);
end
%rsource=(n1.*xsi)+(n2.*eta)+(n3.*gamma);
a=0;
for i=1:7
  a=a+(weight(i)/computeDistance(rsource(i,:),observer_centroid));  
end
%a=a*compute_area(n1,n2,n3);
int_value=a;