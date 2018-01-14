function out=imcdp(inak)

%*********************************************************************
% out = imcdp (in)
%
% The code for "Iterative Method Controlling Dot Placement (IMCDP)"
%
% "in" is the original image and "out" is the resulting halftoned image.
%
% by: Sasan Gooran
%*********************************************************************

disp('imcdp');
disp('----------');
flag=0;
r=1;
filt=kern1(5,1.3);
%	if (mean(mean(inak))>0.5)
 %  in=1-inak;
 %  flag=1;
 %	end;
 
[nor noc]=size(inak);
%filt=kern1(5,1.3);
%filt=1;
big=wrap2(inak,20);
result=conv2(big,filt,'same');
in=result(21:nor+20,21:noc+20);

% 	Number of points to be placed.

sizn=10;

s=5;
inn=wrap2(in,s);

[nr,nc]=size(inn);
%***
%[nr,nc]=size(in);
%***
nr1=nr+2*sizn;
nc1=nc+2*sizn;

out=zeros(nr1,nc1);

in1=-100*ones(nr1,nc1);
if r==0
   n=0;
else
   r=rand(size(inn));
   n=0.001*(r-0.5);
end;


in1(1+sizn:nr+sizn,1+sizn:nc+sizn)=inn+n;
[S,I]=max(in1);
[SM,cc]=max(S);
rr=I(cc);
i=0;

mx=1;
in2=zeros(size(in1));
in2(1+sizn+s:nr1-sizn-s,1+sizn+s:nc1-sizn-s)=inak;

%mx=max(max(inak));

mask2=zeros(nr1,nc1);
flag2=1;
mask2(1+sizn+s:nr1-sizn-s,1+sizn+s:nc1-sizn-s)=(inak>=0.8*mx & inak<0.9*mx);
ii2=round(sum(sum(in2.*mask2)));

mask3=zeros(nr1,nc1);
flag3=1;
mask3(1+sizn+s:nr1-sizn-s,1+sizn+s:nc1-sizn-s)=(inak>=0.7*mx & inak<0.8*mx);
ii3=round(sum(sum(in2.*mask3)));

mask4=zeros(nr1,nc1);
flag4=1;
mask4(1+sizn+s:nr1-sizn-s,1+sizn+s:nc1-sizn-s)=(inak>=0.6*mx & inak<0.7*mx);
ii4=round(sum(sum(in2.*mask4)));

mask5=zeros(nr1,nc1);
flag5=1;
mask5(1+sizn+s:nr1-sizn-s,1+sizn+s:nc1-sizn-s)=(inak>=0.5*mx & inak<0.6*mx);
ii5=round(sum(sum(in2.*mask5)));

mask6=zeros(nr1,nc1);
flag6=1;
mask6(1+sizn+s:nr1-sizn-s,1+sizn+s:nc1-sizn-s)=(inak>=0.4*mx & inak<0.5*mx);
ii6=round(sum(sum(in2.*mask6)));

mask7=zeros(nr1,nc1);
flag7=1;
mask7(1+sizn+s:nr1-sizn-s,1+sizn+s:nc1-sizn-s)=(inak>=0.3*mx & inak<0.4*mx);
ii7=round(sum(sum(in2.*mask7)));


mask8=zeros(nr1,nc1);
flag8=1;
mask8(1+sizn+s:nr1-sizn-s,1+sizn+s:nc1-sizn-s)=(inak>=0.2*mx & inak<0.3*mx);
ii8=round(sum(sum(in2.*mask8)));

mask9=zeros(nr1,nc1);
flag9=1;
mask9(1+sizn+s:nr1-sizn-s,1+sizn+s:nc1-sizn-s)=(inak>=0.1*mx & inak<0.2*mx);
ii9=round(sum(sum(in2.*mask9)));


mask10=zeros(nr1,nc1);
flag10=1;
mask10(1+sizn+s:nr1-sizn-s,1+sizn+s:nc1-sizn-s)=(inak>=0.06*mx & inak<0.1*mx);
ii10=round(sum(sum(in2.*mask10)));

mask11=zeros(nr1,nc1);
flag11=1;
mask11(1+sizn+s:nr1-sizn-s,1+sizn+s:nc1-sizn-s)=(inak>=0.04*mx & inak<0.06*mx);
ii11=round(sum(sum(in2.*mask11)));

