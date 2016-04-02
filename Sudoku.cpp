#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Sudoku.h"

void Sudoku::giveQuestion(){
	int question[81]={3,0,0,0,0,2,1,0,0,0,0,0,4,9,7,2,5,0,5,2,9,1,0,3,0,0,0,2,0,7,0,0,0,9,8,0,0,0,0,7,0,5,0,0,0,0,1,3,0,0,0,7,0,5,0,0,0,2,0,4,6,9,8,0,9,2,5,3,8,0,0,0,0,0,1,9,0,0,0,0,2};

	for(int i=0 ;i<81 ;i++){
		cout << question[i];
		if((i+9)%9 !=8 ) cout<<" ";
		else cout <<"\n";
	}

	return;
}

void Sudoku::readIn(){
    int sdk[9][9];
	for(int i=0 ;i<9 ;i++){
        for(int j=0 ;j<9 ;j++){
            cin>>map[i][j];
        }
    }
    return;
}
void Sudoku::solve(){
	bool possible[9][9][9];
	for(int x=0 ;x<9 ;x++){  //initialize the "possible" to bool
		for(int y=0 ;y<9 ;y++){
			if(map[x][y] != 0){
				for(int z=0 ;z<9 ;z++)
					possible[x][y][z] = false;  //all be false
				possible[x][y][map[x][y]-1] = true;  //one be true
			}
			else
				for(int z=0 ;z<9 ;z++)
					possible[x][y][z] = true;  //all be possible
		}
	}

	int hole = 2 ,pre_hole = 1;  //after initializing ,to solve it!

	while(pre_hole != hole && hole!= 0){  //not yet run out the ans ,keep tryimg
		pre_hole = hole;
		for(int row = 0 ;row<9 ;row++)
			for(int column = 0 ;column<9 ;column++){

				if(map[row][column] != 0){  //map has num already
					for(int z=0 ;z<9 ;z++)
						possible[row][column][z] = false;
					possible[row][column][map[row][column]-1] = true;  //has num ,assign true ,and other all false
				}
				else{  //map doesn't have num
					//check the row
					for(int y=0 ;y<9 ;y++){
						if(map[y][column] != 0)
							possible[row][column][map[y][column]-1] = false;
					}
					//check the column
					for(int x=0 ;x<9 ;x++){
						if(map[row][x] != 0)
							possible[row][column][map[row][x]-1] = false;
					}

					//check the team block 3*3
					for(int i=0 ;i<3 ;i++){
						for(int j=0 ;j<3 ;j++){
							if(map[row -(row%3) + i][column - (column%3) + j] != 0)
								possible[row][column][map[row - (row%3) + i][column - column%3 + j] - 1] = false;
						}
					}
				}
			}  //end of the two ""for loop"" under the "while"

	int count;
	int flag = 0 ;
	for(int i=0 ;i<9 ;i++)	//check the possible num of the "possible" array
		for(int j=0 ;j<9 ;j++){
			count = 0;
			for(int z=0 ;z<9 ;z++){
				if(possible[i][j][z]){
				   	count++;
					flag=z+1;
				}
			}
			if(count == 1){  //the possible num just exist one! Assign it into "map"
					map[i][j] = flag;
			}
		}


	//count how many holes are there in the map
	hole = 0;
	for(int i =0 ;i<9 ;i++)
		for(int j=0 ;j<9 ;j++)
			if(map[i][j] == 0) hole++;


	//check whether error in each column or not
	for(int row=0 ;row<9 ;row++)
		for(int column=0;column<9 ;column++){
			int check[10] = {};
			if(map[row][column] != 0)
				check[map[row][column]]++;
			if(check[map[row][column]]>1){
				cout << row << column << "\n";
				cout<< "0" <<"\n";
				return;
			}
		}

	//check whether error in each row or not
	for(int row=0 ;row<9 ;row++)
		for(int column=0 ;column<9 ;column++){
			int check[10]={};
			if(map[row][column] != 0)
				check[map[row][column]]++;
			if(check[map[row][column]]>1){
				cout<< "0" <<"\n";
				return;
			}
		}

	//check whether error in team block or not
	for(int i=0 ;i<9 ;i++)
		for(int j=0 ;j<9 ;j++){
			if(map[i][j])
				for(int m=0 ;m<3 ;m++)
					for(int n=0 ;n<3 ;n++)
						if( map[i-(i%3)+m][j-(j%3)+n] == map[i][j]&&i !=(i-(i%3)+m) && j!=j-(j%3)+n){
							cout<< "0" <<"\n";  //zero solution
							return;
						}
		}
	}

	if(hole != 0){
        cout<< "2" <<"\n";  //extensive solution
        return;
	}

	cout<< "1" <<"\n";
	printOut();
	return;
}


void Sudoku::changeNum(int a ,int b){
	for(int x=0 ;x<9 ;x++)
		for(int y=0 ;y<9 ;y++){
			if(map[x][y] == a) map[x][y] = b;
			else if(map[x][y] == b) map[x][y] = a;
	}

	return;
}

