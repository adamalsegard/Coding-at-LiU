function K=kern1(N,sig)
% ver: 07:38  95.02.16
%K1=ones([N,N])
%disp('kern1..');
x=-N:N;
y=x;
[X,Y]=meshgrid(x,y);
K1=exp(-(X.^2+Y.^2)/sig^2/2);
%K1=exp(-sqrt(sqrt((abs(X)+abs(Y)))));
K=K1/sum(sum(K1));
%sum(sum(K))
%K=K1;
