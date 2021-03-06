#include<string>
#include <iostream>
#include <iomanip>
#include<vector>
#include<map>
#include<set>
#include <algorithm>

#include "ncs.h"

using namespace std; 
 
spectrum::spectrum(string sname) { 
	name = sname; 
}

bool labeltype::operator<(const labeltype& t2) {
	return (this->name < t2.name);
}

bool operator<(const labeltype& t1, const labeltype& t2) {
	return (t1.name < t2.name);
}




bool operator<(const Scheme& t1, const Scheme& t2) {
	return (t1.simplified < t2.simplified);
}

bool Scheme::operator<(const Scheme& t2) {
	return (this->simplified < t2.simplified);
}



bool operator==(const labeltype& t1, const string& s2) {
	return (t1.name == s2);
}

bool operator==(const Scheme& t1, const Scheme& s2) {
	return (t1.simplified == s2.simplified);
}




bool operator==(const string& s1, const labeltype& t2) {
	return (s1 == t2.name);
}

bool operator==(const labeltype& t1, const labeltype& t2) { //*
	return (t1.name == t2.name);
}


int spectrum::has_signal(labeltype label_type_1, labeltype label_type_2) {
		vector <bool> vec1, vec2;
		/**
		vec1.push_back(label_type_1.isotopes / 100 % 10);
		vec1.push_back(label_type_1.isotopes / 10 % 10);
		vec1.push_back(label_type_1.isotopes % 10);
		vec1.push_back(label_type_2.isotopes / 100 % 10);
		vec1.push_back(label_type_2.isotopes / 10 % 10);
		vec1.push_back(label_type_2.isotopes % 10);**/

		//vector<bool>  atom_list = vec1;

		if (name == "HSQC") {
			return int(label_type_2.label_HN);
		}
		else if (name == "HNCO") {
			return int(label_type_2.label_HN &&  label_type_1.label_CO);
		}

		else if (name == "HNCA") {
			return int(label_type_2.label_HN && (label_type_1.label_CA || label_type_2.label_CA));
		}

		else if (name == "HNCOCA") {
			return int(label_type_2.label_HN && label_type_1.label_CO && label_type_1.label_CA);
		}

		else if (name == "COfHNCA") {
			return int(label_type_2.label_HN  && label_type_1.label_CA &&  !(label_type_1.label_CO));
		}

		else if (name == "DQHNCA") {
			return int(label_type_2.label_HN && label_type_1.label_CA &&    label_type_2.label_CA);
		}

		else if (name == "HNCACO") {
			return int(label_type_2.label_HN &&  label_type_2.label_CA && label_type_2.label_CO);
		}

		else if (name == "HNCAfCO") 
			return int(label_type_2.label_HN && !(label_type_2.label_CA) && label_type_2.label_CO);
	}


