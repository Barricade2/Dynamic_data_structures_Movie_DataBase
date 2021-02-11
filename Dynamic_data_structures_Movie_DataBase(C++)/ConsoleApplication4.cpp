// ConsoleApplication4.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include <string>
#include <stdlib.h>
#include <fstream>
#include <vector>
#include <tuple>

using namespace std;

class List
{
public:
	void insertFirst();
	void insertLast();
	void insertAt(int index);
	void insertLast(string Title, string Genre, string RelDate, string Actors, string Director, string Runtime);
	void removeFirst();
	void removeLast();
	void removeAt(int index);
	void findMovie(string title_val);
	void srcminMovie();
	tuple<string, string, string, string, string, string> operator[](const int index);
	void smallPrint(const int index);
	void printfrHd();
	void printfrTl();
	void emply();
	void clear();
	int GetSize() { return Size; }
	void sorted();
	void update(string title_val, const int index);
	void read();
	void Insert();
	void Delete();
	void Search();
	List ();
	~List ();

private:
	class lstMovie             //описание узла списка
	{
	public:                   //информационное поле           
		string Title;
		string Genre;
		string RelDate;
		string Actors;
		string Director;
		string Runtime;
		lstMovie *pNext; //указатель на узла следующего элемента списка
		lstMovie *pPrev; //указатель на узла предыдущего элемента списка
		//cin or file
		lstMovie(lstMovie *pNext = nullptr, lstMovie *pPrev = nullptr)
		{ //конструктор класса и инициализации  данных из консольного ввода
			/*cin.ignore(numeric_limits<streamsize>::max(), '\n');
			std::cin.clear();*/
			while (cin.get() != '\n');
			cout << "Название фильма: ";
			std::getline(std::cin,this->Title);
			cout << "Жанр: ";
			getline(cin, this->Genre);
			cout << "Год: ";
			getline(cin, this->RelDate);
			cout << "Актеры: ";
			getline(cin, this->Actors);
			cout << "Режиссёр: ";
			getline(cin, this->Director);
			cout << "Длительность: ";
			getline(cin, this->Runtime);
			this->pNext = pNext;
			this->pPrev = pPrev;
		}
		lstMovie(string Title, string Genre,string RelDate,string Actors,string Director,string Runtime, lstMovie *pNext = nullptr, lstMovie *pPrev = nullptr)
		{ //2 конструктор класса для инициализации  данных из текстового потока //Чтобы не усложнять код //не засорять
			while (cin.get() != '\n');
			/*cout << "Название фильма: "<<Title;
			getline(cin, this->Title);*/
			this->Title = Title;
			this->Genre = Genre;
			this->RelDate =  RelDate;
			this->Actors =  Actors;
			this->Director = Director;
			this->Runtime = Runtime;
			this->pNext = pNext;
			this->pPrev = pPrev;
		}
	};
	void print(lstMovie *crrent);
	lstMovie *head;
	lstMovie *tail;
	int Size;
};

List::List()
{
	head = nullptr;
	tail = nullptr;
	Size = 0;
}

List::~List()
{
	clear();
}


void List::emply()
{
		if (head == nullptr)
		{
			cout << "Список пустой" << endl;
		}
		else
		{
			cout << "Список не пустой" << endl;
		}
		system("pause");
}

void List::clear()
{
	while (Size)
	{
		removeFirst();
	}
}

void List::insertFirst()
{
	lstMovie *temp = new lstMovie();
	if (head != NULL)       //Если список не пуст
	{
		temp->pNext = head; //Указываем адрес на след элемента в соотв. поле
		head->pPrev = temp; //Указываем адрес нв преды за head элемента
		head = temp;        //Меняем адрес хвоста
	}
	else                    //Если список пустой
	{
		head = tail = temp; //Голова=Хвост=тот элемент, что сейчас добавили//Следующий и Предыдущий элемент указывает в пустоту
	}
	Size++;
}

void List::insertLast(string Title, string Genre, string RelDate, string Actors, string Director, string Runtime)
{

	lstMovie *temp = new lstMovie(Title, Genre, RelDate, Actors, Director, Runtime, nullptr);
	if (head != NULL)       //Если список не пуст
	{
		temp->pPrev = tail; //Указываем адрес предыд элемента на хвост
		tail->pNext = temp; //Указываем у хвоста адрес следующего
		tail = temp;        //Меняем адрес хвоста
	}
	else                    //Если список пустой
	{
		head = tail = temp;
	}
	Size++;
}

