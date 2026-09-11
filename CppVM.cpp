#include <iostream>
#include <stdint.h>
#include <conio.h>
#include <fstream>

#define RAMSIZE 65536
#define RELJP(NUM) if (NUM > 127) i = i+NUM-256; else i = i + NUM

int state = 0;
uint8_t ram[RAMSIZE];
uint8_t prnt;
unsigned short int a,b,c,d,e = 0;
unsigned short int ta,tb,tc,na,nb,nc = 0;
unsigned short int sp = 0;
unsigned short int stack[32];
unsigned short int i = 0;
int tmp;

//           Z N S S C R R R
bool f[8] = {0,0,0,0,0,0,0,0};

std::ifstream fin("bios.cvm"); // Чтение файла

// TODO: Graphics support?
// TODO: Auto-flags (sub, add, mull, div...)
// TODO: '%' function
// TODO: Multifile
// TODO: Enchance assembler output

int main() {

	std::cout << "CppVM v1.2.1" << std::endl;//v171224

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
			std::cout << a;
		}
		if (ram[i] == 11) {
			if (a > 32767) {
				std::cout << a-65536;
			} else {
				std::cout << a;
			}
		}
		if (ram[i] == 12) {
			//std::cout << a << std::endl;
			if (a < 256) {
				char ch;
				//std::cout << a;
				ch = (char)a;
				std::cout << ch;
			}
			
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
		if (ram[i] == 18) {
			ta = a;
			tb = b;
			tc = c;
			a = na;
			b = nb;
			c = nc;
			na = ta;
			nb = tb;
			nc = tc;
			i++;
			goto r;
		}
		if (ram[i] == 19) {
			stack[sp] = (i+3);
			sp++;
			i++;
			i = ram[i]*256+ram[i+1];
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
			i = c;
			goto r;
		}
		if (ram[i] == 26) {
			if (f[0]) {
				i++;
				i = c;
				goto r;
			}
			i=i+2;
			goto r;
		}
		if (ram[i] == 27) {
			if (!f[0]) {
				i++;
				i = c;
				goto r;
			}
			i=i+2;
			goto r;
		}
		if (ram[i] == 28) {
			if (f[1]) {
				i++;
				i = c;
				goto r;
			}
			i=i+2;
			goto r;
		}
		if (ram[i] == 29) {
			if (!f[1]) {
				i++;
				i = c;
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
		if (ram[i] == 43) {
			i++;
			a=ram[i]*256+ram[i+1];
			i=i+2;
			goto r;
		}
		if (ram[i] == 44) {
			i++;
			b=ram[i]*256+ram[i+1];
			i=i+2;
			goto r;
		}
		if (ram[i] == 45) {
			i++;
			c=ram[i]*256+ram[i+1];
			i=i+2;
			goto r;
		}
		if (ram[i] == 50) {
			i++;
			a=ram[ram[i]*256+ram[i+1]];
			i=i+2;
			goto r;
		}
		if (ram[i] == 51) {
			i++;
			b=ram[ram[i]*256+ram[i+1]];
			i=i+2;
			goto r;
		}
		if (ram[i] == 52) {
			i++;
			c=ram[ram[i]*256+ram[i+1]];
			i=i+2;
			goto r;
		}
		if (ram[i] == 53) {
			i++;
			ram[ram[i]*256+ram[i+1]] = a;
			i=i+2;
			goto r;
		}
		if (ram[i] == 54) {
			i++;
			ram[ram[i]*256+ram[i+1]] = b;
			i=i+2;
			goto r;
		}
		if (ram[i] == 55) {
			i++;
			ram[ram[i]*256+ram[i+1]] = c;
			i=i+2;
			goto r;
		}
		if (ram[i] == 60) {
			i++;
			a = ram[a];
			goto r;
		}
		if (ram[i] == 61) {
			i++;
			a = ram[b];
			goto r;
		}
		if (ram[i] == 62) {
			i++;
			a = ram[c];
			goto r;
		}
		if (ram[i] == 63) {
			i++;
			b = ram[a];
			goto r;
		}
		if (ram[i] == 64) {
			i++;
			b = ram[b];
			goto r;
		}
		if (ram[i] == 65) {
			i++;
			b = ram[c];
			goto r;
		}
		if (ram[i] == 66) {
			i++;
			c = ram[a];
			goto r;
		}
		if (ram[i] == 67) {
			i++;
			c = ram[b];
			goto r;
		}
		if (ram[i] == 68) {
			i++;
			c = ram[c];
			goto r;
		}
		
		if (ram[i] == 70) {
			i++;
			ram[a] = a;
			goto r;
		}
		if (ram[i] == 71) {
			i++;
			ram[b] = a;
			goto r;
		}
		if (ram[i] == 72) {
			i++;
			ram[c] = a;
			goto r;
		}
		if (ram[i] == 73) {
			i++;
			ram[a] = b;
			goto r;
		}
		if (ram[i] == 74) {
			i++;
			ram[b] = b;
			goto r;
		}
		if (ram[i] == 75) {
			i++;
			ram[c] = b;
			goto r;
		}
		if (ram[i] == 76) {
			i++;
			ram[a] = c;
			goto r;
		}
		if (ram[i] == 77) {
			i++;
			ram[b] = c;
			goto r;
		}
		if (ram[i] == 78) {
			i++;
			ram[c] = c;
			goto r;
		}
		if (ram[i] == 110) {
			a=a+b;
		}
		if (ram[i] == 111) {
			a=a+c;
		}
		if (ram[i] == 112) {
			b=b+a;
		}
		if (ram[i] == 113) {
			b=b+c;
		}
		if (ram[i] == 114) {
			c=c+a;
		}
		if (ram[i] == 115) {
			c=c+b;
		}
		if (ram[i] == 116) {
			i++;
			a=a+ram[i];
			i++;
			goto r;
		}
		if (ram[i] == 117) {
			i++;
			b=b+ram[i];
			i++;
			goto r;
		}
		if (ram[i] == 118) {
			i++;
			c=c+ram[i];
			i++;
			goto r;
		}
		if (ram[i] == 120) {
			a=a-b;
		}
		if (ram[i] == 121) {
			a=a-c;
		}
		if (ram[i] == 122) {
			b=b-a;
		}
		if (ram[i] == 123) {
			b=b-c;
		}
		if (ram[i] == 124) {
			c=c-a;
		}
		if (ram[i] == 125) {
			c=c-b;
		}
		if (ram[i] == 126) {
			i++;
			a=a-ram[i];
			i++;
			goto r;
		}
		if (ram[i] == 127) {
			i++;
			b=b-ram[i];
			i++;
			goto r;
		}
		if (ram[i] == 128) {
			i++;
			c=c-ram[i];
			i++;
			goto r;
		}
		if (ram[i] == 130) {
			a=a*b;
		}
		if (ram[i] == 131) {
			a=a*c;
		}
		if (ram[i] == 132) {
			b=b*a;
		}
		if (ram[i] == 133) {
			b=b*c;
		}
		if (ram[i] == 134) {
			c=c*a;
		}
		if (ram[i] == 135) {
			c=c*b;
		}
		if (ram[i] == 136) {
			i++;
			a=a*ram[i];
			i++;
			goto r;
		}
		if (ram[i] == 137) {
			i++;
			b=b*ram[i];
			i++;
			goto r;
		}
		if (ram[i] == 138) {
			i++;
			c=c*ram[i];
			i++;
			goto r;
		}
		if (ram[i] == 140) {
			a=a/b;
		}
		if (ram[i] == 141) {
			a=a/c;
		}
		if (ram[i] == 142) {
			b=b/a;
		}
		if (ram[i] == 143) {
			b=b/c;
		}
		if (ram[i] == 144) {
			c=c/a;
		}
		if (ram[i] == 145) {
			c=c/b;
		}
		if (ram[i] == 146) {
			i++;
			a=a/ram[i];
			i++;
			goto r;
		}
		if (ram[i] == 147) {
			i++;
			b=b/ram[i];
			i++;
			goto r;
		}
		if (ram[i] == 148) {
			i++;
			c=c/ram[i];
			i++;
			goto r;
		}
		if (ram[i] == 190) {
			//i++;
			RELJP(ram[i+1]);
			goto r;
		}
		if (ram[i] == 191) {
			if (f[0]) {
				//i++;
				RELJP(ram[i+1]);
				goto r;
			}
			i=i+1;
			goto r;
		}
		if (ram[i] == 192) {
			if (!f[0]) {
				i++;
				RELJP(ram[i]);
				goto r;
			}
			i=i+2;
			goto r;
		}
		if (ram[i] == 193) {
			if (f[1]) {
				i++;
				RELJP(ram[i]);
				goto r;
			}
			i=i+2;
			goto r;
		}
		if (ram[i] == 194) {
			if (!f[1]) {
				i++;
				RELJP(ram[i]);
				goto r;
			}
			i=i+2;
			goto r;
		}
		/*if (ram[i] == 195) {
			//i++;
			RELJP(c);
			goto r;
		}
		if (ram[i] == 196) {
			if (f[0]) {
				//i++;
				RELJP(c);
				goto r;
			}
			i++;
			goto r;
		}
		if (ram[i] == 197) {
			if (!f[0]) {
				//i++;
				RELJP(c);
				goto r;
			}
			i++;
			goto r;
		}
		if (ram[i] == 198) {
			if (f[1]) {
				//i++;
				RELJP(c);
				goto r;
			}
			i++;
			goto r;
		}
		if (ram[i] == 199) {
			if (!f[1]) {
				//i++;
				RELJP(c);
				goto r;
			}
			i++;
			goto r;
		}*/
		if (ram[i] == 250) {
			f[2] = true;
		}
		if (ram[i] == 251) {
			f[3] = true;
		}
		if (ram[i] == 255) {
			if (sp == 0) {
				if (!f[2]) {
					std::cout << std::endl << "End" << std::endl;
				}
				if (f[3]) {
					state = 2;
				} else {
					state = 1;
				}
			}
			else {
				sp--;
				i = stack[sp];
				stack[sp] = 0;
				goto r;
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
