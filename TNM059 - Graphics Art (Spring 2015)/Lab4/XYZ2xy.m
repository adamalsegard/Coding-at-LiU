function [ x, y ] = XYZ2xy( X, Y, Z )
%

    x = X/(X + Y + Z);
    y = Y/(X + Y + Z);

end

