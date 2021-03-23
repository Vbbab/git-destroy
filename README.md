# `git-destroy`: De-`git init` a github repo


Allows you to, in the final state that you want your local repo to be in, `destroy` that repository -- removing `.git/` and rendering it as a regular directory of files that is
no longer a `git` repo.

## Compiling

Use any old compiler, except note the following:
> * **Use C++ 17. Especially on Windows.**
> * **:exclamation: Make sure your output binary has the name `git-destroy` (`.exe` for windows) or it will be ineffective as a `git` add-on. Also make sure it is on `PATH`.**
<br />
<br />


> | :warning: Warning: Linux untested. |
> |-|
> 
> It should work fine, but no guarantees.
