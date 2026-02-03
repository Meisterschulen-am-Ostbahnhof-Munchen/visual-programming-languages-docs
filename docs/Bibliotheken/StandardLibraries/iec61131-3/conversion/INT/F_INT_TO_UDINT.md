# F_INT_TO_UDINT

```{index} single: F_INT_TO_UDINT
```

<img width="1232" height="187" alt="F_INT_TO_UDINT" src="https://github.com/user-attachments/assets/8bceda1f-dc12-42bd-a8b4-17dea9411990" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_INT_TO_UDINT` dient der Konvertierung eines vorzeichenbehafteten 16-Bit Integer-Werts (`INT`) in einen vorzeichenlosen 32-Bit Integer-Wert (`UDINT`). Diese Konvertierung ist insbesondere in Szenarien erforderlich, in denen Daten zwischen Systemen mit unterschiedlichen Datentypen ausgetauscht werden müssen.

![F_INT_TO_UDINT](F_INT_TO_UDINT.svg)

## Schnittstellenstruktur
### **Ereignis-Eingänge**
- **REQ**: Startet die Konvertierung. Der Eingang ist mit dem Daten-Eingang `IN` verknüpft.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Konvertierung. Der Ausgang ist mit dem Daten-Ausgang `OUT` verknüpft.

### **Daten-Eingänge**
- **IN**: Der vorzeichenbehaftete 16-Bit Integer-Wert (`INT`), der konvertiert werden soll.

### **Daten-Ausgänge**
- **OUT**: Der resultierende vorzeichenlose 32-Bit Integer-Wert (`UDINT`).

### **Adapter**
- Keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock führt die Konvertierung von `INT` zu `UDINT` durch, sobald das Ereignis `REQ` empfangen wird. Die Konvertierung erfolgt mittels der Funktion `INT_TO_UDINT(IN)`, die den Eingabewert `IN` in den entsprechenden `UDINT`-Wert umwandelt. Nach erfolgreicher Konvertierung wird das Ereignis `CNF` ausgelöst, und der konvertierte Wert steht am Ausgang `OUT` zur Verfügung.

## Technische Besonderheiten
- Die Konvertierung erfolgt ohne zusätzliche Parameter oder Konfiguration.
- Der Funktionsblock ist für den Einsatz in Echtzeitsystemen geeignet, da er deterministisch arbeitet.

## Zustandsübersicht
1. **Idle-Zustand**: Wartet auf das Ereignis `REQ`.
2. **Konvertierungszustand**: Führt die Konvertierung durch und setzt den Ausgang `OUT`.
3. **Bestätigungszustand**: Löst das Ereignis `CNF` aus und kehrt in den Idle-Zustand zurück.

## Anwendungsszenarien
- Datenkonvertierung in Steuerungssystemen, die unterschiedliche Datentypen verwenden.
- Integration von Sensordaten, die als `INT` vorliegen, in Systeme, die `UDINT` erfordern.
- Kompatibilitätslayer zwischen verschiedenen Hardware- oder Softwarekomponenten.

## ⚖️ Vergleich mit ähnlichen Bausteinen
- Ähnliche Funktionsblöcke wie `F_DINT_TO_UDINT` oder `F_SINT_TO_UDINT` bieten Konvertierungen zwischen anderen Datentypen, jedoch nicht speziell für `INT` zu `UDINT`.
- Im Gegensatz zu generischen Konvertierungsblöcken ist `F_INT_TO_UDINT` auf eine spezifische Konvertierung optimiert.

## Fazit
Der Funktionsblock `F_INT_TO_UDINT` ist ein spezialisiertes und effizientes Werkzeug zur Konvertierung von vorzeichenbehafteten 16-Bit Integer-Werten in vorzeichenlose 32-Bit Integer-Werte. Seine einfache Schnittstelle und deterministische Funktionsweise machen ihn ideal für den Einsatz in Echtzeitanwendungen.