from numpy import loadtxt
from sys import argv

sel = argv[1]
filename = argv[2]

data = loadtxt(filename,dtype="string",skiprows=1)

ampd = " & "
endl = "\\\\"

for i in range(4):
  line = ''
  line+=data[i,4]+ampd
  # temp = str("%0.5f" % float(data[i,5]))
  line+=data[i,5]+ampd
  line+=data[i,6]+ampd
  line+=data[i,7]+ampd
  # line+=data[i,8]+ampd
  if(sel=='4p'):
    line+=data[i,9]+ampd
  else:
    line+='-'+ampd
  line+=data[i,10]+ampd
  line+=data[i,11]+ampd
  line+=data[i,12]+ampd
  # line+=data[i,13]+ampd
  if(sel=='4p'):
    line+=data[i,14]+ampd
  else:
    line+='-'+ampd
  if i<3:
    line+=data[i,15]+endl
  else:
    line+=data[i,15]
  print line