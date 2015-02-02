#ifndef __MISC_H__
#define __MISC_H__

#include <string>
#include <sstream>

using namespace std;

template<typename T>
class Misc
{
public:
	static string to_string(T value)
	{
		//create an output string stream
		ostringstream os;

		//throw the value into the string stream
		os << value;

		//convert the string stream into a string and return
		return os.str();
	}
private:
};

#endif // __MISC_H__