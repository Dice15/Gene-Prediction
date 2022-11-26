#pragma once

#include "Utility.h"
#include <string>
using namespace std;


class Sequence_Generator
{
public:
	typedef int int_s;
	typedef long long int_l;


private:
	string _Dna_Nucleobases = "ATGC";
	string _Rna_Nucleobases = "AUGC";


public:
	string Make_Dna(int_s _size) {   // dna ���� (A, T, G, C�� ������ ũ�Ⱑ size�� ���ڿ� return)
		string _dna(_size, ' ');
		while (_size) _dna[--_size] = _Dna_Nucleobases[util::Random_Generate<int_s>(0, 3)];
		return _dna;
	}

	string Make_Rna(int_s _size) {   // rna ���� (A, U, G, C�� ������ ũ�Ⱑ size�� ���ڿ� return)
		string _rna(_size, ' ');
		while (_size) _rna[--_size] = _Rna_Nucleobases[util::Random_Generate<int_s>(0, 3)];
		return _rna;
	}
};




/*
class CodonTable
{
private:
	string _Rna_Nucleobases = "UCAG";

public:
	string get(int _first, int _second, int _third) { return to_string(_Rna_Nucleobases[_first]) + _Rna_Nucleobases[_second] + _Rna_Nucleobases[_third]; }
};*/