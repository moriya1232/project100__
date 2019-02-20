
#ifndef ENTERC_H
#define ENTERC_H

#include "Command.h"

class EnterC : public Command {
public:
    EnterC();
    virtual unsigned int doCommand(vector<string> data, unsigned int index);

};



#endif //ENTERC_H