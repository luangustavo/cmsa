#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <random>
#include "SmallestEnclosingCircle.hpp"
#include <string>
#include <fstream>
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

int welz(vector<Point> points, double x_max, double y_max, double x_min, double y_min) {

	//Valores proporcionais
	double metade_x = (x_max - x_min) / 2;
	double metade_y = (y_max - y_min) / 2;

	double aux_max_x_1 = x_min + metade_x, aux_max_x_2 = x_max, aux_max_x_3 = x_min + metade_x, aux_max_x_4 = x_max;
	double aux_max_y_1 = y_max, aux_max_y_2 = y_max, aux_max_y_3 = metade_y, aux_max_y_4 = metade_y;

	double aux_min_x_1 = x_min, aux_min_x_2 = x_min + metade_x, aux_min_x_3 = x_min, aux_min_x_4 = x_min + metade_x;
	double aux_min_y_1 = y_min + metade_y, aux_min_y_2 = y_min + metade_y, aux_min_y_3 = y_min, aux_min_y_4 = y_min;

	vector<Point> quad1, quad2, quad3, quad4;
	/*
		Etapas de dividir

		1: [0, Xmax/2], [Ymax/2, Ymax]
		2: [Xmax/2, Xmax], [Ymax/2, Ymax]
		3: [0, Xmax/2], [0, Ymax/2]
		4: [Xmax/2, Xmax], [0, Ymax/2]

		Se no quadrante não houver pontos retorna.
	*/

	for (int i = 0; i < points.size(); i++) {

		if ((points[i].x >= x_min && points[i].x <= x_min + metade_x) && (points[i].y >= y_min + metade_y && points[i].y <= y_max)) {

			quad1.insert(quad1.end(), points[i]);

		}
		else if ((points[i].x >= x_min + metade_x && points[i].x <= x_max) && (points[i].y >= y_min + metade_y && points[i].y <= y_max)) {

			quad2.insert(quad2.end(), points[i]);
				
		}
		else if ((points[i].x >= x_min && points[i].x <= x_min + metade_x) && (points[i].y >= y_min && points[i].y <= y_min + metade_y)) {

			quad3.insert(quad3.end(), points[i]);
				
		}
		else if ((points[i].x >= x_min + metade_x && points[i].x <= x_max) && (points[i].y >= y_min && points[i].y <= y_min + metade_y)) {

			quad4.insert(quad4.end(), points[i]);

		}

	}

	if (quad1.size() > 1) {

		if (makeSmallestEnclosingCircle(quad1).c.x != NULL) {

			Circle smallest = makeSmallestEnclosingCircle(quad1);

			std::cout << "> X: " << smallest.c.x
				<< ", Y: " << smallest.c.y
				<< ", R: " << smallest.r << std::endl;

			//Verificar se o disco possui raio >= raio do smallestCircle

			for (int i = 0; i < discos.size(); i++) {
				if (discos[i].raio >= smallest.r) {

					d.id = id_aux_d+1;
					d.disco = i;
					d.points = quad1;

					D_line.insert(D_line.end(), d);

					discos[i].R.insert(discos[i].R.end(), d.id);

					std::cout << "====> ID: " << d.id
						<< ", DISCO: " << discos[i].id
						<< ", R: " << discos[i].raio
						<< std::endl;

					id_aux_d++;
				}
			}


		}

		welz(quad1, aux_max_x_1, aux_max_y_1, aux_min_x_1, aux_min_y_1);


	}

	if (quad2.size() > 1) {

		if (makeSmallestEnclosingCircle(quad2).c.x != NULL) {

			Circle smallest = makeSmallestEnclosingCircle(quad2);

			std::cout << "> X: " << smallest.c.x
				<< ", Y: " << smallest.c.y
				<< ", R: " << smallest.r << std::endl;

			//Verificar se o disco possui raio >= raio do smallestCircle

			for (int i = 0; i < discos.size(); i++) {
				if (discos[i].raio >= smallest.r) {

					d.id = id_aux_d + 1;
					d.disco = i;
					d.points = quad2;

					D_line.insert(D_line.end(), d);

					discos[i].R.insert(discos[i].R.end(), d.id);

					std::cout << "====> ID: " << d.id
						<< ", DISCO: " << discos[i].id
						<< ", R: " << discos[i].raio
						<< std::endl;

					id_aux_d++;
				}
			}

		}

		welz(quad2, aux_max_x_2, aux_max_y_2, aux_min_x_2, aux_min_y_2);

	}

	if (quad3.size() > 1) {

		if (makeSmallestEnclosingCircle(quad3).c.x != NULL) {

			Circle smallest = makeSmallestEnclosingCircle(quad3);

			std::cout << "> X: " << smallest.c.x
				<< ", Y: " << smallest.c.y
				<< ", R: " << smallest.r << std::endl;

			//Verificar se o disco possui raio >= raio do smallestCircle

			for (int i = 0; i < discos.size(); i++) {
				if (discos[i].raio >= smallest.r) {

					d.id = id_aux_d + 1;
					d.disco = i;
					d.points = quad3;

					D_line.insert(D_line.end(), d);

					discos[i].R.insert(discos[i].R.end(), d.id);

					std::cout << "====> ID: " << d.id
						<< ", DISCO: " << discos[i].id
						<< ", R: " << discos[i].raio
						<< std::endl;

					id_aux_d++;
				}
			}

		}

		welz(quad3, aux_max_x_3, aux_max_y_3, aux_min_x_3, aux_min_y_3);
	}

	if (quad4.size() > 1) {

		if (makeSmallestEnclosingCircle(quad4).c.x != NULL) {

			Circle smallest = makeSmallestEnclosingCircle(quad4);

			std::cout << "> X: " << smallest.c.x
				<< ", Y: " << smallest.c.y
				<< ", R: " << smallest.r << std::endl;

			//Verificar se o disco possui raio >= raio do smallestCircle

			for (int i = 0; i < discos.size(); i++) {
				if (discos[i].raio >= smallest.r) {

					d.id = id_aux_d + 1;
					d.disco = i;
					d.points = quad4;

					D_line.insert(D_line.end(), d);

					discos[i].R.insert(discos[i].R.end(), d.id);

					std::cout << "====> ID: " << d.id
						<< ", DISCO: " << discos[i].id
						<< ", R: " << discos[i].raio
						<< std::endl;

					id_aux_d++;
				}
			}

		}

		welz(quad4, aux_max_x_4, aux_max_y_4, aux_min_x_4, aux_min_y_4);
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

			y_txt = line.substr(x_txt.length()+1,line.length());
			//Py.insert(Py.end(), stof(y_txt));

			if (max_y < stof(y_txt)) {
				max_y = stof(y_txt);
			}

			point.x = stof(x_txt);
			point.y = stof(y_txt);
			
			points.insert(points.end(), point);
		}
		filePontos.close();
	}

	else cout << "Unable to open file";

	
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

	//Welz
	welz(points, max_x, max_y, 0, 0);
	
	std::cout << "R1: (";
	for (int i = 0; i < discos[0].R.size(); i++)
	{
		std::cout << discos[0].R[i] << ", ";
			
	}
	std::cout << ")" << std::endl;
	return EXIT_SUCCESS;
	
}


