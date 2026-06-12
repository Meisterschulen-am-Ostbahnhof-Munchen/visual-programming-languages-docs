# AE_MUX_3


![AE_MUX_3](./AE_MUX_3.svg)

* * * * * * * * * *

## Einleitung
Der Funktionsblock **AE_MUX_3** ist ein generischer Multiplexer für den AE-Adatertyp (unidirektional). Er wählt einen von drei analogen oder anderen AE-Signaleingängen aus und leitet diesen auf einen gemeinsamen Ausgang weiter. Die Auswahl erfolgt über einen numerischen Index (K). Der Baustein eignet sich besonders für Anwendungen, bei denen abhängig von einer Bedingung verschiedene Signalquellen an eine nachfolgende Verarbeitungseinheit durchgeschaltet werden müssen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
| Name | Datentyp | Beschreibung |
|------|----------|--------------|
| REQ  | Event    | Startet die Umschaltung auf den über `K` festgelegten Eingang. |

### **Ereignis-Ausgänge**
| Name | Datentyp | Beschreibung |
|------|----------|--------------|
| CNF  | Event    | Bestätigt, dass die Umschaltung auf den gewählten Eingang abgeschlossen ist. |

### **Daten-Eingänge**
| Name | Datentyp | Beschreibung |
|------|----------|--------------|
| K    | UINT     | Index des auszuwählenden Eingangs: 0 → IN1, 1 → IN2, 2 → IN3. |

### **Daten-Ausgänge**
Keine.

### **Adapter**
**Ausgang (Plug)**
| Name | Typ                              | Beschreibung |
|------|----------------------------------|--------------|
| OUT  | adapter::types::unidirectional::AE | Ausgang, der den ausgewählten Eingang (IN1/IN2/IN3) durchschaltet. |

**Eingänge (Sockets)**
| Name | Typ                              | Beschreibung |
|------|----------------------------------|--------------|
| IN1  | adapter::types::unidirectional::AE | Erster AE-Eingang – wird bei K=0 an OUT gelegt. |
| IN2  | adapter::types::unidirectional::AE | Zweiter AE-Eingang – wird bei K=1 an OUT gelegt. |
| IN3  | adapter::types::unidirectional::AE | Dritter AE-Eingang – wird bei K=2 an OUT gelegt. |

## Funktionsweise
1. Der Baustein wartet auf ein Ereignis am Eingang **REQ**.
2. Bei Eintreffen von REQ wird der aktuelle Wert des Index **K** ausgewertet:
   - K = 0 → Der Adapter **IN1** wird auf den Ausgang **OUT** umgeschaltet.
   - K = 1 → Der Adapter **IN2** wird auf **OUT** umgeschaltet.
   - K = 2 → Der Adapter **IN3** wird auf **OUT** umgeschaltet.
3. Nach erfolgreicher Umschaltung wird das Ereignis **CNF** ausgegeben, um dem aufrufenden Baustein die Beendigung der Operation zu signalisieren.

Die Umschaltung erfolgt sofort – es gibt keine zusätzliche Verzögerung oder Zwischenzustände.

## Technische Besonderheiten
- **Generischer Baustein:** Der FB trägt das Attribut `GenericClassName = 'GEN_AE_MUX'` und ist daher als generischer FB in der 4diac-IDE nutzbar. Das ermöglicht eine flexible Anpassung an unterschiedliche AE-Typen.
- **Lizenz:** Der Baustein wird unter der **Eclipse Public License 2.0** bereitgestellt. Er ist quelloffen und darf gemäß den Lizenzbedingungen verwendet, geändert und weitergegeben werden.
- **Verwendeter Adaptertyp:** Sowohl die Eingangs-Sockets als auch der Ausgangs-Plug verwenden den Typ `adapter::types::unidirectional::AE`. Dieser Adapter überträgt Werte nur in eine Richtung (vom Socket zum Plug) und eignet sich für einfache analoge oder binäre Signale.

## Zustandsübersicht
Der **AE_MUX_3** besitzt keinen expliziten Zustandsautomaten (ECA). Die Funktionsweise ist rein ereignisgetriggert:  
- Im Ruhezustand wartet der Baustein auf ein REQ-Ereignis.  
- Nach REQ erfolgt die Umschaltung, gefolgt von CNF.  
Danach kehrt er in den Ruhezustand zurück. Es gibt keine persistenten internen Zustände.

## Anwendungsszenarien
- **Sensorauswahl:** In einer Maschinensteuerung sollen unterschiedliche Sensoren (z. B. Drucksensoren) je nach Betriebsmodus ausgewertet werden. Mit AE_MUX_3 kann der passende Sensor über einen Index an die Regelung durchgeschaltet werden.
- **Signalrouting:** In einer modularen Anlage werden analoge AE-Signale von verschiedenen Modulen eingesammelt und über einen gemeinsamen Bus weitergeleitet. Der Baustein ermöglicht die dynamische Auswahl.
- **Test- und Diagnosesystem:** Für manuelle Tests kann zwischen dem normalen Betriebssignal und einem Testsignal umgeschaltet werden, ohne die Verkabelung zu ändern.

## Vergleich mit ähnlichen Bausteinen
- **AE_MUX_2:** Bietet nur zwei Eingänge (K=0,1) und ist kompakter, wenn nur zwei Quellen benötigt werden.
- **AE_MUX_N:** Ein erweiterbarer Multiplexer, der über eine Liste von Eingängen konfiguriert wird (z. B. über ein Array). AE_MUX_3 hingegen hat fest drei Eingänge, was eine einfachere Struktur und geringere Komplexität bietet.
- **MUX (für Basis-Datentypen):** In der Standardbibliothek gibt es Multiplexer für einfache Typen (BOOL, INT, REAL). Der AE_MUX_3 ist speziell für Adapter des Typs `AE` ausgelegt und daher für Signalpfade geeignet, die mehrere Werte oder strukturierte Daten transportieren.

## Fazit
Der **AE_MUX_3** ist ein einfacher, aber robuster Multiplexer für drei AE-Signale. Durch die Indexauswahl über REQ und K lässt er sich leicht in Steuerungslogiken einbinden. Die Generizität und die klare Trennung von Ereignis- und Datenpfaden machen ihn zu einem nützlichen Werkzeug für modulare, ereignisgesteuerte Automatisierungslösungen.