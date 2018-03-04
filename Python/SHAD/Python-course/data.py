import re


def main():
    lines = open('input.txt')
    for line in lines:
        result = re.match(r'\d\d\d\d([.]\d\d[.]|[/]\d\d[/]|[\-]\d\d[\-])\d\d$', line)
        result2 = re.match(r'\d\d([.]\d\d[.]|[/]\d\d[/]|[\-]\d\d[\-])\d\d\d\d$', line)
        result3 = re.match(r'(\d|\d\d)\s*[а-яА-Я]+\s*\d\d\d\d$', line)
        if result3 is not None or result is not None or result2 is not None:
            print('YES')
        else:
            print('NO')
    return


main()
