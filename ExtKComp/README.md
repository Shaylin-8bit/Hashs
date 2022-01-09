# ExtKComp

<p>
    The ExtKComp, or Extended Key Compilation, hash is an experimental hash I'm writing on top of the <a href="../Mulit/README.md"> hash </a>. It works on the principle of generating 64 bit sectors of numbers and then stacking them to create a single 8 byte value. This is my first attempt at a more reallistic hash, and hopefully will be an improved second hash design for my Cryptic program.
</p>

* Warning:  At the date of this writing enought testing has not yet been done to truly say how effecient it actually is.

# Principle

<p>
    My previous hashes have all had the problem of generating value in a fairly small range. After doing some research, I got idea of combining smaller numbers together to generate a larger one.
</p>

<p>
    ExtKComp starts with an array of bytes like, and the first step is to make sure it is formatted and extended properly. Assuming the array's length in bytes is not already at least 64, and a multiple of 8, than it is padded with 0 bytes until it reaches that point. Given the key `key`, it would look something like this:
</p>

```
starting key
107 101 121
```
```
extended key
107 101 121 0   0   0   0   0   0   0   0   0   0   0   0   0
0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0
0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0
0   0   0   0   0   0   0   0   0   0   0   0   0   0   0   0
```

<p> 
    The next step is to populate the key, and here is where we use a version of Mulit. It loops through the key, from the first 0 byte to the last, and sets each to the logorithim, of abs, on Mulit, on the bytes before, * 100. So in the above the fourth bytes will be set to Mulit of `{107, 101, 121}` with a factor of , which will be -29. The pattern repeats for every byte, giving us a final result of:
</p>

```
107  101  121  -29   11  105 -105  -69 -105  -81  -75  -28  -96  45  -64 -85
 23  -45  -19  -77   47  -20  111  -44   70 -119 -103  -84 -106 -65  -68   7
-95  121  -13  111  -85  -42 -109  -91  -13  -22   90 -126  100  70  104  80 
 -3   72   64   69 -125  -89   12   58 -110  -62  -43 -122  126 -46  -26 -79
```

<p>
    Now ExtKComp begins stacking the sectors so it can generate a final result. A 2d array is created that is 8 bytes wide and the number of sectors tall. Then each element in each sector is added to the new stack.
</p>

```
   1    2    3    4    5    6    7    8
________________________________________
 107  101  121  -29   11  105 -105  -69
-105  -81  -75  -28  -96  45  -64   -85
  23  -45  -19  -77   47  -20  111  -44  
  70 -119 -103  -84 -106  -65  -68    7
 -95  121  -13  111  -85  -42 -109  -91
 -13  -22   90 -126  100   70  104   80 
  -3   72   64   69 -125  -89   12   58
-110  -62  -43 -122  126  -46  -26  -79
```

<p>
    This is no compiled into a result by setting each byte, in an 8 byte number, to the result of Mulit on each column of the stack. So the first byte would be Mulit of `{107, -105, 23, 70, -95, -13, -3, -110}`. This results in:
</p>

```
-90  28  71 -30 -42  10  22 -76
```

<p>
    These bytes are now returned as a single 8 byte number. 
</p>

```
12976571294350253222
```

# Disclaimer

<p>
    There are a few things I'd like to get off my chest.
</p>

* First, at the time of writing this, I'm incredibly new to hashes and have very little experience with them. 
* Second, this is only my first attempt at creating a decent hash function.
* Third, this hash hasn't been put through rigorous testing yet, and there are almost certainly bugs in it that I haven't found yet.

<p>
    Given the above, please do not trust this hash to work in production code. I've written it for my eduacation, hopefully to inspire others, and just for the fun of it. I can't guarentee it will work consistently, effeciently, or at all.
</p>

<p>
    All that being said, I hope to continue work on and imporove it as time goes on. Please provide feedback if you see a bug or just something that can be done better!
</p>
