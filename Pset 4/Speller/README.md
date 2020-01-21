# Questions

## What is pneumonoultramicroscopicsilicovolcanoconiosis?

an invented long word said to mean a lung disease caused by inhaling very fine ash and sand dust.

## According to its man page, what does `getrusage` do?

getrusage() returns resource usage measures for processes, for example CPU time and memory used.

## Per that same man page, how many members are in a variable of type `struct rusage`?

There are 16 members in a structure.

## Why do you think we pass `before` and `after` by reference (instead of by value) to `calculate`, even though we're not changing their contents?

Passing large structs by value is slow and takes up a lot of memory. If you are passing large structs by value instead of by reference, copies of the structs will be on the stack, which may lead to stack overflow.

## Explain as precisely as possible, in a paragraph or more, how `main` goes about reading words from a file. In other words, convince us that you indeed understand how that function's `for` loop works.

The for loop reads one char at a time until the end of the file is reached which is where the for loop ends. The for loop makes use of the fgetc function
to accomplish this. By stating c = fgetc(file) the fgetc function gets a char from the file pointer and returns an int, which is then assigned to the int c.
By using the condition c != EOF in the for loop, the for loop will continue until the end of the file is reached. Inside of the for loop there is a logical sequence
of if(if), else if, else if (if). Summarising the logical sequence:
1) If the character is an alphabetical character or an apostrophe that is not at index 0 of the word, the character is appended to the word array.
2) Else if the character is numerical, the word is ignored and we skip ahead to the next word, because numerical values isn't words.
3) Else if we read a space such as \n or punctuation, we know we are at the end of the word so all we have to do is terminate the word by adding a \0 to the word array.

## Why do you think we used `fgetc` to read each word's characters one at a time rather than use `fscanf` with a format string like `"%s"` to read whole words at a time? Put another way, what problems might arise by relying on `fscanf` alone?

fscanf will read an array of characters until a whitespace is found. The problem is that fscanf will read punctuation as part of the word, and we know that
some words within our text file will end with punctuation and can make it more difficult to read in the words without also reading the unwanted punctuation.
If the string is also longer than we might expect and we read it in with fscanf, we could end up with a segmentation fault.

## Why do you think we declared the parameters for `check` and `load` as `const` (which means "constant")?

With const char* we prevent changes to the string to which the parameter is pointing to. Whenever const is used it is mostly to prevent change,
and in this case we do not want to accidentally make changes to our dictionary or word we received as parameters to our function.