%% 2.1

plot(xyz(:,1),xyz(:,2:4))

k1 = 100/sum(xyz(:,3).*(d65(:,2)));

x0 = k1*sum(xyz(:,2).*d65(:,2))
y0 = k1*sum(xyz(:,3).*d65(:,2))
z0 = k1*sum(xyz(:,4).*d65(:,2))


plot(R1(:, 1), R1(:, 2), R2(:, 1), R2(:, 2));

%%
% D65 + R1
x1 = k1*sum(xyz(:,2).*d65(:,2).*R1(:,2));
y1 = k1*sum(xyz(:,3).*d65(:,2).*R1(:,2));
z1 = k1*sum(xyz(:,4).*d65(:,2).*R1(:,2));
% D65 + R2
x2 = k1*sum(xyz(:,2).*d65(:,2).*R2(:,2));
y2 = k1*sum(xyz(:,3).*d65(:,2).*R2(:,2));
z2 = k1*sum(xyz(:,4).*d65(:,2).*R2(:,2));


k2 = 100/sum(xyz(:,3).*(f11(:,2)));

% f11 + R1
x3 = k2*sum(xyz(:,2).*f11(:,2).*R1(:,2))
y3 = k2*sum(xyz(:,3).*f11(:,2).*R1(:,2))
z3 = k2*sum(xyz(:,4).*f11(:,2).*R1(:,2))

% f11 + R2
x4 = k2*sum(xyz(:,2).*f11(:,2).*R2(:,2));
y4 = k2*sum(xyz(:,3).*f11(:,2).*R2(:,2));
z4 = k2*sum(xyz(:,4).*f11(:,2).*R2(:,2));

%%
% D65 + R1
[r1,g1,b1] = xyz2rgb(x1,y1,z1)
% D65 + R2
[r2,g2,b2] = xyz2rgb(x2,y2,z2)
% f11 + R1
[r3,g3,b3] = xyz2rgb(x3,y3,z3)
% f11 + R2
[r4,g4,b4] = xyz2rgb(x4,y4,z4)

%%

x5 = k2*sum(xyz(:,2).*f11(:,2))
y5 = k2*sum(xyz(:,3).*f11(:,2))
z5 = k2*sum(xyz(:,4).*f11(:,2))

map=[r1 g1 b1; r2 g2 b2; r3 g3 b3; r4 g4 b4];
map=min(1,max(0,map));
image([1 2; 3 4])
colormap(map)

%% 2.2

[xp,yp,zp]=lab2xyz(93.45,1.15,-3.40)
[xc,yc,zc]=lab2xyz(71.23,-52.10,-30.73)
[xm,ym,zm]=lab2xyz(50.02,81.70,-12.63)
[xcm,ycm,zcm]=lab2xyz(28.74,20.63,-66.53)

[rp,gp,bp] = xyz2rgb(xp,yp,zp)
[rc,gc,bc] = xyz2rgb(xc,yc,zc)
[rm,gm,bm] = xyz2rgb(xm,ym,zm)
[rcm,gcm,bcm] = xyz2rgb(xcm,ycm,zcm)
[ron,gon,bon] = xyz2rgb(44,45,68)
[roff,goff,boff] = xyz2rgb(31.5,30.5,54.5)

map=[rp gp bp; rc gc bc; rm gm bm; rcm gcm bcm; ron gon bon; roff goff boff];
map=min(1,max(0,map));
image([1 2; 3 4; 5 6])
colormap(map)

%% 2.3

[C, M, Y, K] = tiffread('halftone');

[R, G, B] = cmyk2rgb(C, M, Y, K);
imshowrgb(R, G, B);
shgr(C)
figure, shgr(M)
figure, shgr(Y)
figure, shgr(K)

%% Test 1
C1=C(129:384,129:384);
M1=M(129:384,129:384);
Y1=Y(129:384,129:384);
K1=K(129:384,129:384);


