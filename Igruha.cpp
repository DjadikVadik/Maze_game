
//                               Крупное практическое задание по двумерным массивам
//
//   1.Реализовать перемещение персонажа по лабиринту стрелками влево, вправо, вверх и вниз.Персонаж не должен проходить сквозь стены.Если персонаж  дошёл до выхода
//   из лабиринта в нижнем правом углу - игра заканчивается победой(вывести диалог с сообщением "победа - найден выход" в MessageBox).
//
//   2.Реализовать подсчёт собранных монет, количество монетв наличии выводить в заголовок окна(начиная с нуля монет).Если все монеты лабиринта собраны -
//   игра заканчивается победой(вывести диалог с сообщением "победа - монеты собраны").
//
//   3.Реализовать систему "здоровье персонажа": изначально здоровье на уровне 100 % (выводить текущее состояние здоровья в заголовок окна, либо правее лабиринта с помощью
//	 установки курсора и типа COORD).Пересечение с каждым врагом отнимает от 20 до 25 % здоровья, при этом враг исчезает.Добавить новый тип объектов лабиринта - "лекарство",
//	 который при сборе поправляет здоровье на 5 % .Здоровье персонажа не может быть более 100 %, то есть, если здоровье уже на максимуме, то лекарство нельзя подобрать.
// 	 Если здоровье закончилось(упало до 0 %) - игра заканчивается поражением(вывести диалог с сообщением "поражение - закончилось здоровье").
//
//	 4.Реализовать систему «энергия персонажа» : изначально энергии 500 единиц.Каждое перемещение персонажа тратит одну единицу энергии(выводить текущее состояние энергии
//	 в заголовок окна, либо правее лабиринта).Добавить новый тип объектов лабиринта - "чашка кофе U", которая при сборе повышает запас энергии на 25 единиц.
//   Других ограничений на максимальный уровень запаса энергии нет. Если энергия закончилась - игра заканчивается поражением(вывести диалог с сообщением "поражение – закончилась энергия").
//
//	 5.Реализовать один метод атаки персонажа :
//   *лазерный меч / пинок ногой : все враги, находящиеся в радиусе двух ячеек от персонажа – при нажатии на клавишу Q погибают.
//   Каждое применение оружия(даже если рядом нет врагов) отнимает 10 единиц энергии.Если энергия на исходе – применить оружие нельзя.
//
//   6.Если в лабиринте не осталось врагов - игра заканчивается победой(вывести диалог с сообщением "победа - враги уничтожены!").
//
//   7.Добавить фоновую музыку(гугл в помощь, как это сделать – либо стучите в личку телеграмма).
//
//   8.Реализовать систему "респавн врагов": при каждом 20 - том  перемещении персонажа в случайной(либо определённой) точке лабиринта возникает новый вражеский юнит.
//
//   9.Реализовать перемещение врагов :
//   *ПСИХ НА ДИСКОТЕКЕ - каждый враг перемещается на одну свободную соседнюю ячейку в случайном направлении при каждом перемещении персонажа.Биткоины и прочие
//   объекты враг не подбирает, умышленно на персонажа не нападает.
//
//   10. * Реализовать нормальный, а не случайный алгоритм генерации лабиринта, например систему подземных пещер.

#include<iostream>
#include<conio.h>
#include<windows.h>
#pragma comment(lib, "winmm.lib")
using namespace std;

struct setings {

	const int X = 80;
	const int Y = 25;
	char mass[25][80];

	bool dvigenie = false;
	bool ataka = false;
	bool gameOver = false;
	int monety;
	int sobrano = 0;
	int monster;
	int live = 100;
	int energy = 500;
	int kolichestvo_hodov = 0;
	string napravlenie;
} options;


