//
// Created by Yi-Ning MA on 2019-03-13.
// Modifications: 
// V2: by Ting Huang on 2020-05-28
//	   1. improve the algorithm's performance 
//	   2. update the niche operators
// V3: by Ting Huang on 2020-09-14
//     1. update the creation operator, including the method and the probability
//	   2. update the deletion operator. 
//	   3. modify the trait update.
//    The final version of the draft on 2020-10-15
// R1_V1: by Ting Huang on 2021-08-11
//		1. introduce the effect of ocean currents

#include<iostream>
#include<algorithm>
#include<cstdlib>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<vector>
#include<ctime>

using namespace std;
//----------------------------------------------
#define INF 10e9
#define AntAmount 100
#define NCMAX 1500 // 1000
#define repeat 10 // 30
#define STOP 0

#define SAME log(1.0*YN*ZN) //2*log(1.0*YN*ZN)
#define GAP 50
#define MAXNICHE 5
//#define DEBUG

const char* outdir = "./Results_TITS_R1/DAP-MACS_param_SW_2/";


#define OUTPUTDEF
//#define DEBUG
//#define DEBUG2
//#define EXAMINE

//#define AntCount  20
//#define NCMAX 1000  
//#define repeat 301

//#define ChinaSmall      // 25  (0,24,20)-(24,5,10)
#define ChinaMiddle       // 50  (0,49,35)-(49,5,16)
//#define ChinaLarge      // 10  (0,80,55)-(99,10,30)
//#define ChinaXLarge     // 200 (0,180,120)-(199,5,40)

//#define PacificSmall    // 25  (0,5,15)-(24,20,10)
//#define PacificMiddle   // 50  (0,25,25)-(49,40,20)
//#define PacificLarge    // 100 (0,75,20)-(99,15,60)
//#define PacificXLarge   // 200 (0,180,10)-(199,20,80)

#ifdef ChinaSmall         // 25  (0,24,20)-(24,5,10)
#define STR 0,24,20
#define END 24,5,10
#define ssize 25.0
#define mynsize 25
#define NC  10
const char* datastr = "./data/ChinaSmall.txt"; 
const char* susstr = "./data/sus_data/China25.txt";
const char* csvpath = "./Results_TITS_R1/DAP-MACS_param_SW_2/China_25_total.csv";
const char* itpath = "./Results_TITS_R1/DAP-MACS_param_SW_2/China_25_avgfit.txt";
const char* outpath = "./Results_TITS_R1/DAP-MACS_param_SW_2/China_25_path.txt";
const char* deadout = "./Results_TITS_R1/DAP-MACS_param_SW_2/China_25_dead.txt";
const char* avgdeadout = "./Results_TITS_R1/DAP-MACS_param_SW_2/China_25_avgdead.txt";
const char* instancename = "China";
const char* fullinstancename = "China_25";

const char* currentpath_x = "./data/current/current_x_25.txt";
const char* currentpath_y = "./data/current/current_y_25.txt";
#endif

#ifdef ChinaMiddle     // 50  (0,49,35)-(49,5,16)
#define STR 0,49,35
#define END 49,5,16
#define ssize 50.0
#define mynsize 50
const char* datastr = "./data/ChinaMiddle.txt";
const char* susstr = "./data/sus_data/China50.txt";
const char* csvpath = "./Results_TITS_R1/DAP-MACS_param_SW_2/China_50_total.csv";
const char* itpath = "./Results_TITS_R1/DAP-MACS_param_SW_2/China_50_avgfit.txt";
const char* outpath = "./Results_TITS_R1/DAP-MACS_param_SW_2/China_50_path.txt";
const char* deadout = "./Results_TITS_R1/DAP-MACS_param_SW_2/China_50_dead.txt";
const char* avgdeadout = "./Results_TITS_R1/DAP-MACS_param_SW_2/China_50_avgdead.txt";
const char* instancename = "China";
const char* fullinstancename = "China_50";

const char* currentpath_x = "./data/current/current_x_50.txt";
const char* currentpath_y = "./data/current/current_y_50.txt";
#endif

#ifdef ChinaLarge      // 100 (0,80,55)-(99,10,30)
#define STR 0,80,55
#define END 99,10,30
#define ssize 100.0
#define mynsize 100
const char* datastr = "./data/ChinaLarge.txt";
const char* susstr = "./data/sus_data/China100.txt";
const char* csvpath = "./Results_TITS_R1/DAP-MACS_param_SW_2/China_100_total.csv";
const char* itpath = "./Results_TITS_R1/DAP-MACS_param_SW_2/China_100_avgfit.txt";
const char* outpath = "./Results_TITS_R1/DAP-MACS_param_SW_2/China_100_path.txt";
const char* deadout = "./Results_TITS_R1/DAP-MACS_param_SW_2/China_100_dead.txt";
const char* avgdeadout = "./Results_TITS_R1/DAP-MACS_param_SW_2/China_100_avgdead.txt";
const char* instancename = "China";
const char* fullinstancename = "China_100";

const char* currentpath_x = "./data/current/current_x_100.txt";
const char* currentpath_y = "./data/current/current_y_100.txt";
#endif

#ifdef ChinaXLarge     // 200 (0,180,120)-(199,5,40)
#define STR 0,180,120
#define END 199,5,40
#define ssize 200.0
#define mynsize 200
const char* datastr = "./data/ChinaXLarge.txt";
const char* susstr = "./data/sus_data/China200.txt";
const char* csvpath = "./Results_TITS_R1/DAP-MACS_param_SW_2/China_200_total.csv";
const char* itpath = "./Results_TITS_R1/DAP-MACS_param_SW_2/China_200_avgfit.txt";
const char* outpath = "./Results_TITS_R1/DAP-MACS_param_SW_2/China_200_path.txt";
const char* deadout = "./Results_TITS_R1/DAP-MACS_param_SW_2/China_200_dead.txt";
const char* avgdeadout = "./Results_TITS_R1/DAP-MACS_param_SW_2/China_200_avgdead.txt";
const char* instancename = "China";
const char* fullinstancename = "China_200";

const char* currentpath_x = "./data/current/current_x_200.txt";
const char* currentpath_y = "./data/current/current_y_200.txt";
#endif


