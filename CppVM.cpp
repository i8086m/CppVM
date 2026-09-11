//#define _WIN32_WINNT 0x500 // windows.h
#include "windows.h" // system()
#include <iostream> // ввод-вывод
#include <conio.h> // getch
#include <fstream> // bootloader
#include <string> // stack
#include <sstream> // string stream

#define RAMSIZE 1048576
#define RELJP(NUM) if (NUM > 2147483647) i = i + NUM - 4294967296; else i = i + NUM
#define STACKSIZE 64
#define USTACKSIZE 128
#define VERSION "CppVM v2.3"

int state = 0;
unsigned int ram[RAMSIZE];
unsigned int a,b,c = 0; /// LEGACY
unsigned int d,e = 0; /// EXTRA
unsigned int ta,tb,tc,na,nb,nc = 0;
unsigned int sp, usp = 0; /// stack pointers
unsigned int ustack[USTACKSIZE];
unsigned int stack[STACKSIZE];
unsigned int i = 0;

int tmp;
//               Z N P C
bool flags[4] = {0,0,0,0};
bool f_dbg = false;
bool f_msg = false;

std::ifstream fin("bios.cvm"); // Чтение файла

//RECT rect;
//HWND window = GetConsoleWindow();
//HDC hdc = GetDC(window);

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
/*void gfxmode(bool gfxState) {
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
}*/

