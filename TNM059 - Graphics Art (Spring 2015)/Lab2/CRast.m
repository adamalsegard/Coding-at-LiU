function [ NyBild ] = CRast( Bild, filter, metod )
%Rastrera en färgbild kanal för kanal....typ

R = Bild(:,:,1);
G = Bild(:,:,2);
B = Bild(:,:,3);

if metod == 1
NyBild(:,:,1) = errordif(R, filter);
NyBild(:,:,2) = errordif(G, filter);
NyBild(:,:,3) = errordif(B, filter);
end

if metod == 2
NyBild(:,:,1) = imcdp(R);
NyBild(:,:,2) = imcdp(G);
NyBild(:,:,3) = imcdp(B);
end

if metod == 3
NyBild(:,:,1) = tabellrast(R);
NyBild(:,:,2) = tabellrast(G);
NyBild(:,:,3) = tabellrast(B);
end

if metod == 4
NyBild(:,:,1) = troskel(R, filter);
NyBild(:,:,2) = troskel(G, filter);
NyBild(:,:,3) = troskel(B, filter);
end

end