#ifdef PacificSmall    // 25  (0,5,15)-(24,20,10)
#define STR 0,5,15
#define END 24,20,10
#define ssize 25.0
#define mynsize 25
const char* datastr = "./data/PacificSmall.txt";
const char* susstr = "./data/sus_data/Pacific25.txt";
const char* csvpath = "./Results_TITS_R1/DAP-MACS_param_SW_2/Pacific_25_total.csv";
const char* itpath = "./Results_TITS_R1/DAP-MACS_param_SW_2/Pacific_25_avgfit.txt";
const char* outpath = "./Results_TITS_R1/DAP-MACS_param_SW_2/Pacific_25_path.txt";
const char* deadout = "./Results_TITS_R1/DAP-MACS_param_SW_2/Pacific_25_dead.txt";
const char* avgdeadout = "./Results_TITS_R1/DAP-MACS_param_SW_2/Pacific_25_avgdead.txt";
const char* instancename = "Pacific";
const char* fullinstancename = "Pacific_25";

const char* currentpath_x = "./data/current/current_x_25.txt";
const char* currentpath_y = "./data/current/current_y_25.txt";
#endif

#ifdef PacificMiddle   // 50  (0,25,25)-(49,40,20)
#define STR 0,25,25
#define END 49,40,20
#define ssize 50.0
#define mynsize 50
const char* datastr = "./data/PacificMiddle.txt";
const char* susstr = "./data/sus_data/Pacific50.txt";
const char* csvpath = "./Results_TITS_R1/DAP-MACS_param_SW_2/Pacific_50_total.csv";
const char* itpath = "./Results_TITS_R1/DAP-MACS_param_SW_2/Pacific_50_avgfit.txt";
const char* outpath = "./Results_TITS_R1/DAP-MACS_param_SW_2/Pacific_50_path.txt";
const char* deadout = "./Results_TITS_R1/DAP-MACS_param_SW_2/Pacific_50_dead.txt";
const char* avgdeadout = "./Results_TITS_R1/DAP-MACS_param_SW_2/Pacific_50_avgdead.txt";
const char* instancename = "Pacific";
const char* fullinstancename = "Pacific_50";

const char* currentpath_x = "./data/current/current_x_50.txt";
const char* currentpath_y = "./data/current/current_y_50.txt";
#endif

#ifdef PacificLarge    // 100 (0,75,20)-(99,15,60)
#define STR 0,75,20
#define END 99,15,60
#define ssize 100.0
#define mynsize 100
const char* datastr = "./data/PacificLarge.txt";
const char* susstr = "./data/sus_data/Pacific100.txt";
const char* csvpath = "./Results_TITS_R1/DAP-MACS_param_SW_2/Pacific_100_total.csv";
const char* itpath = "./Results_TITS_R1/DAP-MACS_param_SW_2/Pacific_100_avgfit.txt";
const char* outpath = "./Results_TITS_R1/DAP-MACS_param_SW_2/Pacific_100_path.txt";
const char* deadout = "./Results_TITS_R1/DAP-MACS_param_SW_2/Pacific_100_dead.txt";
const char* avgdeadout = "./Results_TITS_R1/DAP-MACS_param_SW_2/Pacific_100_avgdead.txt";
const char* instancename = "Pacific";
const char* fullinstancename = "Pacific_100";

const char* currentpath_x = "./data/current/current_x_100.txt";
const char* currentpath_y = "./data/current/current_y_100.txt";
#endif

#ifdef PacificXLarge   // 200 (0,180,10)-(199,20,80)
#define STR 0,180,10
#define END 199,20,80
#define ssize 200.0
#define mynsize 200
const char* datastr = "./data/PacificXLarge.txt";
const char* susstr = "./data/sus_data/Pacific200.txt";
const char* csvpath = "./Results_TITS_R1/DAP-MACS_param_SW_2/Pacific_200_total.csv";
const char* itpath = "./Results_TITS_R1/DAP-MACS_param_SW_2/Pacific_200_avgfit.txt";
const char* outpath = "./Results_TITS_R1/DAP-MACS_param_SW_2/Pacific_200_path.txt";
const char* deadout = "./Results_TITS_R1/DAP-MACS_param_SW_2/Pacific_200_dead.txt";
const char* avgdeadout = "./Results_TITS_R1/DAP-MACS_param_SW_2/Pacific_200_avgdead.txt";
const char* instancename = "Pacific";
const char* fullinstancename = "Pacific_200";

const char* currentpath_x = "./data/current/current_x_200.txt";
const char* currentpath_y = "./data/current/current_y_200.txt";
#endif

//UEM parameters
/*
#define STR 0,180,10
#define END 199,20,80
*/
//#define scale 200
#define scale  mynsize
#define XM scale
#define YN scale
#define ZN scale

//Ph parameters
int Nc = 0;
#define _p 0.1 //global pheromone update param
#define _c 0.1 //local pheromone update param
double cnn = -1;  //greedy initial val
#define Qinit ((cnn==-1)? 1/(double(scale)*(double(scale)+double(scale))):(1.0/(XM*cnn))) //initial pheromone strategy
#define Q0 Qinit	//initial pheromone

//MACS parameters
#define q0 0.9  //Pseudo random choose rule
#define deadupdate 1//indicating whether using DAP-MACS_param_SW_2 or original ACS
#define Alpha 2 //guide ph param
#define Belta 2 //alarm ph param
#define CSIZE 5

#define lmd 0.99
double deadamount = 0;

//Searching Rule
#define Distance_rand   rnd_d(0.1, 0.9)     // purposeful param
#define Safe_rand       rnd_d(0.1, 0.9)     // safety param
#define Smooth_rand     rnd_d(0.1, 0.9)     // smoothness param

// param_1
//#define Distance_rand   0.5     // purposeful param
//#define Safe_rand       0.5     // safety param
//#define Smooth_rand     0.5     // smoothness param

//param_2
//#define Distance_rand   0.9     // purposeful param
//#define Safe_rand       0.5     // safety param
//#define Smooth_rand     0.1     // smoothness param


//param_3
//#define Distance_rand   0.9     // purposeful param
//#define Safe_rand       0.1     // safety param
//#define Smooth_rand     0.1     // smoothness param

//////param_4
//#define Distance_rand   0.9     // purposeful param
//#define Safe_rand       0.1     // safety param
//#define Smooth_rand     0.5     // smoothness param



//Evaluating Rule
#define _SAFE 0.3
#define _SMOOTH 0.5
#define _LENGTH 1.2


#define Cansee 3 // sight depth

//#define window_leftright    2 //Steer Window
//#define window_updown       2 //Steer Window

//param_SW_1	DAP-MACS_param_SW_1
//#define window_leftright    1 //Steer Window
//#define window_updown       1 //Steer Window

//param_SW_2	DAP-MACS_param_SW_2
#define window_leftright    3 //Steer Window
#define window_updown       3 //Steer Window