int main() {
    //SelectObject(hdc, GetStockObject(DC_PEN));
    //SetDCPenColor(hdc, RGB(255,0,0));
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
            mon0 << "RAM " << "Usage: " << tmp * 4 << "/" << RAMSIZE / 256 << "kb (" << tmp*100/RAMSIZE << "%)";
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
        else if (ram[i] == 1) {
            a++;
        }
        else if (ram[i] == 2) {
            b++;
        }
        else if (ram[i] == 3) {
            c++;
        }
        else if (ram[i] == 4) {
            a--;
        }
        else if (ram[i] == 5) {
            b--;
        }
        if (ram[i] == 6) {
            c--;
        }
        else if (ram[i] == 7) {
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
            if (tmpa-tmpb > 0) {
                flags[2] = true;
            } else {
                flags[2] = false;
            }
        }
        else if (ram[i] == 8) {
            if (a-b == 0) {
                flags[0] = true;
            } else {
                flags[0] = false;
            }
            if ((signed)(a-b) < 0) {
                flags[1] = true;
            } else {
                flags[1] = false;
            }
            if ((signed)(a-b) > 0) {
                flags[2] = true;
            } else {
                flags[2] = false;
            }
        }
        else if (ram[i] == 9) {
            if (a-c == 0) {
                flags[0] = true;
            } else {
                flags[0] = false;
            }
            if ((signed)(a-c) < 0) {
                flags[1] = true;
            } else {
                flags[1] = false;
            }
            if ((signed)(a-c) > 0) {
                flags[2] = true;
            } else {
                flags[2] = false;
            }
        }

        else if (ram[i] == 10) {
            std::cout << a;
        }

        else if (ram[i] == 11) {
            if (a > 2147483648U) {
                std::cout << a-4294967296;
            } else {
                std::cout << a;
            }
        }
        else if (ram[i] == 12) {///unicode?
            if (a < 256) {
                char ch;
                ch = (char)a;
                //std::cout << ch;
                putchar(ch);
            }

        }
        else if (ram[i] == 13) {
            putchar('\n');
        }
        else if (ram[i] == 14) {
            std::cin >> tmp;
            a = tmp;
        }
        else if (ram[i] == 15) {
            //nodelay(stdscr,TRUE);
            a = getch();
        }
        else if (ram[i] == 16) {
            system("cls");
        }
        else if (ram[i] == 17) {
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
        else if (ram[i] == 18) {
            ta = a;
            tb = b;
            tc = c;
            a = na;
            b = nb;
            c = nc;
            na = ta;
            nb = tb;
            nc = tc;
        }
        else if (ram[i] == 19) {
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
        else if (ram[i] == 20) {
            i++;
            i = ram[i];
            continue;
        }
        else if (ram[i] == 21) {
            if (flags[0]) {
                i++;
                i = ram[i];
                continue;
            } else {
                i++;
            }
        }
        else if (ram[i] == 22) {
            if (!flags[0]) {
                i++;
                i = ram[i];
                continue;
            } else {
                i++;
            }
        }
        else if (ram[i] == 23) {
            if (flags[1]) {
                i++;
                i = ram[i];
                continue;
            } else {
                i++;
            }
        }
        else if (ram[i] == 24) {
            if (flags[2]) {
                i++;
                i = ram[i];
                continue;
            } else {
                i++;
            }
        }
        else if (ram[i] == 25) {
            i = c;
            continue;
        }
        else if (ram[i] == 26) {
            if (flags[0]) {
                i = c;
                continue;
            }
        }
        else if (ram[i] == 27) {
            if (!flags[0]) {
                i = c;
                continue;
            }
        }
        else if (ram[i] == 28) {
            if (flags[1]) {
                i = c;
                continue;
            }
        }
        else if (ram[i] == 29) {
            if (flags[2]) {
                i = c;
                continue;
            }
        }
        else if (ram[i] == 30) {
            a = b;
        }
        else if (ram[i] == 31) {
            a = c;
        }
        else if (ram[i] == 32) {
            b = a;
        }
        else if (ram[i] == 33) {
            b = c;
        }
        else if (ram[i] == 34) {
            c = a;
        }
        else if (ram[i] == 35) {
            c = b;
        }
        /// 40-42 free
        else if (ram[i] == 43) {
            i++;
            a=ram[i];
        }
        else if (ram[i] == 44) {
            i++;
            b=ram[i];
        }
        else if (ram[i] == 45) {
            i++;
            c=ram[i];
        }
        else if (ram[i] == 50) {
            i++;
            a=ram[ram[i]];
        }
        else if (ram[i] == 51) {
            i++;
            b=ram[ram[i]];
        }
        else if (ram[i] == 52) {
            i++;
            c=ram[ram[i]];
        }
        else if (ram[i] == 53) {
            i++;
            ram[ram[i]] = a;
        }
        else if (ram[i] == 54) {
            i++;
            ram[ram[i]] = b;
        }
        else if (ram[i] == 55) {
            i++;
            ram[ram[i]] = c;
        }
        else if (ram[i] == 60) {
            a = ram[a];
        }
        else if (ram[i] == 61) {
            a = ram[b];
        }
        else if (ram[i] == 62) {
            a = ram[c];
        }
        else if (ram[i] == 63) {
            b = ram[a];
        }
        else if (ram[i] == 64) {
            b = ram[b];
        }
        else if (ram[i] == 65) {
            b = ram[c];
        }
        else if (ram[i] == 66) {
            c = ram[a];
        }
        else if (ram[i] == 67) {
            c = ram[b];
        }
        else if (ram[i] == 68) {
            c = ram[c];
        }
        else if (ram[i] == 70) {
            ram[a] = a;
        }
        else if (ram[i] == 71) {
            ram[b] = a;
        }
        else if (ram[i] == 72) {
            ram[c] = a;
        }
        else if (ram[i] == 73) {
            ram[a] = b;
        }
        else if (ram[i] == 74) {
            ram[b] = b;
        }
        else if (ram[i] == 75) {
            ram[c] = b;
        }
        else if (ram[i] == 76) {
            ram[a] = c;
        }
        else if (ram[i] == 77) {
            ram[b] = c;
        }
        else if (ram[i] == 78) {
            ram[c] = c;
        }
        else if (ram[i] == 110) {
            a=a+b;
        }
        else if (ram[i] == 111) {
            a=a+c;
        }
        else if (ram[i] == 112) {
            b=b+a;
        }
        else if (ram[i] == 113) {
            b=b+c;
        }
        else if (ram[i] == 114) {
            c=c+a;
        }
        else if (ram[i] == 115) {
            c=c+b;
        }
        else if (ram[i] == 116) {
            i++;
            a=a+ram[i];
        }
        else if (ram[i] == 117) {
            i++;
            b=b+ram[i];
        }
        else if (ram[i] == 118) {
            i++;
            c=c+ram[i];
        }
        else if (ram[i] == 120) {
            a=a-b;
        }
        else if (ram[i] == 121) {
            a=a-c;
        }
        else if (ram[i] == 122) {
            b=b-a;
        }
        else if (ram[i] == 123) {
            b=b-c;
        }
        else if (ram[i] == 124) {
            c=c-a;
        }
        else if (ram[i] == 125) {
            c=c-b;
        }
        else if (ram[i] == 126) {
            i++;
            a=a-ram[i];
        }
        else if (ram[i] == 127) {
            i++;
            b=b-ram[i];
        }
        else if (ram[i] == 128) {
            i++;
            c=c-ram[i];
        }
        else if (ram[i] == 130) {
            a=a*b;
        }
        else if (ram[i] == 131) {
            a=a*c;
        }
        else if (ram[i] == 132) {
            b=b*a;
        }
        else if (ram[i] == 133) {
            b=b*c;
        }
        else if (ram[i] == 134) {
            c=c*a;
        }
        else if (ram[i] == 135) {
            c=c*b;
        }
        else if (ram[i] == 136) {
            i++;
            a=a*ram[i];
        }
        else if (ram[i] == 137) {
            i++;
            b=b*ram[i];
        }
        else if (ram[i] == 138) {
            i++;
            c=c*ram[i];
        }
        else if (ram[i] == 140) {
            a=a/b;
        }
        else if (ram[i] == 141) {
            a=a/c;
        }
        else if (ram[i] == 142) {
            b=b/a;
        }
        else if (ram[i] == 143) {
            b=b/c;
        }
        else if (ram[i] == 144) {
            c=c/a;
        }
        else if (ram[i] == 145) {
            c=c/b;
        }
        else if (ram[i] == 146) {
            i++;
            a=a/ram[i];
        }
        else if (ram[i] == 147) {
            i++;
            b=b/ram[i];
        }
        else if (ram[i] == 148) {
            i++;
            c=c/ram[i];
        }
        else if (ram[i] == 150) {
            i++;
            a = (a & ram[i]);
        }
        else if (ram[i] == 151) {
            i++;
            a = (a | ram[i]);
        }
        else if (ram[i] == 152) {
            i++;
            a = (a ^ ram[i]);
        }
        else if (ram[i] == 153) {
            a = (~ a);
        }
        else if (ram[i] == 154) {
            a = (a & b);
        }
        else if (ram[i] == 155) {
            a = (a | b);
        }
        else if (ram[i] == 156) {
            a = (a ^ b);
        }

        else if (ram[i] == 160) {
            for (int x = 0; x < USTACKSIZE; x++) {
                ustack[x] = 0;
            }
            usp = 0;
        }

        else if (ram[i] == 161) {
            ustack[usp] = a;
            if (usp < USTACKSIZE) {
                usp++;
            }
        }

        else if (ram[i] == 162) {
            ustack[usp] = b;
            if (usp < USTACKSIZE) {
                usp++;
            }
        }

        else if (ram[i] == 163) {
            ustack[usp] = c;
            if (usp < USTACKSIZE) {
                usp++;
            }
        }

        else if (ram[i] == 164) {
            if (usp>0) {
                usp--;
                a = ustack[usp];
            }
        }

        else if (ram[i] == 165) {
            if (usp>0) {
                usp--;
                b = ustack[usp];
            }
        }

        else if (ram[i] == 166) {
            if (usp>0) {
                usp--;
                c = ustack[usp];
            }
        }

        else if (ram[i] == 167) {
            i++;
            ustack[usp] = ram[i];
            if (usp < USTACKSIZE) {
                usp++;
            }
        }

        else if (ram[i] == 170) {
            if (kbhit()) {
                a = getch();
            }
        }

        else if (ram[i] == 180) {
            i++;
            if (flags[0]) {
                ustack[usp] = 1;
            } else {
                ustack[usp] = 0;
            }
            if (usp < USTACKSIZE) {
                usp++;
            }
            continue;
        }
        else if (ram[i] == 181) {
            i++;
            if (!flags[0]) {
                ustack[usp] = 1;
            } else {
                ustack[usp] = 0;
            }
            if (usp < USTACKSIZE) {
                usp++;
            }
            continue;
        }
        else if (ram[i] == 182) {
            i++;
            if (flags[1]) {
                ustack[usp] = 1;
            } else {
                ustack[usp] = 0;
            }
            if (usp < USTACKSIZE) {
                usp++;
            }
            continue;
        }
        else if (ram[i] == 183) {
            i++;
            if (flags[2]) {
                ustack[usp] = 1;
            } else {
                ustack[usp] = 0;
            }
            if (usp < USTACKSIZE) {
                usp++;
            }
            continue;
        }

        else if (ram[i] == 190) {
            i++;
            RELJP(ram[i]);
            continue;
        }
        else if (ram[i] == 191) {
            if (flags[0]) {
                i++;
                RELJP(ram[i]);
                continue;
            } else {
                i=i+2;
            }
            continue;
        }
        else if (ram[i] == 192) {
            if (!flags[0]) {
                i++;
                RELJP(ram[i]);
                continue;
            } else {
                i=i+2;
            }
            continue;
        }
        else if (ram[i] == 193) {
            if (flags[1]) {
                i++;
                RELJP(ram[i]);
                continue;
            } else {
                i=i+2;
            }
            continue;
        }
        else if (ram[i] == 194) {
            if (flags[2]) {
                i++;
                RELJP(ram[i]);
                continue;
            } else {
                i=i+2;
            }
            continue;
        }

        else if (ram[i] == 250) {
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
            std::cout << "RAM Used: " << tmp * 4 << "b / " << RAMSIZE / 256 << "kb (" << tmp*100/RAMSIZE << "%)" << std::endl << std::endl;
            f_msg = true;
        }

        else if (ram[i] == 251) {
            f_dbg = true;
        }

        else if (ram[i] == 252) {
            f_dbg = false;
        }

        else if (ram[i] == 255) {
            if (sp == 0) {
                if (f_msg) {
                    ;
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

        else if (ram[i] == 300) {
            char lol[USTACKSIZE];
            for (int x = 0; x < USTACKSIZE; x++) {
                lol[x] = ustack[x];
            }
            system(lol);
        }

        else if (ram[i] == 301) {
            gotoxy(a,b);
        }
        /*else if (ram[i] == 302) {
            gfxclear(a);
        }
        else if (ram[i] == 303) {
            gfxmode(true);
        }
        else if (ram[i] == 304) {
            SetDCPenColor(hdc, RGB(a, b, c));
        }
        else if (ram[i] == 305) {
            SetPixel(hdc, a, b, RGB(255,0,0));
        }
        else if (ram[i] == 306) {
            MoveToEx(hdc, a, b, NULL);
        }
        else if (ram[i] == 307) {
            LineTo(hdc, a, b);
        }
        else if (ram[i] == 308) {
            ReleaseDC(window, hdc);
        }*/
        i++;
    }
    return 0;
}
