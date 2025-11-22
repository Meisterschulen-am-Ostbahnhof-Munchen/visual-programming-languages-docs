# F_ULINT_AS_STRING

<img width="1479" height="214" alt="F_ULINT_AS_STRING" src="https://github.com/user-attachments/assets/7f40d872-343a-4628-a23d-a9ba54f7314b" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_ULINT_AS_STRING` dient der Konvertierung eines `ULINT`-Wertes (64-Bit unsigned integer) in einen `STRING`. Diese Funktionalität ist besonders nützlich, wenn numerische Werte für die Ausgabe, Protokollierung oder weitere Verarbeitung als Zeichenketten benötigt werden.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Startet die Konvertierung. Der Eingang ist mit dem Daten-Eingang `IN` verknüpft.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Konvertierung. Der Ausgang ist mit dem Daten-Ausgang `OUT` verknüpft.

### **Daten-Eingänge**
- **IN** (`ULINT`): Der zu konvertierende 64-Bit unsigned integer Wert.

### **Daten-Ausgänge**
- **OUT** (`STRING`): Der Ergebnis-String nach der Konvertierung.

### **Adapter**
- Keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock führt die Konvertierung durch, wenn das Ereignis `REQ` empfangen wird. Dabei wird der `ULINT`-Wert am Eingang `IN` in einen `STRING` umgewandelt und am Ausgang `OUT` ausgegeben. Die erfolgreiche Konvertierung wird durch das Ereignis `CNF` signalisiert.

## Technische Besonderheiten
- Der Funktionsblock ist einfach aufgebaut und enthält nur einen Algorithmus, der die Konvertierung durchführt.
- Die Konvertierung erfolgt direkt und ohne zusätzliche Parameter oder komplexe Logik.

## Zustandsübersicht
Der Funktionsblock hat keine internen Zustände. Die Konvertierung wird bei jedem `REQ`-Ereignis neu durchgeführt.

## Anwendungsszenarien
- **Protokollierung**: Konvertierung von numerischen Werten für die Ausgabe in Log-Dateien.
- **Benutzeroberflächen**: Darstellung von numerischen Werten als Text in Benutzeroberflächen.
- **Datenkommunikation**: Vorbereitung von numerischen Werten für die Übertragung als Zeichenketten.

## Vergleich mit ähnlichen Bausteinen
- **F_INT_AS_STRING**: Konvertiert einen `INT`-Wert in einen `STRING`. Im Gegensatz dazu unterstützt `F_ULINT_AS_STRING` den größeren `ULINT`-Datentyp.
- **F_DINT_AS_STRING**: Konvertiert einen `DINT`-Wert in einen `STRING`. Ähnlich, aber für 32-Bit signed integers.

## Fazit
Der Funktionsblock `F_ULINT_AS_STRING` bietet eine einfache und effiziente Möglichkeit, `ULINT`-Werte in `STRING`-Werte umzuwandeln. Durch seine klare Schnittstelle und direkte Funktionsweise ist er ideal für Anwendungen, die eine solche Konvertierung erfordern.
