#include <stdafx.hpp>
#include <fstream>
#include <random>
#include <cmdline.h>

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

	cmdline::parser p;
	p.add<int>("number", 'n', "mesh size", false, 5);
	p.add("verbose", 'v', "display results");
	p.add("help", 0, "print help");

	if (!p.parse(argc, argv)||p.exist("help")){
    std::cout<<p.error_full()<<p.usage();
    return 0;
  }

	int nRow = p.get<int>("number");
	int nCol = nRow;
	bool verbose = p.exist("verbose");

	// set up.	
	std::vector<int> input;
	srand(time(0));
	for (size_t i = 0; i < nRow*nCol; i++) {
		input.push_back(i);
	}
	random_shuffle(input.begin(), input.end());

	if (verbose) {
		cout << "[org]" << endl;
		printVec(input, nRow);
	}

	// sorting
	int cnt = 1;
	while (true) {
		if (verbose) {
			cout << "[Itr : " << cnt <<  "]" << endl;
		}

		// randomize row.
		for (size_t i = 0; i < nRow; i++) {
			auto s = input.begin() + i*nCol;
			auto e = s + nCol;
			random_shuffle(s, e);
		}
		if (verbose) {
			cout << "[r step]" << endl;
			printVec(input, nRow);
		}

		// sort column.
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
		if (verbose) {
			cout << "[c sort]" << endl;
			printVec(input, nRow);
		}
	
		// shear.
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
		if (verbose){
			cout << "[shear step]" << endl;
			printVec(input, nRow);
		}

		if (isSorted(input, nRow, nCol)) break;

		// sort column.
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
		if (verbose){
			cout << "[c sort]" << endl;
			printVec(input, nRow);
		}

		cnt++;
	}		

	cout << "## row  col  itrs." << endl;
	cout << nRow << " " << nCol << " " << cnt << endl;

	return 0;
}