void initial() {

	system("color F0");


	for (int y = 0; y < options.Y; y++)          // стены комнаты
		for (int x = 0; x < options.X; x++) {
			if ((x == 2 && y > 1 && y < options.Y - 2) ||
				(x == 3 && y > 1 && y < options.Y - 2) ||
				(x == options.X - 3 && y > 1 && y < options.Y - 2) ||
				(x == options.X - 4 && y > 1 && y < options.Y - 2))
				options.mass[y][x] = ' ';
			else
				options.mass[y][x] = char(219);
		}
	int n = rand() % (options.Y - 4) + 2;           // выход из абиринта
	options.mass[n][options.X - 1] = ' ';
	options.mass[n][options.X - 2] = ' ';
	int n1 = rand() % (options.Y - 4) + 2;
	options.mass[n1][1] = char(2);                 // начальная позиция нашего героя
}

void labirint(int y = options.Y / 2, int x = options.X - 4) {

	options.mass[y][x] = ' ';
	options.mass[y][x + 1] = ' ';

	string arr[4];
	int n = 0;

	if (options.mass[y - 2][x] != ' ' && options.mass[y - 2][x + 1] != ' ' && y - 2 > 0) {
		arr[n] = "UP";
		n++;
	}
	if (options.mass[y + 2][x] != ' ' && options.mass[y + 2][x + 1] != ' ' && y + 2 < options.Y - 1) {
		arr[n] = "DOWN";
		n++;
	}
	if (options.mass[y][x - 4] != ' ' && options.mass[y][x - 3] != ' ' && x - 4 > 1) {
		arr[n] = "LEFT";
		n++;
	}
	if (options.mass[y][x + 4] != ' ' && options.mass[y][x + 5] != ' ' && x + 5 < options.X - 2) {
		arr[n] = "RIGHT";
		n++;
	}

	int x1, y1;
	int k;
	if (n > 0) k = rand() % n;
	else return;


	if (arr[k] == "UP")
	{
		options.mass[y - 1][x] = ' ';
		options.mass[y - 1][x + 1] = ' ';
		options.mass[y - 2][x] = ' ';
		options.mass[y - 2][x + 1] = ' ';
		y1 = y - 2;
		x1 = x;
	}

	else if (arr[k] == "DOWN")
	{
		options.mass[y + 1][x] = ' ';
		options.mass[y + 1][x + 1] = ' ';
		options.mass[y + 2][x] = ' ';
		options.mass[y + 2][x + 1] = ' ';
		y1 = y + 2;
		x1 = x;
	}

	else if (arr[k] == "LEFT")
	{
		options.mass[y][x - 1] = ' ';
		options.mass[y][x - 2] = ' ';
		options.mass[y][x - 3] = ' ';
		options.mass[y][x - 4] = ' ';
		x1 = x - 4;
		y1 = y;
	}

	else if (arr[k] == "RIGHT")
	{
		options.mass[y][x + 1] = ' ';
		options.mass[y][x + 2] = ' ';
		options.mass[y][x + 3] = ' ';
		options.mass[y][x + 4] = ' ';
		options.mass[y][x + 5] = ' ';
		x1 = x + 4;
		y1 = y;
	}

	if (n > 0) labirint(y1, x1);
	if (n > 0) labirint(y, x);
}

void initial_objekt() {


	for (int y = 0; y < options.Y; y++)                  //монеты на карте
		for (int x = 0; x < options.X; x++) {
			if (options.mass[y][x] == ' ') {
				if (rand() % 70 == 1) {
					options.mass[y][x] = char(15);
					options.monety++;
				}
			}
		}

	for (int y = 0; y < options.Y; y++)                //монстры на карте
		for (int x = 0; x < options.X; x++) {
			if (options.mass[y][x] == ' ') {
				if (rand() % 70 == 1) {
					options.mass[y][x] = char(1);
				}
			}
		}

	for (int y = 0; y < options.Y; y++)                //лекарство на карте
		for (int x = 0; x < options.X; x++) {
			if (options.mass[y][x] == ' ') {
				if (rand() % 70 == 1) {
					options.mass[y][x] = char(3);
				}
			}
		}

	for (int y = 0; y < options.Y; y++)                // чашка кофе на карте
		for (int x = 0; x < options.X; x++) {
			if (options.mass[y][x] == ' ') {
				if (rand() % 70 == 1) {
					options.mass[y][x] = 'U';
				}
			}
		}
}

