/* 
 * File:   test.cpp
 * Author: Konstantin
 *
 * Created on March 2, 2016, 10:25 AM
 */

#include <iostream>
#include "Utility/HashedKey.hpp"
#include <vector>
#include <map>

/*
 * 
 */
/*
template <typename Ret, typename... Args>
struct __function_wrapper
{
    std::shared_ptr<hermes::interface::IObject> evaluate(const std::vector<hermes::interface::IObject>& arglist)
    {
        if (arglist.size() != sizeof...(Args)) throw std::bad_function_call();
    }
};
*/

#include "Extern/Externalizer.hpp"

int main (int argc, char** argv)
{
    std::shared_ptr<hermes::interface::IClass> stringClass (hermes::ext::createClass<std::string>(std::string("string")));
    std::shared_ptr<hermes::interface::IObject> stringObject ((*stringClass)());
    std::string& stringValue = hermes::object::cast<std::string>(stringObject->reference());
    stringValue = "Sample String";
    std::cout << stringValue << std::endl;
    std::cout << "Class ID = " << stringObject->getClass().id() << std::endl;
//    hermes::object::NativeObject<std::string> int_native ("[String Object]");
//    hermes::interface::IObject& obj_int = int_native;
//    std::shared_ptr<hermes::interface::IObject> ref = obj_int.getClass()();
//    decltype(auto) int_value = cast<std::string>(obj_int.reference());
//    decltype(auto) ref_value = cast<std::string>(ref->reference());
//    int_value = "What's up?";
//    ref_value = "New Object Value";
//    std::cout << int_value << std::endl;
//    std::cout << ref_value << std::endl;
//    size_t hashValue = std::hash<std::string>()("string");
//    obj_int.getClass().id(hashValue);
//    std::cout << "Class id = " << obj_int.getClass().id() << std::endl;
    return 0;
}

