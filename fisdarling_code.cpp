/****************************************************************************/
/* Programa: Algoritme de gestió i cerca de Fis - Darling                   */
/* Autor: Oriol de la Pau Chacón i Albero                                   */
/* Objectiu: administrar una xarxa d'usuaris que cerquen parella            */
/****************************************************************************/

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <math.h>

using namespace std;

#define TAM 1000


struct usuari
{
	string nom;
	string correu;
	float latitud;
	float longitud;
	int any;
	char sexe;
	int musica;
	int cinema;
};

struct topcinc
{
	string nom;
	float puntuacio;
};



/*  Prototips de les funcions  */

int   CarregaFitxer (usuari v[TAM]);
int   OpcionsMenu ();
bool  ComprovarCorreu (usuari v[TAM], string comprovat, int quants);
int   TrobarPosicio (usuari v[TAM], int quants, usuari nou);
void  InserirFitxa (usuari v[TAM], int & quants, usuari nou);
void  NovaFitxa (usuari v[TAM], int & quants);
void  MostrarLlista (usuari v[TAM], int quants);
int   CercarUsuari (usuari v[TAM], int quants, string correu);
int   CercarUsuari2 (usuari v[TAM], int quants, string nom);
void  ModificarFitxa (usuari v[TAM], int quants);
void  EsborrarFitxa (usuari v[TAM], int & quants);
char  MenuSecundari ();
float DistanciaUsuaris (usuari Usuari_1, usuari Usuari_2);
int   CercarPosicio5 (usuari v[TAM], int n, usuari insertat, usuari buscat);
void  Inserir (usuari v[TAM], int n, int pos, usuari insertat);
void  InserirOrdenat (usuari v[TAM], int n, usuari insertat, usuari buscat);
void  ProximitatGeografica (usuari v[TAM], int quants);
int   AfinitatUsuaris (usuari Usuari_1, usuari Usuari_2);
int   CercarPosicio4 (usuari v[TAM], int n, usuari insertat, usuari buscat);
void  InserirOrdenat2 (usuari v[TAM], int n, usuari insertat, usuari buscat);
void  AfinitatGustos (usuari v[TAM], int quants);
void  CercaMulticriteri (usuari v[TAM], int quants);
void  FinalPrograma (usuari v[TAM], int quants);


/*
 *  Funció principal
 */
 

int main ()
{
	usuari  vector [TAM];
	int     usuaris;
	int		opc; 
	char    opc_2;
	
	cout << "Benvingut al menu principal de Fis-Darling: Code & Love." << endl;
	
	usuaris = CarregaFitxer (vector);
	
	
	do
	{
		opc = OpcionsMenu ();
		switch (opc)
		{
			case 1:
				NovaFitxa (vector, usuaris);
				break;
				
			case 2:
				MostrarLlista (vector, usuaris);
				cout << usuaris << " usuaris" << endl;
				break;
				
			case 3:
				ModificarFitxa (vector, usuaris);
				break;
				
			case 4:
				EsborrarFitxa (vector, usuaris);
				break;
				
			case 5:
				do 
				{
					opc_2 = MenuSecundari ();
					if (opc_2 == 'a')
					{
						ProximitatGeografica (vector, usuaris);
					}
					else if (opc_2 == 'b')
						{
							AfinitatGustos (vector, usuaris);
						}
						else
						{
							cout << "Error. Escolleix una de les dues opcions indicades." << endl;
						}
				} while (opc_2 != 'a' && opc_2 != 'b');
				break;
				
			case 6:
				CercaMulticriteri (vector, usuaris);
				break;
				
			default:
				if (opc != 0)
					cout << "Error. Escolleix una de les opcions indicades." << endl;			
		}		
	} while (opc != 0);
	
	FinalPrograma (vector, usuaris);
	
	system ("pause");
	return 0;
}



/*  Implementació de les funcions  */