void respawn_monster() {

	if (options.kolichestvo_hodov % 20 == 0 && options.dvigenie) {

		int y = rand() % (options.Y - 7) + 3;
		int x = rand() % (options.X - 7) + 3;
		if (options.mass[y][x] == ' ') options.mass[y][x] = char(1);
		else if (options.mass[y][x + 1] == ' ') options.mass[y][x + 1] = char(1);
		else if (options.mass[y][x - 1] == ' ') options.mass[y][x - 1] = char(1);
		else if (options.mass[y + 1][x] == ' ') options.mass[y + 1][x] = char(1);
		else if (options.mass[y - 1][x] == ' ') options.mass[y - 1][x] = char(1);
	}
}

void proverka_objekt() {

	int n = 0;

	for (int y = 0; y < options.Y; y++)
		for (int x = 0; x < options.X; x++)
			if (options.mass[y][x] == char(15))
				n++;
	options.sobrano = options.monety - n;
	if (n == 0) {
		options.gameOver = true;
		MessageBoxA(0, "Все монеты собраны !!!", "ПОБЕДА!!!", MB_OK);
	}

	n = 0;

	for (int y = 0; y < options.Y; y++)
		for (int x = 0; x < options.X; x++)
			if (options.mass[y][x] == char(1))
				n++;

	options.monster = n;

	if (n == 0) {
		options.gameOver = true;
		MessageBoxA(0, "Все монстры убиты !!!", "ПОБЕДА !!!", MB_OK);
	}

	if (options.live > 100) options.live = 100;
	else if (options.live < 0) options.live = 0;
	if (options.live == 0) {
		options.gameOver = true;
		MessageBoxA(0, "Здоровье закончилось !!!", "ПОРАЖЕНИЕ !!!", MB_OK);
	}

	if (options.energy <= 0) {
		options.gameOver = true;
		MessageBoxA(0, "Энергия закончилась !!!", "ПОРАЖЕНИЕ !!!", MB_OK);
	}
}

void input() {

	if (_kbhit()) {

		switch (_getch()) {

		case 75:  // влево
			options.napravlenie = "LEFT";
			break;
		case 77: // вправо
			options.napravlenie = "RIGHT";
			break;
		case 80: // вниз
			options.napravlenie = "DOWN";
			break;
		case 72: // вверх
			options.napravlenie = "UP";
			break;
		case 113: // атака
			options.ataka = true;
			break;
		}
	}
}

