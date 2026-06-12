# SET_DINT


![SET_DINT](./SET_DINT.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsbaustein `SET_DINT` dient dazu, einen DINT-Wert von einem Dateneingang auf eine InOut-Variable zu schreiben. Er realisiert damit eine einfache Zuweisungsoperation für den Datentyp `DINT`. Der Baustein wird über ein Ereignis gesteuert und quittiert die erfolgreiche Ausführung mit einem Bestätigungsereignis.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Name | Typ   | Kommentar                     | Mit Variablen |
|------|-------|-------------------------------|---------------|
| REQ  | Event | Normaler Ausführungsanstoß    | IN, OUT       |

### **Ereignis-Ausgänge**

| Name | Typ   | Kommentar                    | Mit Variablen |
|------|-------|------------------------------|---------------|
| CNF  | Event | Bestätigung der Ausführung   | OUT           |

### **Daten-Eingänge**

| Name | Typ  | Kommentar            | Initialwert |
|------|------|----------------------|-------------|
| IN   | DINT | Wert, der geschrieben werden soll | 0           |

### **Daten-Ausgänge**

Der Baustein besitzt keine klassischen Datenausgänge, sondern einen InOut-Parameter (siehe unten). Das Bestätigungsereignis `CNF` ist mit dem Ausgang `OUT` verknüpft, sodass nach der Ausführung der aktualisierte Wert am Ausgang anliegt.

### **Adapter**

Keine.

## Funktionsweise

Bei einem Ereignis am Eingang `REQ` wird der Algorithmus `REQ` ausgeführt. Dieser kopiert den aktuellen Wert des Dateneingangs `IN` direkt in die InOut-Variable `OUT`. Anschließend wird das Bestätigungsereignis `CNF` gesendet.

Die Logik in Structured Text lautet:

```structuredtext
OUT := IN;
```

Die Ausführung ist atomar: Der Wert wird sofort und ohne Verzögerung übernommen.

## Technische Besonderheiten

- Der Baustein verwendet eine **InOut-Variable** (`OUT`). Diese Variable ist gleichzeitig Eingang und Ausgang und kann von außen gelesen und beschrieben werden. Dadurch kann der Baustein den Wert einer bestehenden Variable an Ort und Stelle überschreiben, ohne einen zusätzlichen Ausgang zu belegen.
- Der Baustein ist zustandslos – es gibt nur einen einzigen Ausführungszustand. Jeder Aufruf führt die gleiche einfache Zuweisung aus.
- Alle Variablen sind initial mit `0` vordefiniert.

## Zustandsübersicht

| Zustand | Aktion             | Ausgabeereignis |
|---------|--------------------|-----------------|
| REQ     | OUT := IN          | CNF             |

Der Baustein besitzt keine weiteren Zustände (keine Warteschleifen, keine Verzweigungen). Nach der Aktion wechselt er sofort wieder in den Bereitschaftszustand für den nächsten `REQ`.

## Anwendungsszenarien

- **Parameterübergabe:** Ein externer Wert (z. B. aus einer Konfigurationsschnittstelle) wird in eine lokale Variable einer Applikation geschrieben.
- **Signalweiterleitung:** Ein digitaler Integer-Wert soll von einem Signalpfad auf einen anderen umgeleitet werden, wobei der ursprüngliche Wert erhalten bleibt.
- **Initialisierung:** Beim Systemstart kann über `SET_DINT` ein definierter Startwert in eine Zustandsvariable eingetragen werden.
- **Test- und Debuggingzwecke:** Manuelles Setzen eines DINT-Wertes über eine HMI oder ein Skript.

## Vergleich mit ähnlichen Bausteinen

- **MOVE/DINT**: Standardisierte Bausteine wie `MOVE` aus der IEC‑61131‑3 führen ebenfalls Zuweisungen durch. `SET_DINT` ist auf den Typ `DINT` spezialisiert und bietet eine reduzierte Schnittstelle (nur ein Eingangsereignis, keine zusätzlichen Ausgänge).
- **SET_BOOL, SET_REAL, SET_SINT**: Analoge Bausteine für andere Datentypen existieren in der `logiBUS`-Bibliothek. Sie unterscheiden sich nur im Datentyp, die Funktionsweise ist identisch.
- **Direkte Zuweisung im Netzwerk**: In IEC‑61499 könnte man eine Zuweisung auch ohne Baustein durch eine direkte Datenverbindung realisieren. Der Baustein `SET_DINT` bietet jedoch eine explizite, ereignisgesteuerte Kapselung, die zur Laufzeit überwacht und getriggert werden kann.

## Fazit

`SET_DINT` ist ein einfacher, aber nützlicher Funktionsbaustein für die gezielte Zuweisung von DINT-Werten. Durch die Verwendung einer InOut-Variable bleibt die Schnittstelle schlank, und der Baustein kann direkt in bestehende Datenflüsse eingebunden werden. Seine klare, zustandslose Logik macht ihn zuverlässig und leicht verständlich – ideal für grundlegende Übergabeoperationen in Automatisierungsprojekten.