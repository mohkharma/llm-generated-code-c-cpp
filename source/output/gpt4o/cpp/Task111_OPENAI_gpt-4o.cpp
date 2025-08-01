#include <xmlrpc-c/base.hpp>
#include <xmlrpc-c/registry.hpp>
#include <xmlrpc-c/server_abyss.hpp>

class addMethod : public xmlrpc_c::method {
public:
    void execute(xmlrpc_c::paramList const& paramList, xmlrpc_c::value*   const  retvalP) {
        int const x(paramList.getInt(0));
        int const y(paramList.getInt(1));
        paramList.verifyEnd(2);
        *retvalP = xmlrpc_c::value_int(x + y);
    }
};

class subtractMethod : public xmlrpc_c::method {
public:
    void execute(xmlrpc_c::paramList const& paramList, xmlrpc_c::value*   const  retvalP) {
        int const x(paramList.getInt(0));
        int const y(paramList.getInt(1));
        paramList.verifyEnd(2);
        *retvalP = xmlrpc_c::value_int(x - y);
    }
};
