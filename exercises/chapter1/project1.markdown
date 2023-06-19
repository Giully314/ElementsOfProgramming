Equality can be defined in multiple ways that depend
on properties of the types.
If a type is uniquely represented, that is, for each value we have only one interpretation, then we can compare the bits (datum) of the 2 values and check if they are equal.
Two values can be equal but different in the sequence of bits if the two entities that represent are equal. For example 1/2 and 2/4 could have different sequence of bits but refer to the same entity.
We can extend the notion of equality between different types if we work on the interpretation (the entities that are associated to a particular datum) rather than the bits.  
An example is the float type. Because of the finiteness representation of floating numbers, comparing two numbers with bits could lead to unexpected results. We can just choose to work on the first n digits after point to compare two numbers and avoid errors.