/********************************************************/
/* Funió: CarregaFitxer                                 */
/* Rep el vector buit i hi emplena les dades del vector */
/* Retorna el nombre d'usuaris                          */
/********************************************************/

int CarregaFitxer (usuari v[TAM])
{
	ifstream f;
	usuari   u;
	int      i = 0;
	string   nom;
	char     opc;
	
	cout << endl << "Introdueix el nom del fitxer amb el qual anem a treballar: " << endl;
	cin >> nom;
	
	
	f.open (nom.c_str());
	if (!f)
	{
		do
		{
			cout << "Error obrint el fitxer. Pot ser que hages escrit malament el nom del fitxer o que aquest no existisca encara. Si vols tornar a provar a escriure el nom, escriu A. Si vols crear-ne un de nou amb aquest nom, escriu B:" << endl;
			cin >> opc;
			
			if (opc == 'A')
			{
				cout << "Escriu de nou el nom del fitxer:" << endl;
				cin >> nom;
			}
			else if (opc == 'B')
			    {
					ofstream g;
					g.open(nom.c_str());
					i = 0;
				}
		} while (opc != 'A' && opc != 'B');
	}
	else
	{
		while (!f.eof())
		{
			getline (f, v[i].nom);
			getline (f, v[i].correu);
			f >> v[i].latitud >> v[i].longitud  >> v[i].any >> v[i].sexe; 
 			f >> v[i].musica >> v[i].cinema;
			f.ignore();
			i += 1;
		}
	}
	f.close ();
	i -= 1;
	
	return i;
}



/******************************************************************/
/* Funció: OcionsMenu                                             */
/* Presenta les diferents opcions del menú principal del programa */
/* Retorna l'opció escollida per l'usuari                         */
/******************************************************************/

int OpcionsMenu ()
{
	int Opc_esc;
	
	cout << "Que vols fer a continuacio? Escolleix una de les seguents opcions:" << endl;
	cout << "0) Eixir\n" << "1) Crear nova fitxa\n" << "2) Llistar fitxes\n" << "3) Modificar les dades d'una fitxa determinada\n" << "4) Esborrar una fitxa\n" << "5) Cercar persones per proximitat geografica o interessos comuns\n" <<  "6) Cercador multicriteri (donats els multiplicadors et diu el Top-5 de persones mes afins).\n" << endl;
	cin >> Opc_esc;
	
	return (Opc_esc);
}




/**********************************************************************************************/
/* Funció booleana: ComprovarCorreu                                                           */
/* Recorre el vector i retorna un booleà: si ha trobat el correu que ha rebut per valor o no  */
/**********************************************************************************************/

bool ComprovarCorreu (usuari v[TAM], string comprovat, int quants)
{
	bool Ja_existeix = false;
	int  i;
	
	for (i = 0; i < quants; i++)
	{
		if (v[i].correu == comprovat)
			Ja_existeix = true;
	}
	
	return (Ja_existeix);
}



/***********************************************************************************/
/* Funció: TrobarPosició                                                           */
/* Rep el vector i una estructura usuari, i en retorna la seua posició al vector   */
/* ordenat alfabèticament pel nom                                                  */
/***********************************************************************************/

int TrobarPosicio (usuari v[TAM], int quants, usuari nou)
{
	int i;
	i = 0;
	
	while (i < quants && v[i].nom < nou.nom)
	{
		i += 1;
	}
	
	return i;
}



/****************************************************************************/
/* Funció: InserirFitxa                                                     */
/* Rep les dades d'un usuari i les inserix en el vector en la seua posició  */
/* ordenat alfabèticament. Rep per referència el nombre d'usuaris i canvia  */
/* el seu valor, ja que hi ha un usuari més.                                */
/****************************************************************************/

void InserirFitxa (usuari v[TAM], int & quants, usuari nou)
{
	int posicio;
	int i;
	
	posicio = TrobarPosicio (v, quants, nou);
	
	for (i = quants - 1; i >= posicio; i--)
	{
		v[i + 1] = v[i];
	}
	quants += 1;
	v[posicio] = nou;
}



