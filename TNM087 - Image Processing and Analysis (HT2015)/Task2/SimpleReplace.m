function figh = SimpleReplace(filename, rows, cols, box )
%SimpleReplace Change pixel values in simple image regions
%   Change pixel values in selected rows, columns and a box
%
%% Who has done it
%
% Author: emiju987
% Co-author: adaal265
%
%% Syntax of the function
%
% Input arguments:  filename: pathname to the image file
%                   rows: vector of row indices
%                   cols: vector of column indices
%                   box: vector with four elements [sr,sc,size1,size2]
%                       where (sr,sc) are coordinates of box origin
%                       (size1, size2) is the size of the box
%                       origin and size use row/column convention
%
% Output argument:  figh: handle to the figure displaying the new image
%
% You MUST NEVER change the first line
%
%% Basic version control (in case you need more than one attempt)
%
% Version: 2
% Date: 27/11 - 2015
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

%% create figure and read image
%
figh = figure;
Oimage = imread (filename);

%% Copy image and edit
%
Nimage = im2uint8(Oimage);

% change rows
Nimage(rows, :, 1) = 255;

% change cols
Nimage(:, cols, 2) = 255;

% change box
Nimage(box(1):box(1)+box(3), box(2):box(2)+box(4), :) = 0;

% change grid points
rad = 1:length(rows);
R = zeros(1,length(Nimage(:,1,1)));
R(rows(rad)) = 1;

kol = 1:length(cols);
C = zeros(1,length(Nimage(1,:,1)));
C(cols(kol)) = 1;

M = uint8(R'*C);

% Would be enough to just change the blue channel
Nimage(:,:,1) = Nimage(:,:,1) + M*255;
Nimage(:,:,2) = Nimage(:,:,2) + M*255;
Nimage(:,:,3) = Nimage(:,:,3) + M*255;

% Display result
imshow(Nimage);

end

