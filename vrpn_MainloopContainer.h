#ifndef _VRPN_MAINLOOPCONTAINER_H_
#define _VRPN_MAINLOOPCONTAINER_H_

#include "vrpn_MainloopObject.h"

#include <vector>

class vrpn_MainloopContainer 
{
public:
	vrpn_MainloopContainer() {}
    ~vrpn_MainloopContainer();

    void clear();

    void add(vrpn_MainloopObject * o);

    template<class T>
    void add(T o) {
		add(vrpn_MainloopObject::wrap(o));
    }

    void mainloop();

private:
    std::vector<vrpn_MainloopObject *> _vrpn;
};

#endif // _VRPN_MAINLOOPCONTAINER_H_