/****************************************************************************/
/* Demana les dades per a crear unnou usuari i comprova si el seu correu ja */
/* existeix o no.                                                           */
/****************************************************************************/

void NovaFitxa (usuari v[TAM], int & quants)
{
	struct usuari nou;
	string resposta = "si";
	
	cout << "Heu escollit crear una nova fitxa, introduiu la informacio personal:" << endl;
	cout << "Cognoms, nom: ";
	cin.ignore();
	getline (cin, nou.nom);
	cout << "Correu electronic: ";
	getline (cin, nou.correu);
	cout << "Latitud: ";
	cin >> nou.latitud;
	cout << "Longitud: ";
	cin >> nou.longitud;
	cout << "Any de naixement: ";
	cin >> nou.any;
	cout << "Sexe (h / d): ";
	cin >> nou.sexe;
	cout << "Interes per la musica entre 1 i 5: ";
	cin >> nou.musica;
	cout << "Interes pel cinema entre 1 i 5: ";
	cin >> nou.cinema;
	cout << endl;
	
	while (ComprovarCorreu (v, nou.correu, quants) == true && resposta == "si")
	{
		cout << "Ja existeix un usuari amb aquest correu. Voleu afegir aquesta fitxa de totes formes?";
		
		do
		{
			cin >> resposta;
			if (resposta == "si" || resposta == "Si")
			{
				cout << "Introduiu un nou correu electronic: ";
				cin.ignore();
				getline (cin, nou.correu);
			}
			else if (resposta == "no" || resposta == "No")
					cout << "Com no vols inserir la fitxa tornem al menu principal" << endl;
				else
					cout << "Resposta incorrecta. Contesta si o no" << endl;
		} while (resposta != "si" && resposta != "no");
	}
	
	if (resposta == "si")
	{
		InserirFitxa (v, quants, nou);
		cout << "L'usuari " << nou.nom << " ha sigut donat d'alta." << endl;
		cout << endl;
	}
}





/******************************************************************************/
/* Funció: MostrarLlista                                                      */
/* Rep el vector i el nombre d'usuaris i els mostra tots per pantalla         */
/******************************************************************************/

void MostrarLlista (usuari v[TAM], int quants)
{
	int i;
	
	for (i = 0; i < quants; i++)
	{
		cout << v[i].nom << endl;
		cout << v[i].correu << endl;
		cout << v[i].latitud << "\t" << v[i].longitud << "\t" << v[i].any << "\t" << v[i].sexe << endl;
		cout << v[i].musica << "\t" << v[i].cinema << endl;
	}
}



/***********************************************************************/
/* Retorna la posició d'un usuari al vector buscat pel correu          */
/***********************************************************************/

int CercarUsuari (usuari v[TAM], int quants, string correu)
{
	int i = 0;
	
	while (i < quants && v[i].correu != correu)
	{
		i += 1;
	}
	
	return i;
}



/*********************************************************************/
/* Retorna la posició d'un usuari al vector buscat pel correu        */
/*********************************************************************/


int CercarUsuari2 (usuari v[TAM], int quants, string nom)
{
	int i = 0;
	
	while (i < quants && v[i].nom != nom)
	{
		i += 1;
	}
	
	return i;
}




/***************************************************************************/
/* Modifica un camp de dades d'una fitxa escollit per l'usuari i si es     */
/* canvia el nom, es reordena                                              */
/***************************************************************************/