void List::insertLast()
{
	lstMovie *temp = new lstMovie(); //Выделение памяти под новый элемент
	if (head != NULL)        //Если список не пуст
	{
		temp->pPrev = tail;  //Указываем адрес на предыдущий элемент в соотв. поле
		tail->pNext = temp;  //Указываем адрес следующего за хвостом элемента
		tail = temp;         //Меняем адрес хвоста
	}
	else                     //Если список пустой
	{
		head = tail = temp;  //Голова=Хвост=тот элемент, что сейчас добавили//Следующий и Предыдущий элемент указывает в пустоту
	}
	Size++;
}

void List::removeFirst()
{
  if (head != nullptr){
	if (head->pNext == nullptr){    
		lstMovie*temp = head;
		tail = head = head->pNext;
		delete temp;}
   else{
	lstMovie*temp = head;
	head = head->pNext;
	delete temp;}
    Size--; }
  else emply();}

void List::removeLast()
{
	if (head != nullptr) {
		if (head->pNext == nullptr)
		{
			lstMovie*temp = tail;
			tail = head = tail->pPrev;
			delete temp;
		}
		else
		{
			lstMovie*temp = tail;
			tail = tail->pPrev;
			delete temp;
		}
		Size--;
	}
	else emply();
}
//
void List::insertAt(int index)
{
	if (index == 0) insertFirst();

	else if (index == Size || index > Size) {
		if (index > Size) {
			cout << "Индекс выходит за пределы каталога\n" << "Добавить в конец списка, index: " << Size + 1<< endl;
		}
		insertLast(); }

	else if (index <= Size / 2) {   
		lstMovie*previous = this->head;
		for (int i = 0; i < index - 1; i++)
		{previous = previous->pNext;}

		lstMovie*newNode = new lstMovie(previous->pNext, previous);
		previous->pNext = newNode;
		lstMovie*next = newNode->pNext;
		next->pPrev = newNode;
		Size++;}

	else if (index > Size / 2){
		lstMovie*next = this->tail;
		for (int i = Size - 1; index < i; i--)
		{next = next->pPrev;}

		lstMovie*newNode = new lstMovie(next, next->pPrev);
		next->pPrev = newNode;
		lstMovie*previous = newNode->pPrev;
		previous->pNext = newNode;
		Size++;}
}

void List::removeAt(int index)
{
	if (index == 0) removeFirst();

	else if (index == Size || index > Size) {
		cout << "Индекс выходит за пределы каталога\n" << "Добавить в конец списка, index: \n" << Size + 1;
	    insertLast();
}

	else if (index <= Size / 2) {
		lstMovie*previous = this->head;
		for (int i = 0; i < index - 1; i++)
		{previous = previous->pNext;}

		lstMovie*toDelete = previous->pNext;
		previous->pNext = toDelete->pNext;
		lstMovie*next = toDelete->pNext;
		delete toDelete;
		next->pPrev = previous;
		Size--; }

	else if (index > Size / 2) {
		lstMovie*next = this->tail;
		for (int i = Size - 1; index < i; i--)
		{next = next->pPrev; }

		lstMovie*toDelete = next->pPrev;
		next->pPrev = toDelete->pPrev;
		lstMovie*previous = toDelete->pPrev;
		delete toDelete;
		previous->pNext = next;
		Size--;
	}
}

tuple<string, string, string, string, string, string> List::operator[] (const int index) //поиск итератора по значению узла
{
	if (index <= Size / 2) {   
		int counter = 0;
		lstMovie*current = this->head;

		while (current != nullptr){
			if (counter == index) return { current->Title, current->Genre, current->RelDate, current->Actors, current->Director, current->Runtime };
			current = current->pNext;
			counter++;}
	}//return make_tuple(crrent->Title, crrent->Genre, crrent->RelDate, crrent->Actors, crrent->Director, crrent->Runtime, index); }
	else {
		int counter = Size - 1;
		lstMovie*current = this->tail;

		while (current != nullptr) {
			if (counter == index) return { current->Title , current->Genre, current->RelDate, current->Actors, current->Director, current->Runtime };
			current = current->pPrev;
			counter--; }
	}
}

