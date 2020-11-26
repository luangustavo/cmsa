#include <ilcplex/ilocplex.h>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "SmallestEnclosingCircle.hpp"

using namespace std;

ILOSTLBEGIN

static void Exato(vector <Point> points, vector <Disco> discos, vector <Tupla> tuplas, vector<vector<int>> C)
{
	IloEnv env;

	try
	{
		double time = 900.0; //15 min
		//double memory = 1000.0;
		
		//vector<double> Px;
		//vector<double> Py;
		//vector<double> custos;
		//vector<double> raios;

		float max_x, max_y;
		max_x = 0;
		max_y = 0;

		string line, x_txt, y_txt, custos_txt, raios_txt;

		/*
		//Lendo o arquivo de pontos
		ifstream filePontos("entrada_pontos.txt");
		if (filePontos.is_open())
		{
			while (!filePontos.eof())
			{
				getline(filePontos, line);

				x_txt = line.substr(0, line.find(","));
				Px.insert(Px.end(), stof(x_txt));

				if (max_x < stof(x_txt)) {
					max_x = stof(x_txt);
				}

				y_txt = line.substr(x_txt.length() + 1, line.length());
				Py.insert(Py.end(), stof(y_txt));

				if (max_y < stof(y_txt)) {
					max_y = stof(y_txt);
				}
			}
			filePontos.close();
		}

		else cout << "Unable to open file";

		//Lendo o arquivo de antenas
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

		for (int i = 0; i < points.size(); i++) {
			if (max_x < points[i].x) {
				max_x = points[i].x;
			}
			if (max_y < points[i].y) {
				max_y = points[i].y;
			}
		}

		int n_ant = discos.size(); // num de antenas
		int n_pon = points.size(); // num de pontos
		int n_tuplas = tuplas.size(); // num de tuplas
		//int n_c = C[points[].id].size();


		// create model

		IloModel antena(env, "Problema da Antenas");
		IloCplex cplex(antena);

		//Limites de Tempo e Mem�ria

		cplex.setParam(IloCplex::TiLim, time);
		//cplex.setParam(IloCplex::TreLim, memory);

		// Criando as vari�veis bin�rias
		IloIntVarArray z(env, n_tuplas, 0, 1);
		IloNumVarArray x(env, n_ant, 0, max_x);
		IloNumVarArray y(env, n_ant, 0, max_y);

		IloArray<IloIntVarArray> p(env, n_ant);
		for (int i = 0;i < n_ant;i++)
			p[i] = IloIntVarArray(env, n_pon, 0, 1); // Cria��o vari�veis p[i][j]

		/*
		// Fun��o Objetivo
		IloExpr obj(env);
		for (int i = 0; i < n_ant; i++)
			//obj += custos[i] * z[i];
			obj += discos[i].custo * z[i];
		antena.add(IloMinimize(env, obj));
		*/

		// Fun��o Objetivo
		IloExpr obj(env);
		for (int j = 0; j < n_tuplas; j++)
			//obj += custos[i] * z[i];
			obj += discos[tuplas[j].disco].custo * z[j];
		antena.add(IloMinimize(env, obj));

		/*
		// Restri��o Dist�ncia
		for (int i = 0; i < n_ant; i++)
			for (int j = 0;j < n_pon;j++)
			{
				antena.add(((Px[j] - x[i]) * (Px[j] - x[i])) + ((Py[j] - y[i]) * (Py[j] - y[i])) <=
					(raios[i] * raios[i] * p[i][j]) + (max_x * max_x * (1 - p[i][j])));
			}

		*/

		// Cada ponto deve ser atendido por uma antena
		for (int j = 0;j < n_c;j++)
		{
			IloExpr obj(env);
			for (int i = 0; i < n_ant; i++)
				obj += p[i][j];
			antena.add(obj >= 1);
		}

		// Cada ponto deve ser atendido por uma antena
		for (int j = 0;j < n_pon;j++)
		{
			IloExpr obj(env);
			for (int i = 0; i < n_ant; i++)
				obj += p[i][j];
			antena.add(obj >= 1);
		}

		// Se um ponto j � coberto pela antena i ent�o a antena i est� sendo utilizada
		for (int i = 0; i < n_ant; i++)
			for (int j = 0;j < n_pon;j++)
			{
				antena.add(p[i][j] <= z[i]);
			}


		if (cplex.solve())
			env.out() << "Valor �timo "
			<< cplex.getObjValue() << endl;

		IloNumArray sol(env, n_ant);
		cplex.getValues(sol, z);

		for (int i = 0; i < n_ant; i++)
		{
			IloNum sol_x = cplex.getValue(x[i]);
			IloNum sol_y = cplex.getValue(y[i]);

			if (sol[i] == 1) {
				cout << "Antena " << i + 1 << ": " << "(" << sol_x << " , " << sol_y << ")" << endl;
				cout << "Pontos cobertos: " << endl;
				for (int j = 0; j < n_pon; j++) {
					if (cplex.getValue(p[i][j]) == 1) {
						cout << "- p" << j + 1 << endl;
					}

				}
			}
		}

	}
	catch (const IloException & e)
	{
		cerr << "Exception caught: " << e << endl;
#ifdef FULLTEST
		assert(0);
#endif
	}
	catch (...)
	{
		cerr << "Unknown exception caught!" << endl;
#ifdef FULLTEST
		assert(0);
#endif
	}

	env.end();
	
	//return 0;
}