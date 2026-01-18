# F_USINT_TO_BYTE

```{index} single: F_USINT_TO_BYTE
```

<img width="1454" height="214" alt="F_USINT_TO_BYTE" src="https://github.com/user-attachments/assets/c086c1af-bc1b-492e-87cb-d7c3a52dd7a0" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_USINT_TO_BYTE` dient der Konvertierung eines vorzeichenlosen 8-Bit-Integer-Werts (USINT) in einen Byte-Wertyp (BYTE). Diese Konvertierung ist insbesondere in Szenarien erforderlich, wo Daten zwischen unterschiedlichen Formaten oder Systemen ausgetauscht werden müssen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Startet die Konvertierung. Dieser Eingang ist mit dem Daten-Eingang `IN` verknüpft.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Konvertierung. Dieser Ausgang ist mit dem Daten-Ausgang `OUT` verknüpft.

### **Daten-Eingänge**
- **IN**: Der Eingangswert vom Typ `USINT` (vorzeichenloser 8-Bit-Integer), der in einen `BYTE`-Wert konvertiert werden soll.

### **Daten-Ausgänge**
- **OUT**: Der Ausgangswert vom Typ `BYTE`, der das Ergebnis der Konvertierung darstellt.

### **Adapter**
- Keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock führt die Konvertierung durch, sobald das Ereignis `REQ` empfangen wird. Dabei wird der Wert am Eingang `IN` vom Typ `USINT` in einen `BYTE`-Wert umgewandelt und am Ausgang `OUT` ausgegeben. Das Ereignis `CNF` signalisiert die erfolgreiche Beendigung der Konvertierung.

## Technische Besonderheiten
- Die Konvertierung erfolgt direkt und ohne zusätzliche Verarbeitungsschritte.
- Der Block ist für die Verwendung in Echtzeitsystemen geeignet, da er keine zeitkritischen Operationen durchführt.

## Zustandsübersicht
1. **Idle**: Wartet auf das `REQ`-Ereignis.
2. **Konvertierung**: Führt die Konvertierung durch und gibt das Ergebnis über `OUT` aus.
3. **Bestätigung**: Sendet das `CNF`-Ereignis zur Bestätigung der erfolgreichen Konvertierung.

## Anwendungsszenarien
- Datenkonvertierung in Steuerungssystemen.
- Kommunikation zwischen Systemen mit unterschiedlichen Datentypen.
- Vorverarbeitung von Sensordaten.

## Vergleich mit ähnlichen Bausteinen
- **F_BYTE_TO_USINT**: Führt die umgekehrte Konvertierung durch (BYTE zu USINT).
- **F_INT_TO_STRING**: Konvertiert einen Integer-Wert in einen String, ist jedoch komplexer in der Handhabung.

## Fazit
Der `F_USINT_TO_BYTE`-Funktionsblock ist ein einfaches und effizientes Werkzeug zur Konvertierung von `USINT`- zu `BYTE`-Werten. Seine klare Schnittstellenstruktur und direkte Funktionsweise machen ihn ideal für den Einsatz in verschiedenen industriellen Anwendungen.
