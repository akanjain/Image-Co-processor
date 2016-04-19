function y=d2b(x,bit,m)
% x -- the input decimal number
% t -- the type of input: 0 -- integer, 1 -- float
% y -- the binary result in the form of vector
% bit -- use 12 bits to represent the floating point
% m -- use 3 bits to represent the integer part of number
y=zeros(1,bit);
if x>=0
    y(2:bit)=fix(rem(x*pow2(-(m-1):bit-m-1),2));
else
    a=2^(m+1)+x;
    y=fix(rem(a*pow2(-m:bit-m-1),2));
end