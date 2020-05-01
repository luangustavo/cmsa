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


int welz(vector<Point> points, double x_max, double y_max, double x_min, double y_min) {

	double metade_x = (x_max - x_min) / 2;
	double metade_y = (y_max - y_min) / 2;

	double aux_max_x_1 = x_min + metade_x, aux_max_x_2 = x_max, aux_max_x_3 = x_min + metade_x, aux_max_x_4 = x_max;
	double aux_max_y_1 = y_max, aux_max_y_2 = y_max, aux_max_y_3 = metade_y, aux_max_y_4 = metade_y;

	double aux_min_x_1 = x_min, aux_min_x_2 = x_min + metade_x, aux_min_x_3 = x_min, aux_min_x_4 = x_min + metade_x;
	double aux_min_y_1 = y_min + metade_y, aux_min_y_2 = y_min + metade_y, aux_min_y_3 = y_min, aux_min_y_4 = y_min;


	int teste = 0;

	if (points.size() > 0 && points.size() <= 3) {

		std::cout << "2 - " << points.size() << std::endl;

		if (makeSmallestEnclosingCircle(points).c.x != NULL) {

			std::cout << makeSmallestEnclosingCircle(points).c.x << std::endl;
			std::cout << makeSmallestEnclosingCircle(points).c.y << std::endl;
			std::cout << makeSmallestEnclosingCircle(points).r << std::endl;

		}
	}
	else if (points.size() > 3) {

		vector<Point> quad1, quad2, quad3, quad4;
		/*
			Etapas de dividir

			1: [0, Xmax/2], [Ymax/2, Ymax]
			2: [Xmax/2, Xmax], [Ymax/2, Ymax]
			3: [0, Xmax/2], [0, Ymax/2]
			4: [Xmax/2, Xmax], [0, Ymax/2]

			Se no quadrante não houver pontos retorna.
		*/

		std::cout << x_max << " - " << metade_x << " - " << metade_y << std::endl;

		for (int i = 0; i < points.size(); i++) {

			teste = 1;

			if ((points[i].x >= x_min && points[i].x <= x_min + metade_x) && (points[i].y >= y_min + metade_y && points[i].y <= y_max)) {

				teste = 2;

				quad1.insert(quad1.end(), points[i]);

				/*if (points[i].x > aux_max_x_1) {
					aux_max_x_1 = points[i].x;
				}

				if (points[i].y > aux_max_y_1) {
					aux_max_y_1 = points[i].y;
				}

				if (points[i].x < aux_min_x_1) {
					aux_min_x_1 = points[i].x;
				}

				if (points[i].y < aux_min_y_1) {
					aux_min_y_1 = points[i].y;
				}*/
			}
			else if ((points[i].x >= x_min + metade_x && points[i].x <= x_max) && (points[i].y >= y_min + metade_y && points[i].y <= y_max)) {

				teste = aux_min_x_2;

				quad2.insert(quad2.end(), points[i]);

				/*if (points[i].x > aux_max_x_2) {
					aux_max_x_2 = points[i].x;
				}

				if (points[i].y > aux_max_y_2) {
					aux_max_y_2 = points[i].y;
				}

				if (points[i].x < aux_min_x_2) {
					aux_min_x_2 = points[i].x;
					teste = 3;
				}

				if (points[i].y < aux_min_y_2) {
					aux_min_y_2 = points[i].y;
				}*/
			}
			else if ((points[i].x >= x_min && points[i].x <= x_min + metade_x) && (points[i].y >= y_min && points[i].y <= y_min + metade_y)) {

				teste = 2;

				quad3.insert(quad3.end(), points[i]);

				/*if (points[i].x > aux_max_x_3) {
					aux_max_x_3 = points[i].x;
				}

				if (points[i].y > aux_max_y_3) {
					aux_max_y_3 = points[i].y;
				}

				if (points[i].x < aux_min_x_3) {
					aux_min_x_3 = points[i].x;
				}

				if (points[i].y < aux_min_y_3) {
					aux_min_y_3 = points[i].y;
				}*/
			}
			else if ((points[i].x >= x_min + metade_x && points[i].x <= x_max) && (points[i].y >= y_min && points[i].y <= y_min + metade_y)) {

				teste = 2;

				quad4.insert(quad4.end(), points[i]);

				/*if (points[i].x > aux_max_x_4) {
					aux_max_x_4 = points[i].x;
				}

				if (points[i].y > aux_max_y_4) {
					aux_max_y_4 = points[i].y;
				}

				if (points[i].x < aux_min_x_4) {
					aux_min_x_4 = points[i].x;
				}

				if (points[i].y < aux_min_y_4) {
					aux_min_y_4 = points[i].y;
				}*/
			}

		}

		if (quad1.size() > 0) {

			std::cout << "1 - " << quad1.size() << " - " << aux_max_x_1 << std::endl;
			std::cout << quad1[0].x << std::endl;

			if (makeSmallestEnclosingCircle(quad1).c.x != NULL) {
				std::cout << makeSmallestEnclosingCircle(quad1).c.x << std::endl;
				std::cout << makeSmallestEnclosingCircle(quad1).c.y << std::endl;
				std::cout << makeSmallestEnclosingCircle(quad1).r << std::endl;


			}

			welz(quad1, aux_max_x_1, aux_max_y_1, aux_min_x_1, aux_min_y_1);
			std::cout << "teste1" << std::endl;


		}

		if (quad2.size() > 0) {

			std::cout << "2 - " << quad2.size() << " - " << aux_min_x_2 << std::endl;
			std::cout << quad2[0].x << std::endl;

			if (makeSmallestEnclosingCircle(quad2).c.x != NULL) {

				std::cout << makeSmallestEnclosingCircle(quad2).c.x << std::endl;
				std::cout << makeSmallestEnclosingCircle(quad2).c.y << std::endl;
				std::cout << makeSmallestEnclosingCircle(quad2).r << std::endl;

			}

			welz(quad2, aux_max_x_2, aux_max_y_2, aux_min_x_2, aux_min_y_2);
			std::cout << "teste2" << std::endl;

		}

		if (quad3.size() > 0) {

			std::cout << "3 - " << quad3.size() << std::endl;
			std::cout << quad3[0].x << std::endl;

			if (makeSmallestEnclosingCircle(quad3).c.x != NULL) {

				std::cout << makeSmallestEnclosingCircle(quad3).c.x << std::endl;
				std::cout << makeSmallestEnclosingCircle(quad3).c.y << std::endl;
				std::cout << makeSmallestEnclosingCircle(quad3).r << std::endl;

			}

			welz(quad3, aux_max_x_3, aux_max_y_3, aux_min_x_3, aux_min_y_3);
			std::cout << "teste3" << std::endl;
		}

		if (quad4.size() > 0) {

			std::cout << "4 - " << quad4.size() << std::endl;
			std::cout << quad4[0].x << std::endl;

			if (makeSmallestEnclosingCircle(quad4).c.x != NULL) {

				std::cout << makeSmallestEnclosingCircle(quad4).c.x << std::endl;
				std::cout << makeSmallestEnclosingCircle(quad4).c.y << std::endl;
				std::cout << makeSmallestEnclosingCircle(quad4).r << std::endl;

			}
			welz(quad4, aux_max_x_4, aux_max_y_4, aux_min_x_4, aux_min_y_4);
			std::cout << "teste4" << std::endl;
		}

	}
	else {
		std::cout << "teste" << std::endl;
	}
	return 0;
	
}



int main() {



	//double memory = 1000.0;
	vector<double> Px;
	vector<double> Py;
	vector<double> custos;
	vector<double> raios;

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

	/*
	//Lendo o arquivo de pontos
	ifstream fileAntenas("entrada_antenas.txt");
	if (fileAntenas.is_open())
	{
		while (!fileAntenas.eof())
		{
			getline(fileAntenas, line);

			raios_txt = line.substr(0, line.find(","));

			raios.insert(raios.end(), stof(raios_txt));

			custos_txt = line.substr(raios_txt.length() + 1, line.length());

			custos.insert(custos.end(), stof(custos_txt));

		}
		fileAntenas.close();
	}

	else cout << "Unable to open file";
	*/



	/*Welz*/
	welz(points, max_x, max_y, 0, 0);
	
	return EXIT_SUCCESS;
	
}


