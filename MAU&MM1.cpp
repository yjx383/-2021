#include<ilcplex/ilocplex.h>
#include<__msvc_all_public_headers.hpp>

ILOSTLBEGIN
using namespace std;
void Mau(int A[][13], int B[][4]);
void MM1(int A[][13], int B[][4]);
void MM1_p(int A[][13], int B[][4]);


int main()
{

	int A[][13] = { {1,1,1,0,-1,0,0,0,0,0,0,0,0},
					{-1,0,0,1,0,0,0,0,-1,0,0,0,0},
					{0,-1,0,0,1,1,0,0,0,0,0,0,0},
					{0,0,-1,0,0,0,1,1,0,0,-1,0,0},
					{0,0,0,-1,0,0,-1,0,1,1,0,0,-1},
					{0,0,0,0,0,-1,0,-1,0,0,1,1,0},
					{0,0,0,0,0,0,0,0,0,-1,0,-1,1} };
	int B[][4] = {  {4,4,0,4},
					{-4,0,-4,0},
					{0,-4,4,0},
					{0,0,0,0},
					{0,0,0,0},
					{0,0,0,0},
					{0,0,0,-4} };
	//Mau(A, B);
	//MM1(A, B);
	MM1_p(A, B);
}

void Mau(int A[][13], int B[][4])
{
	IloEnv env;
	IloModel model(env);
	IloNumVarArray var(env);
	IloRangeArray con(env);

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 13; j++)var.add(IloNumVar(env));
	}
	var.add(IloNumVar(env));
	IloObjective obj = IloMinimize(env, var[4 * 13]);
	IloExprArray temp;
	temp = IloExprArray(env, 13);
	for (int i = 0; i < 13; i++)
	{
		temp[i] = IloExpr(env);
		for (int j = 0; j < 4; j++)
		{
			temp[i] += var[13 * j + i] * 0.2;
		}
		temp[i] -= var[4 * 13];
		con.add(temp[i] <= 0);
	}
	IloExprArray temp1;
	temp1 = IloExprArray(env, 13);
	for (int i = 0; i < 13; i++)
	{
		temp1[i] = IloExpr(env);
		for (int j = 0; j < 4; j++)
		{
			temp1[i] += var[13 * j + i];
		}
		con.add(temp1[i] <= 5);
	}
	IloExprArray temp2;
	temp2 = IloExprArray(env, 4 * 7);
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			temp2[i * 4 + j] = IloExpr(env);
			for (int k = 0; k < 13; k++)
			{
				if (A[i][k] == 1)temp2[i * 4 + j] += var[j * 13 + k];
				else if (A[i][k] == -1)temp2[i * 4 + j] -= var[j * 13 + k];
			}
			con.add(temp2[i * 4 + j] == B[i][j]);
		}
	}

	model.add(obj);
	model.add(con);

	IloCplex cplex(model);
	cplex.solve();
	env.out() << model;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 13; j++)
		{
			env.out() << cplex.getValue(var[i * 13 + j])<<" ";
		}
		env.out() << endl;
	}
	env.out() << cplex.getValue(var[4 * 13]) << endl;
	system("pause");
}

