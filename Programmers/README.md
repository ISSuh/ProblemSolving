# 프로그래머스 문제풀이

## 2020

----------------------------------

### [ 길 찾기 게임 ](https://programmers.co.kr/learn/courses/30/lessons/42892) - lv.3

#### 문제

전무로 승진한 라이언은 기분이 너무 좋아 프렌즈를 이끌고 특별 휴가를 가기로 했다. 
내친김에 여행 계획까지 구상하던 라이언은 재미있는 게임을 생각해냈고 역시 전무로 승진할만한 인재라고 스스로에게 감탄했다.
라이언이 구상한(그리고 아마도 라이언만 즐거울만한) 게임은, 카카오 프렌즈를 두 팀으로 나누고, 각 팀이 같은 곳을 다른 순서로 방문하도록 해서 먼저 순회를 마친 팀이 승리하는 것이다.
그냥 지도를 주고 게임을 시작하면 재미가 덜해지므로, 라이언은 방문할 곳의 2차원 좌표 값을 구하고 각 장소를 이진트리의 노드가 되도록 구성한 후, 순회 방법을 힌트로 주어 각 팀이 스스로 경로를 찾도록 할 계획이다.
라이언은 아래와 같은 특별한 규칙으로 트리 노드들을 구성한다.
  - 트리를 구성하는 모든 노드의 x, y 좌표 값은 정수이다.
  - 모든 노드는 서로 다른 x값을 가진다.
  - 같은 레벨(level)에 있는 노드는 같은 y 좌표를 가진다.
  - 자식 노드의 y 값은 항상 부모 노드보다 작다.
  - 임의의 노드 V의 왼쪽 서브 트리(left subtree)에 있는 모든 노드의 x값은 V의 x값보다 작다.
  - 임의의 노드 V의 오른쪽 서브 트리(right subtree)에 있는 모든 노드의 x값은 V의 x값보다 크다.
  
아래 예시를 확인해보자.
라이언의 규칙에 맞게 이진트리의 노드만 좌표 평면에 그리면 다음과 같다. (이진트리의 각 노드에는 1부터 N까지 순서대로 번호가 붙어있다.)

