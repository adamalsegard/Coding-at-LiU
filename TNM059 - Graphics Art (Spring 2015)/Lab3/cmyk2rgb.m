function [ r, g, b ] = cmyk2rgb(c, m, y, k  )
%cmyk2rgb Conversion from CMYK to RGB

    r = 1-c.*(1-k)-k;
    g = 1-m.*(1-k)-k;
    b = 1-y.*(1-k)-k;

end

