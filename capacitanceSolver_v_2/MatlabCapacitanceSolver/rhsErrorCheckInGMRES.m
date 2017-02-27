% EROR checking between c++ MOM and matlab MOM
clc;
matMOM = load('r100.txt');
cppMOM = load('r50.txt');
% Norm by norm Error Check.
NornError = norm(matMOM-cppMOM)/ norm(matMOM);
res = (matMOM-cppMOM)./(matMOM);
% err = res(res>10^-2);
%  errorIndice = find(res>10^-3);
%  matSize = size(matMOM);
%  errRes=zeros(matSize);
% 
% %count = zeros(matSize,matSize);
% for i = 1:matSize
%     for j = 1:matSize
%         if (res(i,j)>10^-2)
%             errRes(i,j)=res(i,j);
%         else
% %         count(i,j)=1;    
%         end
%     end
% end

% Mesh the Error.
%mesh(matMOM-cppMOM);