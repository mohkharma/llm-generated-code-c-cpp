#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>

void drop_privileges() {
    struct passwd *pw;
    uid_t uid;
    gid_t gid;

    // Get nobody user's uid and gid
    pw = getpwnam("nobody");
    if (pw) {
        uid = pw->pw_uid;
        gid = pw->pw_gid;

        // Set gid and uid to nobody
        if (setgid(gid) == -1) {
            perror("setgid");
            return;
        }
        if (setuid(uid) == -1) {
            perror("setuid");
            return;
        }
    } else {
        fprintf(stderr, "Failed to get 'nobody' user details
");
    }
}