# F_USINT_AS_WSTRING

<img width="1495" height="214" alt="F_USINT_AS_WSTRING" src="https://github.com/user-attachments/assets/f7e08d34-adb5-4269-aad6-74d5d362a5a3" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_USINT_AS_WSTRING` dient der Konvertierung eines vorzeichenlosen 8-Bit-Integer-Werts (`USINT`) in eine Unicode-Zeichenkette (`WSTRING`). Diese Funktionalität ist besonders nützlich in Szenarien, wo numerische Werte als Text ausgegeben oder verarbeitet werden müssen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Startet die Konvertierung. Wird dieser Eingang ausgelöst, wird der Wert am Daten-Eingang `IN` verarbeitet.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Konvertierung. Der konvertierte Wert ist am Daten-Ausgang `OUT` verfügbar.

### **Daten-Eingänge**
- **IN**: Ein vorzeichenloser 8-Bit-Integer-Wert (`USINT`), der in eine Unicode-Zeichenkette konvertiert werden soll.

### **Daten-Ausgänge**
- **OUT**: Die resultierende Unicode-Zeichenkette (`WSTRING`) nach der Konvertierung.

### **Adapter**
- Keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock führt die Konvertierung durch, sobald das Ereignis `REQ` ausgelöst wird. Dabei wird der Wert am Eingang `IN` genommen und mittels der Funktion `USINT_AS_WSTRING` in eine Unicode-Zeichenkette umgewandelt. Das Ergebnis wird am Ausgang `OUT` bereitgestellt und das Ereignis `CNF` signalisiert die erfolgreiche Ausführung.

## Technische Besonderheiten
- Verwendet die eingebaute Funktion `USINT_AS_WSTRING` zur Konvertierung.
- Unterstützt den vollständigen Wertebereich von `USINT` (0 bis 255).

## Zustandsübersicht
1. **Idle**: Wartet auf das Ereignis `REQ`.
2. **Konvertierung**: Verarbeitet den Eingangswert und generiert die Ausgabe.
3. **Bestätigung**: Sendet das Ereignis `CNF` und kehrt in den Idle-Zustand zurück.

## Anwendungsszenarien
- Anzeige von numerischen Werten in Benutzeroberflächen.
- Protokollierung von numerischen Daten in Textdateien.
- Kommunikation mit Systemen, die Textdaten erwarten.

## Vergleich mit ähnlichen Bausteinen
- Im Vergleich zu generischen Konvertierungsblöcken ist `F_USINT_AS_WSTRING` spezialisiert auf die Konvertierung von `USINT` zu `WSTRING`.
- Andere Blöcke könnten andere Datentypen oder zusätzliche Formatierungsoptionen unterstützen.

## Fazit
Der `F_USINT_AS_WSTRING` Funktionsblock bietet eine einfache und effiziente Möglichkeit, vorzeichenlose 8-Bit-Integer-Werte in Unicode-Zeichenketten umzuwandeln. Seine klare Schnittstelle und direkte Funktionsweise machen ihn ideal für Projekte, die solche Konvertierungen benötigen.
