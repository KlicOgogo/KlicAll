import sys

def main():
    n = int(sys.stdin.readline())
    a = []
    for i in range(n):
        a.append(sys.stdin.readline().strip())
    result = []
    for i in a:
        b = []
        yes_no = True
        for j in i:
            if j == '[' or j == '(' or j == '{':
                b.append(j)
            elif (j == ']' or j == ')' or j == '}') and len(b) != 0:
                if (b[-1] == '[' and j == ']') or (b[-1] == '(' and j == ')') or (b[-1] == '{' and j == '}'):
                    del b[-1]
                else:
                    yes_no = False
                    break
            else:
                yes_no = False
        if len(b) == 0 and yes_no:
            result.append('yes')
        else:
            result.append('no')
    for i in result:
        print(i)
    return

main()