This is a configurable lexical analyzer written by C,by modifying my older project:Simple-regex-engine,what we need is a file to discribe all the lexical unit.For example,in a file named regex.txt,we can discribe some lexical units like this:
```
identifier:[_a-zA-Z0-9]+
num:[0-9]+
symbol:\+|\*|?
```

