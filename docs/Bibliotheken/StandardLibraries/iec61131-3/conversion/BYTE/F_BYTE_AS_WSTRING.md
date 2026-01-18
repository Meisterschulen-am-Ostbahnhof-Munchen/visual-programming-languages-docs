# F_BYTE_AS_WSTRING

```{index} single: F_BYTE_AS_WSTRING
```

<img width="1274" height="183" alt="F_BYTE_AS_WSTRING" src="https://github.com/user-attachments/assets/711f52f0-48d7-47e3-bb8c-36a79a97fac4" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_BYTE_AS_WSTRING` dient der Konvertierung eines BYTE-Wertes in einen WSTRING-Wert. Dies ist besonders nützlich in Szenarien, wo Byte-Daten als Unicode-Strings weiterverarbeitet oder ausgegeben werden müssen.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
- **REQ**: Startet die Konvertierung. Wird mit dem Eingabewert `IN` verknüpft.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Konvertierung. Liefert den konvertierten Wert über `OUT`.

### **Daten-Eingänge**
- **IN** (BYTE): Der Byte-Wert, der in einen WSTRING konvertiert werden soll.

### **Daten-Ausgänge**
- **OUT** (WSTRING): Der resultierende Unicode-String nach der Konvertierung.

### **Adapter**
- Keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock nutzt die eingebaute Funktion `BYTE_AS_WSTRING`, um den eingegebenen Byte-Wert in einen WSTRING zu konvertieren. Die Konvertierung wird durch das Ereignis `REQ` ausgelöst und das Ergebnis über `CNF` zurückgemeldet.

## Technische Besonderheiten
- Die Konvertierung erfolgt direkt und ohne zusätzliche Parameter.
- Der Block ist für die Verwendung in IEC 61131-3-kompatiblen Umgebungen optimiert.

## Zustandsübersicht
1. **Idle**: Wartet auf das `REQ`-Ereignis.
2. **Processing**: Führt die Konvertierung durch.
3. **Completed**: Sendet das `CNF`-Ereignis mit dem Ergebnis.

## Anwendungsszenarien
- Konvertierung von Byte-Daten für die Anzeige in Benutzeroberflächen.
- Verarbeitung von Byte-Streams in Unicode-kompatiblen Systemen.

## Vergleich mit ähnlichen Bausteinen
- Im Gegensatz zu `F_BYTE_AS_STRING` erzeugt dieser Block einen Unicode-String (WSTRING) statt eines ASCII-Strings (STRING).
- Ähnlich zu `F_WORD_AS_WSTRING`, aber für 8-Bit-Daten optimiert.

## Fazit
Der `F_BYTE_AS_WSTRING`-Block ist ein einfacher und effizienter Weg, um Byte-Daten in Unicode-Strings umzuwandeln. Seine klare Schnittstelle und direkte Funktionsweise machen ihn ideal für zahlreiche Anwendungen in der Automatisierungstechnik.