![example](https://grepp-programmers.s3.amazonaws.com/files/production/dbb58728bd/a5371669-54d4-42a1-9e5e-7466f2d7b683.jpg)

이제, 노드를 잇는 간선(edge)을 모두 그리면 아래와 같은 모양이 된다.

![example](https://grepp-programmers.s3.amazonaws.com/files/production/dbb58728bd/a5371669-54d4-42a1-9e5e-7466f2d7b683.jpg)

위 이진트리에서 전위 순회(preorder), 후위 순회(postorder)를 한 결과는 다음과 같고, 이것은 각 팀이 방문해야 할 순서를 의미한다.
  - 전위 순회 : 7, 4, 6, 9, 1, 8, 5, 2, 3
  - 후위 순회 : 9, 6, 5, 8, 1, 4, 3, 2, 7
  
다행히 두 팀 모두 머리를 모아 분석한 끝에 라이언의 의도를 간신히 알아차렸다.

그러나 여전히 문제는 남아있다. 노드의 수가 예시처럼 적다면 쉽게 해결할 수 있겠지만, 예상대로 라이언은 그렇게 할 생각이 전혀 없었다.
이제 당신이 나설 때가 되었다.
곤경에 빠진 카카오 프렌즈를 위해 이진트리를 구성하는 노드들의 좌표가 담긴 배열 nodeinfo가 매개변수로 주어질 때, 
노드들로 구성된 이진트리를 전위 순회, 후위 순회한 결과를 2차원 배열에 순서대로 담아 return 하도록 solution 함수를 완성하자.

#### 제한사항
  - nodeinfo는 이진트리를 구성하는 각 노드의 좌표가 1번 노드부터 순서대로 들어있는 2차원 배열이다.
      - nodeinfo의 길이는 1 이상 10,000 이하이다.
      - nodeinfo[i] 는 i + 1번 노드의 좌표이며, [x축 좌표, y축 좌표] 순으로 들어있다.
      - 모든 노드의 좌표 값은 0 이상 100,000 이하인 정수이다.
      - 트리의 깊이가 1,000 이하인 경우만 입력으로 주어진다.
      - 모든 노드의 좌표는 문제에 주어진 규칙을 따르며, 잘못된 노드 위치가 주어지는 경우는 없다.

#### 입출력 예

| nodeinfo | return |
| -- | -- |
| [[5,3],[11,5],[13,3],[3,5],[6,1],[1,3],[8,6],[7,2],[2,2]] | [[7,4,6,9,1,8,5,2,3],[9,6,5,8,1,4,3,2,7]] |

```
```

#### 풀이1
  - Tree

```C++
class TreeNode{
    friend class Tree;
public:
    TreeNode(int val = 0, int x = 0, int y = 0, TreeNode* left = nullptr, TreeNode* right = nullptr)
     : val(val), x(x), y(y), left(left), right(right) {}
    
private:
    int val;
    int x, y;
    TreeNode* left;
    TreeNode* right;
};

class Tree{
public:
    Tree(int data = 0, int x = 0, int y = 0) : root(new TreeNode(data, x, y)) {}
    
    void insert(TreeNode* node){
        TreeNode* parentNode = nullptr;
        TreeNode* currentNode = root;

        // 삽입할 노드의 부모노드를 찾기위해,
        // 현재가리키는 노드가 리프노드가 될때 까지 검사
        while (currentNode != nullptr) {
            parentNode = currentNode;
            
            // 삽입할 노드의 x좌표가 현재 가리키는 부모노드 보다 작으면 left
            // 삽입할 노드의 x좌표가 현재 가리키는 부모노드 보다 크면 right
            if (node->x < parentNode->x) 
                currentNode = currentNode->left;
            else 
                currentNode = currentNode->right;
        }
        
        // 부모노드를 찾았으므로 조건을 검사하여 left, right위치에 삽입
        if (node->x < parentNode->x) 
            parentNode->left = node;
        else 
            parentNode->right = node;
    }
    
    // PreOrder 조회
    void preOrder(vector<int>& ans, const TreeNode* const node){
        if(node == nullptr)
            return;
        
        ans.push_back(node->val);
        preOrder(ans, node->left);
        preOrder(ans, node->right);
    }
    
    // PostOrder 조회
    void postOrder(vector<int>& ans, const TreeNode* const node){
        if(node == nullptr)
            return;
        
        postOrder(ans, node->left);
        postOrder(ans, node->right);
        ans.push_back(node->val);
    }
    
    const TreeNode* getRoot() const { return root; }
    
private:
    TreeNode* root;
};

bool comp(vector<int>& a, vector<int>& b){
    if(a[1] == b[1])
        return a[0] < b[0];
    return a[1] > b[1];
}

vector<vector<int>> solution(vector<vector<int>> nodeinfo) {
    vector<vector<int>> answer(2);
    vector<vector<int>> item;
    
    // 각 노드의 번호 삽입
    for(auto i = 0 ; i < nodeinfo.size() ; ++i)
        item.push_back({nodeinfo[i][0], nodeinfo[i][1], i+1});
    
    // 좌표순으로 정렬
    sort(item.begin(), item.end(), comp);
    
    // 트리에 삽입
    Tree tree(item[0][2], item[0][0], item[0][1]);
    for(auto i = 1 ; i < item.size() ; ++i){
        tree.insert(new TreeNode(item[i][2], item[i][0], item[i][1]));
    }
    
    // 조회
    tree.preOrder(answer[0], tree.getRoot());
    tree.postOrder(answer[1], tree.getRoot());

    return answer;
}
```

----------------------------------

### [ 라면공장 ](https://programmers.co.kr/learn/courses/30/lessons/42629#) - lv.2

#### 문제

라면 공장에서는 하루에 밀가루를 1톤씩 사용합니다. 원래 밀가루를 공급받던 공장의 고장으로 앞으로 k일 이후에야 밀가루를 공급받을 수 있기 때문에 해외 공장에서 밀가루를 수입해야 합니다.
해외 공장에서는 향후 밀가루를 공급할 수 있는 날짜와 수량을 알려주었고, 라면 공장에서는 운송비를 줄이기 위해 최소한의 횟수로 밀가루를 공급받고 싶습니다.
현재 공장에 남아있는 밀가루 수량 stock, 밀가루 공급 일정(dates)과 해당 시점에 공급 가능한 밀가루 수량(supplies), 원래 공장으로부터 공급받을 수 있는 시점 k가 주어질 때, 밀가루가 떨어지지 않고 공장을 운영하기 위해서 최소한 몇 번 해외 공장으로부터 밀가루를 공급받아야 하는지를 return 하도록 solution 함수를 완성하세요.
dates[i]에는 i번째 공급 가능일이 들어있으며, supplies[i]에는 dates[i] 날짜에 공급 가능한 밀가루 수량이 들어 있습니다.

#### 제한사항
  - stock에 있는 밀가루는 오늘(0일 이후)부터 사용됩니다.
  - stock과 k는 2 이상 100,000 이하입니다.
  - dates의 각 원소는 1 이상 k 이하입니다.
  - supplies의 각 원소는 1 이상 1,000 이하입니다.
  - dates와 supplies의 길이는 1 이상 20,000 이하입니다.
  - k일 째에는 밀가루가 충분히 공급되기 때문에 k-1일에 사용할 수량까지만 확보하면 됩니다.
  - dates에 들어있는 날짜는 오름차순 정렬되어 있습니다.
  - dates에 들어있는 날짜에 공급되는 밀가루는 작업 시작 전 새벽에 공급되는 것을 기준으로 합니다. 예를 들어 9일째에 밀가루가 바닥나더라도, 10일째에 공급받으면 10일째에는 공장을 운영할 수 있습니다.
  - 밀가루가 바닥나는 경우는 주어지지 않습니다.

#### 입출력 예

| stock | dates |	supplies | k | return |
| -- | -- | -- | -- | -- |
| 4	| [4,10,15] | [20,5,10] | 30 | 2 |

```
입출력 예 #1
  - 현재 밀가루가 4톤 남아 있기 때문에 오늘과 1일 후~3일 후까지 사용하고 나면 모든 밀가루를 다 사용합니다. 따라서 4일 후에는 반드시 밀가루를 공급받아야 합니다.
  - 4일째 공급받고 나면 15일 이후 아침에는 9톤의 밀가루가 남아있게 되고, 이때 10톤을 더 공급받으면 19톤이 남아있게 됩니다. 15일 이후부터 29일 이후까지 필요한 밀가루는 15톤이므로 더 이상의 공급은 필요 없습니다.
  - 따라서 총 2회의 밀가루를 공급받으면 됩니다.
```

#### 풀이
  - Heap

```C++
int solution(int stock, vector<int> dates, vector<int> supplies, int k) {
    int answer = 0;
    int index = 0; 
    priority_queue<int, vector<int>, less<int>> pq;
    
    // 하루씩 k일 까지 날짜를 증가시킴
    // heap을 통해, 보급받은 수량이 가장 큰 것을 선택해 나감 
    for(auto day = 0 ; day < k ; ++day){
        // 현재 날짜가 dates[index]의 날짜와 같다면
        // heap에 해당 날짜의 공급량을 저장하며 index를 하나 증가
        if(dates[index] == day){
            pq.push(supplies[index]);
            ++index;
        }
        
        // 현재 남아있는 수량이 바닥나면,
        // heap에 저장되어 있는 최대 수량만큼 채움고,
        // 보급받은 횟수 +1
        if(stock == 0){
            stock = pq.top();
            pq.pop();
            ++answer;
        }
        
        --stock;
    }
    
    return answer;
}
```

----------------------------------

### [ N-Queen ](https://programmers.co.kr/learn/courses/30/lessons/12952) - lv.3

#### 문제

가로, 세로 길이가 n인 정사각형으로된 체스판이 있습니다. 체스판 위의 n개의 퀸이 서로를 공격할 수 없도록 배치하고 싶습니다.
예를 들어서 n이 4인경우 다음과 같이 퀸을 배치하면 n개의 퀸은 서로를 한번에 공격 할 수 없습니다.

![example](https://i.imgur.com/lt2zdK6.png)

![example](https://i.imgur.com/5c5EUrq.png)

체스판의 가로 세로의 세로의 길이 n이 매개변수로 주어질 때, n개의 퀸이 조건에 만족 하도록 배치할 수 있는 방법의 수를 return하는 solution함수를 완성해주세요.

#### 제한사항
  - 퀸(Queen)은 가로, 세로, 대각선으로 이동할 수 있습니다.
  - n은 12이하의 자연수 입니다.

#### 입출력 예

| n | return |
| -- | -- |
| 4 | 2 | 

```
입출력 예 #1
문제의 예시와 같습니다.
```

#### 풀이
  - Back Tracking

```C++
void BackTracking(int& res, int n, vector<vector<bool>>& board, pair<int,int> point){
    // 열 index가 n과 같아지면 만족하는 경우를 찾았다는 뜻
    if(point.first == n){
        ++res;
        return;
    }
    
    // 현재 행에서 만족하는 좌표 검사 
    for(auto i = 0 ; i < n ; ++i){
        // 이전의 퀸에의해 해당 좌표가 가능한지 불가능한지 검사
        if(board[point.first][i]){
            auto check = board;
            check[point.first][i] = false;
            
            // 현재 좌표에 다음퀸이 올때, 보드에서 불가능한 부분 체크
            int right = i;
            int left = i;
            for(auto y = point.first + 1 ; y < n ; ++y){
                check[y][i] = false;

                if(right + 1 < n)
                    check[y][++right] = false;

                if(0 <= left - 1)
                    check[y][--left] = false;
            }

            // 퀸을 위치 시킨후 다음 행으로 이동
            BackTracking(res, n, check, {point.first+1, 0});
        }
    }
}

int solution(int n) {
    int answer = 0;
    vector<vector<bool>> board(n, vector<bool>(n, true));
    
    BackTracking(answer, n ,board, {0, 0});
        
    return answer;
}
```

----------------------------------

### [ 방문 길이 ](https://programmers.co.kr/learn/courses/30/lessons/49994#) - lv.3

#### 문제

게임 캐릭터를 4가지 명령어를 통해 움직이려 합니다. 명령어는 다음과 같습니다.
U: 위쪽으로 한 칸 가기
D: 아래쪽으로 한 칸 가기
R: 오른쪽으로 한 칸 가기
L: 왼쪽으로 한 칸 가기
캐릭터는 좌표평면의 (0, 0) 위치에서 시작합니다. 좌표평면의 경계는 왼쪽 위(-5, 5), 왼쪽 아래(-5, -5), 오른쪽 위(5, 5), 오른쪽 아래(5, -5)로 이루어져 있습니다.

![example](https://res.cloudinary.com/jistring93/image/upload/v1495542181/방문길이1_qpp9l3.png)

예를 들어, ULURRDLLU로 명령했다면

![example](https://res.cloudinary.com/jistring93/image/upload/v1495542443/방문길이2_lezmdo.png)

- 1번 명령어부터 7번 명령어까지 다음과 같이 움직입니다.

![example](https://res.cloudinary.com/jistring93/image/upload/v1495542704/방문길이3_sootjd.png)

- 8번 명령어부터 9번 명령어까지 다음과 같이 움직입니다.

![example](https://res.cloudinary.com/jistring93/image/upload/v1495542767/방문길이4_hlpiej.png)

이때, 우리는 게임 캐릭터가 지나간 길 중 캐릭터가 처음 걸어본 길의 길이를 구하려고 합니다. 예를 들어 위의 예시에서 게임 캐릭터가 움직인 길이는 9이지만, 캐릭터가 처음 걸어본 길의 길이는 7이 됩니다. (8, 9번 명령어에서 움직인 길은 2, 3번 명령어에서 이미 거쳐 간 길입니다)
단, 좌표평면의 경계를 넘어가는 명령어는 무시합니다.
예를 들어, LULLLLLLU로 명령했다면

![example](https://res.cloudinary.com/jistring93/image/upload/v1495545063/방문길이5_nitjwj.png)

- 1번 명령어부터 6번 명령어대로 움직인 후, 7, 8번 명령어는 무시합니다. 다시 9번 명령어대로 움직입니다.

![example](https://res.cloudinary.com/jistring93/image/upload/v1495544946/방문길이6_nzhumd.png)

이때 캐릭터가 처음 걸어본 길의 길이는 7이 됩니다.
명령어가 매개변수 dirs로 주어질 때, 게임 캐릭터가 처음 걸어본 길의 길이를 구하여 return 하는 solution 함수를 완성해 주세요.

#### 제한사항
  - dirs는 string형으로 주어지며, 'U', 'D', 'R', 'L' 이외에 문자는 주어지지 않습니다.
  - dirs의 길이는 500 이하의 자연수입니다.

#### 입출력 예

| dirs | return |
| -- | -- |
| "ULURRDLLU" | 7 | 
| "LULLLLLLU" | 7 | 

```
입출력 예 #1
문제의 예시와 같습니다.

입출력 예 #2
문제의 예시와 같습니다.
```

#### 풀이
  - Brute Force

```C++
int solution(string dirs) {
	int answer = 0;
    int len = dirs.size(); 
    set<pair<pair<int,int>,pair<int,int>>> path;
    pair<int, int> now = {0, 0};
    
    // 현재좌표 -> 다음좌표 / 다음좌표 -> 현재좌표
    // 이 두가지 경로를 저장하여 지나온길인지, 새로운길인지 판단
    for(auto i = 0 ; i < len ; ++i){
        // 다음좌표값을 구함
        auto next = now;
        if(dirs[i] == 'U' && now.second+1 <= 5){
            next = {now.first, now.second+1};
        }
        else if(dirs[i] == 'D' && -5 <= now.second-1){
            next = {now.first, now.second-1};
        }
        else if(dirs[i] == 'L' && -5 <= now.first-1){
            next = {now.first-1, now.second};
        }
        else if(dirs[i] == 'R' && now.first+1 <= 5){
            next = {now.first+1, now.second};
        }
        
        // 현재좌표와 다음좌표가 같으면 좌표를 전체좌표에 벗어난 것이므로 무시
        if(now == next)
            continue; 
        
        // 현재좌표 -> 다음좌표 / 다음좌표 -> 현재좌표
        // 이 두가지 경우가 모두 없다면 새로 지나온길
        if(path.find({now, next}) == path.end() && path.find({next, now}) == path.end()){
            ++answer;

            path.insert({now, next});
            path.insert({next, now});
        }
        
        // 다음좌표값을 현재좌표로 저장
        now = next;
    }
        
    return answer;
}
```

----------------------------------

### [  줄 서는 방법 ](https://programmers.co.kr/learn/courses/30/lessons/12936) - lv.3

- 문제

n명의 사람이 일렬로 줄을 서고 있습니다. n명의 사람들에게는 각각 1번부터 n번까지 번호가 매겨져 있습니다. n명이 사람을 줄을 서는 방법은 여러가지 방법이 있습니다. 예를 들어서 3명의 사람이 있다면 다음과 같이 6개의 방법이 있습니다.

    [1, 2, 3]
    [1, 3, 2]
    [2, 1, 3]
    [2, 3, 1]
    [3, 1, 2]
    [3, 2, 1]

사람의 수 n과, 자연수 k가 주어질 때, 사람을 나열 하는 방법을 사전 순으로 나열 했을 때, k번째 방법을 return하는 solution 함수를 완성해주세요.


- 제한사항
  - n은 20이하의 자연수 입니다.
  - k는 n! 이하의 자연수 입니다.

- 입출력 예

| n | k| return |
| -- | -- | -- |
| 3 | 5 | [3,1,2] | 

- 풀이
  - Greedy

```C++
vector<int> solution(int n, long long k) {
    vector<int> answer;
    vector<int> item(n + 1, 1);
    vector<long long> mul(n + 1 ,1);

    // n 까지의 값과 n 까지의 factoral를 저장
    for(auto i = 1 ; i <= n ; ++i){
        item[i] = i;
        mul[i] = mul[i-1] * i;
    }
    
    // 구하고자하는 자리수의 값을 mul[i-1]으로 나눈 몫의 인덱스 값이 해당 자리의 값
    // 다음자리의 자리수 값은  현재 자리수 % mul[i-1] 임
    long long val = k - 1;
    for(auto i = n ; i > 1 ; --i){
        auto share = val / mul[i-1];
        val %= mul[i-1];        
        
        answer.push_back(*(item.begin() + 1 + share));
        item.erase(item.begin() + 1 + share);
    }
    
    answer.push_back(item.back());
    
    return answer;
}
```

----------------------------------

### [ 거스름돈 ](https://programmers.co.kr/learn/courses/30/lessons/12907) - lv.3

- 문제

Finn은 편의점에서 야간 아르바이트를 하고 있습니다. 야간에 손님이 너무 없어 심심한 Finn은 손님들께 거스름돈을 n 원을 줄 때 방법의 경우의 수를 구하기로 하였습니다.

예를 들어서 손님께 5원을 거슬러 줘야 하고 1원, 2원, 5원이 있다면 다음과 같이 4가지 방법으로 5원을 거슬러 줄 수 있습니다.

    1원을 5개 사용해서 거슬러 준다.
    1원을 3개 사용하고, 2원을 1개 사용해서 거슬러 준다.
    1원을 1개 사용하고, 2원을 2개 사용해서 거슬러 준다.
    5원을 1개 사용해서 거슬러 준다.

거슬러 줘야 하는 금액 n과 Finn이 현재 보유하고 있는 돈의 종류 money가 매개변수로 주어질 때, Finn이 n 원을 거슬러 줄 방법의 수를 return 하도록 solution 함수를 완성해 주세요.


- 제한사항
  - n은 100,000 이하의 자연수입니다.
  - 화폐 단위는 100종류 이하입니다.
  - 모든 화폐는 무한하게 있다고 가정합니다.
  - 정답이 커질 수 있으니, 1,000,000,007로 나눈 나머지를 return 해주세요.

- 입출력 예

| s | money| return |
| -- | -- | -- |
| 5 | [1,2,5] | 4 | 

- 풀이
  - DP

```C++
int solution(int n, vector<int> money) {
    vector<int> item(n+1, 0);
    
    item[0] = 1;
    // 현재 선택한 동전으로 만들수 있는 거스름돈 조사
	for (int& i : money){
        // 현재 선택된 동전으로 만들수 있는 거스름돈은
        // (현재 선택된 동전의 금액) ~ n * (현재 선택된 동전의 금액) 이며,
        // 현재 선택된 동전으로 만들수 있는 현재 금액의 거스름돈은, 
        // item[현재금액 - 현재선택된동전] 임. 예시로,
        // 현재 선택된 동전이 2일때, 최소 2부터 시작되며,
        // 만들수 있는 금액은 2,4,6,8,10,... 순으로, 현재 금액과 다음 금액의 차이는 2만큼 차이남
        // 전체 동전으로 만들수 있는 수를 구해야 하므로 매번 이전 금액의 수와 더해나감
        // 즉, item[현재금액] = item[현재금액 - 현재선택된 동전] + item[현재금액] 
		for (int j = i; j <= n; j++){
			item[j] += item[j - i];
        }
    }
    return item[n];
}
```

----------------------------------

### [ 가장 긴 팰린드롬 ](https://programmers.co.kr/learn/courses/30/lessons/12904) - lv.3

- 문제

앞뒤를 뒤집어도 똑같은 문자열을 팰린드롬(palindrome)이라고 합니다.
문자열 s가 주어질 때, s의 부분문자열(Substring)중 가장 긴 팰린드롬의 길이를 return 하는 solution 함수를 완성해 주세요.
예를들면, 문자열 s가 abcdcba이면 7을 return하고 abacde이면 3을 return합니다.

- 제한사항
  - 문자열 s의 길이 : 2,500 이하의 자연수
  - 문자열 s는 알파벳 소문자로만 구성

- 입출력 예

| s | return |
| -- | -- |
| "abcdcba" | 7 |
| "abacde" | 3 |

```
입출력 예 #1
	- 4번째자리 'd'를 기준으로 문자열 s 전체가 팰린드롬이 되므로 7을 return합니다.
입출력 예 #2
	- 2번째자리 'b'를 기준으로 aba가 팰린드롬이 되므로 3을 return합니다.
```

- 풀이
  - string

```C++
// 문자열의 길이가 홀수인 펠린드롬 찾기
int oddBasedPalindrome(const string& s){
    int answer = 1;
    int len = s.size();

    for(auto i = 1 ; i < len - 1 ; ++i){      
        // 인덱스 i를 기준으로 양옆의 문자가 같은지 판단
        int left = i - 1;
        int right = i + 1;
        int count = 1;
        
        // 양옆이 같으면 각 왼쪽, 오른쪽의 인덱스를
        // 1씩 증가시키면서 최대 펠린드롬 찾기
        while(left >= 0 && right < len){
            if(s[left] == s[right]){
                count += 2;
                --left;
                ++right;
            }
            else
                break;
        }
        
        answer = max(answer, count);
    }
    
    return answer;
}

// 문자열의 길이가 짝수인 펠린드롬 찾기
int evenBasedPalindrome(const string& s){
    int answer = 1;
    int len = s.size();

    for(auto i = 0 ; i < len - 1 ; ++i){
        // 인덱스 i를 기준으로 양옆의 문자가 같은지 판단
        int left = i;
        int right = i + 1;
        int count = 0;

        // 양옆이 같으면 각 왼쪽, 오른쪽의 인덱스를
        // 1씩 증가시키면서 최대 펠린드롬 찾기
        while(left >= 0 && right < len){
            if(s[left] == s[right]){
                count += 2;
                --left;
                ++right;
            }
            else
                break;
        }
        
        answer = max(answer, count);
    }
    
    return answer;
}

int solution(string s)
{
    int answer = max(evenBasedPalindrome(s), oddBasedPalindrome(s));
    return answer;
}
```

----------------------------------

### [ 최고의 집합 ](https://programmers.co.kr/learn/courses/30/lessons/12938#) - lv.3

- 문제

자연수 n 개로 이루어진 중복 집합(multi set, 편의상 이후에는 집합으로 통칭) 중에 다음 두 조건을 만족하는 집합을 최고의 집합이라고 합니다.

1. 각 원소의 합이 S가 되는 수의 집합
2. 위 조건을 만족하면서 각 원소의 곱 이 최대가 되는 집합

예를 들어서 자연수 2개로 이루어진 집합 중 합이 9가 되는 집합은 다음과 같이 4개가 있습니다.
{ 1, 8 }, { 2, 7 }, { 3, 6 }, { 4, 5 }
그중 각 원소의 곱이 최대인 { 4, 5 }가 최고의 집합입니다.
집합의 원소의 개수 n과 모든 원소들의 합 s가 매개변수로 주어질 때, 최고의 집합을 return 하는 solution 함수를 완성해주세요.

- 제한사항
  - 최고의 집합은 오름차순으로 정렬된 1차원 배열(list, vector) 로 return 해주세요.
  - 만약 최고의 집합이 존재하지 않는 경우에 크기가 1인 1차원 배열(list, vector) 에 -1 을 채워서 return 해주세요.
  - 자연수의 개수 n은 1 이상 10,000 이하의 자연수입니다.
  - 모든 원소들의 합 s는 1 이상, 100,000,000 이하의 자연수입니다.

- 입출력 예

| n | s | return |
| -- | -- | -- |
| 2 | 9 | [4, 5] |
| 2 | 1 | [-1] |
| 2 | 8 | [4, 4] |

```
입출력 예#1
	- 문제의 예시와 같습니다.
입출력 예#2
	- 자연수 2개를 가지고는 합이 1인 집합을 만들 수 없습니다. 따라서 -1이 들어있는 배열을 반환합니다.
입출력 예#3
	- 자연수 2개로 이루어진 집합 중 원소의 합이 8인 집합은 다음과 같습니다.
	{ 1, 7 }, { 2, 6 }, { 3, 4 }, { 4, 4 }
	그중 각 원소의 곱이 최대인 { 4, 4 }가 최고의 집합입니다.
```

- 풀이
  - Greedy

```C++
vector<int> solution(int n, int s) {
    // 각 원소의 합이 S가 되는 수의 집합중, 원소의 곱이 가장크게 되려면
    // 각 원소의 값이 최대한 균등하게 분배되어 있어야 함
    // 따라서 s를 n으로 나눈 몫을 전체 배열로 초기화 시킨다음,
    // s를 n으로 나눈 나머지를 균등하게 1씩 배열의 원소에 더해줌
    int carry = s / n;
    int count = s % n;
    vector<int> answer(n, carry);

    for(auto i = 0 ; i < count ; ++i)
        ++answer[n - i - 1];
    
    if(carry)
        return answer;
    
    return {-1};
}
```

----------------------------------

### [ 저울 ](https://programmers.co.kr/learn/courses/30/lessons/42886#) - lv.3

- 문제

하나의 양팔 저울을 이용하여 물건의 무게를 측정하려고 합니다. 이 저울의 양팔의 끝에는 물건이나 추를 올려놓는 접시가 달려 있고, 양팔의 길이는 같습니다. 또한, 저울의 한쪽에는 저울추들만 놓을 수 있고, 다른 쪽에는 무게를 측정하려는 물건만 올려놓을 수 있습니다.

![example](https://grepp-programmers.s3.amazonaws.com/files/production/f73e61d4de/f4abf5ff-1956-4e49-bd4a-d3d24619bbf0.png)

저울추가 담긴 배열 weight가 매개변수로 주어질 때, 이 추들로 측정할 수 없는 양의 정수 무게 중 최솟값을 return 하도록 solution 함수를 작성해주세요.
예를 들어, 무게가 각각 [3, 1, 6, 2, 7, 30, 1]인 7개의 저울추를 주어졌을 때, 이 추들로 측정할 수 없는 양의 정수 무게 중 최솟값은 21입니다.

- 제한사항
  - 저울추의 개수는 1개 이상 10,000개 이하입니다.
  - 각 추의 무게는 1 이상 1,000,000 이하입니다.

- 입출력 예

| weight | return |
| -- | -- |
| [3, 1, 6, 2, 7, 30, 1] | 21 |

- 풀이
  - Greedy

```C++
int solution(vector<int> weight) {
    int answer = 0;
    
    sort(weight.begin(), weight.end());
    answer = weight[0];
    
    // 정렬후, 요소들의 순서대로 합했을때, 표현할 수 있는 무게는
    // weight[0] ~ weight[i-1] 까지의 합 까지 표현 할수 있음
    // 즉,
    //
    // ((weight[0] ~ weight[i-1] 까지의 합) + 1) >= weight[i] 이면,
    // 초기값 ~ (weight[0] ~ weight[i-1] 까지의 합)의 무게를 모두 표현가능함
    //
    // ((weight[0] ~ weight[i-1] 까지의 합) + 1) < weight[i] 이면,
    // 초기값 ~ (weight[0] ~ weight[i-1] 까지의 합)과 weight[i]사이의 값은
    // 표현할 수 없다.
    for(auto i = 0 ; i < weight.size() ; ++i){
        if(answer+1 < weight[i]){
            break;
        }
        
        answer += weight[i];
    }
    
    return answer;
}
```

----------------------------------

### [ 섬 연결하기 ](https://programmers.co.kr/learn/courses/30/lessons/42861) - lv.3

- 문제

n개의 섬 사이에 다리를 건설하는 비용(costs)이 주어질 때, 최소의 비용으로 모든 섬이 서로 통행 가능하도록 만들 때 필요한 최소 비용을 return 하도록 solution을 완성하세요.
다리를 여러 번 건너더라도, 도달할 수만 있으면 통행 가능하다고 봅니다. 예를 들어 A 섬과 B 섬 사이에 다리가 있고, B 섬과 C 섬 사이에 다리가 있으면 A 섬과 C 섬은 서로 통행 가능합니다.

- 제한사항
  - 섬의 개수 n은 1 이상 100 이하입니다.
  - costs의 길이는 ((n-1) * n) / 2이하입니다.
  - 임의의 i에 대해, costs[i][0] 와 costs[i] [1]에는 다리가 연결되는 두 섬의 번호가 들어있고, costs[i] [2]에는 이 두 섬을 연결하는 다리를 건설할 때 드는 비용입니다.
  - 같은 연결은 두 번 주어지지 않습니다. 또한 순서가 바뀌더라도 같은 연결로 봅니다. 즉 0과 1 사이를 연결하는 비용이 주어졌을 때, 1과 0의 비용이 주어지지 않습니다.
  - 모든 섬 사이의 다리 건설 비용이 주어지지 않습니다. 이 경우, 두 섬 사이의 건설이 불가능한 것으로 봅니다.
  - 연결할 수 없는 섬은 주어지지 않습니다.

- 입출력 예

| n | costs | return |
| -- | -- | -- |
| 4 | [[0,1,1],[0,2,2],[1,2,5],[1,3,1],[2,3,8]]	| 4 |

```
costs를 그림으로 표현하면 다음과 같으며, 이때 초록색 경로로 연결하는 것이 가장 적은 비용으로 모두를 통행할 수 있도록 만드는 방법입니다.
```
![example](https://grepp-programmers.s3.amazonaws.com/files/production/13e2952057/f2746a8c-527c-4451-9a73-42129911fe17.png)

- 풀이
  - DFS, BFS, MST, Kruskal

```C++
// cost가 작은순으로 정렬
bool comp(const vector<int>& a, const vector<int>& b){
    return a[2] < b[2];
}

// 부모노드 찾기
int getParent(vector<int>& parent, int node){
    if(parent[node] == node)
        return node;
    
    return parent[node] = getParent(parent, parent[node]);
}

// 작은 부모노드의 번호로 합치기
void unionParent(vector<int>& parent, int a, int b){
    a = getParent(parent, a);
    b = getParent(parent, b);
    
    int max = a > b ? a : b;
    int min = a <= b ? a : b;
    
    parent[max] = min;
}

// 부모노드 검사를 통해 사이클이 이루어지는지 검사
bool checkCycle(vector<int>& parent, int a, int b){
    a = getParent(parent, a);
    b = getParent(parent, b);
    
    if(a == b)  
        return true;
    else        
        return false;
}

int solution(int n, vector<vector<int>> costs) {
    int answer = 0;
    vector<vector<int>> g(n, vector<int>(n, 0));
    vector<int> parent(n, 0);

    for(auto i = 0 ; i < n ; ++i)
         parent[i] = i;
    
    sort(costs.begin(), costs.end(), comp);
    
    // kruskal 알고리즘을 통해 
    // minimum spanning tree(MST)를 구함
    for(auto i = 0 ; i < costs.size() ; ++i){
        if(!checkCycle(parent, costs[i][0], costs[i][1])){
            answer += costs[i][2];
            unionParent(parent, costs[i][0],costs[i][1]);
        }
    }

    return answer;
}
```

----------------------------------

### [  야근 지수 ](https://programmers.co.kr/learn/courses/30/lessons/12927) - lv.3

- 문제

회사원 Demi는 가끔은 야근을 하는데요, 야근을 하면 야근 피로도가 쌓입니다. 야근 피로도는 야근을 시작한 시점에서 남은 일의 작업량을 제곱하여 더한 값입니다. Demi는 N시간 동안 야근 피로도를 최소화하도록 일할 겁니다.Demi가 1시간 동안 작업량 1만큼을 처리할 수 있다고 할 때, 퇴근까지 남은 N 시간과 각 일에 대한 작업량 works에 대해 야근 피로도를 최소화한 값을 리턴하는 함수 solution을 완성해주세요.

- 제한사항
  - works는 길이 1 이상, 20,000 이하인 배열입니다.
  - works의 원소는 50000 이하인 자연수입니다.
  - n은 1,000,000 이하인 자연수입니다.

- 입출력 예

| works | n | return |
| -- | -- | -- |
| [4, 3, 3] | 4 | 12 |
| [2, 1, 2] | 1 | 6 |
| [1,1] | 3 | 0 |

- 풀이
  - Greedy

```C++
long long solution(int n, vector<int> works) {
    long long answer = 0;
    priority_queue<int, vector<int>, less<int>> pq;
    
    for(auto& i : works)
        pq.push(i);
    
    // n만큼 반복하며 현재 works중 가장 큰수를 골라 -1 함
    // 가장 큰수가 0 일땐 모든수가 0이므로 빠져나옴
    // priority queue를 이용하여 구성
    while(n--){
        auto max = pq.top();
        pq.pop();
        
        if(max == 0)
            break;
        
        pq.push(--max);
    }
    
    while(!pq.empty()){
        auto val = pq.top();
        pq.pop();
        
        answer += val * val;
    }
    
    return answer;
}
```

----------------------------------

### [ 멀리 뛰기 ](https://programmers.co.kr/learn/courses/30/lessons/12914) - lv.3

- 문제

효진이는 멀리 뛰기를 연습하고 있습니다. 효진이는 한번에 1칸, 또는 2칸을 뛸 수 있습니다. 칸이 총 4개 있을 때, 효진이는
(1칸, 1칸, 1칸, 1칸)
(1칸, 2칸, 1칸)
(1칸, 1칸, 2칸)
(2칸, 1칸, 1칸)
(2칸, 2칸)
의 5가지 방법으로 맨 끝 칸에 도달할 수 있습니다. 멀리뛰기에 사용될 칸의 수 n이 주어질 때, 효진이가 끝에 도달하는 방법이 몇 가지인지 알아내, 여기에 1234567를 나눈 나머지를 리턴하는 함수, solution을 완성하세요. 예를 들어 4가 입력된다면, 5를 return하면 됩니다.

- 제한사항
  - n은 1 이상, 2000 이하인 정수입니다.

- 입출력 예

| m | return |
| -- | -- |
| 4 | 5 |
| 3 | 3 |

- 풀이
  - DP

```C++
long long solution(int n) {
    if(n <= 1)
        return 1;
    
    long long answer = 1;
    long long preVal = 0;
    
    // i = (i -1) + (i -2)
    for(auto i = 1 ; i <= n ; ++i){
        auto nextVal = answer + preVal;
        preVal = answer;
        answer = nextVal % 1234567;
    }
    
    return answer;
}
```

----------------------------------

### [ 카카오프렌즈 컬러링북 ](https://programmers.co.kr/learn/courses/30/lessons/1829#) - lv.2

- 문제

출판사의 편집자인 어피치는 네오에게 컬러링북에 들어갈 원화를 그려달라고 부탁하여 여러 장의 그림을 받았다. 여러 장의 그림을 난이도 순으로 컬러링북에 넣고 싶었던 어피치는 영역이 많으면 색칠하기가 까다로워 어려워진다는 사실을 발견하고 그림의 난이도를 영역의 수로 정의하였다. (영역이란 상하좌우로 연결된 같은 색상의 공간을 의미한다.)
그림에 몇 개의 영역이 있는지와 가장 큰 영역의 넓이는 얼마인지 계산하는 프로그램을 작성해보자.

![example](http://t1.kakaocdn.net/codefestival/apeach.png)

위의 그림은 총 12개 영역으로 이루어져 있으며, 가장 넓은 영역은 어피치의 얼굴면으로 넓이는 120이다.

- 제한사항
  - 입력은 그림의 크기를 나타내는 m과 n, 그리고 그림을 나타내는 m × n 크기의 2차원 배열 picture로 주어진다. 
	- 1 <= m, n <= 100
	- picture의 원소는 0 이상 2^31 - 1 이하의 임의의 값이다.
	- picture의 원소 중 값이 0인 경우는 색칠하지 않는 영역을 뜻한다.

- 입출력 예

| m | n | picture | return |
| -- | -- | -- | -- |
| 6 | 4 | [[1, 1, 1, 0], [1, 2, 2, 0], [1, 0, 0, 1], [0, 0, 0, 1], [0, 0, 0, 3], [0, 0, 0, 3]] | [4,5] |

- 풀이
  - BFS, DFS

```C++
vector<int> solution(int m, int n, vector<vector<int>> picture) {
    int number_of_area = 0;
    int max_size_of_one_area = 0;
    
    vector<vector<bool>> checker(m, vector<bool>(n, false));
    
    for(auto i = 0 ; i < m ; ++i){  
        for(auto j = 0 ; j < n ; ++j){
            // 현재 인덱스의 체커가 true 거나 색이 0 이면 패스
            if(checker[i][j] || !picture[i][j])
                continue;
            
            // BFS
            // 저장할 pair의 정보는 {행 index, 열 index}
            int count = 0;
            queue<pair<int, int>> q;
            q.push({i,j});
            
            while(!q.empty()){
                auto curPic = q.front();
                q.pop();
                                        
                // 이미 체크되어있거나, 색이 다르면 패스
                if(checker[curPic.first][curPic.second] || picture[curPic.first][curPic.second] != picture[i][j])
                    continue;
                
                // 현재 인덱스 체크 및 영역 수 증가
                checker[curPic.first][curPic.second] = true;
                count++;
                
                // 위 검사
                if(curPic.first + 1 < m)
                    q.push({curPic.first+1, curPic.second});
                // 아래 검사
                if(curPic.first - 1 >= 0) 
                    q.push({curPic.first-1, curPic.second});
                // 오른쪽 검사
                if(curPic.second + 1 < n)
                    q.push({curPic.first, curPic.second+1});
                // 왼쪽 검사
                if(curPic.second - 1 >= 0)
                    q.push({curPic.first, curPic.second-1});
            }
            
            ++number_of_area;
            max_size_of_one_area = max(count, max_size_of_one_area);
        }
    }
    
    return {number_of_area, max_size_of_one_area};
}
```

----------------------------------

### [ 큰 수 만들기 ](https://programmers.co.kr/learn/courses/30/lessons/42883#) - lv.2

- 문제

어떤 숫자에서 k개의 수를 제거했을 때 얻을 수 있는 가장 큰 숫자를 구하려 합니다.
예를 들어, 숫자 1924에서 수 두 개를 제거하면 [19, 12, 14, 92, 94, 24] 를 만들 수 있습니다. 이 중 가장 큰 숫자는 94 입니다.
문자열 형식으로 숫자 number와 제거할 수의 개수 k가 solution 함수의 매개변수로 주어집니다. number에서 k 개의 수를 제거했을 때 만들 수 있는 수 중 가장 큰 숫자를 문자열 형태로 return 하도록 solution 함수를 완성하세요.

- 제한사항
  - number는 1자리 이상, 1,000,000자리 이하인 숫자입니다.
  - k는 1 이상 number의 자릿수 미만인 자연수입니다.

- 입출력 예

| number | k | return |
| -- | -- | -- |
| "1924" | 2 | "94" |
| "1231234" | 3 | "3234" |
| "4177252841" | 4 | "775841" |

- 풀이
  - Greedy

```C++
string solution(string number, int k) {
    int index = 1;
    
    while(k && index < number.size()){
        // index의 값과 index-1의 값을 비교하여
        // index-1값이 작으면 index-1의 원소를 제거
        // 제거후 전체 크기가 -1 만큼 줄어드므로,
        // 현재 index의 -1을 하여 재 비교가 될수 있도록 함
        if(index > 0 && number[index-1] < number[index]){
            number.erase(number.begin()+(index-1));
            --k;
            --index;
        }
        
        // 마지막 원소에서 까지 k만큼 제거가 안됬다면,
        // 마지막 원소부터 지우기 시작
        // 이때 index값과 index-1의 값을 비교하여 
        // index값이 작으면 index의 원소를 제거
        else if(index == number.size()-1 && number[index] <= number[index-1]){
            number.erase(number.begin()+index);
            --k;
            --index;
        }
        else{
            ++index;
        }        
    }
    
    return number;
}
```

----------------------------------

### [ N개의 최소공배수 ](https://programmers.co.kr/learn/courses/30/lessons/12953) - lv.2

- 문제

두 수의 최소공배수(Least Common Multiple)란 입력된 두 수의 배수 중 공통이 되는 가장 작은 숫자를 의미합니다. 예를 들어 2와 7의 최소공배수는 14가 됩니다. 정의를 확장해서, n개의 수의 최소공배수는 n 개의 수들의 배수 중 공통이 되는 가장 작은 숫자가 됩니다. n개의 숫자를 담은 배열 arr이 입력되었을 때 이 수들의 최소공배수를 반환하는 함수, solution을 완성해 주세요.

- 제한사항
  - arr은 길이 1이상, 15이하인 배열입니다.
  - arr의 원소는 100 이하인 자연수입니다.

- 입출력 예

| arr | return |
| -- | -- |
| [2,6,8,14] | 168 |
| [1,2,3] | 6 |

- 풀이
  - math

```C++
int gcd(int a, int b){
    if(a == 0)
        return b;
    return gcd((b % a), a);
}

int lcm(int a, int b){
    return (a * b) / gcd(a,b);
}

int solution(vector<int> arr) {
    int answer = arr[0];
    
    for(auto i = arr.begin() + 1 ; i != arr.end() ; ++i){
        answer = lcm(answer, *i); 
    }
    
    return answer;
}
```

----------------------------------

### [ [1차] 비밀지도 ](https://programmers.co.kr/learn/courses/30/lessons/17681) - lv.1

- 문제

네오는 평소 프로도가 비상금을 숨겨놓는 장소를 알려줄 비밀지도를 손에 넣었다. 그런데 이 비밀지도는 숫자로 암호화되어 있어 위치를 확인하기 위해서는 암호를 해독해야 한다. 다행히 지도 암호를 해독할 방법을 적어놓은 메모도 함께 발견했다.
지도는 한 변의 길이가 n인 정사각형 배열 형태로, 각 칸은 공백(" ) 또는벽(#") 두 종류로 이루어져 있다.
전체 지도는 두 장의 지도를 겹쳐서 얻을 수 있다. 각각 지도 1과 지도 2라고 하자. 지도 1 또는 지도 2 중 어느 하나라도 벽인 부분은 전체 지도에서도 벽이다. 지도 1과 지도 2에서 모두 공백인 부분은 전체 지도에서도 공백이다.
지도 1과 지도 2는 각각 정수 배열로 암호화되어 있다.
암호화된 배열은 지도의 각 가로줄에서 벽 부분을 1, 공백 부분을 0으로 부호화했을 때 얻어지는 이진수에 해당하는 값의 배열이다.

![example](http://t1.kakaocdn.net/welcome2018/secret8.png)

네오가 프로도의 비상금을 손에 넣을 수 있도록, 비밀지도의 암호를 해독하는 작업을 도와줄 프로그램을 작성하라.

- 제한사항
  - 1 ≦ n ≦ 16
  - arr1, arr2는 길이 n인 정수 배열로 주어진다.
  - 정수 배열의 각 원소 x를 이진수로 변환했을 때의 길이는 n 이하이다. 즉, 0 ≦ x ≦ 2n - 1을 만족한다.

- 입출력 예

| 매개변수 | 값 |
| -- | -- |
| n | 5 |
| arr1 | [9, 20, 28, 18, 11] |
| arr2 | [30, 1, 21, 17, 28] |
| 출력 | ["#####","# # #", "### #", "# ##", "#####"] |

| 매개변수 | 값 |
| -- | -- |
| n | 6 |
| arr1 | [46, 33, 33 ,22, 31, 50]|
| arr2 | [27 ,56, 19, 14, 14, 10]|
| 출력 | ["######", "### #", "## ##", " #### ", " #####", "### # "]|

- 풀이
  - Bit Manipulte

```C++
vector<string> solution(int n, vector<int> arr1, vector<int> arr2) {
    vector<string> answer;
    vector<int> makeMap;
    
    // & 연산을 통해 두 지도 배열을 합침
    for(auto i = 0 ; i < n ; ++i){
        makeMap.push_back(arr1[i] | arr2[i]);
    }
    
    // 합친 지도에서 각 행마다 
    // 2진수를 조사하여 1의 위치를 알아냄
    for(auto& i : makeMap){
        string res;
        stack<int> s;
        
        // 2진수의 1의 위치를 조사할때,
        // 순서에 반대부터 조사하므로 stack을 이용하여 뒤집음
        for(auto k = 0 ; k < n ; ++k){
            auto temp = i & 1;
            s.push(temp);
            i >>= 1;
        }
        
        while(!s.empty()){
            if(s.top() == 1)
                res.push_back('#');
            else
                res.push_back(' ');
            
            s.pop();
        }
        
        answer.push_back(res);
    }
    
    return answer;
}
```

----------------------------------

### [ 정수 내림차순으로 배치하기 ](https://programmers.co.kr/learn/courses/30/lessons/12933) - lv.1

- 문제

함수 solution은 정수 n을 매개변수로 입력받습니다. n의 각 자릿수를 큰것부터 작은 순으로 정렬한 새로운 정수를 리턴해주세요. 예를들어 n이 118372면 873211을 리턴하면 됩니다.

- 제한사항
  - n은 1이상 8000000000 이하인 자연수입니다.

- 입출력 예

| n | return |
|  -- |  -- |
| 118372 | 873211 |

- 풀이
  - math

```C++
long long solution(long long n) {
    long long answer = 0;
    long long temp = 10;
    vector<int> arr;
    
    while(temp < n * 10){
        arr.push_back(((n % temp) - (n % (temp/10))) / (temp/10));
        
        temp *= 10;
    }
    
    sort(arr.begin(), arr.end(), greater<int>());
    
    auto len = arr.size();
    temp = 1;
    for(auto i = 0 ; i < len ; ++i){
        answer += (arr.back() * temp);
        arr.pop_back();
        temp *= 10;
    }
    
    return answer;
}
```

----------------------------------

### [ 정수 제곱근 판별 ](https://programmers.co.kr/learn/courses/30/lessons/12934) - lv.1

- 문제

임의의 양의 정수 n에 대해, n이 어떤 양의 정수 x의 제곱인지 아닌지 판단하려 합니다.
n이 양의 정수 x의 제곱이라면 x+1의 제곱을 리턴하고, n이 양의 정수 x의 제곱이 아니라면 -1을 리턴하는 함수를 완성하세요.

- 제한사항
  - n은 1이상, 50000000000000 이하인 양의 정수입니다.

- 입출력 예

| n | return |
|  -- |  -- |
| 121 | 144 |
| 3 | -1|

```
입출력 예 #1
 - 121은 양의 정수 11의 제곱이므로, (11+1)를 제곱한 144를 리턴합니다.
입출력 예 #2
 - 3은 양의 정수의 제곱이 아니므로, -1을 리턴합니다.
```

- 풀이
  - math

```C++
long long solution(long long n) {
    long long answer = 0;
    long long mul = 1;
    
    while(mul <= n){
        ++answer;
        mul = answer * answer;
        
        if(n == mul){
            return (answer+1) * (answer+1);
        }
    }

    return -1;
}
```

----------------------------------

### [ [2020카카오공채] 문자열 압축 ](https://programmers.co.kr/learn/courses/30/lessons/60057#) - lv.1

- 문제

데이터 처리 전문가가 되고 싶은 어피치는 문자열을 압축하는 방법에 대해 공부를 하고 있습니다. 최근에 대량의 데이터 처리를 위한 간단한 비손실 압축 방법에 대해 공부를 하고 있는데, 문자열에서 같은 값이 연속해서 나타나는 것을 그 문자의 개수와 반복되는 값으로 표현하여 더 짧은 문자열로 줄여서 표현하는 알고리즘을 공부하고 있습니다.
간단한 예로 aabbaccc의 경우 2a2ba3c(문자가 반복되지 않아 한번만 나타난 경우 1은 생략함)와 같이 표현할 수 있는데, 이러한 방식은 반복되는 문자가 적은 경우 압축률이 낮다는 단점이 있습니다. 예를 들면, abcabcdede와 같은 문자열은 전혀 압축되지 않습니다. 어피치는 이러한 단점을 해결하기 위해 문자열을 1개 이상의 단위로 잘라서 압축하여 더 짧은 문자열로 표현할 수 있는지 방법을 찾아보려고 합니다.
예를 들어, ababcdcdababcdcd의 경우 문자를 1개 단위로 자르면 전혀 압축되지 않지만, 2개 단위로 잘라서 압축한다면 2ab2cd2ab2cd로 표현할 수 있습니다. 다른 방법으로 8개 단위로 잘라서 압축한다면 2ababcdcd로 표현할 수 있으며, 이때가 가장 짧게 압축하여 표현할 수 있는 방법입니다.
다른 예로, abcabcdede와 같은 경우, 문자를 2개 단위로 잘라서 압축하면 abcabc2de가 되지만, 3개 단위로 자른다면 2abcdede가 되어 3개 단위가 가장 짧은 압축 방법이 됩니다. 이때 3개 단위로 자르고 마지막에 남는 문자열은 그대로 붙여주면 됩니다.
압축할 문자열 s가 매개변수로 주어질 때, 위에 설명한 방법으로 1개 이상 단위로 문자열을 잘라 압축하여 표현한 문자열 중 가장 짧은 것의 길이를 return 하도록 solution 함수를 완성해주세요.

- 제한사항
  - s의 길이는 1 이상 1,000 이하입니다.
  - s는 알파벳 소문자로만 이루어져 있습니다.

- 입출력 예

| n | return |
|  -- |  -- |
| "aabbaccc" | 7 |
| "ababcdcdababcdcd" | 9 |
| "abcabcdede" | 8 |
| "abcabcabcabcdededededede" | 14 |
| "xababcdcdababcdcd" | 17 |

```
입출력 예 #1
 - 문자열을 1개 단위로 잘라 압축했을 때 가장 짧습니다.
입출력 예 #2
 - 문자열을 8개 단위로 잘라 압축했을 때 가장 짧습니다.
입출력 예 #3
 - 문자열을 3개 단위로 잘라 압축했을 때 가장 짧습니다.
입출력 예 #4
 - 문자열을 2개 단위로 자르면 abcabcabcabc6de 가 됩니다.
 - 문자열을 3개 단위로 자르면 4abcdededededede 가 됩니다.
 - 문자열을 4개 단위로 자르면 abcabcabcabc3dede 가 됩니다.
 - 문자열을 6개 단위로 자를 경우 2abcabc2dedede가 되며, 이때의 길이가 14로 가장 짧습니다.
입출력 예 #5
 - 문자열은 제일 앞부터 정해진 길이만큼 잘라야 합니다.
   따라서 주어진 문자열을 x / ababcdcd / ababcdcd 로 자르는 것은 불가능 합니다.
   이 경우 어떻게 문자열을 잘라도 압축되지 않으므로 가장 짧은 길이는 17이 됩니다.
```

- 풀이
  - string

```C++
int solution(string s) {
    if(s.size() < 2)
        return 1;
    
    int answer = INT_MAX;
    
    // 반복문자를 쪼갤 수만큼 반복
    // 1 ~ size / 2 만큼 쪼갤수 있음
    for(auto i = 1 ; i <= s.size() / 2 ; ++i){
        string res("");
        int count = 1 ;
        auto j = i;
        
        // s를 조회하며 i 만큼 문자를 쪼개며 
        // 반복되는 수를 조사함
        for(; j < s.size() ; j = j+i){
            if(s.substr(j, i) == s.substr(j-i, i))
                ++count;
            else{
                if(count > 1)
                    res += to_string(count) + s.substr(j-i, i);
                else
                    res += s.substr(j-i, i);
                
                count = 1;
            }
        }
        
        // 이전의 반복문에서 마지막 인덱스에 관한 값을
        // 채우지 못하고 빠져나오므로 따로
        // 마지막 인덱스에 관한 정보만 처리
        if(count > 1)
            res += to_string(count) + s.substr(j-i, i);
        else
            res += s.substr(j-i, i);
                
        answer = answer < res.size() ? answer : res.size();
    }
    return answer;
}
```

----------------------------------

### [ 최대공약수와 최소공배수 ](https://programmers.co.kr/learn/courses/30/lessons/12940) - lv.1

- 문제

두 수를 입력받아 두 수의 최대공약수와 최소공배수를 반환하는 함수, solution을 완성해 보세요. 배열의 맨 앞에 최대공약수, 그다음 최소공배수를 넣어 반환하면 됩니다. 예를 들어 두 수 3, 12의 최대공약수는 3, 최소공배수는 12이므로 solution(3, 12)는 [3, 12]를 반환해야 합니다.

- 제한사항
  - 두 수는 1이상 1000000이하의 자연수입니다.

- 입출력 예

| n | m | return |
|  -- |  -- | -- |
| 3 | 12 | [3, 12] |
| 2 | 5 | [1, 10] |

```
입출력 예 #1
 - 위의 설명과 같습니다.
입출력 예 #2
 - 자연수 2와 5의 최대공약수는 1, 최소공배수는 10이므로 [1, 10]을 리턴해야 합니다.
```

- 풀이
  - Hash

```C++
int gcd(int a, int b){
    if(a == 0)
        return b;
    return gcd((b%a), a);    
}

int lcm(int a, int b){
    return (a * b) / gcd(a, b);
}

vector<int> solution(int n, int m) {
    return {gcd(n,m), lcm(n,m)};
}
```

----------------------------------

### [ 베스트앨범 ](https://programmers.co.kr/learn/courses/30/lessons/42579) - lv.3

- 문제

스트리밍 사이트에서 장르 별로 가장 많이 재생된 노래를 두 개씩 모아 베스트 앨범을 출시하려 합니다. 노래는 고유 번호로 구분하며, 노래를 수록하는 기준은 다음과 같습니다.
속한 노래가 많이 재생된 장르를 먼저 수록합니다.
장르 내에서 많이 재생된 노래를 먼저 수록합니다.
장르 내에서 재생 횟수가 같은 노래 중에서는 고유 번호가 낮은 노래를 먼저 수록합니다.
노래의 장르를 나타내는 문자열 배열 genres와 노래별 재생 횟수를 나타내는 정수 배열 plays가 주어질 때, 베스트 앨범에 들어갈 노래의 고유 번호를 순서대로 return 하도록 solution 함수를 완성하세요.

- 제한사항
  - genres[i]는 고유번호가 i인 노래의 장르입니다.
  - plays[i]는 고유번호가 i인 노래가 재생된 횟수입니다.
  - genres와 plays의 길이는 같으며, 이는 1 이상 10,000 이하입니다.
  - 장르 종류는 100개 미만입니다.
  - 장르에 속한 곡이 하나라면, 하나의 곡만 선택합니다.
  - 모든 장르는 재생된 횟수가 다릅니다.

- 입출력 예

| genres | plays | return |
|  -- |  -- | -- |
| [classic, pop, classic, classic, pop]	] | [500, 600, 150, 800, 2500] | [4, 1, 3, 0] |

```
classic 장르는 1,450회 재생되었으며, classic 노래는 다음과 같습니다.
 - 고유 번호 3: 800회 재생
 - 고유 번호 0: 500회 재생
 - 고유 번호 2: 150회 재생
pop 장르는 3,100회 재생되었으며, pop 노래는 다음과 같습니다.
 - 고유 번호 4: 2,500회 재생
 - 고유 번호 1: 600회 재생
따라서 pop 장르의 [4, 1]번 노래를 먼저, classic 장르의 [3, 0]번 노래를 그다음에 수록합니다.
```

- 풀이
  - Hash

```C++
bool comp(pair<int,int>& a, pair<int,int>& b){
    if(a.first == b.first)
        return a.second < b.second;
        
    return a.first > b.first;
}

vector<int> solution(vector<string> genres, vector<int> plays) {
    vector<int> answer;
    int len = genres.size();
    map<string, vector<pair<int,int>>> m;
    map<int, string> sumPlays;
    
    // 장르별 플레이수 vector 구성
    for(auto i = 0 ; i < len ; ++i){
        m[genres[i]].push_back({plays[i], i});
    }
    
    // 플레이수를 내림차순으로 정렬
    // 많이 재생된순의 장르를 알기 위해,
    // 각 장르별 플레이수 합의 map을 구성
    for(auto& i : m){
        sort(i.second.begin(), i.second.end(), comp);
        
        int sum = 0;
        for(auto &j : i.second)
            sum += j.first;
        
        sumPlays[sum] = i.first;
    }
    
    for(auto i = sumPlays.rbegin() ; i != sumPlays.rend() ; ++i){
        if(m[i->second].size() > 1){
            answer.push_back(m[i->second][0].second);
            answer.push_back(m[i->second][1].second);
        }
        else{
            answer.push_back(m[i->second][0].second);
        }
    }
    
    return answer;
}
```

----------------------------------

### [ 이중우선순위큐 ](https://programmers.co.kr/learn/courses/30/lessons/42628) - lv.3

- 문제

이중 우선순위 큐는 다음 연산을 할 수 있는 자료구조를 말합니다.

| 명령어 | 수신 탑(높이) |
|  -- |  -- |
| I 숫자 | 큐에 주어진 숫자를 삽입합니다. |
| D 1 | 큐에서 최댓값을 삭제합니다. |
| D -1 | 큐에서 최소값을 삭제합니다. |

이중 우선순위 큐가 할 연산 operations가 매개변수로 주어질 때, 모든 연산을 처리한 후 큐가 비어있으면 [0,0] 비어있지 않으면 [최댓값, 최솟값]을 return 하도록 solution 함수를 구현해주세요.

- 제한사항
  - operations는 길이가 1 이상 1,000,000 이하인 문자열 배열입니다.
  - operations의 원소는 큐가 수행할 연산을 나타냅니다.
  	- 원소는 “명령어 데이터” 형식으로 주어집니다.- 최댓값/최솟값을 삭제하는 연산에서 최댓값/최솟값이 둘 이상인 경우, 하나만 삭제합니다.
  - 빈 큐에 데이터를 삭제하라는 연산이 주어질 경우, 해당 연산은 무시합니다.


- 입출력 예

| operations | return |
|  -- |  -- |
| [I 16,D 1] ] | [0,0] |
| [I 7,I 5,I -5,D -1] ] | [7,5] |

```
16을 삽입 후 최댓값을 삭제합니다. 비어있으므로 [0,0]을 반환합니다.
7,5,-5를 삽입 후 최솟값을 삭제합니다. 최대값 7, 최소값 5를 반환합니다.
```

- 풀이
  - Deque

```C++
vector<int> solution(vector<string> operations) {
    deque<int> answer;

    for(auto& str : operations){
        vector<string> operation;
        string token;
        stringstream ss(str);

        while (getline(ss, token, ' ')) {
            operation.push_back(token);
        }
        
        if(operation[0] == "I"){
            auto val = stoi(operation[1]);

            answer.push_back(val);
            sort(answer.begin(), answer.end());
        }
        
        //최대값 삭제
        else if(operation[0] == "D" && operation[1] == "1"){
            if(answer.empty())
                continue;
            
            answer.pop_back();
        }
        
        // 최소값 삭제
        else{
            if(answer.empty())
                continue;
            
            answer.pop_front();
        }
    }
    
    if(answer.size() == 0)
        return {0,0};
    else
        return {answer.back(), answer.front()};
}
```

----------------------------------

### [ 등굣길 ](https://programmers.co.kr/learn/courses/30/lessons/42898#) - lv.3

- 문제

계속되는 폭우로 일부 지역이 물에 잠겼습니다. 물에 잠기지 않은 지역을 통해 학교를 가려고 합니다. 집에서 학교까지 가는 길은 m x n 크기의 격자모양으로 나타낼 수 있습니다.

아래 그림은 m = 4, n = 3 인 경우입니다.

![example](https://grepp-programmers.s3.amazonaws.com/files/ybm/056f54e618/f167a3bc-e140-4fa8-a8f8-326a99e0f567.png)

가장 왼쪽 위, 즉 집이 있는 곳의 좌표는 (1, 1)로 나타내고 가장 오른쪽 아래, 즉 학교가 있는 곳의 좌표는 (m, n)으로 나타냅니다.

격자의 크기 m, n과 물이 잠긴 지역의 좌표를 담은 2차원 배열 puddles이 매개변수로 주어집니다. 집에서 학교까지 갈 수 있는 최단경로의 개수를 1,000,000,007로 나눈 나머지를 return 하도록 solution 함수를 작성해주세요.

- 제한사항
  - 격자의 크기 m, n은 1 이상 100 이하인 자연수입니다.
    - m과 n이 모두 1인 경우는 입력으로 주어지지 않습니다.
  - 물에 잠긴 지역은 0개 이상 10개 이하입니다.
  - 집과 학교가 물에 잠긴 경우는 입력으로 주어지지 않습니다.


- 입출력 예

| M | N | puddles | return |
| -- |  -- |  -- |  -- |
| 4 | 3 | [[2, 2]] | 4 |


![example](https://grepp-programmers.s3.amazonaws.com/files/ybm/32c67958d5/729216f3-f305-4ad1-b3b0-04c2ba0b379a.png)


- 풀이
  - DP

```C++
int solution(int m, int n, vector<vector<int>> puddles) {
    int answer = 0;
    vector<vector<int>> tile = vector<vector<int>>(n + 1, vector<int>(m + 1, 1));
    
    for(auto& puddle : puddles){
        // 가로축 첫번째 줄에서 웅덩이가 있을때,
        // 해당 웅덩이의 오른쪽을 모두 0으로 초기화
        if(puddle[1] == 1){
            for(auto i = puddle[0] ; i <= m ; ++i){
                tile[1][i] = 0;
            }
        }
        // 세로축 첫번째 줄에서 웅덩이가 있을때,
        // 해당 웅덩이의 아래를 모두 0으로 초기화
        else if(puddle[0] == 1){
             for(auto i = puddle[1] ; i <= n ; ++i){
                tile[i][1] = 0;
            }
        }
        else{
            tile[puddle[1]][puddle[0]] = 0;
        }
    }
    
    // 물웅덩이를 제외하고,
    // 현재 경로 = 위 경로 + 왼쪽 경로 
    for(auto i = 2 ; i <= n ; ++i){
        for(auto j = 2 ; j <= m ; ++j){
            if(tile[i][j] != 0)
                tile[i][j] = (tile[i-1][j] + tile[i][j-1]) % 1000000007;
        }
    }
        
    return tile[n][m];
}
```

----------------------------------

### [  타일 장식물  ](https://programmers.co.kr/learn/courses/30/lessons/43104) - lv.3

- 문제

대구 달성공원에 놀러 온 지수는 최근에 새로 만든 타일 장식물을 보게 되었다. 타일 장식물은 정사각형 타일을 붙여 만든 형태였는데, 한 변이 1인 정사각형 타일부터 시작하여 마치 앵무조개의 나선 모양처럼 점점 큰 타일을 붙인 형태였다. 타일 장식물의 일부를 그리면 다음과 같다.

![example](https://grepp-programmers.s3.amazonaws.com/files/production/3e31bedd54/fcc48066-e72f-45c8-af03-e4360b58b589.png)

그림에서 타일에 적힌 수는 각 타일의 한 변의 길이를 나타낸다. 타일 장식물을 구성하는 정사각형 타일 한 변의 길이를 안쪽 타일부터 시작하여 차례로 적으면 다음과 같다.
**[1, 1, 2, 3, 5, 8, .]**
지수는 문득 이러한 타일들로 구성되는 큰 직사각형의 둘레가 궁금해졌다. 예를 들어, 처음 다섯 개의 타일이 구성하는 직사각형(위에서 빨간색으로 표시한 직사각형)의 둘레는 26이다.

타일의 개수 N이 주어질 때, N개의 타일로 구성된 직사각형의 둘레를 return 하도록 solution 함수를 작성하시오.

- 제한사항
  - N은 1 이상 80 이하인 자연수이다.

- 입출력 예

| N | return |
| -- |  -- |
| 5 | 26 |
| 6 | 42 |

- 풀이
  - DP

```C++
long long solution(int N) {
    long long answer = 0;
    long long val = 1, preVal = 1;
    
    for(auto i = 2 ; i < N ; ++i){
        long long temp = val + preVal;
        preVal = val;
        val = temp;
    }
    
    answer = (val * 2) + ((val + preVal) * 2);
    return answer;
}
```

----------------------------------

### [ 예산 ](https://programmers.co.kr/learn/courses/30/lessons/43237) - lv.3

- 문제

국가의 역할 중 하나는 여러 지방의 예산요청을 심사하여 국가의 예산을 분배하는 것입니다. 국가예산의 총액은 미리 정해져 있어서 모든 예산요청을 배정해 주기는 어려울 수도 있습니다. 그래서 정해진 총액 이하에서 가능한 한 최대의 총 예산을 다음과 같은 방법으로 배정합니다.

```
1. 모든 요청이 배정될 수 있는 경우에는 요청한 금액을 그대로 배정합니다.
2. 모든 요청이 배정될 수 없는 경우에는 특정한 정수 상한액을 계산하여 그 이상인 예산요청에는 모두 상한액을 배정합니다. 
   상한액 이하의 예산요청에 대해서는 요청한 금액을 그대로 배정합니다. 
```

예를 들어, 전체 국가예산이 485이고 4개 지방의 예산요청이 각각 120, 110, 140, 150일 때, 상한액을 127로 잡으면 위의 요청들에 대해서 각각 120, 110, 127, 127을 배정하고 그 합이 484로 가능한 최대가 됩니다.
각 지방에서 요청하는 예산이 담긴 배열 budgets과 총 예산 M이 매개변수로 주어질 때, 위의 조건을 모두 만족하는 상한액을 return 하도록 solution 함수를 작성해주세요.

- 제한사항
  - 지방의 수는 3 이상 100,000 이하인 자연수입니다.
  - 각 지방에서 요청하는 예산은 1 이상 100,000 이하인 자연수입니다.
  - 총 예산은 _지방의 수 이상_ 1,000,000,000 이하인 자연수입니다.


- 입출력 예

| budgets | M | return |
| -- | --| -- |
| [120, 110, 140, 150] | 485 | 127 |

- 풀이
  - Binary Search

```C++
int solution(vector<int> budgets, int M) {
    int answer = 0, maxSum = 0;
    int min = 0, middle = 0;
    int max = *max_element(budgets.begin(), budgets.end());
    
    // Binary Search 기반
    while(min <= max){
        middle = (max + min) >> 1;
        int sum = 0;
        
        // 각 지방의 예산의 합 계산
        for(auto &i : budgets){
            // 지방의 요청예산보다 중간값이 클경우 지방의 요청예산을 반영
            if(i <= middle){
                sum += i;
            }
            // 지방의 요청예산보다 중간값이 작을시 중간값을 반영
            else{
                sum += middle;
            }
        }
        
        // 지방의 예산 합보다 국가예산이 작은 액수중 가장 큰값을 계산
        if(sum < M && maxSum < sum){
            maxSum = sum;
            answer = middle;
        }
        
        // Binary Search 의 종료조건
        if(min == middle && middle == max){
            break;
        }
        
        if(sum <= M){
            min = middle + 1;
        }
        else{
            max = middle - 1;
        }        
    }
    
    return answer;
}
```

----------------------------------

### [ 디스크 컨트롤러 ](https://programmers.co.kr/learn/courses/30/lessons/42627#) - lv.3

- 문제

하드디스크는 한 번에 하나의 작업만 수행할 수 있습니다. 디스크 컨트롤러를 구현하는 방법은 여러 가지가 있습니다. 가장 일반적인 방법은 요청이 들어온 순서대로 처리하는 것입니다.

예를들어

```
- 0ms 시점에 3ms가 소요되는 A작업 요청
- 1ms 시점에 9ms가 소요되는 B작업 요청
- 2ms 시점에 6ms가 소요되는 C작업 요청
```

와 같은 요청이 들어왔습니다. 이를 그림으로 표현하면 아래와 같습니다.

![eample](https://grepp-programmers.s3.amazonaws.com/files/production/b68eb5cec6/38dc6a53-2d21-4c72-90ac-f059729c51d5.png)

한 번에 하나의 요청만을 수행할 수 있기 때문에 각각의 작업을 요청받은 순서대로 처리하면 다음과 같이 처리 됩니다.

![eample](https://grepp-programmers.s3.amazonaws.com/files/production/5e677b4646/90b91fde-cac4-42c1-98b8-8f8431c52dcf.png)

```
- A: 3ms 시점에 작업 완료 (요청에서 종료까지 : 3ms)
- B: 1ms부터 대기하다가, 3ms 시점에 작업을 시작해서 12ms 시점에 작업 완료(요청에서 종료까지 : 11ms)
- C: 2ms부터 대기하다가, 12ms 시점에 작업을 시작해서 18ms 시점에 작업 완료(요청에서 종료까지 : 16ms)
```

이 때 각 작업의 요청부터 종료까지 걸린 시간의 평균은 10ms(= (3 + 11 + 16) / 3)가 됩니다.

하지만 A → C → B 순서대로 처리하면

![eample](https://grepp-programmers.s3.amazonaws.com/files/production/9eb7c5a6f1/a6cff04d-86bb-4b5b-98bf-6359158940ac.png)

```
- A: 3ms 시점에 작업 완료(요청에서 종료까지 : 3ms)
- C: 2ms부터 대기하다가, 3ms 시점에 작업을 시작해서 9ms 시점에 작업 완료(요청에서 종료까지 : 7ms)
- B: 1ms부터 대기하다가, 9ms 시점에 작업을 시작해서 18ms 시점에 작업 완료(요청에서 종료까지 : 17ms
```

이렇게 A → C → B의 순서로 처리하면 각 작업의 요청부터 종료까지 걸린 시간의 평균은 9ms(= (3 + 7 + 17) / 3)가 됩니다.

각 작업에 대해 [작업이 요청되는 시점, 작업의 소요시간]을 담은 2차원 배열 jobs가 매개변수로 주어질 때, 작업의 요청부터 종료까지 걸린 시간의 평균을 가장 줄이는 방법으로 처리하면 평균이 얼마가 되는지 return 하도록 solution 함수를 작성해주세요. (단, 소수점 이하의 수는 버립니다)

- 제한사항
  - jobs의 길이는 1 이상 500 이하입니다.
  - jobs의 각 행은 하나의 작업에 대한 [작업이 요청되는 시점, 작업의 소요시간] 입니다.
  - 각 작업에 대해 작업이 요청되는 시간은 0 이상 1,000 이하입니다.
  - 각 작업에 대해 작업의 소요시간은 1 이상 1,000 이하입니다.
  - 하드디스크가 작업을 수행하고 있지 않을 때에는 먼저 요청이 들어온 작업부터 처리합니다.

- 입출력 예

| jobs | return |
| -- | --| 
| [[0, 3], [1, 9], [2, 6]] | 9 |

```
예제 #1 
문제에 주어진 예와 같습니다.
    0ms 시점에 3ms 걸리는 작업 요청이 들어옵니다.
    1ms 시점에 9ms 걸리는 작업 요청이 들어옵니다.
    2ms 시점에 6ms 걸리는 작업 요청이 들어옵니다.
```

- 풀이
  - Heap

```C++
class Comp{
public:
    bool operator() (const vector<int>& lhs, const vector<int>& rhs) const{
        return lhs[1] > rhs[1];
    }
};

int solution(vector<vector<int>> jobs) {
    int answer = 0, curTime = 0, index = 0, runTime = 0;
    priority_queue<vector<int>, vector<vector<int>>, Comp> pq;
    
    sort(jobs.begin(), jobs.end());
    
    while(index < jobs.size() || !pq.empty()){
        // 현재 job의 끝나는 시간전 까지 요청이 시작되는 job들을 heap에 넣어,
        // 수행시간이 짧은 순으로(SJF) 정렬.
        while(index < jobs.size() && jobs[index][0] <= curTime){
            pq.push(jobs[index]);
            ++index;
        }
        
        // index는 아직 마지막이 아니지만 Heap이 비어있다면, 
        // 다음 job의 요청시간은 현재 job이 작업을 끝낸 이후.
        // 따라서 현재 시간을 다음 job의 요청시간으로 변경
        if(pq.empty()){
            curTime = jobs[index][0];
            continue;
        }

        // 현재 시간은 heap에 있는 최소 작업시간만큼 더한시간
        curTime += pq.top()[1];

        // 현재시간에 해당 job의 요청시간을 빼주어,
        // (요청시간 - 작업시간) 을 구함
        answer += curTime - pq.top()[0];

        pq.pop();
    }

    return answer / jobs.size();
}
```

----------------------------------

### [ 여행경로 ](https://programmers.co.kr/learn/courses/30/lessons/43164) - lv.3

- 문제

주어진 항공권을 모두 이용하여 여행경로를 짜려고 합니다. 항상 "ICN" 공항에서 출발합니다.

항공권 정보가 담긴 2차원 배열 tickets가 매개변수로 주어질 때, 방문하는 공항 경로를 배열에 담아 return 하도록 solution 함수를 작성해주세요.

- 제한사항
  - 모든 공항은 알파벳 대문자 3글자로 이루어집니다.
  - 주어진 공항 수는 3개 이상 10,000개 이하입니다.
  - tickets의 각 행 [a, b]는 a 공항에서 b 공항으로 가는 항공권이 있다는 의미입니다.
  - 주어진 항공권은 모두 사용해야 합니다.
  - 만일 가능한 경로가 2개 이상일 경우 알파벳 순서가 앞서는 경로를 return 합니다.
  - 모든 도시를 방문할 수 없는 경우는 주어지지 않습니다.

- 입출력 예

| tickets | return |
| -- | --| 
| [["ICN", "JFK"], ["HND", "IAD"], ["JFK", "HND"]] | ["ICN", "JFK", "HND", "IAD"] |
| [["ICN", "SFO"], ["ICN", "ATL"], ["SFO", "ATL"], ["ATL", "ICN"], ["ATL","SFO"]] | ["ICN", "ATL", "ICN", "SFO", "ATL", "SFO"] |

`
예제 #1 
["ICN", "JFK", "HND", "IAD"] 순으로 방문할 수 있습니다.
`

`
예제 #2 
["ICN", "SFO", "ATL", "ICN", "ATL", "SFO"] 순으로 방문할 수도 있지만 ["ICN", "ATL", "ICN", "SFO", "ATL", "SFO"] 가 알파벳 순으로 앞섭니다.
`

- 풀이
  - DFS, BFS

```C++
vector<string> solution(vector<vector<string>> tickets) {
    vector<vector<string>> answer;
    vector<vector<int>> answerIndex;
    map<string, vector<pair<string, int>>> m;
    
    // tickets의 요소를 map으로 구성
    for(auto i = 0 ; i < tickets.size() ; ++i){
        m[tickets[i][0]].push_back({tickets[i][1], i});
    }
    
    // ICN부터 시작하여 요소를 DFS로 검사
    for(auto i = m["ICN"].begin() ; i != m["ICN"].end() ; ++i ){
        stack<pair<string, vector<int>>> q;
        q.push({i->first, {i->second}});

        while(!q.empty()){
            auto tmp = q.top();
            q.pop();

            if(tmp.second.size() == tickets.size()){
                answerIndex.push_back(tmp.second);
            }
            
            for(auto j = m[tmp.first].rbegin() ; j != m[tmp.first].rend() ; ++j){
                // 현재까지 저장된 index vector에 현재 index가 없는지 검사 
                if(find(tmp.second.begin(), tmp.second.end(), j->second) == tmp.second.end()){
                    // 현재 검사중인 운항출발지의 여러 목적지가 답이 될수 있으므로
                    // vector를 copy하여 이를 저장
                    auto ans = tmp.second;
                    ans.push_back(j->second);
                    q.push({j->first, ans});
                }
            }
        }
    }

    // 얻은 경로의 index를 기반하여 문자열 생성
    for(auto& i : answerIndex){
        vector<string> temp;
        temp.push_back(tickets[i[0]][0]);
        
        for(auto& j : i){
            temp.push_back(tickets[j][1]);
        }
        answer.push_back(temp);
    }

    // 알파벳 순으로 정렬
    sort(answer.begin(), answer.end());

    return answer[0];
}
```

----------------------------------

### [ 정수 삼각형 ](https://programmers.co.kr/learn/courses/30/lessons/43105) - lv.3

- 문제

![example](https://grepp-programmers.s3.amazonaws.com/files/production/97ec02cc39/296a0863-a418-431d-9e8c-e57f7a9722ac.png)

위와 같은 삼각형의 꼭대기에서 바닥까지 이어지는 경로 중, 거쳐간 숫자의 합이 가장 큰 경우를 찾아보려고 합니다. 아래 칸으로 이동할 때는 대각선 방향으로 한 칸 오른쪽 또는 왼쪽으로만 이동 가능합니다. 예를 들어 3에서는 그 아래칸의 8 또는 1로만 이동이 가능합니다.

삼각형의 정보가 담긴 배열 triangle이 매개변수로 주어질 때, 거쳐간 숫자의 최댓값을 return 하도록 solution 함수를 완성하세요.

- 제한사항
  - 삼각형의 높이는 1 이상 500 이하입니다.
  - 삼각형을 이루고 있는 숫자는 0 이상 9,999 이하의 정수입니다.

- 입출력 예

| triangle | target 
| -- | --| 
| [[7], [3, 8], [8, 1, 0], [2, 7, 4, 4], [4, 5, 2, 6, 5]] | 30 |

- 풀이
  - DP

```C++
int solution(vector<vector<int>> triangle) {
    vector<vector<int>> answer = triangle;
    
    for(auto i = 0 ; i < triangle.size() - 1 ; ++i ){
        for(auto j = 0 ; j < triangle[i].size() ; ++j){
            int left = answer[i][j] + triangle[i+1][j];
            int right = answer[i][j] + triangle[i+1][j+1];
            
            if(left > answer[i+1][j]){
                answer[i+1][j] = left;
            }
            
            if(right > answer[i+1][j+1]){
                answer[i+1][j+1] = right;
            }
        }
    }
    
    return *max_element(answer.rbegin()->begin(), answer.rbegin()->end());
}
```

----------------------------------

### [ 단어 변환 ](https://programmers.co.kr/learn/courses/30/lessons/43163) - lv.3

- 문제

두 개의 단어 begin, target과 단어의 집합 words가 있습니다. 아래와 같은 규칙을 이용하여 begin에서 target으로 변환하는 가장 짧은 변환 과정을 찾으려고 합니다.

```
1. 한 번에 한 개의 알파벳만 바꿀 수 있습니다.
2. words에 있는 단어로만 변환할 수 있습니다.
```

예를 들어 begin이 "hit", target가 "cog", words가 ["hot","dot","dog","lot","log","cog"]라면 "hit" -> "hot" -> "dot" -> "dog" -> "cog"와 같이 4단계를 거쳐 변환할 수 있습니다.

두 개의 단어 begin, target과 단어의 집합 words가 매개변수로 주어질 때, 최소 몇 단계의 과정을 거쳐 begin을 target으로 변환할 수 있는지 return 하도록 solution 함수를 작성해주세요.

- 제한사항
  - 각 단어는 알파벳 소문자로만 이루어져 있습니다.
  - 각 단어의 길이는 3 이상 10 이하이며 모든 단어의 길이는 같습니다.
  - words에는 3개 이상 50개 이하의 단어가 있으며 중복되는 단어는 없습니다.
  - begin과 target은 같지 않습니다.
  - 변환할 수 없는 경우에는 0를 return 합니다.

- 입출력 예

| begin | target | words | return |
| -- | --| --| --|
| "hit" | "cog" | ["hot", "dot", "dog", "lot", "log", "cog"] | 4 |
| "hit" | "cog" | ["hot", "dot", "dog", "lot", "log"] | 0 |

`예제 #1 문제에 나온 예와 같습니다.`
`예제 #2 target인 "cog"는 words 안에 없기 때문에 변환할 수 없습니다.`

- 풀이
  - DFS

```C++
int solution(string begin, string target, vector<string> words) {
    int answer = INT_MAX;
    
    // begin과 하나만 다른words의 elements 찾아서 저장
    vector<string> choice;
    for(auto& str : words){
        int count = 0;
        for(auto i = 0 ; i < begin.size() ; ++i){
            if(begin[i] != str[i]){
                    ++count;
                }
            }
            if(count == 1)
                choice.push_back(str);
    }

    for(auto i = 0 ; i < choice.size() ; ++i){
        // 한번 조회한 element 체크
        vector<bool> check(words.size(), false);
        stack<pair<string, int>> s;
        int val = INT_MAX;
            
        s.push({choice[i], 1});
        
        while(!s.empty()){
            auto temp = s.top();
            s.pop();
            
            // target과 같을때, 현재 저장된 값보다 count가 작으면 저장
            if(temp.first == target){
                if(temp.second < val)
                    val = temp.second;
            }
            
            // 현재 단계에서 하나만 다른words의 elements 찾아서 저장
            for(auto j = 0; j < words.size() ; ++j){
                if(check[j])
                    continue;

                int count = 0;
                for(auto t = 0 ; t < words[j].size() ; ++t){
                    if(words[j][t] != temp.first[t]){
                        ++count;
                    }
                }
                if(count == 1){
                    s.push({words[j], temp.second + 1});
                    check[j] = true;
                }
            }
        }
        
        if(val < answer)
            answer = val;
    }
    
    return answer == INT_MAX ? 0 : answer;
}
```

----------------------------------

### [ 단속카메라 ](https://programmers.co.kr/learn/courses/30/lessons/42884) - lv.3

- 문제

고속도로를 이동하는 모든 차량이 고속도로를 이용하면서 단속용 카메라를 한 번은 만나도록 카메라를 설치하려고 합니다.

고속도로를 이동하는 차량의 경로 routes가 매개변수로 주어질 때, 모든 차량이 한 번은 단속용 카메라를 만나도록 하려면 최소 몇 대의 카메라를 설치해야 하는지를 return 하도록 solution 함수를 완성하세요.

- 제한사항
  - 차량의 대수는 1대 이상 10,000대 이하입니다.
  - routes에는 차량의 이동 경로가 포함되어 있으며 routes[i][0]에는 i번째 차량이 고속도로에 진입한 지점, routes[i][1]에는 i번째 차량이 고속도로에서 나간 지점이 적혀 있습니다.
  - 차량의 진입/진출 지점에 카메라가 설치되어 있어도 카메라를 만난것으로 간주합니다.
  - 차량의 진입 지점, 진출 지점은 -30,000 이상 30,000 이하입니다.

- 입출력 예

| routes | return |
| -- | --|
| [[-20,15], [-14,-5], [-18,-13], [-5,-3]] | 2 |

`-5 지점에 카메라를 설치하면 두 번째, 네 번째 차량이 카메라를 만납니다.
 -15 지점에 카메라를 설치하면 첫 번째, 세 번째 차량이 카메라를 만납니다. `

- 풀이
  - Greedy

```C++
bool comp(vector<int>& a, vector<int>& b){
    return a[1] < b[1];    
}

int solution(vector<vector<int>> routes) {
    int answer = 1;
    int preValue = 0;
    
    sort(routes.begin(), routes.end(), comp);
    
    preValue = routes[0][1];
    for(auto& i : routes){
        if(i[0] > preValue){
            ++answer;
            preValue = i[1];
        }
    }
    
    return answer;
}
```

----------------------------------

### [ 종이접기 ](https://programmers.co.kr/learn/courses/30/lessons/62049?language=cpp) - lv.3

- 문제

직사각형 종이를 n번 접으려고 합니다. 이때, 항상 오른쪽 절반을 왼쪽으로 접어 나갑니다. 다음은 n = 2인 경우의 예시입니다.

![example](https://res.cloudinary.com/dpxurmkij/image/upload/c_scale,w_390/v1500952547/%EC%A2%85%EC%9D%B4%EC%A0%91%EA%B8%B01_swcvrz.png)

먼저 오른쪽 절반을 왼쪽으로 접습니다.

![example](https://res.cloudinary.com/dpxurmkij/image/upload/c_scale,w_195/v1500952547/%EC%A2%85%EC%9D%B4%EC%A0%91%EA%B8%B02_e49oe3.png)

다시 오른쪽 절반을 왼쪽으로 접습니다.

![example](https://res.cloudinary.com/dpxurmkij/image/upload/c_scale,w_95/v1500952178/%EC%A2%85%EC%9D%B4%EC%A0%91%EA%B8%B03_nqdurc.png)

종이를 모두 접은 후에는 종이를 전부 펼칩니다. 종이를 펼칠 때는 종이를 접은 방법의 역순으로 펼쳐서 처음 놓여있던 때와 같은 상태가 되도록 합니다. 위와 같이 두 번 접은 후 종이를 펼치면 아래 그림과 같이 종이에 접은 흔적이 생기게 됩니다.

![example](https://res.cloudinary.com/dpxurmkij/image/upload/c_scale,w_390/v1500952178/%EC%A2%85%EC%9D%B4%EC%A0%91%EA%B8%B04_qxfoxr.png)

위 그림에서 ∨ 모양이 생긴 부분은 점선(0)으로, ∧ 모양이 생긴 부분은 실선(1)으로 표시했습니다.

종이를 접은 횟수 n이 매개변수로 주어질 때, 종이를 절반씩 n번 접은 후 모두 펼쳤을 때 생기는 접힌 부분의 모양을 배열에 담아 return 하도록 solution 함수를 완성해주세요.

- 제한사항
  - 종이를 접는 횟수 n은 1 이상 20 이하의 자연수입니다.
  - 종이를 접었다 편 후 생긴 굴곡이 ∨ 모양이면 0, ∧ 모양이면 1로 나타냅니다.
  - 가장 왼쪽의 굴곡 모양부터 순서대로 배열에 담아 return 해주세요.

- 입출력 예

| n | result |
| -- | --|
| 1 | [0] |
| 2 | [0,0,1] |
| 3 | [0,0,1,0,0,1,1] |

`입출력 예 #1 종이의 오른쪽 절반을 왼쪽으로 한번 접었다 펴면 아래 그림과 같이 굴곡이 생깁니다. `

![example](https://res.cloudinary.com/dpxurmkij/image/upload/c_scale,w_390/v1500952178/%EC%A2%85%EC%9D%B4%EC%A0%91%EA%B8%B05_fpgzni.png)

`입출력 예 #2 문제의 예시와 같습니다. `

`입출력 예 #3 종이를 절반씩 세 번 접은 후 다시 펼치면 아래 그림과 같이 굴곡이 생깁니다. `

![example](https://res.cloudinary.com/dpxurmkij/image/upload/c_scale,w_390/v1500952178/%EC%A2%85%EC%9D%B4%EC%A0%91%EA%B8%B06_sbn7li.png)

- 풀이
  - index

```C++
vector<int> solution(int n) {
    vector<int> answer;
    int N = 0;
   
    for(auto i = 0 ; i < n ; ++i){
    	// 한번 접을때 마다 N*2+1만큼 증가
        N = N * 2 + 1;
        answer.resize(N);
     
        // 배열의 가운데는 무조건 0
        int size = answer.size() / 2;
        answer[size] = 0;
	
	// 인덱스 i 와 size()-i-1 의 값은 반대
        for(auto j = 0 ; j < size ; ++j){
            answer[answer.size() - j - 1] = answer[j] == 0 ? 1 : 0;
        }
    }
    
    return answer;
}
```

----------------------------------

### [ 2 x n 타일링 ](https://programmers.co.kr/learn/courses/30/lessons/12900) - lv.3

- 문제

가로 길이가 2이고 세로의 길이가 1인 직사각형모양의 타일이 있습니다. 이 직사각형 타일을 이용하여 세로의 길이가 2이고 가로의 길이가 n인 바닥을 가득 채우려고 합니다. 타일을 채울 때는 다음과 같이 2가지 방법이 있습니다.

    타일을 가로로 배치 하는 경우
    타일을 세로로 배치 하는 경우

예를들어서 n이 7인 직사각형은 다음과 같이 채울 수 있습니다.

![example](https://i.imgur.com/29ANX0f.png)

직사각형의 가로의 길이 n이 매개변수로 주어질 때, 이 직사각형을 채우는 방법의 수를 return 하는 solution 함수를 완성해주세요.

- 제한사항
  - 가로의 길이 n은 60,000이하의 자연수 입니다.
  - 경우의 수가 많아 질 수 있으므로, 경우의 수를 1,000,000,007으로 나눈 나머지를 return해주세요.

- 입출력 예

| n | result |
| -- | --|
| 4 | 5 |

`입출력 예 #1 다음과 같이 5가지 방법이 있다.`

![example](https://i.imgur.com/keiKrD3.png)
![example](https://i.imgur.com/O9GdTE0.png)
![example](https://i.imgur.com/IZBmc6M.png)
![example](https://i.imgur.com/29LWVzK.png)
![example](https://i.imgur.com/z64JbNf.png)

- 풀이
  - DP

```C++
int solution(int n) {
    if(n == 0)
        return 0;
    
    int answer = 0;
    int n_1 = 1;
    int n_2 = 0;
    
    for(auto i = 1; i <= n ; ++i){
        answer = (n_2 + n_1) % 1000000007;
        n_2 = n_1;
        n_1 = answer;
    }
    
    return answer;
}
```

## 2019

----------------------------------

### [ 캐시 ](https://programmers.co.kr/learn/courses/30/lessons/17680) - lv.2

- 문제

지도개발팀에서 근무하는 제이지는 지도에서 도시 이름을 검색하면 해당 도시와 관련된 맛집 게시물들을 데이터베이스에서 읽어 보여주는 서비스를 개발하고 있다.
이 프로그램의 테스팅 업무를 담당하고 있는 어피치는 서비스를 오픈하기 전 각 로직에 대한 성능 측정을 수행하였는데, 제이지가 작성한 부분 중 데이터베이스에서 게시물을 가져오는 부분의 실행시간이 너무 오래 걸린다는 것을 알게 되었다.
어피치는 제이지에게 해당 로직을 개선하라고 닦달하기 시작하였고, 제이지는 DB 캐시를 적용하여 성능 개선을 시도하고 있지만 캐시 크기를 얼마로 해야 효율적인지 몰라 난감한 상황이다.
어피치에게 시달리는 제이지를 도와, DB 캐시를 적용할 때 캐시 크기에 따른 실행시간 측정 프로그램을 작성하시오.

- 제한사항
  - 캐시 크기(cacheSize)와 도시이름 배열(cities)을 입력받는다.
  - cacheSize는 정수이며, 범위는 0 ≦ cacheSize ≦ 30 이다.
  - cities는 도시 이름으로 이뤄진 문자열 배열로, 최대 도시 수는 100,000개이다.
  - 각 도시 이름은 공백, 숫자, 특수문자 등이 없는 영문자로 구성되며, 대소문자 구분을 하지 않는다. 도시 이름은 최대 20자로 이루어져 있다.
  - 입력된 도시이름 배열을 순서대로 처리할 때, "총 실행시간"을 출력한다.
  - 캐시 교체 알고리즘은 LRU(Least Recently Used)를 사용한다.
  - cache hit일 경우 실행시간은 1이다.
  - cache miss일 경우 실행시간은 5이다.


- 입출력 예

| 캐시크기(cacheSize) | 도시이름(cities) | 실행시간 |
| -- | --| --|
| 3 |	["Jeju", "Pangyo", "Seoul", "NewYork", "LA", "Jeju", "Pangyo", "Seoul", "NewYork", "LA"] |	50 |
| 3 |	["Jeju", "Pangyo", "Seoul", "Jeju", "Pangyo", "Seoul", "Jeju", "Pangyo", "Seoul"] |	21 |
| 2 |	["Jeju", "Pangyo", "Seoul", "NewYork", "LA", "SanFrancisco", "Seoul", "Rome", "Paris", "Jeju", "NewYork", "Rome"] | 60 |
| 5 |	["Jeju", "Pangyo", "Seoul", "NewYork", "LA", "SanFrancisco", "Seoul", "Rome", "Paris", "Jeju", "NewYork", "Rome"] | 52 |
| 2 |	["Jeju", "Pangyo", "NewYork", "newyork"] |	16 |
| 0 |	["Jeju", "Pangyo", "Seoul", "NewYork", "LA"] |	25 |

- 풀이
  - LRU

```C++
int solution(int cacheSize, vector<string> cities) {
    if(cacheSize < 1)
        return cities.size() * 5;
    
    int answer = 0;
    map<string, int> m;
    queue<string> q;
    
    for(auto& i : cities){
        std::transform(i.begin(), i.end(), i.begin(), ::toupper);
        
        if(m.find(i) != m.end()){
            answer += 1;
            
            queue<string> temp;
            while(!q.empty()){
                if(q.front() != i)
                    temp.push(q.front());
                q.pop();
            }
            temp.push(i);
            
            q.swap(temp);
        }
        else{
            if(m.size() >= cacheSize){
                auto least = q.front();
                q.pop();
                m.erase(least);                
            }
            
            m[i] = 1;
            q.push(i);
            answer += 5;
        }
    }
    
    return answer;
}
```

----------------------------------

### [ 뉴스 클러스터링 ](https://programmers.co.kr/learn/courses/30/lessons/17677) - lv.2

- 문제

여러 언론사에서 쏟아지는 뉴스, 특히 속보성 뉴스를 보면 비슷비슷한 제목의 기사가 많아 정작 필요한 기사를 찾기가 어렵다. Daum 뉴스의 개발 업무를 맡게 된 신입사원 튜브는 사용자들이 편리하게 다양한 뉴스를 찾아볼 수 있도록 문제점을 개선하는 업무를 맡게 되었다.

개발의 방향을 잡기 위해 튜브는 우선 최근 화제가 되고 있는 "카카오 신입 개발자 공채" 관련 기사를 검색해보았다.

    카카오 첫 공채..'블라인드' 방식 채용
    카카오, 합병 후 첫 공채.. 블라인드 전형으로 개발자 채용
    카카오, 블라인드 전형으로 신입 개발자 공채
    카카오 공채, 신입 개발자 코딩 능력만 본다
    카카오, 신입 공채.. "코딩 실력만 본다"
    카카오 "코딩 능력만으로 2018 신입 개발자 뽑는다"

기사의 제목을 기준으로 "블라인드 전형"에 주목하는 기사와 "코딩 테스트"에 주목하는 기사로 나뉘는 걸 발견했다. 튜브는 이들을 각각 묶어서 보여주면 카카오 공채 관련 기사를 찾아보는 사용자에게 유용할 듯싶었다.

유사한 기사를 묶는 기준을 정하기 위해서 논문과 자료를 조사하던 튜브는 "자카드 유사도"라는 방법을 찾아냈다.

자카드 유사도는 집합 간의 유사도를 검사하는 여러 방법 중의 하나로 알려져 있다. 두 집합 A, B 사이의 자카드 유사도 J(A, B)는 두 집합의 교집합 크기를 두 집합의 합집합 크기로 나눈 값으로 정의된다.

예를 들어 집합 A = {1, 2, 3}, 집합 B = {2, 3, 4}라고 할 때, 교집합 A ∩ B = {2, 3}, 합집합 A ∪ B = {1, 2, 3, 4}이 되므로, 집합 A, B 사이의 자카드 유사도 J(A, B) = 2/4 = 0.5가 된다. 집합 A와 집합 B가 모두 공집합일 경우에는 나눗셈이 정의되지 않으니 따로 J(A, B) = 1로 정의한다.

자카드 유사도는 원소의 중복을 허용하는 다중집합에 대해서 확장할 수 있다. 다중집합 A는 원소 "1"을 3개 가지고 있고, 다중집합 B는 원소 "1"을 5개 가지고 있다고 하자. 이 다중집합의 교집합 A ∩ B는 원소 "1"을 min(3, 5)인 3개, 합집합 A ∪ B는 원소 "1"을 max(3, 5)인 5개 가지게 된다. 다중집합 A = {1, 1, 2, 2, 3}, 다중집합 B = {1, 2, 2, 4, 5}라고 하면, 교집합 A ∩ B = {1, 2, 2}, 합집합 A ∪ B = {1, 1, 2, 2, 3, 4, 5}가 되므로, 자카드 유사도 J(A, B) = 3/7, 약 0.42가 된다.

이를 이용하여 문자열 사이의 유사도를 계산하는데 이용할 수 있다. 문자열 "FRANCE"와 "FRENCH"가 주어졌을 때, 이를 두 글자씩 끊어서 다중집합을 만들 수 있다. 각각 {FR, RA, AN, NC, CE}, {FR, RE, EN, NC, CH}가 되며, 교집합은 {FR, NC}, 합집합은 {FR, RA, AN, NC, CE, RE, EN, CH}가 되므로, 두 문자열 사이의 자카드 유사도 J("FRANCE", "FRENCH") = 2/8 = 0.25가 된다.

- 제한사항
  - 입력으로는 str1과 str2의 두 문자열이 들어온다. 각 문자열의 길이는 2 이상, 1,000 이하이다.
  - 입력으로 들어온 문자열은 두 글자씩 끊어서 다중집합의 원소로 만든다. 이때 영문자로 된 글자 쌍만 유효하고, 기타 공백이나 숫자, 특수 문자가 들어있는 경우는 그 글자 쌍을 버린다. 예를 들어 "ab+"가 입력으로 들어오면, "ab"만 다중집합의 원소로 삼고, "b+"는 버린다.
  - 다중집합 원소 사이를 비교할 때, 대문자와 소문자의 차이는 무시한다. "AB"와 "Ab", "ab"는 같은 원소로 취급한다.

- 입출력 예

| str1 | str2 |	answer
| -- | --| --|
| FRANCE | french | 16384 |
| handshake | shake hands | 65536 |
| aa1+aa2 | AAAA12 | 43690 |
| E=M*C^2 | e=m*c^2 | 65536 |

- 풀이
  - sort, set

```C++
int solution(string str1, string str2) {
    int answer = 0;
    vector<string> s1, s2;
    vector<string> unionStr, intersectionStr;
    
    std::transform(str1.begin(), str1.end(), str1.begin(), ::tolower);
    std::transform(str2.begin(), str2.end(), str2.begin(), ::tolower);
    
    for(auto i = 1 ; i < str1.size() ; ++i){
        if(('a' <= str1[i-1] && str1[i-1] <= 'z') && ('a' <= str1[i] && str1[i] <= 'z'))
            s1.push_back(str1.substr(i-1, 2));
    }
    
    for(auto i = 1 ; i < str2.size() ; ++i){
        if(('a' <= str2[i-1] && str2[i-1] <= 'z') && ('a' <= str2[i] && str2[i] <= 'z'))
            s2.push_back(str2.substr(i-1, 2));
    }
    
    sort(s1.begin(), s1.end());
    sort(s2.begin(), s2.end());

    set_union(s1.begin(), s1.end(), s2.begin(), s2.end(), back_inserter(unionStr));    
    set_intersection(s1.begin(), s1.end(), s2.begin(), s2.end(), back_inserter(intersectionStr));
    
    if(unionStr.size() < 1)
        answer = 65536;
    else
        answer = (static_cast<float>(intersectionStr.size()) / static_cast<float>(unionStr.size())) * 65536;
    
    return answer;
}
```
----------------------------------

### [ 가장 큰 정사각형 찾기  ](https://programmers.co.kr/learn/courses/30/lessons/12905) - lv.2

- 문제

1와 0로 채워진 표(board)가 있습니다. 표 1칸은 1 x 1 의 정사각형으로 이루어져 있습니다. 표에서 1로 이루어진 가장 큰 정사각형을 찾아 넓이를 return 하는 solution 함수를 완성해 주세요. (단, 정사각형이란 축에 평행한 정사각형을 말합니다.)

예를 들어

| 1 | 2 | 3 | 4 |
| ----------- | ----------- | ----------- | ----------- |
| 0 | 1 | 1 | 1 |
| 1 | 1 | 1 | 1 |
| 1 | 1 | 1 | 1 |
| 0 | 0 | 1 | 0 |

가 있다면 가장 큰 정사각형은

| 1 | 2 | 3 | 4 |
| ----------- | ----------- | ----------- | ----------- |
| 0 | `1` | `1` | `1` |
| 1 | `1` | `1` | `1` |
| 1 | `1` | `1` | `1` |
| 0 | 0 | 1 | 0 |

가 되며 넓이는 9가 되므로 9를 반환해 주면 됩니다.

- 제한사항
  - 표(board)는 2차원 배열로 주어집니다.
  - 표(board)의 행(row)의 크기 : 1,000 이하의 자연수
  - 표(board)의 열(column)의 크기 : 1,000 이하의 자연수
  - 표(board)의 값은 1또는 0으로만 이루어져 있습니다.

- 입출력 예
  
| board |  result |
| ----------- | ----------- |
| [[0,1,1,1],[1,1,1,1],[1,1,1,1],[0,0,1,0]] | 9 |
| [[0,0,1,1],[1,1,1,1]] | 4 |

`입출력 예 #1
위의 예시와 같습니다.

입출력 예 #2
| 0 | 0 | 1 | 1 |
| 1 | 1 | 1 | 1 |
로 가장 큰 정사각형의 넓이는 4가 되므로 4를 return합니다.`

- 풀이
  - DP

```C++
int solution(vector<vector<int>> board)
{
    if(board.size() < 2 || board[0].size() < 2)
        return 1;
    
    int answer = 0;

    for(auto i = 1; i < board.size() ; ++i){        
        for(auto j = 1; j < board[0].size() ; ++j){
            if(board[i][j] == 0)
                continue;
            
            board[i][j] = min({board[i-1][j-1], board[i-1][j], board[i][j-1]}) + 1;
        }
        
        int max = *max_element(board[i].begin(), board[i].end());
        if(answer < max)
            answer = max;
    }

    return answer * answer;
}
```

### [ H-Index ](https://programmers.co.kr/learn/courses/30/lessons/42747) - lv.2

- 문제

H-Index는 과학자의 생산성과 영향력을 나타내는 지표입니다. 어느 과학자의 H-Index를 나타내는 값인 h를 구하려고 합니다. 위키백과1에 따르면, H-Index는 다음과 같이 구합니다.
어떤 과학자가 발표한 논문 n편 중, h번 이상 인용된 논문이 h편 이상이고 나머지 논문이 h번 이하 인용되었다면 h가 이 과학자의 H-Index입니다.
어떤 과학자가 발표한 논문의 인용 횟수를 담은 배열 citations가 매개변수로 주어질 때, 이 과학자의 H-Index를 return 하도록 solution 함수를 작성해주세요.

- 제한사항
  - 과학자가 발표한 논문의 수는 1편 이상 1,000편 이하입니다.
  - 논문별 인용 횟수는 0회 이상 10,000회 이하입니다.

- 입출력 예
  
| citations |  result |
| ----------- | ----------- |
| [3, 0, 6, 1, 5] | 3 |

`이 과학자가 발표한 논문의 수는 5편이고, 그중 3편의 논문은 3회 이상 인용되었습니다. 그리고 나머지 2편의 논문은 3회 이하 인용되었기 때문에 이 과학자의 H-Index는 3입니다.`

- 풀이
  - sort

```C++
int solution(vector<int> citations) {
    int answer = 0;
    
    std::sort(citations.begin() , citations.end(), greater<int>());

    for(auto i = 0 ; i < citations.size() ; ++i){
        if(citations[i] < i+1)
            return i;
    }    
        
    return citations.size();
}
```
----------------------------------

### [스킬트리](https://programmers.co.kr/learn/courses/30/lessons/49993) - lv.2

- 문제

선행 스킬이란 어떤 스킬을 배우기 전에 먼저 배워야 하는 스킬을 뜻합니다.
예를 들어 선행 스킬 순서가 스파크 → 라이트닝 볼트 → 썬더일때, 썬더를 배우려면 먼저 라이트닝 볼트를 배워야 하고, 라이트닝 볼트를 배우려면 먼저 스파크를 배워야 합니다.
위 순서에 없는 다른 스킬(힐링 등)은 순서에 상관없이 배울 수 있습니다. 따라서 스파크 → 힐링 → 라이트닝 볼트 → 썬더와 같은 스킬트리는 가능하지만, 썬더 → 스파크나 라이트닝 볼트 → 스파크 → 힐링 → 썬더와 같은 스킬트리는 불가능합니다.
선행 스킬 순서 skill과 유저들이 만든 스킬트리1를 담은 배열 skill_trees가 매개변수로 주어질 때, 가능한 스킬트리 개수를 return 하는 solution 함수를 작성해주세요.

- 제한사항
  - 스킬은 알파벳 대문자로 표기하며, 모든 문자열은 알파벳 대문자로만 이루어져 있습니다.
  - 스킬 순서와 스킬트리는 문자열로 표기합니다.
    - 예를 들어, C → B → D 라면 "CBD"로 표기합니다
  - 선행 스킬 순서 skill의 길이는 1 이상 26 이하이며, 스킬은 중복해 주어지지 않습니다.
  - skill_trees는 길이 1 이상 20 이하인 배열입니다.
  - skill_trees의 원소는 스킬을 나타내는 문자열입니다.
    - skill_trees의 원소는 길이가 2 이상 26 이하인 문자열이며, 스킬이 중복해 주어지지 않습니다.


- 입출력 예
  
| Skill | skill_trees | result |
| ----------- | ----------- | ----------- |
| "CBD" | ["BACDE", "CBADF", "AECB", "BDA"] |	2 |

- 풀이
  - index

```C++
int solution(string skill, vector<string> skill_trees) {
    int answer = 0, flag = 1;
    
    for(auto &i : skill_trees){
        int skillIndex = 0;
        
        for(auto &j : i){
            if(skill.find(j) == std::string::npos)
                continue;
            
            if(skill[skillIndex] == j)
                ++skillIndex;
            else{
                flag = 0;
                break;
            }
        }
        if(flag)
            answer++;
        
        flag = 1;
    }
    
    return answer;
}
```
----------------------------------

### [멀쩡한 사각형](https://programmers.co.kr/learn/courses/30/lessons/62048) - lv.2

- 문제

가로 길이가 Wcm, 세로 길이가 Hcm인 직사각형 종이가 있습니다. 종이에는 가로, 세로 방향과 평행하게 격자 형태로 선이 그어져 있으며, 모든 격자칸은 1cm x 1cm 크기입니다. 이 종이를 격자 선을 따라 1cm × 1cm의 정사각형으로 잘라 사용할 예정이었는데, 누군가가 이 종이를 대각선 꼭지점 2개를 잇는 방향으로 잘라 놓았습니다. 그러므로 현재 직사각형 종이는 크기가 같은 직각삼각형 2개로 나누어진 상태입니다. 새로운 종이를 구할 수 없는 상태이기 때문에, 이 종이에서 원래 종이의 가로, 세로 방향과 평행하게 1cm × 1cm로 잘라 사용할 수 있는 만큼만 사용하기로 하였습니다.
가로의 길이 W와 세로의 길이 H가 주어질 때, 사용할 수 있는 정사각형의 개수를 구하는 solution 함수를 완성해 주세요.

- 제한사항
  - W, H : 1억 이하의 자연수

- 입출력 예
  
| W | H | result |
| ----------- | ----------- | ----------- |
| 8 | 12 |	80 |

`가로가 8, 세로가 12인 직사각형을 대각선 방향으로 자르면 총 16개 정사각형을 사용할 수 없게 됩니다. 원래 직사각형에서는 96개의 정사각형을 만들 수 있었으므로, 96 - 16 = 80 을 반환합니다.`

![example](https://grepp-programmers.s3.amazonaws.com/files/production/ee895b2cd9/567420db-20f4-4064-afc3-af54c4a46016.png)

- 풀이
  - GCD

```C++
long long getGCD(int a, int b){
    if(a == 0) return b;
    return getGCD(b % a, a);
}

long long solution(int w,int h)
{
	long long gcd = getGCD(w, h);
	long long sum = (long long)w * (long long)h;
    
	return sum - (w + h - gcd);
}
```
----------------------------------

### [네트워크](https://programmers.co.kr/learn/courses/30/lessons/43162) - lv.3

- 문제
네트워크란 컴퓨터 상호 간에 정보를 교환할 수 있도록 연결된 형태를 의미합니다. 예를 들어, 컴퓨터 A와 컴퓨터 B가 직접적으로 연결되어있고, 컴퓨터 B와 컴퓨터 C가 직접적으로 연결되어 있을 때 컴퓨터 A와 컴퓨터 C도 간접적으로 연결되어 정보를 교환할 수 있습니다. 따라서 컴퓨터 A, B, C는 모두 같은 네트워크 상에 있다고 할 수 있습니다.
컴퓨터의 개수 n, 연결에 대한 정보가 담긴 2차원 배열 computers가 매개변수로 주어질 때, 네트워크의 개수를 return 하도록 solution 함수를 작성하시오.

- 제한사항
  - 컴퓨터의 개수 n은 1 이상 200 이하인 자연수입니다.
  - 각 컴퓨터는 0부터 n-1인 정수로 표현합니다.
  - i번 컴퓨터와 j번 컴퓨터가 연결되어 있으면 computers[i][j]를 1로 표현합니다.
  - computer[i][i]는 항상 1입니다.

- 입출력 예
  - n	computers	return
  
| n | vector | return |
| ----------- | ----------- | ----------- |
| 3 | [[1, 1, 0], [1, 1, 0], [0, 0, 1]] | 2 |
| 3 | [[1, 1, 0], [1, 1, 1], [0, 1, 1]] | 1 |

`예제 #1 아래와 같이 2개의 네트워크가 있습니다.`

![example](https://grepp-programmers.s3.amazonaws.com/files/ybm/5b61d6ca97/cc1e7816-b6d7-4649-98e0-e95ea2007fd7.png)

`예제 #2 아래와 같이 1개의 네트워크가 있습니다.`

![example](https://grepp-programmers.s3.amazonaws.com/files/ybm/7554746da2/edb61632-59f4-4799-9154-de9ca98c9e55.png)

- 풀이
  - DFS, BFS

```C++
int solution(int n, vector<vector<int>> computers) {
    int answer = 0;   
    stack<int> s;

    for(auto index = 0 ; index < n ; ++index){
        if(!computers[index][index])
            continue;
        
        s.push(index);

        while(!s.empty()){
            int i = s.top();
            s.pop();

            for(auto j = 0 ; j < n ; ++j){                
                if(computers[i][j] && computers[j][i]){
                    computers[i][j] = 0;
                    s.push(j);
                }
            }
        }
        
        ++answer;
    }
    
    return answer;
}
```
