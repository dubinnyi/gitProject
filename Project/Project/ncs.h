#pragma once
#ifndef NCS_H_INCLUDED
#define NCS_H_INCLUDED
#include<string>
#include<vector>
#include<map>
#include<set>
#include<fstream>
#include<sstream>
#include<iostream>
#include<iomanip>
#include<regex>
#include<tuple>
#include<time.h> 



//#include<tr1>
using namespace std;

class labeltype {
public:
	//string name;
	//int  isotopes;
	//bool HN, CA, CO;
	char name; 
	bool label_HN, label_CA, label_CO;
	// 
	labeltype(char lname = 'X', bool l_HN =0, bool l_CA=0, bool l_CO=0) {
		name = lname;
		label_HN = l_HN;
		label_CA = l_CA;
		label_CO = l_CO;
	}

	bool operator<(const labeltype & t2);

};

//labeltype typeT("T", 1, 1, 0);

bool operator<(const labeltype& t1, const labeltype& t2);
bool operator==(const labeltype& t1, const string& s2);
bool operator==(const string& s1, const labeltype& t2);




class spectrum {
public:
	string name;
	spectrum(string sname);
	int has_signal(labeltype label_type_1, labeltype label_type_2);
};

typedef string pattern_type;

class NCS {
public:
	const vector <char> NITRO_TYPES = { 'N', 'D', 'S', 'T' };
	string name;
	vector<spectrum>spec_list;
	vector<labeltype> label_types;
	bool deuterated;
	//map<pattern_type, labeltype> label_dict
	map<char, labeltype> label_dict;
	vector <char> letters;
	//vector <> spectra_numbers; 
	map<labeltype, int> label_power;
	map <labeltype, map <labeltype, string>> codes_dict;
	vector <vector <int>> vectors;
	//map <labeltype, string> subdict;
	
	//name, spectra_list, label_types, deuterated = False)
	//NCS(string name_ncs, vector<spectrum>spectra_list_ncs, vector<labeltype> label_types_ncs, bool deuterated_ncs = false);
	NCS(string name_ncs = "", vector<spectrum>spectra_list_ncs = {}, vector<labeltype> label_types_ncs = {}, bool deuterated_ncs = 0);
	void make_coding_table(void); 
	NCS& operator=(NCS& other);
	//NCS& operator=(const NCS& other);
	string calc_code(const string& pattern_1, const string& pattern_2);
	bool check_power(string new_pattern,int min_depth);
};



//bool operator==(const  Scheme& t1, const  Scheme& t2); 






/**
class Product {
public:
	all_blocks;
	product_list;

	Product(all_blocks, product_list);



};**/


//for scheme (patterns) 
bool pattern_bigger(string pattern1, string  pattern2);
string simplify_pattern(string pattern);
map <string, int>  simplify_list_of_patterns(vector<string> list_of_patterns); 
tuple<int, int > count_type_in_list_of_simplified(map <string, int> simplified, int index_of_type); 
int index_of_type(labeltype label_type);
tuple<int, int > count_type_in_list_of_patterns(vector<string>  patterns,labeltype label_type);


#endif  // NCS_H_INCLUDED

//def read_blocks(block_file, logger = None);
//void read_blocks(string block_file,  logger, string *result,map<  , > blocks, string *ncs_name ,bool *deuterated);
