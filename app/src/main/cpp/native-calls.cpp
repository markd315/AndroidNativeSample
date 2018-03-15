#include <jni.h>
#include <string>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/fcntl.h>
#include <iostream>

extern "C"
JNIEXPORT jstring
JNICALL
Java_edu_ufl_cise_os_p2_P2Activity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {

    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}
char* read_file(const char *filename){
    char* ret;
    int fileRead;
    fileRead = open(filename, O_RDONLY); //Make POSIX call.
    if(fileRead == -1){ //Catch FileNotFound type errors.
        ret = "Couldn't find file!";
        return ret;
    }
    off_t size = lseek(fileRead, 0, SEEK_END); //POSIX call to find filesize.
    lseek(fileRead, 0, SEEK_SET); //Move cursor back to start.
    char* buffer = (char*) malloc(size + 1); //Leave space for null-terminator.
    while(read(fileRead, buffer, size) > 0){}//Should only run once.
    close(fileRead);
    return buffer; //We need to free() it after this though (from caller)
}
extern "C"
JNIEXPORT jstring
JNICALL
Java_edu_ufl_cise_os_p2_P2Activity_stringFromFile(
        JNIEnv *env,
        jobject /* this */,
        jstring filename) { //Add new parameter to list for the file to load from.
    const char* nativeFilename = (env)->GetStringUTFChars(filename, JNI_FALSE); //dumb constructor, means it's not a copy.
    const char* nativeContents = read_file(nativeFilename);
    return env->NewStringUTF(nativeContents);
}


