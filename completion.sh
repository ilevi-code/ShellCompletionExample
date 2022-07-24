function _foo_completion() {
	_get_comp_words_by_ref -n ':'
	COMPREPLY=( $(COMP_CWORD=$cword _FOO_COMPLETE=complete $1 ${words[@]:1}) )
	return 0
}

complete -F _foo_completion foo
