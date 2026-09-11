#define _WIN32_WINNT 0x500 // windows.h
#include "windows.h" // system()
#include <iostream> // ввод-вывод
#include <conio.h> // getch
#include <fstream> // bootloader
#include <string> // stack
#include <sstream> // string stream

#define RAMSIZE 65536
#define RELJP(NUM) if (NUM > 2147483647) i = i + NUM - 4294967296; else i = i + NUM
#define STACKSIZE 64
#define USTACKSIZE 128
#define VERSION "CppVM v2.2"

int state = 0;
unsigned int ram[RAMSIZE];
unsigned int a,b,c = 0; /// LEGACY
unsigned int d,e = 0; /// EXTRA
unsigned int ta,tb,tc,na,nb,nc = 0;
unsigned int sp, usp = 0; /// stack pointers
char ustack[USTACKSIZE];
unsigned int stack[STACKSIZE];
unsigned int i = 0;

int tmp;
//               Z N C ?
bool flags[4] = {0,0,0,0};
bool f_dbg = false;
bool f_msg = false;

std::ifstream fin("bios.cvm"); // Чтение файла

RECT rect;
HWND window = GetConsoleWindow();
HDC hdc = GetDC(window);

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void gfxmode(bool gfxState) {
    gfxState = !gfxState;
    if (!gfxState) {
        ShowScrollBar(window, SB_BOTH, gfxState);
    }
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = gfxState;
    SetConsoleCursorInfo(consoleHandle, &info);
}
void gfxclear(int colorShift) {
    GetClientRect(window, &rect);
    FillRect(hdc, &rect, (HBRUSH)(COLOR_WINDOW+colorShift));
}