void ModificarFitxa (usuari v[TAM], int quants)
{
	string  correu;
	int     pos;
	int     i;
	char    opc;
	usuari  aux;
	
	cout << "Heu escollit modificar les dades d'una fitxa. Introduiu el correu electronic de l'usuari del qual voleu canviar les dades. " << endl;
	cin.ignore ();
	getline (cin, correu);

		
	if (ComprovarCorreu (v, correu, quants))
	{
		pos = CercarUsuari (v, quants, correu);
	
		cout << "L'usuari/a buscat es " << v[pos].nom << "." << endl;	
		
		do
		{
			cout << "Escolliu quin camp de dades voleu modificar: \n" << "a) Nom.\n" << "b) Correu.\n" << "c) Latitud.\n" << "d) Longitud.\n" << "e) Any.\n" << "f) Sexe.\n" << "g) Musica.\n" << "h) Cinema.\n" << "i) Eixir.\n" << endl;
			cin >> opc;
			
			switch (opc)
			{
				case 'a':
					cout << "Introdueix el nou nom de la seguent forma: Cognom, Nom" << endl;
					cin.ignore();
					getline (cin, v[pos].nom);
					aux = v[pos];
					for (i = pos; i < quants - 1; i++)
					{
						v[i] = v[i + 1];
					}
					quants -= 1;
					InserirFitxa (v, quants, aux);
					break;
					
				case 'b':
					cout << "Introdueix el nou correu electronic: " << endl;
					cin >> v[pos].correu;
					break;
					
				case 'c':
					cout << "Introdueix la nova latitud: " << endl;
					cin >> v[pos].latitud;
					break;
					
				case 'd':
					cout << "Introdueix la nova longitud: " << endl;
					cin >> v[pos].longitud;
					break;
					
				case 'e':
					cout << "Introdueix el nou any de naixement: " << endl;
					cin >> v[pos].any;
					break;
					
				case 'f': 
					cout << "Introdueix el nou sexe: " << endl;
					cin >> v[pos].sexe;
					break;
				
				case 'g':
					cout << "Introdueix el nou grau d'interes per la musica (entre 1 i 5): " << endl;
					cin >> v[pos].musica;
					break;	
				
				case 'h': 
					cout << "Introdueix el nou grau d'interes pel cinema (entre 1 i 5): " << endl;
					cin >> v[pos].cinema;
					break;
					
				default:
					if (opc != 'i')
						cout << endl << "Error. Introdueix una de les opcions indicades" << endl;
			} 	
			cout << endl;
			
		} while (opc != 'i');
	}
	else
	{
		cout << "El correu introduit no pertany a ningun usuari." << endl;
	}
	cout << endl;
}



/**********************************************************************/
/* Esborra una fitxa. Rep per referència el nombre d'usuaris, ja que  */
/* serà un de menys                                                   */
/**********************************************************************/

void EsborrarFitxa (usuari v[TAM], int & quants)
{
	string  correu;
	int     posicio;
	int     i;
	
	cout << "Heu escollit eliminar una fitxa. Introduiu el correu electronic de l'usuari que voleu eliminar: " << endl;
	cin.ignore ();
	getline (cin, correu);
		
	if (ComprovarCorreu (v, correu, quants))
	{
		posicio = CercarUsuari (v, quants, correu);
	
		cout << "L'usuari/a " << v[posicio].nom << " ha sigut donat de baixa." << endl;	
		
		for (i = posicio; i < quants - 1; i++)
		{
			v[i] = v[i + 1];
		}
	
		quants -= 1;
	}
	else
	{
		cout << "El correu introduit no pertany a ningun usuari." << endl;
	}
	cout << endl;
}



char MenuSecundari ()
{
	char opc_escollida;
	
	cout << "Escolleix una d'aquestes opcions:\n" << "\ta) Top-5 de persones mes a prop.\n" << "\tb) Top-5 de persones amb interessos comuns en musica i cinema.\n" << endl;
	cin >> opc_escollida;
	
	return (opc_escollida);
}



float DistanciaUsuaris (usuari Usuari_1, usuari Usuari_2)
{
	float res;
	
	res = fabs (Usuari_1.longitud - Usuari_2.longitud) + fabs (Usuari_1.latitud - Usuari_2.latitud);
	
	return res;
}



