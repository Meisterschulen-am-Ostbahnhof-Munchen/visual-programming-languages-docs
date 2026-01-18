# FB_CTD_ULINT

```{index} single: FB_CTD_ULINT
```

<img width="1411" height="282" alt="FB_CTD_ULINT" src="https://github.com/user-attachments/assets/47813539-b542-43ce-82f2-a1f5ec03073f" />

* * * * * * * * * *
## Einleitung
Der FB_CTD_ULINT ist ein Abwärtszähler (Down Counter) für den Datentyp ULINT (Unsigned Long Integer). Er wird verwendet, um Werte von einem vorgegebenen Startwert aus abwärts zu zählen und signalisiert, wenn der Zählerstand den Wert 0 erreicht oder unterschreitet.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
- **REQ**: Normaler Ausführungsanforderung. Wird verwendet, um den Zähler zu aktualisieren. Verknüpft mit den Daten-Eingängen CD, PV und LD.

### **Ereignis-Ausgänge**
- **CNF**: Ausführungsbestätigung. Wird ausgelöst, nachdem der Zähler aktualisiert wurde. Verknüpft mit den Daten-Ausgängen Q und CV.

### **Daten-Eingänge**
- **CD (BOOL)**: Signalisiert, dass der Zähler um 1 verringert werden soll (Count Down).
- **LD (BOOL)**: Signalisiert, dass der Zähler mit dem Wert von PV geladen werden soll (Load).
- **PV (ULINT)**: Der voreingestellte Wert (Preset Value), mit dem der Zähler geladen wird, wenn LD aktiviert ist.

### **Daten-Ausgänge**
- **Q (BOOL)**: Signalisiert, ob der Zählerstand kleiner oder gleich 0 ist.
- **CV (ULINT)**: Der aktuelle Zählerstand (Count Value).

### **Adapter**
Es sind keine Adapter für diesen Funktionsblock definiert.

## Funktionsweise
Der Funktionsblock arbeitet nach folgenden Regeln:
1. Wenn LD (Load) aktiviert ist, wird der Zählerstand (CV) auf den vorgegebenen Wert (PV) gesetzt.
2. Wenn CD (Count Down) aktiviert ist und der Zählerstand (CV) größer als 0 ist, wird der Zählerstand um 1 verringert.
3. Der Ausgang Q wird auf TRUE gesetzt, wenn der Zählerstand (CV) kleiner oder gleich 0 ist.

## Technische Besonderheiten
- Der Zähler arbeitet mit dem Datentyp ULINT, was sehr große positive Zahlen ermöglicht (0 bis 18.446.744.073.709.551.615).
- Der Zähler wird nur aktualisiert, wenn das REQ-Ereignis ausgelöst wird.

## Zustandsübersicht
- **Initialisierung**: Der Zählerstand (CV) ist undefiniert bis zum ersten REQ-Ereignis.
- **Laden (LD)**: CV wird auf PV gesetzt.
- **Zählen (CD)**: CV wird um 1 verringert, solange CV > 0.
- **Ausgang Q**: TRUE, wenn CV ≤ 0.

## Anwendungsszenarien
- Steuerung von Produktionsprozessen mit Abwärtszählung (z.B. Verbleibende Teile in einem Lager).
- Zeitsteuerung mit großen Zeitintervallen.
- Überwachung von Ereignissen mit begrenzter Anzahl.

## Vergleich mit ähnlichen Bausteinen
- Im Vergleich zu anderen Zählern (z.B. FB_CTD_INT) bietet dieser Baustein eine größere Zahlenreichweite durch ULINT.
- Ähnlich wie FB_CTD, aber speziell für ULINT-Werte optimiert.

## Fazit
Der FB_CTD_ULINT ist ein leistungsfähiger Abwärtszähler für Anwendungen, die sehr große Zählbereiche erfordern. Seine einfache und klare Schnittstelle macht ihn leicht integrierbar in verschiedene Steuerungssysteme.