int main() {
    SelectObject(hdc, GetStockObject(DC_PEN));
    SetDCPenColor(hdc, RGB(255,0,0));
    SetConsoleTitle(VERSION);

    while (i < RAMSIZE-1) { /// erase RAM
        ram[i] = 0;
        i++;
    }
    ram[RAMSIZE-1] = 255;
    i = 0;
    int buff, bc = 0;
    if (!fin.is_open()) { /// bootloader
        std::cout << "bios.cvm not found" << std::endl;
        system("pause");
        return 0;
    } else {
        while (bc < RAMSIZE+1 && !fin.eof()) {
            fin >> buff;
            ram[bc] = buff;
            fin >> buff;
            ram[bc] = ram[bc]*256+buff;
            fin >> buff;
            ram[bc] = ram[bc]*256+buff;
            fin >> buff;
            ram[bc] = ram[bc]*256+buff;
            //std::cout << bc << " " << ram[bc] <<std::endl;
            bc++;
        }
        fin.close();
    }


    while (state == 0) {
        if (f_dbg) {
            bc = 0;
            tmp = 0;
            while (bc<RAMSIZE) {
                if (ram[bc] != 0) {
                    tmp++;
                }
                bc++;
            }
            std::stringstream mon0;
            std::string mon;
            tmp--;
            mon0 << "RAM " << "Usage: " << tmp << "/" << RAMSIZE << "b (" << tmp*100/RAMSIZE << "%)";
            mon0 << "  |  A=" << a << ", B=" << b << ", C=" << c;
            mon0 << "  |  PC=" << i << "  |  ram[PC]=" << +ram[i];
            mon = mon0.str();			// Type 1
            //std::getline(mon0, mon);	// Type 2
            char cmon[64];
            tmp = 0;
            strcpy(cmon, mon.c_str());
            SetConsoleTitle(cmon);
            getch();
        }
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
            int tmpa = 0;
            int tmpb = 0;
            if (a > 2147483648U) {
                tmpa = a-4294967296;
            } else {
                tmpa = a;
            }
            tmpb = ram[i];
            if (tmpa-tmpb == 0) {
                flags[0] = true;
            } else {
                flags[0] = false;
            }
            if (tmpa-tmpb < 0) {
                flags[1] = true;
            } else {
                flags[1] = false;
            }
            i++;
            continue;
        }
        if (ram[i] == 8) {
            if (a-b == 0) {
                flags[0] = true;
            } else {
                flags[0] = false;
            }
            if (a-b < 0) {
                flags[1] = true;
            } else {
                flags[1] = false;
            }
            i++;
            continue;
        }
        if (ram[i] == 9) {
            if (a-c == 0) {
                flags[0] = true;
            } else {
                flags[0] = false;
            }
            if (a-c < 0) {
                flags[1] = true;
            } else {
                flags[1] = false;
            }
            i++;
            continue;
        }

        if (ram[i] == 10) {
            std::cout << a;
        }

        if (ram[i] == 11) {
            if (a > 2147483648U) {
                std::cout << a-4294967296;
            } else {
                std::cout << a;
            }
        }
        if (ram[i] == 12) {///unicode?
            if (a < 256) {
                char ch;
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
            //nodelay(stdscr,TRUE);
            a = getch();
        }
        if (ram[i] == 16) {
            system("cls");
        }
        if (ram[i] == 17) {
            if (sp < STACKSIZE) {
                stack[sp] = i+1;
                sp++;
                i = c;
                continue;
            } else {
                std::cout << std::endl << "Error: Stack Overflow" << std::endl;
                state = 2;
            }
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
            continue;
        }
        if (ram[i] == 19) {
            if (sp < STACKSIZE) {
                stack[sp] = i+2;
                sp++;
                i++;
                i = ram[i];
                continue;
            } else {
                std::cout << std::endl << "Error: Stack Overflow" << std::endl;
                state = 2;
            }
        }
        if (ram[i] == 20) {
            i++;
            i = ram[i];
            continue;
        }
        if (ram[i] == 21) {
            if (flags[0]) {
                i++;
                i = ram[i];
                continue;
            }
            i=i+2;
            continue;
        }
        if (ram[i] == 22) {
            if (!flags[0]) {
                i++;
                i = ram[i];
                continue;
            }
            i=i+2;
            continue;
        }
        if (ram[i] == 23) {
            if (flags[1]) {
                i++;
                i = ram[i];
                continue;
            }
            i=i+2;
            continue;
        }
        if (ram[i] == 24) {
            if (!flags[1]) {
                i++;
                i = ram[i];
                continue;
            }
            i=i+2;
            continue;
        }
        if (ram[i] == 25) {
            i++;
            i = c;
            continue;
        }
        if (ram[i] == 26) {
            if (flags[0]) {
                i++;
                i = c;
                continue;
            }
            i=i+2;
            continue;
        }
        if (ram[i] == 27) {
            if (!flags[0]) {
                i++;
                i = c;
                continue;
            }
            i=i+2;
            continue;
        }
        if (ram[i] == 28) {
            if (flags[1]) {
                i++;
                i = c;
                continue;
            }
            i=i+2;
            continue;
        }
        if (ram[i] == 29) {
            if (!flags[1]) {
                i++;
                i = c;
                continue;
            }
            i=i+2;
            continue;
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
        /// 40-42 free
        if (ram[i] == 43) {
            i++;
            a=ram[i];
            i++;
            continue;
        }
        if (ram[i] == 44) {
            i++;
            b=ram[i];
            i++;
            continue;
        }
        if (ram[i] == 45) {
            i++;
            c=ram[i];
            i++;
            continue;
        }
        if (ram[i] == 50) {
            i++;
            a=ram[ram[i]];
            i++;
            continue;
        }
        if (ram[i] == 51) {
            i++;
            b=ram[ram[i]];
            i++;
            continue;
        }
        if (ram[i] == 52) {
            i++;
            c=ram[ram[i]];
            i++;
            continue;
        }
        if (ram[i] == 53) {
            i++;
            ram[ram[i]] = a;
            i++;
            continue;
        }
        if (ram[i] == 54) {
            i++;
            ram[ram[i]] = b;
            i++;
            continue;
        }
        if (ram[i] == 55) {
            i++;
            ram[ram[i]] = c;
            i++;
            continue;
        }
        if (ram[i] == 60) {
            i++;
            a = ram[a];
            continue;
        }
        if (ram[i] == 61) {
            i++;
            a = ram[b];
            continue;
        }
        if (ram[i] == 62) {
            i++;
            a = ram[c];
            continue;
        }
        if (ram[i] == 63) {
            i++;
            b = ram[a];
            continue;
        }
        if (ram[i] == 64) {
            i++;
            b = ram[b];
            continue;
        }
        if (ram[i] == 65) {
            i++;
            b = ram[c];
            continue;
        }
        if (ram[i] == 66) {
            i++;
            c = ram[a];
            continue;
        }
        if (ram[i] == 67) {
            i++;
            c = ram[b];
            continue;
        }
        if (ram[i] == 68) {
            i++;
            c = ram[c];
            continue;
        }

        if (ram[i] == 70) {
            i++;
            ram[a] = a;
            continue;
        }
        if (ram[i] == 71) {
            i++;
            ram[b] = a;
            continue;
        }
        if (ram[i] == 72) {
            i++;
            ram[c] = a;
            continue;
        }
        if (ram[i] == 73) {
            i++;
            ram[a] = b;
            continue;
        }
        if (ram[i] == 74) {
            i++;
            ram[b] = b;
            continue;
        }
        if (ram[i] == 75) {
            i++;
            ram[c] = b;
            continue;
        }
        if (ram[i] == 76) {
            i++;
            ram[a] = c;
            continue;
        }
        if (ram[i] == 77) {
            i++;
            ram[b] = c;
            continue;
        }
        if (ram[i] == 78) {
            i++;
            ram[c] = c;
            continue;
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
            continue;
        }
        if (ram[i] == 117) {
            i++;
            b=b+ram[i];
            i++;
            continue;
        }
        if (ram[i] == 118) {
            i++;
            c=c+ram[i];
            i++;
            continue;
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
            continue;
        }
        if (ram[i] == 127) {
            i++;
            b=b-ram[i];
            i++;
            continue;
        }
        if (ram[i] == 128) {
            i++;
            c=c-ram[i];
            i++;
            continue;
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
            continue;
        }
        if (ram[i] == 137) {
            i++;
            b=b*ram[i];
            i++;
            continue;
        }
        if (ram[i] == 138) {
            i++;
            c=c*ram[i];
            i++;
            continue;
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
            continue;
        }
        if (ram[i] == 147) {
            i++;
            b=b/ram[i];
            i++;
            continue;
        }
        if (ram[i] == 148) {
            i++;
            c=c/ram[i];
            i++;
            continue;
        }
        if (ram[i] == 150) {
            i++;
            a = (a & ram[i]*256+ram[i+1]);
            i=i+2;
            continue;
        }
        if (ram[i] == 151) {
            i++;
            a = (a | ram[i]*256+ram[i+1]);
            i=i+2;
            continue;
        }
        if (ram[i] == 152) {
            i++;
            a = (a ^ ram[i]*256+ram[i+1]);
            i=i+2;
            continue;
        }
        if (ram[i] == 153) {
            i++;
            a = (~ a);
            continue;
        }
        if (ram[i] == 154) {
            i++;
            a = (a & b);
            continue;
        }
        if (ram[i] == 155) {
            i++;
            a = (a | b);
            continue;
        }
        if (ram[i] == 156) {
            i++;
            a = (a ^ b);
            continue;
        }

        if (ram[i] == 160) {
            i++;
            if (usp>0) {
                usp--;
                a = ustack[usp];
            }
        }
        if (ram[i] == 161) {
            ustack[usp] = a;
            if (usp < USTACKSIZE) {
                usp++;
            }
        }

        if (ram[i] == 162) {
            for (int x = 0; x < USTACKSIZE; x++) {
                ustack[x] = 0;
            }
            usp = 0;
        }

        if (ram[i] == 190) {
            //i++;
            RELJP(ram[i+1]);
            continue;
        }
        if (ram[i] == 191) {
            if (flags[0]) {
                //i++;
                RELJP(ram[i+1]);
                continue;
            }
            i=i+1;
            continue;
        }
        if (ram[i] == 192) {
            if (!flags[0]) {
                i++;
                RELJP(ram[i]);
                continue;
            }
            i=i+2;
            continue;
        }
        if (ram[i] == 193) {
            if (flags[1]) {
                i++;
                RELJP(ram[i]);
                continue;
            }
            i=i+2;
            continue;
        }
        if (ram[i] == 194) {
            if (!flags[1]) {
                i++;
                RELJP(ram[i]);
                continue;
            }
            i=i+2;
            continue;
        }

        if (ram[i] == 250) {
            bc = 0;
            tmp = 0;
            while (bc<RAMSIZE) {
                if (ram[bc] != 0) {
                    tmp++;
                }
                bc++;
            }
            std::stringstream mon0;
            std::string mon;
            tmp--;
            std::cout << VERSION << std::endl;
            std::cout << "RAM Used: " << tmp << "/" << RAMSIZE << "b (" << tmp*100/RAMSIZE << "%)" << std::endl << std::endl;
            f_msg = true;
        }

        if (ram[i] == 251) {
            f_dbg = true;
        }

        if (ram[i] == 252) {
            f_dbg = false;
        }

        if (ram[i] == 255) {
            if (sp == 0) {
                if (f_msg) {
                    std::cout << std::endl << "End";
                    getch();
                }
                state = 2; // Exit
            } else {
                sp--;
                i = stack[sp];
                stack[sp] = 0;
                continue;
            }
        }

        if (ram[i] == 300) {
            system(ustack);
        }

        if (ram[i] == 301) {
            gotoxy(a,b);
        }
        if (ram[i] == 302) {
            gfxclear(a);
        }
        if (ram[i] == 303) {
            gfxmode(true);
        }
        if (ram[i] == 304) {
            SetDCPenColor(hdc, RGB(a, b, c));
        }
        if (ram[i] == 305) {
            SetPixel(hdc, a, b, RGB(255,0,0));
        }
        if (ram[i] == 306) {
            MoveToEx(hdc, a, b, NULL);
        }
        if (ram[i] == 307) {
            LineTo(hdc, a, b);
        }
        if (ram[i] == 308) {
            ReleaseDC(window, hdc);
        }
        i++;
    }
    return 0;
}