void Sudoku::changeRow(int a ,int b){
	int temp_a[3][9]={};
	int temp_b[3][9]={};

	//copy the row of a to "temp_a"
	//all of the row of temp counted from 2 to 0
	for(int i=0 ;i<3 ;i++)
		if(a==i){
			for(int row=i*3-1 ;row>i*3-1-3 ;row--)
				for(int column=0 ;column<9 ;column++){
					temp_a[row-3*i+1+2][column] = map[row][column];
				}
		}

	//copy the column of b to ""temp_b
	//all of the row of temp counted from 2 to 0
	for(int j=0 ;j<3 ;j++)
		if(b==j){
			for(int row=j*3-1 ;row>j*3-1-3 ;row--)
				for(int column=0 ;column<9 ;column++){
					temp_b[row-3*j+1+2][column] = map[row][column];
				}
		}

	//store temp_a to the_map_of_b
	//exactly changing!
	for(int i=0 ;i<3 ;i++)
		if(a==i){
			for(int row=i*3-1 ;row>i*3-1-3 ;row--)
				for(int column=0 ;column<9 ;column++){
					map[row][column] = temp_b[row-3*i+1+2][column];
				}
		}

	//store temp_b to the_map_of_a
	//exactly changing!
	for(int j=0 ;j<3 ;j++)
		if(b==j){
			for(int row=j*3-1 ;row>j*3-1-3 ;row--)
				for(int column=0 ;column<9 ;column++){
					map[row][column] = temp_b[row-3+j+1+2][column];
				}
		}


	//initialize the two "temp"
	for(int i=0 ;i<3 ;i++)
		for(int j=0 ;j<9 ;j++){
			temp_a[i][j] = 0;
			temp_b[i][j] = 0;
		}

	return;

}


void Sudoku::changeCol(int a ,int b){
	int temp_a[9][3]={};
	int temp_b[9][3]={};

	//copy the column of a to "temp_a"
	//all of the column of temp counted from 2 to 0
	for(int i=0 ;i<3 ;i++)
		if(a==i){
			for(int row=0 ;row<9 ;row++)
				for(int column=i*3-1 ;column>i*3-1-3 ;column--){
					temp_a[row][column-i*3+1+2] = map[row][column];
				}
		}

	//copy the column of b to "temp_b"
	//all of the column of temp counted from 2 to 0
	for(int j=0 ;j<3 ;j++)
		if(b==j){
			for(int row=0 ;row<9 ;row++)
				for(int column=j*3-1 ;column>j*3-1-3 ;column--){
					temp_a[row][column-j*3+1+2] = map[row][column];
				}
		}

	//store temp_a to the_map_of_b
	//exactly chamging
	for(int i=0 ;i<3 ;i++)
		if(a==i){
			for(int row=0 ;row<9 ;row++)
				for(int column=i*3-1 ;column>i*3-1-3 ;column--){
					map[row][column] = temp_a[row][column-i*3+1+2];
				}
		}

	//store temp_b to the_map_of_a
	//exactly chamging
	for(int j=0 ;j<3 ;j++)
		if(b==j){
			for(int row=0 ;row<9 ;row++)
				for(int column=j*3-1 ;column>j*3-1-3 ;column--){
					map[row][column] = temp_a[row][column-j*3+1+2];
				}
		}

	//initialize the two temp
	for(int i=0 ;i<9 ;i++)
		for(int j=0 ;j<9 ;j++){
			temp_a[i][j] = 0;
			temp_b[i][j] = 0;
		}

	return;
}



void Sudoku::rotate(int n){
	int buffer[9][9];

	while(n){
		for(int i=0 ;i<9 ;i++)
			for(int j=0 ;j<9 ;j++){
				buffer[i][j] = map[i][j];
			}
		}
		return;
	}

void Sudoku::flip(int n){
    int temp_map[9][9];

    for(int i=0 ;i<9 ;i++)
        for(int j=0 ;j<9 ;j++){
            temp_map[i][j] = map[i][j];
    }

	//up side down
	if(n == 0){
		for(int i=0 ;i<9 ;i++)
			for(int j=0 ;j<9 ;j++)
				map[i][j] = temp_map[8-i][j];
	}

	//left side right
	else if(n == 1){
		for(int i=0 ;i<9 ;i++)
			for(int j=0 ;j<9 ;j++)
				map[i][j] = temp_map[i][8-j];
	}

	return;
}

void Sudoku::transform(){
	readIn();
	srand((unsigned)time(NULL));
	changeNum(rand()%9+1 , rand()%9+1);
	changeRow(rand()%3 , rand()%3);
	changeCol(rand()%3 , rand()%3);
	rotate(rand()%101);
	flip(rand()%2);
	printOut();

	return;
}

/////////the following are my own func/////////

void Sudoku::printOut(){
	for(int i=0 ;i<9 ;i++)
		for(int j=0 ;j<9 ;j++){
			cout << map[i][j] <<" ";
			if(j == 8) cout<<"\n";
		}
    return;
}
