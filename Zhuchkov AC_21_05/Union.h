#pragma once

#include "Pipe.h"
#include "CS.h"

class Union
{
public:
    int id;
    CS CS_1;
    CS CS_2;
    Pipe _Pipe;

    void add_Union_inner(int _id, CS CS_1, CS CS_2, Pipe Pipe_);
    void out_Union_inner();
};
