%Charge les valeurs dans MatLab
filename = 'ValeursMatLab.txt';
data = load(filename);

%Défini les variables associées aux valeurs dans MatLab
dt_num = data(:,1); 
xfin_num = data(:,2);

%Exercice 1.3b)
%x = 0.778363*10^-6;
%xdiff = abs(xfin_num - x);

%Génération du graphe
lw=2; fs=16;
figure
plot(dt_num, xfin_num, 'k+-','linewidth',lw)
set(gca,'fontsize',fs)
xlabel('dt [s]')
ylabel('v_{final} [m/s]')
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
