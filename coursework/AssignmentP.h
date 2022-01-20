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
	std::map<int, int> track;		// ��������� ���� �� �������� ��������
	std::map<std::vector<int>, int> max_elem; // ��� ����������� ��������, �� �������������� ������� � -1
	std::vector<std::vector<int>> work; // ��������� ������ �����, ������� ��������(��������� -1)
	std::vector<int> min_comb;
	std::vector<int> comb; // ������ ��� ������� ��������(��������� ��� ��������� � ������� ����)
	std::vector<std::vector<int>> Matrix;  // ������� ��������-������
	std::vector<int> used_idx;  // �������� �������������� �������
public:
	AssignmentP() : size(0), tmp_summ(0), min_summ(INT_MAX) {}

	void load(const std::string fname);
	
	void GreedyAlg();

	void InputValidation();

	void BruteForce(int idx, std::vector<int>& bruteforce, int work_idx);

	void save(const std::string fname);

	friend bool check_used_idx(int idx, const AssignmentP& pr, const std::vector<int>& itstr); // ��� �������� �������������� �������� � greedy
	friend bool check_used_idx(int idx, std::vector<int>& vec, int size); // ��� �������� �������������� �������� � BruteForce
	friend void replace(AssignmentP& pr);
	friend void unavailable_works(AssignmentP& pr);  // ���������� ��� ��������� ������ � ������ work
	void BR();
};

#endif 

