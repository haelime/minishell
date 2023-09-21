# EdgeCases List
- [x] example
- [x] 파이프가 맨 앞에 오는 경우 (fail)  
```
| ls | cat
```
- [x] 파이프가 맨 마지막에 오는 경우 (fail)  
```
ls | cat |
```
- [x] 파이프가 여러 개 연달아 오는 경우 (fail)
```
ls | | cat  
```
- [x] 여러 리다이렉션이 중첩되는 경우 덮어씌워 함 (exception)
```
1. 다음 경우는 c에 out
cat a >> b > c
2. 다음 경우는 c에 out
cat a > b > c
3. 다음 경우는 append 하나만 작동
cat a > c >> b
4. <. << 도 마찬가지
``` 
- [ ] 리다이렉션만 존재하는 경우 (실행은 되어야 함)
```
< a  
<< EOF  
< a | cat  
> a | cat  
<< EOF | cat  
cat a | < a | cat
```
- [x] 리다이렉션 문법 에러
```
> >> a  
> > a  
```