void List::smallPrint(const int index) {   //поиск элемента с заданным значением x
	string Title, Genre, RelDate, Actors, Director, Runtime;
	tie(Title, Genre, RelDate, Actors, Director, Runtime) = this->operator[](index);
	cout << index << " | " << Title << " | " << Genre << "  | " << RelDate << "  | " << Actors << "  |  " << Director << "    |   " << Runtime << endl;
	system("pause");
}

void List::findMovie(string title_val)//  поиск фильма по названию
{
	lstMovie *crrent = head;
	lstMovie *temp = nullptr;
	int index = 0;
	while (crrent) {
		if (crrent->Title == title_val) {
			temp = crrent;
			print(temp);
		} 
		index += index;
		crrent = crrent->pNext;
	}
}

void List::print(lstMovie *crrent) {
	lstMovie*temp = crrent;
	if (temp!=nullptr) {
		cout << "Место  | " << "Название фильма   | " << "Жанр   | " << "Год  |" << "Актеры       | " << "Режиссёр       | " << "Длительность   | " << "Емкость база данных= " << Size << endl
			<< "------------------------------------------------------------------\n";
		cout << "index " << " | " << temp->Title << " | " << temp->Genre << "  | " << temp->RelDate << "  | " << temp->Actors << "  |  " << temp->Director << "    |   " << temp->Runtime << endl;
		system("pause");
	}
	else { cout << "Не нашлось";  system("pause"); }
}

void List::srcminMovie()
{
	lstMovie *temp = nullptr;
	lstMovie *temp1 = nullptr;
	lstMovie *temp2 = nullptr;
	int index = Size / 2; //отhead(0) to index; от index+1 to taile;
	if (Size == 1) { temp = head; }
	else {
		lstMovie*previous = head;
		string min1 = previous->Title;
		temp1 = previous;
		for (int i = 0; i < index; i++)
		{
			if (previous->Title < min1) {
				min1 = previous->Title; temp = previous;
			}previous = previous->pNext;
		}

		lstMovie*next = tail;
		string min2 = next->Title;
		temp2 = next;
		for (int i = Size - 1; index <= i; i--)
		{
			if (next->Title < min2) {
				min2 = next->Title; temp2 = next;
			}
			next = next->pPrev;
		}

		if (min1 <= min2) {temp = temp1; } //if (previous->pPrev->Title < next->pNext->Title)
		else {temp = temp2; }
	}
	print(temp);
}

void List::update(string title_val, const int index) //  обновить инфо по месту списка
{
	int counter = 0;
	for (lstMovie *crrent = head; crrent != nullptr; crrent = crrent->pNext) {
		if (counter == index)
		{
			crrent->Title = title_val;
		}
		counter++;}
	if (index > Size) {cout << "Не нашлось"; } 
	}

void List::sorted() { // Сортировка вставками
	lstMovie*a, *b, *p, *h = nullptr;
	for (lstMovie* i = head; i != nullptr;) {
		a = i;
		i = i->pNext;
		b = h;
		for (p = nullptr; (b != nullptr) && (a->Title > b->Title);) {
			p = b;
			b = b->pNext;
		}
		if (p == nullptr) {
			a->pNext = h;
			h = a;
		}
		else { a->pNext = b; p->pNext = a; }
	}
	if (h != nullptr)
		head = h;
}

void List::read() {
	string item;
	ifstream lstMovieFile("file.txt");
	if (!lstMovieFile.is_open()) //Не удалось открыть файл lstMovieFile.is_open()==false
	{
		exit(EXIT_FAILURE);
	}
	else {
		cout << "This is good\n";
		while (getline(lstMovieFile, item))
		{
			vector<string> arr;
			string str(item);
			string delim(";");
			size_t prev = 0;
			size_t next;
			size_t delta = delim.length();

			while ((next = str.find(delim, prev)) != string::npos) {
				string tmp = str.substr(prev, next - prev);
				arr.push_back(str.substr(prev, next - prev));
				prev = next + delta;
			}
			insertLast(arr[0], arr[1], arr[2], arr[3], arr[4], arr[5]);
			arr.clear();
		}
	}	lstMovieFile.close();
}

