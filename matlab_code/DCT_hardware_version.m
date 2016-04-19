% Global variables
bit = 16; % number of bits to represent the floating point
m = 3;    % number of bits to represent the integer part of the number
shift = 8;% number of bits being shifted of input integer signal

S = [182 196 199 201 203 201 199 173 %input integer signal
     175 180 176 142 148 152 148 120
     148 118 123 115 114 107 108 107
     115 110 110 112 105 109 101 100
     104 106 106 102 104 95 98 105
     99 115 131 104 118 86 87 133
     112 154 154 107 140 97 88 151
     145 158 178 123 132 140 138 133];
% Convert input signal to binary 
S = S/2^shift;
S_b = struct;
for i=1:8
    for j=1:8
        S_b(i,j).b=d2b(S(i,j),bit,m);
    end
end
%create look up table
run('lk_table.m');
% Go through 1D dct for each row
input_1 = zeros(8,bit);
DCT_1 = struct;
for i=1:8
    for j=1:8
        input_1(j,:)=S_b(j,i).b;
    end
    result = dctbin(input_1,m,L_b_o,L_b_e,0);
    for j=1:8
        DCT_1(j,i).b=result(j,:);
    end
end

% Transpose matrix
DCT_1_d = zeros(8,8);
for i=1:8
    for j=1:8
        DCT_1_d(i,j)=2^shift*b2d(DCT_1(i,j).b,m);
    end
end
RAM = DCT_1.';

% Go through another 1D dct
DCT_2 = struct;
input_2 = zeros(8,bit);
for i=1:8
    for j=1:8
        input_2(j,:) = RAM(j,i).b;
    end
    if(i==1)
        print=1;
    else
        print=0;
    end
    result = dctbin(input_2,m,L_b_o,L_b_e,print);
    for j=1:8
        DCT_2(j,i).b=result(j,:);
    end
end

S_b_out = DCT_2.';
% reconvert the binary back to decimal to check the integrity
S_d_out = zeros(8,8);
for i=1:8
    for j=1:8
        S_d_out(i,j)=2^shift*b2d(S_b_out(i,j).b,m)*16;
    end
end

            