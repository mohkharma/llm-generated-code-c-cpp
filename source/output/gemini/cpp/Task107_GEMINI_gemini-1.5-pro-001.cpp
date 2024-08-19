#include <jni.h>
#include <string.h>

extern "C" JNIEXPORT jobject JNICALL Java_JndiLookup_lookup(JNIEnv *env, jclass clazz, jstring name) {
    const char *nameStr = env->GetStringUTFChars(name, nullptr);
    jobject result = nullptr;

    try {
        // Create a Java object of type JndiLookup
        jclass jndiLookupClass = env->FindClass("JndiLookup");
        jmethodID lookupMethod = env->GetStaticMethodID(jndiLookupClass, "lookup", "(Ljava/lang/String;)Ljava/lang/Object;");
        result = env->CallStaticObjectMethod(jndiLookupClass, lookupMethod, name);
    } catch (...) {
        // Handle exceptions
    }

    env->ReleaseStringUTFChars(name, nameStr);
    return result;
}

int main() {
    // Load the Java library
    JavaVM *jvm;
    JNIEnv *env;
    JavaVMInitArgs vm_args;
    memset(&vm_args, 0, sizeof(vm_args));
    vm_args.version = JNI_VERSION_1_8; // Adjust version as needed
    vm_args.nOptions = 0;
    JNI_CreateJavaVM(&jvm, (void **)&env, &vm_args);

    // Call the Java method
    jstring jname = env->NewStringUTF("your_jndi_name");
    jobject result = Java_JndiLookup_lookup(env, nullptr, jname);

    // Process the result (if successful)
    // ...
//error: ‘JNIEnv’ {aka ‘struct JNIEnv_’} has no member named ‘DestroyJavaVM’; did you mean ‘GetJavaVM’?
    // can't be fixed, line is commented
    // env->DestroyJavaVM();
    return 0;
}
