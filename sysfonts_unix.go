// +build linux

package sysfonts

/*
#cgo LDFLAGS: -L . -lfontconfig
#include "headers/sysfonts_unix.h"
*/
import "C"
import (
	"unsafe"
)

func newFontDescription(cf *_Ctype_struct__FontDescription) *FontDescription {
	fd := &FontDescription{
		Name:      C.GoString(cf.name),
		Path:      C.GoString(cf.path),
		Family:    C.GoString(cf.family),
		Style:     C.GoString(cf.style),
		Weight:    FontWeight(int(cf.weight)),
		Width:     FontWidth(int(cf.width)),
		Italic:    bool(cf.italic),
		Monospace: bool(cf.monospace),
	}
	return fd
}

// Fonts ...
func Fonts() []*FontDescription {
	cFonts := C.getFonts()
	defer C.freeFontList(cFonts)
	n := int(cFonts.length)
	fontSlice := (*[1 << 30]*_Ctype_struct__FontDescription)(unsafe.Pointer(cFonts.fonts))[:n:n]
	fonts := make([]*FontDescription, n)
	for i, f := range fontSlice {
		fonts[i] = newFontDescription(f)
	}
	return fonts
}
