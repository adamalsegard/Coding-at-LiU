function out=tabellrast(in)

% **************************************************************
% out=tabellrast(in)
%
% "in" är originalbilden.
% "out" är den rastrerade bilden.
% "tabellrast" är en enkel funktion som tabellrastrerar
% inbilden. Medelvärdet (summan) av varje 3 x 3 omgivning i 
% inbilden beräknas och beroende på detta värde väljs en 
% uppsättning av punkter som ska fylla motsvarande 3 x 3 region 
% i utbilden.
% **************************************************************

a(:,:,1)=zeros(3,3);

a(:,:,2)=[0 0 0;
          0 1 0;
          0 0 0];
 
 a(:,:,3)=[0 0 0;
           1 1 0;
           0 0 0];
  
  a(:,:,4)=[1 0 0;
            1 1 0;
            0 0 0];
   
  a(:,:,5)=[1 1 0;
            1 1 0;
            0 0 0];
   
  a(:,:,6)=[1 1 1;
            1 1 0;
            0 0 0];
    
  a(:,:,7)=[1 1 1;
            1 1 1;
            0 0 0];
   
  a(:,:,8)=[1 1 1;
            1 1 1;
            0 0 1];
   
  a(:,:,9)=[1 1 1;
           1 1 1;
           0 1 1];
   
  a(:,:,10)=ones(3,3);
  
  [nr,nc]=size(in);
  
  if rem(nr,3)==1 in1=zeros(nr+1,nc+1); end;
  if rem(nr,3)==2 in1=zeros(nr+2,nc+2); end;
  
  in1(1:nr,1:nc)=in;
  [nr1,nc1]=size(in1);
  
  out=zeros(nr1,nc1);
  
  for i=1:3:nr1-3
     for j=1:3:nc1-3
        s=round(sum(sum(in1(i:i+2,j:j+2))));
        out(i:i+2,j:j+2)=a(:,:,s+1);
     end;
  end;
  
  out=out(1:nr,1:nc);
  
   