T1p = sum(sum(~C1 & ~M1 & ~Y1 & ~K1))/256^2
T1c = sum(sum(C1 & ~M1 & ~Y1 & ~K1))/256^2
T1m = sum(sum(~C1 & M1 & ~Y1 & ~K1))/256^2
T1y = sum(sum(~C1 & ~M1 & Y1 & ~K1))/256^2
T1k = sum(sum(~C1 & ~M1 & ~Y1 & K1))/256^2
T1cm = sum(sum(C1 & M1 & ~Y1 & ~K1))/256^2
T1cy = sum(sum(C1 & ~M1 & Y1 & ~K1))/256^2
T1ck = sum(sum(C1 & ~M1 & ~Y1 & K1))/256^2
T1my = sum(sum(~C1 & M1 & Y1 & ~K1))/256^2
T1mk = sum(sum(~C1 & M1 & ~Y1 & K1))/256^2
T1yk = sum(sum(~C1 & ~M1 & Y1 & K1))/256^2
T1cmy = sum(sum(C1 & M1 & Y1 & ~K1))/256^2
T1cmk = sum(sum(C1 & M1 & ~Y1 & K1))/256^2
T1cyk = sum(sum(C1 & ~M1 & Y1 & K1))/256^2
T1myk = sum(sum(~C1 & M1 & Y1 & K1))/256^2
T1cmyk = sum(sum(C1 & M1 & Y1 & K1))/256^2


sum([T1p, T1c, T1m, T1y, T1k, T1cm, T1cy, T1ck, T1my, T1mk, T1yk, T1cmy, T1cmk, T1cyk, T1myk, T1cmyk])

%% Test 2

C1=C(139:394,139:394);
M1=M(129:384,129:384);
Y1=Y(109:364,109:364);
K1=K(129:384,129:384);


T1p = sum(sum(~C1 & ~M1 & ~Y1 & ~K1))/256^2
T1c = sum(sum(C1 & ~M1 & ~Y1 & ~K1))/256^2
T1m = sum(sum(~C1 & M1 & ~Y1 & ~K1))/256^2
T1y = sum(sum(~C1 & ~M1 & Y1 & ~K1))/256^2
T1k = sum(sum(~C1 & ~M1 & ~Y1 & K1))/256^2
T1cm = sum(sum(C1 & M1 & ~Y1 & ~K1))/256^2
T1cy = sum(sum(C1 & ~M1 & Y1 & ~K1))/256^2
T1ck = sum(sum(C1 & ~M1 & ~Y1 & K1))/256^2
T1my = sum(sum(~C1 & M1 & Y1 & ~K1))/256^2
T1mk = sum(sum(~C1 & M1 & ~Y1 & K1))/256^2
T1yk = sum(sum(~C1 & ~M1 & Y1 & K1))/256^2
T1cmy = sum(sum(C1 & M1 & Y1 & ~K1))/256^2
T1cmk = sum(sum(C1 & M1 & ~Y1 & K1))/256^2
T1cyk = sum(sum(C1 & ~M1 & Y1 & K1))/256^2
T1myk = sum(sum(~C1 & M1 & Y1 & K1))/256^2
T1cmyk = sum(sum(C1 & M1 & Y1 & K1))/256^2


sum([T1p, T1c, T1m, T1y, T1k, T1cm, T1cy, T1ck, T1my, T1mk, T1yk, T1cmy, T1cmk, T1cyk, T1myk, T1cmyk])

%% 2.4


[R, G, B]=tiffread('butterfly');
imshowrgb(R ,G, B)

[C, M, Y, K]=rgb2cmyk(R,G,B);
figure(1)
shgr(C)
figure(2)
shgr(M)
figure(3)
shgr(Y)
figure(4)
shgr(K)

%%
% Brightness
[L, a, b]=rgb2lab(R,G,B);
imshowrgb(R ,G, B)
figure
[R2, G2, B2]=lab2rgb(L+20, a, b);
imshowrgb(R2, G2, B2)
figure
[R3, G3, B3]=lab2rgb(L-20, a, b);
imshowrgb(R3, G3, B3)
% Contrast
figure
imshowrgb(R ,G, B)
figure
[R2, G2, B2]=lab2rgb((L-60)*2+60, a, b);
imshowrgb(R2, G2, B2)
figure
[R3, G3, B3]=lab2rgb((L-60)*0.8+60, a, b);
imshowrgb(R3, G3, B3)

%% Hue

imshowrgb(R ,G, B)
figure
[R2, G2, B2]=lab2rgb(L, 0, b);
imshowrgb(R2, G2, B2)
figure
[R3, G3, B3]=lab2rgb(L, -a, b);
imshowrgb(R3, G3, B3)

%% Saturation
imshowrgb(R ,G, B)
figure
[R2, G2, B2]=lab2rgb(L, 0.5*a, 0.5*b);
imshowrgb(R2, G2, B2)
figure
[R3, G3, B3]=lab2rgb(L, 3*a, 3*b);
imshowrgb(R3, G3, B3)

