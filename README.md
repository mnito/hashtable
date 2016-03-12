# Hash Table Module in C

## Notes

A hash table implementation.

There is also a command line interface to the module.


## Author

Michael P. Nitowski <[mpnitowski@gmail.com](mailto:mpnitowski@gmail.com)> 
    (Twitter: [@mikenitowski](https://twitter.com/mikenitowski))
    
## License

The MIT License

## Notes

To compile the command line client:

Navigate to the folder using the command line and:

For gcc:

```cmd
gcc -O3 -std=c99 -Wall -o htcli *.c
```

For clang:

```cmd
clang -O3 -std=c99 -Wall -o htcli *.c
```

This implementation uses strdup (included as a header). 
This function is not a standard C function, but compilers may make it 
available. If there is a conflict in standard compilation try using 
-std=c99 -pedantic -Wall flags.

The header file can cause a conflict if strdup is perceived
as a standard function, so removing that file may also work. 
If you need a strdup implementation (as in your platform does not have it 
available), there is an implementation in the etc folder.
