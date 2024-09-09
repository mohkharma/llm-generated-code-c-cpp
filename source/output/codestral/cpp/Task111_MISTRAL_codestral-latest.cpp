#include <xmlrpc-c/base.hpp>
#include <xmlrpc-c/registry.hpp>
#include <xmlrpc-c/server_abyss.hpp>
//error: ‘iterator’ is not a member of ‘xmlrpc_c::value_array’
//code can't be fixed, file is commented
int add(xmlrpc_c::paramList const& paramList, xmlrpc_c::value* const retvalP) {
    int sum = 0;
    /*rror: ‘iterator’ is not a member of ‘xmlrpc_c::value_array’
    7 |     for (xmlrpc_c::value_array::iterator i = paramList.begin(); i != paramList.end(); ++i) {*/
    for (xmlrpc_c::value_array::iterator i = paramList.begin(); i != paramList.end(); ++i) {
        xmlrpc_c::value_int const* valueIntP;
        if (xmlrpc_c::value_int_internals::getFromValue(*i, &valueIntP)) {
            sum += valueIntP->getValue();
        } else {
            return XMLRPC_INT_INVALID_TYPE;
        }
    }
    *retvalP = xmlrpc_c::value_int(sum);
    return XMLRPC_SUCCESS;
}

int main() {
    xmlrpc_c::registry registry;
    xmlrpc_c::methodPtr const addMethodP(new xmlrpc_c::method("add", &add));
    registry.addMethod("add", addMethodP);

    xmlrpc_c::serverAbyss.serve(registry, 8000);

    xmlrpc_c::cleanUpLibrary();
    return 0;
}
