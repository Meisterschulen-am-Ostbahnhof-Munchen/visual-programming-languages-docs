# NOOP


![NOOP](./NOOP.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock NOOP („No Operation“) dient als reiner Durchlaufbaustein. Er kopiert den am Dateneingang `IN` anliegenden BOOL-Wert auf den Datenausgang `OUT`, sobald ein Ereignis am Eingang `REQ` eintritt. Anschließend wird der Ausgang `CNF` ausgelöst. Der FB führt keine logische oder arithmetische Operation aus, sondern leitet das Signal unverändert weiter.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
| Ereignis | Typ | Kommentar |
|----------|-----|-----------|
| `REQ`    | Event | Normaler Ausführungsimpuls |

### **Ereignis-Ausgänge**
| Ereignis | Typ | Kommentar |
|----------|-----|-----------|
| `CNF`    | Event | Bestätigung der Ausführung |

### **Daten-Eingänge**
| Name | Typ | Kommentar |
|------|-----|-----------|
| `IN` | BOOL | Eingangssignal |

### **Daten-Ausgänge**
| Name | Typ | Kommentar |
|------|-----|-----------|
| `OUT`| BOOL | Ausgangssignal (identisch mit `IN`) |

### **Adapter**
Keine.

## Funktionsweise
Intern besteht der Baustein aus einer Instanz von `F_MOVE` (aus der Bibliothek `iec61131::selection::F_MOVE`), die auf den Datentyp `BOOL` konfiguriert ist.  
- Bei einem Ereignis auf `REQ` wird der Wert von `IN` an `F_MOVE.IN` übergeben und eine Ausführung angestoßen.  
- Nach erfolgreicher Verarbeitung gibt `F_MOVE.OUT` den Wert aus, welcher auf `OUT` gelegt wird. Gleichzeitig wird `F_MOVE.CNF` ausgelöst, das den Ereignisausgang `CNF` aktiviert.  

Somit entspricht das Verhalten genau einer Durchschaltung: `OUT := IN`.

## Technische Besonderheiten
- Der FB verwendet intern einen vorgefertigten MOVE-Baustein, sodass keine eigene Zustandslogik notwendig ist.
- Die Datenpfade sind explizit auf `BOOL` ausgelegt. Eine Erweiterung auf andere Datentypen wäre durch Anpassung des `F_MOVE`-Attributes möglich, ist im vorliegenden Entwurf aber nicht vorgesehen.
- Es werden keine Seiteneffekte wie Verzögerungen oder Zustandsänderungen außerhalb der reinen Signalweitergabe realisiert.

## Zustandsübersicht
Da der Baustein keine eigene Zustandsmaschine besitzt, kann der Ablauf als einfacher Zweischritt betrachtet werden:
1. **Warten** – auf ein Ereignis `REQ`.
2. **Weiterleiten** – sofortige Übernahme von `IN` nach `OUT` und Ausgabe von `CNF`.

Es gibt keine internen Speicherzustände oder Verzweigungen.

## Anwendungsszenarien
- **Debugging und Test**: Einsatz als Platzhalter, um die Signalpfade in einem komplexen Netzwerk zu prüfen, ohne die Funktionalität zu beeinflussen.
- **Signalweiterleitung**: Wenn ein Ereignis-Signal unverändert durchgereicht werden muss, z. B. zur Synchronisation mehrerer Zweige.
- **Platzhalter für spätere Erweiterungen**: In einer frühen Entwicklungsphase kann NOOP an Stellen gesetzt werden, die später eine spezifische Verarbeitung erhalten sollen.
- **Kaskadierung von Ereignissen**: Durch die Ereignis-Kopplung können mehrere Empfänger nacheinander bedient werden.

## Vergleich mit ähnlichen Bausteinen
- **MOVE**: Ein MOVE-Baustein (wie der intern verwendete) führt ebenfalls eine Wertzuweisung aus. NOOP unterscheidet sich nur durch den Namen und die explizite Dokumentation als „keine Operation“. Beide sind funktional nahezu identisch, mit dem Unterschied, dass MOVE oft für beliebige Datentypen typisiert wird, während NOOP hier statisch auf BOOL festgelegt ist.
- **BISTABLE (RS / SR)**: Diese Bausteine ändern ihren Zustand basierend auf Eingängen. NOOP speichert keinen Zustand, sondern gibt nur den aktuellen Eingangswert aus.
- **CONSTANT**: Ein Konstanten-Baustein liefert immer einen festen Wert. NOOP hingegen reagiert auf wechselnde Eingänge und Ereignisse.

## Fazit
Der NOOP-Funktionsblock ist ein einfacher, aber nützlicher Baustein, der ohne eigene Logik auskommt. Er kopiert den eingehenden BOOL-Wert bei jedem Ereignis auf den Ausgang und bestätigt die Ausführung. Aufgrund seiner Durchschaltungseigenschaften eignet er sich hervorragend für Testzwecke, als Platzhalter oder zur ereignisgesteuerten Signalweitergabe in IEC 61499-Netzwerken.