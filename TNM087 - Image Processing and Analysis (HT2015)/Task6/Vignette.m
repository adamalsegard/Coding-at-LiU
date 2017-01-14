function [ Profile1, Profile2 ] = Vignette( Im1, Im2, norings )
%%Vignette: Compare vignetting properties of two images
%   If Im1 and Im2 show the same object imaged under different conditions
%   then Profile1 and Profile2 describe the mean gray value as a function
%   of the radius
%
%% Who has done it
%
% Author: adaal265
% Co-author: emiju987

%% Syntax of the function
%
% Input arguments:  Im1, Im2 are input images, you can assume that they are
%                       gray value images (of type uint8, uint16 or double)
%                   norings is optional and describes the number of
%                       concentric rings to use. The default is to use 50 rings
% Output arguments: Profile1 and Profile2 are vectors with the mean gray
%                       values in each ring. The final results are normed
%                       so that the maximum values in Profile1 and Profile2
%                       are equal to one
%
% You MUST NEVER change the first line
%
%% Basic version control (in case you need more than one attempt)
%
% Version: 1
% Date: 2015-11-30
%
% Gives a history of your submission to Lisam.
% Version and date for this function have to be updated before each
% submission to Lisam (in case you need more than one attempt)
%
%% General rules
%
% 1) Don't change the structure of the template by removing %% lines
%
% 2) Document what you are doing using comments
%
% 3) Before submitting make the code readable by using automatic indentation
%       ctrl-a / ctrl-i
%
% 4) In case a task requires that you have to submit more than one function
%       save every function in a single file and collect all of them in a
%       zip-archive and upload that to Lisam. NO RAR, NO GZ, ONLY ZIP!
%       All non-zip archives will be rejected automatically
%
% 5) Often you must do something else between the given commands in the
%       template
%
%

%% Your code starts here
%

%% Input parameters
%

if nargin < 3
    norings = 50;
end

%% Generate two square images cIm1 and cIm2 that have the same size
% Use the center of the images and if at least one of them is an RGB image
% either convert to gray value or exit with an error message
%
[sr1, sc1, nc1] = size(Im1);
[sr2, sc2, nc2] = size(Im2);

if sr1 ~= sc1
    Im1 = Im1(round(sr1/2 - min(sr1,sc1)/2)+1  : round(sr1/2 + min(sr1,sc1)/2), round(sc1/2 - min(sr1,sc1)/2 )+1 : round(sc1/2 + min(sr1,sc1)/2), :);
end

if sr2 ~= sc2
    Im2 = Im2(round(sr2/2 - min(sr2,sc2)/2 )+1 :round( sr2/2 + min(sr2,sc2)/2),round( sc2/2 - min(sr2,sc2)/2)+1  : round(sc2/2 + min(sr2,sc2)/2), :);
end

if min(sr1,sc1) < min(sr2,sc2)
    Im2 = Im2(round(min(sr2,sc2)/2 - min(sr1,sc1)/2)+1 : round(min(sr2,sc2)/2 + min(sr1,sc1)/2), round(min(sr2,sc2)/2 - min(sr1,sc1)/2)+1  : round(min(sr2,sc2)/2 + min(sr1,sc1)/2), :);
elseif min(sr1,sc1) > min(sr2,sc2)
    Im1 = Im1(round(min(sr1,sc1)/2 - min(sr2,sc2)/2)+1  : round(min(sr1,sc1)/2 + min(sr2,sc2)/2), round(min(sr1,sc1)/2 - min(sr2,sc2)/2)+1  : round(min(sr1,sc1)/2 + min(sr2,sc2)/2), :);
end


if (nc1 > 1)
    Im1 = rgb2gray(Im1);
end

if (nc2 > 1)
    Im2 = rgb2gray(Im2);
end

%%
Profile1 = zeros(norings,1);
Profile2 = Profile1;

%% Now you have two gray value images of the size (square) size and you
%   generate grid with the help of an axis vector ax that defines your
%   rings
%

ax = ( 1:length(Im1(1,:))/(norings*2):length(Im1(1,:))/2);
% or read the documentation of linspace
%ax = linspace
%...

[C R] = meshgrid(1:size(Im1,1),1:size(Im1,2)); %Euclidean mesh
D =sqrt( (C-size(Im1,1)/2).^2 + (R-size(Im1,2)/2).^2 );
%D(D>size(Im1,1)/2) = 0;

%[~,Rho] = cart2pol(R-size(Im1,1)/2, C-size(Im1,2)/2 ); %Polar coordinates comment on the ~ used

%% Do the actual calculations
RMask = uint8( zeros(size(Im1,1),size(Im1,2)) );
for ringno = 1:norings
    RMask(D<ax(ringno)) = 1;    % Generate a mask describing the ring number ringno
    nopixels = sum(sum(RMask));% Compute the number of pixes in RMask
    pixsum = sum(sum(RMask.*Im1)); % Compute the sum over all pixel values in RMask in Im1
    Profile1(ringno) = pixsum/nopixels;% ../.. Mean gray value of pixels i RMask
    % ... and now you do it for the second images
    pixsum = sum(sum(RMask.*Im2));
    Profile2(ringno) = pixsum/nopixels;
end

% Finally the normalization to max value one
%

Profile1 = Profile1/max(max(Profile1,Profile2));
Profile2 = Profile2/max(max(Profile1,Profile2));

%plot(Profile1), figure, plot(Profile2);

%% Extra question: How can you find out if Im1 is better than Im2?

end


