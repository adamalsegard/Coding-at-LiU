function sfunction = Sharpness(FStack)
%TNM087Template General Template for TNM087 Lab Tasks
%   Everybody has to use this template
%
%% Who has done it
%
% Author: emiju987
% Co-author: adaal265
%
%% Syntax of the function
%
% Input arguments: In1, In2 are the input variables defined in the
%   lab-document
% Output arguments: Out1, Out2 output variables defined in the lab-document
%
% You MUST NEVER change the first line
%
%% Basic version control (in case you need more than one attempt)
%
% Version: 1
% Date: 14/12 - 2015
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

%% Size of images and number of images
%
[sx,sy,noimages] = size(FStack);

%% Generate a grid, convert the Euclidean to polar coordinates
%
ir = 1:sy; %index vector for pixels along first Matlab dimension
ic = 1:sx; %same in the second direction

cr = ir-sy/2; %find center
cc = ic-sx/2; 

[X, Y] = meshgrid(cr, cc);
[TH,R] = cart2pol(X, Y);

%% Number of COMPLETE rings in the Fourier domain 
% ignore the points in the corners

norings = 8; %Change this if you want
ImQ = zeros(sy, sx);

%this is the quantized version of R where the pixel value is the index of the ring 
% (origin = 0, and the point (0,r) has index norings
r = linspace(0, sx/2, norings);

RQ =  R < r(2);
ImQ(RQ) = 1;

for i = 2:norings
  RQ =  R < r(i) & R > r(i-1);
  ImQ(RQ) = i;
end

maxindex = max(ImQ(:)); 

%% Number of grid points in each ring

ptsperring = zeros(norings,1);
for ringno = 1:norings
    %RQ = ImQ <ringno+1 & ImQ >ringno-1;
    RQ = ImQ == ringno;
    ptsperring(ringno) =  sum(sum(RQ));
end

%% Sum of fft magnitude per image - per ring

absfftsums = zeros(noimages,maxindex);

for imno = 1:noimages
    padimage = padarray(FStack(:,:,imno), [2 2]); % Read about zero-padding / oklart ifall zero-pad behövs!?
    %padimage = FStack(:,:,imno);
    ftplan = fft2(padimage); % 2D fft
    cftplan = fftshift(ftplan); % move origin to the center
    
    for ringno = 1:norings
        %ringmask = ImQ <ringno+1 & ImQ >ringno-1; %this is a logical array defining the ring
        ringmask = ImQ == ringno;
        ringmask = padarray(ringmask, [2 2]);
        absfftsums(imno,ringno) = sum(abs(cftplan(ringmask)))/ptsperring(ringno); % average over Fourier magnitude in ring
    end
end
    
%% Compute weighted average over the ring sums

meanfreqcontent = zeros(noimages,1);

w = 1:norings;% here you may use the ring index, radius or something you define

for imno = 1:noimages
    meanfreqcontent(imno) = sum((w).*absfftsums(imno,w)); % combine w and absfftsums
end

%% Requested result
% default solution but you can invent something else if you want
sfunction = meanfreqcontent;

end

