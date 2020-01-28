# 백준 문제풀이

----------------------------------

### [ 날짜 계산 ](https://www.acmicpc.net/problem/1476)

#### 문제

준규가 사는 나라는 우리가 사용하는 연도와 다른 방식을 이용한다. 준규가 사는 나라에서는 수 3개를 이용해서 연도를 나타낸다. 각각의 수는 지구, 태양, 그리고 달을 나타낸다.

지구를 나타내는 수를 E, 태양을 나타내는 수를 S, 달을 나타내는 수를 M이라고 했을 때, 이 세 수는 서로 다른 범위를 가진다. (1 ≤ E ≤ 15, 1 ≤ S ≤ 28, 1 ≤ M ≤ 19)

우리가 알고있는 1년은 준규가 살고있는 나라에서는 1 1 1로 나타낼 수 있다. 1년이 지날 때마다, 세 수는 모두 1씩 증가한다. 만약, 어떤 수가 범위를 넘어가는 경우에는 1이 된다.

예를 들어, 15년은 15 15 15로 나타낼 수 있다. 하지만, 1년이 지나서 16년이 되면 16 16 16이 아니라 1 16 16이 된다. 이유는 1 ≤ E ≤ 15 라서 범위를 넘어가기 때문이다.

E, S, M이 주어졌고, 1년이 준규가 사는 나라에서 1 1 1일때, 준규가 사는 나라에서 E S M이 우리가 알고 있는 연도로 몇 년인지 구하는 프로그램을 작성하시오.

#### 입력

첫째 줄에 세 수 E, S, M이 주어진다. 문제에 나와있는 범위를 지키는 입력만 주어진다.

#### 입출력 예

```
예제 입력 1

1 16 16

예제 출력 1

16

예제 입력 2

1 1 1

예제 출력 2

1

예제 입력 3

1 2 3

예제 출력 3

5266

예제 입력 4

15 28 19

예제 출력 4

7980
```

#### 풀이
  - BruteForce

```python
if __name__=='__main__' : 
    E,S,M = map(int,raw_input().split(' '))

    x = 1
    while True : 
        if (x-E)%15 == 0 and (x-S)%28 == 0 and  (x-M)%19 == 0 :
            break
        
        x += 1

    print(x)
```

----------------------------------

### [ 최소 스패닝 트리 ](https://www.acmicpc.net/problem/1197)

- 문제

국민대학교 홍보대사 국희는 여름방학을 맞아 고등학생들을 대상으로 학교 내부에 있는 건물을 소개해주는 일을 하게 되어 학교 건물을 차례로 소개할 수 있는 이동 경로를 짜보기로 하였다. 국민대학교는 북한산의 정기를 받는 위치에 있어 건물 간 연결된 길이 험난한 오르막길일 수도 있고, 내리막길일 수도 있다. 국희는 먼저 입구를 기준으로 건물 간 연결된 도로가 오르막길인지, 내리막길인지를 파악하여 오르막길인 경우 점선, 내리막길인 경우 실선으로 표시하였다.

