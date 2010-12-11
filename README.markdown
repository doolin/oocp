# Object Oriented C Programming

Yes, it can be done.  You really can write c in object-oriented style.
You're not going to get all the bells and whistles of C++ or Java,
but if you need to tidy up a well-defined c library, these techniques
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



## Simple prototyping trick for c "modules"

There really isn't a generally defined way to create a 
"module" in the c programming language.  However, with 
a little care one can define functions that are strictly
limited to a single file, versus those functions in that 
same file that one might want to use elsewhere.

Here's how we do that.

1. Functions you want to use elsewhere, export these in a 
matching header file.  For example, `foo.c` has it's 
matching `foo.h`.  

1. Internal functions (i.e., private), define in `foo.c`, 
but define the function before you use it.  This way you 
avoid chasing around function prototypes as you develop 
your API, and your code won't compile if the arguments 
don't match.   

It looks like this (from prototrick.c): 


    #include <stdio.h>
    
    void 
    foo(void) {
       printf("From foo...\n");
    }
    
    int 
    main(int argc, char ** argv) {
       foo();
       return 0;
    }

`foo()` is called after `foo` is defined.

If you don't do this, you will have to add a
prototype for every function.


Once in a while, you may find something that has a
circular dependency.  In that rare case, prototype
as usual.

## Compiling a module as standalone program

There are times when it's useful to compile a module as 
a program which can run by itself, but also as a part
of a library.

One way to do that is to wrap a `main()`  function
at the bottom of the `mymod.c` file like so:

    #ifdef mymod_STANDALONE
    int
    main(int argc, char ** argv) {
       return 0;
    }
#endif /* mymod_STANDALONE */


The key to this is adding `-D$*_STANDALONE` to your compiler
command. 

Read more about make's 
[automatic variables](http://www.gnu.org/software/make/manual/make.html#Automatic-Variables).

