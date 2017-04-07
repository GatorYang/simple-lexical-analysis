# simple-lexical-analysis
lexical analysis task for a limited version
(i.e., the depth of the nested loops) of a programming language. Lexical analysis is the
first stage that compilers parse and detect the possible syntax errors.
Ideally, any new (programming) languages can be designed and analyzed in the similar
manner. It will analyze a Pascal-and-C-like language in it.

Given a segment of the source code, the C++ code will analyze the code and
extract all tokens, which include:
• Keywords: keywords are the words reserved by the language. They are all upper-
case. In the case of this simplified language, the keywords are restricted to the set
{ ”BEGIN”, ”END”, ”FOR” }
• Identifiers: An identifier is used to describe the variables, which are all lower-case
• Constants: Numbers like 10, ... .
• Operators: all arithmetic operations (i.e., +, -, *, and /), ”++” and ”=”
• Delimiters: like ”,” and ”;”
