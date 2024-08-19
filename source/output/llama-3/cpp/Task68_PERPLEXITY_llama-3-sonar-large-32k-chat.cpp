#include <ldap.h>
#include <iostream>
#include <string>

//error: ‘ldap_bind_s’ was not declared in this scope
//added these gloable functions
int ldap_bind_s(LDAP * ldap, std::string::const_pointer c_str, std::string::const_pointer const_pointer, ber_tag_t ber_tag);

int ldap_search_ext_s(LDAP * ld, std::string::const_pointer base, ber_int_t scope, std::string::const_pointer filter, long attrs, int attrsonly,
                      long serverctrls, LDAPMessage ** result);

int main(int argc, char** argv) {
    if (argc != 3) {
        std::cout << "Usage: " << argv[0] << " <domain_component> <username>" << std::endl;
        return 1;
    }

    std::string dc = argv[1];
    std::string username = argv[2];

    LDAP* conn = nullptr;
    int rc = ldap_initialize(&conn, "ldap://localhost:389");
    if (rc != LDAP_SUCCESS) {
        std::cerr << "Error initializing LDAP: " << ldap_err2string(rc) << std::endl;
        return 1;
    }

    // Use a valid bind DN and password for authentication
    std::string bindDN = "cn=admin," + dc; // Example bind DN
    std::string password = "your_password"; // Replace with the actual password

    rc = ldap_bind_s(conn, bindDN.c_str(), password.c_str(), LDAP_AUTH_SIMPLE);
    if (rc != LDAP_SUCCESS) {
        std::cerr << "Error binding to LDAP: " << ldap_err2string(rc) << std::endl;
        ldap_unbind_ext(conn, NULL, NULL);
        return 1;
    }

    std::string baseDN = "dc=" + dc.replace(dc.find('.'), 1, ",dc=");
    std::string query = "(uid=" + username + ")";
    LDAPMessage* result = nullptr;

    rc = ldap_search_ext_s(conn, baseDN.c_str(), LDAP_SCOPE_SUBTREE, query.c_str(), NULL, 0, NULL, &result);
    if (rc != LDAP_SUCCESS) {
        std::cerr << "Error searching LDAP: " << ldap_err2string(rc) << std::endl;
        ldap_unbind_ext(conn, NULL, NULL);
        return 1;
    }

    // Iterate through the results
    for (LDAPMessage* entry = ldap_first_entry(conn, result); entry != nullptr; entry = ldap_next_entry(conn, entry)) {
        char* dn = ldap_get_dn(conn, entry);
        if (dn) {
            std::cout << "DN: " << dn << std::endl;
            ldap_memfree(dn);
        }
    }

    ldap_msgfree(result);
    ldap_unbind_ext(conn, NULL, NULL);
    return 0;
}
