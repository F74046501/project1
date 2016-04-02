using namespace std;

class Sudoku{
	public:
		void giveQuestion();
		void readIn();
		void solve();
		void changeNum(int a ,int b);
		void changeRow(int a ,int b);
		void changeCol(int a ,int b);
		void rotate(int n);
		void flip(int n);
		void transform();
		///
		void setsdk(int set[9][9]);
		void getsdk();
		void printOut();

	private:
		int map[9][9];
};