![example](https://onlinejudgeimages.s3-ap-northeast-1.amazonaws.com/problem/13418/F1.png)

건물을 구분하기 쉽도록 번호를 붙였고, 입구에는 숫자 0을 붙이기로 하였다. 그 다음 모든 건물을 방문하는 데 필요한 최소한의 길을 선택하여, 해당 길을 통해서만 건물들을 소개하기로 하였다. 이 과정은 굉장히 신중해야 하는데, 오르막길이 많이 포함되게 되면 굉장히 피곤해지기 때문이다.

얼마나 피곤해지는지 알아보기 위해 피로도를 계산하기로 하였다. 오르막길을 k번 오를 때, 피로도는 k2이 된다. 피로도의 계산은 최초 조사된 길을 기준으로만 한다. 즉, 내리막길로 내려갔다 다시 올라올 때 오르막길이 되는 경우는 고려하지 않는다. 입구는 항상 1번 건물과 연결된 도로를 가지며, 출발은 항상 입구에서 한다.

![example](https://onlinejudgeimages.s3-ap-northeast-1.amazonaws.com/problem/13418/F2.png)

![example](https://onlinejudgeimages.s3-ap-northeast-1.amazonaws.com/problem/13418/F3.png)

그림 1에서 모든 건물을 소개하기 위해 거쳐야 할 최소한의 도로는 4개임을 알 수 있다. 다음 2개의 그림은 그 4개의 도로를 뽑은 각각의 경우이다. 그림 2는 학교를 소개하는 데 총 3개의 오르막길을 오르게 되며 피로도가 9가 되는 최악의 코스가 된다. 그림 3은 오르막길을 1번만 오르게 되므로 학생들의 피로도는 1이 되는 최적의 코스가 된다. 이 경우 최악의 코스와 최적의 코스간 최종 피로도의 차이는 8이 된다. 국희는 최고의 프로그래머인 당신에게 위와 같은 방식으로 최악, 최선의 경로 간 피로도의 차이를 계산하는 프로그램의 제작을 부탁하였다. 프로그램을 작성하여 국희를 도와주자.

- 입력

입력 데이터는 표준 입력을 사용한다. 입력은 1개의 테스트 데이터로 구성된다. 입력의 첫 번째 줄에는 건물의 개수 N(1≤N≤1,000)과 도로의 개수 M(1≤M≤n*(n-1)/2) 이 주어진다. 입력의 두 번째 줄부터 M+1개의 줄에는 A, B(1≤ A,B ≤ N), C 가 주어진다. 이는 A와 B 건물에 연결된 도로가 있다는 뜻이며, C는 0(오르막길) 또는 1(내리막길)의 값을 가진다. 같은 경로 상에 2개 이상의 도로가 주어지는 경우는 없으며, 입구는 항상 1번 건물과 연결되어 있다. 입구와 1번 도로 간의 연결 관계는 항상 2번째 줄에 주어진다. 입구에서 모든 건물로 갈 수 있음이 보장된다.

- 입출력 예

```
#예제 입력 1 
4 5
0 1 1
1 2 0
1 4 0
4 2 1
3 4 1
2 3 0

#예제 출력 1 
8
```

- 풀이
  - Greedy, MST, Kruskal

```C++
bool comp(vector<int>& a, vector<int>& b){
	return a[2] < b[2];
}

// 해당 그래프의 root 찾기 
int findRoot(vector<int>& root, int node){
	if(root[node] == node)
		return node;
		
	return root[node] = findRoot(root, root[node]);
}

// 더 작은 root index로 합치기
void mergeRoot(vector<int>& root, int a, int b){
	a = findRoot(root, a);
	b = findRoot(root, b);

	int max = a > b ? a : b;
	int min = a <= b ? a : b;

	root[max] = min;
}

// kruskal 알고리즘 을 통해 Minimum Spanning Tree를 구함
int solution(const int v, const int e, vector<vector<int>> edge) {
	int maxVal = 0, minVal = 0;
	vector<int> root(v+1, 0);
		
	sort(edge.begin(), edge.end(), comp);

	for(auto i = 0 ; i <= v ; ++i)
		root[i] = i;

	for(auto iter = edge.begin() ; iter != edge.end() ; ++iter){
		int strat = findRoot(root, (*iter)[0]);
		int end = findRoot(root, (*iter)[1]);
		
		if(strat != end){
			root[end] = strat;
			minVal += (*iter)[2];
		}
	}

	for(auto i = 0 ; i <= v ; ++i)
		root[i] = i;

	for(auto iter = edge.rbegin() ; iter != edge.rend() ; ++iter){
		int strat = findRoot(root, (*iter)[0]);
		int end = findRoot(root, (*iter)[1]);
		
		if(strat != end){
			root[end] = strat;
			maxVal += (*iter)[2];
		}
	}

	return (maxVal*maxVal) - (minVal*minVal);
}

int main(int argc, char* argv[]) {
	
	int V = 0, E = 0;
	cin >> V >> E;
	
	vector<vector<int>> edge;

	for(auto i = 0 ; i <= E ; ++i){
		int s = 0, e = 0, v = 0;
		cin >> s >> e >> v;
		
		// 이해하기 쉽도록 
		// 내리막길을 0, 오르막길을 1로 바꿈
		v = v ? 0 : 1;

		edge.push_back({s, e, v});
	}

	std::cout << solution(V, E, edge) << std::endl;
	
	return 0;
}
```

----------------------------------

### [ 최소 스패닝 트리 ](https://www.acmicpc.net/problem/1197)

- 문제

그래프가 주어졌을 때, 그 그래프의 최소 스패닝 트리를 구하는 프로그램을 작성하시오.
최소 스패닝 트리는, 주어진 그래프의 모든 정점들을 연결하는 부분 그래프 중에서 그 가중치의 합이 최소인 트리를 말한다.

- 입력
 
첫째 줄에 정점의 개수 V(1 ≤ V ≤ 10,000)와 간선의 개수 E(1 ≤ E ≤ 100,000)가 주어진다. 다음 E개의 줄에는 각 간선에 대한 정보를 나타내는 세 정수 A, B, C가 주어진다. 이는 A번 정점과 B번 정점이 가중치 C인 간선으로 연결되어 있다는 의미이다. C는 음수일 수도 있으며, 절댓값이 1,000,000을 넘지 않는다.

최소 스패닝 트리의 가중치가 -2147483648보다 크거나 같고, 2147483647보다 작거나 같은 데이터만 입력으로 주어진다.

- 입출력 예

```
#예제 입력 1 
3 3
1 2 1
2 3 2
1 3 3

#예제 출력 1 
3
```

- 풀이
  - Greedy, MST, Kruskal

```C++
bool comp(const vector<int>& a, const vector<int>& b){
	return a[2] < b[2];
}

// 해당 그래프의 root 찾기 
int findRoot(vector<int>& root, int node){
	if(root[node] == node)
		return node;

	root[node] = findRoot(root, root[node]);
	return root[node];
}

// kruskal 알고리즘 을 통해 Minimum Spanning Tree를 구함
int solution(const int v, const int e, vector<vector<int>>& edge) {
	int answer = 0;
	vector<int> root(v+1, 0);
	
	for(auto i = 0 ; i <= v ; ++i)
		root[i] = i;
	
	sort(edge.begin(), edge.end(), comp);

	for(auto& item : edge){
		int a = findRoot(root, item[0]);
		int b = findRoot(root, item[1]);

		if(a != b){
			root[b] = a;
			answer += item[2];
		}
	}

	return answer;
}
```

----------------------------------

