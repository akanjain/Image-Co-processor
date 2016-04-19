function y=binadd(x1,x2)
[a,b]=size(x1);
c=0;
y=zeros(1,b);
for i=b:-1:1
    y(i)=x1(i)+x2(i)+c;
    if y(i)==2
        y(i)=0;
        c=1;
    elseif y(i)==3
        y(i)=1;
        c=1;
    else
        c=0;
    end
end
    