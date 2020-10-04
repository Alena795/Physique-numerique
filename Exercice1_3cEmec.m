% Nom du fichier d'output a analyser (modifiez selon vos besoins)
filename = 'output.out'; 

% Chargement des donnees
data = load(filename);

% Extraction des quantites d'interet
Pf = data(:,4);
Emec = data(:,5);

%Variables utiles
nsteps = 2e3;
tfin = 1.5e-12;
dt = tfin/nsteps; 

%Calcul de la matrice contenant les éléments de temps
t = 0;
ListeTemps = [];
while t < tfin - dt 
    ListeTemps = [ListeTemps; t];
    t = t + dt;
end

%Calcul de la pente de Emec par rapport à t
PenteEmec = [];
for c = 1:(size(Emec)-1)
    PenteEmec = [PenteEmec; (Emec(c+1)-Emec(c))/dt];
end

%Suppression du dernier élément de pf pour pouvoir le plot
Pf(end) = [];

% Test taille arrays
%size(PenteEmec)
%size(ListeTemps)
%size(Pf)

%Génération du graphe
lw=2; fs=16;
figure
plot(ListeTemps, PenteEmec, 'k+-','linewidth',lw)
hold on
plot(ListeTemps, Pf, 'r*-','linewidth',lw)
hold off
set(gca,'fontsize',fs)
xlabel('Temps [s]')
ylabel('Puissance [W]')
legend('dEmec/dt','Pf')
grid on

