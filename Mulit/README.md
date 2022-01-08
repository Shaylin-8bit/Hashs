# Mulit

<p>
    Mulit is a multiplication based hash, designed to correct some of the problems in the basic sum hash, while still retaining its simplicity. I created as an experiment to learn more about the basics of hashes, and like it for it's simplicity. It's an incredibly easy hash to implement, and I believe would be great for use in hash tables. Though I take credit for writing this implimentation, I can't, in good faith, take credit for the idea, as given its simplicity I would be surprised if I was the first to use this concept.
</p>

# Principles

<p>
    Using multiplication over addition has a few pros and cons. When multiplying every element in an array, you have the possibility to generate a much larger value, rather than simply summing the values in an array. As the array grows in size this possibility also increases. However there is the danger of your value becoming locked on zero. Because any number multiplyed by zero is zero, than a single zero value in an array causes and issue. As such, for every iteration, Mulit will only perform multiplication if the result is not zero.
</p>

<p>
    The biggest issue I find with the basic sum hash is that the order of characters does not matter, meaning you can receive many collisions. This is simply based on the commutative property:
</p>

```
    a + b = b + a
```

<p> 
    This same property carries over to multiplication. To fix this, Mulit also uses subtraction. At every iteration, result is first multiplied by the current bytes value (assuming this does not result in zero), and then has the value of the next byte subtracted from it (again assuming this does not result in zero). 
</p>

# Drawbacks

<p>
    Though Mulit solves the issues of character order importance that the sum hash has, and improves on the range of values that can be created, it still on average generates values in a fairly small range. This range increases as the size of the array does, but not in a very practical manner. 
</p>