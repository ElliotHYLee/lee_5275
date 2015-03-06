CON

  _clkmode      = xtal1 + pll16x  'Change to xtal1 + pll8x for Propeller Backpack.
  _xinfreq      = 5_000_000       'Change to 10_000_000    for Propeller Backpack.

  #0, TYPE, DIGIT
  #0, ALTIMETER, BAROMETER

OBJ

  alt   : "29124_altimeter"
  pst   : "parallax serial terminal"

VAR

  long sea_p, cur_t, cur_p, avg_t, avg_p, med_t, med_p
  long cur_a, avg_a, med_a, loc_a, input_data, input_sign
  byte input_type, input_state, function 

PUB  start | data, reading, unit, s

  pst.start(115200)
  alt.start(alt#QUICKSTART | alt#MS5611, alt#BACKGROUND)
  alt.set_resolution(alt#RES_4096)
  pst.str(@grid)
  repeat
    alt.pause
    longmove(@sea_p, alt.results_addr(alt#SEA_P), 7)
    alt.resume
    pst.position(30, 1)
    if (function == BAROMETER)
      cur_a := avg_a := med_a := loc_a
      sea_p := alt.sealevel_press(avg_p, loc_a)
      s := string("Barometer")      
    else
      cur_a := alt.altitude(cur_p)
      avg_a := alt.altitude(avg_p)
      med_a := alt.altitude(med_p)
      s := string("Altimeter")

    if (cnt & $f00_0000 == $f00_0000)
      s := string("         ")
    pst.str(s)      
       
    repeat data from 0 to 1
      repeat reading from 0 to 4 step 2
        repeat unit from 0 to 1
          pst.position((reading >> 1) * 16 + 16, data * 3 + unit + 5)
          pst.str(alt.formatn(cur_t[reading + data], units[data << 1 + unit], 8))

    repeat reading from 0 to 2
      repeat unit from 0 to 1
        pst.position(reading * 16 + 16, unit + 11)
        pst.str(alt.formatn(cur_a[reading], units[unit + 4], 8))

    repeat unit from 0 to 1
      pst.position(32, unit + 14)
      pst.str(alt.formatn(sea_p, units[unit + 2], 8))

    check_input
    
PUB check_input | ch

  repeat while (pst.rxcount)
    ch := pst.charin
    case input_state
      TYPE:
        if (ch == 13)
          pst.str(@grid)
        elseif (ch == " ")
          loc_a := avg_a
          alt.set_sealevel_press(sea_p)
          function := 1 - function
        elseif (lookdown(ch: "m", "i", "c", "f", "M", "I", "C", "F"))
          input_type := ch | $20
          input_state := DIGIT
          input_data~
          input_sign := 1
      DIGIT:
        if (ch == "-")
          if (input_sign == 1 and input_data == 0)
            input_sign := -1
        elseif (lookdown(ch: "0" .. "9"))
          input_data := input_data * 10 + ch - "0"
        else
          input_state := TYPE
        if (ch == 13)
          input_data *= input_sign
          case input_type
            "m": function := ALTIMETER
            "i": input_data := alt.mb_from_in(input_data)
                 function := ALTIMETER
            "c": loc_a := input_data
                 input_data := alt.sealevel_press(avg_p, loc_a)
                 function := BAROMETER
            "f": loc_a := alt.m_from_ft(input_data)
                 input_data := alt.sealevel_press(avg_p, loc_a)
                 function := BAROMETER
          alt.set_sealevel_press(input_data)
        
DAT

grid          byte      pst#CS
              byte      "+-------------------------------------------------------------+",13
              byte      "|             Parallax #29124 Altimeter Readings              |",13
              byte      "+-------------+---------------+---------------+---------------+",13
              byte      "|             |    Current    |    Average    |    Median     |",13
              byte      "+-------------+---------------+---------------+---------------+",13
              byte      "| Temperature |               |               |               |",13
              byte      "|             |               |               |               |",13
              byte      "+-------------+---------------+---------------+---------------+",13
              byte      "|   Local     |               |               |               |",13
              byte      "|  Pressure   |               |               |               |",13
              byte      "+-------------+---------------+---------------+---------------+",13
              byte      "|  Altitude   |               |               |               |",13
              byte      "|             |               |               |               |",13
              byte      "+-------------+---------------+---------------+---------------+",13
              byte      "|  Sea Level  |               |               |               |",13
              byte      "|  Pressure   |               |               |               |",13
              byte      "+-------------+---------------+---------------+---------------+",13,13
              byte      "To set the sea-level pressure, type m000000 for millibars * 100",13
              byte      "                                or i0000   for inches * 100",13
              byte      "followed by the ENTER key. (The zeroes represent any digits.)",13,13
              byte      "        Examples: m101025 enters 1010.25 millibars.",13
              byte      "                  i3001   enters 30.01 inches of mercury.",13,13
              byte      "To set your current altitude, type c0000000 for cm (m * 100)",13
              byte      "                                or f0000000 for feet * 100",13
              byte      "followed by the ENTER key. (The zeroes represent any digits.)",13,13
              byte      "        Examples: c34567 enters 34567 cm (345.67 meters)",13
              byte      "                  f12503 enters 125.03 feet.",13,13
              byte      "ENTER clears and refreshes the screen if it gets messed up.",13
              byte      "SPACE toggles between Altimeter and Barometer.",0

units         byte      alt#DEGC,alt#TO_DEGF,alt#MILLIBARS,alt#TO_INCHES,alt#METERS,alt#TO_FEET
                     