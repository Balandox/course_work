#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <climits>
#include <algorithm>
#include <fstream>
#include <sstream>
#include "AssignmentP.h"

void AssignmentP::load(const std::string fname) {
	int tmp_num = 0, count = 0;
	std::vector<int> tmp_vec;
	std::string tmp_str;
	
	std::fstream fin(fname);
	if (!fin)
		throw std::invalid_argument("Can not open file!");  // invalid arg throw
	fin >> tmp_str;
	std::stringstream(tmp_str) >> this->size; 
	
	for (fin >> tmp_str; !fin.eof(); fin >> tmp_str) {
		std::stringstream(tmp_str) >> tmp_num;
		count++;
		tmp_vec.push_back(tmp_num);
		if (count == this->size) {
			this->Matrix.push_back(tmp_vec);
			tmp_vec.clear(); tmp_vec.resize(0);
			count = 0;
		}
	}
}

void AssignmentP::InputValidation() {
	for (const auto& it : this->Matrix)
		if (std::count(it.begin(), it.end(), -1) == this->size)
			throw std::invalid_argument("Incorrect file input! Rows of Matrix can not consist only -1.");
}


void AssignmentP::save(const std::string fname) {
	
	for (int i = 0; i < this->min_comb.size(); i++)
		this->track.insert(std::make_pair(i, this->min_comb[i])); // для BruteForce, восстанавливаем путь по min_comb
	std::ofstream fout(fname);
	if (!fout)
		throw std::invalid_argument("Can not open file!");


	fout << "Total summ = " << this->min_summ << std::endl << std::endl;

	//auto it = this->Matrix.begin();  
	auto it_map = this->track.begin();
	int idx = 0;

	for (const auto& it : this->Matrix) {  
		for (int i = 0; i < it.size(); i++) {
			if (i == it_map->second) 
				fout << std::setw(7) << "W";
			else
				fout << std::setw(7) << it.at(i);
		}
		fout << std::endl;
		++it_map;
	}
	it_map = this->track.begin();

	fout << "\nTrack:\n";
	for (; it_map != this->track.end(); ++it_map)
		fout << "(" << it_map->first + 1 << ";" << it_map->second + 1 << ")" <<"  W = "<< this->Matrix[it_map->first][it_map->second] << std::endl;
}

bool check_used_idx(int idx, const AssignmentP& pr, const std::vector<int>& itstr) { // 
	std::vector<int>::const_iterator it = pr.used_idx.begin();  
	it = std::find(begin(pr.used_idx), end(pr.used_idx), idx);		// метод для проверки уже использованных столбцов или наличие -1
	if (itstr.at(idx) == -1)
		return true;
	else if (it == pr.used_idx.end()) // если эта позиция не занята то возвращаем фолс
		return false;
	return true;
}

bool check_used_idx(int idx, std::vector<int>& vec, int size) { // для BruteForce
	std::vector<int>::const_iterator it = vec.begin();
	for (int i = 0; i < size; i++)
		if (vec[i] == idx)
			return true;
	return false;
}

void replace(AssignmentP& matr) {
	auto itmap = matr.max_elem.begin();
	while (itmap != matr.max_elem.end()) {
		matr.Matrix[itmap->first[0]][itmap->first[1]] = itmap->second;
		++itmap;
	}
}

void AssignmentP::GreedyAlg() {
	std::vector<int>::iterator it_min; // указывает на минимальное число в строке матрицы
	int min_idx = 0, matrix_str = 0;
	std::vector<int> tmp_idx;
	bool flag_int_max = false;
	this->min_summ = 0;

	for(auto& it: this->Matrix) {
		it_min = std::min_element(it.begin(), it.end()); // ищем минимальный элемент в строке
		min_idx = std::distance(it.begin(), it_min);  // получаем индекс этого минимального элемента в строке
		
		while (check_used_idx(min_idx, *this, it)) {
			tmp_idx.push_back(matrix_str); tmp_idx.push_back(min_idx); // запоминаем индекс и число, чтобы потом его вывести
			this->max_elem.insert(std::make_pair(tmp_idx, it.at(min_idx)));
			it.at(min_idx) = INT_MAX; // помечаем индекс как недоступный
			it_min = std::min_element(it.begin(), it.end());		// ищем новый минимальный элемент
			if (*it_min == INT_MAX) {
				flag_int_max = true;
				break;
			}
			min_idx = std::distance(it.begin(), it_min);
			tmp_idx.clear();
		}

		if (!flag_int_max) {
			this->used_idx.push_back(min_idx); // помечаем наш индекс как использованный
			this->min_summ += it.at(min_idx);		// добавляем стоимость назначения в итоговую сумму
			this->track.insert(std::make_pair(matrix_str, min_idx)); // добавляем использованный индекс в наш путь
		}
		if (tmp_idx.size() != 0)
			tmp_idx.clear();
		matrix_str++;
		flag_int_max = false;
	}
	replace(*this);
}


void unavailable_works(AssignmentP& matr) {
	std::vector<int> tmp;
	for (int i = 0; i < matr.size; i++) {
		for (int j = 0; j < matr.size; j++) {
			if (matr.Matrix[i][j] != -1)
				tmp.push_back(j);
		}
		matr.work.push_back(tmp);
		tmp.clear();
	}
}

void AssignmentP::BR() {
	int work_idx = 0;
	this->comb.resize(this->size, -1);
	unavailable_works(*this);
	BruteForce(0, this->comb, work_idx);
}

void AssignmentP::BruteForce(int idx, std::vector<int>& bruteforce, int work_idx) {
	if (work_idx == this->size) {   // idx - индекс в bruteforce, work_idx - индекс строки в массиве work
		for (int i = 0; i < bruteforce.size(); i++)
			this->tmp_summ += this->Matrix[i][bruteforce[i]];
		this->min_summ = std::min(this->min_summ, this->tmp_summ);
		if(this->min_summ == this->tmp_summ)
			this->min_comb = bruteforce;  //запоминаем вектор с минимальной стоимостью
		this->tmp_summ = 0; 
	}
	else {
		for (int j = 0; j < this->work[work_idx].size(); j++) {
			this->used_idx = bruteforce;					
			bruteforce[idx] = this->work[work_idx][j];		// записываем доступный нам индекс в вектор перебора
			if (!check_used_idx(this->work[work_idx][j], this->used_idx, idx)) {  // проверяем нет ли уже этого индекса в использованных
				this->used_idx.push_back(this->work[work_idx][j]);			// добавляем в использованные
				BruteForce(idx + 1, bruteforce, work_idx + 1);   // переходим на следующий шаг рекурсии с новой строкой и новым индексом в векторе перебора
			}
		}
	}
}