void List::printfrHd()
{
	system("cls");
	lstMovie *print = head;
	cout << "Место|" << "\tНазвание|" << "\tЖанр|" << "\tГод|"<< "\tАктеры|" <<"\tРежиссёр|" << "\tДлительность|"<<"\tЕмкость база данных= "<< Size << endl
		<< "------------------------------------------------------------------------------\n";
	int i = 0;
	while (print)
	{
		cout << ++i << "\t|" << print->Title <<"\t|"<< print->Genre << "\t|" << print->RelDate << "\t|" << print->Actors << "\t|" << print->Director << "\t|" << print->Runtime<<endl;
		print = print->pNext;
	}
	system("pause");
}

void List::printfrTl()
{
	system("cls");
	int i = 0;
	lstMovie *print = tail;
	cout << "Место|" << "\tНазвание|" << "\tЖанр|" << "\tГод|" << "\tАктеры|" << "\tРежиссёр|" << "\tДлительность|" << "\tЕмкость база данных= " << Size << endl
		<< "------------------------------------------------------------------------------\n";
	while (print)
	{
		cout << ++i << "\t|" << print->Title << "\t|" << print->Genre << "\t|" << print->RelDate << "\t|" << print->Actors << "\t|" << print->Director << "\t|" << print->Runtime << endl;
		print = print->pPrev;
	}
	cout << endl;
}


void List::Search()
{
	system("cls");
	int choice;
	cout << "1 - ПОИСК ФИЛЬМА ПО ИНДЕКСУ\n" << "2 - ПОИСК ФИЛЬМА ПО НАЗАВАНИЮ\n" << "3 - ПОИСК МИНИМАЛЬНОГО ЭЛЕМЕНТА ПО НАЗВАНИЮ\n" << "4 - ИЗМЕНИТЬ НАЗВАНИЕ ФИЛЬМА\n" 
		<< "-------------------------------------------------\n" << "Please enter 1-4 numbers:\n";
	string title;
	cin >> choice;
	{//ввод прекращается из-за не соответствие типу данных
		switch (choice) {
		case 1:
			cout << "Selceted 1 - ПОИСК ФИЛЬМОВ ПО ИНДЕКСУ\n" << "Ввод нужного индекса: ";
			int index;
			cin >> index;
			smallPrint(index);
			break;
		case 2:
			cout << "Selected 2 -ПОИСК ФИЛЬМОВ ПО НАЗАВАНИЮ\n"<<"Ввод title(название) фильма:   ";
			while (cin.get() != '\n');
			cin.clear();
			getline(cin, title);
			findMovie(title);
			break;
		case 3:
			cout << "Selected 3 - ПОИСК МИНИМАЛЬНОГО ЭЛЕМЕНТА ПО НАЗВАНИЮ\n";
			srcminMovie();
			break;
		case 4:
			cout << "Selected 4 - ИЗМЕНИТЬ НАЗВАНИЕ ФИЛЬМА\n" << "Ввод title(название):  ";
			while (cin.get() != '\n');
			cin.clear();
			getline(cin, title);
			cin >> index;
			update(title, index);
			smallPrint(index);
			break;
		case 9:
			break;
		default: cout << "Некорректный ввод\n";
		}
	}
}

void List::Delete(){
system("cls");
int choice;
cout << "1 - УДАЛИТЬ ПЕРВЫЙ ФИЛЬМ С КАТАЛОГА\n" << "2 - УДАЛИТЬ ПОСЛЕДНЕ ДОБАВЛЕННЫЙ ФИЛЬМ С КАТАЛОГА\n" << "3 - УДАЛИТЬ ФИЛЬМ ПО ИНДЕКСУ\n"
 << "-------------------------------------------------\n" << "Please enter 1-3 number:\n";
cin >> choice;
{//ввод прекращается из-за не соответствие типу данных
	switch (choice) {
	case 1:
		cout << "Selected 1 - УДАЛИТЬ ПЕРВЫЙ ФИЛЬМ С КАТАЛОГА\n";
		removeFirst();
		break;
	case 2: cout << "Selected 2 - УДАЛИТЬ ПОСЛЕДНЕ ДОБАВЛЕННЫЙ ФИЛЬМ С КАТАЛОГА\n";
		removeLast();
		break;
	case 3:
		cout << "Selected 3 - УДАЛИТЬ ФИЛЬМ ПО ИНДЕКСУ\n" << "Ввод нужного индекса: ";
		int index;
		cin >> index;
		removeAt(index);
		cout << "It's Ok.\n";
		system("pause");
		break;
	case 9:
		break;
	default: cout << "Некорректный ввод\n";
	}
}
}

