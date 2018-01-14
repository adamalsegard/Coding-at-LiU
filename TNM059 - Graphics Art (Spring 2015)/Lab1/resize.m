function [ bild2 ] = resize( bild1 )
%UNTITLED3 Summary of this function goes here
%   Detailed explanation goes here
    
   [m, n] = size(bild1);

   pi = 1;
   pj = 1;
    for i = 1:2:m
        for j = 1:2:n
            
            bild2(pi, pj) = (bild1(i, j) + bild1(i+1, j) + bild1(i, j+1) + bild1(i+1,j+1))/4;
            pj = pj+1;
        end
       pj = 1;
       pi = pi+1;
    end

end

