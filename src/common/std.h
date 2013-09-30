#ifndef _STD_H_
#define _STD_H_

#include <string>
#include <vector>
#include <map>
#include <tuple>
#include <memory>
#include <array>
#include <functional>

using std::string;
using std::to_string;

using std::vector;
using std::array;

using std::map;
using std::pair;

using std::swap;

using std::function;
using std::bind;
using namespace std::placeholders;

using std::tuple;
using std::make_tuple;
using std::get;

using std::static_pointer_cast;
using std::dynamic_pointer_cast;

using std::unique_ptr;
// http://herbsutter.com/gotw/_102/
template<typename T, typename ...Args>
std::unique_ptr<T> make_unique( Args&& ...args ) {
    return std::unique_ptr<T>( new T( std::forward<Args>(args)... ) );
}

using uint = unsigned int;

#endif
