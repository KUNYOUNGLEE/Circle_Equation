#include <stdio.h>
#include <math.h>
#include <cmath>

#define MIN(X,Y) ((X) < (Y) ? (X) : (Y))  
#define MAX(X,Y) ((X) > (Y) ? (X) : (Y))
#define ROUND(x,dig) (floor((x)*pow(10,dig)+0.5)/pow(10,dig))

struct Point //X,Y 3개점을 넣기위한 구조체
{
	double X, Y;
};

void Get3point(Point *XY_point);//세점을 입력받는 함수
double search_distance(Point *XY_point); //반지름의 최댓값을 구하기위한 함수 R_max
void search_Value(double X_max, double X_min, double Y_max, double Y_min, double R_max,double pre_min, Point *XY_point); //원의방정식 a,b,r을 구하는 함수


int main(void)
{
	Point XY_Point[3];

	Get3point(XY_Point);//세점을 입력받는 함수

	//각각 3개점의 대한 최댓값, 최소값을 구함.
	double X_max = MAX(XY_Point[0].X, MAX(XY_Point[1].X, XY_Point[2].X));
	double X_min = MIN(XY_Point[0].X, MIN(XY_Point[1].X, XY_Point[2].X));
	double Y_max = MAX(XY_Point[0].Y, MAX(XY_Point[1].Y, XY_Point[2].Y));
	double Y_min = MIN(XY_Point[0].Y, MIN(XY_Point[1].Y, XY_Point[2].Y));

	//원의방정식 a,b,r을 구하는 함수
	search_Value( X_max, X_min,  Y_max, Y_min, search_distance(XY_Point), 9999999, XY_Point);

	return 0;

}	

void Get3point(Point *XY_Point)
{
	for (int i = 0; i < 3; i++)
	{

		if (i == 0)
		{
			while (1)
			{
				printf("%d번째 점 (X%d, Y%d)좌표를 입력하세요[X<=0, Y<=0] :", i + 1, i + 1, i + 1);
				scanf("%lf %lf", &XY_Point[i].X, &XY_Point[i].Y);
				if ((XY_Point[i].X <= 0) && (XY_Point[i].Y <= 0))
					break;
				else
					printf("범위를 벗어났습니다. 다시 입력해주세요\n");
			}
		}
		else if (i == 1)
		{
			while (1)
			{
				printf("%d번째 점 (X%d, Y%d)좌표를 입력하세요[Y>=0] :", i + 1, i + 1, i + 1);
				scanf("%lf %lf", &XY_Point[i].X, &XY_Point[i].Y);
				if ((XY_Point[i].Y >= 0))
					break;
				else
					printf("범위를 벗어났습니다. 다시 입력해주세요\n");
			}
		}
		else if (i == 2)
		{
			while (1)
			{
				printf("%d번째 점 (X%d, Y%d)좌표를 입력하세요[X>=0, Y<=0] :", i + 1, i + 1, i + 1);
				scanf("%lf %lf", &XY_Point[i].X, &XY_Point[i].Y);
				if ((XY_Point[i].X >= 0) && (XY_Point[i].Y<=0))
					break;
				else
					printf("범위를 벗어났습니다. 다시 입력해주세요\n");
			}


		}
	}
}

void search_Value(double X_max, double X_min,  double Y_max, double Y_min, double R_max, double pre_min, Point *XY_point)
{
	//원의방정식 a,b,r을 구하는 함수
	double X_length, Y_length;
	X_length = ROUND((X_max - X_min), 5) / 100;
	Y_length = ROUND((Y_max - Y_min), 5) / 100;
	double min = 99999;
	double A, B, C; //원의방정식 3개의 변수이름
	double result_a, result_b, result_r;

	
	for(double a=X_min; a<=X_max; a += X_length)
		for(double b=Y_min; b<=Y_max; b += Y_length)
			for (double r = 1; r <= R_max; r += (ROUND(R_max, 5) / 100)  )
			{
				A = fabs(pow(XY_point[0].X - a, 2.0) + pow(XY_point[0].Y - b, 2.0) - pow(r, 2.0));
				B = fabs(pow(XY_point[1].X - a, 2.0) + pow(XY_point[1].Y - b, 2.0) - pow(r, 2.0));
				C = fabs(pow(XY_point[2].X - a, 2.0) + pow(XY_point[2].Y - b, 2.0) - pow(r, 2.0));

				if (min > (A + B + C))
				{
					min = (A + B + C);
					result_a = a;
					result_b = b;
					result_r = r;
				}			
			}

	//if(min < 0.1 )
	//{
	//	printf("종료 결과 A+B+C의 가장 작은 값은 : %.5lf 이다 , 그리고 a : %.5lf , b : %.5lf , r : %.5lf 이다.\n", min, result_a, result_b, result_r);
	//	return ;
	//}
	//else 
	//{
	if (fabs(pre_min - min) < 0.005)
	{
		printf("종료 결과 A+B+C의 가장 작은 값은 : %.5lf 이다 , 그리고 a : %.5lf , b : %.5lf , r : %.5lf 이다.\n", min, result_a, result_b, result_r);
		return;
	}
	else
	{
		printf("이번 연산에서 A+B+C의 가장 작은 값은 : %.5lf 이다 , 그리고 a : %.5lf , b : %.5lf , r : %.5lf 이다.\n", min, result_a, result_b, result_r);
		search_Value(result_a + ((X_length * 10) / 2), result_a - ((X_length * 10) / 2), result_b + ((Y_length * 10) / 2), result_b - ((Y_length * 10) / 2), R_max, min, XY_point);
	}
	//}

}

double search_distance(Point *X)
{
	double maxvalue;
	double value1 = sqrt(pow(X[0].X -  X[1].X, 2.0) + pow(X[0].Y - X[1].Y, 2.0));
	double value2 = sqrt(pow(X[1].X - X[2].X, 2.0) + pow(X[1].Y - X[2].Y, 2.0));
	double value3 = sqrt(pow(X[0].X - X[2].X, 2.0) + pow(X[0].Y - X[2].Y, 2.0));

	if (value1 >= value2 && value1 >= value3)
		return value1;

	else if (value2 >= value1 && value2 >= value3)
		return value2;

	else
		return value3;
}