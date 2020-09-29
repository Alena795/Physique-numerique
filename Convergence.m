%Charge les valeurs dans MatLab
filename = 'ValeursMatLab.txt';
data = load(filename);

%Définit les variables associées aux valeurs dans MatLab
nsteps_num = data(:,1); 
xfin_num = data(:,1);

%Génération du graphe
lw=2; fs=16;
figure
plot(1./nsteps_num, xfin_num, 'k+-','linewidth',lw)
set(gca,'fontsize',fs)
xlabel('1/N_{steps}')
ylabel('x_{final}')
grid on

% si on a la solution analytique:
% xfin_ana = ...; % à compléter
% error_xfin = xfin_num-xfin_ana;
% figure
% plot(nsteps_num, abs(error_xfin),'k+-')
% set(gca,'fontsize',fs)
% set(gca,'xscale','log')
% set(gca,'yscale','log')
% xlabel('N_{steps}')
% ylabel('Error on x_{fin}')
% grid on
