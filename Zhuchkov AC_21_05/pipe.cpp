#include "pipe.h"
#include <iostream>
using namespace std;

void Pipe::add_pipe_inner(int __idPipe, float __length, float __diameter, bool __inWork) {
    _idPipe = __idPipe;
    _length = __length;
    _diameter = __diameter;
    _inWork = __inWork;
}

void Pipe::out_pipe_inner() {
    cout << "\n\nТруба\n" << "ID: " << _idPipe << "\nДлина: " << _length << "\nДиаметр: " << _diameter << "\nВ работе: " << _inWork << "\n";
};
