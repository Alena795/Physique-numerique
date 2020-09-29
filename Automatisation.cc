#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <vector>
using namespace std;



// //!\\ Se référer au github suivant pour obtenir des informations supplémentaire: https://github.com/PierreAncey/Physique-numerique





// //!\\ IMPORTANT: A MODIFIER

const char* Configuration("configuration.in"); //Fichier de configuration
const char* Executable("./Exercice1_2020_PierreAncey"); //Insérer commande servant à exécuter l'exercice de physique numérique dans le terminal
string Output("output.out"); //Insérer nom du fichier d'output de l'exercice
size_t PosColonne(2); //Insérer la colonne de l'élément (colonne dans l'output) que l'on va utiliser dans MatLab
/* Exemple:
   Soit output.ou de la forme:
   0 0 0
   0 a 0
   La colonne qui contient la valeur a est la colonne numéro 2. Si l'on veut voir comment évolue x en fonction de nsteps 
   et que les x sont contenus dans la 3ème colonne, alors on prend la colonne numéro 3.
*/

// //!\\ IMPORTANT: A MODIFIER





//Calcul du nombre de colonne en fonction des espaces entre les nombres de la première ligne et retour du résultat
size_t NombreColonneOutput(){
	ifstream ALire;
	ALire.open(Output);
	string ligne;
	getline(ALire, ligne);
	int compteur(0);
	for (size_t i(0); i < ligne.length(); ++i){
		if (ligne[i] == ' '){
			++compteur;
		}
	}
	return compteur;
}

//Retourne la string prise en paramètre en supprimant tout élément après le premier chiffre de la string.
string LireJusquaEgal(string const& LigneASeparer){
	size_t i = 0;
	for (; i < LigneASeparer.length(); i++){ 
		if (LigneASeparer[i]=='='){ 
			++i;
			break; 
		}
	}
	return LigneASeparer.substr(0, i);
}

//Retourne la string prise en paramètre en supprimant tout élément après le premier espace de la string.
string LireJusquaEspace(string const& LigneASeparer){
	size_t i = 0;
	for (; i < LigneASeparer.length(); i++){ 
		if (isblank(LigneASeparer[i])){ 
			break; 
		}
	}
	return LigneASeparer.substr(0, i);
}

//Retourne la string prise en paramètre en supprimant tout élément avant le premier espace de la string.
string LireDepuisEspace(string const& LigneASeparer){
	size_t i = 0;
	for (; i < LigneASeparer.length(); i++){ 
		if (isblank(LigneASeparer[i])){ 
			break; 
		}
	}
	return LigneASeparer.substr(i, LigneASeparer.length() - i);
}

//Retourne la string prise en paramètre à partir de '%'
string LireDepuisCommentaire(string const& LigneASeparer){
	size_t i = 0;
	for (; i < LigneASeparer.length(); i++){ 
		if (LigneASeparer[i] == '%'){ 
			break; 
		}
	}
	return LigneASeparer.substr(i, LigneASeparer.length() - i);
}

//Retourne le nombre d'une ligne (elle ne doit pas en contenir plusieurs)
string LireChiffres(string const& LigneASeparer){
	string Temp;
	size_t i(LireJusquaEgal(LigneASeparer).length() + 1);
	while((!isblank(LigneASeparer[i])) and (LigneASeparer[i] != '%')){
		Temp.push_back(LigneASeparer[i]);
		++i;
	}
	return Temp;
}

//Modifie toute les valeurs du fichier de configuration à l'exception de nsteps
void ModifierLesValeursHorsNSteps(){
	//Déclaration variables et ouverture des canaux
	string ligne;
	ifstream ALire;
	ALire.open(Configuration);
	if (ALire.is_open() != true){
		throw(1);
	}
	ofstream temp;
	temp.open("temp.txt");
	string reponse;
	
	//Informations à l'utlisateur
	cout << endl << "================================================================================" << endl
	     << "Fonctionnement : Choisissez une valeur pour toutes les variables. Si vous ne voulez pas changer la valeur d'une variable, appuyez sur entrée. Entrez i pour avoir des informations sur la variable. Tapez v pour voir la valeur actuelle."
	     << endl << "================================================================================" << endl << endl;
	     
	//Création d'un fichier temporaire auquel on ajoute les informations que l'on souhaite
	while (getline(ALire, ligne)){
		//Si la ligne ne contient pas de valeur intéressante, on la saute
		if ((ligne.find("nsteps") != ligne.npos) or ligne[0] == '%' or ligne.empty()){
			temp << ligne << endl;
		}
		// Sinon on demande une précision sur ce que l'utilisateur veut faire
		else{
			do{
				cout << "Quelle valeur donner à la variable " << LireJusquaEspace(ligne) << " ?  "; 
				
				getline(cin, reponse);
				if (reponse.empty()){
					temp << ligne << endl;
				}
				else{
					if (reponse == "i"){
						cout << LireDepuisCommentaire(ligne) << endl;
					}
					else if (reponse == "v"){
						cout << LireChiffres(ligne) << endl;
					}
					else{
						ligne = LireJusquaEgal(ligne) + " " + reponse + "   " + LireDepuisCommentaire(ligne);									
						temp << ligne << endl;
					}
				}
			} while(reponse == "i" or reponse =="v");	
		}	
	}
	
	//On ferme les canaux et on remplace le fichier à lire par le fichier temporaire
	ALire.close();
	temp.close();
	remove(Configuration); 
	rename("temp.txt", Configuration);
}

