# Minishell tests

Here are some tests for the minishell project of school 42 cursus. It's not exaustive, so don't limit yourself with this tests.
These tests are not all mines. Credits to vgoldman, mashar, and jecaudal.

tmarx
# Tests

- [OK] echo bonjour ; |
- [OK] echo bonjour | |
- [OK] |
- [OK] echo bonjour |;
- [OK] echo bonjour \; ls
- [OK] echo bonjour > test\ 1
- [OK] cd $HOME/Documents
- [OK] echo "\s" & echo "\\s"
- [OK] echo \>
- [OK] echo -n -n -nnnn -nnnnm
- [X] cat /dev/random | head -n 1 | cat -e
- [OK] unset var1 # with undefined var1
- [OK] export "" et unset ""
- [OK] echo test > file test1
- [OK] $
- [OK] not_cmd bonjour > salut
- [OK] env puis export puis env # vars aren't sorted
- [ ] cat Makefile | grep pr | head -n 5 | cd test (mybin) # check status code
- [ ] cat Makefile | grep pr | head -n 5 | cat test (bin) # check status code
- [ ] cat Makefile | grep pr | head -n 5 | hello (NA) # check status code
- [OK] echo bonjour >>> test
- [OK] echo bonjour > > out
- [OK] echo 2 >> out1 > out2
- [OK] echo 2 > out1 >> out2
- [OK] cat < test # with non-existent test
- [OK] export var; export var=test
- [OK] echo bonjour > $test # with test not defined
- [OK] file_name_in_current_dir
- [?] cd ../../../../../.. ; pwd
- [ ] ctrl-C . 130 sur bin(ex : sleep 10)&line vide
- [ ] ctrl-\ .131 sur bin
- [ ] echo "bip | bip ; coyotte > < \" "
- [OK] cat | cat | cat | ls # check outputs order
- [OK] $bla # with bla not defined
- [ ] export var ="cat Makefile | grep >"
- [OK] export "test=ici"=coucou
- [OK] c$var Makefile # with var=at
- [OK] $LESS$VAR
- [OK] /bin/echo bonjour
- [OK] not_cmd
- [OK] sleep 5 | exit
- [OK] echo bonjour > $test w/ t
- [X] "exit retour a la ligne"
- [X] minishell # binary not in path without "./" before
- [OK] cat diufosgid # check exit code
- [OK] exit # should return the last exit code value
- [X] exit -10
- [X] exit +10
- [ ] ;
- [ ] echo coucou | ;
- [OK] echo "$HOME"
- [X] echo '$HOME'
- [ ] export ; env # display is different for both commands
- [ ] echo \$HOME
- [X] > log echo coucou
- [OK] echo hudifg d | | hugdfihd
- [OK] echo
- [OK] echo simple
- [OK] echo -n simple
- [ ] echo '\'
- [ ] echo "\"
- [ ] echo "\\"
- [ ] echo "\n \n \n"
- [ ] echo "\n \\n \\\n"
- [ ] echo ;;
- [ ] echo hi";" hihi
- [ ] echo hi "   ;   " hihi
- [OK] cd
- [OK] cd .
- [OK] cd ~
- [OK] cd /
- [OK] cd no_file
- [OK] cd a b c d
- [OK] pwd a
- [OK] pwd a b c d
- [OK] export LOL=lala ROR=rara
- [OK] unset LOL ROR
- [OK] export "HI= hi"
- [OK] export "HI =hi"
- [OK] /bin/ls
- [OK] # write something the press ctrl+c
- [OK] # write something then press ctrl+d
- [OK] # write something then press ctrl+\
- [OK] echo $?
- [?] l^Ds
- [OK] echo |
- [OK] | echo
- [OK] sort | ls # check output order
- [OK] cat < >
- [OK] cat < <
- [OK] cat > >
- [X] > a ls > b < Makefile
- [OK] echo > a Hello World!
- [OK] > a echo Hello World!
- [OK] cat < Makefile | grep gcc > output
- [OK] exit 0 | exit 1
- [OK] exit 1 | exit 0
- [X] env | grep PATH | cat









CMD_IS_DIR - takes precedence over NOT_EXEC
	exec_call
		is_local
			bash: full_path/dir: is a directory
			bash: exec: full_path/dir: cannot execute: Undefined error: 0
		not_local
			bash: exec: dir: not found
	not_exec_call
		is_local
			bash: ./dir: is a directory
		not_local
			bash: dir: command not found

CMD_NOT_EXEC
	exec_call
		is_local
			bash: full_path/file: Permission denied
			bash: exec: full_path/file: cannot execute: Undefined error: 0
		not_local
			bash: full_path/file: Permission denied
			bash: exec: full_path/file: cannot execute: Undefined error: 0
	not_exec_call
		is_local
			bash: ./file: Permission denied
		not_local
			bash: /Users/giuliovalente/Desktop/42/42_Projects_GIT/core_3/minishell/olapo.sh: Permission denied

CMD_NOT_FOUND
	exec_call
		is_local
			bash: full_path/file: No such file or directory
			bash: exec: full_path/file: cannot execute:
		not_local
			bash: exec: file: not found
	not_exec_call
		is_local
			bash: ./file: No such file or directory
		not_local
			bash: file: command not found