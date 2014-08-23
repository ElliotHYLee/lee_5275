void goToMark(int mark)
{
  unsigned long numOfMillis = 120000;
  mark=mark+trackMarks;
  metroAcc.interval(numOfMillis);
  metroAcc.reset();
  do
  {
    goFor(5);
  }
  while(!metroAcc.check()==1 && trackMarks<mark);  
}