class constants {
	constants() {
		spectrum HSQC("HSQC");
		spectrum HNCO("HNCO");
		spectrum HNCA("HNCA");
		spectrum HNCOCA("HNCOCA");
		spectrum DQHNCA("DQHNCA");
		spectrum COfHNCA("COfHNCA");
		spectrum HNCACO("HNCACO");
		spectrum HNCAfCO("HNCAfCO");
		const vector <spectrum> basic_spectra = { HSQC, HNCO, HNCA, HNCOCA, DQHNCA, COfHNCA, HNCACO, HNCAfCO };
		/**labeltype typeX("X", 000);
		labeltype typeN("N", 100);
		labeltype typeC("C", 001);
		labeltype typeD("D", 111);
		labeltype typeA("A", 010);
		labeltype typeT("T", 110);
		labeltype typeS("S", 101);
		labeltype typeF("F", 011);
		**/
		labeltype typeX('X', 0, 0, 0);
		labeltype typeN('N', 1, 0, 0);
		labeltype typeC('C', 0, 0, 1);
		labeltype typeD('D', 1,1 , 1);
		labeltype typeA('A', 0, 1, 0);
		labeltype typeT('T', 1, 1, 0);
		labeltype typeS('S', 1, 0, 1);
		labeltype typeF('F', 0, 1, 1);

		//const vector <labeltype> BASIC_TYPES = { typeX, typeN, typeC, typeD, typeA, typeT, typeS, typeF };
		const map <labeltype, int>BASIC_TYPES = { {typeX, 0}, {typeN,1}, {typeC, 2}, {typeD,3}, {typeA, 4}, {typeT,5}, {typeS, 6}, {typeF,7} };

		//const vector  <string> TYPES = {"X", "N", "C", "D", "A", "T", "S", "F"};


	}
};
	NCS::NCS(string name_ncs , vector<spectrum>spectra_list_ncs , vector<labeltype> label_types_ncs , bool deuterated_ncs ) {
		name = name_ncs;
		spec_list = spectra_list_ncs;
		label_types = label_types_ncs;
		deuterated = deuterated_ncs;
		for (labeltype l : label_types) {
			label_dict[l.name] = l;
		}
		letters = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h','i', 'j' };
		make_coding_table(); 
	}

	void	NCS::make_coding_table() {
		vector <vector <string>> codes_table;
		for (int j = 0; j < label_types.size(); j++) {
			codes_table.push_back(vector<string>());
			for (int i = 0; i < label_types.size(); i++) {
				//codes_table[j].push_back({ "0" });
				//codes_table[j].push_back("0");
				codes_table[j].push_back("0");
			}
		}
		//vector<int> vec;
		//vector<string> result;
		set<string> s;
		int power;
		int code;
		//labeltype label_2, label_1;
		for (int i = 0; i < label_types.size(); i++) {
			labeltype label_2 = label_types[i];

			for (int j = 0; j < label_types.size(); j++) {
				labeltype label_1 = label_types[j];
				 vector<int> vec;
				for (spectrum spect : spec_list) {
					vec.push_back(spect.has_signal(label_1, label_2));
					
				}
				
				if (find(vectors.begin(), vectors.end(), vec) != vectors.end()) {
					code = distance(vectors.begin(), find(vectors.begin(), vectors.end(), vec));
				}
				else {
					code = vectors.size();
					vectors.push_back(vec);
				}
				if (code > 9) {
					codes_table[j][i] = letters[code - 10];
				}
				else {
					codes_table[j][i] = to_string(code);
				}
			}
		}
		for (int i = 0; i < label_types.size(); i++) {
			//result = {};
			vector<string> result; 
			for (vector <string> row : codes_table) {
				result.push_back(row[i]);
			}
			set <string> s(result.begin(), result.end());
			power = s.size();
			
			label_power[label_types[i]] = power;
			cout << "NCS POWER" << label_power[label_types[i]] << endl;

			if (power == 1 and find(NITRO_TYPES.begin(), NITRO_TYPES.end(), label_types[i]) != NITRO_TYPES.end()) {

				throw ("Error");
			}
		}
		//map <labeltype, string> subdict;
		//cout << "creating map" << endl; 
		for (int i = 0; i < label_types.size(); i++) {
			labeltype  label_1 = label_types[i];
			map <labeltype, string> subdict;
			for (int j = 0; j < label_types.size(); j++) {
				labeltype label_2 = label_types[j];
				subdict[label_2] = codes_table[i][j];
				//cout << " codes" << codes_table[i][j];
				//cout << label_2.name << "it's label" << endl; 
				//cout << "FROM SUBDICT " << subdict[label_2] << endl; 
			}
			
			codes_dict[label_1] = subdict;
		}

	}
	//????
NCS& NCS::operator=(NCS& other){
	if (this != &other) {  //?
		name = other.name;
		spec_list = other.spec_list;
		label_types = other.label_types;
		deuterated = other.deuterated;
		label_dict = other.label_dict;
		letters = other.letters; 
		label_power =other.label_power;
		 codes_dict=other.codes_dict;
		 vectors = other.vectors;
	}
	return *this;
}


/**
NCS& NCS::operator=(const NCS& other) {
	if (this != &other) {  //?
		name = other.name;
		spec_list = other.spec_list;
		label_types = other.label_types;
		deuterated = other.deuterated;
		label_dict = other.label_dict;
		letters = other.letters;
		label_power = other.label_power;
		codes_dict = other.codes_dict;
		vectors = other.vectors;
	}
	return *this;
}
**/


