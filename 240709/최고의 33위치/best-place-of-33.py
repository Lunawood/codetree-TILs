# 입력값
n = int(input())
li = list()
for i in range(n):
    li.append(list(map(int, input().split())))

move = n - 2
ans = 0
# 3 x 3이 움직일 수 있는 크기
for i in range(move):
    for j in range(move):
        cnt = 0
        # 3 x 3으로 check
        for k in range(3):
            for l in range(3):
                if li[k + i][l + j] == 1:
                    cnt += 1
        ans = max(ans, cnt)

print(ans)