//UEM var
bool*** world;
bool*** space;
double** current_x;
double** current_y;
double*** ph = NULL;
double*** AP = NULL;
double fit[NCMAX];
double avgdead[NCMAX];

//----------------------------------------------
//Tool Fuctions
inline int rnd(int nLow, int nUpper) {
	return nLow + (nUpper - nLow) * ((double)rand() / (RAND_MAX + 1.0));
}
inline double rnd_d(double Low, double Upper) {
	double Temp;
	Temp = rand() / ((double)RAND_MAX + 1.0);
	Temp = Low + Temp * (Upper - Low);
	return Temp;
}

double round(double r)
{
	return (r > 0.0) ? floor(r + 0.5) : ceil(r - 0.5);
}
//----------------------------------------------
//Class Definition
class Point
{
public:
	int x; int y; int z;
	double rx; double ry; double rz;
	Point() { x = 0; y = 0; z = 0; rx = 0; ry = 0; rz = 0; };
	Point(int xx, int yy, int zz) {
		x = xx; y = yy; z = zz;
		rx = (double)x * 1.0; ry = (double)y * 1.0; rz = (double)z * 1.0;
	}
	double getDistance(Point& p2) {
		double ans = pow(rx - p2.rx, 2);
		ans += pow(ry - p2.ry, 2);
		ans += pow(rz - p2.rz, 2);
		return pow(ans, 0.5);
	}
	void print() {
		printf("[(%d,%d,%d)]", x, y, z);
	}

	int checkSimilarity(Point& t) {
		int y1, y2, z1, z2, sum = 0;
		if (y == t.y) {
			if (z >= t.z) {
				z1 = t.z;
				z2 = z;
			}
			else {
				z1 = z;
				z2 = t.z;
			}
			for (int i = z1 + 1; i < z2; i++) {
				if (!world[x][y][i])
					sum++;
			}
		}
		else {
			if (y - t.y < 0) { y1 = y, z1 = z, y2 = t.y, z2 = t.z; }
			else { y1 = t.y, z1 = t.z, y2 = y, z2 = z; }
			double k = (z2 - z1) / (y2 - y1);
			for (int i = y1 + 1; i < y2; i++) {
				double curz = k * 1.0 * (double(i - y1)) + (double(z1));
				int cur_z = int(round(curz));
				if (!world[x][i][cur_z])
					sum++;
			}
		}
		return sum;
	}

	Point& operator=(const Point& rhs) {
		if (this == &rhs)
			return *this;
		else {
			this->x = rhs.x;
			this->y = rhs.y;
			this->z = rhs.z;
			this->rx = rhs.rx;
			this->ry = rhs.ry;
			this->rz = rhs.rz;
			return *this;
		}
	}
}startPoint(STR), endPoint(END);

class Ant {
public:
	Ant() {
		fitness = INF;
		PathLength = INF;
		safeFitness = INF;
		soomthFitness = INF;
		MovedCityCount = -1;
		isalive = true;
	}
	void init() {
		fitness = INF;
		PathLength = INF;
		safeFitness = INF;
		soomthFitness = INF;
		MovedCityCount = -1;
		isalive = true;
	}
	Point Path[XM];
	double fitness;
	double PathLength;
	double safeFitness;
	double soomthFitness;
	int MovedCityCount; //total moved cnt£¬Path[MovedCityCount-1] is its cur pos
	bool isalive;
	double checkSimilarity(Ant& b) {
		double distance = 0, block = 0;
		for (int i = 0; i < XM - 1; i++) {
			block += Path[i].checkSimilarity(b.Path[i]);
			distance += Path[i].getDistance(b.Path[i]);
		}
		return block + log(1.0 + distance);
	}
	void printSimilarity(Ant& b) {
		double distance = 0, block = 0;
		for (int i = 0; i < XM - 1; i++) {
			block += Path[i].checkSimilarity(b.Path[i]);
			distance += Path[i].getDistance(b.Path[i]);
		}
		cout << "b: " << block << " dis:" << distance << " ln: " << log(1.0 + block) << " " << log(1 + distance) << endl;
		return;
	}
	Ant& operator=(const Ant& rhs) {
		if (this == &rhs)
			return *this;
		else {
			for (int i = 0; i < XM; i++)
				this->Path[i] = rhs.Path[i];
			this->fitness = rhs.fitness;
			this->PathLength = rhs.PathLength;
			this->safeFitness = rhs.safeFitness;
			this->soomthFitness = rhs.soomthFitness;
			this->MovedCityCount = rhs.MovedCityCount;
			this->isalive = rhs.isalive;
			return *this;
		}
	}
}Gbest;


class Colony {
public:
	Ant Ants[AntAmount];
	int size;
	double*** localph;
	void restart_localph(double*** source) {
		NiGBest.fitness = INF;
		//localph = new double**[XM];
		for (int m = 0; m < XM; m++)
		{
			for (int i = 0; i < YN; i++) {
				for (int j = 0; j < ZN; j++)
					localph[m][i][j] = source[m][i][j];
			}
		}
	}

	void start_localph(double*** source) {
		localph = new double** [XM];
		for (int m = 0; m < XM; m++)
		{
			localph[m] = new double* [YN];
			for (int i = 0; i < YN; i++) {
				localph[m][i] = new double[ZN];
				for (int j = 0; j < ZN; j++)
					localph[m][i][j] = source[m][i][j];
			}
		}
	}
	void stop_localph() {
		if (localph == NULL)
			return;
		for (int m = 0; m < XM; m++) {
			for (int i = 0; i < YN; i++) {
				delete[] localph[m][i];
			}
			delete[] localph[m];
		}
		delete[]localph;
		localph = NULL;

	};
	Colony(int NUM) {
		size = NUM;
		overlapping = 0;
		createAnts();
	}
	void createAnts() {
		for (int i = 0; i < size; i++) {
			Ants[i].init();
		}
		for (int i = 0; i < size; i++)
		{
			Ants[i].isalive = true;
			Ants[i].PathLength = 0;
			Ants[i].fitness = INF;
			Ants[i].safeFitness = 0;
			Ants[i].soomthFitness = 0;
			Ants[i].Path[0] = startPoint;
			Ants[i].MovedCityCount = 1;
		}
	}
	Ant NiGBest;
	int since;
	int overlapping;
};
vector<Colony>myColony;

//----------------------------------------------
//Functions


