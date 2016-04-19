function y=shift(x,n)
[a,b]=size(x);
if n>=0
    y=[x(1,n+1:b) zeros(1,n)];
else
    if x(1)==1
        y=[ones(1,-n) x(1,1:b+n)];
    else
        y=[zeros(1,-n) x(1,1:b+n)];
    end
end