void logika_pleyer() {

	HANDLE h = GetStdHandle(-11);
	CONSOLE_CURSOR_INFO info;
	info.bVisible = false;
	info.dwSize = 100;
	SetConsoleCursorInfo(h, &info);
	COORD cursor;

	for (int y = 0; y < options.Y; y++)
		for (int x = 0; x < options.X; x++) {
			if (options.mass[y][x] == char(2) && options.napravlenie == "LEFT" && options.mass[y][x - 1] != char(219))
			{
				options.kolichestvo_hodov++;
				if (options.mass[y][x - 1] == char(1)) options.live -= rand() % 6 + 20;
				else if (options.mass[y][x - 1] == char(3)) {
					options.live = options.live + 5;
				}
				else if (options.mass[y][x - 1] == 'U') {
					options.energy += 25;
				}

				options.mass[y][x] = ' ';
				options.mass[y][x - 1] = char(2);

				cursor.X = x;
				cursor.Y = y;
				SetConsoleCursorPosition(h, cursor);
				cout << " ";

				SetConsoleTextAttribute(h, 15);
				cursor.X = x - 1;
				cursor.Y = y;
				SetConsoleCursorPosition(h, cursor);
				cout << char(2);

				options.energy--;
				options.napravlenie = " ";
				options.dvigenie = true;
			}
			else if (options.mass[y][x] == char(2) && options.napravlenie == "RIGHT" && options.mass[y][x + 1] != char(219))
			{
				options.kolichestvo_hodov++;
				if (options.mass[y][x + 1] == char(1)) options.live -= rand() % 6 + 20;
				else if (options.mass[y][x + 1] == char(3)) {
					options.live = options.live + 5;
				}
				else if (options.mass[y][x + 1] == 'U') {
					options.energy += 25;
				}

				options.mass[y][x] = ' ';
				options.mass[y][x + 1] = char(2);

				cursor.X = x;
				cursor.Y = y;
				SetConsoleCursorPosition(h, cursor);
				cout << " ";

				SetConsoleTextAttribute(h, 15);
				cursor.X = x + 1;
				cursor.Y = y;
				SetConsoleCursorPosition(h, cursor);
				cout << char(2);

				options.energy--;
				options.napravlenie = " ";
				options.dvigenie = true;
			}
			else if (options.mass[y][x] == char(2) && options.napravlenie == "DOWN" && options.mass[y + 1][x] != char(219))
			{
				options.kolichestvo_hodov++;
				if (options.mass[y + 1][x] == char(1)) options.live -= rand() % 6 + 20;
				else if (options.mass[y + 1][x] == char(3)) {
					options.live = options.live + 5;
				}
				else if (options.mass[y + 1][x] == 'U') {
					options.energy += 25;
				}

				options.mass[y][x] = ' ';
				options.mass[y + 1][x] = char(2);

				cursor.X = x;
				cursor.Y = y;
				SetConsoleCursorPosition(h, cursor);
				cout << " ";

				SetConsoleTextAttribute(h, 15);
				cursor.X = x;
				cursor.Y = y + 1;
				SetConsoleCursorPosition(h, cursor);
				cout << char(2);

				options.energy--;
				options.napravlenie = " ";
				options.dvigenie = true;
			}
			else if (options.mass[y][x] == char(2) && options.napravlenie == "UP" && options.mass[y - 1][x] != char(219))
			{
				options.kolichestvo_hodov++;
				if (options.mass[y - 1][x] == char(1)) options.live -= rand() % 6 + 20;
				else if (options.mass[y - 1][x] == char(3)) {
					options.live = options.live + 5;
				}
				else if (options.mass[y - 1][x] == 'U') {
					options.energy += 25;
				}
				
				options.mass[y][x] = ' ';
				options.mass[y - 1][x] = char(2);

				cursor.X = x;
				cursor.Y = y;
				SetConsoleCursorPosition(h, cursor);
				cout << " ";

				SetConsoleTextAttribute(h, 15);
				cursor.X = x;
				cursor.Y = y - 1;
				SetConsoleCursorPosition(h, cursor);
				cout << char(2);

				options.energy--;
				options.napravlenie = " ";
				options.dvigenie = true;
			}
			if (options.mass[y][options.X - 1] == char(2))
			{
				options.gameOver = true;
				MessageBoxA(0, "Вы нашли выход !!!", "ПОБЕДА!!!", MB_OK);
			}
		}
}

void logika_ataka() {


	HANDLE h = GetStdHandle(-11);
	CONSOLE_CURSOR_INFO info;
	info.bVisible = false;
	info.dwSize = 100;
	SetConsoleCursorInfo(h, &info);
	COORD cursor;

	for (int y = 0; y < options.Y; y++)
		for (int x = 0; x < options.X; x++) {
			if (options.mass[y][x] == char(2) && options.ataka) {
				for (int i = y - 2; i <= y + 2; i++)
					for (int j = x - 2; j <= x + 2; j++)
						if (options.mass[i][j] == char(1) && options.energy >= 10) {
							options.mass[i][j] = ' ';
							cursor.X = j;
							cursor.Y = i;
							SetConsoleCursorPosition(h, cursor);
							cout << " ";
							options.energy -= 10;
						}	
			}
		}
}

