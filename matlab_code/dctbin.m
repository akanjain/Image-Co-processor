function DCT=dctbin(S,m,L_b_o,L_b_e,print)
% S -- input binary signal, should be 8x12 matrix
% number of bits to represent the integer part of the number
% DCT -- output binary signal, also an 8x12 matrix

[a, b]=size(S);

X_o = [binadd(S(1,:),S(8,:))
       binadd(S(2,:),S(7,:))
       binadd(S(3,:),S(6,:))
       binadd(S(4,:),S(5,:))]; %should be a 4x12 matrix

X_e = [binsub(S(1,:),S(8,:))
       binsub(S(2,:),S(7,:))
       binsub(S(3,:),S(6,:))
       binsub(S(4,:),S(5,:))]; %should be a 4x12 matrix
if(print)
    fid=fopen('dct_signals.txt','wt');
    fprintf(fid, 'preadd_sum_out\n');
    for i=1:4
        fprintf(fid, '%s\n', dec2hex(X_o(i,:)));
    end
    fprintf(fid, 'preadd_sub_out\n');
    for i=1:4
        fprintf(fid, '%s\n', dec2hex(X_e(i,:)));
    end
end
DCT = zeros(a,b);
for i=1:4
    cb = L_b_o(i,bin2dec(dec2hex(X_o(:,1))')+1).b;
    adder_1 = binaryVectorToHex(DCT(2*i-1,:));
    DCT(2*i-1,:)=binsub(DCT(2*i-1,:),shift(cb,m));
    if(print)
        fprintf(fid, 'output[%d]\n', 2*(i-1));
        fprintf(fid, ' cycle\t|addr2rom|rom2acum_data_in|   adder_in_0   |   adder_in_1   |    adder_out   |\n');
        %fprintf(fid, ' 0\t\t| %s | %s | %s | %s |\n', dec2hex(cb), dec2hex(shift(cb,m)), adder_1, dec2hex(DCT(2*i-1,:)));
        p1 = binaryVectorToHex(cb);
        p2 = binaryVectorToHex(shift(cb,m));
        p3 = adder_1;
        p4 = binaryVectorToHex(DCT(2*i-1,:));
        fprintf(fid, ' 0\t\t|  %s  |      %s      |      %s      |      %s      |      %s      |\n',dec2hex(X_o(:,1))', p1{:}, p2{:}, p3{:}, p4{:});
    end
    for j=2:b
        cb = L_b_o(i,bin2dec(dec2hex(X_o(:,j))')+1).b;
        adder_1 = binaryVectorToHex(DCT(2*i-1,:));
        DCT(2*i-1,:)=binadd(DCT(2*i-1,:),shift(cb,m-j+1));
        if(print)
            %fprintf(fid, ' %d\t\t| %s | %s | %s | %s |\n', j-1, dec2hex(cb), dec2hex(shift(cb,m-j+1)), adder_1, dec2hex(DCT(2*i-1,:)));
               p1 = binaryVectorToHex(cb);
        p2 = binaryVectorToHex(shift(cb,m-j+1));
        p3 = adder_1;
        p4 = binaryVectorToHex(DCT(2*i-1,:));
        fprintf(fid, ' %d\t\t|  %s  |      %s      |      %s      |      %s      |      %s      |\n',j-1,dec2hex(X_o(:,j))', p1{:}, p2{:}, p3{:}, p4{:});
        end
    end
    cb = L_b_e(i,bin2dec(dec2hex(X_e(:,1))')+1).b;
    adder_1 = binaryVectorToHex(DCT(2*i,:));
    DCT(2*i,:)=binsub(DCT(2*i,:),shift(cb,m));
    if(print)
        fprintf(fid, 'output[%d]\n', 2*i-1);
        fprintf(fid, ' cycle\t|addr2rom|rom2acum_data_in|   adder_in_0   |   adder_in_1   |    adder_out   |\n');
        %fprintf(fid, ' 0\t\t| %s | %s | %s | %s |\n', dec2hex(cb), dec2hex(shift(cb,m)), adder_1, dec2hex(DCT(2*i,:)));
        p1 = binaryVectorToHex(cb);
        p2 = binaryVectorToHex(shift(cb,m));
        p3 = adder_1;
        p4 = binaryVectorToHex(DCT(2*i,:));
        fprintf(fid, ' 0\t\t|  %s  |      %s      |      %s      |      %s      |      %s      |\n',dec2hex(X_e(:,1))', p1{:}, p2{:}, p3{:}, p4{:});
    end
    for j=2:b
        cb = L_b_e(i,bin2dec(dec2hex(X_e(:,j))')+1).b;
        adder_1 = binaryVectorToHex(DCT(2*i,:));
        DCT(2*i,:)=binadd(DCT(2*i,:),shift(cb,m-j+1));
        if(print)
            %fprintf(fid, ' %d\t\t| %s | %s | %s | %s |\n', j-1, dec2hex(cb), dec2hex(shift(cb,m-j+1)), adder_1, dec2hex(DCT(2*i,:)));
            p1 = binaryVectorToHex(cb);
            p2 = binaryVectorToHex(shift(cb,m-j+1));
            p3 = adder_1;
            p4 = binaryVectorToHex(DCT(2*i,:));
            fprintf(fid, ' %d\t\t|  %s  |      %s      |      %s      |      %s      |      %s      |\n', j-1, dec2hex(X_e(:,j))', p1{:}, p2{:}, p3{:}, p4{:});
        end
    end
end
