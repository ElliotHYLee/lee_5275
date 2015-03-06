CON

  _clkmode      = xtal1 + pll16x  ' Change to xtal1 + pll8x for Propeller Backpack.
  _xinfreq      = 5_000_000       ' Change to 10_000_000    for Propeller Backpack.

  ALTITUDE      = 200             ' Your altitude in feet.

OBJ

  bar   : "29124_altimeter"
  pst   : "parallax serial terminal"

PUB start | p, sp, cm

  pst.start(115200)                                          ' Start Parallax serial terminal.
  bar.start(bar#QUICKSTART, bar#BACKGROUND)                 ' Start altimeter for QuickStart with background processing.
  bar.set_resolution(bar#HIGHEST)                           ' Set to highest resolution.
  cm := bar.m_from_ft(ALTITUDE * 100)                       ' Convert altitude in feet to cm.
  repeat
    p := bar.average_press                                  ' Get the average pressure.
    sp := bar.sealevel_press(p, cm)                         ' Convert to equivalent sea-level pressure, given altitude.
    pst.str(string(pst#HM, "    Local pressure:"))          ' Print local pressure heading.
    pst.str(bar.formatn(p, bar#MILLIBARS | bar#CECR, 8))    ' Print local pressure in millibars, clear-to-end, and CR.
    pst.str(bar.formatn(p, bar#TO_INCHES | bar#CECR, 27))   ' Print local pressure in inches Hg, clear-to-end, and CR.
    pst.str(string(pst#NL, "Sea-level pressure:"))          ' Print sea-level pressure heading.
    pst.str(bar.formatn(sp, bar#MILLIBARS | bar#CECR, 8))   ' Print sea-level pressure in millibars, clear-to-end, and CR.
    pst.str(bar.formatn(sp, bar#TO_INCHES | bar#CECR, 27))  ' Print sea-level pressure in inches Hg, clear-to-end, and CR.
    if (pst.rxcount)                                        ' Respond to any key by clearing screen.
      pst.rxflush
      pst.char(pst#CS)