function [x, error, iter, flag] = doGMRES( momMat, x, b, M, restrt, max_iteration, tol )
   iter = 0;                                            % initialization
   flag = 0;
   bnrm2 = norm( b );
   if( bnrm2 == 0.0 )    
       bnrm2 = 1.0;
   end
   
   r = M\( b-momMat*x );
   error = norm(r)/ bnrm2;
   if ( error < tol) 
       return;
   end
 % initialize workspace
   [~,n] = size(momMat);    
   m = restrt;
   V = zeros(n,(m+1));
   H = zeros(m+1,m);
   a_1(1:m) = zeros(m,1);
   b_1(1:m) = zeros(m,1);
   e1 = zeros(n,1);
   e1(1) = 1.0;
% begin iteration
   for iter = 1:max_iteration,                        

      r = M \(b-momMat*x );
      V(:,1) = r/norm(r);
      s = norm( r )*e1;
    %construct orthonormal
    for i = 1:m,
     %basis using Gram-Schmidt
	 w = M \ (momMat*V(:,i));                         
	 for k = 1:i,
	   H(k,i)= w'*V(:,k);
	   w = w - H(k,i)*V(:,k);
	 end
	 H(i+1,i) = norm(w);
	 V(:,i+1) = w / H(i+1,i);
	 % apply Givens rotation
     for k = 1:i-1,                                  
            temp     =  a_1(k)*H(k,i) + b_1(k)*H(k+1,i);
            H(k+1,i) = -b_1(k)*H(k,i) + a_1(k)*H(k+1,i);
            H(k,i)   = temp;
     end
     % form i-th rotation matrix
     [a_1(i),b_1(i)] = rotmat( H(i,i), H(i+1,i));
        % approximate residual norm    
         temp   = a_1(i)*s(i);                       
         s(i+1) = -b_1(i)*s(i);
	 s(i)   = temp;
         H(i,i) = a_1(i)*H(i,i) + b_1(i)*H(i+1,i);
         H(i+1,i) = 0.0;
	 error  = abs(s(i+1)) / bnrm2;
	 % update approximation
       if ( error <= tol ),                           
	     % and exit
         y = H(1:i,1:i) \ s(1:i);                   
            x = x + V(:,1:i)*y;
	    break;
	  end
    end

      if ( error <= tol ) 
          break;
      end
      y = H(1:m,1:m) \ s(1:m);
      % update approximation
      x = x + V(:,1:m)*y;                            
      % compute residual
      r = M \ ( b-momMat*x );                        
      s(i+1) = norm(r);
      % check convergence
      error = s(i+1) / bnrm2;                        
      if ( error <= tol ), break, end;
   end

   if ( error > tol ) 
       flag = 1; 
   end; 
   % converged

%% ........ END of gmres.m .......................... %%