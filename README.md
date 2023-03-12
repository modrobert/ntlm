# ntlm

### Copyright (C) 2023 by Robert &lt;modrobert@gmail.com&gt;
### Software licensed under Zero Clause BSD.

---

### Description

C program which calculate NTLM hash for given string with UTF-8 support.

---

### Usage

<pre>
$ ntlm
ntlm v0.10 by modrobert in 2023
Syntax: ntlm &lt;string&gt;
</pre>

---


### Build

Use 'make' or compile manually with:
<pre>
gcc -O3 -Wpedantic ntlm.c -o ntlm -lcrypto
</pre>

---

### Example output
<pre>
$ ntlm 😁
309453CC997A7C40AABD68779FD6980C

$ ntlm test
0CB6948805F797BF2A82807973B89537
</pre>
