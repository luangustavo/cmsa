#include <ilcplex/ilocplex.h>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "SmallestEnclosingCircle.hpp"

using namespace std;

ILOSTLBEGIN

static double Exato(vector <Point> points, vector <Disco> discos, vector <Tupla> tuplas, vector<vector<int>> C)
{
	double valor_otimo = NULL;
	std::cout << points.size() << " = " << " - " << C.size() << std::endl;
	
	IloEnv env;

	try
	{
		double time = 900.0; //15 min
		//double memory = 1000.0;
		
		//vector<double> Px;
		//vector<double> Py;
		//vector<double> custos;
		//vector<double> raios;
		
		/*
		float max_x, max_y;
		max_x = 0;
		max_y = 0;
		
		string line, x_txt, y_txt, custos_txt, raios_txt;

		for (int i = 0; i < points.size(); i++) {
			if (max_x < points[i].x) {
				max_x = points[i].x;
			}
			if (max_y < points[i].y) {
				max_y = points[i].y;
			}
		}
		*/

		int n_ant = discos.size(); // num de antenas
		int n_pon = points.size(); // num de pontos
		int n_tuplas = tuplas.size(); // num de tuplas
		//int n_c = C[points[].id].size();

		
		// create model

		IloModel antena(env, "Problema da Antenas");
		IloCplex cplex(antena);

		//Limites de Tempo e Memória

		cplex.setParam(IloCplex::TiLim, time);
		//cplex.setParam(IloCplex::TreLim, memory);

		// Criando as variáveis binárias
		IloIntVarArray x(env, n_tuplas, 0, 1);
		
		/*
		IloArray<IloIntVarArray> p(env, n_ant);
		for (int i = 0;i < n_ant;i++)
			p[i] = IloIntVarArray(env, n_pon, 0, 1); // Criação variáveis p[i][j]
			
		// Função Objetivo
		IloExpr obj(env);
		for (int i = 0; i < n_ant; i++)
			//obj += custos[i] * z[i];
			obj += discos[i].custo * z[i];
		antena.add(IloMinimize(env, obj));
		*/

		// Função Objetivo
		IloExpr obj(env);
		for (int j = 0; j < n_tuplas; j++)
			//obj += custos[i] * z[i];
			obj += discos[tuplas[j].disco].custo * x[j];
		antena.add(IloMinimize(env, obj));

		/*
		// Restrição Distância
		for (int i = 0; i < n_ant; i++)
			for (int j = 0;j < n_pon;j++)
			{
				antena.add(((Px[j] - x[i]) * (Px[j] - x[i])) + ((Py[j] - y[i]) * (Py[j] - y[i])) <=
					(raios[i] * raios[i] * p[i][j]) + (max_x * max_x * (1 - p[i][j])));
			}

		*/

		
		// Cada ponto deve ser atendido por uma tupla
		for (int i = 0; i < n_pon; i++)
		{
			IloExpr somatorio(env);
			for (int j = 0; j < C[i].size(); j++)
				somatorio += x[C[i][j]];
			antena.add(somatorio >= 1);
		}

		// Cada disco deve ser usado uma unica vez
		for (int d = 0; d < discos.size(); d++)
		{
			IloExpr somatorio(env);
			for (int j = 0; j < discos[d].R.size(); j++)
				somatorio += x[discos[d].R[j]];
			antena.add(somatorio <= 1);
		}

		/*
		// Se um ponto j é coberto pela antena i então a antena i está sendo utilizada
		for (int i = 0; i < n_ant; i++)
			for (int j = 0;j < n_pon;j++)
			{
				antena.add(p[i][j] <= z[i]);
			}

		*/
		
		if (cplex.solve()) {
			env.out() << "Valor Ótimo "
				<< cplex.getObjValue() << endl;

			valor_otimo = cplex.getObjValue();
		}
		//std::cout << "================Tupla==============" << std::endl;

		IloNumArray sol(env, n_tuplas);
		cplex.getValues(sol, x);
		
		
		for (int i = 0; i < n_tuplas; i++)
		{
			

			if (sol[i] == 1) {
				cout << "Tupla " << i << ", Disco: "<< tuplas[i].disco << ", Pos ("<< tuplas[i].pos.x << ", " << tuplas[i].pos.y << ")" << endl;

				for (int j = 0; j < tuplas[i].points.size(); j++) {
						cout << "Ponto: " << tuplas[i].points[j].id << endl;
				}

				/*
				cout << "////////////////////////////////////////////////////" << endl;

				for (int j = 0; j < points.size(); j++) {
					
					for (int id = 0; id < C[j].size(); id++) {
						if (C[j][id] == i) {
							cout << "Ponto: " << j << endl;
						}
					}
					
				}
				*/
				
			}
		}
		
		/*
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
		*/

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
	
	return valor_otimo;
}