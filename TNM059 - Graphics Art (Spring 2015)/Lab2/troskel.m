function out=troskel(in,tr)

% ***************************************************
% out=troskel(in,tr)
%
% "in" är originalbilden.
% "out" är den rastrerade bilden.
% "tr" är tröskelmatrisen.
% "troskel" tröskelrastrerar originalbilden med 
% tröskelmatrisen "tr".
% ***************************************************

[rin,cin]=size(in);
[rtr,ctr]=size(tr);

M=ceil(rin/rtr);
N=ceil(cin/ctr);
TR=repmat(tr,M,N);
TR=TR(1:rin,1:cin);  
  out= in >= TR;