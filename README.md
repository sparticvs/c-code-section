C Code Section Test
===================

I have been working on some firmware recently and thought about using this
method when trying to solve implementing an abstraction layer. Seems to do
exactly what I am looking for.

Basically, you put the addresses for the functions in a special section. You
can then run all of them. This is useful for having driver authors write an
init function that will register correctly without extra functions and happens
at compile time not during runtime. No more need for the dev to go find the
best place to put their code.
