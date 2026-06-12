# NOOP_INIT


![NOOP_INIT](./NOOP_INIT.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **NOOP_INIT** (No Operation with INIT) dient als einfacher Durchschalt- oder Platzhalterbaustein. Er ermöglicht die Initialisierung sowie die normale Datenweitergabe eines Booleschen Signals von einem Eingang zu einem Ausgang. Die Besonderheit liegt in der zusätzlichen Behandlung des INIT-Ereignisses, das sowohl eine Bestätigung (INITO) als auch eine Datenweitergabe auslöst.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
| Name | Typ | Kommentar |
|------|-----|-----------|
| INIT | EInit | Initialisierungsanforderung |
| REQ  | Event | Normale Ausführungsanforderung (verbunden mit IN) |

### **Ereignis-Ausgänge**
| Name | Typ | Kommentar |
|------|-----|-----------|
| INITO | EInit | Initialisierungsbestätigung |
| CNF   | Event | Ausführungsbestätigung (verbunden mit OUT) |

### **Daten-Eingänge**
| Name | Typ | Kommentar |
|------|-----|-----------|
| IN   | BOOL | Eingangssignal |

### **Daten-Ausgänge**
| Name | Typ | Kommentar |
|------|-----|-----------|
| OUT  | BOOL | Ausgangssignal (entspricht IN nach einem Durchlauf) |

### **Adapter**
Keine Adapter vorhanden.

## Funktionsweise
Der Baustein verarbeitet eingehende Ereignisse wie folgt:

1. **INIT-Ereignis**:
   - Es wird sofort ein **INITO**-Ereignis ausgegeben.
   - Gleichzeitig wird intern der `F_MOVE`-Baustein angestoßen, der den Wert von `IN` nach `OUT` kopiert. Nach Abschluss dieses Kopiervorgangs wird das **CNF**-Ereignis ausgelöst.

2. **REQ-Ereignis**:
   - Es wird der gleiche `F_MOVE`-Baustein aktiviert, der `IN` nach `OUT` überträgt. Nach Fertigstellung wird **CNF** ausgegeben.

Im Ergebnis wird sowohl bei INIT als auch bei REQ eine Datenweitergabe durchgeführt und jeweils ein Bestätigungsereignis erzeugt. Der Datenausgang `OUT` entspricht stets dem zuletzt übernommenen Wert des Eingangs `IN`.

## Technische Besonderheiten
- Der Baustein nutzt intern eine Instanz des Standard-FBs `iec61131::selection::F_MOVE` für die Datenkopie.
- Die INIT-Behandlung ist zweigeteilt: Sie quittiert sofort mit `INITO` und führt parallel die Datenweitergabe aus. Dies kann für Initialisierungssequenzen nützlich sein, bei denen das System nach der ersten Übergabe eines Startwerts arbeiten soll.
- Es sind keine internen Zustände oder Timings vorhanden; die Reaktion erfolgt ereignisgesteuert.

## Zustandsübersicht
Der FB besitzt keinen expliziten Zustandsautomaten, das Verhalten ist rein ereignisgesteuert:
- Im Ruhezustand (kein Ereignis) warten die Eingänge.
- Bei **INIT** oder **REQ** wird die Datenkopie gestartet; nach deren Abschluss wird `CNF` gesendet. Bei INIT wird zusätzlich sofort `INITO` emittiert.

## Anwendungsszenarien
- **Platzhalter** in der Entwicklungsphase: Anstatt eines komplexen Bausteins wird NOOP_INIT eingefügt, um Datenflüsse zu testen.
- **Debugging**: Das explizite INIT-Ereignis kann verwendet werden, um einen initialen Wert zu setzen und gleichzeitig eine Bestätigung zu erhalten.
- **Signalkopplung**: Wenn ein Signal unverändert weitergeleitet werden muss, aber die INIT-Schnittstelle eines nachfolgenden Bausteins bedient werden soll.
- **Test von Initialisierungssequenzen**: Simulation einer Startroutine, die einen Wert setzt und quittiert.

## Vergleich mit ähnlichen Bausteinen
- **NOOP (ohne INIT)**: Einfacher Durchschaltbaustein ohne Initialisierungsereignis. NOOP_INIT erweitert dies um die INIT/INITO-Paarung.
- **MOVE (direkt)**: Ein reiner Datenkopierer ohne Ereignissteuerung; NOOP_INIT bietet eine ereignisgesteuerte Version mit Bestätigungen.
- **E_CYCLE oder E_PERMIT**: Diese Bausteine steuern Ereignisse, übertragen aber keine Daten. NOOP_INIT kombiniert Datenweitergabe mit Ereignisweiterleitung.

## Fazit
Der Funktionsblock **NOOP_INIT** ist ein einfacher, aber flexibler Hilfsbaustein für den ereignisgesteuerten Datentransport. Durch die Kombination von INIT- und REQ-Ereignissen eignet er sich besonders für Initialisierungsabläufe und Testumgebungen. Seine interne Struktur macht ihn leicht verständlich und gut in bestehende 4diac-Netzwerke integrierbar.