bool NCS::check_power(string new_pattern, int min_power) {
	int power = 1; 
	labeltype e; 
	//cout << "check power" << endl; 
	for (char label : new_pattern) {
		e = label_dict[label];
		
		//cout << e.name << endl;
		power = power * label_power[  e  ];  
		//cout << label << endl; 
		//cout << "label  " << label << " label_dict[to_string(label)]   " << e.name << endl; 
		//cout << "   label[power] is "  <<label_power[e] << endl;
		//power *= label_power[label_dict[label]];
	} 
	//cout <<  "return or ot " <<  (power >= min_power) << endl;
	return (power >= min_power); 



}

string NCS::calc_code(string pattern_1, string pattern_2) {
	string value = "";
	char s1, s2; 
	for (int i = 0; i < pattern_1.size(); i++) {
		s1 = pattern_1[i]; // change? 
		s2 = pattern_2[i];
		value.push_back(codes_dict[label_dict[s1]][label_dict[s2]][0]); //
	}
	return value; 
} //needs tests 

bool Scheme::check_codes() {
	set <string> codes; 
	string code; // n or not n 
	bool first = true; 
	for (string pattern_1 : patterns) {
		for (string pattern_2 : patterns) {
			code = ncs.calc_code(pattern_1, pattern_2);
			if (first) {
				first = false; 
				continue;
			}
			//else if (find(codes.begin(), codes.end(), code) != codes.end()) { //?=
			else if (codes.find(code) != codes.end()) {
				return false;
			}
			else {
				codes.insert(code);
			}
		}
	}
	return true;
}
/**
Scheme& Scheme::operator=(Scheme& other) {
	if (this != &other) {  //?
		name = other.name;
		 ncs = other.ncs;
		samples = other.samples;
		patterns = other.patterns;
		codes = other.codes;
		new_codes = other.new_codes;
		simplified = other.simplified;
		good = other.good;
	}
	return *this;
}**/

void Scheme::setscheme(string sname , NCS sncs , int  bsamples , vector <string>  bpatterns) {
	name = sname;
	patterns = bpatterns;
	samples = bsamples;
	//ncs = NCS(sncs.name, sncs.spec_list, sncs.label_types, sncs.deuterated);
	ncs = sncs;
	set <string> codes; //
	good = check_codes();
	map <string, int> simplified;//
	simplify();
	set <string> new_codes;

}


/**
Scheme& Scheme::operator=(  const Scheme& other) {
	if (this != &other) {  //?
		name = other.name;
		ncs = other.ncs;
		samples = other.samples;
		patterns = other.patterns;
		codes = other.codes;
		new_codes = other.new_codes;
		simplified = other.simplified;
		good = other.good;
	}
	return *this;
}**/





string simplify_pattern(string pattern) { // instead TYPES 
	string result = "";
	//cout << "start" << endl ; 
	const vector  <string> TYPES = { "X", "N", "C", "D", "A", "T", "S", "F" };
	vector <int> simple_form; 
	for (int i = 0; i < TYPES.size(); i++) {
		simple_form.push_back(0);
	}

	//cout << simple_form[2] << endl; 
	for (char label: pattern) {
		for (int i = 0; i < TYPES.size(); i++) {
			//cout << TYPES[i] << " Type " << label << " l" << endl; 
			if (TYPES[i][0] == label) {
				//cout << "we are here " << endl; 
				simple_form[i] = simple_form[i] + 1;
				//cout << simple_form[i] << endl;
				continue;
			}

		}
	}

	
	for ( int a : simple_form) {
		//b = <char>(a);
		//cout << " a " << a << "b " << b << endl; 
		result = result + to_string(a); 
		//result.push_back(char(a));
		//result.push_back(b);
	}
	//cout << result << endl; 

	return result;
}




