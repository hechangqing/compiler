#include <iostream>
#include <exception>
#include "scope.h"

using namespace std;

int main()
{
    try {
        Scope::ScopePtr global(new Scope(NULL, "global"));
        Symbol i("i", Symbol::kInt);
        global->define(i);
        Symbol ai("j", Symbol::kFloat);
        global->define(ai);
        Symbol dump;
        cout << global->resolve("i", &dump) << endl;
        cout << dump.to_str() << endl;
        cout << global->resolve("j", &dump) << endl;
        cout << dump.to_str() << endl;
        cout << global->resolve("x", &dump) << endl;
        cout << dump.to_str() << endl;
        Scope local(global, "local");
        cout << local.resolve("i", &dump) << endl;
        cout << dump.to_str() << endl;
        
    } catch (exception &e) {
        cout << e.what() << endl;
    }
    return 0;
}
