#include <stdio.h>

int main(void) {
	int num = 0;
	int buf[5] = { 0 };
	char dan[5][3] = { "", "��", "��", "õ", "��" };

	printf("Input integer (1 ~ 32,765) : ");
	scanf("%d", &num);

	int i = -1;
	while (++i < 5) {
		buf[i] = num % 10;

		num /= 10;
	}
	int j = 5;
	while (--j >= 0) {
		if (buf[j] == 0) continue;
		printf("%d%s ", buf[j], dan[j]);
	}

	return 0;
}