void get3DWorld() {
	//read file
	double hight[YN][XM];
	FILE* fp;
	fp = fopen(datastr, "r");
	if (fp == NULL)
	{
		printf("Cannot open data source.\n");
		exit(0);
	}

	for (int i = 0; i < YN; i++)
		for (int m = 0; m < XM; m++)
			fscanf(fp, "%lf", &hight[i][m]);
	fclose(fp);

	//initial and storage
	world = new bool** [XM];
	for (int m = 0; m < XM; m++)
	{
		world[m] = new bool* [YN];
		for (int i = 0; i < YN; i++) {
			world[m][i] = new bool[ZN];
			int curhight = hight[i][m];
			if (curhight == ZN)
				curhight--;
			for (int h = 0; h < ZN; h++)
				if (h < curhight)
					world[m][i][h] = false;
				else
					world[m][i][h] = true;

		}
	}
}

void spacial() {
	space = new bool** [XM];
	for (int m = 0; m < XM; m++)
	{
		space[m] = new bool* [YN];
		for (int i = 0; i < YN; i++) {
			space[m][i] = new bool[ZN];
			for (int j = 0; j < ZN; j++)
				space[m][i][j] = false;
		}
	}

	for (int x = 1; x < XM - 1; x++)
		for (int y = 0; y < YN; y++)
			for (int z = 0; z < ZN; z++)
			{
				if (world[x][y][z] &&
					(abs(y - startPoint.y) <= window_leftright * x) && (abs(y - endPoint.y) <= window_leftright * (XM - 1 - x)) &&
					(abs(z - startPoint.z) <= window_updown * x) && (abs(z - endPoint.z) <= window_updown * (XM - 1 - x))
					)
					space[x][y][z] = true;
			}
}

void putSuspended(int x, int y, int z, int r) {
	for (int m = 0; m < r; m++) {
		double temp = pow(double(r), 2) - pow(double(m), 2);
		int R = ceil(pow(temp, 0.5));
		for (int i = y - R; i <= y + R; i++)
			for (int j = z - R; j <= z + R; j++)
				if (x - m >= 0 && x - m < XM && m + x >= 0 && m + x < XM && i >= 0 && i < YN && j >= 0 && j < ZN)
				{
					world[x - m][i][j] = false;
					world[x + m][i][j] = false;
				}
	}
}
void getCurrentVol() {
	FILE* fp;

	fp = fopen(currentpath_x, "r");
	if (fp == NULL)
	{
		printf("Cannot open source file.\n");
		exit(0);
	}
	current_x = new double* [XM];
	for (int m = 0; m < XM; m++)
	{
		current_x[m] = new double[YN];
		for (int i = 0; i < YN; i++) {
			fscanf(fp, "%lf", &current_x[m][i]);
		}
	}


	fp = fopen(currentpath_y, "r");
	if (fp == NULL)
	{
		printf("Cannot open current file.\n");
		exit(0);
	}
	current_y = new double* [XM];
	for (int m = 0; m < XM; m++)
	{
		current_y[m] = new double[YN];
		for (int i = 0; i < YN; i++) {
			fscanf(fp, "%lf", &current_y[m][i]);
		}
	}
}
void getSuspended() {
	FILE* fp;
	fp = fopen(susstr, "r");
	if (fp == NULL)
	{
		printf("Cannot open source file.\n");
		exit(0);
	}
	while (!feof(fp)) {
		int x, y, z, r;
		fscanf(fp, "%d%d%d%d", &x, &y, &z, &r);
		putSuspended(x - 1, y - 1, z - 1, r);
	}
}

void evaluate(Ant& a) {
	a.PathLength = 0;
	a.soomthFitness = 0;
	a.safeFitness = 0;
	int dan = 0;
	for (int i = 0; i < XM - 1; i++)
	{
		double distance = a.Path[i].getDistance(a.Path[i + 1]);
		double smo = abs(a.Path[i + 1].y - a.Path[i].y) +
			abs(a.Path[i + 1].z - a.Path[i].z);
		//TITS_R1
		// TITS_R1: abs -> fabs
		double energy = fabs(1.0 - current_x[a.Path[i].x][a.Path[i].y])
			+ fabs(a.Path[i + 1].y - a.Path[i].y - current_y[a.Path[i].x][a.Path[i].y])
			+ fabs(a.Path[i + 1].z - a.Path[i].z);
		for (int yy = a.Path[i].y - window_leftright; yy <= a.Path[i].y + window_leftright; yy++) {
			for (int zz = a.Path[i].z - window_updown; zz <= a.Path[i].z + window_updown; zz++)
				if (yy >= 0 && zz >= 0 &&
					yy < YN && zz < ZN &&
					!world[a.Path[i].x][yy][zz])
					dan++;
		}

		a.PathLength += distance;
		a.soomthFitness += energy;
	}
	a.safeFitness = dan;

	//TITS_R1
	a.soomthFitness = (a.soomthFitness / 3.0);
	a.safeFitness = a.safeFitness + 1;
	a.fitness = (pow(a.PathLength, _LENGTH) * pow(a.soomthFitness, _SMOOTH) * pow(a.safeFitness, _SAFE));
}

