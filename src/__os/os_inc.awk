#BareLibC -- Copyright (C) 2010 Gergely Gabor Nagy (ngg@ngg.hu) -- see attached LICENSE file

BEGIN {
	FS = "[ \t\n]+"
	printf "#ifndef ____OS_INC_H\n"
	printf "#define ____OS_INC_H\n"
	printf "\n"
}
$2 == "equ" {
	printf "#define __%s \".equ %s, %s\\n\"\n", $1, $1, $3
}
END {
	printf "\n"
	printf "#endif //____OS_INC_H\n"
	printf "\n"
	printf "///\n"
	printf "\n"
}

###
