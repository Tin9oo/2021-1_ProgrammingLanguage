/*
* 파일명 : calc_cylinder_v_sa.cpp
* 목적 및 기본 기능 : 
*	사용자로부터 원기둥의 반지름, 원기둥의 높이를 입력받고, 이 원기둥의
*	체적(volume)과 표면적(surface area)를 계산
* 작성자 : 김주환(21812158)
* 작성일 : 2021년 3월 8일
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