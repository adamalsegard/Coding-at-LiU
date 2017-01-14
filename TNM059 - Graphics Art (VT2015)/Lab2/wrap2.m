function out=wrap2(in,s)

[nr,nc]=size(in);

out=ones(nr+2*s ,nc+2*s);

out(1:s,1:s)=in(nr-s+1:nr,nc-s+1:nc);
out(1:s,s+1:nc+s)=in(1:s,:);
out(1:s,nc+s+1:nc+2*s)=in(nr-s+1:nr,1:s);

out(s+1:nr+s,1:s)=in(1:nr,1:s);
out(s+1:nr+s,nc+s+1:nc+2*s)=in(1:nr,nc-s+1:nc);

out(nr+s+1:nr+2*s,1:s)=in(1:s,nc-s+1:nc);
out(nr+s+1:nr+2*s,s+1:nc+s)=in(nr-s+1:nr,:);
out(nr+s+1:nr+2*s,nc+s+1:nc+2*s)=in(1:s,1:s);



out(s+1:nr+s,s+1:nc+s)=in;