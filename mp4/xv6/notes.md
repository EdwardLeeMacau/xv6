# Code tracking

## Large file write()

Related code

```
sys_write()
-> filewrite()
-> writei(..., user_src=1, ...)
   ->     addr := balloc()
   -> buf_addr := bread()
   -> do i need log_write() for intermediate node?

sys_unlink()
-> writei()
-> iput()
    -> itrunc()
    -> iupdate()
```

Modification

1. MAXFILE >= 66666 to fulfill sys_write() success
2. struct inode && struct dinode
    number of entries for NDIRECT consist to 13
```