void MM1(int A[][13], int B[][4])
{
	IloEnv env;
	IloModel model(env);
	IloNumVarArray var(env);
	IloRangeArray con(env);

	for (int i = 0; i <= 4; i++)
	{
		for (int j = 0; j < 13; j++)var.add(IloNumVar(env));
	}
	IloExpr obj_temp(env);
	for (int j = 0; j < 13; j++)obj_temp += var[4 * 13 + j];
	IloObjective obj = IloMinimize(env, obj_temp);
	IloExprArray temp;
	temp = IloExprArray(env, 6*13);
	for (int i = 0; i < 13; i++)
	{
		temp[i] = IloExpr(env);
		for (int j = 0; j < 4; j++)
		{
			temp[i] += var[13 * j + i];
		}
		temp[i] -= var[13 * 4 + i];
		con.add(temp[i] <= 0);
	}
	for (int i = 0; i < 13; i++)
	{
		temp[13+i] = IloExpr(env);
		for (int j = 0; j < 4; j++)
		{
			temp[13+i] += 3*var[13 * j + i];
		}
		temp[13+i] -= var[13 * 4 + i];
		con.add(temp[13+i] <= 2.0/3.0*5);
	}
	for (int i = 0; i < 13; i++)
	{
		temp[2*13 + i] = IloExpr(env);
		for (int j = 0; j < 4; j++)
		{
			temp[2*13 + i] += 10 * var[13 * j + i];
		}
		temp[2*13 + i] -= var[13 * 4 + i];
		con.add(temp[2*13 + i] <= 16.0 / 3.0 * 5);
	}
	for (int i = 0; i < 13; i++)
	{
		temp[3 * 13 + i] = IloExpr(env);
		for (int j = 0; j < 4; j++)
		{
			temp[3 * 13 + i] += 70 * var[13 * j + i];
		}
		temp[3 * 13 + i] -= var[13 * 4 + i];
		con.add(temp[3 * 13 + i] <= 178.0 / 3.0 * 5);
	}
	for (int i = 0; i < 13; i++)
	{
		temp[4 * 13 + i] = IloExpr(env);
		for (int j = 0; j < 4; j++)
		{
			temp[4 * 13 + i] += 500 * var[13 * j + i];
		}
		temp[4 * 13 + i] -= var[13 * 4 + i];
		con.add(temp[4 * 13 + i] <= 1468.0 / 3.0 * 5);
	}
	for (int i = 0; i < 13; i++)
	{
		temp[5 * 13 + i] = IloExpr(env);
		for (int j = 0; j < 4; j++)
		{
			temp[5 * 13 + i] += 5000 * var[13 * j + i];
		}
		temp[5 * 13 + i] -= var[13 * 4 + i];
		con.add(temp[5 * 13 + i] <= 16318.0 / 3.0 * 5);
	}
	IloExprArray temp1;
	temp1 = IloExprArray(env, 13);
	for (int i = 0; i < 13; i++)
	{
		temp1[i] = IloExpr(env);
		for (int j = 0; j < 4; j++)
		{
			temp1[i] += var[13 * j + i];
		}
		con.add(temp1[i] <= 5);
	}
	IloExprArray temp2;
	temp2 = IloExprArray(env, 4 * 7);
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			temp2[i * 4 + j] = IloExpr(env);
			for (int k = 0; k < 13; k++)
			{
				if (A[i][k] == 1)temp2[i * 4 + j] += var[j * 13 + k];
				else if (A[i][k] == -1)temp2[i * 4 + j] -= var[j * 13 + k];
			}
			con.add(temp2[i * 4 + j] == B[i][j]);
		}
	}

	model.add(obj);
	model.add(con);

	IloCplex cplex(model);
	cplex.solve();
	env.out() << model;
	for (int i = 0; i <= 4; i++)
	{
		for (int j = 0; j < 13; j++)
		{
			env.out() << cplex.getValue(var[i * 13 + j]) << " ";
		}
		env.out() << endl;
	}
	IloNum tempx = 0;
	env.out() << cplex.getObjValue();
	for (int j = 0; j < 13; j++) tempx += cplex.getValue(var[4 * 13 + j]);
	//env.out()<<tempx;
	system("pause");
}


