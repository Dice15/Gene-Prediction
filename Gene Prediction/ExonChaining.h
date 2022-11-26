#pragma once

#include "Biological.h"
#include "Utility.h"

#include <iostream>
#include <functional>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;


class ExonChaining
{
public:
	typedef long long int_l;

	struct CandidateExon {
		int _Start_Position, _End_Position; int_l _Weight;
		CandidateExon() :_Start_Position(0), _End_Position(0), _Weight(0) {}
		CandidateExon(int _start_pos, int _end_pos, int_l _weight) :_Start_Position(_start_pos), _End_Position(_end_pos), _Weight(_weight) {}
		bool operator < (CandidateExon& _other) { return _Start_Position < _other._Start_Position ? true : _Start_Position == _other._Start_Position ? _End_Position < _other._End_Position : false; }
	};


private:
	int _Sequence_Length, _Candidate_Exon_Number;
	string _Rna_Sequence;
	vector<CandidateExon> _Candidate_Exon_Set;


public:
	ExonChaining(int _sequence_length) :ExonChaining(_sequence_length, vector<CandidateExon>(util::Random_Generate<int>(_sequence_length / 3, _sequence_length - 1))) { Contruct_Random_Candidate_Exon_Set(); }
	ExonChaining(int _sequence_length, vector<CandidateExon> _coding_set) :_Sequence_Length(_sequence_length), _Candidate_Exon_Number(_coding_set.size()), _Rna_Sequence(Sequence_Generator().Make_Rna(_sequence_length)), _Candidate_Exon_Set(_coding_set) {}
	~ExonChaining() { _Rna_Sequence.clear(); _Candidate_Exon_Set.clear(); }


private:
	void Contruct_Random_Candidate_Exon_Set()	// contruct coding set
	{
		vector<bool> _check_duplication(_Sequence_Length, false);

		for (int _exon_count = 0; _exon_count < _Candidate_Exon_Number; _exon_count++)
		{
			int _exon_start_pos = util::Random_Generate<int>(0, _Sequence_Length - 2);
			while (_check_duplication[_exon_start_pos]) _exon_start_pos = util::Random_Generate<int>(0, _Sequence_Length - 2);
			_check_duplication[_exon_start_pos] = true;
			_Candidate_Exon_Set[_exon_count] = CandidateExon(_exon_start_pos, _exon_start_pos + util::Random_Generate<int>(1, _Sequence_Length - _exon_start_pos - 1), util::Random_Generate<int_l>(0, _Sequence_Length));
		}
	}


public:
	pair<vector<vector<CandidateExon>>, vector<int_l>> Get_Gene()	// exon chaining with dynamic
	{
		sort(_Candidate_Exon_Set.begin(), _Candidate_Exon_Set.end());


		// dynamic for exon chaining
		int_l _max_score_gene = 0;  vector<int_l> _dp_table(_Sequence_Length, 0);
		
		int _pos = 0;
		for (auto& _exon : _Candidate_Exon_Set) {
			while (_pos < _exon._Start_Position) { _pos++; _dp_table[_pos] = max(_dp_table[_pos], _dp_table[_pos - 1]); }
			_dp_table[_exon._End_Position] = max(_dp_table[_exon._End_Position], _dp_table[_exon._Start_Position] + _exon._Weight);
			_max_score_gene = max(_max_score_gene, _dp_table[_exon._End_Position]);
		}


		// backtracking for find all genes
		vector<vector<CandidateExon>> _gene_set; vector<CandidateExon> _gene;

		function<void(int)> Backtracking = [&](int _curr_pos) {
			if (_dp_table[_curr_pos] == 0) { _gene_set.push_back(_gene); reverse(_gene_set.back().begin(), _gene_set.back().end()); return; }

			for (auto& _exon : _Candidate_Exon_Set) {
				if (_curr_pos == _exon._End_Position && _dp_table[_exon._Start_Position] == _dp_table[_curr_pos] - _exon._Weight) {
					_gene.push_back(_exon);
					Backtracking(_exon._Start_Position);
					_gene.pop_back();
				}
			}
			if (_dp_table[_curr_pos] == _dp_table[_curr_pos - 1]) Backtracking(_curr_pos - 1);
		};

		for (auto& _exon : _Candidate_Exon_Set) {
			if (_dp_table[_exon._End_Position] == _max_score_gene && _dp_table[_exon._Start_Position] == _max_score_gene - _exon._Weight) {
				_gene.push_back(_exon);
				Backtracking(_exon._Start_Position);
				_gene.pop_back();
			}
		}

		return { _gene_set,_dp_table };
	}


	vector<CandidateExon> Get_Candidate_Exon_Set() { return _Candidate_Exon_Set; }
};