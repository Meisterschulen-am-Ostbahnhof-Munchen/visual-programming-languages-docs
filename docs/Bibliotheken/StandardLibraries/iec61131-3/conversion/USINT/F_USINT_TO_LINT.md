# F_USINT_TO_LINT

```{index} single: F_USINT_TO_LINT
```

<img width="1448" height="214" alt="F_USINT_TO_LINT" src="https://github.com/user-attachments/assets/d5f2a448-fc5d-4ba6-952d-0852c28b6ea5" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_USINT_TO_LINT` dient der Konvertierung eines `USINT`-Wertes (8-Bit unsigned integer) in einen `LINT`-Wert (64-Bit signed integer). Diese Konvertierung ist besonders nützlich, wenn Werte aus kleineren Datentypen in größere umgewandelt werden müssen, ohne dabei die ursprüngliche Information zu verlieren.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
- **REQ**: Startet die Konvertierung. Der Eingang ist mit dem Daten-Eingang `IN` verknüpft.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Konvertierung. Der Ausgang ist mit dem Daten-Ausgang `OUT` verknüpft.

### **Daten-Eingänge**
- **IN**: Der Eingangswert vom Typ `USINT`, der konvertiert werden soll.

### **Daten-Ausgänge**
- **OUT**: Der konvertierte Ausgangswert vom Typ `LINT`.

### **Adapter**
Es sind keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock führt eine direkte Zuweisung des Eingangswertes `IN` zum Ausgangswert `OUT` durch. Da `USINT` ein 8-Bit unsigned integer und `LINT` ein 64-Bit signed integer ist, wird der Wert ohne Änderung des numerischen Werts in den größeren Datentyp umgewandelt.

## Technische Besonderheiten
- **Algorithmus**: Der Algorithmus besteht aus einer einfachen Zuweisung (`OUT := IN;`).
- **Datentyp-Kompatibilität**: Da `USINT` ein unsigned Datentyp ist und `LINT` signed, wird der Wert implizit erweitert, ohne dass es zu Datenverlust kommt.

## Zustandsübersicht
Der Funktionsblock hat keine internen Zustände. Die Konvertierung erfolgt sofort bei Empfang des `REQ`-Ereignisses.

## Anwendungsszenarien
- **Datenverarbeitung**: Wenn Werte aus kleineren in größere Datentypen umgewandelt werden müssen.
- **Kommunikation**: Bei der Übertragung von Daten zwischen Systemen mit unterschiedlichen Datentyp-Anforderungen.

## Vergleich mit ähnlichen Bausteinen
- **F_USINT_TO_INT**: Konvertiert `USINT` zu `INT` (16-Bit signed integer). Im Gegensatz dazu bietet `F_USINT_TO_LINT` eine größere Reichweite durch den 64-Bit Ausgang.
- **F_USINT_TO_ULINT**: Konvertiert `USINT` zu `ULINT` (64-Bit unsigned integer). Hier wird der Ausgang ebenfalls als unsigned behandelt.

## Fazit
Der `F_USINT_TO_LINT` Funktionsblock ist ein einfacher, aber effektiver Baustein zur Konvertierung von 8-Bit unsigned integer Werten in 64-Bit signed integer Werte. Durch seine direkte und verlustfreie Umwandlung eignet er sich ideal für Anwendungen, bei denen die Erhaltung des numerischen Werts in einem größeren Datentyp erforderlich ist.