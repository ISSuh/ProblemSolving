/*
https://www.acmicpc.net/problem/1744

길이가 N인 수열이 주어졌을 때, 그 수열의 합을 구하려고 한다. 하지만, 그냥 그 수열의 합을 모두 더해서 구하는 것이 아니라, 수열의 두 수를 묶으려고 한다. 어떤 수를 묶으려고 할 때, 위치에 상관없이 묶을 수 있다. 하지만, 같은 위치에 있는 수(자기 자신)를 묶는 것은 불가능하다. 그리고 어떤 수를 묶게 되면, 수열의 합을 구할 때 묶은 수는 서로 곱한 후에 더한다.

예를 들면, 어떤 수열이 {0, 1, 2, 4, 3, 5}일 때, 그냥 이 수열의 합을 구하면 0+1+2+4+3+5 = 15이다. 하지만, 2와 3을 묶고, 4와 5를 묶게 되면, 0+1+(2*3)+(4*5) = 27이 되어 최대가 된다.

수열의 모든 수는 단 한번만 묶거나, 아니면 묶지 않아야한다.

수열이 주어졌을 때, 수열의 각 수를 적절히 묶었을 때, 그 합이 최대가 되게 하는 프로그램을 작성하시오
*/

#include <iostream>
#include <vector>
#include <algorithm>

int main(){
    int N = 0 , result = 0;;
    std::cin >> N;

    std::vector<int> positiveItem;
    std::vector<int> negativeItem;

    for(auto i = 0 ; i < N ; i++){
        int tmp = 0;
        std::cin >> tmp;
        
        if(tmp > 0)
            positiveItem.push_back(tmp);
        else
            negativeItem.push_back(tmp);
    }

    std::sort(positiveItem.begin(), positiveItem.end(), std::greater<int>());    
    std::sort(negativeItem.begin(), negativeItem.end());

    if(positiveItem.size() != 0){
       int index = 0;
       while(index < positiveItem.size()){
            if(index + 2 <= positiveItem.size()){
                if(positiveItem[index] > 1 && positiveItem[index+1] > 1){
                   result += positiveItem[index] * positiveItem[index+1];
                    index += 2;
                }
                else{
                    result += positiveItem[index];
                    index += 1;
                }
            }
            else{
                result += positiveItem[index];
                index += 1;
            }
       }
    }

    if(negativeItem.size() != 0){
       int index = 0;
       while(index < negativeItem.size()){
            if(index + 2 <= negativeItem.size()){
                result += negativeItem[index] * negativeItem[index+1];
                index += 2;
            }
            else{
                result += negativeItem[index];
                index += 1;
            }
       }
    }
    
    std::cout << result << "\n";
}