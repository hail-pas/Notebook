# Vim

## reference
```shell
# movement
h j k l   # left/down/up/right
b  w      # cursor on word start left/right
ge e      # cursor on word end left/right
{  }      # begining of paragraph previous/next
(  )      # beginning of setence pervious/next
^  $      # line begin/end
g^ g$     # line begin/end
nG ngg    # nth line, default last/first line
n|        # nth column of current line

B  W      # space separated as b w
GE E      # space separated

g0 gm     # begin/middle column of line


# insertion replace
i  a        # insert before/after cursor
I  A        # insert beginning/end of line
gI          # insert beginning of line
o  O        # new linr below/above
rc          # replacce character with c
grc         # like rc
R           # replace chars starting at cursor
gR          # like R
C           # clear chars starting at cursor
cc          # whole line clear => S

# search
/       # search down
?       # search up
n
```
{
    ()
}
