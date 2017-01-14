%% 1
R1 = ones(1,61);

XYZ1 = colorsignal2xyz(R1, CIEA);
[x1, y1] = XYZ2xy(XYZ1(1), XYZ1(2), XYZ1(3));
plot(x1, y1, '+ r');
hold on

XYZ2 = colorsignal2xyz(R1, CIEB);
[x2, y2] = XYZ2xy(XYZ2(1), XYZ2(2), XYZ2(3));
plot(x2, y2, '+ g');

XYZ3 = colorsignal2xyz(R1, CIED65);
[x3, y3] = XYZ2xy(XYZ3(1), XYZ3(2), XYZ3(3));
plot(x3, y3, '+ b');

XYZ4 = colorsignal2xyz(R1, Halogen75W);
[x4, y4] = XYZ2xy(XYZ4(1), XYZ4(2), XYZ4(3));
plot(x4, y4, 's r');

XYZ5 = colorsignal2xyz(R1, plank50k);
[x5, y5] = XYZ2xy(XYZ5(1), XYZ5(2), XYZ5(3));
plot(x5, y5, '* r');

XYZ6 = colorsignal2xyz(R1, plank65k);
[x6, y6] = XYZ2xy(XYZ6(1), XYZ6(2), XYZ6(3));
plot(x6, y6, '* g');

XYZ7 = colorsignal2xyz(R1, plank90k);
[x7, y7] = XYZ2xy(XYZ7(1), XYZ7(2), XYZ7(3));
plot(x7, y7, '* b');

XYZ8 = colorsignal2xyz(R1, Tungsten60W);
[x8, y8] = XYZ2xy(XYZ8(1), XYZ8(2), XYZ8(3));
plot(x8, y8, 's g');

%% 2

[r, g, b] = xyz2rgb(XYZ1(1), XYZ1(2), XYZ1(3));
RGB1 = [r, g, b];
[r, g, b] = xyz2rgb(XYZ2(1), XYZ2(2), XYZ2(3));
RGB2 = [r, g, b];
[r, g, b] = xyz2rgb(XYZ3(1), XYZ3(2), XYZ3(3));
RGB3 = [r, g, b];
[r, g, b] = xyz2rgb(XYZ4(1), XYZ4(2), XYZ4(3));
RGB4 = [r, g, b];
[r, g, b] = xyz2rgb(XYZ5(1), XYZ5(2), XYZ5(3));
RGB5 = [r, g, b];
[r, g, b] = xyz2rgb(XYZ6(1), XYZ6(2), XYZ6(3));
RGB6 = [r, g, b];
[r, g, b] = xyz2rgb(XYZ7(1), XYZ7(2), XYZ7(3));
RGB7 = [r, g, b];
[r, g, b] = xyz2rgb(XYZ8(1), XYZ8(2), XYZ8(3));
RGB8 = [r, g, b];

RGB = [RGB1; RGB2; RGB3; RGB4; RGB5; RGB6; RGB7; RGB8];
showRGB(RGB);

%% 4

plot(waverange, CIEA, 'r');
hold on
plot(waverange, CIEB, 'g');
plot(waverange, CIED65, 'b');
plot(waverange, Halogen75W, 'y');
plot(waverange, plank50k, 'c');
plot(waverange, plank65k, 'm');
plot(waverange, plank90k, 'k');
plot(waverange, Tungsten60W, 'k:');

%% 5


for x = 1:20
    XYZ1(x, :) = colorsignal2xyz(chips20(x, :), CIEB);
    [r, g, b] = xyz2rgb(XYZ1(x, 1), XYZ1(x, 2), XYZ1(x, 3));
    RGB11(x, :) = [r, g, b];
    RGB(x, :) = RGB11(x, :);
end

showRGB(RGB)

for x = 1:20
    XYZ2(x, :) = colorsignal2xyz(chips20(x, :), plank90k);
    [r, g, b] = xyz2rgb(XYZ2(x, 1), XYZ2(x, 2), XYZ2(x, 3));
    RGB22(x, :) = [r, g, b];
    RGB(x, :) = RGB22(x, :);
end
%figure
showRGB(RGB)

for x = 1:20
    XYZ3(x, :) = colorsignal2xyz(chips20(x, :), Tungsten60W);
    [r, g, b] = xyz2rgb(XYZ3(x, 1), XYZ3(x, 2), XYZ3(x, 3));
    RGB33(x, :) = [r, g, b];
    RGB(x, :) = RGB33(x, :);
end
%figure
showRGB(RGB)


%% 6a
XYZ2 = colorsignal2xyz(R1, CIEB);
XYZ7 = colorsignal2xyz(R1, plank90k);
XYZ8 = colorsignal2xyz(R1, Tungsten60W);
plot3(XYZ2(1), XYZ2(2), XYZ2(3), 'k +');
hold on
plot3(XYZ7(1), XYZ7(2), XYZ7(3), 'r *');
plot3(XYZ8(1), XYZ8(2), XYZ8(3), 'b x');


%% 6b
for x = 1:20
    plot3(XYZ1(x, 1), XYZ1(x, 2), XYZ1(x, 3), '+ k');
    hold on
    plot3(XYZ2(x, 1), XYZ2(x, 2), XYZ2(x, 3), '* r');
    plot3(XYZ3(x, 1), XYZ3(x, 2), XYZ3(x, 3), 'x b' );
end

%% 7a

XYZ22 = colorsignal2xyz(R1, CIEB);
XYZ77 = colorsignal2xyz(R1, plank90k);
XYZ88 = colorsignal2xyz(R1, Tungsten60W);
Lab1 = xyz2lab(XYZ22, XYZ22);
Lab2 = xyz2lab(XYZ77, XYZ77);
Lab3 = xyz2lab(XYZ88, XYZ88);

plot3(Lab1(1), Lab1(2), Lab1(3), 'k +');
hold on
plot3(Lab2(1), Lab2(2), Lab2(3), 'r *');
plot3(Lab3(1), Lab3(2), Lab3(3), 'b x');

%% 7b
XYZ22 = colorsignal2xyz(R1, CIEB);
XYZ77 = colorsignal2xyz(R1, plank90k);
XYZ88 = colorsignal2xyz(R1, Tungsten60W);

for x = 1:20
    Lab11(x, :) = xyz2lab(XYZ1(x,:), XYZ22);
    Lab22(x, :) = xyz2lab(XYZ2(x,:), XYZ77);
    Lab33(x, :) = xyz2lab(XYZ3(x,:), XYZ88);
end



for x = 1:20
    plot3(Lab11(x, 1), Lab11(x, 2), Lab11(x, 3), '+ k');
    hold on
    plot3(Lab22(x, 1), Lab22(x, 2), Lab22(x, 3), '* r');
    plot3(Lab33(x, 1), Lab33(x, 2), Lab33(x, 3), 'x b' );
end