mask12=zeros(nr1,nc1);
flag12=1;
mask12(1+sizn+s:nr1-sizn-s,1+sizn+s:nc1-sizn-s)=(inak>=0.03*mx & inak<0.04*mx);
ii12=round(sum(sum(in2.*mask12)));

mask13=zeros(nr1,nc1);
flag13=1;
mask13(1+sizn+s:nr1-sizn-s,1+sizn+s:nc1-sizn-s)=(inak>=0.02*mx & inak<0.03*mx);
ii13=round(sum(sum(in2.*mask13)));

mask14=zeros(nr1,nc1);
flag14=1;
mask14(1+sizn+s:nr1-sizn-s,1+sizn+s:nc1-sizn-s)=(inak>=0.01*mx & inak<0.02*mx);
ii14=round(sum(sum(in2.*mask14)));

mask1=zeros(nr1,nc1);
flag1=1;
mask1(1+sizn+s:nr1-sizn-s,1+sizn+s:nc1-sizn-s)=(inak>=0.98*mx);
ii1=round(sum(sum(in2.*mask1)));

mask15=zeros(nr1,nc1);
flag15=1;
mask15(1+sizn+s:nr1-sizn-s,1+sizn+s:nc1-sizn-s)=(inak>=0.97*mx & inak<0.98*mx);
ii15=round(sum(sum(in2.*mask15)));

mask16=zeros(nr1,nc1);
flag16=1;
mask16(1+sizn+s:nr1-sizn-s,1+sizn+s:nc1-sizn-s)=(inak>=0.96*mx & inak<0.97*mx);
ii16=round(sum(sum(in2.*mask16)));

mask17=zeros(nr1,nc1);
flag17=1;
mask17(1+sizn+s:nr1-sizn-s,1+sizn+s:nc1-sizn-s)=(inak>=0.94*mx & inak<0.96*mx);
ii17=round(sum(sum(in2.*mask17)));

mask18=zeros(nr1,nc1);
flag18=1;
mask18(1+sizn+s:nr1-sizn-s,1+sizn+s:nc1-sizn-s)=(inak>=0.9*mx & inak<0.94*mx);
ii18=round(sum(sum(in2.*mask18)));

mask19=zeros(nr1,nc1);
flag19=1;
mask19(1+sizn+s:nr1-sizn-s,1+sizn+s:nc1-sizn-s)=(inak>0 & inak<0.01*mx);
ii19=round(sum(sum(in2.*mask19)));

mask20(1+sizn+s:nr1-sizn-s,1+sizn+s:nc1-sizn-s)=(inak==0);
in1(1+sizn+s:nr1-sizn-s,1+sizn+s:nc1-sizn-s)=in1(1+sizn+s:nr1-sizn-s,1+sizn+s:nc1-sizn-s).*(1-mask20(1+sizn+s:nr1-sizn-s,1+sizn+s:nc1-sizn-s))-1000*mask20(1+sizn+s:nr1-sizn-s,1+sizn+s:nc1-sizn-s);

insum=ii1+ii2+ii3+ii4+ii5+ii6+ii7+ii8+ii9+ii10+ii11+ii12+ii13+ii14+ii15+ii16+ii17+ii18+ii19;


jj1=0;
jj2=0;
jj3=0;
jj4=0;
jj5=0;
jj6=0;
jj7=0;
jj8=0;
jj9=0;
jj10=0;
jj11=0;
jj12=0;
jj13=0;
jj14=0;
jj15=0;
jj16=0;
jj17=0;
jj18=0;
jj19=0;
while (i < insum)
   %dis=kern1(siz,1.3);
     if ((rr>s+sizn) & (rr<=nr1-s-sizn) & (cc>s+sizn) & (cc<=nc1-s-sizn))
        i=i+1; out(rr,cc)=1;
                
        %if (rr<=2*sizn)
        if (in1(rr,cc) <=-500)
          disp('ajab ajab');
           end;
         %  dis(2*siz-rr+1:-1:1,:)=0;
         %  dis=dis/sum(sum(dis));
           
           
        %end;     
     end;
     
     %if ((in1(rr,cc)>=0.9 & in1(rr,cc)<=1) | ( in1(rr,cc)<0.1))
      %  siz=10;
       % sigma=3;
     %else
        siz=5;
        sigma=1.3;
        %  end;
                
                
		
             
     
