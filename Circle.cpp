#include <stdio.h>
#include <math.h>
#include <cmath>

#define MIN(X,Y) ((X) < (Y) ? (X) : (Y))  
#define MAX(X,Y) ((X) > (Y) ? (X) : (Y))
#define ROUND(x,dig) (floor((x)*pow(10,dig)+0.5)/pow(10,dig))

struct Point //X,Y 3������ �ֱ����� ����ü
{
	double X, Y;
};

void Get3point(Point *XY_point);//������ �Է¹޴� �Լ�
double search_distance(Point *XY_point); //�������� �ִ��� ���ϱ����� �Լ� R_max
void search_Value(double X_max, double X_min, double Y_max, double Y_min, double R_max,double pre_min, Point *XY_point); //���ǹ����� a,b,r�� ���ϴ� �Լ�


int main(void)
{
	Point XY_Point[3];

	Get3point(XY_Point);//������ �Է¹޴� �Լ�

	//���� 3������ ���� �ִ�, �ּҰ��� ����.
	double X_max = MAX(XY_Point[0].X, MAX(XY_Point[1].X, XY_Point[2].X));
	double X_min = MIN(XY_Point[0].X, MIN(XY_Point[1].X, XY_Point[2].X));
	double Y_max = MAX(XY_Point[0].Y, MAX(XY_Point[1].Y, XY_Point[2].Y));
	double Y_min = MIN(XY_Point[0].Y, MIN(XY_Point[1].Y, XY_Point[2].Y));

	//���ǹ����� a,b,r�� ���ϴ� �Լ�
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
				printf("%d��° �� (X%d, Y%d)��ǥ�� �Է��ϼ���[X<=0, Y<=0] :", i + 1, i + 1, i + 1);
				scanf("%lf %lf", &XY_Point[i].X, &XY_Point[i].Y);
				if ((XY_Point[i].X <= 0) && (XY_Point[i].Y <= 0))
					break;
				else
					printf("������ ������ϴ�. �ٽ� �Է����ּ���\n");
			}
		}
		else if (i == 1)
		{
			while (1)
			{
				printf("%d��° �� (X%d, Y%d)��ǥ�� �Է��ϼ���[Y>=0] :", i + 1, i + 1, i + 1);
				scanf("%lf %lf", &XY_Point[i].X, &XY_Point[i].Y);
				if ((XY_Point[i].Y >= 0))
					break;
				else
					printf("������ ������ϴ�. �ٽ� �Է����ּ���\n");
			}
		}
		else if (i == 2)
		{
			while (1)
			{
				printf("%d��° �� (X%d, Y%d)��ǥ�� �Է��ϼ���[X>=0, Y<=0] :", i + 1, i + 1, i + 1);
				scanf("%lf %lf", &XY_Point[i].X, &XY_Point[i].Y);
				if ((XY_Point[i].X >= 0) && (XY_Point[i].Y<=0))
					break;
				else
					printf("������ ������ϴ�. �ٽ� �Է����ּ���\n");
			}


		}
	}
}

void search_Value(double X_max, double X_min,  double Y_max, double Y_min, double R_max, double pre_min, Point *XY_point)
{
	//���ǹ����� a,b,r�� ���ϴ� �Լ�
	double X_length, Y_length;
	X_length = ROUND((X_max - X_min), 5) / 100;
	Y_length = ROUND((Y_max - Y_min), 5) / 100;
	double min = 99999;
	double A, B, C; //���ǹ����� 3���� �����̸�
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
	//	printf("���� ��� A+B+C�� ���� ���� ���� : %.5lf �̴� , �׸��� a : %.5lf , b : %.5lf , r : %.5lf �̴�.\n", min, result_a, result_b, result_r);
	//	return ;
	//}
	//else 
	//{
	if (fabs(pre_min - min) < 0.005)
	{
		printf("���� ��� A+B+C�� ���� ���� ���� : %.5lf �̴� , �׸��� a : %.5lf , b : %.5lf , r : %.5lf �̴�.\n", min, result_a, result_b, result_r);
		return;
	}
	else
	{
		printf("�̹� ���꿡�� A+B+C�� ���� ���� ���� : %.5lf �̴� , �׸��� a : %.5lf , b : %.5lf , r : %.5lf �̴�.\n", min, result_a, result_b, result_r);
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