/*
* ���ϸ� : calc_cylinder_v_sa.cpp
* ���� �� �⺻ ��� : 
*	����ڷκ��� ������� ������, ������� ���̸� �Է¹ް�, �� �������
*	ü��(volume)�� ǥ����(surface area)�� ���
* �ۼ��� : ����ȯ(21812158)
* �ۼ��� : 2021�� 3�� 8��
*/
#include <stdio.h>

#define PI 3.141592

int main(void) {
	double radius, height, volume, surface_area;

	printf("\n  INPUT RADIUS : ");
	scanf("%lf", &radius);
	printf("  INPUT HEIGHT : ");
	scanf("%lf", &height);

	volume = PI * radius * radius * height;
	surface_area = PI * radius * radius * 2 + 2 * PI * radius * height;

	printf("\n  ================================\n\n");
	printf("  VOLUME : %lf\n  SURFACE AREA : %lf\n\n", volume, surface_area);

	return 0;
}