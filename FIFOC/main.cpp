#include<iostream>
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>


class FIFO
{
public:
	FIFO();
	FIFO(int index1); // конструктор с индексом
	~FIFO();
	void add(int x1); //добавление класса в конец FIFO
	void deleteFirst(); //удаление первого объекта FIFO.
	void del(); //удаление всех элементов


	FIFO* searchWriteFIFO();//поиск элемента с writeFIFO=1, возвращает указатель на элемент
	FIFO* searchReadFIFO(); //поиск элемента с readFIFO=1, возвращает указатель на элемент

	void showBoolReadFIFO(); // изображение очереди в виде таблицы, где столбцы index-индекс элемента, write - статус редактирования,read - статус чтения, x- значение свойства.
	
	void SetFIFOX(FIFO* p1,int x1); // изменение значения переменной объекта, стоящий в очереди на редактирование.
	int GetFIFOX(FIFO* p1); //получение значения переменной объекта, стоящий в очереди на чтение.

private:
	FIFO* Head; //Head - указатель на начало FIFO, 
	FIFO* Tail; //Tail -указатель на конец FIFO
	FIFO* Next; //Next - указатель на следующий класс FIFO.
	int x; // значение которое можно изменить или получить.
	int index; // для удобства представления порядка объектов в FIFO
	bool writeFIFO; //статус редактирования объекта
	bool readFIFO; //статус чтения объекта 
};

FIFO::FIFO() :index(0), writeFIFO(0),readFIFO(0)
{

}

FIFO::FIFO(int index1):index(index1)
{
}

FIFO::~FIFO()
{
	std::cout << "~FIFO()" << std::endl; 
}

void FIFO::add(int x1) {

	FIFO* p = new FIFO(index);
	index += 1;
	Next = NULL;
	if (Head != NULL) {
		Tail->Next = p;
		Tail = p;
		p->x=x1;
	}
	else {
		Head = Tail = p;
		p->writeFIFO = 1;
		p->readFIFO = 1;
		p->x=x1;
	}

}

void FIFO::showBoolReadFIFO() {
	FIFO* p = Head;
	std::cout << "showBoolReadFIFO()" << std::endl;
	while (p != Tail->Next)
	{
		std::cout<<"index:"<<p->index<<"  write:" << p->writeFIFO <<"  read:"<< p->readFIFO <<"  x=" << p->x<< std::endl;
		p = p->Next;
	}
	std::cout << std::endl;
	std::cout << std::endl;
	delete p;
}

FIFO* FIFO::searchWriteFIFO() {
	FIFO* p = Head;
	while (p != Tail->Next) {
		if (p->writeFIFO == 1) {
			return p;
		}
		else
		{
			p = p->Next;
		}
	}
	delete p;
	return Head;
}

FIFO* FIFO::searchReadFIFO()
{	
	FIFO* p = Head;
	while (p != Tail->Next) {
		if (p->readFIFO == 1) {
			return p;
		}
		else
		{
			p = p->Next;
		}
	}
	Head->readFIFO = 1;
	delete p;
	return Head;
}

void FIFO::SetFIFOX(FIFO* p1,int x1) {
	p1->x=x1;
	p1->writeFIFO = 0;
	if (p1->Next != NULL) {
		p1->Next->writeFIFO = 1;
	}
	else {
		Head->writeFIFO = 1;
	}

}

void FIFO::deleteFirst()
{
	FIFO* p = Head;
	if (Head->Next != NULL) {
		Head = Head->Next;

	}
	delete p;

}

int FIFO::GetFIFOX(FIFO* p1)
{
	p1->readFIFO = 0;
	if (p1->Next != NULL) {
		p1->Next->readFIFO = 1;
	}
	else {
		Head->readFIFO = 1;
	}
	return p1->x;
}

void FIFO::del() {
	while (Head != Tail) {

		if (Head->Next != NULL) {
			FIFO* p = Head;
			Head = Head->Next;
			std::cout<<"del ad: " << Head << std::endl;
			delete p;
		}

	}
	std::cout << "del ad: " << Tail << std::endl;
	delete Tail;

}



int main() {
	FIFO fifo;
	fifo.add(1); 
	fifo.add(2);
	fifo.add(3);
	fifo.add(4);
	fifo.add(5);
	fifo.showBoolReadFIFO(); 

	for (int i = 7; i > 0; i--) {
		fifo.SetFIFOX(fifo.searchWriteFIFO(), i); // настройка свойства x в элементах FIFO
		fifo.showBoolReadFIFO();
	}
	fifo.deleteFirst();

	for (int i = 7; i > 0; i--) {
		std::cout<<"GET(x)= "<<fifo.GetFIFOX(fifo.searchReadFIFO())<<std::endl; //получение свойства x из элементов FIFO
		fifo.showBoolReadFIFO();
	}


	fifo.del();
	std::cout << "_CrtDumpMemoryLeaks()=" << _CrtDumpMemoryLeaks() << std::endl; //проверка на утечку памяти.
	system("PAUSE");
	return 0;
}