void MM1_p(int A[][13], int B[][4])
{
	IloEnv env;
	IloModel model(env);
	IloNumVarArray var(env);
	IloRangeArray con(env);

	for (int i = 0; i <= 5; i++)
	{
		for (int j = 0; j < 13; j++)var.add(IloNumVar(env));
	}
	IloExpr obj_temp(env);
	for (int j = 0; j < 13; j++)obj_temp += var[4 * 13 + j];
	IloObjective obj = IloMinimize(env, obj_temp);
	IloExprArray temp;
	temp = IloExprArray(env, 6 * 13);
	for (int i = 0; i < 13; i++)
	{
		temp[i] = IloExpr(env);
		for (int j = 0; j < 4; j++)
		{
			temp[i] += var[13 * j + i];
		}
		temp[i] -= var[13 * 4 + i];
		con.add(temp[i] <= 0);
	}
	for (int i = 0; i < 13; i++)
	{
		temp[13 + i] = IloExpr(env);
		for (int j = 0; j < 4; j++)
		{
			temp[13 + i] += 3 * var[13 * j + i];
		}
		temp[13 + i] -= var[13 * 4 + i];
		temp[13 + i] -= var[13 * 5 + i] * 2.0 / 3.0;
		con.add(temp[13 + i] <=  0);
	}
	for (int i = 0; i < 13; i++)
	{
		temp[2 * 13 + i] = IloExpr(env);
		for (int j = 0; j < 4; j++)
		{
			temp[2 * 13 + i] += 10 * var[13 * j + i];
		}
		temp[2 * 13 + i] -= var[13 * 4 + i];
		temp[2 * 13 + i] -= var[13 * 5 + i]*16.0/3.0;
		con.add(temp[2 * 13 + i] <= 0);
	}
	for (int i = 0; i < 13; i++)
	{
		temp[3 * 13 + i] = IloExpr(env);
		for (int j = 0; j < 4; j++)
		{
			temp[3 * 13 + i] += 70 * var[13 * j + i];
		}
		temp[3 * 13 + i] -= var[13 * 4 + i];
		temp[3 * 13 + i] -= var[13 * 5 + i] * 178.0 / 3.0;
		con.add(temp[3 * 13 + i] <= 0);
	}
	for (int i = 0; i < 13; i++)
	{
		temp[4 * 13 + i] = IloExpr(env);
		for (int j = 0; j < 4; j++)
		{
			temp[4 * 13 + i] += 500 * var[13 * j + i];
		}
		temp[4 * 13 + i] -= var[13 * 4 + i];
		temp[4 * 13 + i] -= var[13 * 5 + i] * 1468.0 / 3.0;
		con.add(temp[4 * 13 + i] <= 0);
	}
	for (int i = 0; i < 13; i++)
	{
		temp[5 * 13 + i] = IloExpr(env);
		for (int j = 0; j < 4; j++)
		{
			temp[5 * 13 + i] += 5000 * var[13 * j + i];
		}
		temp[5 * 13 + i] -= var[13 * 4 + i];
		temp[5 * 13 + i] -= var[13 * 5 + i] * 16318.0 / 3.0;
		con.add(temp[5 * 13 + i] <= 0);
	}
	IloExprArray temp1;
	temp1 = IloExprArray(env, 13);
	for (int i = 0; i < 13; i++)
	{
		temp1[i] = IloExpr(env);
		for (int j = 0; j < 4; j++)
		{
			temp1[i] += var[13 * j + i];
		}
		temp1[i] -= var[13 * 5 + i];
		con.add(temp1[i] <= 0);
	}
	IloExprArray temp2;
	temp2 = IloExprArray(env, 4 * 7);
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			temp2[i * 4 + j] = IloExpr(env);
			for (int k = 0; k < 13; k++)
			{
				if (A[i][k] == 1)temp2[i * 4 + j] += var[j * 13 + k];
				else if (A[i][k] == -1)temp2[i * 4 + j] -= var[j * 13 + k];
			}
			con.add(temp2[i * 4 + j] == B[i][j]);
		}
	}
	IloExpr temp3;
	temp3 = IloExpr(env);
	for (int i = 0; i < 13; i++)temp3 += var[13 * 5 + i];
	con.add(temp3 == 13*5);

	model.add(obj);
	model.add(con);

	IloCplex cplex(model);
	cplex.solve();
	env.out() << model;
	
	for (int i = 0; i <= 5; i++)
	{
		for (int j = 0; j < 13; j++)
		{
			env.out() << cplex.getValue(var[i * 13 + j]) << " ";
		}
		env.out() << endl;
	}
	IloNum tempx = 0;
	env.out() << cplex.getObjValue();
	for (int j = 0; j < 13; j++) tempx += cplex.getValue(var[4 * 13 + j]);
	//env.out()<<tempx;
	system("pause");
}