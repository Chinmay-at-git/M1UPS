%change le signal
[signal,fs,q,options] = wavread('parole.wav');
%affiche le signal
%plot(signal);
%taille signal
taille = size(signal)
%Intervalle de variation des échantillons du signal
min(signal)
max(signal)
%calcul de la durée
nombre_points = taille(1)
duree =nombre_points/fs

%affichage de la portion
for I=11300:12323
    signal_extrait(I-11300+1) = signal(I);
end
plot(signal_extrait, 'rx')

%signal_emplifie = signal
for I=8854:14999
    signal_emplifie(I) = signal_emplifie(I)*5;
end
%sauvegarde wavwrite(signal_emplifie, 'test.wav')
wavwrite(signal_emplifie, 'Signal_emplifie.wav')

for I=138:taille
    son_sans_bip(I) = signal(I);
end
wavwrite(son_sans_bip, 'son_sans_bip.wav')

[music,fs,q,options] = wavread('musique.wav');
taille_music = size

