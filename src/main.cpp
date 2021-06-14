#include <stdafx.hpp>
#include <fstream>
#include <random>

using namespace std;

void printVec(const std::vector<int>& trg, int nCol) {

	for (size_t i = 0; i < trg.size(); i++) {
		printf(" %2d", trg[i]);
		if (i%nCol == nCol-1) cout << endl;
	}
}

int getIdx(int id, int nCol) {

	return ((id)/(nCol)%2 == 0) ? id : id + nCol - (id)%nCol*2 - 1;
}

bool isSorted(const std::vector<int>& trg, int nRow, int nCol){

	for (size_t i = 0; i < trg.size()-1; i++) {
		int idx  = getIdx(i, nCol);
		int nidx = getIdx(i+1, nCol);

		if ( trg[idx] > trg[nidx] ) return false;
	}

	return true;
}

int main(int argc, char const *argv[]) {

	int nRow = 5;
	int nCol = 5;

	// set up.
	
	std::vector<int> input;
	if (argc > 1) {
		nRow = nCol = atoi(argv[1]);
	}
	srand(time(0));
	for (size_t i = 0; i < nRow*nCol; i++) {
		input.push_back(i);
	}
	random_shuffle(input.begin(), input.end());

	cout << "[org]" << endl;
	printVec(input, nRow);

	// sorting
	int cnt = 1;
	while (true) {
		cout << "[Itr : " << cnt <<  "]" << endl;

		// randomize row.
		cout << "[r step]" << endl;
		for (size_t i = 0; i < nRow; i++) {
			auto s = input.begin() + i*nCol;
			auto e = s + nCol;
			random_shuffle(s, e);
		}
		printVec(input, nRow);

		// sort column.
		cout << "[c sort]" << endl;
		for (size_t i = 0; i < nCol; i++) {
			vector<int> col;
			for (size_t r = 0; r < nRow; r++) {
				col.push_back(input[i+nCol*r]);
			}
			sort(col.begin(), col.end());
			for (size_t r = 0; r < nRow; r++) {
				input[i+nCol*r] = col[r];
			}
		}
		printVec(input, nRow);
	
		// shear.
		cout << "[shear step]" << endl;
		for (size_t i = 0; i < nRow; i++) {
			auto s = input.begin() + i*nCol;
			auto e = s + nCol;
			if (i%2 == 0) {
				sort(s, e);
			}
			else {
				sort(s, e, greater<int>());
			}
		}
		printVec(input, nRow);

		if (isSorted(input, nRow, nCol)) break;

		// sort column.
		cout << "[c sort]" << endl;
		for (size_t i = 0; i < nCol; i++) {
			vector<int> col;
			for (size_t r = 0; r < nRow; r++) {
				col.push_back(input[i+nCol*r]);
			}
			sort(col.begin(), col.end());
			for (size_t r = 0; r < nRow; r++) {
				input[i+nCol*r] = col[r];
			}
		}
		printVec(input, nRow);

		cnt++;
	}		

	cout << "Complete by " << cnt << " itrs." << endl;

	return 0;
}