hh=1;

      if (flag1==1)
        if (mask1(rr,cc)==1)
           jj1=jj1+1;
           if (in1(rr,cc)>=0.98)
           		siz=10;
              	sigma=3;
            end;
        end;
        
        %jj=sum(sum(out(1+siz+s:nr1-siz-s,1+siz+s:nc1-siz-s).*mask1));
        if (jj1>=ii1)
           disp('here1');
           in1(1+sizn+s:nr1-sizn-s,1+sizn+s:nc1-sizn-s)=in1(1+sizn+s:nr1-sizn-s,1+sizn+s:nc1-sizn-s).*(1-mask1(1+sizn+s:nr1-sizn-s,1+sizn+s:nc1-sizn-s))-1000*mask1(1+sizn+s:nr1-sizn-s,1+sizn+s:nc1-sizn-s);
           flag1=2;
           hh=2;
        end;
     end;
     
     
     if (flag15==1)
        if (mask15(rr,cc)==1)
           jj15=jj15+1;
           if(in1(rr,cc)>=0.97)
           		siz=9;
              sigma=2.7;
              end;
              
        end;
        
        %jj=sum(sum(out(1+siz+s:nr1-siz-s,1+siz+s:nc1-siz-s).*mask1));
        if (jj15>=ii15)
           disp('here15');
           in1(1+sizn+s:nr1-sizn-s,1+sizn+s:nc1-sizn-s)=in1(1+sizn+s:nr1-sizn-s,1+sizn+s:nc1-sizn-s).*(1-mask15(1+sizn+s:nr1-sizn-s,1+sizn+s:nc1-sizn-s))-1000*mask15(1+sizn+s:nr1-sizn-s,1+sizn+s:nc1-sizn-s);
           flag15=2;
           hh=2;
        end;
     end;
     
     if (flag16==1)
        if (mask16(rr,cc)==1)
           jj16=jj16+1;
           if (in1(rr,cc)>=0.96)
           	siz=8;
              sigma=2.3;
           end;
           
              
        end;
        
        %jj=sum(sum(out(1+siz+s:nr1-siz-s,1+siz+s:nc1-siz-s).*mask1));
        if (jj16>=ii16)
           disp('here16');
           in1(1+sizn+s:nr1-sizn-s,1+sizn+s:nc1-sizn-s)=in1(1+sizn+s:nr1-sizn-s,1+sizn+s:nc1-sizn-s).*(1-mask16(1+sizn+s:nr1-sizn-s,1+sizn+s:nc1-sizn-s))-1000*mask16(1+sizn+s:nr1-sizn-s,1+sizn+s:nc1-sizn-s);
           flag16=2;
           hh=2;
        end;
     end;
     
     if (flag17==1)
        if (mask17(rr,cc)==1)
           jj17=jj17+1;
           if (in1(rr,cc)>=0.94)
           	siz=7;
              sigma=2;
           end;
           
              
        end;
        
        %jj=sum(sum(out(1+siz+s:nr1-siz-s,1+siz+s:nc1-siz-s).*mask1));
        if (jj17>=ii17)
           disp('here17');
           in1(1+sizn+s:nr1-sizn-s,1+sizn+s:nc1-sizn-s)=in1(1+sizn+s:nr1-sizn-s,1+sizn+s:nc1-sizn-s).*(1-mask17(1+sizn+s:nr1-sizn-s,1+sizn+s:nc1-sizn-s))-1000*mask17(1+sizn+s:nr1-sizn-s,1+sizn+s:nc1-sizn-s);
           flag17=2;
           hh=2;
        end;
     end;
     
