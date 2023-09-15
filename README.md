# EdgeCases List
- [x] example
- [ ] 파이프가 맨 앞에 오는 경우 (fail)  
| ls | cat
- [ ] 파이프가 맨 마지막에 오는 경우 (fail)  
ls | cat |
- [ ] 여러 리다이렉션이 중첩되는 경우 덮어씌워 함 (exception)
1. 다음 경우는 c에 out
cat a >> b > c
2. 다음 경우는 c에 out
cat a > b > c
3. 다음 경우는 append 하나만 작동
cat a > c >> b
4. <. << 도 마찬가지 