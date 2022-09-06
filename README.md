# Learn-DES-with-CMD (WINDOWS VERSION)

Symmetrische Verschlüsselung\
2.6.1 DES\
(Beispiel in Eigenarbeit)) Das Programm hat zwei\
Zustände. Zum einen gibt es den „Quiz“-Modus und zum anderen gibt es den ”Präsentatios”-\
Modus. Beim ”Präsentations”-Modus kann der Dozent den Ablauf des Data Encryption\
Standard Algorithmus zeigen. Der Dozent kann die Runde wählen, und somit\
den jeweiligen Zustand des Algorithmus zeigen. Wenn die Runde zu Ende ist, hat der Benutzer\
die Wahl, auf die nächste Runde überzugehen. Dafür muss er ein beliebiges Zeichen\
eingeben außer ”b”. Falls er den Cipher Text sehen möchte, muss er ”b” eingeben. Beim\
Quiz-Mode wird dem Benutzer zuerst die initiale Permutationsfunktion veranschaulicht.\
Dabei muss der Benutzter die ersten und letzten drei Bits eingeben. Um diese Aufgabe\
zu lösen, muss er in der Matrix nach der Bitnummer nachschauen. Für die ersten drei\
Bits sind die Bitnummern 58, 50, und 42. Für die letzten drei Bits sind die Bitnummern\
23, 15, 7. Mit Bitnummern wird hier gemeint, an der wievielten Stelle das Bit steht. In\
der unteren Matrix stehen die Bytes des Plaintexts. Der Plaintext ist zeilenweise in 8\
einzelne Bytes geteilt. Beispielsweise wollen wir das Bit mit der Bitnummer 42 ablesen.\
Hierbei muss der Benutzer beim 5. Byte nachschauen. 5 * 8 = 40 Bit. Jetzt muss er\
um 2 Stellen nach rechts gehen. Somit liest er dann die Bitnummer 42 ab. In diesen Fall\
wäre das Bit ”0”. Nachdem diese Aufgabe erfolgreich gelöst wurde, muss der Benutzer die\
Expansionsfunktions-Aufgabe lösen. Dabei wird gezeigt, wie die rechte Hälfte des Bitstromes\
von 32 Bits auf 48 Bit aufgepumpt wird. Die Aufgabe kann mithilfe der Matrix\
gelöst werden. Die Bits werden folgendermaßen aufgepumpt:\
10\
32 | 0000 |5\
4 | 0000 |9\
8 | 1111 | 13\
12| 1110 | 17\
16| 1001 | 21\
20 | 0100 | 25\
24 | 0011 | 29\
28 | 0010 | 32\
Die Zahlen der Bits sind die Bitnummern. Die Bits mit den Bitnummern müssen eingegeben\
werden. In der nächsten Aufgabe wird gezeigt, wie die Bits mit anderen Bits substituiert\
werden. Beispielsweise haben wir das Bit ”000110”. Mittels S-Boxen wird dieser Bitstrom\
substituiert und von 6 Bits auf 4 Bits reduziert. In diesen S-Boxen stehen diese 4 Bits,\
welche die 6 Bits ersetzten werden. Folgendermaßen werden die 4 Bits ermittelt: Das\
erste Bit und das letzte Bit. Also: ”00”. Dies ist die Zeile 1 in der S-Box. Die mittleren\
Bits : ”0011” bestimmen die Spalte Dies wäre die Spalte 4. Zeile 1 und Spalte 4 ist die\
ermittelte Zahl. Die S-Box ist folgendermaßen aufgebaut:\
	0000 0001 0010 0011 0100 0101 0110 0111 1000 1001 101 1011 1100 1101 1110 1111 <br /> 
00\
01\
10\