string simplify_pattern2(string pattern) { // instead TYPES 
	string result = "";
	static map <  char, int> res; 
	static  vector  <char> TYPES = { 'X', 'N', 'C', 'D', 'A', 'T', 'S', 'F' };
	res = { {'X' , 0}, {'N',1}, {'C',2}, {'D',3}, {'A',4}, {'T',5}, {'S', 6}, {'F',7} }; 
	//static map < char, int > TYPES; 
	vector <int> simple_form;
	for (int i = 0; i < TYPES.size(); i++) {
		simple_form.push_back(0);
	}
	for (char label : pattern){
		simple_form[res[label]] = simple_form[res[label]] + 1;
		//cout << (res[label]) << endl ;
	}

	
	for ( int  a : simple_form) {
		result = result + to_string(a);
		//b = static_cast<char>(a);
		//result.push_back(char(a));
		//result.push_back(a);
	}
	return result;
}











void Scheme::simplify() {
	//map <string, int> simplified; //new
	//map <pattern_type, int> simplified = {};
	string simple_pattern;
	simplified = {};
	for (string pattern : patterns) {
		simple_pattern = simplify_pattern2(pattern);
		//if (( simplified.empty != true ) && (simplified.count(simple_pattern) > 0)) {
		if ((simplified.size()!=0) && (simplified.find(simple_pattern) != simplified.end())) {
			simplified[simple_pattern] = simplified[simple_pattern] + 1;
		}
		else {
			simplified[simple_pattern] = 1;
		}
	}

}

Scheme::Scheme(string sname, NCS sncs, int  bsamples, vector <string>  bpatterns) {
	name = sname;
	patterns = bpatterns;
	samples = bsamples;
	//ncs = NCS(sncs.name, sncs.spec_list, sncs.label_types, sncs.deuterated);
	ncs = sncs; 
	set <string> codes; //
	good = check_codes();
	//map <string, int> simplified;//new comment 
	simplify();
	set <string> new_codes;
	//+?
}
bool Scheme::check_patterns(vector <string> patterns) {
	if (patterns.size()==0) {
		return false; 
	}
	int sizep; 
	sizep = patterns[0].size();
	for (string pattern : patterns) {
		for (char label_type : pattern) {
			if (find(ncs.label_types.begin(), ncs.label_types.end(), to_string(label_type)) == ncs.label_types.end()) { //-/ 
				return false;
			}
		}
		if (pattern.size() != sizep) {
			return false;
		}
	}
	return true; 
}

void Scheme::sort() { //* 
	string temp_pattern;
	for (int i = 0; i < (patterns.size() - 1); i++) {
		for (int j = 0; j < (patterns.size() -i-1); j++) {
			if (pattern_bigger(patterns[i], patterns[i + j + 1])) {
				temp_pattern = patterns[i];
				patterns[i] = patterns[i + j + 1];
				patterns[i + j + 1] = temp_pattern;
			}
		}
	}
}

void Scheme::add_new_codes(string new_pattern) {
	for (string pattern : patterns) {
		codes.insert(ncs.calc_code(pattern, new_pattern));
		codes.insert(ncs.calc_code(new_pattern, pattern));
	}

	codes.insert(ncs.calc_code(new_pattern, new_pattern));

}

void Scheme::add_pattern(string new_pattern) {
	patterns.push_back(new_pattern);
	add_new_codes(new_pattern);
	simplify();
}

/**
bool Scheme::operator==(const Scheme& t2) {

	return ( (this->name == t2.name)    &&  (this->patterns == t2.patterns )  && ( this->samples == t2.samples  )  );
}

bool operator==(const  Scheme& t1, const  Scheme& t2) { //*
	return ((t1.name == t2.name)  &&  (t1.patterns==t2.patterns) && ( t1.samples == t2.samples )   );
}
**/
/**
bool Scheme::operator<(const Scheme& t2) {
	return (this->name < t2.name);
}**/



