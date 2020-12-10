#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <random>
#include "SmallestEnclosingCircle.hpp"
#include <string>
#include <fstream>
#include "exato.cpp"
using namespace std;

using std::size_t;
using std::vector;

// Random number generation global variables
static std::default_random_engine randGen((std::random_device())());
static std::normal_distribution<double> normalDist;

static const double EPSILON = 1e-12;

vector<Tupla> D_line;

Tupla d;

vector<Disco> discos;

int id_aux_d = 0;

vector <vector <int>> C;

int welz(vector<Point> points, double x_max, double y_max, double x_min, double y_min) {

	//Valores proporcionais
	double metade_x = (x_max - x_min) / 2;
	double metade_y = (y_max - y_min) / 2;
	
	/*
	int max_int_x = floor(metade_x); //arredondar para baixo
	int min_int_x = ceil(x_min); //arredondar para cima

	int max_int_y = floor(metade_y); //arredondar para baixo
	int min_int_y = ceil(y_min); //arredondar para cima

	*/

	int max_int_x = floor(x_max); //arredondar para baixo
	int min_int_x = ceil(x_min); //arredondar para cima

	int max_int_y = floor(y_max); //arredondar para baixo
	int min_int_y = ceil(y_min); //arredondar para cima

	double rand1 = metade_x + x_min;
	double rand2 = metade_y + y_min;
	double rand3 = metade_x + x_min;

	if (min_int_x < max_int_x) {
		if (max_int_x - min_int_x > 4) {
			rand1 = rand() % (max_int_x - min_int_x + 1) + min_int_x;
			rand2 = rand() % (max_int_y - min_int_y + 1) + min_int_y;
			rand3 = rand() % (max_int_x - min_int_x + 1) + min_int_x;

			//std::cout << rand1 << "-" << rand2 << "-" << rand3 << std::endl;
		}

	}

	//std::cout << max_int_y << "-" << min_int_y << "-" << min_int_x << "-" << max_int_x << std::endl;
	
	//rand1 = rand(xmin ate xmax);
	//rand2 = rand(ymin ate ymax);
	//rand3 = rand(xmin ate xmax);

	/*
		Etapas de dividir

		Q1: XminQ1 = Xmin, XmaxQ1 = rand(Xmin até Xmax) | YminQ1 = Ymin, YmaxQ1 = rand(Ymin até Ymax)
		|RESTO
		V
		Q2: XminQ2 = XmaxQ1, XmaxQ2 = Xmax | YminQ2 = Ymin, YmaxQ2 = YmaxQ1
		Q3: XminQ3 = Xmin, XmaxQ3 = rand(Xmin até Xmax) | YminQ3 = YmaxQ1, YmaxQ3 = Ymax
		|RESTO
		V
		Q4: XminQ4 = XmaxQ3, XmaxQ4 = Xmax | YminQ4 = YmaxQ1, YmaxQ4 = Ymax

		Se no quadrante não houver pontos retorna.
	*/

	double XminQ1 = x_min, YminQ1 = y_min, XmaxQ1 = rand1, YmaxQ1 = rand2;
	double XminQ2 = XmaxQ1, YminQ2 = y_min, XmaxQ2 = x_max, YmaxQ2 = YmaxQ1;
	double XminQ3 = x_min, YminQ3 = YmaxQ1, XmaxQ3 = rand3, YmaxQ3 = y_max;
	double XminQ4 = XmaxQ3, YminQ4 = YmaxQ1, XmaxQ4 = x_max, YmaxQ4 = y_max;

	/*
	double aux_max_x_1 = x_min + metade_x, aux_max_x_2 = x_max, aux_max_x_3 = x_min + metade_x, aux_max_x_4 = x_max;
	double aux_max_y_1 = y_max, aux_max_y_2 = y_max, aux_max_y_3 = metade_y, aux_max_y_4 = metade_y;

	double aux_min_x_1 = x_min, aux_min_x_2 = x_min + metade_x, aux_min_x_3 = x_min, aux_min_x_4 = x_min + metade_x;
	double aux_min_y_1 = y_min + metade_y, aux_min_y_2 = y_min + metade_y, aux_min_y_3 = y_min, aux_min_y_4 = y_min;
	*/

	vector<Point> quad1, quad2, quad3, quad4;

	for (int i = 0; i < points.size(); i++) {

		if ((points[i].x >= XminQ1 && points[i].x <= XmaxQ1) && (points[i].y >= YminQ1 && points[i].y <= YmaxQ1)) {

			quad1.insert(quad1.end(), points[i]);

		}
		else if ((points[i].x >= XminQ2 && points[i].x <= XmaxQ2) && (points[i].y >= YminQ2 && points[i].y <= YmaxQ2)) {

			quad2.insert(quad2.end(), points[i]);

		}
		else if ((points[i].x >= XminQ3 && points[i].x <= XmaxQ3) && (points[i].y >= YminQ3 && points[i].y <= YmaxQ3)) {

			quad3.insert(quad3.end(), points[i]);

		}
		else if ((points[i].x >= XminQ4 && points[i].x <= XmaxQ4) && (points[i].y >= YminQ4 && points[i].y <= YmaxQ4)) {

			quad4.insert(quad4.end(), points[i]);

		}

	}

	if (quad1.size() > 1) {

		if (makeSmallestEnclosingCircle(quad1).c.x != NULL) {

			Circle smallest = makeSmallestEnclosingCircle(quad1);

			/*
			std::cout << rand1 << "-" << rand2 << "-" << rand3 << "> QUAD1 > X: " << smallest.c.x
				<< ", Y: " << smallest.c.y
				<< ", R: " << smallest.r << std::endl;
			*/

			//Verificar se o disco possui raio >= raio do smallestCircle

			for (int i = 0; i < discos.size(); i++) {
				if (discos[i].raio >= smallest.r) {

					//comecar do id 0
					//d.id = id_aux_d+1;
					d.id = id_aux_d;
					d.disco = i;
					d.points = quad1;
					d.pos.x = smallest.c.x;
					d.pos.y = smallest.c.y;

					for (int j = 0; j < quad1.size(); j++) {

						//C eh um vetor de vetores
						C[quad1[j].id].push_back(d.id);
					}

					D_line.insert(D_line.end(), d);

					discos[i].R.insert(discos[i].R.end(), d.id);

					/*
					std::cout << "====> ID: " << d.id
						<< ", DISCO: " << discos[i].id
						<< ", R: " << discos[i].raio
						<< std::endl;
					*/

					id_aux_d++;
				}
			}


		}

		welz(quad1, XmaxQ1, YmaxQ1, XminQ1, YminQ1);


	}
	//std::cout << "SAINDO..." <<  std::endl;
	if (quad2.size() > 1) {

		if (makeSmallestEnclosingCircle(quad2).c.x != NULL) {

			Circle smallest = makeSmallestEnclosingCircle(quad2);

			/*
			std::cout << rand1 << "-" << rand2 << "-" << rand3 << "> QUAD2 > X: " << smallest.c.x
				<< ", Y: " << smallest.c.y
				<< ", R: " << smallest.r << std::endl;
			*/
			//Verificar se o disco possui raio >= raio do smallestCircle

			for (int i = 0; i < discos.size(); i++) {
				if (discos[i].raio >= smallest.r) {

					d.id = id_aux_d;
					d.disco = i;
					d.points = quad2;
					d.pos.x = smallest.c.x;
					d.pos.y = smallest.c.y;

					for (int j = 0; j < quad2.size(); j++) {

						//C eh um vetor de vetores
						C[quad2[j].id].push_back(d.id);
					}

					D_line.insert(D_line.end(), d);

					discos[i].R.insert(discos[i].R.end(), d.id);

					/*
					std::cout << "====> ID: " << d.id
						<< ", DISCO: " << discos[i].id
						<< ", R: " << discos[i].raio
						<< std::endl;
					*/

					id_aux_d++;
				}
			}

		}

		welz(quad2, XmaxQ2, YmaxQ2, XminQ2, YminQ2);

	}
	//std::cout << "SAINDO..." << std::endl;
	if (quad3.size() > 1) {

		if (makeSmallestEnclosingCircle(quad3).c.x != NULL) {

			Circle smallest = makeSmallestEnclosingCircle(quad3);

			/*
			std::cout << rand1 << "-" << rand2 << "-" << rand3 << "> QUAD3 > X: " << smallest.c.x
				<< ", Y: " << smallest.c.y
				<< ", R: " << smallest.r << std::endl;
			*/
			//Verificar se o disco possui raio >= raio do smallestCircle

			for (int i = 0; i < discos.size(); i++) {
				if (discos[i].raio >= smallest.r) {

					d.id = id_aux_d;
					d.disco = i;
					d.points = quad3;
					d.pos.x = smallest.c.x;
					d.pos.y = smallest.c.y;

					for (int j = 0; j < quad3.size(); j++) {

						//C eh um vetor de vetores
						C[quad3[j].id].push_back(d.id);
					}

					D_line.insert(D_line.end(), d);

					discos[i].R.insert(discos[i].R.end(), d.id);

					/*
					std::cout << "====> ID: " << d.id
						<< ", DISCO: " << discos[i].id
						<< ", R: " << discos[i].raio
						<< std::endl;
					*/

					id_aux_d++;
				}
			}

		}

		welz(quad3, XmaxQ3, YmaxQ3, XminQ3, YminQ3);
	}
	//std::cout << "SAINDO..." << std::endl;
	if (quad4.size() > 1) {

		if (makeSmallestEnclosingCircle(quad4).c.x != NULL) {

			Circle smallest = makeSmallestEnclosingCircle(quad4);

			/*
			std::cout << rand1 << "-" << rand2 << "-" << rand3 << "> QUAD4 > X: " << smallest.c.x
				<< ", Y: " << smallest.c.y
				<< ", R: " << smallest.r << std::endl;
			*/

			//Verificar se o disco possui raio >= raio do smallestCircle

			for (int i = 0; i < discos.size(); i++) {
				if (discos[i].raio >= smallest.r) {

					d.id = id_aux_d;
					d.disco = i;
					d.points = quad4;
					d.pos.x = smallest.c.x;
					d.pos.y = smallest.c.y;

					for (int j = 0; j < quad4.size(); j++) {

						//C eh um vetor de vetores
						C[quad4[j].id].push_back(d.id);
					}

					D_line.insert(D_line.end(), d);

					discos[i].R.insert(discos[i].R.end(), d.id);

					/*
					std::cout << "====> ID: " << d.id
						<< ", DISCO: " << discos[i].id
						<< ", R: " << discos[i].raio
						<< std::endl;
					*/

					id_aux_d++;
				}
			}

		}

		welz(quad4, XmaxQ4, YmaxQ4, XminQ4, YminQ4);
	}

	return 0;

}

