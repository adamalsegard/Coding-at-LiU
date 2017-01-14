function [ w ] = myvector( v, a, b, n )

if a<=0
    a=1;
end

if n > length(v)
    n = length(v);
end
    

plats = 1;

for i = a:b:n

    w(plats) = v(i);
    plats = plats+1;
end
  

end