int CercarPosicio5 (usuari v[TAM], int n, usuari insertat, usuari buscat)
{
	int i = 0;
	
	while (i < n && DistanciaUsuaris (insertat, buscat) > DistanciaUsuaris (v[i], buscat))
	{
		i += 1;
	}
	
	return i;
}

void Inserir (usuari v[TAM], int n, int pos, usuari insertat)
{
	int i;
	
	if (n == 0)
	{
		v[n] = insertat;
		n += 1;
	}
	else
	{
		for (i = n - 1; i >= pos; i--)
		{
			v[i + 1] = v[i];
		}
		v[pos] = insertat;
		n += 1;
	}
}


void InserirOrdenat (usuari v[TAM], int n, usuari insertat, usuari buscat)
{
	int pos;
	
	pos = CercarPosicio5 (v, n, insertat, buscat);
	
	if (pos >= 0 && pos < TAM)
		Inserir (v, n, pos, insertat);
}



/************************************************************/
/* Mostra el topcinc d'usuaris més propers a un introduit   */
/* per l'usuari: inserix tots els usuaris en un vector      */
/* Ordenadament per la distància de Manhattan               */
/************************************************************/

void ProximitatGeografica (usuari v[TAM], int quants)
{
	string  nom;
	usuari  buscat;
	usuari  topcinc [TAM];
	int     i, j, k; 
	bool	canviat = false;
	
	cout << "Has escollit trobar el top-5 de persones mes properes per ubicacio. De quin usuari vols el ranquing? (Introdueix el cognom i nom): ";
	cin.ignore();
	getline (cin, nom);
	
	buscat = v[CercarUsuari2 (v, quants, nom)];
	
	i = 0;
	while (i < quants)
	{
		InserirOrdenat (topcinc, i, v[i], buscat);
		i += 1;
	}
	
	k = 0;		// Eliminem del ranquing a l'usuari que buscàvem
	do
	{		
		if (topcinc[k].nom == buscat.nom)	
		{
			for (j = k; j < quants - 1; j++)
			{
				topcinc [j] = topcinc [j + 1];
				canviat = true;
			}
		}
		k += 1;
	} while (k < quants && canviat == false);
	
	cout << "El Top-5 de persones mes properes a " << buscat.nom << " es:" << endl;
	MostrarLlista (topcinc, 5);
	cout << endl;
}



int AfinitatUsuaris (usuari Usuari_1, usuari Usuari_2)
{
	int res;
	
	res = abs (Usuari_1.musica - Usuari_2.musica) + abs (Usuari_1.cinema - Usuari_2.cinema);
	
	return res;
}



int CercarPosicio4 (usuari v[TAM], int n, usuari insertat, usuari buscat)
{
	int i = 0;
	
	while (i < n && AfinitatUsuaris (insertat, buscat) > AfinitatUsuaris (v[i], buscat))
	{
		i += 1;
	}
	
	return i;
}



void InserirOrdenat2 (usuari v[TAM], int n, usuari insertat, usuari buscat)
{
	int pos;
	
	pos = CercarPosicio4 (v, n, insertat, buscat);
	
	if (pos >= 0 && pos < TAM)
		Inserir (v, n, pos, insertat);
}


void AfinitatGustos (usuari v[TAM], int quants)
{
	string  nom;
	usuari  buscat;
	usuari  topcinc [TAM];
	int     i, j, k; 
	bool	canviat = false;
	
	cout << "Has escollit trobar el top-5 de persones mes afins per gustos (cinema i musica). De quin usuari vols el ranquing? (Introdueix el cognom i nom): ";
	cin.ignore();
	getline (cin, nom);
	
	buscat = v[CercarUsuari2 (v, quants, nom)];
	
	i = 0;
	while (i < quants)
	{
		InserirOrdenat2 (topcinc, i, v[i], buscat);
		i += 1;
	}

		
	k = 0;		//  Eliminem del rànquing a l'usuari que buscàvem.
	do
	{		
		if (topcinc[k].nom == buscat.nom)	
		{
			for (j = k; j < quants - 1; j++)
			{
				topcinc [j] = topcinc [j + 1];
				canviat = true;
			}
		}
		k += 1;
	} while (k < quants && canviat == false);
	
	cout << "El top-5 amb gustos mes propers a " << buscat.nom << " es:" << endl;
	MostrarLlista (topcinc, 5);
	cout << endl;
}



