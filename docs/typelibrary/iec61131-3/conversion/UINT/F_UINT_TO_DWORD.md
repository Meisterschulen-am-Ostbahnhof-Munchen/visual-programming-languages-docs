# F_UINT_TO_DWORD

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_UINT_TO_DWORD` dient der Konvertierung eines UINT-Wertes (16-Bit unsigned integer) in einen DWORD-Wert (32-Bit unsigned integer). Diese Konvertierung ist insbesondere in Szenarien erforderlich, in denen Daten unterschiedlicher Bitbreiten verarbeitet oder übertragen werden müssen.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
- **REQ**: Startet die Konvertierung. Der Eingang ist mit dem Daten-Eingang `IN` verknüpft.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Konvertierung. Der Ausgang ist mit dem Daten-Ausgang `OUT` verknüpft.

### **Daten-Eingänge**
- **IN**: UINT-Wert (16-Bit), der in einen DWORD-Wert konvertiert werden soll.

### **Daten-Ausgänge**
- **OUT**: DWORD-Wert (32-Bit), der das Ergebnis der Konvertierung enthält.

### **Adapter**
- Keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock führt die Konvertierung durch, sobald ein Ereignis am Eingang `REQ` eintrifft. Der Algorithmus `REQ` wandelt den UINT-Wert am Eingang `IN` in einen DWORD-Wert um und speichert das Ergebnis in `OUT`. Anschließend wird das Ereignis `CNF` ausgelöst, um den Abschluss der Konvertierung zu signalisieren.

## Technische Besonderheiten
- Die Konvertierung erfolgt ohne Datenverlust, da der Wertebereich von UINT (0 bis 65535) vollständig in DWORD (0 bis 4294967295) abgebildet werden kann.
- Der Funktionsblock ist Teil des Pakets `iec61131::conversion`.

## Zustandsübersicht
Der Funktionsblock besitzt keine internen Zustände. Die Konvertierung wird bei jedem `REQ`-Ereignis neu ausgeführt.

## Anwendungsszenarien
- Datenkonvertierung in Steuerungssystemen, wenn unterschiedliche Bitbreiten harmonisiert werden müssen.
- Integration in größere Funktionsblocknetzwerke, die sowohl UINT- als auch DWORD-Daten verarbeiten.

## Vergleich mit ähnlichen Bausteinen
- Im Vergleich zu anderen Konvertierungsbausteinen (z.B. `F_INT_TO_DINT`) ist `F_UINT_TO_DWORD` spezialisiert auf die Konvertierung von 16-Bit zu 32-Bit unsigned integers.
- Ähnliche Bausteine könnten zusätzliche Funktionen wie Skalierung oder Grenzwertprüfung bieten, was hier nicht der Fall ist.

## Fazit
Der Funktionsblock `F_UINT_TO_DWORD` bietet eine einfache und effiziente Möglichkeit, UINT-Werte in DWORD-Werte umzuwandeln. Durch seine klare Schnittstelle und deterministische Funktionsweise eignet er sich ideal für den Einsatz in Steuerungs- und Automatisierungslösungen.