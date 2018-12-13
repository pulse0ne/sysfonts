package sysfonts

// FontWeight describes the weight (boldness/thinness). range: 100-900
type FontWeight int

// these consts describe the various font weights
const (
	_ FontWeight = iota * 100
	FontWeightThin
	FontWeightUltraLight
	FontWeightLight
	FontWeightNormal
	FontWeightMedium
	FontWeightSemiBold
	FontWeightBold
	FontWeightExtraBold
	FontWeightUltraBlack
)

// FontWidth describes the spacing between glyphs. ranges: 1-9
type FontWidth int

// these consts define the font widths
const (
	_ FontWidth = iota
	FontWidthUltraCondensed
	FontWidthExtraCondensed
	FontWidthCondensed
	FontWidthSemiCondensed
	FontWidthNormal
	FontWidthSemiExpanded
	FontWidthExpanded
	FontWidthExtraExpanded
	FontWidthUltraExpanded
)

// FontDescription is the main structure that fonts are parsed into
type FontDescription struct {
	Name      string     `json:"name"`
	Path      string     `json:"path"`
	Family    string     `json:"family"`
	Style     string     `json:"style"`
	Weight    FontWeight `json:"weight"`
	Width     FontWidth  `json:"width"`
	Italic    bool       `json:"italic"`
	Monospace bool       `json:"monospace"`
}