double getCnnLength() {
	Ant temp;
	Point* cnnTour = temp.Path;
	cnnTour[0] = startPoint;
	bool hasok = false;
	for (int m = 1; m < XM - 1; m++) {
		Point curcity = cnnTour[m - 1];
		double** p = new double* [1 + 2 * window_leftright];
		for (int i = 0; i < 1 + 2 * window_leftright; i++) {
			p[i] = new double[1 + 2 * window_updown];
			for (int j = 0; j < 1 + 2 * window_updown; j++)
				p[i][j] = 0;
		}
		//distance[][] and mindistance
		double mindistance = INF;
		double** distance = new double* [1 + 2 * window_leftright];
		for (int i = 0; i < 1 + 2 * window_leftright; i++) {
			distance[i] = new double[1 + 2 * window_updown];
			for (int j = 0; j < 1 + 2 * window_updown; j++) {
				distance[i][j] = INF;
				int next_y = curcity.y + i - window_leftright;
				int next_z = curcity.z + j - window_updown;
				if (next_y >= 0 && next_z >= 0 && next_y < YN && next_z < ZN && world[m][next_y][next_z]) {
					Point temp(m, next_y, next_z);
					distance[i][j] = endPoint.getDistance(temp);
					if (distance[i][j] < mindistance)
						mindistance = distance[i][j];
				}
			}
		}
		//safety
		double minfnum = INF;
		double** fnum = new double* [1 + 2 * window_leftright];
		for (int i = 0; i < 1 + 2 * window_leftright; i++) {
			fnum[i] = new double[1 + 2 * window_updown];
			for (int j = 0; j < 1 + 2 * window_updown; j++)
			{
				fnum[i][j] = INF;
				int next_y = curcity.y + i - window_leftright;
				int next_z = curcity.z + j - window_updown;
				if (next_y >= 0 && next_z >= 0 && next_y < YN && next_z < ZN && world[m][next_y][next_z]) {
					int ffnum = 0;
					for (int z = 1; z <= Cansee && z + m < XM; z++)
						for (int zi = 0; zi < 1 + 2 * window_leftright; zi++)
							for (int zj = 0; zj < 1 + 2 * window_updown; zj++)
							{
								int cansee_y = next_y + zi - window_leftright;
								int cansee_z = next_z + zj - window_updown;
								if (cansee_y >= 0 && cansee_z >= 0 && cansee_y < YN && cansee_z < ZN &&
									!world[z + m][cansee_y][cansee_z])
									ffnum++;
							}
					fnum[i][j] = ffnum;
					if (fnum[i][j] < minfnum)
						minfnum = fnum[i][j];
				}

			}
		}
		double tempmax = p[0][0];
		int index_i = 0;
		int index_j = 0;
		for (int i = 0; i < 1 + 2 * window_leftright; i++)
			for (int j = 0; j < 1 + 2 * window_updown; j++)
			{
				int next_y = curcity.y + i - window_leftright;
				int next_z = curcity.z + j - window_updown;
				if (next_y >= 0 && next_z >= 0 &&
					next_y < YN && next_z < ZN &&
					world[m][next_y][next_z]) {
					hasok = true;

					double dis = 1.0 / (distance[i][j] - mindistance + 1);

					double smooth = 1 / ((fabs(double(curcity.y - next_y)) + fabs(double(curcity.z - next_z))) / 2 + 1);

					double safe = 1.0 / ((fnum[i][j] - minfnum) + 1);

					p[i][j] = pow(dis, 0.8) * pow(smooth, _SMOOTH) * pow(safe, _SAFE);
					if (p[i][j] > tempmax) {
						index_i = i;
						index_j = j;
						tempmax = p[i][j];
					}
				}
			}
		if (!hasok) {
			cout << "Path building fail!" << endl;
			return -1;
		}



		Point* SelectedPos = new Point(m, index_i + curcity.y - window_leftright, index_j + curcity.z - window_updown);
		Point temp(SelectedPos->x, SelectedPos->y, SelectedPos->z);
		cnnTour[m] = temp;

		delete SelectedPos;
		for (int i = 0; i < 1 + 2 * window_leftright; i++)
			delete[] p[i];
		delete p;
		for (int i = 0; i < 1 + 2 * window_leftright; i++)
			delete[] distance[i];
		delete distance;
		for (int i = 0; i < 1 + 2 * window_leftright; i++)
			delete[] fnum[i];
		delete fnum;
	}

	Point curcity = cnnTour[XM - 2];
	if ((endPoint.y < (curcity.y - window_leftright)) || (endPoint.y > (curcity.y + window_leftright)) ||
		(endPoint.z < (curcity.z - window_updown)) || (endPoint.z > (curcity.z + window_updown))) {
		cout << "last fail!" << endl;
		return -1;
	}

	cnnTour[XM - 1] = endPoint;

	evaluate(temp);
	printf("[-]fit:%lf Len:%lf Smooth:%.0f safe:%.0f\n", temp.fitness, temp.fitness, temp.soomthFitness, temp.safeFitness);
	return temp.fitness;
}

void Init_ph() {
	clock_t start_time = clock();
	cnn = getCnnLength();
	clock_t end_time = clock();
	double runtime = (double)(end_time - start_time) * 1000 / CLOCKS_PER_SEC;
	printf("runtime: %lf\nCnn: %lf Q_init %lf\n", runtime, cnn, Qinit);
	ph = new double** [XM];
	for (int m = 0; m < XM; m++) {
		ph[m] = new double* [YN];
		for (int i = 0; i < YN; i++) {
			ph[m][i] = new double[ZN];
			for (int j = 0; j < ZN; j++)
				ph[m][i][j] = Qinit;
		}
	}
	AP = new double** [XM];
	for (int m = 0; m < XM; m++) {
		AP[m] = new double* [YN];
		for (int i = 0; i < YN; i++) {
			AP[m][i] = new double[ZN];
			for (int j = 0; j < ZN; j++)
				AP[m][i][j] = 0;
		}
	}
}

void update_Ph(double*** Ph, Ant& S) {
	for (int j = 0; j < XM - 1; j++) {
		Point m;
		m = S.Path[j];
		Ph[m.x][m.y][m.z] = Ph[m.x][m.y][m.z] * (1.0 - _p) + _p * (1.0 / S.fitness);
	}
}

void update_AP(Ant& a) {
	if (!a.isalive) {
		int nn = 0;
		for (int i = a.MovedCityCount - 1; i > 0; i--) {
			AP[a.Path[i].x][a.Path[i].y][a.Path[i].z] +=
				1.0 * pow(lmd, nn++);
		}
	}
	else {
		for (int i = 0; i < a.MovedCityCount; i++) {
			AP[a.Path[i].x][a.Path[i].y][a.Path[i].z] = 0;
		}
	}
}



bool CMP(const Ant* a, const Ant* b) {
	if (a->fitness < b->fitness) { return true; }
	else { return false; }
}

bool vCMP(const Colony& a, const Colony& b) {
	if (a.NiGBest.fitness > b.NiGBest.fitness) { return true; }
	else { return false; }
}

bool overlappingCMP(const Colony& a, const Colony& b) {
	if (a.overlapping == b.overlapping) {
		return a.NiGBest.fitness > b.NiGBest.fitness;
	}
	if (a.overlapping > b.overlapping) { return true; }
	else { return false; }
}


