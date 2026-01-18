# F_UDINT_AS_WSTRING

```{index} single: F_UDINT_AS_WSTRING
```

<img width="1494" height="212" alt="F_UDINT_AS_WSTRING" src="https://github.com/user-attachments/assets/dd3fe324-73e2-4f6e-8ccc-6a9fe7bb8e35" />

* * * * * * * * * *
## 📺 Video

* [Zusätzlich: Uebung_083: Aufwärts/Abwärts zählen: E_CTUD_UDINT Datentyp UDINT; mit Anzeige am VT.](https://www.youtube.com/watch?v=oTPDtsw5eAw)

## Einleitung
Der Funktionsblock `F_UDINT_AS_WSTRING` dient der Konvertierung eines vorzeichenlosen 32-Bit-Integer-Werts (`UDINT`) in eine Unicode-Zeichenkette (`WSTRING`). Diese Funktionalität ist besonders nützlich, wenn numerische Werte für die Anzeige oder Weiterverarbeitung als Text benötigt werden.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Startet die Konvertierung. Der Eingang ist mit dem Daten-Eingang `IN` verknüpft.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Konvertierung. Der Ausgang ist mit dem Daten-Ausgang `OUT` verknüpft.

### **Daten-Eingänge**
- **IN**: Der vorzeichenlose 32-Bit-Integer-Wert (`UDINT`), der in eine Unicode-Zeichenkette konvertiert werden soll.

### **Daten-Ausgänge**
- **OUT**: Die resultierende Unicode-Zeichenkette (`WSTRING`) nach der Konvertierung.

### **Adapter**
Es sind keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock führt die Konvertierung durch, sobald das Ereignis `REQ` ausgelöst wird. Der Algorithmus wandelt den Wert von `IN` in eine `WSTRING`-Darstellung um und speichert das Ergebnis in `OUT`. Anschließend wird das Ereignis `CNF` ausgelöst, um den Abschluss der Operation zu signalisieren.

## Technische Besonderheiten
- Die Konvertierung erfolgt direkt und ohne zusätzliche Parameter.
- Der Funktionsblock ist für die Verwendung in IEC 61131-konformen Umgebungen optimiert.

## Zustandsübersicht
1. **Idle**: Wartet auf das `REQ`-Ereignis.
2. **Processing**: Führt die Konvertierung durch.
3. **Completed**: Signalisiert den Abschluss mit `CNF` und kehrt in den Idle-Zustand zurück.

## Anwendungsszenarien
- Anzeige von numerischen Werten in Benutzeroberflächen.
- Protokollierung von numerischen Daten in Textdateien.
- Vorbereitung von Daten für die Kommunikation über Text-basierte Protokolle.

## Vergleich mit ähnlichen Bausteinen
- Im Vergleich zu `F_DINT_AS_WSTRING` verarbeitet dieser Baustein vorzeichenlose Werte.
- Ähnlich wie `F_UDINT_AS_STRING`, aber mit Unicode-Unterstützung.

## Fazit
Der `F_UDINT_AS_WSTRING`-Funktionsblock bietet eine einfache und effiziente Möglichkeit, vorzeichenlose 32-Bit-Integer-Werte in Unicode-Zeichenketten umzuwandeln. Seine klare Schnittstelle und direkte Funktionsweise machen ihn zu einem wertvollen Werkzeug in vielen Automatisierungsanwendungen.