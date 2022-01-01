#include <queue>

template<typename S>
class Explorer
{
private:
    class Compare
    {
    public:
        bool operator()(S a, S b)
        {
            return (b.Done() && !a.Done()) || (a.cost > b.cost);
        }
    };

public:
    std::priority_queue<S, std::vector<S>, Compare> todo;
    S Explore(S start)
    {
        bool bestValid = false;
        long best = 0;
        todo.push(start);

        while(!todo.empty())
        {
            auto top = todo.top();
            todo.pop();

            for(const auto& i:top.GetNext())
            {
                if (i.Done())
                {
                    if (!bestValid || i.cost < best)
                    {
                        best = i.cost;
                        bestValid = true;

                        i.Best();
                    }
                }
                else if (i.Accept())
                {
                    todo.push(i);
                }
            }
        }
        return S{};
    }
};