void List::Insert()
{
	system("cls");
	int choice;
	cout <<"1 - ДОБАВИТЬ НОВЫЙ ФИЛЬМ В НАЧАЛО КАТАЛОГА\n"<<"2 - ДОБАВИТЬ НОВЫЙ ФИЛЬМ В КОНЕЦ КАТАЛОГА\n"<<"3 - ДОБАВИТЬ НОВЫЙ ФИЛЬМ В КАТАЛОГ ПО ИНДЕКСУ\n"
		 <<"4 - СЧИТЫВАТЬ ЗАПИСИ С ФАЙЛА\n "<< "-------------------------------------------------\n" << "Please enter 1-4 number:\n";
	cin >> choice;
	{//ввод прекращается из-за не соответствие типу данных
		switch (choice) {
		case 1:
			cout << "Selected 1 -> ДОБАВИТЬ НОВЫЙ ФИЛЬМ В НАЧАЛО КАТАЛОГА\n";
			insertFirst();
			break;
		case 2:
			cout << "Selected 2 - ДОБАВИТЬ НОВЫЙ ФИЛЬМ В КОНЕЦ КАТАЛОГА\n";
			insertLast();
			break;
		case 3:
			cout << "Selected 3 -> ДОБАВИТЬ НОВЫЙ ФИЛЬМ В КАТАЛОГ ПО ИНДЕКСУ\n" << "Ввод нужного индекса: ";
			int index;
			cin >> index;
			insertAt(index);
			break;
		case 4:
			cout << "Selected 4 -> СЧИТЫВАТЬ ЗАПИСИ С ФАЙЛА\n ";
			read();
			break;
		case 9:
			break;
		default: cout << "Некорректный ввод\n";
		}
	}
}


void showmenu()
	{//Менью приветсвие //нажатие два раза клавишы// время счетчик.
		cout << "Please enter 1-7 number:\n" << "-------------------------------------------------\n";
		cout << "1 - ДОБАВИТЬ НОВЫЙ ФИЛЬМ В КАТАЛОГ" << endl;
		cout << "2 - УДАЛИТЬ ВЫБРАННЫЙ ФИЛЬМ С КАТАЛОГА" << endl;
		cout << "3 - ВЗГЛЯНУТЬ НА СПИСОК ФИЛЬМОВ" << endl;
		cout << "4 - УЗНАТЬ КОЛИЧЕСТВО ДОБАВЛЕННЫХ ФИЛЬМОВ" << endl;		
		cout << "5 - ПОИСК И ОБНОВЛЕНИЯ ФИЛЬМОВ В БАЗЕ" << endl;
		cout << "6 - ОТСОРТИРОВАТЬ ФИЛЬМ" << endl;
		cout << "7 - ОЧИСТИТЬ БАЗУ ДАННЫХ" << endl;
		cout << "8 - РАЗБИТЬ КАТАЛОГ" << endl;
		cout << "9 - ВЫХОД" << endl;
		cout << "-------------------------------------------------\n" << "Please enter 1-9 number:\n";
	}

int main()
{
	setlocale(LC_CTYPE, "rus");
	int choice;
	cout << "СОЗДАЕТСЯ КАТАЛОГ..." << endl;
	system("pause");
	List lst;
	lst.emply();
	//lst.insertFirst();
	//lst.insertLast("al", "", "", "", "", "");
	//lst.insertLast("tile","","","","","");
	//lst.insertLast("tal", "", "", "", "", "");
	//lst.insertLast("aa", "", "", "", "", "");
	//lst.printfrHd();
	//lst.emply();
	while ((true)) {
		system("cls");
		showmenu();
		cin >> choice;
		switch (choice) {
		case 1:
			lst.Insert();
			break;
		case 2:
			lst.Delete();
			break;
		case 3:
			lst.printfrHd();
			break;
		case 4:
			cout<<"Емкость базы данных: " 
			<< lst.GetSize()<<endl;
			system("pause");
			break;
		case 5:
			lst.Search();
			break;
		case 6:
			lst.sorted();
			cout << "It's Ok.\n";
			system("pause");
			break;
		case 7:
			lst.clear();
			break;
		case 9:
			return 0;
		default: cout<<"Некорректный ввод\n";
		}	
	}
	return 0;
}