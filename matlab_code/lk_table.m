% This file generate the ROM look up table
c = zeros(1,8);
for i=1:8
    c(i)=0.5*cos(pi/16*i);
end
C_o = [c(4) c(4) c(4) c(4)
       c(2) c(6) -c(6) -c(2)
       c(4) -c(4) -c(4) c(4)
       c(6) -c(2) c(2) -c(6)];
   
C_e = [c(1) c(3) c(5) c(7)
       c(3) -c(7) -c(1) -c(5)
       c(5) -c(1) c(7) c(3)
       c(7) -c(5) c(3) -c(1)];

k=4;
L_o = zeros(4,2^k);
for i=1:4
    for j=0:2^k-1
        for l=1:k
            L_o(i,j+1)=L_o(i,j+1)+fix(rem(j/2^(l-1),2))*C_o(i,k+1-l)/4;
        end
    end
end
L_e = zeros(4,2^k);
for i=1:4
    for j=0:2^k-1
        for l=1:k
            L_e(i,j+1)=L_e(i,j+1)+fix(rem(j/2^(l-1),2))*C_e(i,k+1-l)/4;
        end
    end
end

% Check the lossness of binary convertion
R_o = zeros(4,2^k);
R_e = zeros(4,2^k);
L_b_o = struct; % Create binary look up table
L_b_e = struct;
for i=1:4
    for j=1:2^k
        cov = d2b(L_o(i,j),bit,m);
        L_b_o(i,j).b=cov;
        R_o(i,j) = b2d(cov,m);
        cov = d2b(L_e(i,j),bit,m);
        L_b_e(i,j).b=cov;
        R_e(i,j) = b2d(cov,m);
    end
end
loss_o = R_o-L_o;
loss_e = R_e-L_e;

fid=fopen('lk_table.txt','wt');
fprintf(fid,'Odd\n');
for i=1:4
    for j=1:2^k
        fprintf(fid,'%s\n',dec2hex(L_b_o(i,j).b));
    end
end
fprintf(fid,'Even\n');
for i=1:4
    for j=1:2^k
        fprintf(fid,'%s\n',dec2hex(L_b_e(i,j).b));
    end
end
fclose(fid);