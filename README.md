# file_storage
This is a file storage system for the linux operating system. It will sort files into music, images, videos, documents and executable files. It also has a search feature to find and view files. The history of opened files can also be viewed.

To run the program, you need to have the ncurses library installed. Compile the program.c file with the following command. Run the executable in the folder whose files you want sorted.

```
gcc program.c -lncursess
./a.out
```
**make sure to not change the name of the program file or the executable as the program will sort files with any other name**

The directory you run the program in must also have the following folders

```
Music
Images
Videos
Documents
Executable
Unclassified
```
