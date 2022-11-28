#include "Union.h"

#include <iostream>
using namespace std;

void Union::add_Union_inner(int _id, CS CS_1_, CS CS_2_, Pipe Pipe) {
	id = _id;
	CS_1 = CS_1_;
	CS_2 = CS_2_;
	_Pipe = Pipe;
};

void Union::out_Union_inner() {
	cout << "\n\nid соединения: " << id;
	CS_1.out_CS_inner();
	CS_2.out_CS_inner();
	_Pipe.out_pipe_inner();
};