void MACS()
{
	Nc = 0;
	Colony newone(AntAmount);
	newone.NiGBest.fitness = INF;
	newone.since = Nc;
	newone.start_localph(ph);
	myColony.push_back(newone);

	while (Nc<NCMAX && Gbest.fitness > STOP) {
		//STEP1 search with niches
		for (vector<Colony>::iterator g = myColony.begin(); g != myColony.end(); g++) {
			g->createAnts();
			for (int a = 0; a < g->size; a++) {
				double Distance = Distance_rand; 
				double Safe = Safe_rand;
				double Smooth = Smooth_rand; 

				for (int m = 1; m < XM - 1; m++) {
					if (!g->Ants[a].isalive)
						break;
					Point curcity = g->Ants[a].Path[g->Ants[a].MovedCityCount - 1];

					double partsum = 0;
					double** p = new double* [1 + 2 * window_leftright];
					for (int i = 0; i < 1 + 2 * window_leftright; i++) {
						p[i] = new double[1 + 2 * window_updown];
						for (int j = 0; j < 1 + 2 * window_updown; j++)
							p[i][j] = 0;
					}

					double mindistance = INF;
					double** distance = new double* [1 + 2 * window_leftright];
					for (int i = 0; i < 1 + 2 * window_leftright; i++) {
						distance[i] = new double[1 + 2 * window_updown];
						for (int j = 0; j < 1 + 2 * window_updown; j++) {
							distance[i][j] = INF;
							int next_y = curcity.y + i - window_leftright;
							int next_z = curcity.z + j - window_updown;
							if (next_y >= 0 && next_z >= 0 &&
								next_y < YN && next_z < ZN &&
								world[m][next_y][next_z] &&
								space[m][next_y][next_z]) {
								Point temp(m, next_y, next_z);
								distance[i][j] = endPoint.getDistance(temp);
								if (distance[i][j] < mindistance)
									mindistance = distance[i][j];
							}
						}
					}
					//initilize the safe array
					double minfnum = INF;
					double** fnum = new double* [1 + 2 * window_leftright];
					for (int i = 0; i < 1 + 2 * window_leftright; i++) {
						fnum[i] = new double[1 + 2 * window_updown];
						for (int j = 0; j < 1 + 2 * window_updown; j++) {
							fnum[i][j] = INF;
							int next_y = curcity.y + i - window_leftright;
							int next_z = curcity.z + j - window_updown;
							if (next_y >= 0 && next_z >= 0 &&
								next_y < YN && next_z < ZN &&
								world[m][next_y][next_z] &&
								space[m][next_y][next_z]) {

								int ffnum = 0;
								for (int z = 1; z <= Cansee && z + m < XM; z++)
									for (int zi = 0; zi < 1 + 2 * window_leftright; zi++)
										for (int zj = 0; zj < 1 + 2 * window_updown; zj++) {
											int cansee_y = next_y + zi - window_leftright;
											int cansee_z = next_z + zj - window_updown;
											if (cansee_y >= 0 && cansee_z >= 0 &&
												cansee_y < YN && cansee_z < ZN &&
												!world[z + m][cansee_y][cansee_z])
												ffnum++;
										}
								fnum[i][j] = ffnum;
								if (fnum[i][j] < minfnum)
									minfnum = fnum[i][j];
							}
						}
					}

					// update the probability information
					bool hasok = false;
					for (int i = 0; i < 1 + 2 * window_leftright; i++)
						for (int j = 0; j < 1 + 2 * window_updown; j++) {
							int next_y = curcity.y + i - window_leftright;
							int next_z = curcity.z + j - window_updown;
							if (next_y >= 0 && next_z >= 0 &&
								next_y < YN && next_z < ZN &&
								world[m][next_y][next_z] && space[m][next_y][next_z]) {
								hasok = true;

								//-> the heuristic of distance 
								double dis = 1.0 / (distance[i][j] - mindistance + 1);
								//-> the heuristic of smooth 
								double smooth = 1.0 / ((fabs(double(curcity.y - next_y)) + fabs(double(curcity.z - next_z))) / 2 + 1);
								//-> the heuristic of safety
								double safe = 1.0 / ((fnum[i][j] - minfnum) + 1);
								//-> the heuristic of ant dead
								double dead = 1.0 / (log(1.0 + AP[m][next_y][next_z]) + 1.0);

								p[i][j] = pow(g->localph[m][next_y][next_z], Alpha) *
									pow(dead, Belta) *
									pow(dis, Distance) *
									pow(smooth, Smooth) *
									pow(safe, Safe);
								partsum = partsum + p[i][j];
							}

						}

					if (!hasok) {
						g->Ants[a].isalive = false;
						break;
					}

					Point* SelectedPos = NULL;
					double q = rnd_d(0.0, 1.0);

					if (q > q0) {
						do {
							double P_temp = rnd_d(0.0, partsum); 
							double sum = 0.0 - 0.0;  

							for (int i = 0; i < 1 + 2 * window_leftright && SelectedPos == NULL; i++) {
								for (int j = 0; j < 1 + 2 * window_updown && SelectedPos == NULL; j++) {
									int next_y = curcity.y + i - window_leftright;
									int next_z = curcity.z + j - window_updown;
									if (next_y >= 0 && next_z >= 0 &&
										next_y < YN && next_z < ZN &&
										world[m][next_y][next_z] &&
										space[m][next_y][next_z]) {
										sum += p[i][j];
										if (sum >= P_temp)
											SelectedPos = new Point(m, next_y, next_z);
									}
								}
							}
						} while (SelectedPos == NULL || !world[SelectedPos->x][SelectedPos->y][SelectedPos->z]);
					}
					else {
						double tempmax = p[0][0];
						int index_i = 0;
						int index_j = 0;

						for (int i = 0; i < 1 + 2 * window_leftright; i++)
							for (int j = 0; j < 1 + 2 * window_updown; j++)
								if (p[i][j] > tempmax) {
									index_i = i;
									index_j = j;
									tempmax = p[i][j];
								}
						SelectedPos = new Point(m, index_i + curcity.y - window_leftright,
							index_j + curcity.z - window_updown);

					}

					g->localph[SelectedPos->x][SelectedPos->y][SelectedPos->z] =
						g->localph[SelectedPos->x][SelectedPos->y][SelectedPos->z] * (1.0 - _c) +
						Q0 * _c;
					ph[SelectedPos->x][SelectedPos->y][SelectedPos->z] =
						ph[SelectedPos->x][SelectedPos->y][SelectedPos->z] * (1.0 - _c) +
						Q0 * _c;
					Point temp(SelectedPos->x, SelectedPos->y, SelectedPos->z);
					g->Ants[a].Path[g->Ants[a].MovedCityCount] = temp;
					g->Ants[a].MovedCityCount++;

					delete SelectedPos;
					for (int i = 0; i < 1 + 2 * window_leftright; i++)
						delete[] p[i];
					delete p;
					for (int i = 0; i < 1 + 2 * window_leftright; i++)
						delete[] distance[i];
					delete distance;
					for (int i = 0; i < 1 + 2 * window_leftright; i++)
						delete[] fnum[i];
					delete fnum;
				}
			}
			for (int a = 0; a < g->size; a++) {
				if (!g->Ants[a].isalive) {
					deadamount++;
					avgdead[Nc]++;
					continue;
				}
				Point curcity = g->Ants[a].Path[g->Ants[a].MovedCityCount - 1];

				if ((endPoint.y < (curcity.y - window_leftright)) || (endPoint.y > (curcity.y + window_leftright)) ||
					(endPoint.z < (curcity.z - window_updown)) || (endPoint.z > (curcity.z + window_updown))) {
					g->Ants[a].isalive = false;
					continue;
				}
				g->Ants[a].Path[g->Ants[a].MovedCityCount] = endPoint;
				g->Ants[a].MovedCityCount++;
				if (g->Ants[a].isalive) {
					evaluate(g->Ants[a]);
					if (g->Ants[a].fitness < g->NiGBest.fitness)
						g->NiGBest = g->Ants[a];
				}
			}
		}

		for (vector<Colony>::iterator g = myColony.begin(); g != myColony.end(); g++) {
			if (g->NiGBest.fitness < Gbest.fitness)
				Gbest = g->NiGBest;
		}
		if (deadupdate) {
			for (vector<Colony>::iterator g = myColony.begin(); g != myColony.end(); g++) {
				for (int i = 0; i < g->size; i++) {
					if (!g->Ants[i].isalive) {
						update_AP(g->Ants[i]);
					}
				}
			}
		}

		fit[Nc] += Gbest.fitness;
		if (Nc >= GAP && Nc % GAP == 0) {
			int num_alive_ants = 0;

			for (int i = 0; i < myColony.size(); i++) {
				int p1, p2;
				for (p1 = 0, p2 = 0; p2 < myColony[i].size; p2++) {
					if (myColony[i].Ants[p1].isalive == true) {
						myColony[i].Ants[p1] = myColony[i].Ants[p2];
						p1++;
						num_alive_ants++;
					}
				}
				myColony[i].size = p1;
			}
			int num_dead_ants = AntAmount - num_alive_ants;
			// Algorithm3 Create niches
			int num_TBD = 0;
			double minNicheDist = INF;
			for (int i = 0; i < myColony.size() - 1; i++) {
				for (int j = i + 1; j < myColony.size(); j++) {
					minNicheDist = min(minNicheDist, myColony[i].NiGBest.checkSimilarity(myColony[j].NiGBest));
				}
			}
			int myColony_size = myColony.size();

			for (int i = 0; i < myColony_size; i++) {
				if (myColony_size > MAXNICHE) break;
				double min_dist = INF;
				int min_idx = -1;
				for (int k = myColony[i].size - 1; k >= 0; k--) {
					for (int j = 0; j < myColony.size(); j++) {
						double dist = myColony[i].Ants[k].checkSimilarity(myColony[j].NiGBest);
						if (dist < min_dist) {
							min_idx = j;
							min_dist = dist;
						}
					}
					if (min_dist > SAME) {
						if (myColony.size() < MAXNICHE && rnd_d(0, 1) <= (1.0 / (1 + exp(-1.0 / (myColony[i].Ants[k].fitness / Gbest.fitness * min_dist / minNicheDist))))) {
							Colony newone(1);
							newone.NiGBest = myColony[i].Ants[k];
							newone.size = 1;
							newone.since = Nc;
							newone.start_localph(ph);
							myColony.push_back(newone);
						}
						else {
							num_TBD++;
						}
						for (int j = k; j < myColony[i].size - 1; j++)
							myColony[i].Ants[j] = myColony[i].Ants[j + 1];
						myColony[i].size--;

					}
					else {
						if (min_idx != i) {
							if (myColony[min_idx].size == 0) {
								myColony[min_idx].restart_localph(ph);
							}

							myColony[min_idx].Ants[myColony[min_idx].size] = myColony[i].Ants[k];
							myColony[min_idx].size++;

							if (myColony[i].Ants[k].fitness < myColony[min_idx].NiGBest.fitness) {
								myColony[min_idx].NiGBest = myColony[i].Ants[k];
							}

							for (int j = k; j < myColony[i].size - 1; j++)
								myColony[i].Ants[j] = myColony[i].Ants[j + 1];
							myColony[i].size--;
						}
					}

				}

			}
			int candidate_num = num_TBD + num_dead_ants;
			int left_num = num_TBD + num_dead_ants;

			if (left_num > 0) {
				double sum_fitness = 0;
				int max_idx = 0;

				double max_fitness = myColony[0].NiGBest.fitness;
				for (int i = 0; i < myColony.size(); i++) {
					sum_fitness += myColony[i].NiGBest.fitness;
					if (max_fitness < myColony[i].NiGBest.fitness) {
						max_fitness = myColony[i].NiGBest.fitness;
						max_idx = i;
					}
				}
				for (int i = 0; i < myColony.size(); i++) {
					int assign_num = (int)(candidate_num * myColony[i].NiGBest.fitness / sum_fitness);
					myColony[i].size += assign_num;
					left_num -= assign_num;
				}
				myColony[max_idx].size += left_num;
			}

			for (int i = myColony_size - 1; i >= 0; i--) {
				if (myColony[i].size == 0) {
					myColony[i].stop_localph();
					myColony.erase(myColony.begin() + i);
				}
			}

			// Algorithm4 É¾³ýÐ¡Éú¾³
			if (myColony.size() > 1) {
				for (vector<Colony>::iterator it = myColony.begin(); it != myColony.end(); it++) {
					it->overlapping = 0;
				}
				for (int i = 0; i < myColony.size() - 1; i++)
				{
					for (int j = i + 1; j < myColony.size(); j++) {
						if (myColony[i].NiGBest.checkSimilarity(myColony[j].NiGBest) < SAME) {
							myColony[i].overlapping++;
							myColony[j].overlapping++;
						}
					}
				}


				sort(myColony.begin(), myColony.end(), overlappingCMP);
				for (int i = 0; i < myColony.size() - 1; i++)
				{
					double dist = INF;
					int tar = -1;
					double tmp = INF;
					for (int j = i + 1; j < myColony.size(); j++) {
						tmp = myColony[i].NiGBest.checkSimilarity(myColony[j].NiGBest);
						if (tmp < SAME / sqrt(2.0) && tmp < dist) {
							dist = tmp;
							tar = j;
						}
					}
					if (tar != -1) {
						if (myColony[tar].NiGBest.fitness < myColony[i].NiGBest.fitness) {
							myColony[tar].size += myColony[i].size;
							tar = i;
							i--;
						}
						else {
							myColony[i].size += myColony[tar].size;
						}
						myColony[tar].stop_localph();
						myColony.erase(myColony.begin() + tar);
					}

				}
			}
		}


		for (vector<Colony>::iterator g = myColony.begin(); g != myColony.end(); g++) {
			update_Ph(g->localph, g->NiGBest);
		}
		update_Ph(ph, Gbest);
		Nc++;
	}
}
void run(double& deadA, double& runtime, double& fitness, double& LenFitness, double& SafeFitness, double& SmoothFitness, int index) {
	printf("\nstart MACS alogrithm...\n");

	while (myColony.size() != 0) {
		myColony.begin()->stop_localph();
		myColony.erase(myColony.begin());
	}
	Gbest.fitness = INF;
	deadamount = 0;
	myColony.clear();

	clock_t start_time = clock();

	MACS();
	clock_t end_time = clock();
	runtime = (double)(end_time - start_time) * 1000 / CLOCKS_PER_SEC;

	fitness = Gbest.fitness;
	LenFitness = Gbest.PathLength;
	SafeFitness = Gbest.safeFitness;
	SmoothFitness = Gbest.soomthFitness;
	printf("[END] (%d) FIT:%f Len:%lf Dangerous:%.0f Smooth:%.0f\n", myColony.size(),
		Gbest.fitness, Gbest.PathLength, Gbest.safeFitness, Gbest.soomthFitness);

	for (vector<Colony>::iterator g = myColony.begin(); g != myColony.end(); g++) {
		printf(" \t * \t (%d,since:%d) FIT:%f Len:%lf Dangerous:%.0f Smooth:%.0f\n", g->size, g->since,
			g->NiGBest.fitness, g->NiGBest.PathLength, g->NiGBest.safeFitness,
			g->NiGBest.soomthFitness);
	}

	deadA = deadamount / (1.0 * AntAmount * NCMAX);


#ifdef	OUTPUTDEF
	char filename[500];
	sprintf_s(filename, "%s/BestPath/%s_run_%d.txt", outdir, fullinstancename, index);

	FILE* stream;
	if ((stream = fopen((filename), "w")) == NULL)
	{
		printf("Pathout %s fails", filename);
		system("pause");
		exit(-2);
	}
	for (vector<Colony>::iterator g = myColony.begin(); g != myColony.end(); g++) {
		for (int i = 0; i < XM; i++) {
			fprintf(stream, "%d %d %d\n", g->NiGBest.Path[i].x, g->NiGBest.Path[i].y, g->NiGBest.Path[i].z);
		}
	}
	fclose(stream);

	sprintf_s(filename, "%s/NicheInfo/%s_run_%d.txt", outdir, fullinstancename, index);
	stream = fopen(filename, "w");
	int k = 0;
	for (vector<Colony>::iterator g = myColony.begin(); g != myColony.end(); g++, k++) {
		fprintf(stream, "%d,%lf,%lf,%lf,%lf\n", k, g->NiGBest.fitness, g->NiGBest.PathLength, g->NiGBest.safeFitness, g->NiGBest.soomthFitness);

	}
	fclose(stream);

#endif

#ifdef	OUTPUTDEF
	sprintf_s(filename, "%s/APMatrix/%s_run_%d.txt", outdir, fullinstancename, index);
	if ((stream = fopen(filename, "w")) == NULL)
	{
		printf("1275  APout.c_str() %s fails", filename);
		system("pause");
		exit(-2);
	}
	for (int i = 0; i < scale; i++)
		for (int x = scale - 1; x >= 0; x--)
			for (int y = scale - 1; y >= 0; y--) {
				if (AP[i][x][y] != 0)
					fprintf(stream, "%d %d %d %lf\n", i, x, y, AP[i][x][y]);
			}
	fclose(stream);
#endif

	for (int m = 0; m < XM; m++) {
		for (int i = 0; i < YN; i++) {
			for (int j = 0; j < ZN; j++)
				ph[m][i][j] = Qinit;
		}
	}
	for (int m = 0; m < XM; m++) {
		for (int i = 0; i < YN; i++) {
			for (int j = 0; j < ZN; j++)
				AP[m][i][j] = 0;
		}
	}
}

