# Object Oriented C Programming

Yes, it can be done.  You really can write c in object-oriented style.
You're not going to get all the bells and whistles of C++ or Java,
but if you need to tidy up a well-defined c library, there techniques
can be enormously useful.

The type of structure where this works best is (again) fairly small
and well-defined, with a shallow, unambiguous inheritance, and 
where polymorphism isn't overly critical. 

This is not a very high priority project, but I'm happy to answer 
questions.

## Starting from the beginning 

Just as Test and Behavior Driven Development start with the writing 
scenarios and tests, it's traditional for an open source c program 
to start with getting the build system right.

Over the years, building c code has become much easier, as the build
tools have become more refined.  

We're using the [automake](http://www.gnu.org/software/automake/ "GNU Automake") 
family of tools for this simple code.

Long story short, the usual should make it all happen:

    $ ./configure
    $ make 

You should find the simplest example here `bin/snafu`
