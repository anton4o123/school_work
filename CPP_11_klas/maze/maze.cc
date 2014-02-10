#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cstdio>
using namespace std;

enum Direction {
	NONE = 0,
	UP = 1,
	LEFT = 1 << 1,
	DOWN = 1 << 2,
	RIGHT = 1 << 3
};

class Cell {
	static const int WALL_SIZE=20;

	unsigned int walls_;
	unsigned int row_;
	unsigned int col_;
	bool visited_;
	
	string draw_wall(bool has_wall) const {
		return has_wall?" rlineto":" rmoveto";
	}
public:
	Cell(unsigned int row, unsigned int col,
		unsigned int walls=UP|LEFT|DOWN|RIGHT)
	: walls_(walls),
	  row_(row),
	  col_(col),
	  visited_(false)
	{}
	
	Cell& visit() {
		visited_=true;
		return *this;
	}
	
	Cell& unvisit() {
		visited_=false;
		return *this;
	}
	
	bool is_visited() const {
		return visited_;
	}
	
	bool has_wall(Direction dir) const {
		return dir & walls_;
	}

	Cell& set_wall(Direction dir) {
		walls_ |= dir;	
			return *this;
	}
	
	Cell& unset_wall(Direction dir) {
		walls_ &= ~dir;
		return *this;
	}

	unsigned get_row() const {
		return row_;
	}
	
	unsigned get_col() const {
		return col_;
	}
	
	void draw(ostream& out) const {
		out << (get_col()+1)*WALL_SIZE << ' ' << (get_row()+1)*WALL_SIZE << ' ' << "moveto" << endl;
		out << WALL_SIZE << ' ' << 0 << draw_wall(has_wall(DOWN)) << endl;
		out << 0 << ' ' << WALL_SIZE << draw_wall(has_wall(RIGHT)) << endl;
		out << -WALL_SIZE << ' ' << 0 << draw_wall(has_wall(UP)) << endl;
		out << 0 << ' ' << -WALL_SIZE << draw_wall(has_wall(LEFT)) << endl;
	}
};

	class BoardError{};

	Direction n_dir(Direction dir) {
		Direction ndir;
		
		switch(dir) {
			case UP:
				ndir=DOWN;
				break;
			case LEFT:
				ndir=RIGHT;
				break;
			case DOWN:
				ndir=UP;
				break;
			case RIGHT:
				ndir=LEFT;
				break;
			default:
				throw BoardError();
		}
		
		return ndir;
	}

class Board {
	unsigned width_;
	unsigned height_;
	vector<Cell> cells_;
public:
	Board(unsigned width, unsigned height)
	: width_(width),
	  height_(height)
	{
		for(unsigned row=0;row<height_;row++) {
			for(unsigned col=0;col<width_;col++) {
				cells_.push_back(Cell(row,col));
			}
		}
	}
	const Cell& get_cell(unsigned row, unsigned col) const {
		return cells_[row*width_+col];
	}
	
	Cell& get_cell(unsigned row, unsigned col) {
		return cells_[row*width_+col];
	}
	
	void draw(ostream& out) const {
		out << "newpath" << endl;
		
		for(vector<Cell>::const_iterator it=cells_.begin(); it!=cells_.end(); it++) {
			(*it).draw(out);
		}
		
		out << "closepath" << endl;
	}
	
	bool has_neighbour(unsigned row, unsigned col, Direction dir) const {
		if(row==0 && dir==DOWN)
			return false;
		if(row==height_-1 && dir==UP)
			return false;
		if(col==0 && dir==LEFT)
			return false;
		if(col==width_-1 && dir==RIGHT)
			return false;
		return true;
	}
	
	Cell& get_neighbour(unsigned row, unsigned col, Direction dir) {
		if(! has_neighbour(row, col, dir)) {
			throw BoardError();
		}
		unsigned nr= (dir==UP)? row+1:((dir==DOWN)? row-1: row);
		unsigned nc= (dir==RIGHT)? col+1: ((dir==LEFT)? col-1:col);
		return get_cell(nr,nc);
	}
	
	const Cell& get_neighbour(unsigned row, unsigned col, Direction dir) const {
		if(! has_neighbour(row, col, dir)) {
			throw BoardError();
		}
		unsigned nr= (dir==UP)? row+1:((dir==DOWN)? row-1: row);
		unsigned nc= (dir==RIGHT)? col+1: ((dir==LEFT)? col-1:col);
		return get_cell(nr,nc);
	}
	
