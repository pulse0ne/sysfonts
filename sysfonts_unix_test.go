package sysfonts

import (
	"fmt"
	"testing"
)

func TestFonts(t *testing.T) {
	fonts := Fonts()
	for _, f := range fonts {
		fmt.Printf("%+v\n", f)
	}
}
