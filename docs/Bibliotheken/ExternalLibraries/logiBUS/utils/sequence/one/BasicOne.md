# BasicOne


![BasicOne](./BasicOne.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsbaustein **BasicOne** ist ein grundlegender, ereignisgesteuerter Baustein nach IEC 61499. Er dient als einfaches Sequenzelement zur Initialisierung, Ausführung einer Hauptoperation und ordnungsgemäßen Deinitialisierung. Der Baustein eignet sich besonders für Steuerungsabläufe, bei denen ein Ressourcenzustand (z. B. Gerät bereit) überwacht und zurückgesetzt werden muss. Der Baustein ist im Paket `logiBUS::utils::sequence::one` enthalten.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
| Ereignis | Typ | Mitgeführte Daten | Beschreibung |
|----------|-----|-------------------|--------------|
| `INIT`   | EInit | `QI` | Initialisierungsanforderung; die Transition hängt vom Wert des Qualifiers `QI` ab. |
| `REQ`    | Event | `QI`, `DI1` | Normale Ausführungsanforderung; startet die Hauptoperation. |

### **Ereignis-Ausgänge**
| Ereignis | Typ | Mitgeführte Daten | Beschreibung |
|----------|-----|-------------------|--------------|
| `INITO`  | EInit | `QO` | Bestätigung einer erfolgreichen Initialisierung oder Deinitialisierung. |
| `CNF`    | Event | `QO`, `DO1` | Bestätigung der normalen Ausführung; gibt den aktuellen Zustand aus. |

### **Daten-Eingänge**
| Name | Typ | Beschreibung |
|------|-----|--------------|
| `QI`  | BOOL | Eingangsqualifier – steuert, ob eine Initialisierung aktiv (`TRUE`) oder deinitialisierend (`FALSE`) ist. Beeinflusst auch die Ausführung der Hauptoperation. |
| `DI1` | BOOL | Erster Dateneingang; wird nur bei aktiver Initialisierung (`QI = TRUE`) während der normalen Operation auf den Ausgang `DO1` übertragen. |

### **Daten-Ausgänge**
| Name | Typ | Beschreibung |
|------|-----|--------------|
| `QO`  | BOOL | Ausgangsqualifier – spiegelt nach einer Aktion den Wert von `QI` wider (außer nach Deinitialisierung: dann `FALSE`). |
| `DO1` | BOOL | Erster Datenausgang; enthält bei einer normalen Operation den Wert von `DI1`, sofern `QI = TRUE`, ansonsten `FALSE`. |

### **Adapter**
Keine.

## Funktionsweise
Der Baustein durchläuft einen klar definierten Lebenszyklus:
1. **Startzustand (START)**: Nach dem Hochlauf wartet der Baustein auf ein `INIT`-Ereignis.
2. **Initialisierung (Init)**: Wird `INIT` mit `QI = TRUE` empfangen, führt der Baustein den Algorithmus *initialize* aus. Dabei wird `QO := QI` gesetzt (also `TRUE`). Anschließend wird `INITO` gesendet und der Baustein wechselt in den Zustand **Initialized**.
3. **Normalbetrieb (NormalOp)**: Im Zustand **Initialized** kann durch ein `REQ`-Ereignis die normale Operation gestartet. Der Algorithmus *normalOperation* setzt `QO := QI` (immer noch `TRUE`) und überträgt – wenn `QI = TRUE` ist – den Wert von `DI1` nach `DO1`. Danach wird `CNF` gesendet und der Baustein kehrt automatisch nach **Initialized** zurück.
4. **Deinitialisierung (DeInit)**: Wird im Zustand **Initialized** ein `INIT`-Ereignis mit `QI = FALSE` empfangen, führt der Baustein den Algorithmus *deInitialize* aus. Dieser setzt `QO := FALSE` und `DO1 := FALSE`. Anschließend wird `INITO` gesendet und der Baustein springt zurück in den Startzustand **START**.

Wichtig: Die normale Operation wird nur dann ausgeführt, wenn `QI = TRUE` ist. Bei `QI = FALSE` im `REQ`-Ereignis wird zwar der Algorithmus durchlaufen, aber `DO1` bleibt unverändert (er wird nicht auf `DI1` gesetzt; stattdessen bleibt der letzte Wert oder der Standardwert `FALSE` gemäß Algorithmus – bei `QI = FALSE` wird die IF‑Bedingung nicht erfüllt, daher ändert sich `DO1` nicht).

## Technische Besonderheiten
- **Ereignisabhängigkeit von QI**: Die Transition `INIT[TRUE = QI]` bzw. `INIT[FALSE = QI]` zeigt, dass das gleiche Ereignis `INIT` je nach Wert von `QI` unterschiedliche Zustandsübergänge auslöst. Dies ermöglicht eine kompakte Steuerung von Initialisierung und Deinitialisierung über ein einziges Ereignis.
- **Automatischer Rückfall**: Nach einem `REQ`-Ereignis kehrt der Baustein ohne externes Ereignis in den Zustand **Initialized** zurück (Transition mit Bedingung `1`). Dies vereinfacht die Anbindung an zyklische Abläufe.
- **Keine Selbsthemmung**: Der Baustein blockiert nicht; nach jeder erfolgreichen Ausführung ist er bereit für das nächste Ereignis.

## Zustandsübersicht
| Zustand | Beschreibung | Mögliche Aktionen |
|---------|--------------|-------------------|
| `START` | Initialer Ruhezustand nach Systemstart oder nach einer Deinitialisierung. | Wartet auf `INIT` mit `QI = TRUE`. |
| `Init` | Initialisierungsphase; setzt `QO = QI`. | Führt Algorithmus *initialize* aus, sendet `INITO`. |
| `Initialized` | Wartezustand nach erfolgreicher Initialisierung. | Kann auf `REQ` (startet NormalOp) oder auf `INIT` mit `QI = FALSE` (startet DeInit) reagieren. |
| `NormalOp` | Ausführung der Hauptoperation; überträgt `DI1` nach `DO1` (nur wenn `QI = TRUE`). | Führt Algorithmus *normalOperation* aus, sendet `CNF`. |
| `DeInit` | Deinitialisierungsphase; setzt `QO = FALSE` und `DO1 = FALSE`. | Führt Algorithmus *deInitialize* aus, sendet `INITO`. |

## Anwendungsszenarien
- **Initialisierung einer Komponente**: Ein Gerät muss beim Einschalten konfiguriert werden. Mit `INIT` (QI=TRUE) wird der Gerätezustand auf "bereit" gesetzt, `REQ` führt dann zyklisch die eigentliche Logik aus.
- **Ressourcenverwaltung**: Der Baustein kann als einfacher Sequenzer für eine einmalige Initialisierung und spätere Deinitialisierung verwendet werden (z. B. für eine Datenbankverbindung).
- **Sicherheitsorientierte Steuerung**: Durch den Qualifier `QI` kann die Ausgabe `DO1` nur dann den Eingangswert annehmen, wenn der Baustein initialisiert ist. Bei Deinitialisierung werden alle Ausgänge zurückgesetzt (`FALSE`).

## Vergleich mit ähnlichen Bausteinen
- **BasicBOOLEAN**: Ein einfacher Boolescher Baustein ohne Zustandsautomat, der nur auf ein Ereignis reagiert und einen Wert weitergibt. `BasicOne` bietet dagegen eine explizite Initialisierungs- und Deinitialisierungssequenz.
- **SR-Flipflop**: Ein Speicherbaustein mit Setzen und Rücksetzen. `BasicOne` ist eher ein Zustandsautomat, der einen einmaligen Start und Stopp abbildet, jedoch keine Haltefunktion besitzt.
- **SimpleCycle**: Ein zyklischer Baustein, der immer wieder die gleiche Operation ausführt. `BasicOne` unterscheidet zwischen Initialisierung und zyklischer Ausführung und erlaubt eine saubere Trennung.

## Fazit
Der Funktionsbaustein `BasicOne` ist ein hervorragendes Basiselement für Steuerungsprojekte, die eine kontrollierte Initialisierung, einen gesicherten Betrieb und eine definierte Deinitialisierung erfordern. Seine einfache Zustandsmaschine und die Abhängigkeit vom Qualifier `QI` machen ihn flexibel einsetzbar, ohne unnötige Komplexität. Er eignet sich sowohl für Einsteiger in die IEC-61499-Welt als auch für erfahrene Entwickler, die klare, wiederverwendbare Ablaufbausteine benötigen.