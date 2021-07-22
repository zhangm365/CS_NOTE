

#include <bits/stdc++.h>

using namespace std;


void _display_category_(input_iterator_tag)
{

    cout << "input_iterator_tag\n";

}

void _display_category_(forward_iterator_tag)
{

    cout << "forward_iterator_tag\n";

}

void _display_category_(bidirectional_iterator_tag)
{

    cout << "bidirectional_iterator_tag\n";

}

void _display_category_(random_access_iterator_tag)
{

    cout << "random_access_iterator_tag\n";

}

void _display_category_(output_iterator_tag)
{

    cout << "output_iterator_tag\n";

}

template<typename T>
void display_category( const T &iter)
{
    typename iterator_traits<T>::iterator_category cagy;
    _display_category_(cagy);

}



int main()
{

    display_category(array<int,10>::iterator());
    display_category(vector<int>::iterator());
    display_category(list<int>::iterator());
    display_category(deque<int>::iterator());
    display_category(forward_list<int>::iterator());


    display_category(set<int>::iterator());
    display_category(multiset<int>::iterator());
    display_category(map<int, int>::iterator());
    display_category(unordered_map<int, int>::iterator());
    display_category(unordered_set<int>::iterator());

    display_category(istream_iterator<int>());
    display_category(ostream_iterator<int>(cout, ""));
    
    return 0;
}
