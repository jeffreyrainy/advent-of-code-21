#include <vector>
#include <string>
#include <map>
#include <set>

class Data
{
public:
    std::vector<std::vector<std::string>> words;
    std::vector<std::vector<int64_t>> numbers;

    std::vector<std::string> raw;
    std::set<std::string> allWords;
};

void process(Data& data);
std::map<char, std::string> getReplacements();

template<typename U, typename V> std::ostream& operator<<(std::ostream& out, std::pair<U, V>& t)
{
    out << t.first << " " << t.second;

    return out;
}

template<typename T> std::ostream& operator<<(std::ostream& out, std::vector<T>& t)
{
    for(auto x: t)
    {
        out << x << " ";
    }
    return out;
}

template<typename T> std::ostream& operator<<(std::ostream& out, std::set<T>& t)
{
    for(auto x: t)
    {
        out << x << " ";
    }
    return out;
}

template<typename U, typename V> std::ostream& operator<<(std::ostream& out, std::map<U, V>& t)
{
    for(auto i: t)
    {
        out << i.first << ":" << i.second << ", ";
    }
    return out;
}

