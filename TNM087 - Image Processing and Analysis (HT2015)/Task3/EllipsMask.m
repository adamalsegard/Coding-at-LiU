function MImage = EllipsMask(FImage)
%EllipsMask Generate a mask for one eye and the complete face
%   Change pixel color for one eye and extract the face
%
%% Who has done it
%
% Author: emiju987
% Co-author: adaal265
%
%% Syntax of the function
%
% Input arguments:  Fimage: Image containing a face
%
% Output argument:  Mimage: Image with elliptical mask and a red eye
%
% You MUST NEVER change the first line
%
%% Basic version control (in case you need more than one attempt)
%
% Version: 2
% Date: 23/11 - 2015
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

%% create the output image (RGB!) which is a copy of the original image
% Use einstein.jpg as your FImage

[sr,sc] = size(FImage);
MImage = cat(3, FImage, FImage, FImage);

%% Generate the coordinates of the grid points
[C R] = meshgrid((1:sc),(1:sr));
% Remember the matlab convention regarding rows, columns, x and y coordinates. Feel free to use
% [Y,X] = meshgrid((1:sx),(1:sy)) or whatever notation instead if you feel more comfortable with that notation



%% Pick three points that define the elliptical mask of the face
% Read more about ellipses at https://en.wikipedia.org/wiki/Ellipse
% Your solution must at least be able to solve the problem for the case
% where the axes of the ellipse are parallel to the coordinate axes
%

imshow(FImage);
fpts = ginput(3);
close

%% Generate the elliptical mask and
% set all points in MImage outside the mask to black
rows = R(round(fpts(:,2)),1)';
columns = C(1,round(fpts(:,1)));

centerpoint = [(rows(1)+rows(2))/2, (columns(1)+columns(2))/2];

a = abs(centerpoint(1)-rows(1));
b = abs(centerpoint(2)-columns(3));

C1 = abs(C - centerpoint(2));
R1 = abs(R - centerpoint(1));

fmask = (C1/b).^2 + (R1/a).^2;
fmask(fmask<1) = 1;
fmask(fmask>1) = 0;
fmask = uint8(fmask);

MImage(:,:,1) = MImage(:,:,1).*fmask;
MImage(:,:,2) = MImage(:,:,2).*fmask;
MImage(:,:,3) = MImage(:,:,3).*fmask;


%% Pick two points defining one eye, generate the eyemask, paint it red

imshow(MImage);
epts = ginput(2);

%%
center = [epts(1,2), epts(1,1)];
d = (epts(1,1)-epts(2,1))^2 + (epts(1,2)-epts(2,2))^2 ;

C1 = abs(C - center(2));
R1 = abs(R - center(1));

emask = (C1).^2 + (R1).^2;
emask(emask<d) = 1;
emask(emask>d) = 0;
emask = uint8(emask);

MImage(:,:,1) = MImage(:,:,1).*(1-emask) + emask*255;
MImage(:,:,2) = MImage(:,:,2).*(1-emask);
MImage(:,:,3) = MImage(:,:,3).*(1-emask);



%% Display result if you want
%
imshow(MImage);

end

