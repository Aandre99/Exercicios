#include <iostream>
#include <vector>
#include <algorithm>

#define mid(x,y) (x + ((y-x) >> 1))

using namespace std;

vector<int> v;
int index_left = 0;
int index_right = 0;

void search_Left_index(vector<int>:: iterator a, vector<int>:: iterator b, int value)
{
    if(left == right){
        cout << v[left];
    }
}
int main()
{
    int i;
    v.push_back(5);
    v.push_back(54);
    v.push_back(54);
    v.push_back(54);
    v.push_back(566);

    for ( vector <int>::iterator it = v.begin(); it != v.end(); ++it)
    {
        cout << *it << ' ' << endl;
    }

    search_Left_index(v.begin(), v.end(), 54);
    return 0;
}