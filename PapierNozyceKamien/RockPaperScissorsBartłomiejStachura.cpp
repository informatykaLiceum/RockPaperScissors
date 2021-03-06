// ConsoleAppli// PapierNozyceKamien.cpp : Defines the entry point for the console application.
//

#include <cstdlib>
#include <random>
#include <iostream>
#include <array>

enum Ruch { Papier, Nozyce, Kamien };
enum Wynik { Remis, Wygral_Pierwszy, Wygral_Drugi };



std::ostream& operator<<(std::ostream& s, Ruch w)
{
	return s << ((w == Kamien) ? "Kamien" : (w == Papier) ? "Papier" : "Nozyce");
}

class Gracz {
public:
	virtual void przedstawSie() = 0;
	virtual Ruch ruch(Ruch poprzedniRuchPrzeciwnika) = 0;
	virtual void reset() = 0;
};


class Gra {
	std::array<int, 3> _ktoWygralPojedynek;
	std::array<int, 3> _ktoWygralGre;
	Gracz & _gracz1;
	Gracz & _gracz2;

	const std::array<std::array<Wynik, 3>, 3> _macierzWynikow;

public:
	Gra(Gracz & gracz1, Gracz & gracz2) : _gracz1(gracz1), _gracz2(gracz2), _macierzWynikow{ Remis, Wygral_Drugi, Wygral_Pierwszy,
		Wygral_Pierwszy, Remis, Wygral_Drugi ,
		Wygral_Drugi, Wygral_Pierwszy, Remis } {
		_ktoWygralGre[0] = _ktoWygralGre[1] = _ktoWygralGre[2] = 0;
		zeruj();
	}
	void graj() {

		Ruch staryRuch1 = Papier;
		Ruch staryRuch2 = Papier;
		for (int pojedynek = 0; pojedynek < 10; pojedynek++) {
			for (int i = 0; i < 10000; i++) {
				Ruch ruch1 = _gracz1.ruch(staryRuch2);
				Ruch ruch2 = _gracz2.ruch(staryRuch1);
				_ktoWygralPojedynek[ktoWygral(ruch1, ruch2)]++;
				staryRuch1 = ruch1;
				staryRuch2 = ruch2;
			}
			_ktoWygralGre[pokazWynikiPojedynku()] += abs(_ktoWygralPojedynek[Wygral_Drugi] - _ktoWygralPojedynek[Wygral_Pierwszy]);
			zeruj();
		}
		pokazWynikiGry();
	}
	void zeruj() {
		_ktoWygralPojedynek[0] = _ktoWygralPojedynek[1] = _ktoWygralPojedynek[2] = 0;
		_gracz1.reset();
		_gracz2.reset();
	}

	Wynik ktoWygral(Ruch ruchGracza1, Ruch ruchGracza2)const {


		return _macierzWynikow[ruchGracza1][ruchGracza2];
	}
	Wynik pokazWynikiPojedynku()const {
		for (int i = 0; i < _ktoWygralPojedynek.size(); ++i) {
			std::cout << _ktoWygralPojedynek[i] << " ";
		}

		if (_ktoWygralPojedynek[Wygral_Pierwszy] == _ktoWygralPojedynek[Wygral_Drugi]) {
			std::cout << "Remis!\n";
			return Wynik::Remis;
		}
		else {
			if (_ktoWygralPojedynek[Wygral_Pierwszy] > _ktoWygralPojedynek[Wygral_Drugi]) {
				std::cout << "Pojedynek wygral gracz: "; _gracz1.przedstawSie(); std::cout << std::endl;
				std::cout << "Zdobyl " << _ktoWygralPojedynek[Wygral_Pierwszy] - _ktoWygralPojedynek[Wygral_Drugi] << " punktow\n";
				return Wynik::Wygral_Pierwszy;
			}
			else {
				std::cout << "Pojedynek wygral gracz: "; _gracz2.przedstawSie(); std::cout << std::endl;
				std::cout << "Zdobyl " << _ktoWygralPojedynek[Wygral_Drugi] - _ktoWygralPojedynek[Wygral_Pierwszy] << " punktow\n";
				return Wynik::Wygral_Drugi;
			}
		}
	}
	void pokazWynikiGry()const {
		std::cout << std::endl << std::endl << std::endl;
		for (int i = 0; i < _ktoWygralGre.size(); ++i) {
			std::cout << _ktoWygralGre[i] << " ";
		}

		if (_ktoWygralGre[Wygral_Pierwszy] == _ktoWygralGre[Wygral_Drugi]) {
			std::cout << "Remis!\n";
		}
		else {
			if (_ktoWygralGre[Wygral_Pierwszy] > _ktoWygralGre[Wygral_Drugi]) {
				std::cout << "Gre wygral gracz: "; _gracz1.przedstawSie(); std::cout << std::endl;
				std::cout << "Zdobyl " << _ktoWygralGre[Wygral_Pierwszy] - _ktoWygralGre[Wygral_Drugi] << " punktow\n";
			}
			else {
				std::cout << "Gre wygral gracz: "; _gracz2.przedstawSie(); std::cout << std::endl;
				std::cout << "Zdobyl " << _ktoWygralGre[Wygral_Drugi] - _ktoWygralGre[Wygral_Pierwszy] << " punktow\n";
			}
		}
	}
};


