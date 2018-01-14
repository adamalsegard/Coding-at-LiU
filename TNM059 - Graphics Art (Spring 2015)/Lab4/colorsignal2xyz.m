function [ XYZ ] = colorsignal2xyz( R, I )
% XYZ=colorsignal2xyz(reflectance,illumination)
%
% R = reflectance = Reflektansspektra (1x61)
% I = illumination = Belysningens spektralf�rdelning (1x61)
% XYZ = CIEXYZ-v�rden
%
% Reflektansspektra multipliceras med belysningens spektralf�rdelning
% och �vers�tts sedan med hj�lp av CIE:s standardobservat�r till
% CIEXYZ-v�rden. Observat�ren �terfinns i filen "xyz.mat". Gl�m inte
% att ber�kna k-v�rdet f�r belysningen och skala CIEXYZ-v�rdena med
% erh�llet k-v�rde! (Formler f�r detta �terfinns i laboration 3)
%
% Om CIEXYZ-v�rden ska ber�knas f�r en belysning s� kan
% reflektanspektrat ers�ttas med ettor (full reflektans i alla
% v�gl�ngder).
% Ex: reflectance = ones(1,61);

%x = [0.49 0.31 0.20];
%y = [0.17697 0.81240 0.01063];
%z = [0 0.01 0.99];
%load('H:\MATLAB\TNM059\Lab4\xyz.mat');

x = xyz(:,1);
y = xyz(:,2);
z = xyz(:,3);

k = 100/(sum(I.*y'));

X = k*sum(I.*R.*x');
Y = k*sum(I.*R.*y');
Z = k*sum(I.*R.*z');


XYZ = [X Y Z];


end