void logika_monster() {

	HANDLE h = GetStdHandle(-11);

	CONSOLE_CURSOR_INFO info;
	info.bVisible = false;
	info.dwSize = 100;
	SetConsoleCursorInfo(h, &info);
	COORD cursor;

	int perestanovki[100][2];           // массив для сохранения координат монстров которых мы уже переставили
	int n1 = 0;                        // номер элэмента этого массива
	bool perestanovka = false;         // переменная для проверки: переставляли мы этого монстра , или нет

	for (int y = 0; y < options.Y; y++)
		for (int x = 0; x < options.X; x++) {

			string arr[4];
			int n = 0;

			if (options.mass[y][x] == char(1) && (options.mass[y - 1][x] == ' ' || options.mass[y - 1][x] == char(2))) {
				arr[n] = "UP";
				n++;
			}
			if (options.mass[y][x] == char(1) && (options.mass[y + 1][x] == ' ' || options.mass[y + 1][x] == char(2))) {
				arr[n] = "DOWN";
				n++;
			}
			if (options.mass[y][x] == char(1) && (options.mass[y][x - 1] == ' ' || options.mass[y][x - 1] == char(2))) {
				arr[n] = "LEFT";
				n++;
			}
			if (options.mass[y][x] == char(1) && (options.mass[y][x + 1] == ' ' || options.mass[y][x + 1] == char(2))) {
				arr[n] = "RIGHT";
				n++;
			}

			int k;
			if (n > 0) k = rand() % n;
			else continue;

			for (int i = 0; i < 100; i++) {
				if (perestanovki[0][i] == y) {
					for (int j = 0; j < 100; j++)
						if (perestanovki[1][i] == x)
							perestanovka = true;
				}
			}

			if (arr[k] == "UP" && options.dvigenie && !perestanovka)
			{
				options.mass[y][x] = ' ';
				cursor.X = x;
				cursor.Y = y;
				SetConsoleCursorPosition(h, cursor);
				cout << " ";
				if (options.mass[y - 1][x] == char(2)) {
					options.mass[y - 1][x] = char(2);
					SetConsoleTextAttribute(h, 15);
					cursor.X = x;
					cursor.Y = y - 1;
					SetConsoleCursorPosition(h, cursor);
					cout << char(2);
					options.live -= rand() % 6 + 20;
				}
				else {
					options.mass[y - 1][x] = char(1);
					SetConsoleTextAttribute(h, 12);
					cursor.X = x;
					cursor.Y = y - 1;
					SetConsoleCursorPosition(h, cursor);
					cout << char(1);
					perestanovki[0][n1] = y - 1;
					perestanovki[1][n1] = x;
					n1++;
				}
			}

			else if (arr[k] == "DOWN" && options.dvigenie && !perestanovka)
			{
				options.mass[y][x] = ' ';
				cursor.X = x;
				cursor.Y = y;
				SetConsoleCursorPosition(h, cursor);
				cout << " ";
				if (options.mass[y + 1][x] == char(2)) {
					options.mass[y + 1][x] = char(2);
					SetConsoleTextAttribute(h, 15);
					cursor.X = x;
					cursor.Y = y + 1;
					SetConsoleCursorPosition(h, cursor);
					cout << char(2);
					options.live -= rand() % 6 + 20;
				}
				else {
					options.mass[y + 1][x] = char(1);
					SetConsoleTextAttribute(h, 12);
					cursor.X = x;
					cursor.Y = y + 1;
					SetConsoleCursorPosition(h, cursor);
					cout << char(1);
					perestanovki[0][n1] = y + 1;
					perestanovki[1][n1] = x;
					n1++;
				}
			}

			else if (arr[k] == "LEFT" && options.dvigenie && !perestanovka)
			{
				options.mass[y][x] = ' ';
				cursor.X = x;
				cursor.Y = y;
				SetConsoleCursorPosition(h, cursor);
				cout << " ";
				if (options.mass[y][x - 1] == char(2)) {
					options.mass[y][x - 1] = char(2);
					SetConsoleTextAttribute(h, 15);
					cursor.X = x - 1;
					cursor.Y = y;
					SetConsoleCursorPosition(h, cursor);
					cout << char(2);
					options.live -= rand() % 6 + 20;
				}
				else {
					options.mass[y][x - 1] = char(1);
					SetConsoleTextAttribute(h, 12);
					cursor.X = x - 1;
					cursor.Y = y;
					SetConsoleCursorPosition(h, cursor);
					cout << char(1);
					perestanovki[0][n1] = y;
					perestanovki[1][n1] = x - 1;
					n1++;
				}
			}

			else if (arr[k] == "RIGHT" && options.dvigenie && !perestanovka)
			{
				options.mass[y][x] = ' ';
				cursor.X = x;
				cursor.Y = y;
				SetConsoleCursorPosition(h, cursor);
				cout << " ";
				if (options.mass[y][x + 1] == char(2)) {
					options.mass[y][x + 1] = char(2);
					SetConsoleTextAttribute(h, 15);
					cursor.X = x + 1;
					cursor.Y = y;
					SetConsoleCursorPosition(h, cursor);
					cout << char(2);
					options.live -= rand() % 6 + 20;
				}
				else {
					options.mass[y][x + 1] = char(1);
					SetConsoleTextAttribute(h, 12);
					cursor.X = x + 1;
					cursor.Y = y;
					SetConsoleCursorPosition(h, cursor);
					cout << char(1);
					perestanovki[0][n1] = y;
					perestanovki[1][n1] = x + 1;
					n1++;
				}
			}
			perestanovka = false;
		}
}

