# AUI_MUX_2


![AUI_MUX_2](./AUI_MUX_2.svg)

* * * * * * * * * *

## Einleitung
Der Funktionsblock **AUI_MUX_2** ist ein generischer Multiplexer für AUI-Adapter (unidirektionale Schnittstelle). Er wählt anhand eines Indexparameters einen von zwei Eingängen aus und leitet diesen an den Ausgang weiter. Der Baustein realisiert eine 2-zu-1-Auswahl für AUI-Datenströme.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
| Name | Typ | Kommentar |
|------|-----|-----------|
| REQ  | Event | Set Index K; übernimmt den Wert von K |

### **Ereignis-Ausgänge**
| Name | Typ | Kommentar |
|------|-----|-----------|
| CNF  | Event | Bestätigung, dass der Index K gesetzt wurde |

### **Daten-Eingänge**
| Name | Typ | Kommentar |
|------|-----|-----------|
| K    | UINT | Index für die Auswahl (0 = IN1, 1 = IN2) |

### **Daten-Ausgänge**
*Keine*

### **Adapter**
| Richtung | Name | Typ | Kommentar |
|----------|------|-----|-----------|
| Socket   | IN1  | `adapter::types::unidirectional::AUI` | Erster Eingangswert |
| Socket   | IN2  | `adapter::types::unidirectional::AUI` | Zweiter Eingangswert |
| Plug     | OUT  | `adapter::types::unidirectional::AUI` | Ausgang: IN1 für K = 0, IN2 für K = 1 |

## Funktionsweise
Ein Ereignis am Eingang **REQ** übernimmt den aktuellen Wert des Daten-Eingangs **K** und wählt den entsprechenden Adapter-Eingang aus:
- Bei **K = 0** wird der an **IN1** anliegende AUI-Datenstrom an den Ausgang **OUT** weitergeleitet.
- Bei **K = 1** wird der an **IN2** anliegende AUI-Datenstrom an den Ausgang **OUT** weitergeleitet.
- Für andere Werte von K ist das Verhalten undefiniert (es wird kein gültiger Ausgang gesetzt).

Nach erfolgreicher Umschaltung wird ein Ereignis am Ausgang **CNF** ausgegeben.

Der Baustein ist generisch ausgelegt und verwendet die Typ-Hash-Mechanik von Eclipse 4diac, um eine effiziente Codegenerierung zu ermöglichen.

## Technische Besonderheiten
- **Generischer Baustein**: Der FB ist als generischer Funktionsblock deklariert (`GenericClassName = 'GEN_AUI_MUX'`), sodass er für verschiedene AUI-Adaptervarianten mit unterschiedlichen Datenbreiten oder -typen eingesetzt werden kann.
- **Typ-Hash**: Über das Attribut `eclipse4diac::core::TypeHash` wird eine eindeutige Hash-Prüfsumme für den generierten Code bereitgestellt, was die Wiederverwendung und Kompilierung optimiert.
- **Paket-Struktur**: Der FB gehört zum Paket `adapter::selection::unidirectional`, was auf eine klare Modularisierung hinweist.

## Zustandsübersicht
Der Funktionsblock besitzt keinen expliziten Zustandsautomaten. Die Verarbeitung erfolgt ereignisgesteuert: Bei jedem **REQ**-Ereignis wird der Ausgang entsprechend dem aktuellen **K**-Wert umgeschaltet. Der Baustein ist daher als rein kombinatorisch bzw. als einfaches Schaltwerk ohne internen Zustand zu betrachten.

## Anwendungsszenarien
- **Auswahl zwischen zwei AUI-Datenquellen**: z. B. Umschalten zwischen zwei Sensoren oder Steuerungssignalen in der Automatisierungstechnik.
- **Redundanzumschaltung**: Fallback auf einen zweiten AUI-Pfad, falls der erste ausfällt.
- **Konfigurierbare Signalweiche**: In modularen Steuerungssystemen können unterschiedliche AUI-Adapter dynamisch an einen gemeinsamen Ausgang geschaltet werden.

## Vergleich mit ähnlichen Bausteinen
- **MUX_2 (Standard IEC 61499)**: Ein allgemeiner 2-zu-1-Multiplexer, der mit einfachen Datentypen (z. B. ANY) arbeitet. AUI_MUX_2 ist dagegen speziell auf die AUI-Adapter-Schnittstelle zugeschnitten und nutzt die Adapter-basierte Kommunikation.
- **AUI_MUX_4 oder AUI_MUX_8**: Erweiterte Versionen mit mehr Eingängen; AUI_MUX_2 bietet eine minimalistische, intuitive 2-Kanal-Auswahl.
- **AUI_MERGE**: Ein Baustein, der mehrere AUI-Ströme zusammenführt (datengetrieben) – hier handelt es sich um eine aktive Auswahl, nicht um eine Merge-Operation.

## Fazit
Der **AUI_MUX_2** ist ein kompakter, generischer Multiplexer für unidirektionale AUI-Schnittstellen. Er ermöglicht eine saubere, ereignisgesteuerte Umschaltung zwischen zwei Eingangsadaptern und eignet sich ideal für alle Anwendungen, bei denen eine einfache 2-zu-1-Auswahl auf AUI-Ebene benötigt wird. Dank seiner generischen Auslegung kann er flexibel an verschiedene AUI-Datentypen angepasst werden.