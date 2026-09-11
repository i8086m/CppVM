#include <iostream>
#include <stdint.h>
#include <conio.h>
#include <fstream>

#define RAMSIZE 65536
#define RELJP(NUM) if (NUM > 127) i = i+NUM-256; else i = i + NUM

int state = 0;
uint8_t a,b,c = 0;
uint8_t ram[RAMSIZE];
unsigned short int i = 0;
int tmp;

//           Z N S S C R R R
bool f[8] = {0,0,0,0,0,0,0,0};

std::ifstream fin("bios.cvm"); // Чтение файла

// TODO: Graphics support?
// TODO: File Access (Self-Programming?)
// TODO: Relative jumps
// TODO: 'MOV' fix
// TODO: Auto-flags (sub, add, mull, div...)
// TODO: '%' function
// TODO: Multifile

int main() {

	std::cout << "CppVM v1.1" << std::endl;//v171222
	
	std::cout << "RAM: " << RAMSIZE/1024 << "KB" << std::endl << std::endl;

	while (i < RAMSIZE-1) { // erase RAM
		ram[i] = 0;
		i++;
	}
	ram[RAMSIZE-1] = 255; // чтоб не циклилось
	i = 0; // pc в ноль

	int buff;
	int bc = 0;

	if (!fin.is_open()) {
		state = 1;
	} else {
		while (bc < RAMSIZE) {
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
			// Do nothing
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
			} else {
				f[0] = false;
			}
			if (a-ram[i] < 0) {
				f[1] = true;
			} else {
				f[1] = false;
			}
			i++;
			goto r;
		}
		if (ram[i] == 8) {
			i++;
			if (a-b == 0) {
				f[0] = true;
			} else {
				f[0] = false;
			}
			if (a-b < 0) {
				f[1] = true;
			} else {
				f[1] = false;
			}
			i++;
			goto r;
		}
		if (ram[i] == 9) {
			i++;
			if (a-c == 0) {
				f[0] = true;
			} else {
				f[0] = false;
			}
			if (a-c < 0) {
				f[1] = true;
			} else {
				f[1] = false;
			}
			i++;
			goto r;
		}

		if (ram[i] == 10) {
			std::cout << +a;
		}
		if (ram[i] == 11) {
			if (a > 127) {
				std::cout << a-256;
			}
			else {
				std::cout << +a;
			}
		}
		if (ram[i] == 12) {
			std::cout << a;
		}
		if (ram[i] == 13) {
			std::cout << "\n";
		}
		if (ram[i] == 14) {
			std::cin >> tmp;
			a = tmp;
		}
		if (ram[i] == 15) {
			a = getch();
		}
		if (ram[i] == 16) {
			system("cls");
		}
		if (ram[i] == 17) {
			i = 0;
			goto r;
		}
		if (ram[i] == 20) {
			i++;
			i = ram[i]*256+ram[i+1];
			goto r;
		}
		if (ram[i] == 21) {
			if (f[0]) {
				i++;
				i = ram[i]*256+ram[i+1];
				goto r;
			}
			i=i+3;
			goto r;
		}
		if (ram[i] == 22) {
			if (!f[0]) {
				i++;
				i = ram[i]*256+ram[i+1];
				goto r;
			}
			i=i+3;
			goto r;
		}
		if (ram[i] == 23) {
			if (f[1]) {
				i++;
				i = ram[i]*256+ram[i+1];
				goto r;
			}
			i=i+3;
			goto r;
		}
		if (ram[i] == 24) {
			if (!f[1]) {
				i++;
				i = ram[i]*256+ram[i+1];
				goto r;
			}
			i=i+3;
			goto r;
		}
		if (ram[i] == 25) {
			i++;
			i = b*256+c;
			goto r;
		}
		if (ram[i] == 26) {
			if (f[0]) {
				i++;
				i = b*256+c;
				goto r;
			}
			i++;
			goto r;
		}
		if (ram[i] == 27) {
			if (!f[0]) {
				i++;
				i = b*256+c;
				goto r;
			}
			i++;
			goto r;
		}
		if (ram[i] == 28) {
			if (f[1]) {
				i++;
				i = b*256+c;
				goto r;
			}
			i++;
			goto r;
		}
		if (ram[i] == 29) {
			if (!f[1]) {
				i++;
				i = b*256+c;
				goto r;
			}
			i++;
			goto r;
		}
		if (ram[i] == 40) {
			a = b;
		}
		if (ram[i] == 41) {
			a = c;
		}
		if (ram[i] == 42) {
			b = a;
		}
		if (ram[i] == 43) {
			b = c;
		}
		if (ram[i] == 44) {
			c = a;
		}
		if (ram[i] == 45) {
			c = b;
		}
		if (ram[i] == 46) {
			i++;
			a=ram[i];
			i++;
			goto r;
		}
		if (ram[i] == 47) {
			i++;
			b=ram[i];
			i++;
			goto r;
		}
		if (ram[i] == 48) {
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
			} else {
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
		std::cin.get();
	}
}
