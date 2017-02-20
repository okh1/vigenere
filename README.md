# vigenere
With this tool, you can:
1. **Encode** text files using the Vigenere cipher with a keyword you choose
2. **Decode** already encoded text, providing a keyword
3. Attempt to **break** the cipher, guessing the keyword length first and then the most likely keywords. The index of coincidence and a chi-squared test are used, with pretty good results!

## Usage
The program will guide you with a step-by-step menu.

## Compiling
Compilation is extremely straightforward:
`gcc -o vigenere main.c Vigenere.c`
Remember to save the `prob-en.txt` file in the same folder as the executable.
