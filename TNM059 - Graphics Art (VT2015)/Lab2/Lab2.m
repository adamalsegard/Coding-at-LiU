
Bild = imread('kvarn.tif'); 
imshow(Bild)
Bild = double(Bild)/255;

out1=Bild>=0.5;
imshow(out1);


%%
%1.2/3
load('H:\MATLAB\Lab2\troskelmatriser.mat');
tr1 = tr1/19;
tr2 = tr2/33;
tr3 = tr3/33;

B1 = troskel(Bild, tr1);
B2 = troskel(Bild, tr2);
B3 = troskel(Bild, tr3);

imshow(B1);
figure, imshow(B2);
figure, imshow(B3);

%%
%1.4

LRH = [1 2 3 4; 5 6 7 8; 
        1 2 3 4; 5 6 7 8];
LRH = LRH/9;

LRV = LRH';
SR = [ 7 8 9 10;
       6 1 2 11;
       5 4 3 12;
       16 15 14 13];
SR = SR/17;
TRS = rand(4);

I1 = troskel(Bild, LRH);
I2 = troskel(Bild, LRV);
I3 = troskel(Bild, SR);
I4 = troskel(Bild, TRS);
   
imshow(I1);
figure, imshow(I2);
figure, imshow(I3);
figure, imshow(I4);

%%
%2.1

out2 = tabellrast(Bild);
figure 
imshow(out2);

%%
%3.1
Floyd = [0 0 7; 3 5 1]/16;

out3 = errordif(Bild, Floyd);
figure
imshow(out3);

%3.2
Ninke = [0 0 0 7 5;
         3 5 7 5 3;
         1 3 5 3 1]/48;
out4 = errordif(Bild, Ninke);
figure
imshow(out4);

%3.3
Sasan = [0 0 0 0.841 -0.171;
         0.247 0.459 0.344 0.071 -0.164;
         -0.415 -0.218 -0.172 -0.145 0.001;
         0.137 0.101 0.008 -0.028 0.104];
out4 = errordif(Bild, Sasan);
figure
imshow(out4);
%%
%3.4
filt1 = [0 0 3;
         0 2 5]/10;
filt2 = [0 0 1;
         0 0 0];
filt3 = [0 0 0.3;
         0.7 0 0];
     
out5 = errordif(Bild, filt1);
figure
imshow(out5)
out6 = errordif(Bild, filt2);
figure
imshow(out6);
out7 = errordif(Bild, filt3);
figure
imshow(out7);
%%
%3.5
Floyd = [0 0 7; 3 5 1]/16;
out3 = errordif(Bild, Floyd);
imshow(out3);

Brus = (rand(512)-0.5)/6;
Bild2 = Bild+Brus;
out8 = errordif(Bild2, Floyd);
figure
imshow(out8);

%%
%4

out9 = imcdp(Bild);
figure
imshow(out9);

%%
%5

Color = imread('musicians.tif');
imshow(Color);
Color = double(Color)/255;
%%
Ny = CRast(Color, Floyd, 1);
figure
imshow(Ny);