if (flag18==1)
        if (mask18(rr,cc)==1)
           jj18=jj18+1;
           if (in1(rr,cc)>=0.9)
           	siz=6;
              sigma=1.8;
              end;
              
        end;
        
        %jj=sum(sum(out(1+siz+s:nr1-siz-s,1+siz+s:nc1-siz-s).*mask1));
        if (jj18>=ii18)
           disp('here18');
           in1(1+sizn+s:nr1-sizn-s,1+sizn+s:nc1-sizn-s)=in1(1+sizn+s:nr1-sizn-s,1+sizn+s:nc1-sizn-s).*(1-mask18(1+sizn+s:nr1-sizn-s,1+sizn+s:nc1-sizn-s))-1000*mask18(1+sizn+s:nr1-sizn-s,1+sizn+s:nc1-sizn-s);
           flag18=2;
           hh=2;
        end;
     end;


               if (flag2==1)
        if (mask2(rr,cc)==1)
           jj2=jj2+1;
        end;

        %jj=sum(sum(out(1+siz+s:nr1-siz-s,1+siz+s:nc1-siz-s).*mask2));
        if (jj2>=ii2)
           disp('here2');
           in1(1+sizn+s:nr1-sizn-s,1+sizn+s:nc1-sizn-s)=in1(1+sizn+s:nr1-sizn-s,1+sizn+s:nc1-sizn-s).*(1-mask2(1+sizn+s:nr1-sizn-s,1+sizn+s:nc1-sizn-s))-1000*mask2(1+sizn+s:nr1-sizn-s,1+sizn+s:nc1-sizn-s);
           flag2=2;
           hh=2;
        end;
     end;

	if (flag3==1)
   	if (mask3(rr,cc)==1)
           jj3=jj3+1;
       end;

        %jj=sum(sum(out(1+siz+s:nr1-siz-s,1+siz+s:nc1-siz-s).*mask3));
        if (jj3>=ii3)
           disp('here3');
           in1(1+sizn+s:nr1-sizn-s,1+sizn+s:nc1-sizn-s)=in1(1+sizn+s:nr1-sizn-s,1+sizn+s:nc1-sizn-s).*(1-mask3(1+sizn+s:nr1-sizn-s,1+sizn+s:nc1-sizn-s))-1000*mask3(1+sizn+s:nr1-sizn-s,1+sizn+s:nc1-sizn-s);
           flag3=2;
           hh=2;
        end; 
     end;
     
     if (flag4==1)
   	if (mask4(rr,cc)==1)
           jj4=jj4+1;
       end;

        %jj=sum(sum(out(1+siz+s:nr1-siz-s,1+siz+s:nc1-siz-s).*mask3));
        if (jj4>=ii4)
           disp('here4');
           in1(1+sizn+s:nr1-sizn-s,1+sizn+s:nc1-sizn-s)=in1(1+sizn+s:nr1-sizn-s,1+sizn+s:nc1-sizn-s).*(1-mask4(1+sizn+s:nr1-sizn-s,1+sizn+s:nc1-sizn-s))-1000*mask4(1+sizn+s:nr1-sizn-s,1+sizn+s:nc1-sizn-s);
           flag4=2;
           hh=2;
        end; 
     end;

     if (flag5==1)
   	if (mask5(rr,cc)==1)
           jj5=jj5+1;
       end;

        %jj=sum(sum(out(1+sizn+s:nr1-sizn-s,1+sizn+s:nc1-sizn-s).*mask3));
        if (jj5>=ii5)
           disp('here5');
           in1(1+sizn+s:nr1-sizn-s,1+sizn+s:nc1-sizn-s)=in1(1+sizn+s:nr1-sizn-s,1+sizn+s:nc1-sizn-s).*(1-mask5(1+sizn+s:nr1-sizn-s,1+sizn+s:nc1-sizn-s))-1000*mask5(1+sizn+s:nr1-sizn-s,1+sizn+s:nc1-sizn-s);
           flag5=2;
           hh=2;
        end; 
     end;
     
     if (flag6==1)
   	if (mask6(rr,cc)==1)
           jj6=jj6+1;
       end;

        %jj=sum(sum(out(1+sizn+s:nr1-sizn-s,1+sizn+s:nc1-sizn-s).*mask3));
        if (jj6>=ii6)
           disp('here6');
           in1(1+sizn+s:nr1-sizn-s,1+sizn+s:nc1-sizn-s)=in1(1+sizn+s:nr1-sizn-s,1+sizn+s:nc1-sizn-s).*(1-mask6(1+sizn+s:nr1-sizn-s,1+sizn+s:nc1-sizn-s))-1000*mask6(1+sizn+s:nr1-sizn-s,1+sizn+s:nc1-sizn-s);
           flag6=2;
           hh=2;
        end; 
     end;

