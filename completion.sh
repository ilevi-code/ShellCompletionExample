_foo_completion() {
    local IFS=$'
'
    COMPREPLY=$(COMP_CWORD=$COMP_CWORD _FOO_COMPLETE=complete $1 ${COMP_WORDS[@]})
    return 0
}

complete -F _foo_completion foo