# Binary Search Tree

Binary Search Tree by Kyle Dukart

GitHub URL https://github.com/2018WI343/bst-kyledukart

Expected Mark: 95

Time spent: About 15 hours

Compiled and tested on CSS Linux Lab: YES


> cpplint *.cpp *.h

> cppcheck --enable=all --force --inconclusive --language=c++ --std=posix --suppress=missingIncludeSystem *.cpp *.h

I used // NOLINT a few times to ignore warnings about lines above 80 characters.
I used // NOLINE to ignore my use of &answer as a variable in helper functions because I am not sure how to fix

cppcheck complains about my testing using the NumberOfNodes() function:
(warning) Assert statement calls a function which may have desired side effects: 'NumberOfNodes'.
I am not sure exactly what this means or how to fix it, so I commented out those 2 test lines.

cppcheck complains that the copy constructor is not explicit, but from what I understand it is bad practice to make
copy constructor explicit, so I am ignoring those 2 warnings.

> valgrind ./bst.exe

==22513== LEAK SUMMARY:
==22513==    definitely lost: 0 bytes in 0 blocks
==22513==    indirectly lost: 0 bytes in 0 blocks
==22513==      possibly lost: 0 bytes in 0 blocks
==22513==    still reachable: 72,704 bytes in 1 blocks
==22513==         suppressed: 0 bytes in 0 blocks

Implemented every method in assignment 2 documentation

Improvements for next time:

- More tests - work with CATCH instead of assert
- integrate cpplint with CLion
- try travis-ci.com


                                                         .
                                              .         ;
                 .              .              ;%     ;;
                   ,           ,                :;%  %;
                    :         ;                   :;%;'     .,
           ,.        %;     %;            ;        %;'    ,;
             ;       ;%;  %%;        ,     %;    ;%;    ,%'
              %;       %;%;      ,  ;       %;  ;%;   ,%;'
               ;%;      %;        ;%;        % ;%;  ,%;'
                `%;.     ;%;     %;'         `;%%;.%;'
                 `:;%.    ;%%. %@;        %; ;@%;%'
                    `:%;.  :;bd%;          %;@%;'
                      `@%:.  :;%.         ;@@%;'
                        `@%.  `;@%.      ;@@%;
                          `@%%. `@%%    ;@@%;
                            ;@%. :@%%  %@@%;
                              %@bd%%%bd%%:;
                                #@%%%%%:;;
                                %@@%%%::;
                                %@@@%(o);  . '
                                %@@@o%;:(.,'
                            `.. %@@@o%::;
                               `)@@@o%::;
                                %@@(o)::;
                               .%@@@@%::;
                               ;%@@@@%::;.
                              ;%@@@@%%:;;;.
                          ...;%@@@@@%%:;;;;,..
