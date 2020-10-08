# hashFunction_cpp
Programa, panaši į HashFunction C#, tik leidžianti dirbti su Command Line argumentais ir turinti collision testavimo funkcijas
# Versija v0.09999999(9)
1. Sukurtas testavimas
# Eksperimentinis tyrimas
- Pradinių testinių failų analizė
  - Pirmasis testinis failas **a.txt.** turi vieną simbolį - "a".
  - Antrasis testinis failas **b.txt** atitinkamai turi tik "b".
  - Trečiajame testiniame faile atsitiktinai sugeneruoti 1000+ simbolių
  - Ketvirtajame testiniame faile pakeistas vienas simbolis iš trečiame faile esančios eilutės
  - Penktasis ir šeštasis testiniai failai sugeneruoti atsitiktinai (TBD)
  ![Rezultatas](https://github.com/arturasvell/hashFunction_cpp/blob/0.09/result1.png)
  ![Antro bandymo rezultatas](https://github.com/arturasvell/hashFunction_cpp/blob/0.09/result2.png)
- Konstitucija.txt spartos analizė
  ![Trečio bandymo rezultatas](https://github.com/arturasvell/hashFunction_cpp/blob/0.09/result3.png)
- 100 000 string analizė
  -Bitų, hex skirtingumas bei kolizijos testas vykdomas kartu
  ![Ketvirto bandymo rezultatas](https://github.com/arturasvell/hashFunction_cpp/blob/0.09/result4.png)
  
# Stiprybės
- Sparta
- Neblogas atsparumas kolizijai
# Silpnybės
- Silpnas binary vidutinis skirtingumas
# Custom hash funkcijos pseudokodas

initialize "keys" as integer array with 8 consecutive prime numbers\
initialize "sum" with **magic number**\
  for loop through each character of string\
  {\
      sum <-sum XOR (sum leftwise keys[ i mod 8]+ string[i]+(sum rightwise keys[(i+1) mod 8])\
  }\
  sum->((sum rightwise 8) XOR sum) XOR **another magic number**\
  sum->((sum rightwise 8) XOR sum) XOR **another magic number**\
  sum->((sum rightwise 8) XOR sum)\
  initialise stringstream\
  for loop from 0 to 4\
  {\
      pass sum* **magic number** to stringstream\
  }\
  while(stream string size is less than 64)\
  {\
      pass another sum* **magic number** to stringstream\
  }\
  while(stream string size is more than 64)\
  {\
      result<-remove the last element of result\
  }\
  return sum in HEX