void show() {


	HANDLE h = GetStdHandle(-11);

	for (int y = 0; y < options.Y; y++) {
		for (int x = 0; x < options.X; x++) {
			if (options.mass[y][x] == char(2)) {
				SetConsoleTextAttribute(h, 15);
				cout << options.mass[y][x];
			}
			else if (options.mass[y][x] == char(15)) {
				SetConsoleTextAttribute(h, 14);
				cout << options.mass[y][x];
			}
			else if (options.mass[y][x] == char(1)) {
				SetConsoleTextAttribute(h, 12);
				cout << options.mass[y][x];
			}
			else if (options.mass[y][x] == char(3)) {
				SetConsoleTextAttribute(h, 10);
				cout << options.mass[y][x];
			}
			else if (options.mass[y][x] == 'U') {
				SetConsoleTextAttribute(h, 5);
				cout << options.mass[y][x];
			}
			else {
				SetConsoleTextAttribute(h, 9);
				cout << options.mass[y][x];
			}
		}

		cout << "\n";
	}
}

void statistica() {

	HANDLE h = GetStdHandle(-11);

	CONSOLE_CURSOR_INFO info;
	info.bVisible = false;
	info.dwSize = 100;
	SetConsoleCursorInfo(h, &info);

	COORD cursor;
	cursor.X = 84;
	cursor.Y = 1;
	SetConsoleCursorPosition(h, cursor);
	cout << "SOBRANO MONET - " << options.sobrano << "  ";

	cursor.X = 84;
	cursor.Y = 2;
	SetConsoleCursorPosition(h, cursor);
	cout << "LIVE = " << options.live << "%        ";

	cursor.X = 84;
	cursor.Y = 3;
	SetConsoleCursorPosition(h, cursor);
	cout << "ENERGY = " << options.energy << "       ";

	cursor.X = 84;
	cursor.Y = 4;
	SetConsoleCursorPosition(h, cursor);
	cout << "MONSTER = " << options.monster << "       ";
}

DWORD WINAPI MusicThread(void* param) {
	PlaySoundA("time.wav", NULL, SND_LOOP | SND_ASYNC);
	return 0;
}



int main()
{	
	CreateThread(0, 0, MusicThread, 0, 0, 0);
	srand(time(0));
	initial();
	labirint();
	initial_objekt();
	show();
	do {
		input();
		logika_pleyer();
		logika_monster();
		respawn_monster();
		proverka_objekt();
		logika_ataka();
		statistica();
		options.ataka = false;
		options.dvigenie = false;
	} while (!options.gameOver);
}