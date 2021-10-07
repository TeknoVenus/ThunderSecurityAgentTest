#include <memory>
#include <iostream>
#include <dlfcn.h>

int main(int argc, char const *argv[])
{
    const char* path = "./libSecurityAgentTestLib.so";
    std::cout << "Loading library from " << path << "\n";
    void* handle = dlopen(path, RTLD_LAZY);

    if (!handle)
    {
        std::cerr << "Failed to dlopen() lib with error: " << dlerror() << "\n";
        return 1;
    }
    else
    {
        std::cout << "Successfully loaded library from " << path << "\n";
    }

    // reset errors
    dlerror();

    typedef void (*generate_token_t)();
    generate_token_t generateTokenFn = (generate_token_t) dlsym(handle, "GenerateToken");

    const char *dlsym_error = dlerror();
    if (dlsym_error) {
        std::cerr << "Cannot load symbol 'hello': " << dlsym_error << '\n';
        dlclose(handle);
        return 1;
    }

    if (!generateTokenFn)
    {
        std::cerr << "ctor not found\n";
        return 1;
    }

    generateTokenFn();

    std::cout << "Closing library...\n";
    dlclose(handle);

    return 0;
}
