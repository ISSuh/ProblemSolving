/*
https://www.acmicpc.net/problem/2565

두 전봇대 A와 B 사이에 하나 둘씩 전깃줄을 추가하다 보니 전깃줄이 서로 교차하는 경우가 발생하였다. 합선의 위험이 있어 이들 중 몇 개의 전깃줄을 없애 전깃줄이 교차하지 않도록 만들려고 한다.

예를 들어, <그림 1>과 같이 전깃줄이 연결되어 있는 경우 A의 1번 위치와 B의 8번 위치를 잇는 전깃줄, A의 3번 위치와 B의 9번 위치를 잇는 전깃줄, A의 4번 위치와 B의 1번 위치를 잇는 전깃줄을 없애면 남아있는 모든 전깃줄이 서로 교차하지 않게 된다.



전깃줄이 전봇대에 연결되는 위치는 전봇대 위에서부터 차례대로 번호가 매겨진다. 전깃줄의 개수와 전깃줄들이 두 전봇대에 연결되는 위치의 번호가 주어질 때, 남아있는 모든 전깃줄이 서로 교차하지 않게 하기 위해 없애야 하는 전깃줄의 최소 개수를 구하는 프로그램을 작성하시오.
*/

#include <iostream>
#include <vector>
#include <algorithm>

int main(){
    int n = 0;
    
    std::cin >> n;
    
    std::vector<std::pair<int,int>> item;
    std::vector<int> val(n);
    
    for (auto i=0; i<n; i++){
        int first = 0, second = 0;
        std::cin >> first >> second;

        item.push_back(std::make_pair(first, second));
    }
    
    std::sort(item.begin(), item.end());

    val[0] = 1;
    for(auto i=1 ; i<n; ++i){
        int maxValueIndex = 0, maxValue = 0;

        for(auto j=0 ; j<i ; ++j){
            if((item[i].second > item[j].second) && (maxValue < val[j])){
                    maxValue = val[j];
                    maxValueIndex = j;
            }
        }

        if(item[i].second > item[maxValueIndex].second)
            val[i] = 1 + val[maxValueIndex];
        else
            val[i] = val[maxValueIndex];
    }
        
    std::cout << n - *std::max_element(val.begin(),val.end()) << std::endl;

}


