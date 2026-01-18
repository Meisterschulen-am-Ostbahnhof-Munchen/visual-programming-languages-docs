# F_REAL_AS_WSTRING

```{index} single: F_REAL_AS_WSTRING
```

<img width="1256" height="180" alt="F_REAL_AS_WSTRING" src="https://github.com/user-attachments/assets/bc7fddcb-82a0-423e-aabe-56670bf82552" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_REAL_AS_WSTRING` dient der Konvertierung eines `REAL`-Wertes in einen `WSTRING`-Wert. Dieser Baustein ist besonders nützlich, wenn numerische Werte in eine für die Ausgabe oder Weiterverarbeitung geeignete Zeichenkette umgewandelt werden müssen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Dieser Eingang löst die Konvertierung aus. Bei einem ankommenden Ereignis wird der Algorithmus zur Umwandlung des `REAL`-Wertes in einen `WSTRING`-Wert gestartet.

### **Ereignis-Ausgänge**
- **CNF**: Dieses Ereignis signalisiert die erfolgreiche Beendigung der Konvertierung und liefert das Ergebnis als `WSTRING`-Wert.

### **Daten-Eingänge**
- **IN**: Der Eingang erwartet einen `REAL`-Wert, der in einen `WSTRING` umgewandelt werden soll.

### **Daten-Ausgänge**
- **OUT**: Der Ausgang liefert den konvertierten `WSTRING`-Wert nach Abschluss der Konvertierung.

### **Adapter**
Dieser Funktionsblock verfügt über keine Adapter-Schnittstellen.

## Funktionsweise
Der Funktionsblock `F_REAL_AS_WSTRING` führt bei einem eingehenden `REQ`-Ereignis die Konvertierung des `REAL`-Wertes am Eingang `IN` in einen `WSTRING`-Wert durch. Das Ergebnis wird am Ausgang `OUT` bereitgestellt und durch ein `CNF`-Ereignis bestätigt.

Der Konvertierungsalgorithmus ist als einfache ST (Structured Text)-Anweisung implementiert:
```ST
ALGORITHM REQ
OUT := REAL_AS_WSTRING(IN);
END_ALGORITHM
```

## Technische Besonderheiten
- Der Funktionsblock ist Teil des Pakets `iec61131::conversion`.
- Die Konvertierung erfolgt direkt und ohne zusätzliche Parameter oder Einstellmöglichkeiten.

## Zustandsübersicht
1. **Idle**: Wartet auf ein `REQ`-Ereignis.
2. **Processing**: Führt die Konvertierung durch.
3. **Completed**: Sendet das `CNF`-Ereignis mit dem Ergebnis.

## Anwendungsszenarien
- **Datenausgabe**: Konvertierung von numerischen Werten für die Anzeige auf einem Bedienpanel oder in einer Log-Datei.
- **Datenkommunikation**: Vorbereitung von numerischen Werten für die Übertragung als Zeichenketten in Netzwerkprotokollen.

## Vergleich mit ähnlichen Bausteinen
- **F_REAL_TO_STRING**: Ähnlicher Funktionsblock, der jedoch in einen `STRING` statt in einen `WSTRING` konvertiert. `F_REAL_AS_WSTRING` ist für Unicode-fähige Umgebungen besser geeignet.
- **F_WSTRING_AS_REAL**: Führt die umgekehrte Konvertierung durch (von `WSTRING` zu `REAL`).

## Fazit
Der Funktionsblock `F_REAL_AS_WSTRING` bietet eine einfache und effiziente Möglichkeit, `REAL`-Werte in `WSTRING`-Werte umzuwandeln. Durch seine klare Schnittstelle und direkte Funktionsweise ist er ideal für Anwendungen, die eine Unicode-kompatible Zeichenkettenrepräsentation von Gleitkommazahlen benötigen.