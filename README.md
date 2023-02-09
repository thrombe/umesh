
<!-- // none of the char* stored in structs are null terminated -->

- todo
  - [ ] KeyValue.value cannot be freed properly when freeing KeyValue and anything that stores a KeyValue
    as KeyValue.value may have something heap allocated inside it. replace current free functions
    - [ ] maybe just pass a function to free it in free functions like ```free_object(&free_user)```
    - [ ] maybe pass the free function when creating the hashmap/whatever objects
  - [x] user key/value operations
    - [x] insert
    - [x] delete
    - [x] get
    - [x] undo
    - [x] redo
    - [x] print
  - [x] print operation
  - [ ] global operation queue
  - [x] UserManagementSystem
    - [x] insert
    - [x] delete
    - [x] get
  - [x] seperate the code in multiple files
  - [ ] deal with usage of ```Key``` and ```Key*``` as parameters
    - [!] eliminate the use of ```Key*``` in parameters where not necessary as it is treated as Copy
    - [ ] but maybe ```Key``` can be used to indicate if the function takes ownership
  - [!] check if clone_keyvalue safe
