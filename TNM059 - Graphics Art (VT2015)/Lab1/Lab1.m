%%
%1.1
a=5;
a/4
whos a

b= uint8(a);
b/4

whos b

%1.2
myimage1 = imread('S:\TN\M\TNM059\Lektion1\kvarn.tif', 'tif');
imshow(myimage1);


myimage2 = myimage1/255;


imshow(myimage2);
figure;
imshow(double(myimage2));



myimage3 = double(myimage1)/255;
imshow(myimage3);

%%
%2.1
imshow(myimage3/3);

%2.2 
%figure;
imagesc(myimage3/3);
colormap gray

%2.3
map=([1 0 0; 0 1 1; 0.5 0.2 0.3; 1 0 0.6]);
image([1, 2; 3, 4]);
colormap(map);
%figure;

map=([1 0 1; 0 1 0.2; 0.5 0.2 0.3; 1 0 0.6]);
image([1, 2; 3, 4]);
colormap(map);
%figure;

map=([1 0 1; 0 1 0.2; 0.5 0.2 0.3; 1 0 0.6]);
image([1, 2, 3, 4]);
colormap(map);
%figure;

map=([1 0 1; 0 1 0.2; 0.5 0.2 0.3; 1 0 0.6]);
image([1, 2]);
colormap(map);
%figure;

%2.3+
map=([1 1 0 ; 0 1 1; 0.3 0.3 0.3; 0.6 0.6 0.6]);
image([1, 2; 3 4]);
colormap(map);

%%
%3.1
v1 = [1 2 3 4 5];
%v1=1:5;
v2=[5 4 3 2 1];
%v2=5:-1:1;

%v=v1*v2
s1=v1*v2'
s2=v1'*v2
v=v1.*v2

s3=sum(v)

%3.2
x = 0:0.01:pi/2;
p = sin(x).*cos(x);
l1 = sum(p)
l1*0.01

x = 0:0.001:pi/2;
p = sin(x).*cos(x);
l2 = sum(p)
l2*0.001

%3.2+
x = 0:0.001:1;
p = (x./sqrt((x.^2)+1)).*sin(x);
l3 = sum(p)
l3*0.001

%%
%4.1

v = 1:10;

v(1:4)
v(1:2:4)
v(1:2:end)
v(1:3:end)
v(3:3:end)
v(:)

%4.2

myvector([1 3 4 5 6 8], 2, 2, 6)

myvector([1 3 4 5 6 8], 2, 2, 8)
myvector([1 3 4 5 6 8], 0, 2, 6)

%%
%4.3
myimage = imread('kvarn.tif');
myimage = double(myimage)/255;
myimage1 = myimage(1:2:end, 1:2:end);
imshow(myimage1)
figure;
imshow(myimage1(:))

myimage2 = myimage;
myimage2(:,100)= 1;
figure;
imshow(myimage2)


size(myimage)
size(myimage1)

%4.3+

myimage2 = myimage(1:3:end, 1:4:end);
imshow(myimage2)

%%
%5.1
Bild1 = imread('Butterfl.tif');
Bild1 = double(Bild1)/255;

red = Bild1(:,:,1); 

green = Bild1(:,:,2);

blue = Bild1(:,:,3);

imshow(red);
%figure;
imshow(green);
%figure;
imshow(blue);
%figure

%5.1+
mygrey = (Bild1(:,:,1)/3 + Bild1(:,:,2)/3 + Bild1(:,:,3)/3);
imshow(mygrey)

%%
%5.2
mygrey1 = mygrey(1:2:end, 1:2:end);
imshow(mygrey1)
figure

m = resize(mygrey);
imshow(m)
figure

m1 = imresize(mygrey1, 2);
imshow(m1)
figure

mygrey2 = imresize(m, 2, 'nearest');
mygrey3 = imresize(m, 2, 'bilinear');
mygrey4 = imresize(m, 2, 'bicubic');
imshow(mygrey2)
figure
imshow(mygrey3)
figure
imshow(mygrey4)


%%
%5.3
mycolorimage = imread('Butterfl.tif');
mycolorimage = double(mycolorimage)/255;
imshow(mycolorimage)
figure

bild53 = imresize(imresize(mycolorimage, 0.5, 'nearest'), 2, 'nearest');
imshow(bild53)

%%
%5.4a
Bild1 = imread('Butterfl.tif');
Bild1 = double(Bild1)/255;

red = Bild1(:,:,1); 
green = Bild1(:,:,2);
blue = Bild1(:,:,3);
B2 = blue(1:2:end, 1:2:end);
G2 = green(1:2:end, 1:2:end);
B2 = imresize(B2, 2, 'nearest');
G2 = imresize(G2, 2, 'nearest');

bild54a(:,:,1) = red;
bild54a(:,:,2) = G2;
bild54a(:,:,3) = B2;
imshow(bild54a)

%%
%5.4b
bild1 = red+green+blue;

bild2 = red-green;

bild3 = red+green-2*blue;

bild2 = bild2(1:2:end, 1:2:end);
bild3 = bild3(1:2:end, 1:2:end);
bild2 = imresize(bild2, 2, 'nearest');
bild3 = imresize(bild3, 2, 'nearest');
imshow(bild1)
figure
imshow(bild2)
figure
imshow(bild3)

%%
A = [1 1 1; 1 -1 0; 1 1 -2]; 
I = inv(A);

bild54b(:,:,1) = bild1/3 + bild2/2 + bild3/6;
bild54b(:,:,2) = bild1/3 - bild2/2 + bild3/6;
bild54b(:,:,3) = bild1/3 - bild3/3;

imshow(bild54b)
figure, imshow(bild53)
figure, imshow(bild54a)
figure, imshow(Bild1)