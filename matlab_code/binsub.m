function y=binsub(x1,x2)
[a,b]=size(x2);
for i=1:b
    x2(i)=1-x2(i);
end
x2 = binadd(x2,[zeros(1,b-1) 1]);
y=binadd(x1,x2);