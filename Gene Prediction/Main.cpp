
#include "Utility.h"
#include "ExonChaining.h"

#include <iostream>
#include <vector>
using namespace std;


int main()
{
	int sequence_length = 19;
	vector<ExonChaining::CandidateExon> example_candidate_exon = {
		ExonChaining::CandidateExon(2, 3, 3),
		ExonChaining::CandidateExon(9, 10, 1),
		ExonChaining::CandidateExon(13, 14, 0),
		ExonChaining::CandidateExon(16, 18, 4),
		ExonChaining::CandidateExon(1, 5, 5),
		ExonChaining::CandidateExon(7, 17, 12),
		ExonChaining::CandidateExon(4, 8, 6),
		ExonChaining::CandidateExon(11, 15, 7),
		ExonChaining::CandidateExon(6, 12, 10),
	};


	//ExonChaining exon_chaining(sequence_length, example_candidate_exon);
	ExonChaining exon_chaining(sequence_length);
	auto result = exon_chaining.Get_Gene();


	cout << "exon set ==============" << "\n";
	int exon_num = 0;
	for (auto& exon : exon_chaining.Get_Candidate_Exon_Set())
		cout << "exon" << util::Print_Format<int>(++exon_num, 3) << " (" << util::Print_Format<int>(exon._Start_Position, 3, util::Right) << ", " << util::Print_Format<int>(exon._End_Position, 3, util::Right) << ", " << util::Print_Format<int>(exon._Weight, 3, util::Right) << ")\n";
	cout << "=======================" << "\n\n";


	if (result.first.size() >= 0)
	{
		auto gene_set = result.first;
		auto dp_table = result.second;

		cout << "max score: " << dp_table[gene_set[0].back()._End_Position] << "\n\n";

		cout << "dp table --------------------------------------------------------------------------------------------" << "\n\n";
		cout << util::String_Format("index", 5) << ": ";
		for (int i = 0; i < sequence_length; i++) cout << util::Print_Format<int>(i, 4) << ' '; cout << '\n';
		cout << util::String_Format("value", 5) << ": ";
		for (int i = 0; i < sequence_length; i++) cout << util::Print_Format<int>(dp_table[i], 4) << ' '; cout << '\n';
		cout << "-----------------------------------------------------------------------------------------------------" << "\n\n";


		int gene_num = 0;
		for (auto& gene : gene_set) {
			cout << "gene" << ++gene_num << ": ";
			for (auto& exon : gene) cout << "(" << exon._Start_Position << ", " << exon._End_Position << ", " << exon._Weight << ") "; cout << "\n\n";
		}
	}

	return 0;
}
