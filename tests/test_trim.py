import subprocess as sp
import os
stri = '  a  '
r = sp.check_output(["/Users/faru/Codam/minishell/minishell", stri])
print("status", r)


