# Own implementation of utilities for Linux cat and grep.  

## cat - utility for outputting the contents of a text file  
### cat -flag1 file1, file2, -flag2
### flags:  
-n number all strings  
-b number only non_blank strings  
-s squeeze blank strings  
-v show nonprintable symbols  
-e (-E) show strings end  
-t (-T) show tabs  
flags work both separately and together

## grep - utility for searching the contents of a text file  
### grep -flag1 pattern file1, file2 -flag2
### flags:  
-n numbers the found lines  
-c get number of matches  
-i ignore case  
-v invert request  
-o show only matched part  
-l list mathced files  
-h hide filenames  
-f get pattern from file  
-e print additional pattern  
-s supress error  
flags work both separately and together  
