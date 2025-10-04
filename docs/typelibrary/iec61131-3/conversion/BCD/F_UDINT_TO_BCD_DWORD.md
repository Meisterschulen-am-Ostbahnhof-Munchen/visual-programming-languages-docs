# F_UDINT_TO_BCD_DWORD

<img width="1304" height="185" alt="F_UDINT_TO_BCD_DWORD" src="https://github.com/user-attachments/assets/9028a6e3-4da9-4881-90d3-71ad99cbbef7" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_UDINT_TO_BCD_DWORD` dient der Konvertierung eines vorzeichenlosen 32-Bit-Integer-Werts (UDINT) in ein BCD-kodiertes DWORD. Diese Konvertierung ist insbesondere in Anwendungen nützlich, bei denen numerische Werte in einem für Menschen lesbaren Format dargestellt oder verarbeitet werden müssen.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
- **REQ**: Startet die Konvertierung. Der Eingang ist mit dem Daten-Eingang `IN` verknüpft.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Konvertierung. Der Ausgang ist mit dem Daten-Ausgang `OUT` verknüpft.

### **Daten-Eingänge**
- **IN**: Ein vorzeichenloser 32-Bit-Integer-Wert (UDINT), der in ein BCD-kodiertes DWORD umgewandelt werden soll.

### **Daten-Ausgänge**
- **OUT**: Das Ergebnis der Konvertierung als BCD-kodiertes DWORD.

### **Adapter**
Keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock führt die Konvertierung durch, sobald das Ereignis `REQ` empfangen wird. Der Algorithmus wandelt den Wert am Eingang `IN` von UDINT in ein BCD-kodiertes DWORD um und legt das Ergebnis am Ausgang `OUT` ab. Anschließend wird das Ereignis `CNF` ausgelöst, um den erfolgreichen Abschluss der Operation zu signalisieren.

## Technische Besonderheiten
- Die Konvertierung erfolgt mittels der Funktion `UDINT_TO_BCD_DWORD`, die im Algorithmus des Funktionsblocks implementiert ist.
- Der Funktionsblock ist Teil des Pakets `iec61131::conversion`.

## Zustandsübersicht
1. **Wartezustand**: Der Funktionsblock wartet auf das Ereignis `REQ`.
2. **Aktivzustand**: Bei Empfang von `REQ` wird die Konvertierung durchgeführt und das Ergebnis an `OUT` ausgegeben.
3. **Bestätigungszustand**: Nach erfolgreicher Konvertierung wird `CNF` ausgelöst und der Funktionsblock kehrt in den Wartezustand zurück.

## Anwendungsszenarien
- **Anzeigesteuerung**: Konvertierung von numerischen Werten für die Anzeige auf siebensegmentigen Displays oder LCDs.
- **Datenkommunikation**: Vorbereitung von Daten für die Übertragung in BCD-kodierten Protokollen.
- **Druckersteuerung**: Umwandlung von numerischen Werten für den Druck in einem lesbaren Format.

## Vergleich mit ähnlichen Bausteinen
- **F_UDINT_TO_STRING**: Konvertiert einen UDINT in einen String, ist jedoch weniger effizient für BCD-spezifische Anwendungen.
- **F_UDINT_TO_DWORD**: Führt eine direkte Typumwandlung durch, ohne BCD-Kodierung.

## Fazit
Der Funktionsblock `F_UDINT_TO_BCD_DWORD` bietet eine effiziente und spezialisierte Lösung für die Konvertierung von vorzeichenlosen 32-Bit-Integern in BCD-kodierte DWORDs. Seine einfache Schnittstelle und zuverlässige Funktionsweise machen ihn ideal für Anwendungen, die eine BCD-Kodierung erfordern.
