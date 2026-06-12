# SET_DWORD


![SET_DWORD](./SET_DWORD.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsbaustein `SET_DWORD` dient dazu, einen DWORD-Wert über einen Eingang in eine als InOut deklarierte Zielvariable zu schreiben. Er stellt eine einfache und effiziente Möglichkeit dar, Werte im laufenden Betrieb zu setzen, ohne dass eine separate Zuweisung im Programm erfolgen muss.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
| Name | Typ | Comment |
|------|-----|---------|
| REQ  | Event | Normal Execution Request – löst das Schreiben aus |

Mit dem Ereignis `REQ` werden die Daten `IN` und `OUT` gleichzeitig bereitgestellt.

### **Ereignis-Ausgänge**
| Name | Typ | Comment |
|------|-----|---------|
| CNF  | Event | Execution Confirmation – wird nach erfolgreicher Ausführung gesendet |

Der Ausgang `CNF` referenziert die veränderte Variable `OUT`.

### **Daten-Eingänge**
| Name | Typ | Comment |
|------|-----|---------|
| IN   | DWORD | Wert, der in die Zielvariable geschrieben werden soll (Initialwert: 0) |

### **Daten-Ausgänge**
| Name | Typ | Comment |
|------|-----|---------|
| OUT  | DWORD | Zielvariable (InOut) – der Wert von `IN` wird hierhin geschrieben (Initialwert: 0) |

**Hinweis:** `OUT` ist als InOut-Variable deklariert, d. h. sie kann von außen referenziert werden und ihr Speicherort wird direkt durch den Baustein verändert. Sie erscheint im FB-Netzwerk sowohl als Ausgang als auch als Eingang.

### **Adapter**
Keine Adapter vorhanden.

## Funktionsweise
Der Baustein besitzt eine einzelne Aktion, die beim Eintreffen des Ereignisses `REQ` ausgeführt wird:

```structured text
OUT := IN;
```

Anschließend wird das Ereignis `CNF` gesendet. Der Baustein ist zustandslos und führt bei jedem `REQ` die Zuweisung aus, unabhängig vom aktuellen Wert.

## Technische Besonderheiten
- **InOut-Variable**: Die Verwendung einer InOut-Variable erlaubt es, direkt auf den Speicherort einer externen Variable zuzugreifen. Dies reduziert den Datenkopieraufwand und ermöglicht die Veränderung von Variablen, die auch an anderen Stellen im System genutzt werden.
- **Keine Zustandslogik**: Der Baustein implementiert keinen Zustandsautomaten mit mehreren Zuständen – er reagiert immer gleich auf das Eingangsereignis.
- **Initialwerte**: Beide Variablen sind mit 0 vorbelegt, werden aber in der Regel zur Laufzeit überschrieben.

## Zustandsübersicht
Der Baustein besteht aus einem einfachen Zustandsautomaten mit genau einem Zustand:

| Zustand | Auslösendes Ereignis | Aktion | Ausgang |
|---------|----------------------|--------|---------|
| `REQ`   | `REQ`                | `OUT := IN;` | `CNF` |

Es gibt keine Wartezustände oder Verzweigungen.

## Anwendungsszenarien
- **Konfiguration von Peripherie**: Setzen eines DWORD-Registers in einem Modul (z. B. Zeitbasis, Schwellwert).
- **Parameterweitergabe**: Übergabe eines konstanten oder berechneten Werts an eine global verfügbare Variable (z. B. über einen InOut-Datentyp).
- **Test und Debugging**: Temporäres Überschreiben eines Wertes während des Betriebs, ohne den Quellcode zu ändern.
- **Migration von Klartextzuweisungen**: Ersatz für eine einfache `OUT := IN`-Anweisung in einem IEC‑61499-Netzwerk durch einen wiederverwendbaren Baustein.

## Vergleich mit ähnlichen Bausteinen
- **MOVE / MV**: In vielen Bibliotheken vorhanden, arbeiten jedoch meist mit reinen Ein-/Ausgangsvariablen und erfordern einen expliziten Zwischenspeicher. `SET_DWORD` greift dagegen direkt auf eine bestehende Variable zu (InOut).
- **SET_BOOL / SET_INT / SET_REAL**: Analoge Bausteine für andere Datentypen; das Prinzip ist identisch, lediglich der Datentyp variiert.
- **WRITE_DWORD**: Einige Bibliotheken bieten einen Baustein, der über einen Adressbus schreibt. `SET_DWORD` ist einfacher und benötigt keine Adresslogik.

## Fazit
`SET_DWORD` ist ein minimaler, aber sehr nützlicher Funktionsbaustein für die direkte Wertzuweisung an eine DWORD‑InOut-Variable. Seine Einfachheit macht ihn fehlerunanfällig, und der Verzicht auf Zustandslogik sorgt für vorhersagbares Echtzeitverhalten. Er eignet sich besonders für Konfigurations- und Initialisierungsaufgaben, bei denen eine schnelle, unkomplizierte Wertübernahme erforderlich ist.