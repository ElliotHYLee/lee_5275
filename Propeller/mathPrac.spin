CON
  _clkmode = xtal1 + pll16x
  _xinfreq = 5_000_000

VAR

  long value
OBJ
  pst : "Parallax Serial Terminal"
  f   : "Float32"  
PUB main| a,b,c,aa,bb,cc,norm,dirVx,alpha, beta, gamma

  pst.Start(115200)
  a := 2
  b := 4
  c := 8
  pst.str(string("a= "))
  pst.dec(a)
  pst.newline
  
  pst.str(string("b= "))
  pst.dec(b)
  pst.newline   

  pst.str(string("c= "))
  pst.dec(c)
  pst.newline
  
  aa := a*a
  bb := b*b
  cc := c*c



  pst.str(string("aa= "))
  pst.dec(aa)
  pst.newline

  pst.str(string("bb= "))
  pst.dec(bb)
  pst.newline

  pst.str(string("cc= "))
  pst.dec(cc)
  pst.newline

  norm := ^^(aa*aa + bb*bb + cc*cc)
  pst.str(string("direction vector x= "))
  dirVx := f.fdiv(aa, norm)
  pst.dec(dirVx)
  pst.newline

 
  