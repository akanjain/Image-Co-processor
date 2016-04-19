%Print out test signals
run ('DCT_hardware_version.m');
fid = fopen('test_signals.txt','wt');

%input signal
fprintf(fid,'Input signal\n');
for i=1:8
    for j=1:8
        decimal = -2^(bit-1)*S_b(j,i).b(1);
        for k=2:bit
            decimal = decimal + 2^(bit-k)*S_b(j,i).b(k);
        end
        a=binaryVectorToHex(S_b(j,i).b);
        fprintf(fid, 'x_%d_%d = %s (%d)\n', j-1, i-1, a{1}, decimal);
    end
end

%correct results for the first dct
fprintf(fid, '1st dct outputs\n');
for i=1:8
    for j=1:8
        decimal = -2^(bit-1)*DCT_1(j,i).b(1);
        for k=2:bit
            decimal = decimal + 2^(bit-k)*DCT_1(j,i).b(k);
        end
        a=binaryVectorToHex(DCT_1(j,i).b);
        fprintf(fid, 'DCT_1_%d_%d = %s (%d)\n', j-1, i-1, a{1}, decimal);
    end
end
%correct results for the transpose ram output
fprintf(fid, '\nRAM outputs\n');
for i=1:8
    for j=1:8
        decimal = -2^(bit-1)*RAM(j,i).b(1);
        for k=2:bit
            decimal = decimal + 2^(bit-k)*RAM(j,i).b(k);
        end
        a=binaryVectorToHex(RAM(j,i).b);
        fprintf(fid, 'RAM_%d_%d = %s (%d)\n', j-1, i-1, a{1}, decimal);
    end
end
%correst results for the second dct
fprintf(fid, '\n2st dct outputs\n');
for i=1:8
    for j=1:8
        decimal = -2^(bit-1)*DCT_2(j,i).b(1);
        for k=2:bit
            decimal = decimal + 2^(bit-k)*DCT_2(j,i).b(k);
        end
        a=binaryVectorToHex(DCT_2(j,i).b);
        fprintf(fid, 'DCT_2_%d_%d = %s (%d)\n', j-1, i-1, a{1}, decimal);
    end
end
fclose(fid);