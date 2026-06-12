# ARR08B_TO_WORDS


![ARR08B_TO_WORDS](./ARR08B_TO_WORDS.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsbaustein **ARR08B_TO_WORDS** dient der Aufteilung eines 8‑Byte‑Arrays in vier 16‑Bit‑Wörter (WORD). Er wird typischerweise in der Datenvorverarbeitung eingesetzt, wenn rohe Byte‑Daten aus Sensoren oder Kommunikationsschnittstellen in ganzzahlige Werte umgewandelt werden müssen. Die Umwandlung erfolgt byteweise unter Berücksichtigung der Little‑Endian‑Bytereihenfolge.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
| Ereignis | Beschreibung |
|----------|--------------|
| REQ      | Auslösen der Konvertierung; der Baustein verarbeitet den aktuellen Wert von `IN` und legt die Ergebnisse an den Ausgängen an. |

### **Ereignis-Ausgänge**
| Ereignis | Beschreibung |
|----------|--------------|
| CNF      | Bestätigung, dass die Konvertierung abgeschlossen ist und die Ausgangswerte gültig sind. |

### **Daten-Eingänge**
| Name | Typ   | Array-Größe | Beschreibung |
|------|-------|-------------|--------------|
| IN   | BYTE  | 0…7         | Eingangsarray aus 8 Bytes, das in vier Words zerlegt wird. |

### **Daten-Ausgänge**
| Name    | Typ  | Beschreibung |
|---------|------|--------------|
| OUT_00  | WORD | Aus den Bytes IN[0] und IN[1] gebildetes Word (niederwertigstes). |
| OUT_01  | WORD | Aus den Bytes IN[2] und IN[3] gebildetes Word. |
| OUT_02  | WORD | Aus den Bytes IN[4] und IN[5] gebildetes Word. |
| OUT_03  | WORD | Aus den Bytes IN[6] und IN[7] gebildetes Word (höchstwertigstes). |

### **Adapter**
Keine Adapter vorhanden.

## Funktionsweise
Bei Aktivierung des Ereignisses `REQ` wird das 8‑Byte‑Array `IN` sequenziell abgearbeitet. Jeweils zwei aufeinanderfolgende Bytes werden in ein 16‑Bit‑Wort zusammengefasst, wobei das erste Byte (`IN[0]`) das niederwertige Byte (`%B0`) und das zweite Byte (`IN[1]`) das höherwertige Byte (`%B1`) des Wortes bildet (Little‑Endian‑Format). Die resultierenden vier Wörter werden an den Ausgängen `OUT_00` bis `OUT_03` bereitgestellt. Anschließend wird das Ereignis `CNF` gesendet.

## Technische Besonderheiten
- **Byte‑Reihenfolge:** Die Konvertierung erfolgt stets im Little‑Endian‑Format, d.h. das zuerst im Array stehende Byte wird zum niederwertigen Teil des Wortes.
- **Keine Pufferung:** Der Baustein ist rein kombinatorisch und speichert keine Zustände. Jeder `REQ`‑Aufruf verarbeitet den aktuellen Eingangswert.
- **Typisierung:** Eingänge sind als Array von `BYTE` (0‑Indizierung), Ausgänge als `WORD` definiert. Der Baustein setzt keine weiteren Typumwandlungen voraus.

## Zustandsübersicht
Der Baustein besitzt keinen internen Zustandsautomaten. Die Verarbeitung erfolgt streng ereignisgesteuert:
1. Warten auf `REQ`.
2. Bei `REQ`: Kopieren der Bytes in die Ausgangswörter.
3. Senden von `CNF` und Rückkehr in den Wartezustand.

## Anwendungsszenarien
- **Sensorauslesung:** Ein Temperatursensor liefert 8 Rohbytes, die in vier 16‑Bit‑Messwerte (z.B. zwei Kanäle mit je einem Word) aufgeteilt werden müssen.
- **Protokoll‑Dekodierung:** Ein serielles Protokoll überträgt Nutzdaten als Byte‑Array; der Baustein extrahiert daraus vier 16‑Bit‑Registerwerte.
- **Datenvorverarbeitung in SPS‑Systemen:** Zusammenführen mehrerer Byte‑orientierter Schnittstellen (z.B. Profibus, CAN) in einheitliche Word‑Signale für die weitere Verarbeitung.

## Vergleich mit ähnlichen Bausteinen
- **`BYTE_TO_WORD`:** Wandelt nur zwei Bytes in ein einzelnes Word um, benötigt bei 8 Bytes vier Aufrufe.
- **`ARRAY_TO_WORD` (allgemein):** Meist parametrierbar, z.B. mit Startindex und Anzahl – `ARR08B_TO_WORDS` ist dagegen fest auf 8 Bytes und 4 Words ausgelegt und dadurch einfacher und performanter in diesem spezifischen Fall.
- **`WORD_TO_ARR08B` (gegebenenfalls vorhanden):** Die inverse Funktion, die vier Words wieder in ein 8‑Byte‑Array packt.

## Fazit
Der Funktionsbaustein **ARR08B_TO_WORDS** bietet eine schlanke, spezialisierte Lösung zum Zerlegen eines 8‑Byte‑Arrays in vier 16‑Bit‑Wörter. Durch die feste Verdrahtung der Byte‑Zuordnung wird eine hohe Ausführungsgeschwindigkeit und einfache Handhabung erreicht, insbesondere in zeitkritischen Umgebungen oder bei wiederkehrenden Konvertierungsaufgaben. Die Little‑Endian‑Interpretation ist für viele industrielle und eingebettete Systeme der Standard, sodass der Baustein ohne zusätzliche Parameter auskommt.