int main() {

	//double memory = 1000.0;
	//vector<double> Px;
	//vector<double> Py;

	Disco disco;

	int id_aux = 0;
	//vector<double> custos;
	//vector<double> raios;

	float max_x, max_y;
	max_x = 0;
	max_y = 0;

	string line, x1_txt, x_txt, y_txt, custos_txt, raios_txt;

	vector<Point> points;

	Point point;

	//Lendo o arquivo de pontos
	ifstream filePontos("entrada_pontos.txt");
	if (filePontos.is_open())
	{
		while (!filePontos.eof())
		{
			getline(filePontos, line);

			/*
				Monaliza

			x1_txt = line.substr(0, line.find(" "));
			x_txt = line.substr(x1_txt.length() + 1, line.length());
			x_txt = x_txt.substr(0, x_txt.find(" "));
			//Px.insert(Px.end(), stof(x_txt));

			if (max_x < stof(x_txt)) {
				max_x = stof(x_txt);
			}

			y_txt = line.substr(x1_txt.length() + x_txt.length() + 2, line.length());

			//Py.insert(Py.end(), stof(y_txt));

			if (max_y < stof(y_txt)) {
				max_y = stof(y_txt);
			}
			*/

			x_txt = line.substr(0, line.find(","));
			//Px.insert(Px.end(),stof(x_txt));

			if (max_x < stof(x_txt)) {
				max_x = stof(x_txt);
			}

			y_txt = line.substr(x_txt.length() + 1, line.length());
			//Py.insert(Py.end(), stof(y_txt));

			if (max_y < stof(y_txt)) {
				max_y = stof(y_txt);
			}

			point.x = stof(x_txt);
			point.y = stof(y_txt);
			point.id = id_aux;

			points.insert(points.end(), point);
			id_aux++;
		}
		filePontos.close();
	}

	else cout << "Unable to open file";

	C.resize(id_aux);

	id_aux = 0;
	//Lendo o arquivo de antenas
	ifstream fileDiscos("entrada_antenas.txt");
	if (fileDiscos.is_open())
	{
		while (!fileDiscos.eof())
		{
			getline(fileDiscos, line);

			raios_txt = line.substr(0, line.find(","));

			disco.raio = stof(raios_txt);

			//raios.insert(raios.end(), stof(raios_txt));

			custos_txt = line.substr(raios_txt.length() + 1, line.length());

			disco.custo = stof(custos_txt);

			disco.id = id_aux;

			discos.insert(discos.end(), disco);

			//custos.insert(custos.end(), stof(custos_txt));

			id_aux++;

		}
		fileDiscos.close();
	}

	else cout << "Unable to open file";

	int qtd_discos = 0;

	/*
	d.id = 0;
	d.disco = antenas[0].id;
	d.points = points;

	D_line.insert(D_line.end(), d);
	*/

	/*
	while (1) {

		unsigned seed = time(0);

		srand(seed);

		double rand1 = rand() % (30 - 1 + 1) + 1;
		double rand2 = rand() % (100 - 50 + 1) + 50;
		double rand3 = rand() % (150 - 120 + 1) + 120;

		std::cout << "R1: " << rand1 << " | R2: " << rand2 << " | R3: " << rand3 << std::endl;

	}
	*/
	
	double valor_otimo = INT_MAX, valor_exato = NULL;

	unsigned seed = time(0);

	srand(seed);

	while (1) {
		//Welz
		welz(points, max_x, max_y, 0, 0);

		/*
		std::cout << "R1: (";
		for (int i = 0; i < discos[0].R.size(); i++)
		{
			std::cout << discos[0].R[i] << ", ";

		}
		std::cout << ")" << std::endl;
		*/

		/*
		for (int i = 0; i < C.size(); i++) {
			std::cout << i << "{";
			for (int j = 0; j < C[i].size(); j++) {

				//C eh um vetor de vetores
				std::cout << C[i][j] << ", ";
			}
			std::cout << "}" << std::endl;
		}
		*/

		valor_exato = Exato(points, discos, D_line, C);

		if (valor_exato != NULL ) {
			if (valor_exato <= valor_otimo) {
				valor_otimo = valor_exato;
			}

		}
	}
	return EXIT_SUCCESS;

}