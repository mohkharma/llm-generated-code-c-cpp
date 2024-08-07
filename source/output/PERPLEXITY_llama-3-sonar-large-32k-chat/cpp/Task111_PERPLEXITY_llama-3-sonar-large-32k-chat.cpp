// Note: XML-RPC is not natively supported in C++. This example uses the xmlrpc-c library.
// You need to install xmlrpc-c and its development package to compile this code.

//can't be fixed by regeneration


#include <xmlrpc-c/config.h>
#include <xmlrpc-c/util.h>
#include <xmlrpc-c/server.h>
#include <xmlrpc-c/registry.hpp>
//
// class MyXmlRpcHandler : public xmlrpc_c::requestHandler {
// public:
//     MyXmlRpcHandler(xmlrpc_c::registry* const registryP) :
//             xmlrpc_c::requestHandler(registryP) {}
//
//     void add(xmlrpc_c::paramList const& paramList, xmlrpc_c::value* const resultP) {
//         int const a = xmlrpc_c::value_int(paramList.getString(0));
//         int const b = xmlrpc_c::value_int(paramList.getString(1));
//         *resultP = xmlrpc_c::value_int(a + b);
//     }
//
//     void subtract(xmlrpc_c::paramList const& paramList, xmlrpc_c::value* const resultP) {
//         int const a = xmlrpc_c::value_int(paramList.getString(0));
//         int const b = xmlrpc_c::value_int(paramList.getString(1));
//         *resultP = xmlrpc_c::value_int(a - b);
//     }
// };
//
// int main() {
//     xmlrpc_c::registry myRegistry;
//     MyXmlRpcHandler myHandler(&myRegistry);
//     myRegistry.addMethod("add", &MyXmlRpcHandler::add);
//     myRegistry.addMethod("subtract", &MyXmlRpcHandler::subtract);
//     xmlrpc_c::serverAbyss myServer(&myRegistry, 8080);
//     myServer.run();
//     return 0;
// }