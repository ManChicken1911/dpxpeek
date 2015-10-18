all: dpxpeek

dpxpeek: dpxpeek.cpp dpxpeek.h endian.cpp endian.h helpers.cpp helpers.h
	g++ dpxpeek.cpp endian.cpp helpers.cpp -o dpxpeek
