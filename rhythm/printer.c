#include <stdio.h>
#include "../util/util.h"
#include "rhythm.h"

void r_print_SS() {
	printf("\x1b[97m");
	printf("  ┏━━━━━┏━━━━━\n");
	printf("  ┃      ┃      \n");
	printf("  ┗━━━━┓┗━━━━┓\n");
	printf("       ┃      ┃\n");
	printf("  ━━━━━┛━━━━━┛\n");
	printf("\x1b[0m");
}

void r_print_S() {
	printf("\x1b[91m");
	printf("  ┏━━━━━\n");
	printf("  ┃      \n");
	printf("  ┗━━━━┓\n");
	printf("       ┃\n");
	printf("  ━━━━━┛\n\n");
	printf("\x1b[0m");
}
void r_print_A() {
	printf("\x1b[32m");
	printf("  ┏━━━━┓\n");
	printf("  ┃    ┃\n");
	printf("  ┣━━━━┫\n");
	printf("  ┃    ┃\n");
	printf("  ┃    ┃\n\n");
	printf("\x1b[0m");
}
void r_print_B() {
	printf("\x1b[34m");
	printf("  ┏━━━━┓\n");
	printf("  ┃    ┃\n");
	printf("  ┣━━━━┫\n");
	printf("  ┃    ┃\n");
	printf("  ┣━━━━┛\n\n");
	printf("\x1b[0m");
}
void r_print_C() {
	printf("\x1b[35m");
	printf("  ┏━━━━┓\n");
	printf("  ┃      \n");
	printf("  ┃      \n");
	printf("  ┃      \n");
	printf("  ┗━━━━┛\n\n");
	printf("\x1b[0m");
}
void r_print_D() {
	printf("\x1b[33m");
	printf("  ┏━━━━┓\n");
	printf("  ┃    ┃\n");
	printf("  ┃    ┃\n");
	printf("  ┃    ┃\n");
	printf("  ┣━━━━┛\n\n");
	printf("\x1b[0m");
}

void r_print_note(int n) {
	switch (n) 
	{
	case 0: printf("   "); break;
	case 1: printf(" ♦ "); break;
	case 2: printf(" \x1b[31m*\x1b[0m "); break;
	case 3: printf(" \x1b[33m*\x1b[0m "); break;
	case 4: printf(" \x1b[33m*\x1b[0m "); break;
	case 5: printf(" \x1b[34m*\x1b[0m "); break;
	case 6: printf("   "); break;
	default:
		break;
	}
}

void r_print_note_hit(int n, int p, int b1, int b2) {
	if (n == 1) {
		printf("-♦-");
		return;
	}
	if (n == 2 || p == 2) {
		printf("\x1b[101m---\x1b[0m");
		return;
	}
	if (b1 == 3 || n == 3 || p == 4) {
		printf("\x1b[103m---\x1b[0m");
		return;
	}
	if (b2 == 5 || b1 == 5) {
		printf("\x1b[104m---\x1b[0m");
		return;
	}
	else {
		printf("---");
	}
	return;
}

void r_print_score(map_status* status) {
	double acc = r_accuracy(status->result);
	printf("\n");
	divider("", 'b');
	printf("Point: %d\n", status->point);
	printf("Combo: x%d\n", status->combo);
	printf("Accuracy: %.2f%%\n", acc);
	printf("\n");
	divider("", 'b');
}

void r_print_rank(int result[5]) {
	double acc = r_accuracy(result);
	if (acc == 100) {
		r_print_SS();
	}
	else if (result[3] == 0 && acc > 92) {
		r_print_S();
	}
	else if (acc > 93) {
		r_print_A();
	}
	else if (acc > 85) {
		r_print_B();
	}
	else if (acc > 75) {
		r_print_C();
	}
	else {
		r_print_D();
	}
	return;
}

