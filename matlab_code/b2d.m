function y=b2d(x,m)
% x -- the input binary number in the form of vector
% y -- the output decimal number
n=size(x);% the number of bits in x
% m -- the number of bits used to represent integer part of the number
y=-2^m*x(1);
for i=2:n(2)
    y=y+2^(m-i+1)*x(i);
end