if (flag7==1)
   	if (mask7(rr,cc)==1)
         jj7=jj7+1;
      end;

        %jj=sum(sum(out(1+sizn+s:nr1-sizn-s,1+sizn+s:nc1-sizn-s).*mask3));
        if (jj7>=ii7)
           disp('here7');
           in1(1+sizn+s:nr1-sizn-s,1+sizn+s:nc1-sizn-s)=in1(1+sizn+s:nr1-sizn-s,1+sizn+s:nc1-sizn-s).*(1-mask7(1+sizn+s:nr1-sizn-s,1+sizn+s:nc1-sizn-s))-1000*mask7(1+sizn+s:nr1-sizn-s,1+sizn+s:nc1-sizn-s);
           flag7=2;
           hh=2;
        end; 
     end;
     
     if (flag8==1)
   	if (mask8(rr,cc)==1)
         jj8=jj8+1;
      end;

        %jj=sum(sum(out(1+sizn+s:nr1-sizn-s,1+sizn+s:nc1-sizn-s).*mask3));
        if (jj8>=ii8)
           disp('here8');
           in1(1+sizn+s:nr1-sizn-s,1+sizn+s:nc1-sizn-s)=in1(1+sizn+s:nr1-sizn-s,1+sizn+s:nc1-sizn-s).*(1-mask8(1+sizn+s:nr1-sizn-s,1+sizn+s:nc1-sizn-s))-1000*mask8(1+sizn+s:nr1-sizn-s,1+sizn+s:nc1-sizn-s);
           flag8=2;
           hh=2;
        end; 
     end;
     
if (flag9==1)
   	if (mask9(rr,cc)==1)
         jj9=jj9+1;
      end;

        %jj=sum(sum(out(1+sizn+s:nr1-sizn-s,1+sizn+s:nc1-sizn-s).*mask3));
        if (jj9>=ii9)
           disp('here9');
           in1(1+sizn+s:nr1-sizn-s,1+sizn+s:nc1-sizn-s)=in1(1+sizn+s:nr1-sizn-s,1+sizn+s:nc1-sizn-s).*(1-mask9(1+sizn+s:nr1-sizn-s,1+sizn+s:nc1-sizn-s))-1000*mask9(1+sizn+s:nr1-sizn-s,1+sizn+s:nc1-sizn-s);
           flag9=2;
           hh=2;
        end; 
     end;


if (flag10==1)
   	if (mask10(rr,cc)==1)
         jj10=jj10+1;
         siz=6;
         sigma=1.6;
       end;

        %jj=sum(sum(out(1+sizn+s:nr1-sizn-s,1+sizn+s:nc1-sizn-s).*mask3));
        if (jj10>=ii10)
           disp('here10');
           in1(1+sizn+s:nr1-sizn-s,1+sizn+s:nc1-sizn-s)=in1(1+sizn+s:nr1-sizn-s,1+sizn+s:nc1-sizn-s).*(1-mask10(1+sizn+s:nr1-sizn-s,1+sizn+s:nc1-sizn-s))-1000*mask10(1+sizn+s:nr1-sizn-s,1+sizn+s:nc1-sizn-s);
           flag10=2;
           hh=2;
        end; 
     end;

if (flag11==1)
   	if (mask11(rr,cc)==1)
         jj11=jj11+1;
         siz=7;
         sigma=2;
       end;

        %jj=sum(sum(out(1+sizn+s:nr1-sizn-s,1+sizn+s:nc1-sizn-s).*mask3));
        if (jj11>=ii11)
           disp('here11');
           in1(1+sizn+s:nr1-sizn-s,1+sizn+s:nc1-sizn-s)=in1(1+sizn+s:nr1-sizn-s,1+sizn+s:nc1-sizn-s).*(1-mask11(1+sizn+s:nr1-sizn-s,1+sizn+s:nc1-sizn-s))-1000*mask11(1+sizn+s:nr1-sizn-s,1+sizn+s:nc1-sizn-s);
           flag11=2;
           hh=2;
        end; 
     end;
     
     if (flag12==1)
   	if (mask12(rr,cc)==1)
         jj12=jj12+1;
         siz=8;
         sigma=2.3;
       end;

        %jj=sum(sum(out(1+sizn+s:nr1-sizn-s,1+sizn+s:nc1-sizn-s).*mask3));
        if (jj12>=ii12)
           disp('here12');
           in1(1+sizn+s:nr1-sizn-s,1+sizn+s:nc1-sizn-s)=in1(1+sizn+s:nr1-sizn-s,1+sizn+s:nc1-sizn-s).*(1-mask12(1+sizn+s:nr1-sizn-s,1+sizn+s:nc1-sizn-s))-1000*mask12(1+sizn+s:nr1-sizn-s,1+sizn+s:nc1-sizn-s);
           flag12=2;
           hh=2;
        end; 
     end;

     if (flag13==1)
   	if (mask13(rr,cc)==1)
         jj13=jj13+1;
         siz=9;
         sigma=2.7;
       end;

        %jj=sum(sum(out(1+sizn+s:nr1-sizn-s,1+sizn+s:nc1-sizn-s).*mask3));
        if (jj13>=ii13)
           disp('here13');
           in1(1+sizn+s:nr1-sizn-s,1+sizn+s:nc1-sizn-s)=in1(1+sizn+s:nr1-sizn-s,1+sizn+s:nc1-sizn-s).*(1-mask13(1+sizn+s:nr1-sizn-s,1+sizn+s:nc1-sizn-s))-1000*mask13(1+sizn+s:nr1-sizn-s,1+sizn+s:nc1-sizn-s);
           flag13=2;
           hh=2;
        end; 
     end;