	void drill_wall(unsigned row, unsigned col, Direction dir) {
		Cell& c=get_cell(row, col);
		c.unset_wall(dir);
		
		if(! has_neighbour(row, col, dir)) {
			return;
		}
		Cell& n=get_neighbour(row, col, dir);
		Direction ndir=n_dir(dir);
		n.unset_wall(ndir);
		// ??????
		// FIND OPOSITE DIRECTION
		// UNSET NEIGHBOUR WALL
	}
private:
	const static Direction DIRECTIONS[];//={UP,LEFT,RIGHT,DOWN};
	const static int DSIZE=4;
		
public:
	Direction has_unvisited_neighbour(int row, int col) const {
		for(int i=0;i<DSIZE;++i) {
			Direction d=DIRECTIONS[i];
			if(has_neighbour(row,col,d)) {
				const Cell& c=get_neighbour(row,col,d);
				if(!c.is_visited()) {
					return d;
				}
			}
		}
		
		return NONE;
	}
	
	Direction has_unvisited_neighbour_wall(int row, int col) const {
		for(int i=0;i<DSIZE;++i) {
			Direction d=DIRECTIONS[i];
			if(has_neighbour(row,col,d)) {
				const Cell& c=get_neighbour(row,col,d);
				if((!c.is_visited()) && (!c.has_wall(n_dir(d)))) {
					return d;
				}
			}
		}
		
		return NONE;
	}
	
	int how_many_unvisited_neighbours(int row, int col) const {
		int j=0;
		for(int i=0;i<DSIZE;++i) {
			Direction d=DIRECTIONS[i];
			if(has_neighbour(row,col,d)) {
				const Cell& c=get_neighbour(row,col,d);
				if((!c.is_visited()) && (!c.has_wall(n_dir(d)))) {
					j++;
				}
			}
		}
		
		return j;
	}
	
	Direction get_random_unvisited_neighbour(int row,int col) const {
		if(!has_unvisited_neighbour(row,col)) {
			return NONE;
		}
		
		while(true) {
			int ind=rand()%DSIZE;
			Direction d=DIRECTIONS[ind];
			if(has_neighbour(row,col,d)) {
				const Cell& c=get_neighbour(row,col,d);
				if(!c.is_visited()) {
					return d;
				}
			}
		}
	}
	
	Direction get_random_unvisited_neighbour_wall(int row,int col) const {
		if(!has_unvisited_neighbour_wall(row,col)) {
			return NONE;
		}
		
		while(true) {
			int ind=rand()%DSIZE;
			Direction d=DIRECTIONS[ind];
			if(has_neighbour(row,col,d)) {
				const Cell& c=get_neighbour(row,col,d);
				if((!c.is_visited()) && (!c.has_wall(n_dir(d)))) {
					return d;
				}
			}
		}
	}
	
	void generate(int row, int col) {
		Cell& c=get_cell(row, col);
		c.visit();
		
		while(true) {
			Direction dir=get_random_unvisited_neighbour(row,col);
			if(dir==NONE) {
				return;
			}
			drill_wall(row,col,dir);
			Cell& n=get_neighbour(row,col,dir);
			generate(n.get_row(),n.get_col());
		}
	}
	
	void unvisit_all() {
		for(int i=0;i<height_;i++)
			for(int j=0;j<width_;j++) {
				Cell& c=get_cell(i, j);
				c.unvisit();
			}
	}
	
	void draw_path(int start_row, int start_col, int end_row, int end_col,ostream& out) {
		int crosscells[100][2];
		int path[400][2];
		int k[400];
		int i=-1,j=-1,row=start_row,col=start_col;
		Cell& c=get_cell(start_row,start_col);
		unvisit_all();
		c.visit();
		
		while(true) {
			j++;
			row=path[j][0]=c.get_row();
			col=path[j][1]=c.get_col();
			
			if(row==end_row && col==end_col) {
				break;
			}
			
			if(how_many_unvisited_neighbours(row,col)>1) {
				i++;
				k[i]=j;
				crosscells[i][0]=c.get_row();
				crosscells[i][1]=c.get_col();
			}

			if(how_many_unvisited_neighbours(row,col)==0) {
				row=crosscells[i][0];
				col=crosscells[i][1];
				if(how_many_unvisited_neighbours(row,col)==1) {
					j=k[i];
					i--;
				}
				continue;
			}

			Direction dir=get_random_unvisited_neighbour_wall(row,col);
			if(dir==NONE) {
				break;
			}
			c=get_neighbour(row,col,dir);
			c.visit();
		//	cout << c.is_visited() << endl;
		}
		
		out << "stroke" << endl;
		out << "30 30 moveto" << endl;
		out << "1 0 0 setrgbcolor" << endl;
		for(i=1;i<=j;i++) {
			out << (path[i][1]-path[i-1][1])*20 << ' ' << (path[i][0]-path[i-1][0])*20 << " rlineto" << endl;
		}
		
		out << "stroke" << endl;
		out << "showpage" << endl;
	}
};

const Direction Board::DIRECTIONS[]={UP,LEFT,RIGHT,DOWN};

int main() {
	srand((unsigned)time(NULL));
	Board b(20,20);
	
	b.generate(0,0);
	
	b.draw(cout);
	b.draw_path(0,0,2,2,cout);

	return 0;
}
