%1.
a = [1 2 3 4 5]

%2.
a+2

%3.
A = [1 2 3; 4 5 6; 7 8 9]

%4.
B = rand(3, 3)

%%
%5.
C = A*B
c= mtimes(A, B)


%6.
D = A.*B
d = times(A, B)

%%
%7.
E = zeros(3)
F = ones(3)

%8.
A+2

%9.
A(2,3)

%10.
G = [1 2 3];

G + A(1, :)

%%
%11.
A = [1 1 1 1 1; 2 2 2 2 2; 3 3 3 3 3;
    4 4 4 4 4; 5 5 5 5 5]
B = A(1:2,1:3)

%12.
C = A>=3

%13.
c = sum(sum(A))
d = sum(A)

%14.
mean(mean(A))
mean(A)

%15.
A3(:,:,1) = A;
A3(:,:,2) = A+1;
A3(:,:,3) = A+2;
A3

%16.
A3(:,:,2)

%17.

B3 = ones(size(A3)) 

%%
% 3.0 Enkla bildoperationer
%1
Bild1 = imread('S:\TN\M\TNM059\Lektion1\kvarn.tif', 'tif');

%2
Bild1 = double(Bild1);
m = max(max(Bild1));
Bild1 = Bild1/m;
Bild1

%%
%3.
size(Bild1)

%4.
mean(mean(Bild1))

%5.
imshow(Bild1)

%6.
imwrite(Bild1, 'NyBild.tif');
%%
%7.
med = ones(3)/9;
Bild2 = filter2(med, Bild1);
fighandle = figure;
imshow(Bild2)


%8.
hold on
subplot(1, 2, 1);
imshow(Bild1)

subplot(1, 2, 2);
imshow(Bild2)
hold off

%9.
truesize(fighandle, [512 512]);

%10.
close(fighandle);

%%
%11.
Bild3 = imread('S:\TN\M\TNM059\Lektion1\musicians.tif', 'tif');
red = Bild3(:,:,1); % Red channel
green = Bild3(:,:,2); % Green channel
blue = Bild3(:,:,3); % Blue channel

a = zeros(size(Bild3, 1),size(Bild3, 2));
just_red = cat(3, red, a, a);
just_green = cat(3, a, green, a);
just_blue = cat(3, a, a, blue);
back_to_original_img = cat(3, red, green, blue);


%12.
hold on
figure, imshow(Bild3), title('Original image')
figure, imshow(just_red), title('Red channel')
figure, imshow(just_green), title('Green channel')
figure, imshow(just_blue), title('Blue channel')
figure, imshow(back_to_original_img), title('Back to original image')
hold off

%% 4.0 Att skriva egna funktioner i Matlab
%1
A = [1 2 3; 5 6 7; 3 -8 1];
B = [1; 2; 3];
I = inv(A);
Y = I*A

a = I*B
b = kryssa(A, B)
c = A\B