if (flag14==1)
   	if (mask14(rr,cc)==1)
         jj14=jj14+1;
         siz=10;
         sigma=3;
       end;

        %jj=sum(sum(out(1+sizn+s:nr1-sizn-s,1+sizn+s:nc1-sizn-s).*mask3));
        if (jj14>=ii14)
           disp('here14');
           in1(1+sizn+s:nr1-sizn-s,1+sizn+s:nc1-sizn-s)=in1(1+sizn+s:nr1-sizn-s,1+sizn+s:nc1-sizn-s).*(1-mask14(1+sizn+s:nr1-sizn-s,1+sizn+s:nc1-sizn-s))-1000*mask14(1+sizn+s:nr1-sizn-s,1+sizn+s:nc1-sizn-s);
           flag14=2;
           hh=2;
        end; 
     end;
     
   if (flag19==1)
   	if (mask19(rr,cc)==1)
         jj19=jj19+1;
         siz=10;
         sigma=3;
       end;

        %jj=sum(sum(out(1+sizn+s:nr1-sizn-s,1+sizn+s:nc1-sizn-s).*mask3));
        if (jj19>=ii19)
           disp('here14');
           in1(1+sizn+s:nr1-sizn-s,1+sizn+s:nc1-sizn-s)=in1(1+sizn+s:nr1-sizn-s,1+sizn+s:nc1-sizn-s).*(1-mask19(1+sizn+s:nr1-sizn-s,1+sizn+s:nc1-sizn-s))-1000*mask19(1+sizn+s:nr1-sizn-s,1+sizn+s:nc1-sizn-s);
           flag19=2;
           hh=2;
        end; 
     end;
  
  dis=kern1(siz,sigma);

   if (i/10000 == floor(i/10000)) disp([num2str(round((i/insum)*100)),'% done']);disp('----');
      %out1=out(1+siz+s:nr1-siz-s,1+siz+s:nc1-siz-s);
      %O=abs(fft2(inak-out1));
      %surf(O(2:128,2:128));
      %pause;
      %imshow(out1);
      %pause;
   end; %figure(1); imshow(out(1+siz+s:nr1-siz-s,1+siz+s:nc1-siz-s)); 
   %figure(2); imshow(in1(1+siz+s:nr1-siz-s,1+siz+s:nc1-siz-s)); pause; end;
   %end;
   
   %if (in1(rr,cc) <=0.01) siz=10; dis=kerntest(0.01,siz,4.025); end;   
    
   in1(rr-siz:rr+siz,cc-siz:cc+siz)=in1(rr-siz:rr+siz,cc-siz:cc+siz)-dis;
   
   
   in1(rr,cc)=-1000;
   
   
   if (hh==1)
   	rrr=(rr-siz:rr+siz);
   	ccc=(cc-siz:cc+siz);
   	[S(ccc),I(ccc)]=max(in1(:,ccc));
   	[SM, cc]=max(S);
      rr=I(cc);
   else
      
      [S,I]=max(in1);
		[SM,cc]=max(S);
      rr=I(cc);
   end;
   

     
   
   
end
if (~flag)
   out=out(1+sizn+s:nr1-sizn-s,1+sizn+s:nc1-sizn-s);
else
   out=1-out(1+sizn+s:nr1-sizn-s,1+sizn+s:nc1-sizn-s);
end;