//----------------------------------------------
int main(int argc, char* argv[]) {
	srand((unsigned)time(NULL));
	//srand((1));
	get3DWorld();
	spacial();
	getSuspended();
	getCurrentVol();
	Init_ph();
	double rtime[repeat];
	double fitness[repeat];
	double LenF[repeat];
	double SafeF[repeat];
	double SmoothF[repeat];
	double deadA[repeat];
	double su = 0;
	for (int i = 0; i < NCMAX; i++)
		fit[i] = 0;

	FILE* stream;
	if ((stream = fopen(csvpath, "w+")) == NULL)
	{
		printf("csvpath %s fails", csvpath);
		system("pause");
		exit(-2);
	}
	char filename[500];
	for (int i = 0; i < repeat; i++) {
		run(deadA[i], rtime[i], fitness[i], LenF[i], SafeF[i], SmoothF[i], i);
		cout << i + 1 << " ----- Runtime:" << rtime[i] << " Fitness:" << fitness[i] << " Len:" << LenF[i] <<
			" Safe:" << SafeF[i] << " Smooth:" << SmoothF[i] << " DeadAmount:" << deadA[i] << endl;
		su = su + rtime[i];
		fprintf(stream, "%d,%lf,%lf,%lf,%lf,%lf,%d,%lf\n", (i + 1), rtime[i], fitness[i], LenF[i], SafeF[i], SmoothF[i], myColony.size(), deadA[i]);
	}
	fclose(stream);
	if ((stream = fopen(itpath, "w")) == NULL)
	{
		printf("itpath %s fails", itpath);
		system("pause");
		exit(-1);
	}

	for (int i = 0; i < NCMAX; i++) {
		fprintf(stream, "%lf\n", fit[i] / double(repeat));
	}
	fclose(stream);

	if ((stream = fopen(avgdeadout, "w")) == NULL)
	{
		printf("avgdeadout %s fails", avgdeadout);
		system("pause");
		exit(-2);
	}
	for (int i = 0; i < NCMAX; i++) {
		fprintf(stream, "%lf\n", avgdead[i] / double(repeat));
	}
	fclose(stream);

	printf("AVG Time:%lf\n", su / double(repeat));

	for (int m = 0; m < XM; m++) {
		for (int i = 0; i < YN; i++) {
			delete[] world[m][i];
		}
		delete[] world[m];
	}
	delete[]world;
	world = NULL;

	for (int m = 0; m < XM; m++) {
		for (int i = 0; i < YN; i++) {
			delete[] space[m][i];
		}
		delete[] space[m];
	}
	delete[]space;
	space = NULL;
	//system("pause");
}