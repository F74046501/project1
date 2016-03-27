#include"class.h"
#include <fstream>

void soduko::giveQuestion()

void soduko::readIn(){
	ifstream fin("soduko");  //file in
	
	if(!fin){
	cout<<"the file can not be opened";
	return 1;
	}

	soduko project1;  //the class "name" of the project1	
	
	int map[9][9];
	for(int i=0 ;i<9 ;i++)
		for(int j=0 ;j<9 ;j++){
			fin >> sdk[i][j];
			project1.setsdk(sdk[i][j]);  //store the sdk[][] into "map[][]" ;and set[][] is the media
			}
}

void soduko::solve(){
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
	
	int hole = 1 ,pre_hole = 1;  //after initializing ,to solve it!
	
	while(pre_hole != hole && hole!= 0){  //not yet run out the ans ,keep tryimg
		pre_hole = hole;
		for(int row = 0 ;row<9 ;row++)
			for(int column = 0 ;column<9 ;column++){
				
				if(map[row][column] != 0){  //map has num already
					for(z=0 ;z<9 ;z++)
						possible[row][column][z] = false;
					possible[row][column][map[row][column]-1] = true;  //has num ,assign true ,and other all false
				}
				else{  //map doesn't have num
					for(int z=0 ;z<9 ;z++)
						possible[row][column][z] = false;  //assign it false again
				
					//check the row
					for(int y=0 ;y<9 y++){
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
						for(int j=0 ;j<3 j++){
							if(map[row -(row%3) + i][column - (column%3) + j])
								possible[row][column][map[row - (row%3) + i][column - column%3 + j] - 1] = false;
						}
					}
				}
			}  //end of the two ""for loop"" under the "while"


	for(int i=0 ;i<9 ;i++)	//check the possible num of the "possible" array
		for(int j=0 ;j<9 ;j++){
			for(int z=0 ;z=9 ;z++)
				if(possible[i][j][z] == 0) int count++;
				else int flag = z;

				if(count == 8){  //the possible num just exist one! Assign it into "map"
					map[i][j] = flag+1;
				}
		}
		
	hole = 0;  //refresh the num of hole
	for(int i =0 ;i<9 ;i++)
		for(int j=0 ;j<9 ;j++)
			if(map[i][j] == 0) hole++;	
	

	//check whether error in each column
	for(int column=0 ;column<9 ;column++)	
		for(int row=0 ;row<9 ;row++){
			int check[i] = {};
			if(map[row][column] != 0)
				check[map[row][column]]++;
			if(check[map[row][column]]>1)
				return 0;	
		}

	//check whether error in each row
	for(int row=0 ;row<9 ;row++)
		for(int column=0 ;column<9 ;column++){
			int check[9]={};
			if(map[row][column] != 0)
				check[map[row][column]]++;
			if(check[map[row][column]]>1)
				return 0;
		}
			
	//check whether error in team block
	for(int i=0 ;i<9 ;i++)
		for(int j=0 ;j<9 ;j++){
			if(map[i][j])
				for(int m=0 ;m<3 ;m++)
					for(int n=0 ;n<3 ;n++)
						if( map[ i - ( i % 3 ) + m ][ j - ( j % 3 ) + n ] == map[ i ][ j ] && i != ( i - ( i % 3 ) + m ) && j != j - ( j % 3 ) + n ) return 0;
		}
	}
	
	if(hole != 0) return 2;
	return 1;
}


void soduko::changeNum(int a ,int b){
	f_sdk[9][9][9] = getsdk();
	for(int x=0 ;x<9 ;x++)
		for(int y=0 ;y<9 ;y++){
			if(f_sdk[x][y][0] == a)
				

void soduko::changeRow(int a ,int b)

void soduko::changeCol(int a ,int b)

void soduko::rotate(int n)

void soduko::flip(int n)

void soduko::transform()

/////////the following are my own func/////////

void soduko::setsdk(int set[9][9][9]){
	for(int i ;i<8 ;i++){
		
		sdk[i][j] = set[i][j];
	}
}

void soduko::getsdk(){
	return sdk[9][9];
}