void CercaMulticriteri (usuari v[TAM], int quants)
{
	int     pos;
	int     i, j, k;
	int     mt_dis;  	//  Multiplicador de distància geogràfica
	int     mt_sex;  	// Multiplicador de diferència de sexe
	int     mt_mc;  	//  Multiplicador de similitud d'aficions
	int     mt_edat;  	// Multiplicador de diferència d'edat  
	string  correu;
	usuari  buscat;
	float   dis;		//  Valor de distància geogràfica utilitzat en l'equció final que ens dona l'afinitat entre dos usuaris
	int     dif_edat;		// Diferència d'edat: per a l'equació final
	int     dif_sexe;		// Diferència de sexe: per a l'equació final
	int     af;			// Valor de l'afinitat d'interessos utilitzat en l'equació final
	struct topcinc   llista [TAM];
	struct topcinc   aux;
	bool    canviat = false;
	
	
	cout << "Heu escollit la cerca multicriteri, basada en la distancia geografica, els interessos, l'edat i el sexe. De quin usuari vols trobar el top-5 d'afinitat? (Introdueix el correu)." << endl;
	cin.ignore ();
	getline (cin, correu);
	
	if (ComprovarCorreu (v, correu, quants))
	{
		pos = CercarUsuari (v, quants, correu);
		buscat = v[pos];
			
		do
		{
			cout << "En una escala entre -100 i 100, com valores la proximitat geografica? (-100 significa que prefereixes que visca lluny, 0 significa que et dona igual i 100, que li dones molta importancia a que visca prop):" << endl;
			cin >> mt_dis;
			if (mt_dis < -100 || mt_dis > 100)
			{
				cout << "Error. Introdueix un nombre entre 100 i -100." << endl;
			}
		} while (mt_dis < -100 || mt_dis > 100);	
		
		do
		{
			cout << "En una escala entre -100 i 100, com valores l'afinitat de gustos? (100 significa que li dones molta importancia a que tinga els mateixos interessos que tu, 0 significa que et dona igual i -100, que li dones molta importancia a que tinga aficions molt diferents):" << endl;
			cin >> mt_mc;
			if (mt_mc < -100 || mt_mc > 100)
			{
				cout << "Error. Introdueix un nombre entre 100 i -100." << endl;
			}
		} while (mt_mc < -100 || mt_mc > 100);
		
		do
		{
			cout << "En una escala entre -100 i 100, com valores la proximitat en edat? (-100 significa que li dones molta importancia a que la diferencia d'edat siga maxima, 0 que et dona igual si hi ha molta o poca diferencia d'edat,  i 100, que li dones molta importancia a que la diferencia d'edat siga minima):" << endl;
			cin >> mt_edat;
			if (mt_edat < -100 || mt_edat > 100)
			{
				cout << "Error. Introdueix un nombre entre 100 i -100." << endl;
			}
		} while (mt_edat < -100 || mt_edat > 100);
		
		do
		{
			cout << "En una escala entre -100 i 100, com valores que siga de sexe diferent? (-100 significa que prefereixes que siga del mateix sexe, 0 significa que et dona igual i 100, que li dones molta importancia a que siga de sexe diferent):" << endl;
			cin >> mt_sex;
			if (mt_sex < -100 || mt_sex > 100)
			{
				cout << "Error. Introdueix un nombre entre 100 i -100." << endl;
			}
		} while (mt_sex < -100 || mt_sex > 100);
		
		
		for (i = 0; i < quants; i++)
		{
			dis = DistanciaUsuaris (buscat, v[i]);
			dis =  8 * dis / 260; //		Com la distància màxima de Manhattan a la Terra és aproximadament de 260, i l'afinitat de cinema i música s'expressa en un rang entre 0 i 8, expressem la distància geogràfica en un rang entre 0 i 8 també.
			dis = 8 - dis;  //		Faig la transformació  a la inversa, ja que abans els nombres més petits eren els de més afinitat i vull que siga al revés;
			dis *= mt_dis;
			
			af = AfinitatUsuaris(buscat, v[i]);
			af = 8 - af; //		Faig la transformació  a la inversa, ja que abans els nombres més petits eren els de més afinitat i vull que siga al revés.
			af *= mt_mc;
			
			dif_edat = abs (buscat.any - v[i].any);
			dif_edat = 8 * dif_edat / 70;  //		Igual que en la distància geogràfica, prenent 70 com a diferència d'edat màxima, l'expresse en un rang entre 0 i 8.
			dif_edat = 8 - dif_edat;
			dif_edat *= mt_edat;
			
			if (buscat.sexe != v[i].sexe)
			{
				dif_sexe = 1 * mt_sex;
			}
			else
			{
				dif_sexe = (-1) * mt_sex;
			}
				
			llista[i].nom = v[i].nom;
			llista[i].puntuacio = dif_sexe + dif_edat + af + dis;
		}
		
		for (i = 1; i < quants; i++)		//  Ordenem els usuaris de manera que la puntuació més alta (màxima afinitat) queda el primer
		{
			for (j = 0; j < quants - 1; j++)
			{
				if (llista[j].puntuacio < llista[j + 1].puntuacio)
				{
					aux = llista[j];
					llista [j] = llista [j + 1];
					llista [j + 1] = aux;
				}
			}
		}
		
		
		k = 0;		// Eliminem de la llista d'afinitat al propi usuari del qual busquem afins 
		do
		{		
			if (llista[k].nom == buscat.nom)	
			{
				for (j = k; j < quants - 1; j++)
				{
					llista[j] = llista [j + 1];
				}
				canviat = true;
			}
			k += 1;
		} while (k < quants && canviat == false);	
		
		
		cout << "El top-5 d'usuaris mes afins a " << buscat.nom << " es:" << endl;
		for (i = 0; i < 5; i++)
		{
			cout << llista[i].nom << endl;
		}	
		cout << endl;
	}
	else
	{
		cout << "El correu introduit no pertany a ningun usuari." << endl;
		cout << endl;
	}
}