class Gracz1 : public Gracz {
	std::random_device _rd;

	std::mt19937 _gen;

	std::uniform_int_distribution<> _dis;

public:
	Gracz1() : _gen(_rd()), _dis(0, 2) {

	}
	virtual Ruch ruch(Ruch poprzedniRuchPrzeciwnika) {
		return Ruch::Kamien;
	}
	void przedstawSie() {
		std::cout << "Szymon Palka";
	}
	void reset() {

	}
};

class Gracz2 : public Gracz {
	int _licznik = 0;
	int _przypadek = rand() % 5;
public:
	Gracz2() {
		_licznik;
		_przypadek;
	}

	virtual Ruch ruch(Ruch poprzedniRuchPrzeciwnika) {
		// Dziaa
		switch (_przypadek) {
		case 0: {if (_licznik == 0) {
			_licznik = 2;
			return Ruch::Papier;
			//return coto(0, _licznik);
		}if (_licznik == 2) {
			_licznik--;
			return Ruch::Papier;
			//return coto(0, _licznik);
		}if (_licznik == 1) {
			//return coto(1, _licznik);
			_licznik--;
			_przypadek = rand() % 5;
			return Ruch::Kamien;
		}}

		case 1: {if (_licznik == 0) {
			_licznik = 2;
			return Ruch::Nozyce;
			//return coto(1, _licznik);
		}if (_licznik == 2) {
			_licznik--;
			return Ruch::Nozyce;
			//return coto(1, _licznik);
		}if (_licznik == 1) {
			_licznik--;
			_przypadek = rand() % 5;
			return Ruch::Papier;
			//return coto(2, _licznik);
		}}
		case 2: {if (_licznik == 0) {
			_licznik = 2;
			return Ruch::Kamien;
			//return coto(2, _licznik);
		}if (_licznik == 2) {
			_licznik--;
			return Ruch::Papier;
			//return coto(2, _licznik);
		}if (_licznik == 1) {
			_licznik--;
			_przypadek = rand() % 5;
			return Ruch::Nozyce;
		}}
				//return coto(0, _licznik);}}
		case 3: {if (_licznik == 0) {
			_licznik = 2;
			return Ruch::Papier;
			//return coto(2, _licznik);
		}if (_licznik == 2) {
			_licznik--;
			return Ruch::Nozyce;
			//return coto(2, _licznik);
		}if (_licznik == 1) {
			_licznik--;
			_przypadek = rand() % 5;
			return Ruch::Kamien;
		}}
				//return coto(3, _licznik);}}
				// nowy schemat
		case 4: {if (_licznik == 0) {
			_licznik = 2;
			return Ruch::Nozyce;
			//return coto(0, _licznik);
		}if (_licznik == 2) {
			_licznik--;
			return Ruch::Kamien;
			//return coto(1, _licznik);
		}if (_licznik == 1) {
			//return coto(2, _licznik);
			_licznik--;
			_przypadek = rand() % 5;
			return Ruch::Papier;
		}}
		case 5: {if (_licznik == 0) {
			_licznik = 2;
			return Ruch::Papier;
			//return coto(1, _licznik);
		}if (_licznik == 2) {
			_licznik--;
			return Ruch::Nozyce;
			//return coto(2, _licznik);
		}if (_licznik == 1) {
			_licznik--;
			_przypadek = rand() % 5;
			return Ruch::Kamien;
			//return coto(3, _licznik);
		}}

		}
	}

	void reset() {

	}
	virtual void przedstawSie() {
		std::cout << "Bartlomiej Stachura";
	}
};

int main() {

	Gracz1 gracz1;
	Gracz2 gracz2;
	Gra gra(gracz1, gracz2);
	gra.graj();
	return 0;
}
