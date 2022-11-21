#pragma once
class Pipe
{
private:
    int _idPipe;
    float _length;
    float _diameter;

public:

    bool _inWork;

    int get_idPipe() { return _idPipe; };
    float get_length() { return _length; };
    float get_diameter() { return _diameter; };
    bool get_inWork() { return _inWork; };

    void add_pipe_inner(int __idPipe, float __length, float __diameter, bool __inWork);

    void out_pipe_inner();
};

