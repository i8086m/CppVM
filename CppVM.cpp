#include <iostream>
#include <stdint.h>
#include <conio.h>
#include <fstream>
#include <cstdlib>

int state = 0; // Костыль, режим VM/MIDE
uint8_t a,b,c = 0; // Регистры, чё
uint8_t ram[256]; // Это память
int i = 0; // Программный счетчик
int tmp; // Системная переменная для костылей
bool f[4] = {0,0,0,0}; // Это флаги если что

std::ifstream fin("bios.cvm"); // Чтение файла

// TODO: Gfx[]
// TODO: File Access

int main() {

	std::cout << "CppVM" << std::endl;//v170730+e171221
	std::cout << "Verion 1.0.0 Fixed Final" << std::endl;

	while (i < 255) { // erase ram
		ram[i] = 0;
		i++;
	}
	ram[255] = 255; // чтоб не циклилось
	i = 0; // pc в ноль

	int buff;
 	int bc = 0;

    if (!fin.is_open()) {
        state = 1;
        goto d;
    }
    else {
    	while (bc < 255) {
    		fin >> buff;
    		ram[bc] = buff;
    		bc++;
		}
    	fin.close();
	}

	std::cout << "Running" << std::endl;

	while (state == 0) {
		r:

		if (ram[i] == 0) {
		std::cout << "Null" << std::endl;
		}

		if (ram[i] == 1) {
			a++;
		}

		if (ram[i] == 2) {
			b++;
		}

		if (ram[i] == 3) {
			c++;
		}

		if (ram[i] == 4) {
			a--;
		}

		if (ram[i] == 5) {
			b--;
		}

		if (ram[i] == 6) {
			c--;
		}

		if (ram[i] == 7) {
			i++;
			if (a-ram[i] == 0) {
				f[0] = true;
			}
			else {
				f[0] = false;
			}
			if (a-ram[i] < 0) {
				f[1] = true;
			}
			else {
				f[1] = false;
			}
			i++;
			goto r;
		}

		if (ram[i] == 8) {
			i++;
			if (b-ram[i] == 0) {
				f[0] = true;
			}
			else {
				f[0] = false;
			}
			if (b-ram[i] < 0) {
				f[1] = true;
			}
			else {
				f[1] = false;
			}
			i++;
			goto r;
		}

		if (ram[i] == 9) {
			i++;
			if (c-ram[i] == 0) {
				f[0] = true;
			}
			else {
				f[0] = false;
			}
			if (c-ram[i] < 0) {
				f[1] = true;
			}
			else {
				f[1] = false;
			}
			i++;
			goto r;
		}

		if (ram[i] == 10) {
			std::cout << +a;
		}

		if (ram[i] == 11) {
			std::cout << a;
		}

		if (ram[i] == 12) {
			std::cout << "\n";
		}

		if (ram[i] == 13) {
			std::cin >> tmp;
			a = tmp;
		}

		if (ram[i] == 14) {
			a = getch();
		}

		if (ram[i] == 15) {
			system("cls");
		}

		if (ram[i] == 20) {
			i = 0;
			goto r;
		}

		if (ram[i] == 21) {
			i++;
			i = ram[i];
			goto r;
		}

		if (ram[i] == 22) {
			if (f[0]) {
				i++;
				i = ram[i];
				goto r;
			}
			i=i+2;
			goto r;
		}

		if (ram[i] == 23) {
			if (!f[0]) {
				i++;
				i = ram[i];
				goto r;
			}
			i=i+2;
			goto r;
		}

		if (ram[i] == 24) {
			if (f[1]) {
				i++;
				i = ram[i];
				goto r;
			}
			i=i+2;
			goto r;
		}

		if (ram[i] == 25) {
			if (!f[1]) {
				i++;
				i = ram[i];
				goto r;
			}
			i=i+2;
			goto r;
		}

		if (ram[i] == 30) {
			a = b;
		}

		if (ram[i] == 31) {
			a = c;
		}

		if (ram[i] == 32) {
			b = a;
		}

		if (ram[i] == 33) {
			b = c;
		}

		if (ram[i] == 34) {
			c = a;
		}

		if (ram[i] == 35) {
			c = b;
		}

		if (ram[i] == 40) {
			i++;
			a=ram[i];
			i++;
			goto r;
		}

		if (ram[i] == 41) {
			i++;
			b=ram[i];
			i++;
			goto r;
		}

		if (ram[i] == 42) {
			i++;
			c=ram[i];
			i++;
			goto r;
		}

		if (ram[i] == 50) {
			i++;
			a=ram[ram[i]];
			i++;
			goto r;
		}

		if (ram[i] == 51) {
			i++;
			b=ram[ram[i]];
			i++;
			goto r;
		}

		if (ram[i] == 52) {
			i++;
			c=ram[ram[i]];
			i++;
			goto r;
		}

		if (ram[i] == 53) {
			i++;
			ram[ram[i]] = a;
			i++;
			goto r;
		}

		if (ram[i] == 54) {
			i++;
			ram[ram[i]] = b;
			i++;
			goto r;
		}

		if (ram[i] == 55) {
			i++;
			ram[ram[i]] = c;
			i++;
			goto r;
		}

		if (ram[i] == 60) {
			a=a+b;
		}
		if (ram[i] == 61) {
			a=a+c;
		}
		if (ram[i] == 62) {
			b=b+a;
		}
		if (ram[i] == 63) {
			b=b+c;
		}
		if (ram[i] == 64) {
			c=c+a;
		}
		if (ram[i] == 65) {
			c=c+b;
		}
		if (ram[i] == 66) {
			i++;
			a=a+ram[i];
			i++;
			goto r;
		}
		if (ram[i] == 67) {
			i++;
			b=b+ram[i];
			i++;
			goto r;
		}
		if (ram[i] == 68) {
			i++;
			c=c+ram[i];
			i++;
			goto r;
		}

		if (ram[i] == 70) {
			a=a-b;
		}
		if (ram[i] == 71) {
			a=a-c;
		}
		if (ram[i] == 72) {
			b=b-a;
		}
		if (ram[i] == 73) {
			b=b-c;
		}
		if (ram[i] == 74) {
			c=c-a;
		}
		if (ram[i] == 75) {
			c=c-b;
		}
		if (ram[i] == 76) {
			i++;
			a=a-ram[i];
			i++;
			goto r;
		}
		if (ram[i] == 77) {
			i++;
			b=b-ram[i];
			i++;
			goto r;
		}
		if (ram[i] == 78) {
			i++;
			c=c-ram[i];
			i++;
			goto r;
		}

		if (ram[i] == 80) {
			a=a*b;
		}
		if (ram[i] == 81) {
			a=a*c;
		}
		if (ram[i] == 82) {
			b=b*a;
		}
		if (ram[i] == 83) {
			b=b*c;
		}
		if (ram[i] == 84) {
			c=c*a;
		}
		if (ram[i] == 85) {
			c=c*b;
		}
		if (ram[i] == 86) {
			i++;
			a=a*ram[i];
			i++;
			goto r;
		}
		if (ram[i] == 87) {
			i++;
			b=b*ram[i];
			i++;
			goto r;
		}
		if (ram[i] == 88) {
			i++;
			c=c*ram[i];
			i++;
			goto r;
		}

		if (ram[i] == 90) {
			a=a/b;
		}
		if (ram[i] == 91) {
			a=a/c;
		}
		if (ram[i] == 92) {
			b=b/a;
		}
		if (ram[i] == 93) {
			b=b/c;
		}
		if (ram[i] == 94) {
			c=c/a;
		}
		if (ram[i] == 95) {
			c=c/b;
		}
		if (ram[i] == 96) {
			i++;
			a=a/ram[i];
			i++;
			goto r;
		}
		if (ram[i] == 97) {
			i++;
			b=b/ram[i];
			i++;
			goto r;
		}
		if (ram[i] == 98) {
			i++;
			c=c/ram[i];
			i++;
			goto r;
		}

		if (ram[i] == 250) {
			f[2] = true;
		}

		if (ram[i] == 251) {
			f[3] = true;
		}

		if (ram[i] == 255) {
			if (!f[2]) {
				std::cout << std::endl << "End" << std::endl;
			}
			if (f[3]) {
				state = 2;
			}
			else {
				state = 1;
			}
		}

		i++;
	}

	d:
	if (state == 1) {
		i = 0;
		a = 0;
		b = 0;
		c = 0;
		f[0] = false;
		f[1] = false;
		f[2] = false;
		f[3] = false;
		std::cout << std::endl << std::endl << "Mini IDE" << std::endl;
		std::cout << "255 to save&exit" << std::endl << std::endl;
		int sas = 0;
		while (i < 255) {
			ram[i] = 0;
			i++;
		}
		ram[255] = 255;
		i = 0;
		while (state == 1) {
			std::cout << "Enter address " << i << " value: ";
			std::cin >> sas;
			ram[i] = sas;
			if (ram[i] == 255) {
				i = 0;
				state = 0;
				std::cout << std::endl;
				goto r;
			}
			i++;
		}
	}
	std::cout << std::endl;
	std::cin.get();
}


