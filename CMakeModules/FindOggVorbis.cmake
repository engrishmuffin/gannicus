# Locate Ogg Vorbis libraries

FIND_PATH(VORBIS_INCLUDE_DIR vorbis/vorbisfile.h)

FIND_LIBRARY(VORBIS_LIBRARY 
	NAMES vorbis)

FIND_PACKAGE_HANDLE_STANDARD_ARGS(OGG_VORBIS
	REQUIRED_VARS
	VORBIS_LIBRARY
	VORBIS_INCLUDE_DIR)
