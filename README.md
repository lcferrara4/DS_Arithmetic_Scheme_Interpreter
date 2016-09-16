Project 01: uScheme
===================

This is a simple implementation of a [Scheme] interpreter that supports the
following syntax:

    <digit>         = 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9
    <number>        = {<digit>}
    <op>            = - | + | * | /
    <expression>    = (<op> <expression> <expression>) | <number>

Examples
--------

    :::scheme
    1
    (+ 1 2)
    (+ 1 (- 2 3))
    (+ (* 1 2) (- 3 4))

[Scheme]:   https://en.wikipedia.org/wiki/Scheme_(programming_language)


1. The complexity of the interpretor is O(n), where N is the number of nodes in the tree.  As N grows the complexity increases at a linear rate.  This is because each additiona of N is another operation on the stack and another node to add to the tree.  

2. The uscheme executable size is 107K while the uschemeSmart executable size is 130K.  This information is found using the 'ls -l -h' command.  The amount of memory used is found using the measure command with 'input' directed into uscheme or uschemeSmart.  When run, uscheme used 2.554688 bytes in .033994 seconds.  uschemeSmart used 3.308594 Mbytes in .052991 seconds.   While the uschemeSmart program takes up more space and more memory we still prefer it over uscheme due to the ease of implementation with smart pointers.  If memory usage was a major issue (i.e. if we were working at a company that payed for memory by the Mbyte) then the uscheme implementation would be a better choice.  The weight of the trade-off between memory usage and file size and implementation varies case to case.  As students we prefer the easier and more convenient implementation and believe the extra memory usage to be worth it.  

3. To support arbitrary length expressions the abstract syntax tree would have to deal with operand with more than two numbers as children.  One way to implement this would be to split the arbitrary length operation into pairs and push these pairs into a seperate abstract syntax tree.  For example, if the operation was (+ 1 2 3 4 5) the new program would have to create ceiling of N/2 (N being the amount of numbers) trees: (+ 1 2), (+ 3 4 ), 5.  The parser would have to be updated to accomodate this by parsing until a ')' is reached, creating new Nodes as follows: (operand), (number1), (number2), and then a new tree with: (repeated operand), (number3), (number4), etc...  If there were an odd amount of numbers the parser would create an abstract tree of just one node.  The program would compute the sum of each subtree in a while loop until only two sums are left.  Then the full sum (or other operation) could be calculated normally.  The interpretor would not have to be modified with this method.

Work Distribution: 
    We all worked on each part of the project together.  We used pair programming techniques and switched 'drivers'.  Each member contributed evenly to the project from start to finish.  