// 0 - Null
// 1 - inc a
// 2 - inc b
// 3 - inc c
// 4 - dec a
// 5 - dec b
// 6 - dec c
// 7 - cmp a,[int]
// 8 - cmp b,[int]
// 9 - cmp c,[int]

// 10 - cout
// 11 - couts
// 12 - cnl
// 13 - cin
// 14 - getch
// 15 - cls

// 20 - rst
// 21 - jmp [int]
// 22 - jz [int]
// 23 - jnz [int]
// 24 - jn [int]
// 25 - jp [int]

// 30 - mov a,b
// 31 - mov a,c
// 32 - mov b,a
// 33 - mov b,c
// 34 - mov c,a
// 35 - mov c,b

// 40 - mov a,[int]
// 41 - mov b,[int]
// 42 - mov c,[int]

// 50 - mov a,[addr]
// 51 - mov b,[addr]
// 52 - mov c,[addr]
// 53 - mov [addr],a
// 54 - mov [addr],b
// 55 - mov [addr],c

// 60 - add a,b
// 61 - add a,c
// 62 - add b,a
// 63 - add b,c
// 64 - add c,a
// 65 - add c,b
// 66 - add a,[int]
// 67 - add b,[int]
// 68 - add c,[int]

// 70 - sub a,b
// 71 - sub a,c
// 72 - sub b,a
// 73 - sub b,c
// 74 - sub c,a
// 75 - sub c,b
// 76 - sub a,[int]
// 77 - sub b,[int]
// 78 - sub c,[int]

// 80 - mul a,b
// 81 - mul a,c
// 82 - mul b,a
// 83 - mul b,c
// 84 - mul c,a
// 85 - mul c,b
// 86 - mul a,[int]
// 87 - mul b,[int]
// 88 - mul c,[int]

// 90 - div a,b
// 91 - div a,c
// 92 - div b,a
// 93 - div b,c
// 94 - div c,a
// 95 - div c,b
// 96 - div a,[int]
// 97 - div b,[int]
// 98 - div c,[int]


// 250 - endf
// 251 - idef
// 255 - ret
