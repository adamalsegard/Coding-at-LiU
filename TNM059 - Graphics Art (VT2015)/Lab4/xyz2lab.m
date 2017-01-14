function [ Lab ] = xyz2lab( XYZ, XoYoZo )
% Lab=xyz2lab(XYZ,XoYoZo)
%
% XoYoZo = CIEXYZ-v�rden f�r vitpunkten (belysningen).
% XYZ = CIEXYZ-v�rden f�r f�rgen som ska konverteras till CIELABv�rden.

% Lab = CIELAB-v�rden f�r den konverterade f�rgen.
% Formlerna f�r konvertering �terfinns i laboration 3.

Xn = XoYoZo(1);
Yn = XoYoZo(2);
Zn = XoYoZo(3);

x = XYZ(1);
y = XYZ(2);
z = XYZ(3);

ylim = Yn*0.008856;
L = (y>ylim).*(116*(y/Yn).^(1/3)-16)+(y<=ylim).*(903.3*y/Yn);
ytemp = foo(y/Yn);
a = 500*(foo(x/Xn)-ytemp);
b = 200*(ytemp-foo(z/Zn));

Lab = [L, a, b];


end

