#ifndef _ASSIGNMENTP_H_
#define _ASSIGNMENTP_H_
#include <string>
#include <vector>
#include <map>
#include <iomanip>
#include <algorithm>


class AssignmentP {
private:
	int size;
	int tmp_summ;
	int min_summ;
	std::map<int, int> track;		// сохраняем путь по которому проходим
	std::map<std::vector<int>, int> max_elem; // для запоминания значений, на использованных позиция и -1
	std::vector<std::vector<int>> work; // двумерный массив работ, которые доступны(исключены -1)
	std::vector<int> min_comb;
	std::vector<int> comb; // вектор для полного перебора(заполняем его индексами в строках матр)
	std::vector<std::vector<int>> Matrix;  // матрица работник-работа
	std::vector<int> used_idx;  // помечаем использованные индексы
public:
	AssignmentP() : size(0), tmp_summ(0), min_summ(INT_MAX) {}

	void load(const std::string fname);
	
	void GreedyAlg();

	void InputValidation();

	void BruteForce(int idx, std::vector<int>& bruteforce, int work_idx);

	void save(const std::string fname);

	friend bool check_used_idx(int idx, const AssignmentP& pr, const std::vector<int>& itstr); // для проверки использованных индексов в greedy
	friend bool check_used_idx(int idx, std::vector<int>& vec, int size); // для проверки использованных индексов в BruteForce
	friend void replace(AssignmentP& pr);
	friend void unavailable_works(AssignmentP& pr);  // выписывает все доступные работы в массив work
	void BR();
};

#endif 

