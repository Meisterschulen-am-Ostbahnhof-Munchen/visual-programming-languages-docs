# F_DWORD_TO_USINT

```{index} single: F_DWORD_TO_USINT
```

<img width="1255" height="182" alt="F_DWORD_TO_USINT" src="https://github.com/user-attachments/assets/4cdaf96f-2ab8-4655-8fed-b81775155fae" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_DWORD_TO_USINT` dient der Konvertierung eines 32-Bit-Wertes (DWORD) in einen 8-Bit-unsigned-Integer-Wert (USINT). Diese Konvertierung ist besonders nützlich, wenn Daten zwischen Systemen mit unterschiedlichen Wortbreiten ausgetauscht werden müssen.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
- **REQ**: Startet die Konvertierung. Wird dieser Eingang ausgelöst, wird der Wert am Daten-Eingang `IN` verarbeitet.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Konvertierung. Der konvertierte Wert steht am Daten-Ausgang `OUT` zur Verfügung.

### **Daten-Eingänge**
- **IN** (DWORD): Der 32-Bit-Wert, der in einen 8-Bit-unsigned-Integer-Wert konvertiert werden soll.

### **Daten-Ausgänge**
- **OUT** (USINT): Der resultierende 8-Bit-unsigned-Integer-Wert nach der Konvertierung.

### **Adapter**
Dieser Funktionsblock verfügt über keine Adapter-Schnittstellen.

## Funktionsweise
Der Funktionsblock führt die Konvertierung durch, indem der 32-Bit-Wert am Eingang `IN` in einen 8-Bit-unsigned-Integer-Wert umgewandelt wird. Die Konvertierung erfolgt durch die Funktion `DWORD_TO_USINT`, die den Wert entsprechend umwandelt. Bei der Konvertierung wird nur das niederwertigste Byte des DWORD-Wertes berücksichtigt, während die höherwertigen Bytes ignoriert werden.

## Technische Besonderheiten
- Die Konvertierung schneidet die höherwertigen Bytes ab, was zu einem Datenverlust führen kann, wenn der ursprüngliche DWORD-Wert größer als 255 ist.
- Der Funktionsblock ist deterministisch und führt die Konvertierung in einem einzigen Ausführungsschritt durch.

## Zustandsübersicht
Der Funktionsblock besitzt keine internen Zustände. Die Konvertierung wird bei jedem Auslösen des `REQ`-Ereignisses neu durchgeführt.

## Anwendungsszenarien
- Datenreduktion in Kommunikationsprotokollen, wo nur 8-Bit-Werte übertragen werden können.
- Anpassung von Datenformaten zwischen unterschiedlichen Systemkomponenten.
- Verwendung in Steuerungen, wo spezifische Hardware nur 8-Bit-Daten verarbeiten kann.

## Vergleich mit ähnlichen Bausteinen
- **F_WORD_TO_USINT**: Konvertiert einen 16-Bit-Wert (WORD) in einen 8-Bit-unsigned-Integer-Wert. Im Gegensatz dazu verarbeitet `F_DWORD_TO_USINT` 32-Bit-Werte.
- **F_DWORD_TO_BYTE**: Ähnlich in der Funktionalität, aber der Ausgangstyp ist BYTE, was ebenfalls 8 Bit umfasst, aber ohne Vorzeichen.

## Fazit
Der Funktionsblock `F_DWORD_TO_USINT` ist ein einfaches und effizientes Werkzeug zur Konvertierung von 32-Bit-Werten in 8-Bit-unsigned-Integer-Werte. Er eignet sich besonders für Anwendungen, bei denen Daten auf eine kleinere Wortbreite reduziert werden müssen. Aufgrund der möglichen Datenverluste bei großen Eingangswerten sollte seine Verwendung jedoch sorgfältig geplant werden.
