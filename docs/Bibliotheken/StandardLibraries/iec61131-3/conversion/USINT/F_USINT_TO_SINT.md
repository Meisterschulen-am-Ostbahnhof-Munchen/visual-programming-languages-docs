# F_USINT_TO_SINT

```{index} single: F_USINT_TO_SINT
```

<img width="1451" height="214" alt="F_USINT_TO_SINT" src="https://github.com/user-attachments/assets/6cc23cdf-2a2a-43cf-b2fe-3158508fb208" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_USINT_TO_SINT` dient der Konvertierung eines vorzeichenlosen 8-Bit-Integer-Werts (USINT) in einen vorzeichenbehafteten 8-Bit-Integer-Wert (SINT). Dieser Baustein ist besonders nützlich, wenn Daten zwischen Systemen ausgetauscht werden, die unterschiedliche Datentypen verwenden.

![F_USINT_TO_SINT](F_USINT_TO_SINT.svg)

## Schnittstellenstruktur
### **Ereignis-Eingänge**
- **REQ**: Startet die Konvertierung. Bei Aktivierung wird der Eingangswert `IN` verarbeitet.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Konvertierung. Der Ausgangswert `OUT` ist dann verfügbar.

### **Daten-Eingänge**
- **IN** (USINT): Der vorzeichenlose 8-Bit-Integer-Wert, der konvertiert werden soll.

### **Daten-Ausgänge**
- **OUT** (SINT): Der resultierende vorzeichenbehaftete 8-Bit-Integer-Wert nach der Konvertierung.

### **Adapter**
Keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock führt die Konvertierung durch, indem er den USINT-Wert `IN` in einen SINT-Wert `OUT` umwandelt. Die Konvertierung erfolgt direkt bei Aktivierung des `REQ`-Ereignisses, und das Ergebnis wird über das `CNF`-Ereignis ausgegeben.

## Technische Besonderheiten
- Die Konvertierung erfolgt ohne zusätzliche Parameter oder Konfiguration.
- Der Algorithmus ist in Structured Text (ST) implementiert und verwendet die Funktion `USINT_TO_SINT`.

## Zustandsübersicht
1. **Idle**: Wartet auf das `REQ`-Ereignis.
2. **Processing**: Führt die Konvertierung durch.
3. **Completed**: Sendet das `CNF`-Ereignis mit dem Ergebnis.

## Anwendungsszenarien
- Datenkonvertierung in Steuerungssystemen.
- Kommunikation zwischen Geräten mit unterschiedlichen Datentypen.
- Vorverarbeitung von Sensordaten.

## Vergleich mit ähnlichen Bausteinen
- Ähnliche Bausteine wie `F_INT_TO_REAL` oder `F_BOOL_TO_INT` bieten Konvertierungen zwischen anderen Datentypen.
- `F_USINT_TO_SINT` ist spezialisiert auf die Konvertierung zwischen 8-Bit-Integer-Typen.

## Fazit
Der `F_USINT_TO_SINT`-Funktionsblock ist ein einfacher und effizienter Baustein für die Konvertierung zwischen vorzeichenlosen und vorzeichenbehafteten 8-Bit-Integer-Werten. Seine klare Schnittstelle und direkte Funktionsweise machen ihn ideal für den Einsatz in verschiedenen Steuerungs- und Kommunikationsanwendungen.