#
# ~/.bashrc
#

# If not running interactively, don't do anything
[[ $- != *i* ]] && return
alias scrot='scrot ~/Pictures/%Y-%m-%d-%H:%M:%S.png'
alias ls='exa -l --group-directories-first'
#PS1='[\u@\h \W]\$ '
PS1='\[\e[1m\][\[\e[32m\]\u\[\e[37m\]@\[\e[36m\]\h\[\e[37m\] \W]\[\e[34m\] $\[\e[00m\] '