void FinalPrograma (usuari v[TAM], int quants)
{
	string   resp;
	int      i;
	ofstream g;
	
	cout << "Heu escollit ixir del programa. Voleu guardar tots els canvis que s'han realitzat en les dades dels usuaris?" << endl;
	
	do
	{
		cin >> resp;
		if (resp != "si" && resp != "Si" && resp != "no" && resp != "No" )
			cout << "Error. Introdueix una resposta valida." << endl;
	} while (resp != "si" && resp != "Si" && resp != "no" && resp != "No");
	
	
	if (resp == "si" || resp == "Si")
	{
		g.open ("usuarisfis.txt");
		if (!g)
			cout << "Error obrint el fitxer." << endl;
		else
		{
			for (i = 0; i < quants; i++)
			{
				g << v[i].nom << endl;
				g << v[i].correu << endl;
				g << v[i].latitud << "\t" << v[i].longitud << "\t" << v[i].any << "\t" << v[i].sexe << endl;
				g << v[i].musica << "\t" << v[i].cinema << endl;
			}
		}
		g.close();
		cout << "Els canvis en el fitxer d'usuaris s'han guardat correctament." << endl;
	}
	cout << endl << "\t\t\t\t\t\tFI DEL PROGRAMA" << endl;
	cout << endl;
}