//Modifie nsteps
void ModifierNSteps(int valeur){	
	//Déclaration variables et ouverture des canaux
	string ligne; 
	ifstream ALire;
	ALire.open(Configuration);
	if (ALire.is_open() != true){
		throw(1);
	}
	ofstream temp;
	temp.open("temp.txt");
	
	//Création d'un fichier temporaire auquel on ajoute les informations que l'on souhaite
	while (getline(ALire, ligne)){
		// La ligne ne contient pas la variable recherchée
		if (ligne.find("nsteps") == ligne.npos){
			temp << ligne << endl;
		}
		//Si on trouve la variable, on modifie sa valeur
		else{		
			ligne = LireJusquaEgal(ligne) + " " + to_string(valeur) + "   " + LireDepuisCommentaire(ligne);			
			temp << ligne << endl;
		}
	}
	
	//On ferme les canaux et on remplace le fichier à lire par le fichier temporaire
	ALire.close();
	temp.close();
	remove(Configuration); 
	rename("temp.txt", Configuration);
}

//Sauvegarde le fichier de configuration
void SauvegardeFichierInitial(string FichierInitial){
	//Déclaration variables et ouverture des canaux
	string ligne; 
	ifstream ALire;
	ALire.open(FichierInitial);
	if (ALire.is_open() != true){
		throw(1);
	}
	
	//Regarde si la copie existe déjà
	ifstream Check;
	Check.open("Copie_configuration.txt");
	
	//Si la copie n'existe pas, on la fait. Si elle existe, on ne fait rien.
	if (Check.fail()){
		//Création d'une copie du fichier de configuration
		ofstream Copie;
		Copie.open("Copie_configuration.txt");
		while (getline(ALire, ligne)){
			Copie << ligne << endl;
		}
		//On ferme le canal de copie
		Copie.close();
	}
	
	//On ferme les canaux
	ALire.close();
	Check.close();
}

//Réinitialise le fichier de configuration
void ReinitialiserConfiguration(){
	remove(Configuration);
	rename("Copie_configuration.txt", Configuration);
	SauvegardeFichierInitial(Configuration);
}

//On prend la dernière valeur de la colonne choisie
double DerniereValeurColonne(int NombreColonne){
	ifstream ALire;
	ALire.open(Output);
	vector<double> vec;
	double a;
	while (ALire >> a){
		vec.push_back(a);
	}
	double donnee(vec[vec.size()-1 - (NombreColonne-PosColonne)]);
	ALire.close();
	
	return donnee;
}

//Exécution du programme
int main(){	
	//On calcule le nombre de colonne dans le fichier d'Output
	size_t NombreColonne(NombreColonneOutput());
	
	//On demande des informations à l'utilisateur
	size_t nbr_nsteps(0); // Nombre de steps pour la première simulation
	size_t nbr_simulations(0); // Nombre de simulations à faire
	double coeff(0); // Coefficient entre les nsteps de chaque simulation 
	char que_faire;
	
	/*Exemple:
	coeff=2, nbre_steps = 1'000, nbr_simulations = 5
	
	On aura respectivement comme nbr_steps pour les simulations: 1'000, 2'000, 4'000, 8'000, 16'000
	*/
	
	//Présentation
	cout << "======================================================" << endl 
	     << "Programme d'automatisation par Pierro le meilleur bro'" << endl 
	     << "======================================================" << endl << endl;
	
	//Sauvegarde du fichier initial
	SauvegardeFichierInitial(Configuration);
	
	//Choix de l'application
	cout << "Voulez-vous modifier tous les elements du fichier de configuration ou seulement nsteps ? (o = tous les modifier, r = remplacer le fichier de configuration actuel par le fichier initial, tout autre caractère = modifier juste nsteps)  ";
	cin >> que_faire;
	
	//Reinitialise le fichier de configuration si demandé
	if (que_faire == 'r'){
		cin.ignore();
		ReinitialiserConfiguration();
		return 0;
	}
	
	//Choix des paramètres liés à nsteps
	cout << endl 
	     << "==================================" << endl 
	     << "Choix des paramètres liés à nsteps" << endl 
	     << "==================================" << endl;	
	cout << endl << "Combien de nsteps voulez-vous pour la première simulation?" << endl;
	cin >> nbr_nsteps;
	cout << "Combien de simulation voulez-vous faire?" << endl;
	cin >> nbr_simulations;
	while (coeff <= 0){
		cout << "Quel coefficient entre les nsteps de simulations différentes?" << endl;
		cin >> coeff;
	}
	
	//Exécute le programme total si condition demandé
	if (que_faire == 'o'){
		cin.ignore();
		ModifierLesValeursHorsNSteps();
	}

	//Annonce
	cout << endl << "===========================" << endl 
		 << "*Lancement des simulations*" << endl 
		 << "===========================" << endl << endl;
	
	//On crée un fichier texte pour recevoir les données que l'on utilisera dans MatLab
	ofstream ValeursMatLab;
	ValeursMatLab.open("ValeursMatLab.txt");
	
	//Exécute les simulations
	for (size_t i(0); i < nbr_simulations; ++i){
		cout << "=============" << endl
		     << "Simulation " << i+1 << ": " << endl
		     << "=============" << endl << endl;
		ModifierNSteps(nbr_nsteps*(pow(coeff, i)));
		std::system(Executable); //Sous Linux (marche pour les machines virtuelles)
		ValeursMatLab << nbr_nsteps*(pow(coeff, i)) << " " << DerniereValeurColonne(NombreColonne) << endl;		
		cout << endl;
	}
	
	//On affiche le message finaé
	cout << "=====================" << endl 
		 << "*Fin des simulations*" << endl 
		 << "=====================";
	//Le fichier contient les nsteps dans la première colonne et la valeur choisie dans la deuxième
	
	//On ferme le dernier ostream
	ValeursMatLab.close();

	return 0;
}
