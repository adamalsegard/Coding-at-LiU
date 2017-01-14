function [ c, m, y, k ] = rgb2cmyk( r, g, b )
%rgb2cmyk Conversion from RGB to CMYK


    k = min(1-r, min(1-g, 1-b));
    c = (1-r-k)./(1-k);
    m = (1-g-k)./(1-k);
    y = (1-b-k)./(1-k);

end

