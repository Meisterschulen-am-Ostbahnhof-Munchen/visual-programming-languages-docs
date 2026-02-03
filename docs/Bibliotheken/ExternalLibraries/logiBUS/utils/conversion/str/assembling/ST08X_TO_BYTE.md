# ST08X_TO_BYTE

```{index} single: ST08X_TO_BYTE
```

<img width="1075" height="213" alt="image" src="https://github.com/user-attachments/assets/006152fd-288f-460f-9c7b-723922245e8e" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `ST08X_TO_BYTE` dient der Konvertierung einer speziellen Datenstruktur, die acht einzelne boolesche Werte (BOOL) enthält, in einen einzigen Byte-Wert (BYTE). Diese Operation ist nützlich, um kompakte digitale Signale für die Übertragung oder Speicherung zu bündeln oder um sie mit Systemen zu verbinden, die Daten im Byte-Format erwarten.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
*   **REQ**: Dieses Ereignis löst die Konvertierungsfunktion aus. Bei seinem Eintreffen werden die aktuellen Werte am Dateneingang `IN` gelesen und in den Byte-Ausgang `OUT` umgewandelt.

### **Ereignis-Ausgänge**
*   **CNF**: Dieses Ereignis signalisiert die erfolgreiche Beendigung der Konvertierung. Es wird gleichzeitig mit der Ausgabe des berechneten Byte-Wertes am Datenausgang `OUT` erzeugt.

### **Daten-Eingänge**
*   **IN** (Typ: `ST08X`): Der Eingang für die zu konvertierende Datenstruktur. Der Typ `ST08X` ist ein benutzerdefinierter Strukturtyp (STRUCT), der acht einzelne BOOL-Elemente mit den Namen `X_00` bis `X_07` enthält.

### **Daten-Ausgänge**
*   **OUT** (Typ: `BYTE`): Der Ausgang, an dem das Ergebnis der Konvertierung bereitgestellt wird. Die acht Bits des Bytes (Bit 0 bis Bit 7) entsprechen direkt den acht BOOL-Werten der Eingangsstruktur.

### **Adapter**
Dieser Funktionsblock verfügt über keine Adapterschnittstellen.

## Funktionsweise
Bei Auslösung durch das `REQ`-Ereignis führt der Block eine bitweise Zuweisung durch. Jedes Bit des Ausgangsbytes `OUT` wird auf den Wert des entsprechenden booleschen Elements in der Eingangsstruktur `IN` gesetzt. Die Zuordnung erfolgt nach folgendem, fest definiertem Schema:
*   `OUT`.0 (niederwertigstes Bit, LSB) = `IN`.`X_00`
*   `OUT`.1 = `IN`.`X_01`
*   `OUT`.2 = `IN`.`X_02`
*   `OUT`.3 = `IN`.`X_03`
*   `OUT`.4 = `IN`.`X_04`
*   `OUT`.5 = `IN`.`X_05`
*   `OUT`.6 = `IN`.`X_06`
*   `OUT`.7 (höchstwertiges Bit, MSB) = `IN`.`X_07`

Nach Abschluss dieser Zuweisungen wird das `CNF`-Ereignis zusammen mit dem neuen Wert von `OUT` ausgegeben.

## Technische Besonderheiten
*   **Deterministisches Mapping**: Die Zuordnung der einzelnen BOOL-Elemente zu bestimmten Bit-Positionen im Byte ist fest im Code hinterlegt und nicht konfigurierbar.
*   **Einfache Logik**: Der Block enthält keine Zustandsautomaten oder komplexe Algorithmen. Die Funktionsweise beschränkt sich auf eine direkte, parallele Zuweisung.
*   **Typabhängigkeit**: Der Block ist spezifisch für den benutzerdefinierten Datentyp `ST08X`. Für andere Strukturen oder eine andere Anzahl von Bits sind ggf. andere Blöcke erforderlich.

## Zustandsübersicht
Der Funktionsblock besitzt keinen internen Zustand im Sinne eines Zustandsautomaten. Er verhält sich rein kombinatorisch in Bezug auf die Daten und sequentiell in Bezug auf die Ereignissteuerung: Auf ein eingehendes `REQ` folgt stets ein ausgehendes `CNF`.

## Anwendungsszenarien
*   **Kommunikation mit Byte-orientierten Schnittstellen**: Vorbereitung von Daten für die Übertragung über serielle Bussysteme (z.B. Modbus, Profibus), Netzwerke oder Kommunikationsprotokolle, die Daten in Byte-Blöcken erwarten.
*   **Kompakte Speicherung**: Bündeln mehrerer digitaler Schaltzustände (z.B. von Grenzwertmeldern, Maschinenzuständen) in einem einzelnen Byte, um Speicherplatz zu optimieren.
*   **Datenaufbereitung für Visualisierung oder Logging**: Umwandlung von strukturierten BOOL-Signalen in ein für Anzeigesysteme oder Datenspeicher einfacher zu handhabendes Byte-Format.

## ⚖️ Vergleich mit ähnlichen Bausteinen
*   **`BOOL_TO_BYTE` (oder ähnliche Blöcke aus Standardbibliotheken)**: Viele IEC 61499- oder IEC 61131-3-Bibliotheken bieten Blöcke an, die acht separate `BOOL`-Eingänge direkt in ein `BYTE` umwandeln. `ST08X_TO_BYTE` unterscheidet sich dadurch, dass die Eingangswerte bereits in einer strukturierten Variable (`ST08X`) gebündelt vorliegen, was die Verdrahtung im Anwendungsdiagramm vereinfachen kann.
*   **`PACK` / `UNPACK`-Blöcke**: Allgemeinere Blöcke zum Packen und Entpacken von Daten. `ST08X_TO_BYTE` ist eine spezialisierte und typsichere Implementierung für genau diesen einen Anwendungsfall.
*   **Manuelle Bit-Operationen**: Die Funktion könnte auch durch direkte Zuweisungen in Structured Text (ST) realisiert werden. Der Funktionsblock kapselt diese Logik und bietet eine standardisierte, wieder verwendbare Schnittstelle mit klarer Ereignissteuerung.

## Fazit
Der `ST08X_TO_BYTE`-Funktionsblock ist ein spezialisiertes und effizientes Werkzeug zur Konvertierung einer strukturierten Gruppe von acht booleschen Signalen in ein kompaktes Byte. Durch seine klare, fest definierte Schnittstelle und einfache Funktionsweise eignet er sich ideal für Anwendungen, bei denen digitale Signale für die effiziente Kommunikation oder Speicherung gebündelt werden müssen. Seine Verwendung fördert die Wiederverwendbarkeit und Lesbarkeit von Steuerungsprogrammen im Vergleich zu manuell implementierten Bit-Operationen.