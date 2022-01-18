/*
* 파일명 : piano.c
* 목적 및 기본 기능
*	키를 입력받아 몇 옥타브인지 판단하고 해당 음의 주파수로 소리를 출력
* 작성자 : 김주환(21812158)
* 작성일 : 2021년 3월 22일
*/

#include <stdio.h>
#include <Windows.h>
#include <conio.h>

void mapping_key_to_freq(void);

int main(void) {
	printf("\nSimple Electric Piano !!\n");
	printf("'A' ~ 'J' : octave 8 도 레 미 파 솔 라 시, \n");
	printf("'Z' ~ 'M' : octave 7 도 레 미 파 솔 라 시, \n");
	printf("'q' ~ 'u' : octave 6 도 레 미 파 솔 라 시, \n");
	printf("'a' ~ 'j' : octave 5 도 레 미 파 솔 라 시, and \n");
	printf("'z' ~ 'm' : octave 4 도 레 미 파 솔 라 시, \n");
	printf("input next key : \n");

	mapping_key_to_freq();

	return 0;
}


void mapping_key_to_freq(void) {
	const char sound_k[7][3] = { "도", "레", "미", "파", "솔", "라", "시" };
	const int keys_to_freq[2][2][26] = {
		// alt_on == 0
		{
			{
				523, 392, 330, 660, 1323, 698, 784, 880, -1, 988, -1, -1, 494,
				440, -1, -1, 1048, 1396, 588, 1568, 1976, 349, 1176, 294, 1760, 262
			}, {
				4186, 3136, 2637, 5274, -1, 5588, 6272, 7040, -1, 7902, -1, -1, 3951,
				3520, -1, -1, -1, -1, 4699, -1, -1, 2794, -1, 2349, -1, 2093
			}
		}, {// alot_on == 1
			{
				554, 415, 330, 660, 1323, 740, 830, 932, -1, 988, -1, -1, 494,
				466, -1, -1, 1109, 1480, 622, 1661, 1976, 370, 1245, 311, 1865, 277
			}, {
				4435, 3322, 2637, 5274, -1, 5920, 6645, 7459, -1, 7902, -1, -1, 3951,
				3729, -1, -1, -1, -1, 4978, -1, -1, 2960, -1, 2489, -1, 2217
			}
		}
	};
	const int keys_to_oct_sound[5][7] = {
	{
		122, 120, 99, 118, 98, 110, 109
}, {
		97, 115, 100, 102, 103, 104, 106
}, {
		113, 119, 101, 114, 116, 121, 117
}, {
		90, 88, 67, 86, 66, 78, 77
}, {
		65, 83, 68, 70, 71, 72, 74
}
	};
	char ch;
	while ((ch = _getch()) != 27) {
		int freq = -1, i, j;
		int temp = 0;
		char alt_on = 0;
		if (GetAsyncKeyState(VK_MENU) & 0x8000) {
			alt_on = 1;
		}

		if (65 <= ch && ch <= 90) freq = keys_to_freq[alt_on][1][ch - 65];
		else if (97 <= ch && ch <= 122) freq = keys_to_freq[alt_on][0][ch - 97];
		else freq = -1;

		for (i = 0; i < 5; i++) {
			for (j = 0; j < 7; j++) {
				if (ch == keys_to_oct_sound[i][j]) {
					temp++;
					break;
				}
			}
			if (temp == 1) break;
		}

		if (freq != -1) {
			printf("inputkey (");
			if (alt_on == 1) printf("Alt + ");
			printf("%c) : %d oct %s", ch, i + 4, sound_k[j]);
			if (alt_on == 1) printf("#");
			printf(", freq(% 3d)\n", freq);
			Beep(freq, 100);
		}
		else printf("input key (%c) is wrong key input..\n", ch);
	}
}