/**
bool pattern_bigger( string pattern1, string  pattern2) {
	char type1, type2;
	//const vector  <char> TYPES = { char("X"), char("N"), char("C", "D", "A", "T", "S", "F" };
	//constants consts(); 
	const vector  <string> TYPES = { "X", "N", "C", "D", "A", "T", "S", "F" };
	for (int i = 0; i < pattern1.size(); i++) {
		type1 = pattern1[i];
		type2 = pattern2[i];
		//!
		if (distance(TYPES.begin(), find(TYPES.begin(), TYPES.end(), to_string(type1))) > distance(TYPES.begin(), find(TYPES.begin(), TYPES.end(), to_string(type2)))) {
			return true; 
		}
		else if (distance(TYPES.begin(), find(TYPES.begin(), TYPES.end(), to_string(type1))) < distance(TYPES.begin(), find(TYPES.begin(), TYPES.end(), to_string(type2)))) {
			return false; 
		}
		else continue;
	}
	return true;
}
**/
bool pattern_bigger(string pattern1, string  pattern2) {
	char type1, type2;
	//const vector  <char> TYPES = { char("X"), char("N"), char("C", "D", "A", "T", "S", "F" };
	//constants consts(); 
	static map<char, int>  TYPES = { {'X',0}, {'N',1}, {'C',2}, {'D', 3}, {'A',4}, {'T',5}, {'S', 6}, {'F', 7} };
	for (int i = 0; i < pattern1.size(); i++) {
		type1 = pattern1[i];
		type2 = pattern2[i];
		//!
		if (TYPES[type1] > TYPES[type2]) {
			return true;
		}
		else if (TYPES[type1] < TYPES[type2]) {
			return false;
		}
		else continue;
	}
	return true;
}











bool Scheme::try_pattern(string  new_pattern) {
	if (good == false) {
		return false; 
	}
	set <string> new_codes;
	string code_1, code_2;
	if (find(patterns.begin(), patterns.end(), new_pattern) != patterns.end()) {
		return false;
	}
	for (string pattern : patterns) {

		code_1 = ncs.calc_code(pattern, new_pattern);
		code_2 =ncs.calc_code(new_pattern, pattern);
		//if ( (find(codes.begin(), codes.end(), code_1) != codes.end() )|| (find(codes.begin(), codes.end(), code_2) != codes.end()) || code_1 == code_2 || (find(new_codes.begin(), new_codes.end(), code_2) != new_codes.end())|| (find(new_codes.begin(), new_codes.end(), code_1) != new_codes.end())) {
		if ( codes.find(code_1)!=codes.end() || codes.find(code_2) != codes.end()   ||     (code_2==code_1) || new_codes.find(code_1) != new_codes.end() || new_codes.find(code_2) != new_codes.end()){
			
			return false; 
		}
		else {
				new_codes.insert(code_1);
				new_codes.insert(code_2);
		}

	}
	string self_code = ncs.calc_code(new_pattern, new_pattern);
	if (codes.find(self_code) != codes.end() || new_codes.find(self_code) != new_codes.end()) {
		return false;

	}
	else {
		new_codes.insert(self_code);
	}
	return true;
}

Scheme Scheme::direct_product(Scheme scheme) {
	vector <string>  new_patterns;

	for ( string pattern_1 : patterns){
		for (string  pattern_2 : scheme.patterns){
			new_patterns.push_back(pattern_1 + pattern_2);
		}
	}
	string new_name = name + "_X_" + scheme.name;
	samples = new_patterns[0].size(); // n or o 
	Scheme new_scheme = Scheme(new_name, ncs, samples, new_patterns);
		return new_scheme;
}


string Scheme::full_str() {
	string s = ""; 
	string all_p = "";

	for (string i : patterns) {
		all_p = all_p + i + "\n";


	}

	s ="[ELB samples = " + to_string(samples) + " patterns = " + to_string(patterns.size()) + "]\n"+ all_p;

	return s; 
}


























/**
class BlockFinder {
public:
int samples;
bool block_finder_mode;
NCS ncs;
int min_depth;
BlockFinder(int bsamples, NCS bncs, int bmin_depth, logger, elb_logger, bool bblock_finder_mode = 0) {
samples = bsamples;
block_finder_mode = bblock_finder_mode;
min_depth = bmin_depth;
ncs = bncs; //определить присваивание?
}
};**/
