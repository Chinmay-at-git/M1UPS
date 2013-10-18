%Diallo ALpha Oumar Binta
%Groupe 3.2
%Tp2 OIM

%Question 1.2
%chargement de l'image
img = imread('TP2_1.jpg');
%affichage de l'image image(img);

%Question 1.2
%taille de l'image
taille = size(img)
%400 represente le nombre de lignes
%600 represente le nombre de colonnes
%3 represente le Nombre d'échantillons
%L'image comporte 400 sur 600 pixels, stockée dans une matrice à 3 dimensions.
%La valeur 3 indique qu'on utilise 3 composantes pour coder la couleur de chaque
%pixel, la couleur peut être obtenue en mélangeant une certaine quantité 
%(= intensité) de Rouge, une certaine quantité de Vert,et une certaine quantité
%de Bleu.
%imfinfo('TP2_1.jpg') pour avoir les informations sur l'image
%uint8 conversion de donnees en type non signe sur 8 bits

%Question 1.4
%Matrice à trois dimensions
imgBleue =  uint8(zeros(taille));
for I=1:taille(1)
    for J=1:taille(2)
      for K=1:taille(3)
	% on recopie uniquement la troisieme composante
	%les intensites en Rouge et en Vert restent a 0
	imgBleue(I,J,3) = img(I,J,3);
      end
    end
end

%Question 1.5
imgRouge =  uint8(zeros(taille));
imgRouge(:,:,1) = img(:,:,1);
imgVerte =  uint8(zeros(taille));
imgVerte(:,:,2) = img(:,:,2);

%  image(imgBleue);
%  figure;
%  image(imgRouge);
%  figure;
%  image(imgVerte);
%la carroserie ne contient ni de rouge, ni de bleue

%Question 2.1
seuil = 200;
imgf = uint8(zeros(taille));
for x=1:taille(1)
    for y=1:taille(2)
        if img(x,y,3) > seuil
            imgf(x,y,1) = img(x,y,1);
            imgf(x,y,2) = img(x,y,2);
            imgf(x,y,3) = img(x,y,3);
        end
    end
end
%  figure;
%  image(imgf);

%Question 2.2 seuil=110 condition=img(x,y,3) > seuil
%Question 2.2 seuil=110 condition=img(x,y,1) < seuil (seuillage composante rouge)
%Question 2.4
seuil = 110;
imgVoiture = uint8(zeros(taille));
for x=1:taille(1)
    for y=1:taille(2)
        if img(x,y,1) < seuil && img(x,y,3) > seuil
            imgVoiture(x,y,1) = img(x,y,1);
            imgVoiture(x,y,2) = img(x,y,2);
            imgVoiture(x,y,3) = img(x,y,3);
        end
    end
end
%  figure;
%  image(imgVoiture);

%Question 2.5 image couleur
imgTransforme = imgVoiture;
for x=1:taille(1)
    for y=1:taille(2)
      %on intervertit le vert et le bleue
      imgTransforme(x,y,3) = img(x,y,2);
      imgTransforme(x,y,2) = img(x,y,3);
      %on recopie les contours
      if ~(img(x,y,1) < seuil && img(x,y,3) > seuil)
            imgTransforme(x,y,1) = img(x,y,1);
            imgTransforme(x,y,2) = img(x,y,2);
            imgTransforme(x,y,3) = img(x,y,3);
        end
    end
end
%  figure;
%  image(imgTransforme);

%Question II.1.1) Niveau de gris et image binaire
imgNG = uint8(zeros(taille));
%methode pour la perception de l'oeil humain
%imgNG = 0.2989 * img(:,:,1) + 0.5870 * img(:,:,2) + 0.1140 * img(:,:,3);
%methode simple
imgNG = img(:,:,1)/3 + img(:,:,2)/3 + img(:,:,3)/3;
%  figure;
%  image(imgNG);
%  colormap(gray(256));

%%Question II.1.2) Binarisation
imgBin = imgNG;
for x=1:taille(1)
    for y=1:taille(2)
      if imgBin(x,y) > 128
         imgBin(x,y) = 1;
       else
	  imgBin(x,y)=0;
      end
    end
end
figure;
image(imgBin);
colormap(gray(2));




