# F_WSTRING_AS_BYTE

```{index} single: F_WSTRING_AS_BYTE
```

<img width="1480" height="214" alt="F_WSTRING_AS_BYTE" src="https://github.com/user-attachments/assets/5af29946-8d1c-495b-a40a-d21f8d38b1fc" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_WSTRING_AS_BYTE` dient der Konvertierung eines WSTRING-Datentyps in einen BYTE-Datentyp. Dieser Baustein ist besonders nützlich in Szenarien, wo eine Umwandlung von breiten Zeichenketten in einzelne Bytes erforderlich ist.

![F_WSTRING_AS_BYTE](F_WSTRING_AS_BYTE.svg)

## Schnittstellenstruktur
### **Ereignis-Eingänge**
- **REQ**: Startet die Ausführung des Funktionsblocks. Bei diesem Ereignis wird der Eingangswert `IN` verarbeitet.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Verarbeitung und gibt das Ergebnis über den Ausgang `OUT` aus.

### **Daten-Eingänge**
- **IN** (WSTRING): Der Eingangswert, der in einen BYTE-Wert konvertiert werden soll.

### **Daten-Ausgänge**
- **OUT** (BYTE): Das Ergebnis der Konvertierung.

### **Adapter**
- Keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock führt bei Auftreten des `REQ`-Ereignisses die Konvertierung des WSTRING-Eingangs `IN` in einen BYTE-Wert durch. Das Ergebnis wird über den Ausgang `OUT` ausgegeben und das `CNF`-Ereignis signalisiert den erfolgreichen Abschluss der Operation.

## Technische Besonderheiten
- Der Funktionsblock nutzt die Funktion `WSTRING_AS_BYTE` zur Konvertierung.
- Es handelt sich um einen einfachen Funktionsblock ohne interne Zustandsverwaltung.

## Zustandsübersicht
Der Funktionsblock hat keine internen Zustände. Die Verarbeitung erfolgt direkt bei Auftreten des `REQ`-Ereignisses.

## Anwendungsszenarien
- Konvertierung von WSTRING-Daten in BYTE-Werte für die weitere Verarbeitung in Systemen, die nur BYTE-Daten unterstützen.
- Verwendung in Kommunikationsprotokollen, wo Zeichenketten in Bytes umgewandelt werden müssen.

## Vergleich mit ähnlichen Bausteinen
- Im Vergleich zu anderen Konvertierungsbausteinen wie `F_STRING_AS_BYTE` ist dieser speziell für WSTRING-Datentypen ausgelegt.
- Ähnliche Bausteine könnten zusätzliche Parameter oder Zustände haben, dieser Funktionsblock ist jedoch auf die einfache Konvertierung beschränkt.

## Fazit
Der `F_WSTRING_AS_BYTE` Funktionsblock bietet eine einfache und effiziente Möglichkeit, WSTRING-Daten in BYTE-Werte umzuwandeln. Seine klare Schnittstellenstruktur und direkte Funktionsweise machen ihn zu einer zuverlässigen Lösung für entsprechende Anwendungsfälle.