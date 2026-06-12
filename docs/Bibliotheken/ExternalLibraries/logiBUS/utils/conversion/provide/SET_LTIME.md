# SET_LTIME


![SET_LTIME](./SET_LTIME.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **SET_LTIME** dient dazu, einen Eingangswert vom Typ `LTIME` in eine als InOut deklarierte Variable zu schreiben. Dies ermöglicht es, den Wert einer externen Referenz (z. B. einer Instanzvariablen oder eines anderen Bausteins) direkt zu setzen. Die Verwendung einer InOut-Variable erlaubt eine effiziente Übergabe, ohne einen separaten Datenausgang zu benötigen.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
| Name | Typ | Kommentar |
|------|-----|-----------|
| REQ  | Event | Normaler Ausführungsanstoß. Verbunden mit den Daten `IN` und `OUT`. |

### **Ereignis-Ausgänge**
| Name | Typ | Kommentar |
|------|-----|-----------|
| CNF  | Event | Bestätigung der erfolgreichen Ausführung. Verbunden mit Daten `OUT`. |

### **Daten-Eingänge**
| Name | Typ | Initialwert | Kommentar |
|------|-----|-------------|-----------|
| IN   | LTIME | LT#0s | Wert, der in die Zielvariable geschrieben werden soll. |

### **Daten-Ausgänge**
| Name | Typ | Initialwert | Kommentar |
|------|-----|-------------|-----------|
| OUT  | LTIME | LT#0s | **InOut-Variable** – Zielvariable, die den übergebenen Wert erhält. Der FB schreibt den Wert von `IN` in diese Variable. Als InOut kann sie sowohl gelesen als auch von außen beschrieben werden. |

### **Adapter**
Keine.

## Funktionsweise
Bei einem Ereignis am Eingang **REQ** wird der Algorithmus `REQ` ausgeführt:
- Der Wert des Dateneingangs `IN` wird direkt in die InOut-Variable `OUT` kopiert.
- Anschließend wird das Ereignis **CNF** ausgegeben, um die erfolgreiche Zuweisung zu signalisieren.

Die Logik ist denkbar einfach und besteht aus einer einzigen Zuweisung:
```
OUT := IN;
```

## Technische Besonderheiten
- Der FB arbeitet ausschließlich mit dem Datentyp **LTIME** (Zeit mit hoher Auflösung, gemäß IEC 61499).
- Die Zielvariable `OUT` ist als **InOut** deklariert. Das bedeutet, dass sie von außen als Referenz übergeben wird. Änderungen, die der FB an `OUT` vornimmt, wirken sich unmittelbar auf die referenzierte Variable aus.
- Initial sind sowohl `IN` als auch `OUT` auf `LT#0s` gesetzt, um undefinierte Zustände zu vermeiden.
- Der Baustein ist ein **einfacher FB** (SimpleFB) mit nur einem Zustand, der sofort auf ein REQ-Ereignis reagiert.

## Zustandsübersicht
Der FB besitzt genau einen Zustand:

| Zustand | Aktion | Ausgabe |
|---------|--------|---------|
| REQ     | `REQ` (OUT := IN) | CNF |

Es gibt keine Verzweigungen oder Zeitsteuerungen. Der FB ist im Grunde kombinatorisch, da er sofort auf das Eingangsereignis reagiert.

## Anwendungsszenarien
- **Setzen einer zentralen Zeitbasis**: Wenn mehrere Bausteine auf eine gemeinsame LTIME-Variable zugreifen, kann `SET_LTIME` diese Variable aktualisieren.
- **Konfiguration von Laufzeiten**: In einer Steuerungsanwendung können Sollzeitwerte aus einer Konfigurationsschnittstelle in die entsprechenden InOut-Parameter geschrieben werden.
- **Test und Simulation**: Der Baustein eignet sich, um in Testumgebungen gezielt Werte in eine beobachtbare Variable zu schreiben.

## Vergleich mit ähnlichen Bausteinen
- **SET_TIME**: Arbeitet analog, jedoch mit dem Datentyp `TIME` (Sekundenauflösung). `SET_LTIME` bietet eine höhere Zeitauflösung (Nanosekunden) und ist daher für präzise Anwendungen geeignet.
- **MOVE-Bausteine**: Viele IEC-61499-Bibliotheken enthalten generische MOVE-FBs, die Werte von einem Eingang auf einen Ausgang kopieren. `SET_LTIME` spezialisiert sich auf `LTIME` und nutzt eine InOut-Referenz statt eines separaten Ausgangs, was in bestimmten Architekturen vorteilhaft sein kann.

## Fazit
`SET_LTIME` ist ein minimalistischer, aber nützlicher Funktionsblock zum gezielten Setzen einer LTIME-Variablen. Seine klare Schnittstelle und die Verwendung einer InOut-Referenz machen ihn zu einem effizienten Werkzeug in Zeitsteuerungs- und Konfigurationsszenarien. Der Baustein ist einfach zu verstehen und unkompliziert einzusetzen.